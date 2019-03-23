#include "main.h"

COffsets offsets;

void Offsets::getOffsets()
{
    std::vector<RecvTable *> tables = NetVarManager::GetTables();
    
    offsets.DT_BasePlayer.m_Local = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_Local");
    offsets.DT_BasePlayer.m_aimPunchAngle = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_aimPunchAngle");
    offsets.DT_BasePlayer.m_viewPunchAngle = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_viewPunchAngle");
    offsets.DT_BasePlayer.m_vecViewOffset = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_vecViewOffset[0]");
    offsets.DT_BasePlayer.m_nTickBase = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_nTickBase");
    offsets.DT_BasePlayer.m_vecVelocity = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_vecVelocity[0]");
    offsets.DT_BasePlayer.m_iHealth = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_iHealth");
    offsets.DT_BasePlayer.m_lifeState = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_lifeState");
    offsets.DT_BasePlayer.m_fFlags = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_fFlags");
    offsets.DT_BasePlayer.m_iObserverMode = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_iObserverMode");
    offsets.DT_BasePlayer.m_hObserverTarget = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_hObserverTarget");
    offsets.DT_BasePlayer.m_hViewModel = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_hViewModel[0]");
    offsets.DT_BasePlayer.m_szLastPlaceName = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_szLastPlaceName");
    offsets.DT_BasePlayer.m_iAccount = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_iAccount");
    offsets.DT_BasePlayer.m_angRotation1 = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_angEyeAngles[0]");
    offsets.DT_BasePlayer.m_angRotation2 = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_angEyeAngles[1]");
    offsets.DT_BasePlayer.m_flLowerBodyYawTarget = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_flLowerBodyYawTarget");
    offsets.DT_BasePlayer.deadflag = NetVarManager::GetOffset(tables, "DT_BasePlayer", "deadflag");
    
    offsets.DT_BaseEntity.m_vecOrigin = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_vecOrigin");
    offsets.DT_BaseEntity.m_nRenderMode = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_nRenderMode");
    offsets.DT_BaseEntity.m_iTeamNum = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_iTeamNum");
    offsets.DT_BaseEntity.m_MoveType = offsets.DT_BaseEntity.m_nRenderMode + 1;
    offsets.DT_BaseEntity.m_Collision = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_Collision");
    offsets.DT_BaseEntity.m_bSpotted = NetVarManager::GetOffset(tables, "DT_BaseEntity", "m_bSpotted");
    
    offsets.DT_BaseCombatCharacter.m_hActiveWeapon = NetVarManager::GetOffset(tables, "DT_BaseCombatCharacter", "m_hActiveWeapon");
    offsets.DT_BaseCombatCharacter.m_hMyWeapons = NetVarManager::GetOffset(tables, "DT_BaseCombatCharacter", "m_hMyWeapons") / 2;
    offsets.DT_BaseCombatCharacter.m_hMyWearables = NetVarManager::GetOffset(tables, "DT_BaseCombatCharacter", "m_hMyWearables");
    
    offsets.DT_PlayerResource.m_iPing = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iPing");
    offsets.DT_PlayerResource.m_iKills = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iKills");
    offsets.DT_PlayerResource.m_iAssists = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iAssists");
    offsets.DT_PlayerResource.m_iDeaths = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iDeaths");
    offsets.DT_PlayerResource.m_bConnected = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_bConnected");
    offsets.DT_PlayerResource.m_iTeam = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iTeam");
    offsets.DT_PlayerResource.m_iPendingTeam = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iPendingTeam");
    offsets.DT_PlayerResource.m_bAlive = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_bAlive");
    offsets.DT_PlayerResource.m_iHealth = NetVarManager::GetOffset(tables, "DT_PlayerResource", "m_iHealth");
    
    offsets.DT_CSPlayerResource.m_iPlayerC4 = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iPlayerC4");
    offsets.DT_CSPlayerResource.m_iPlayerVIP = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iPlayerVIP");
    offsets.DT_CSPlayerResource.m_bHostageAlive = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bHostageAlive");
    offsets.DT_CSPlayerResource.m_isHostageFollowingSomeone = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_isHostageFollowingSomeone");
    offsets.DT_CSPlayerResource.m_iHostageEntityIDs = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iHostageEntityIDs");
    offsets.DT_CSPlayerResource.m_bombsiteCenterB = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bombsiteCenterB");
    offsets.DT_CSPlayerResource.m_hostageRescueX = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueX");
    offsets.DT_CSPlayerResource.m_hostageRescueY = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueY");
    offsets.DT_CSPlayerResource.m_hostageRescueZ = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_hostageRescueZ");
    offsets.DT_CSPlayerResource.m_iMVPs = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iMVPs");
    offsets.DT_CSPlayerResource.m_iArmor = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iArmor");
    offsets.DT_CSPlayerResource.m_bHasHelmet = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bHasHelmet");
    offsets.DT_CSPlayerResource.m_bHasDefuser = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bHasDefuser");
    offsets.DT_CSPlayerResource.m_iScore = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iScore");
    offsets.DT_CSPlayerResource.m_iCompetitiveRanking = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveRanking");
    offsets.DT_CSPlayerResource.m_iCompetitiveWins = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCompetitiveWins");
    offsets.DT_CSPlayerResource.m_iCompTeammateColor = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCompTeammateColor");
    offsets.DT_CSPlayerResource.m_bControllingBot = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bControllingBot");
    offsets.DT_CSPlayerResource.m_iControlledPlayer = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iControlledPlayer");
    offsets.DT_CSPlayerResource.m_iControlledByPlayer = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iControlledByPlayer");
    offsets.DT_CSPlayerResource.m_iBotDifficulty = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iBotDifficulty");
    offsets.DT_CSPlayerResource.m_szClan = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_szClan");
    offsets.DT_CSPlayerResource.m_iTotalCashSpent = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iTotalCashSpent");
    offsets.DT_CSPlayerResource.m_iCashSpentThisRound = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_iCashSpentThisRound");
    offsets.DT_CSPlayerResource.m_nEndMatchNextMapVotes = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nEndMatchNextMapVotes");
    offsets.DT_CSPlayerResource.m_bEndMatchNextMapAllVoted = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_bEndMatchNextMapAllVoted");
    offsets.DT_CSPlayerResource.m_nActiveCoinRank = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nActiveCoinRank");
    offsets.DT_CSPlayerResource.m_nMusicID = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nMusicID");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicLevel = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsLeader = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsTeacher = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
    offsets.DT_CSPlayerResource.m_nPersonaDataPublicCommendsFriendly = NetVarManager::GetOffset(tables, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");
    
    offsets.DT_PlantedC4.m_bBombTicking = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_bBombTicking");
    offsets.DT_PlantedC4.m_flC4Blow = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_flC4Blow");
    offsets.DT_PlantedC4.m_bBombDefused = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_bBombDefused");
    offsets.DT_PlantedC4.m_hBombDefuser = NetVarManager::GetOffset(tables, "DT_PlantedC4", "m_hBombDefuser");
    
    offsets.DT_CSPlayer.m_iShotsFired = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_iShotsFired");
    offsets.DT_CSPlayer.m_ArmorValue = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_ArmorValue");
    offsets.DT_CSPlayer.m_bHasDefuser = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
    offsets.DT_CSPlayer.m_bIsDefusing = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsDefusing");
    offsets.DT_CSPlayer.m_bIsGrabbingHostage = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsGrabbingHostage");
    offsets.DT_CSPlayer.m_bIsScoped = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsScoped");
    offsets.DT_CSPlayer.m_bGunGameImmunity = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bGunGameImmunity");
    offsets.DT_CSPlayer.m_bIsPlayerGhost = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsPlayerGhost");
    offsets.DT_CSPlayer.m_bIsRescuing = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bIsRescuing");
    offsets.DT_CSPlayer.m_bHasHelmet = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bHasHelmet");
    offsets.DT_CSPlayer.m_bHasDefuser = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_bHasDefuser");
    offsets.DT_CSPlayer.m_flFlashDuration = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_flFlashDuration");
    offsets.DT_CSPlayer.m_flFlashMaxAlpha = NetVarManager::GetOffset(tables, "DT_CSPlayer", "m_flFlashMaxAlpha");
    
    offsets.DT_BaseAttributableItem.m_iItemDefinitionIndex = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");
    offsets.DT_BaseAttributableItem.m_iItemIDHigh = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iItemIDHigh");
    offsets.DT_BaseAttributableItem.m_iAccountID = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iAccountID");
    offsets.DT_BaseAttributableItem.m_iEntityQuality = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_iEntityQuality");
    offsets.DT_BaseAttributableItem.m_szCustomName = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_szCustomName");
    offsets.DT_BaseAttributableItem.m_nFallbackPaintKit = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackPaintKit");
    offsets.DT_BaseAttributableItem.m_nFallbackSeed = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackSeed");
    offsets.DT_BaseAttributableItem.m_flFallbackWear = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_flFallbackWear");
    offsets.DT_BaseAttributableItem.m_nFallbackStatTrak = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_nFallbackStatTrak");
    offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidHigh = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
    offsets.DT_BaseAttributableItem.m_OriginalOwnerXuidLow = NetVarManager::GetOffset(tables, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
    
    offsets.DT_BaseViewModel.m_nModelIndex = NetVarManager::GetOffset(tables, "DT_BaseViewModel", "m_nModelIndex");
    offsets.DT_BaseViewModel.m_hWeapon = NetVarManager::GetOffset(tables, "DT_BaseViewModel", "m_hWeapon");
    offsets.DT_BaseViewModel.m_hOwner = NetVarManager::GetOffset(tables, "DT_BaseViewModel", "m_hOwner");
    
    offsets.DT_WeaponCSBase.m_fAccuracyPenalty = NetVarManager::GetOffset(tables, "DT_WeaponCSBase", "m_fAccuracyPenalty");
    
    offsets.DT_WeaponC4.m_bStartedArming = NetVarManager::GetOffset(tables, "DT_WeaponC4", "m_bStartedArming");
    
    offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack = NetVarManager::GetOffset(tables, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
    offsets.DT_BaseCombatWeapon.m_hOwner = NetVarManager::GetOffset(tables, "DT_BaseCombatWeapon", "m_hOwner");
    offsets.DT_BaseCombatWeapon.m_iClip1 = NetVarManager::GetOffset(tables, "DT_BaseCombatWeapon", "m_iClip1");
    offsets.DT_BaseCombatWeapon.m_bInReload = offsets.DT_BaseCombatWeapon.m_flNextPrimaryAttack + 113;
    
    offsets.DT_DynamicProp.m_bShouldGlow = NetVarManager::GetOffset(tables, "DT_DynamicProp", "m_bShouldGlow");
    
    offsets.DT_BasePlayer.m_nHitboxSet = NetVarManager::GetOffset(tables, "DT_BasePlayer", "m_nHitboxSet");
    
}
