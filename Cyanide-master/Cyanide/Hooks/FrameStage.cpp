#include "main.h"
#include "skinchanger.h"
//#include "../Hacks/test.hpp"


void MakeNoflash(ClientFrameStage_t stage) {
    
    if (!pEngine->IsInGame())
        return;
    
    if(!vars.misc.noflash)
        return;
    
    if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return;
    
    if (vars.misc.noflash) {
        *localplayer->GetFlashMaxAlpha() = 255.0f - vars.misc.flashalpha;
    } else {
        *localplayer->GetFlashMaxAlpha() = 255.0f;
    }
}


void hkFrameStage(void* thisptr, ClientFrameStage_t curStage) {
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return;
    
    Vector* PointerPunch = nullptr;
    Vector* PointerView = nullptr;
    
    Vector VecPunch, VecView;
    
    if (curStage == ClientFrameStage_t::FRAME_RENDER_START && (pEngine->IsConnected() && pEngine->IsInGame())) {
        if(local->GetLifeState() == LIFE_ALIVE) {
            if(vars.misc.thirdpersonmode) {
                *reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(local) + offsets.DT_BasePlayer.deadflag + 0x4) = tpangles;
            }
        }
    }
    
    if(curStage == ClientFrameStage_t::FRAME_RENDER_START && vars.misc.enabled && vars.misc.novisualrecoil) {
        if(local) {
            if(local->GetLifeState() == LIFE_ALIVE) {
                
                PointerPunch = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_aimPunchAngle);
                PointerView = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_viewPunchAngle);
                
                
                VecPunch = *PointerPunch;
                VecView = *PointerView;
                
                PointerPunch->Init();
                PointerView->Init();
            }
        }
    }
    
    if(vars.misc.noflash)
        MakeNoflash(curStage);
    
    if(vars.visuals.skinc) {
        MakeSkinChanger(curStage);
    }

    
    clientvmt->GetOriginalMethod<tFrameStage>(37)(thisptr, curStage);
    
    if(curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
        
        for(int i = 1; i < 64; i++) {
            
            auto* entity = pEntList->GetClientEntity(i);
            
            if(!entity) continue;
            if(entity->GetLifeState() != 0) continue;
            if(entity->GetHealth() < 1) continue;
            if(entity->GetDormant()) continue;
            if(entity->GetGhost())
                continue;
            if(entity == local) continue;
            if(!gCorrections[entity->GetIndex()].resolved) continue;
            
        }
    }
    
    if(PointerPunch && PointerView) {
        *PointerPunch = VecPunch;
        *PointerView = VecView;
    }
}
