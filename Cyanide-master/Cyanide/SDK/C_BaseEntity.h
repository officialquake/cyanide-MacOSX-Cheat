#pragma once

class CCSWeaponInfo;
class KeyValues;
class CHudTexture;

struct model_t {
    char name[255];
};

#define MAX_SHOOT_SOUNDS 16
#define MAX_WEAPON_STRING 80
#define MAX_WEAPON_PREFIX 16
#define MAX_WEAPON_AMMO_NAME 32

enum MoveType_t
{
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
};

enum class CSWeaponType : int
{
    WEAPONTYPE_KNIFE = 0,
    WEAPONTYPE_PISTOL,
    WEAPONTYPE_SUBMACHINEGUN,
    WEAPONTYPE_RIFLE,
    WEAPONTYPE_SHOTGUN,
    WEAPONTYPE_SNIPER_RIFLE,
    WEAPONTYPE_MACHINEGUN,
    WEAPONTYPE_C4,
    WEAPONTYPE_GRENADE,
    WEAPONTYPE_UNKNOWN
    
    };
    
    enum WeaponSound_t
    {
        EMPTY,
        SINGLE,
        SINGLE_NPC,
        WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
        DOUBLE_NPC,
        BURST,
        RELOAD,
        RELOAD_NPC,
        MELEE_MISS,
        MELEE_HIT,
        MELEE_HIT_WORLD,
        SPECIAL1,
        SPECIAL2,
        SPECIAL3,
        TAUNT,
        FAST_RELOAD,
        
        // Add new shoot sound types here
        REVERSE_THE_NEW_SOUND,
        
        NUM_SHOOT_SOUND_TYPES,
    };
    
    enum DataUpdateType_t
    {
        DATA_UPDATE_CREATED = 0,
        DATA_UPDATE_DATATABLE_CHANGED,
    };
    
    class CHudTexture {
        char pad[0x82];
    public:
        char cCharacterInFont;
    };
    
    
    class FileWeaponInfo_t
    {
    public:
        FileWeaponInfo_t();
        
        // Each game can override this to get whatever values it wants from the script.
        virtual void Parse(KeyValues *pKeyValuesData, const char *szWeaponName);
        
        bool bParsedScript;
        bool bLoadedHudElements;
        
        char szClassName[MAX_WEAPON_STRING];
        char szPrintName[MAX_WEAPON_STRING];
        
        char szViewModel[MAX_WEAPON_STRING];
        char szWorldModel[MAX_WEAPON_STRING];
        char szAmmo1[MAX_WEAPON_AMMO_NAME];
        char szWorldDroppedModel[MAX_WEAPON_STRING];
        char szAnimationPrefix[MAX_WEAPON_PREFIX];
        int iSlot;
        int iPosition;
        int iMaxClip1;
        int iMaxClip2;
        int iDefaultClip1;
        int iDefaultClip2;
        int iWeight;
        int iRumbleEffect;
        bool bAutoSwitchTo;
        bool bAutoSwitchFrom;
        int iFlags;
        char szAmmo2[MAX_WEAPON_AMMO_NAME];
        char szAIAddOn[MAX_WEAPON_STRING];
        
        // Sound blocks
        char aShootSounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING];
        
        int iAmmoType;
        int iAmmo2Type;
        bool m_bMeleeWeapon;
        
        // This tells if the weapon was built right-handed (defaults to true).
        // This helps cl_righthand make the decision about whether to flip the model or not.
        bool m_bBuiltRightHanded;
        bool m_bAllowFlipping;
        
        // Sprite data, read from the data file
        int iSpriteCount;
        CHudTexture* iconActive;
        CHudTexture* iconInactive;
        CHudTexture* iconAmmo;
        CHudTexture* iconAmmo2;
        CHudTexture* iconCrosshair;
        CHudTexture* iconAutoaim;
        CHudTexture* iconZoomedCrosshair;
        CHudTexture* iconZoomedAutoaim;
        CHudTexture* iconSmall;
    };
    
    class CCSWeaponInfo : public FileWeaponInfo_t {
    public:
        CSWeaponType GetWeaponType() {
            return (CSWeaponType)((uintptr_t)this + 0xFA0);
        }
        
        bool IsFullAuto() {
            return (bool)((uintptr_t)this + 0x870);
        }
        
        float GetWeaponArmorRatio() {
            return (float)((uintptr_t)this + 0x878);
        }
        
        float GetMaxPlayerSpeed() {
            return (float)((uintptr_t)this + 0x86C);
        }
        
        float GetMaxPlayerSpeedAlt() {
            return (float)((uintptr_t)this + 0x880);
        }
        
        float GetPenetration() {
            return (float)((uintptr_t)this + 0xAD4);
        }
        
        int GetDamage() {
            return (int)((uintptr_t)this + 0x890);
        }
        
        float GetRange() {
            return (float)((uintptr_t)this + 0x894);
        }
        
        float GetRangeModifier() {
            return (float)((uintptr_t)this + 0x898);
        }
        
        float GetSpread() {
            return (float)((uintptr_t)this + 0x8A8);
        }
        
        int GetZoomLevels() {
            return (int)((uintptr_t)this + 0x884);
        }
    };
    
    class ICollideable
    {
    public:
        virtual void pad0( );
        virtual const Vector& OBBMins( ) const;
        virtual const Vector& OBBMaxs( ) const;
    };
    
    class CBaseHandle;
    
    class IHandleEntity
    {
    public:
        virtual ~IHandleEntity() {};
        virtual void SetRefEHandle( const CBaseHandle &handle ) = 0;
        virtual const CBaseHandle& GetRefEHandle() const = 0;
    };
    
    class IClientUnknown : public IHandleEntity {};
    class IClientRenderable
    {
    public:
        virtual ~IClientRenderable() {};
        
        model_t* GetModel()
        {
            typedef model_t* (* oGetModel)(void*);
            return getvfunc<oGetModel>(this, 8)(this);
        }
        
        bool SetupBones(matrix3x4_t* pBoneMatrix, int nMaxBones, int nBoneMask, float flCurTime = 0)
        {
            typedef bool (* oSetupBones)(void*, matrix3x4_t*, int, int, float);
            return getvfunc<oSetupBones>(this, 13)(this, pBoneMatrix, nMaxBones, nBoneMask, flCurTime);
        }
    };
    
    class IClientNetworkable
    {
    public:
        virtual ~IClientNetworkable() {};
        
        ClientClass* GetClientClass()
        {
            typedef ClientClass* (* oGetClientClass)(void*);
            return getvfunc<oGetClientClass>(this, 2)(this);
        }
        
        void PreDataUpdate(DataUpdateType_t updateType)
        {
            typedef void (* oPreDataUpdate)(void*, DataUpdateType_t);
            return getvfunc<oPreDataUpdate>(this, 6)(this, updateType);
        }
        
        void SetDestroyedOnRecreateEntities()
        {
            typedef void (* oSetDestroyedOnRecreateEntities)(void*);
            return getvfunc<oSetDestroyedOnRecreateEntities>(this, 13)(this);
        }
    };
    
    class IClientThinkable
    {
    public:
        virtual ~IClientThinkable() {};
    };
    
    class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
    {
    public:
        virtual ~IClientEntity() {};
        
        int GetIndex()
        {
            return *(int*)((uintptr_t)this + 0x94);
        }
    };
    
    class C_BaseEntity : public IClientEntity
    {
    public:
        
        IClientNetworkable* GetNetworkable()
        {
            return (IClientNetworkable*)((uintptr_t)this + 0x10);
        }
        
        int GetId()
        {
            return *(int*)((uintptr_t)this + 0x94);
        }
        
        int* GetModelIndex()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_nModelIndex);
        }
        
        void SetModelIndex(int index)
        {
            typedef void (* oSetModelIndex)(void*, int);
            return getvfunc<oSetModelIndex>(this, 111)(this, index);
        }
        
        int GetHealth()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_iHealth);
        }
        
        Vector GetPunchAngles() {
            return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_aimPunchAngle);
        }
        
        int GetArmor()
        {
            return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_ArmorValue);
        }
        
        int GetMoney()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_iAccount);
        }
        
        int HasHelmet()
        {
            return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_bHasHelmet);
        }
        
        int HasDefuser()
        {
            return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_bHasDefuser);
        }
        
        int GetTeam()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BaseEntity.m_iTeamNum);
        }
        
        bool GetDormant()
        {
            return *(bool*)((uintptr_t)this + 0x121);
        }
        
        unsigned char GetLifeState()
        {
            return *(unsigned char*)((uintptr_t)this + offsets.DT_BasePlayer.m_lifeState);
        }
        
        bool GetAlive()
        {
            return this->GetHealth() > 0 && this->GetLifeState() == LIFE_ALIVE;
        }
        
        int* GetWeapons()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hMyWeapons);
        }
        
        void* GetActiveWeapon()
        {
            return (void*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hActiveWeapon);
        }
        
        void* GetViewModel()
        {
            return (void*)((uintptr_t)this + offsets.DT_BasePlayer.m_hViewModel);
        }
        
        Vector GetVecOrigin()
        {
            return *(Vector*)((uintptr_t)this + offsets.DT_BaseEntity.m_vecOrigin);
        }
        
        Vector GetVecViewOffset()
        {
            return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_vecViewOffset);
        }
        
        Vector GetEyePosition()
        {
            return this->GetVecOrigin() + this->GetVecViewOffset();
        }
        
        int GetFlags()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_fFlags);
        }
        
        
        MoveType_t GetMoveType()
        {
            return *(MoveType_t*)((uintptr_t)this + offsets.DT_BaseEntity.m_MoveType);
        }
        
        float GetFlashDuration()
        {
            return *(float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flFlashDuration);
        }
        
        float* GetFlashMaxAlpha()
        {
            return (float*)((uintptr_t)this + offsets.DT_CSPlayer.m_flFlashMaxAlpha);
        }
        
        bool IsDefusing()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsDefusing);
        }
        
        bool IsGrabbingHostage()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsGrabbingHostage);
        }
        
        bool IsScoped()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsScoped);
        }
        
        bool IsRescuing()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsRescuing);
        }
        
        bool GetImmune()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bGunGameImmunity);
        }
        
        bool GetGhost() {
            return *(bool*)((uintptr_t)this + offsets.DT_CSPlayer.m_bIsPlayerGhost);
        }
        
        Vector GetBonePosition(int boneIndex)
        {
            matrix3x4_t BoneMatrix[MAXSTUDIOBONES];
            
            if (!this->SetupBones(BoneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
                return this->GetVecOrigin();
            
            matrix3x4_t hitbox = BoneMatrix[boneIndex];
            
            return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
        }
        
        int* GetObserverMode()
        {
            return (int*)((uintptr_t)this + offsets.DT_BasePlayer.m_iObserverMode);
        }
        
        void* GetObserverTarget()
        {
            return (void*)((uintptr_t)this + offsets.DT_BasePlayer.m_hObserverTarget);
        }
        
        ICollideable* GetCollideable()
        {
            return (ICollideable*)((uintptr_t)this + offsets.DT_BaseEntity.m_Collision);
        }
        
        bool* GetSpotted()
        {
            return (bool*)((uintptr_t)this + offsets.DT_BaseEntity.m_bSpotted);
        }
        
        char* GetLastPlaceName()
        {
            return (char*)((uintptr_t)this + offsets.DT_BasePlayer.m_szLastPlaceName);
        }
        
        Vector GetVelocity()
        {
            return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.m_vecVelocity);
        }
        
        float GetHeadRotation()
        {
            return *(float*)((uintptr_t)this + offsets.DT_BasePlayer.m_angRotation1);
        }
        
        float GetYawRotation()
        {
            return *(float*)((uintptr_t)this + offsets.DT_BasePlayer.m_angRotation2);
        }
        
        float GetLowerBodyYawTarget()
        {
            return *(float*)((uintptr_t)this + offsets.DT_BasePlayer.m_flLowerBodyYawTarget);
        }
        
        Vector GetViewAngles()
        {
            return *(Vector*)((uintptr_t)this + offsets.DT_BasePlayer.deadflag + 0x4);
        }
        
        int GetTickBase()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_nTickBase);
        }
        
        int GetHitboxSet()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_nHitboxSet);
        }
        
        int GetCrosshairID()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BasePlayer.m_dwCrosshairID);
        }
        
        int* GetWearables()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hMyWearables);
        }
        
    };
    
    /* generic game classes */
    class C_BasePlayer : public C_BaseEntity
    {
    public:
        int* GetWeapons()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseCombatCharacter.m_hMyWeapons);
        }
        
        QAngle GetAimPunchAngle()
        {
            return *(QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.m_aimPunchAngle);
        }
        
        QAngle* GetViewPunchAngle()
        {
            return (QAngle*)((uintptr_t)this + offsets.DT_BasePlayer.m_viewPunchAngle);
        }
        
        int GetShotsFired()
        {
            return *(int*)((uintptr_t)this + offsets.DT_CSPlayer.m_iShotsFired);
        }
    };
    
    class C_BasePlantedC4 : public C_BaseEntity
    {
    public:
        bool IsBombTicking()
        {
            return (bool)((uintptr_t)this + offsets.DT_PlantedC4.m_bBombTicking);
        }
        
        float GetBombTime()
        {
            return *(float*)((uintptr_t)this + offsets.DT_PlantedC4.m_flC4Blow);
        }
        
        bool IsBombDefused()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_PlantedC4.m_bStartedArming);
        }
        
        int GetBombDefuser()
        {
            return *(int*)((uintptr_t)this + offsets.DT_PlantedC4.m_hBombDefuser);
        }
    };
    
    class C_BaseAttributableItem : public C_BaseEntity
    {
    public:
        short* GetItemDefinitionIndex()
        {
            return (short*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex);
        }
        
        int* GetItemIDHigh()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iItemIDHigh);
        }
        
        int* GetEntityQuality()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iEntityQuality);
        }
        
        char* GetCustomName()
        {
            return (char*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_szCustomName);
        }
        
        int* GetFallbackPaintKit()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackPaintKit);
        }
        
        int* GetFallbackSeed()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackSeed);
        }
        
        float* GetFallbackWear()
        {
            return (float*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_flFallbackWear);
        }
        
        int* GetFallbackStatTrak()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_nFallbackStatTrak);
        }
        
        int* GetOriginalOwnerXuidLow(){
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidLow);
        }
        
        int* GetOriginalOwnerXuidHigh(){
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidHigh);
        }
        
        
        int* GetAccountID()
        {
            return (int*)((uintptr_t)this + offsets.DT_BaseAttributableItem.m_iAccountID);
        }
        
        bool IsPistol()
        {
            switch (*this->GetItemDefinitionIndex())
            {
                case WEAPON_DEAGLE:
                case WEAPON_ELITE:
                case WEAPON_FIVESEVEN:
                case WEAPON_GLOCK:
                case WEAPON_TEC9:
                case WEAPON_HKP2000:
                case WEAPON_USP_SILENCER:
                case WEAPON_P250:
                case WEAPON_CZ75A:
                case WEAPON_REVOLVER:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsAutomatic()
        {
            switch (*this->GetItemDefinitionIndex())
            {
                case WEAPON_AK47:
                case WEAPON_AUG:
                case WEAPON_FAMAS:
                case WEAPON_GALILAR:
                case WEAPON_M249:
                case WEAPON_M4A1:
                case WEAPON_M4A1_SILENCER:
                case WEAPON_MAC10:
                case WEAPON_P90:
                case WEAPON_UMP45:
                case WEAPON_BIZON:
                case WEAPON_NEGEV:
                case WEAPON_MP7:
                case WEAPON_MP9:
                case WEAPON_SG556:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsShotgun()
        {
            switch(*this->GetItemDefinitionIndex())
            {
                case WEAPON_XM1014:
                case WEAPON_SAWEDOFF:
                case WEAPON_NOVA:
                case WEAPON_MAG7:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsKnife()
        {
            switch (*this->GetItemDefinitionIndex())
            {
                case WEAPON_KNIFE:
                case WEAPON_KNIFE_T:
                case WEAPON_KNIFE_GUT:
                case WEAPON_KNIFE_FLIP:
                case WEAPON_KNIFE_BAYONET:
                case WEAPON_KNIFE_M9_BAYONET:
                case WEAPON_KNIFE_KARAMBIT:
                case WEAPON_KNIFE_BUTTERFLY:
                case WEAPON_KNIFE_SURVIVAL_BOWIE:
                case WEAPON_KNIFE_FALCHION:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsGrenade()
        {
            switch (*this->GetItemDefinitionIndex())
            {
                case WEAPON_SMOKEGRENADE:
                case WEAPON_HEGRENADE:
                case WEAPON_INCGRENADE:
                case WEAPON_FLASHBANG:
                case WEAPON_MOLOTOV:
                case WEAPON_DECOY:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsBomb()
        {
            return *this->GetItemDefinitionIndex() == WEAPON_C4;
        }
        
        bool CanScope()
        {
            switch (*this->GetItemDefinitionIndex())
            {
                case WEAPON_AUG:
                case WEAPON_AWP:
                case WEAPON_G3SG1:
                case WEAPON_SCAR20:
                case WEAPON_SG556:
                case WEAPON_SSG08:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsSniperRifle()
        {
            switch (*this->GetItemDefinitionIndex())
            {
                case WEAPON_AWP:
                case WEAPON_G3SG1:
                case WEAPON_SCAR20:
                case WEAPON_SSG08:
                    return true;
                default:
                    return false;
            }
        }
        
        bool IsRCSWeapon() //NY RCS
        {
            bool ret = true;
            
            if ((CanScope())) {
                ret = false;
            }
            
            if (IsPistol()) {
                ret = false;
            }
            
            if (IsShotgun()) {
                ret = false;
            }
            
            return ret;
        }
        
        
        
    };
    
    
    class C_BaseViewModel: public C_BaseEntity {
    public:
        int GetWeapon()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_hWeapon);
        }
        
        int GetOwner()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BaseViewModel.m_hOwner);
        }
    };
    
    class C_BaseCombatWeapon: public C_BaseAttributableItem
    {
    public:
        int GetOwner()
        {
            return *(int*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_hOwner);
        }
        
        unsigned int GetAmmo()
        {
            return *(unsigned int*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_iClip1);
        }
        
        float GetNextPrimaryAttack()
        {
            return *(float*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack);
        }
        
        bool GetInReload()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_BaseCombatWeapon.m_bInReload);
        }
        
        float GetAccuracyPenalty()
        {
            return *(float*)((uintptr_t)this + offsets.DT_WeaponCSBase.m_fAccuracyPenalty);
        }
        
        CCSWeaponInfo* GetCSWpnData()
        {
            typedef CCSWeaponInfo* (* oGetCSWpnData)(void*);
            return getvfunc<oGetCSWpnData>(this, 524)(this);
        }
        
        float GetInaccuracy()
        {
            typedef float (* oGetInaccuracy)(void*);
            return getvfunc<oGetInaccuracy>(this, 552)(this);
        }
        
        float GetSpread()
        {
            typedef float (* oGetSpread)(void*);
            return getvfunc<oGetSpread>(this, 553)(this);
        }
        
        void UpdateAccuracyPenalty()
        {
            typedef void (* oUpdateAccuracyPenalty)(void*);
            return getvfunc<oUpdateAccuracyPenalty>(this, 554)(this);
        }
    };
    
    class C_WeaponC4 : C_BaseCombatWeapon
    {
    public:
        bool GetStartedArming()
        {
            return *(bool*)((uintptr_t)this + offsets.DT_WeaponC4.m_bStartedArming);
        }
    };
    
    class C_Chicken : C_BaseEntity
    {
    public:
        bool* GetShouldGlow()
        {
            return (bool*)((uintptr_t)this + offsets.DT_DynamicProp.m_bShouldGlow);
        }
        };
