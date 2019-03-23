//#include "skinchanger.h"
#include "../Config/Config.h"
#include "../Config/skins.h"

void applySkins() {
    
    int localplayer_index = pEngine->GetLocalPlayer();
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(localplayer_index);
    
    if (!local || local->GetHealth() < 1)
        return;
    
    
    player_info_t localplayer_info;
    pEngine->GetPlayerInfo(localplayer_index, &localplayer_info);
    
    int* pWeapons = local->GetWeapons();
    
    if(pWeapons) {
        for(int i = 0; pWeapons[i]; i++){
            C_BaseAttributableItem* weapon = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(pWeapons[i]);
            
            if (!weapon)
                continue;
            
            short* item_definition_index = weapon->GetItemDefinitionIndex();
            
            if (*item_definition_index == 0)
                continue;
            
            const char* weaponConfigName = ItemDefIndex.at(*item_definition_index).entity_name;
            
            if (config->HasWeaponConfiguration(weaponConfigName)) {
                
                const cSkin& weapon_config = config->GetWeaponConfiguration(weaponConfigName);
                
                if (weapon_config.ItemDefinition != -1) {
                    
                    if (ItemDefIndex.find(weapon_config.ItemDefinition) != ItemDefIndex.end()) {
                        
                        *reinterpret_cast<int*>(weapon->GetModelIndex()) = pModelInfo->GetModelIndex(ItemDefIndex.at(weapon_config.ItemDefinition).model);
                        
                        if (ItemDefIndex.find(*item_definition_index) != ItemDefIndex.end()) {
                            
                            //                 const Item_t& original_item = ItemDefIndex.at(*item_definition_index);
                            //             const Item_t& replacement_item = ItemDefIndex.at(weapon_config.ItemDefinition);
                            *item_definition_index = weapon_config.ItemDefinition;
                        }
                    }
                }
                
                
                
                *weapon->GetEntityQuality() = 4;
                *weapon->GetFallbackWear() = 0.000000000001f;
                *weapon->GetFallbackStatTrak() = -1;
                *weapon->GetItemIDHigh() = -1;
                *weapon->GetAccountID() = localplayer_info.xuidlow;
                
                
                if (weapon_config.Paintkit != -1)
                    *weapon->GetFallbackPaintKit() = weapon_config.Paintkit;
                
                if (weapon_config.Seed != -1)
                    *weapon->GetFallbackSeed() = weapon_config.Seed;
                
                
                
            }
        }
        
        C_BaseViewModel* viewmodel = (C_BaseViewModel*)pEntList->GetClientEntityFromHandle(local->GetViewModel());
        
        if (!viewmodel)
            return;
        
        CBaseHandle viewmodel_weapon_handle = viewmodel->GetWeapon();
        
        if (viewmodel_weapon_handle == INVALID_EHANDLE_INDEX)
            return;
        
        C_BaseAttributableItem* viewmodel_weapon = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(viewmodel_weapon_handle);
        
        if (!viewmodel_weapon)
            return;
        
        
        if (ItemDefIndex.find(*viewmodel_weapon->GetItemDefinitionIndex()) != ItemDefIndex.end()) {
            
            const Item_t& override_weapon = ItemDefIndex.at(*viewmodel_weapon->GetItemDefinitionIndex());
            *viewmodel->GetModelIndex() = pModelInfo->GetModelIndex(override_weapon.model);
            
        }
    }
    return;
}

void MakeSkinChanger(ClientFrameStage_t stage) {
    
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
        
        C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        
        if(local && local->GetHealth() > 0)
            applySkins();
        
    }
}
bool glovesUpdated = true;

void ApplyCustomGloves(C_BaseEntity* pLocal) {
    
    if (!pEntList->GetClientEntityFromHandle((void*)pLocal->GetWearables())) {
        for (ClientClass* pClass = pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext) {
            if (pClass->m_ClassID != (int)EClassIds::CEconWearable)
                continue;
            
            int entry = (pEntList->GetHighestEntityIndex() + 1);
            int    serial = RandomInt(0x0, 0xFFF);
            
            pClass->m_pCreateFn(entry, serial);
            pLocal->GetWearables()[0] = entry | serial << 16;
            
            //glovesUpdated = true;
            
            break;
        }
    }
    
    player_info_t LocalPlayerInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &LocalPlayerInfo);
    
    C_BaseAttributableItem* glove = (C_BaseAttributableItem*)pEntList->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);
    
    if (!glove)
        return;
    
    //   int* glove_index = glove->GetModelIndex();
    
    if(pLocal->GetTeam() == TEAM_COUNTER_TERRORIST)
        *glove->GetItemDefinitionIndex() = skin.gloveT;
    
    if(pLocal->GetTeam() == TEAM_TERRORIST)
        *glove->GetItemDefinitionIndex() = skin.gloveCT;
    
    int gSkin = pLocal->GetTeam() == TEAM_TERRORIST ? skin.TgloveID : skin.CTgloveID;
    
    *glove->GetFallbackPaintKit() = gSkin;
    *glove->GetItemIDHigh() = -1;
    *glove->GetEntityQuality() = 4;
    *glove->GetFallbackSeed() = 0;
    *glove->GetFallbackWear() = 0.00000001f;
    *glove->GetAccountID() = LocalPlayerInfo.xuidlow;
    
    if(glovesUpdated) {
        glove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
        glovesUpdated = false;
    }
}



// Fix Animations

inline const int RandomSequence(int low, int high) {
    return (rand() % (high - low + 1) + low);
}

void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
    
    CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
    C_BaseViewModel* pViewModel = (C_BaseViewModel*)pStruct;
    
    if(!pViewModel)
        return g_pSequence(pDataConst, pStruct, pOut);
    
    C_BaseEntity* pOwner = (C_BaseEntity*)pEntList->GetClientEntityFromHandle(pViewModel->GetOwner());
    
    if (pViewModel && pOwner) {
        if (pOwner->GetIndex() == pEngine->GetLocalPlayer()) {
            
            const model_t* knife_model = pModelInfo->GetModel(*pViewModel->GetModelIndex());
            const char* model_filename = pModelInfo->GetModelName(knife_model);
            
            int m_nSequence = (int)pData->m_Value.m_Int;
            
            if (!strcmp(model_filename, "models/weapons/v_knife_butterfly.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
                        break;
                    default:
                        m_nSequence++;
                }
                
            } else if (!strcmp(model_filename, "models/weapons/v_knife_falchion_advanced.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_FALCHION_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence--;
                }
                
            } else if (!strcmp(model_filename, "models/weapons/v_knife_push.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_DAGGERS_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_LIGHT_MISS1:
                    case SEQUENCE_DEFAULT_LIGHT_MISS2:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_HIT1:
                    case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence += 3;
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence += 2;
                }
                
            } else if (!strcmp(model_filename, "models/weapons/v_knife_survival_bowie.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_BOWIE_IDLE1;
                        break;
                    default:
                        m_nSequence--;
                }
                
            }
            
            pData->m_Value.m_Int = m_nSequence;
        }
    }
    
    return g_pSequence(pData, pStruct, pOut);
}


