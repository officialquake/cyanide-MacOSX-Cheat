#include "main.h"

Vector tpangles;
Vector atTargets;
vector<int64_t> aimbotfriends = { };

bool* bSendPacket = nullptr;



/* No Recoil */
auto MakeNoRecoil(C_BaseEntity* local, CUserCmd* cmd) -> void {
    if(!vars.misc.enabled)
        return;
    
    if(!vars.misc.norecoil)
        return;
    
    if(cmd->buttons & IN_ATTACK) {
        Vector localVec = local->GetPunchAngles() * 2.f;
        
        cmd->viewangles.x -= localVec.x;
        cmd->viewangles.y -= localVec.y;
    }
}
/* RCS */
auto LegitRecoil(C_BaseEntity* local, CUserCmd* cmd) -> void {
    if(!vars.misc.enabled)
        return;
    
    if(!vars.aimbot.rcs)
        return;
    
    if(cmd->buttons & IN_ATTACK) {
        Vector localVec = local->GetPunchAngles() * 2.f;
        
        cmd->viewangles.x -= localVec.x * (2.f / 100.f * vars.aimbot.rcsf);;
        cmd->viewangles.y -= localVec.y * (2.f / 100.f * vars.aimbot.rcsf);;
    }
}


Vector CalcAngle(Vector src, Vector dst) {
    
    Vector delta, angles;
    delta.x = (src.x - dst.x);
    delta.y = (src.y - dst.y);
    delta.z = (src.z - dst.z);
    
    double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
    
    angles.x = (float)(atanf(delta.z / hyp) * M_RADPI);
    angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI);
    
    angles.z = 0.0f;
    if (delta.x >= 0.0) { angles.y += 180.0f; }
    return angles;
}


float GetFOV(Vector start, Vector src, Vector dst) {
    Vector ang, aim;
    ang = CalcAngle(src, dst);
    AngleVectors(start, &aim);
    AngleVectors(ang, &ang);
    
    float mag_s = std::sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
    float mag_d = mag_s;
    float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
    float fov = std::acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI_F);
    return fov;
}

float GetFov(const Vector& viewAngle, const Vector& aimAngle) {
    Vector delta = aimAngle - viewAngle;
    NormalizeAngles(delta);
    
    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

struct FireBulletData {
    Vector          src;
    trace_t         enter_trace;
    Vector          direction;
    CTraceFilter    filter;
    float           trace_length;
    float           trace_length_remaining;
    float           current_damage;
    int             penetrate_count;
};

void TraceLine(Vector vecAbsStart, Vector vecAbsEnd, unsigned int mask, C_BaseEntity * ignore, trace_t * ptr) {
    Ray_t ray;
    ray.Init(vecAbsStart, vecAbsEnd);
    CTraceFilter filter;
    filter.pSkip = ignore;
    
    pEngineTrace->TraceRay(ray, mask, &filter, ptr);
}


bool TraceToExit( Vector &end, trace_t *enter_trace, Vector start, Vector dir, trace_t *exit_trace )
{
    float distance = 0.0f;
    
    while( distance <= 90.0f )
    {
        distance += 4.0f;
        end = start + dir * distance;
        
        auto point_contents = pEngineTrace->GetPointContents( end, MASK_SHOT_HULL | CONTENTS_HITBOX, NULL );
        
        if( point_contents & MASK_SHOT_HULL && ( !( point_contents & CONTENTS_HITBOX ) ) )
            continue;
        
        auto new_end = end - ( dir * 4.0f );
        
        TraceLine( end, new_end, 0x4600400B, 0, exit_trace );
        
        // bool allsolid; @ TR + 54
        // bool startsolid; @ TR + 55
        
        if( exit_trace->startsolid && exit_trace->surface.flags & SURF_HITBOX )
        {
            TraceLine( end, start, 0x600400B, exit_trace->m_pEnt, exit_trace );
            
            if( ( exit_trace->fraction < 1.0f || exit_trace->allsolid ) && !exit_trace->startsolid )
            {
                end = exit_trace->endpos;
                return true;
            }
            continue;
        }
        
        if( !( exit_trace->fraction < 1.0 || exit_trace->allsolid || exit_trace->startsolid ) || exit_trace->startsolid )
        {
            if( exit_trace->m_pEnt )
            {
                if( enter_trace->m_pEnt && enter_trace->m_pEnt == pEntList->GetClientEntity(0))
                    return true;
            }
            continue;
        }
        
        // checking for SURF_NODRAW perhaps
        if( ( ( exit_trace->surface.flags >> 7 ) & 1 ) && !( ( enter_trace->surface.flags >> 7 ) & 1 ) )
            continue;
        
        if( exit_trace->plane.normal.Dot( dir ) <= 1.0f )
        {
            auto fraction = exit_trace->fraction * 4.0f;
            end = end - ( dir * fraction );
            return true; 
        } 
    } 
    return false; 
}



Vector Smooth(Vector& angle) {
    
    if(!vars.aimbot.enabled)
        return;
    
    if(!vars.aimbot.smooth)
        return;
    
    if(vars.aimbot.silent)
        return;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAngles(delta);
    
    float smooth = powf(vars.aimbot.smoothf, 0.4f);
    smooth = std::min(0.99f, smooth);
    
    Vector toChange = delta - delta * smooth;
    
    return angle = viewAngles + toChange;
}



auto MakeAimbot(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide, bool& bSendPacket) -> void {
    Vector eyepos = local->GetEyePosition();
    if(!vars.aimbot.enabled) return;
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++) {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(entity->GetGhost())
            continue;
        
        if(weapon->IsBomb())
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        if(gCorrections[entity->GetIndex()].prefer)
            continue;

        
        Vector vFrom, vTo;
        
        vFrom = GetHitboxPosition(entity, vars.aimbot.hitbox); // 0 = head.
            
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(local, entity);
        
        
        atTargets = vTo;
        
            if(isVISIBLE) {
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) < vars.aimbot.fov) {
                
                
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(vars.aimbot.smooth) {
                    pCmd->viewangles = Smooth(vTo);
                }
                ButtonCode_t aimKey = (ButtonCode_t)vars.aimbot.aimKey;
                if(pInputSystem->IsButtonDown(aimKey)) {
                    if(!vars.aimbot.silent) {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    } else {
                        pCmd->viewangles = vTo;
                    }
                }
            }
        }
    }
}



void ClampMoves(float& flForward, float& flSide, float& flUp) {
    if(flForward > 450) flForward = 450;
    if(flSide > 450) flSide = 450;
    if(flUp > 450) flUp = 450;
    if(flForward < -450) flForward = -450;
    if(flSide < -450) flSide = -450;
    if(flUp < -450) flUp = -450;
}

auto MakeBhop(CUserCmd* cmd, C_BaseEntity* local) -> void {
    if(!vars.misc.enabled) return;
    if(!vars.misc.bhop) return;
    
    static bool shouldJump = false;
    static bool shouldFake = false;
    
    if (shouldFake && !shouldJump) {
        cmd->buttons |= IN_JUMP;
        shouldFake = false;
    }
    else if (cmd->buttons & IN_JUMP) {
        if (local->GetFlags() & FL_ONGROUND) {
            shouldFake = false;
            shouldJump = false;
            
        }
        else {
            cmd->buttons &= ~IN_JUMP;
            shouldJump = false;
        }
    }
    else {
        shouldJump = false;
        shouldFake = false;
    }
}

void MakeTrigger(CUserCmd *Cmd) {
    
    if(!vars.aimbot.trigger)
        return;
    
    ButtonCode_t triggerKey = (ButtonCode_t)vars.aimbot.triggerKey;
    if(pInputSystem->IsButtonDown(triggerKey)) {
        
        C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        
        if (!LocalPlayer || LocalPlayer->GetHealth() < 0) {
            return;
        }
    
        C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(LocalPlayer->GetActiveWeapon());
        if (!activeWeapon || activeWeapon->GetAmmo() == 0)
            return;
        
        
        Vector traceStart, traceEnd;
        
        Vector viewAngles;
        pEngine->GetViewAngles(viewAngles);
        Vector viewAngles_rcs = viewAngles + (LocalPlayer->GetPunchAngles() * 2.0f);
        
        AngleVectors(viewAngles_rcs, &traceEnd);
        
        traceStart = LocalPlayer->GetEyePosition();
        traceEnd = traceStart + (traceEnd * 8192.0f);
        
        Ray_t ray;
        trace_t trace;
        CTraceFilter filter;
        filter.pSkip = LocalPlayer;
        
        ray.Init(traceStart, traceEnd);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        
        if (trace.allsolid || trace.startsolid) {
            return;
        }
        
        C_BaseEntity* player = (C_BaseEntity*)trace.m_pEnt;
        if(!player || player->GetHealth() < 0 || player->GetImmune()) {
            return;
        }
        
        if(player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer) {
            return;
        }
        
        if(LocalPlayer->GetTeam() == player->GetTeam()) {
            return;
        }
        
        if (activeWeapon->GetNextPrimaryAttack() > pGlobals->curtime) {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER) {
                Cmd->buttons &= ~IN_ATTACK2;
            } else {
                Cmd->buttons &= ~IN_ATTACK;
            }
        } else {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER) {
                Cmd->buttons |= IN_ATTACK2;
            } else {
                Cmd->buttons |= IN_ATTACK;
            }
        }
    }
}

void MakeShowRanks(CUserCmd* cmd)
{
    if (!vars.misc.showrank)
        return;
    
    if (!(cmd->buttons & IN_SCORE))
        return;
    
    float input[3] = { 0.f };
    MsgFunc_ServerRankRevealAll(input);
}


auto hacks(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, Vector& vOldAngles, float& flForwardmove, float& flSidemove, bool& sendpacket) -> void {
    
    MakeBhop(cmd, local);

    MakeAimbot(cmd, local, weapon, flForwardmove, flSidemove, sendpacket); // Add some black magic shit.
    
    MakeNoRecoil(local, cmd); // Add norecoil
        
    if(vars.misc.norecoil && vars.aimbot.rcs)
        vars.aimbot.rcs = false;
            
    if(vars.aimbot.rcs && !vars.misc.norecoil)
        LegitRecoil(local, cmd);
    
    MakeShowRanks(cmd);
    
    MakeTrigger(cmd);
    
}
bool bOnce = false;


void ClampYaw(float& angle) {
    while(angle > 180) {
        angle -= 360;
    }
    while(angle < -180) {
        angle += 360;
    }
}


bool SendPacket = true;
bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd) {
    createmovehook->GetOriginalMethod<tCreateMove>(25)(thisptr, flSampleInput, cmd);
    
    if(!cmd->command_number)
        return true;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return false;
    
    if(local->GetLifeState() != 0)
        return false;
    
    if(local->GetHealth() < 1)
        return false;
    
    if(local->GetDormant())
        return false;
    
    if(bSendPacket == nullptr)
        return false;
    
    
    auto* weapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(local->GetActiveWeapon());
    
    if(!weapon)
        return false;

    SendPacket = true;
    *bSendPacket = SendPacket;
    
    
    Vector vOldAngles = cmd->viewangles;
    Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
    Vector qAimAngles;
    
    float forward = cmd->forwardmove;
    float sidemove = cmd->sidemove;
    float upmove = cmd->upmove;
    
    if(pEngine->IsInGame() && pEngine->IsConnected()) {
        
        hacks(cmd, local, weapon, vOldAngles, forward, sidemove, *bSendPacket);
        
        
        if(pInputSystem->IsButtonDown(KEY_N))
            *bSendPacket = false;
        else
            *bSendPacket = true;
        
        
        FixMovement(vOldAngles, cmd);
        ClampMoves(forward, sidemove, upmove);
        

        
        if(vars.misc.enabled && vars.misc.antiuntrust) {
            cmd->viewangles.ClampAngles();
        }
        
        if(*bSendPacket)
        tpangles = cmd->viewangles;
    }
    return false;
}
