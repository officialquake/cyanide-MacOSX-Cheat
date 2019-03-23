#include "esp.h"


void DrawSkeleton(C_BaseEntity* pEntity, Color color) {
    
    studiohdr_t* pStudioModel = pModelInfo->GetStudioModel( pEntity->GetModel() );
    
    if ( pStudioModel ) {
        
        static matrix3x4_t pBoneToWorldOut[128];
        
        if ( pEntity->SetupBones( pBoneToWorldOut, 128, 256, 0) )
        {
            for ( int i = 0; i < pStudioModel->numbones; i++ )
            {
                mstudiobone_t* pBone = pStudioModel->pBone( i );
                
                if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
                    continue;
                
                Vector vBone1 = pEntity->GetBonePosition(i);
                Vector vBoneOut1;
                
                Vector vBone2 = pEntity->GetBonePosition(pBone->parent);
                Vector vBoneOut2;
                
                if(WorldToScreen(vBone1, vBoneOut1) && WorldToScreen(vBone2, vBoneOut2)) {
                    draw->drawline(vBoneOut1.x, vBoneOut1.y, vBoneOut2.x, vBoneOut2.y, color);
                }
            }
        }
    }
}

void RenderBones(Vector* vBones, Color color) {
    
    draw->drawline((int)vBones[0].x, (int)vBones[0].y, (int)vBones[1].x, (int)vBones[1].y, color); // head to neck
    draw->drawline((int)vBones[1].x, (int)vBones[1].y, (int)vBones[2].x, (int)vBones[2].y, color); // neck to lower neck
    draw->drawline((int)vBones[2].x, (int)vBones[2].y, (int)vBones[7].x, (int)vBones[7].y, color); // lower neck to upper chest
    
    draw->drawline((int)vBones[7].x, (int)vBones[7].y, (int)vBones[6].x, (int)vBones[6].y, color); // upper chest to chest
    draw->drawline((int)vBones[6].x, (int)vBones[6].y, (int)vBones[18].x, (int)vBones[18].y, color);
    draw->drawline((int)vBones[6].x, (int)vBones[6].y, (int)vBones[16].x, (int)vBones[16].y, color);
    
    draw->drawline((int)vBones[16].x, (int)vBones[16].y, (int)vBones[17].x, (int)vBones[17].y, color);
    draw->drawline((int)vBones[17].x, (int)vBones[17].y, (int)vBones[14].x, (int)vBones[14].y, color);
    draw->drawline((int)vBones[18].x, (int)vBones[18].y, (int)vBones[15].x, (int)vBones[15].y, color);
    
    draw->drawline((int)vBones[6].x, (int)vBones[6].y, (int)vBones[5].x, (int)vBones[5].y, color);
    draw->drawline((int)vBones[5].x, (int)vBones[5].y, (int)vBones[4].x, (int)vBones[4].y, color);
    draw->drawline((int)vBones[4].x, (int)vBones[4].y, (int)vBones[3].x, (int)vBones[3].y, color);
    
    draw->drawline((int)vBones[3].x, (int)vBones[3].y, (int)vBones[9].x, (int)vBones[9].y, color);
    draw->drawline((int)vBones[3].x, (int)vBones[3].y, (int)vBones[8].x, (int)vBones[8].y, color);
    
    draw->drawline((int)vBones[9].x, (int)vBones[9].y, (int)vBones[11].x, (int)vBones[11].y, color);
    draw->drawline((int)vBones[11].x, (int)vBones[11].y, (int)vBones[13].x, (int)vBones[13].y, color);
    
    draw->drawline((int)vBones[8].x, (int)vBones[8].y, (int)vBones[10].x, (int)vBones[10].y, color);
    draw->drawline((int)vBones[10].x, (int)vBones[10].y, (int)vBones[12].x, (int)vBones[12].y, color);
}


Color GetColorBase(Color& col) {
    return Color(col.r(), col.g(), col.b(), 255);
}


void drawBombTimer(C_BasePlantedC4* bomb, C_BaseEntity* local){
    
    float bombTimer = bomb->GetBombTime() - pGlobals->curtime;
    string bombTime = to_string(bombTimer);
    draw->DrawBasicString(10, 35, Color::Red(), espfont, bombTime);
    
}


auto DrawPlayerESP() -> void {
    
    if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        return;
    
    int getscreenw, getscreenh;

    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    if(!vars.visuals.enabled)
        return;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++) {
        
        auto* entity = pEntList->GetClientEntity(i);
        C_BasePlantedC4* pC4 = (C_BasePlantedC4*)entity;
        
        if(!entity)
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetGhost())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        if(vars.visuals.enemyonly && entity->GetTeam() == local->GetTeam())
            continue;
        
        player_info_t info;
        
        pEngine->GetPlayerInfo(i, &info);
        
        auto vis = IsVisible(local, entity);
        
        Color playercolor = [&]() -> Color {
            
            if(entity->GetTeam() == 3)
                return vis ? GetColorBase(vars.colors.ctbox) : GetColorBase(vars.colors.ctbox_ign);
            
            else if(entity->GetTeam() == 2)
                return vis ? GetColorBase(vars.colors.tbox) : GetColorBase(vars.colors.tbox_ign);
            
        }();
        
        boxstruct players;
        
        Vector vFrom = GetHitboxPosition(entity, (int)CSGOBones::Head);
        Vector vW2s;
        Vector vvvv;
        Vector origin = entity->GetVecOrigin();
        
        //STDs ;)
        std::string money = "Money $" + std::to_string(entity->GetMoney());
        
        if(DrawPlayerBox(entity, players)) {
            
            /* Draw box */
            if(vars.visuals.box)
                draw->drawboxoutline(players.x, players.y, players.w, players.h, playercolor);
                
            /* Draw name */
            if(vars.visuals.name)
                draw->drawstring(players.x + players.w / 2, players.y - 12, Color::White(), espfont, info.name, true);
                
            /* Draw health as text */
            if(vars.visuals.healthtext)
                draw->drawstring(players.x + players.w / 2, players.y + players.h + 8, Color::Green(), espfont, std::to_string(entity->GetHealth()).c_str(), true);
            
            /* Draw armour as text */
            if(vars.visuals.armourtext)
                draw->drawstring(players.x + players.w / 2, players.y + players.h + 8, Color::Aqua(), espfont, std::to_string(entity->GetArmor()).c_str(), true);
                
            /* Draws Cash */
            if(vars.visuals.cash)
                draw->drawstring(players.x + players.w + 5, players.y + 30, Color::Green(), espfont, money.c_str(), false);
            
            /* Draw Bomb Carrier */
            if(vars.visuals.cash)
                draw->drawstring(players.x + players.w + 5, players.y + 30, Color::Red(), espfont, money.c_str(), false);
                        
                    
                    
                    
                }
            }
                
        }


/* Getting the module and library address */
void getModule(task_t task, mach_vm_address_t * start, off_t * length, const char * module, Byte * buffer = nullptr, bool readBuffer = false)
{
    struct task_dyld_info dyld_info;
    mach_vm_address_t address = 0;
    mach_msg_type_number_t count = TASK_DYLD_INFO_COUNT;
    if (task_info(task, TASK_DYLD_INFO, (task_info_t)&dyld_info, &count) == KERN_SUCCESS)
    {
        address = dyld_info.all_image_info_addr;
    }
    
    struct dyld_all_image_infos *dyldaii;
    mach_msg_type_number_t size = sizeof(dyld_all_image_infos);
    vm_offset_t readMem;
    kern_return_t kr = vm_read(task, address, size, &readMem, &size);
    if (kr != KERN_SUCCESS)
    {
        return;
    }
    
    dyldaii = (dyld_all_image_infos *) readMem;
    int imageCount = dyldaii->infoArrayCount;
    mach_msg_type_number_t dataCnt = imageCount * 24;
    struct dyld_image_info *g_dii = NULL;
    g_dii = (struct dyld_image_info *) malloc (dataCnt);
    // 32bit bs 64bit
    kern_return_t kr2 = vm_read(task, (mach_vm_address_t)dyldaii->infoArray, dataCnt, &readMem, &dataCnt);
    if (kr2)
    {
        return;
    }
    struct dyld_image_info *dii = (struct dyld_image_info *) readMem;
    for (int i = 0; i < imageCount; i++)
    {
        dataCnt = 1024;
        vm_read(task, (mach_vm_address_t)dii[i].imageFilePath, dataCnt, &readMem, &dataCnt);
        char *imageName = (char *)readMem;
        if (imageName)
        {
            g_dii[i].imageFilePath = strdup(imageName);
        }
        else
        {
            g_dii[i].imageFilePath = NULL;
        }
        g_dii[i].imageLoadAddress = dii[i].imageLoadAddress;
        if (strstr(imageName, module) != NULL)
        {
            struct stat st;
            stat(imageName, &st);
            *start = (mach_vm_address_t)dii[i].imageLoadAddress;
            
            *length = st.st_size;
        }
    }
}


uintptr_t GetLibraryAddress(const char* moduleName)
{
    pid_t pids[1024];
    pid_t p = -1;
    int numberOfProcesses = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    for (int i = 0; i < numberOfProcesses; ++i)
    {
        if (pids[i] == 0) { continue; }
        char name[1024];
        proc_name(pids[i], name, sizeof(name));
        if (!strncmp(name, (const char *)"csgo_osx64", sizeof("csgo_osx64")))
        {
            p = pids[i];
            break;
        }
    }
    task_t task = 0;
    task_for_pid(current_task(), p, &task);
    off_t moduleLength = 0;
    mach_vm_address_t moduleStartAddress;
    getModule(task, &moduleStartAddress, &moduleLength, moduleName);
    return moduleStartAddress;
}


/* Display menu */
auto pwnmymenu() -> void {
    
    if(pInputSystem->IsButtonDown(KEY_LALT) || pInputSystem->IsButtonDown(KEY_RALT) || pInputSystem->IsButtonDown(KEY_INSERT)) {
        vars.menu = !vars.menu;
    }
    
}




