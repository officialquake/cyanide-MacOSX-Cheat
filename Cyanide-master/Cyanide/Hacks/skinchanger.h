#include "../main.h"

void MakeSkinChanger(ClientFrameStage_t stage);
void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);

class cSkin{
public:
    
    cSkin(){}
    
    cSkin(int paintkit, int seed, int itemDefinition, int stattrack, char* szName, float flWear) :
    Paintkit(paintkit), Seed(seed), ItemDefinition(itemDefinition), StatTrack(stattrack), name(szName), Wear(flWear){}
    
    int Paintkit = 0;
    int Seed = 0;
    int ItemDefinition = 0;
    int StatTrack = -1;
    char* name = nullptr;
    float Wear = 0.0001f;
};

const std::unordered_map<size_t, Item_t> ItemDefIndex = {
    {WEAPON_DEAGLE, {"Desert Eagle", "weapon_deagle", "models/weapons/v_pist_deagle.mdl", "deagle"}},
    {WEAPON_ELITE, {"Dual Berettas", "weapon_elite", "models/weapons/v_pist_elite.mdl", "elite"}},
    {WEAPON_FIVESEVEN, {"Five-SeveN", "weapon_fiveseven", "models/weapons/v_pist_fiveseven.mdl", "fiveseven"}},
    {WEAPON_GLOCK, {"Glock-18", "weapon_glock", "models/weapons/v_pist_glock18.mdl", "glock"}},
    {WEAPON_AK47, {"AK-47", "weapon_ak47", "models/weapons/v_rif_ak47.mdl", "ak47"}},
    {WEAPON_AUG, {"AUG", "weapon_aug", "models/weapons/v_rif_aug.mdl", "aug"}},
    {WEAPON_AWP, {"AWP", "weapon_awp", "models/weapons/v_snip_awp.mdl", "awp"}},
    {WEAPON_FAMAS, {"FAMAS", "weapon_famas", "models/weapons/v_rif_famas.mdl", "famas"}},
    {WEAPON_G3SG1, {"G3SG1", "weapon_g3sg1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1"}},
    {WEAPON_GALILAR, {"Galil AR", "weapon_galilar", "models/weapons/v_rif_galilar.mdl", "galilar"}},
    {WEAPON_M249, {"M249", "weapon_m249", "models/weapons/v_mach_m249para.mdl", "m249"}},
    {WEAPON_M4A1, {"M4A4", "weapon_m4a1", "models/weapons/v_rif_m4a1.mdl", "m4a1"}},
    {WEAPON_MAC10, {"MAC-10", "weapon_mac10", "models/weapons/v_smg_mac10.mdl", "mac10"}},
    {WEAPON_P90, {"P90", "weapon_p90", "models/weapons/v_smg_p90.mdl", "p90"}},
    {WEAPON_UMP45, {"UMP-45", "weapon_ump45", "models/weapons/v_smg_ump45.mdl", "ump45"}},
    {WEAPON_XM1014, {"XM1014", "weapon_xm1014", "models/weapons/v_shot_xm1014.mdl", "xm1014"}},
    {WEAPON_BIZON, {"PP-Bizon", "weapon_bizon", "models/weapons/v_smg_bizon.mdl", "bizon"}},
    {WEAPON_MAG7, {"MAG-7", "weapon_mag7", "models/weapons/v_shot_mag7.mdl", "mag7"}},
    {WEAPON_NEGEV, {"Negev", "weapon_negev", "models/weapons/v_mach_negev.mdl", "negev"}},
    {WEAPON_SAWEDOFF, {"Sawed-Off", "weapon_sawedoff", "models/weapons/v_shot_sawedoff.mdl", "sawedoff"}},
    {WEAPON_TEC9, {"Tec-9", "weapon_tec9", "models/weapons/v_pist_tec9.mdl", "tec9"}},
    {WEAPON_TASER, {"Zeus x27", "weapon_taser", "models/weapons/v_eq_taser.mdl", "taser"}},
    {WEAPON_HKP2000, {"P2000", "weapon_hkp2000", "models/weapons/v_pist_hkp2000.mdl", "hkp2000"}},
    {WEAPON_MP7, {"MP7", "weapon_mp7", "models/weapons/v_smg_mp7.mdl", "mp7"}},
    {WEAPON_MP9, {"MP9", "weapon_mp9", "models/weapons/v_smg_mp9.mdl", "mp9"}},
    {WEAPON_NOVA, {"Nova", "weapon_nova", "models/weapons/v_shot_nova.mdl", "nova"}},
    {WEAPON_P250, {"P250", "weapon_p250", "models/weapons/v_pist_p250.mdl", "p250"}},
    {WEAPON_SCAR20, {"SCAR-20", "weapon_scar20", "models/weapons/v_snip_scar20.mdl", "scar20"}},
    {WEAPON_SG556, {"SG 556", "weapon_sg556", "models/weapons/v_rif_sg556.mdl", "sg556"}},
    {WEAPON_SSG08, {"SSG 08", "weapon_ssg08", "models/weapons/v_snip_ssg08.mdl", "ssg08"}},
    {WEAPON_KNIFE, {"Knife (Counter-Terrorists)", "weapon_knife", "models/weapons/v_knife_default_ct.mdl", "knife_default_ct"}},
    {WEAPON_FLASHBANG, {"Flashbang", "weapon_flashbang", "models/weapons/v_eq_flashbang.mdl", "flashbang"}},
    {WEAPON_HEGRENADE, {"HE Grenade", "weapon_hegrenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade"}},
    {WEAPON_SMOKEGRENADE, {"Smoke Grenade", "weapon_smokegrenade", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade"}},
    {WEAPON_MOLOTOV, {"Molotov", "weapon_molotov", "models/weapons/v_eq_molotov.mdl", "inferno"}},
    {WEAPON_DECOY, {"Decoy Grenade", "weapon_decoy", "models/weapons/v_eq_decoy.mdl", "decoy"}},
    {WEAPON_INCGRENADE, {"Incendiary Grenade", "weapon_incgrenade", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno"}},
    {WEAPON_C4, {"C4 Explosive", "weapon_c4", "models/weapons/v_ied.mdl"}},
    {WEAPON_KNIFE_T, {"Knife (Terrorists)", "weapon_knife_t", "models/weapons/v_knife_default_t.mdl", "knife_t"}},
    {WEAPON_M4A1_SILENCER, {"M4A1-S", "weapon_m4a1_silencer", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer"}},
    {WEAPON_USP_SILENCER, {"USP-S", "weapon_usp_silencer", "models/weapons/v_pist_223.mdl", "usp_silencer"}},
    {WEAPON_CZ75A, {"CZ75 Auto", "weapon_cz75a", "models/weapons/v_pist_cz_75.mdl", "cz75a"}},
    {WEAPON_REVOLVER, {"R8 Revolver", "weapon_revolver", "models/weapons/v_pist_revolver.mdl", "revolver"}},
    {WEAPON_KNIFE_BAYONET, {"Bayonet", "weapon_bayonet", "models/weapons/v_knife_bayonet.mdl", "bayonet"}},
    {WEAPON_KNIFE_FLIP, {"Flip Knife", "weapon_knife_flip", "models/weapons/v_knife_flip.mdl", "knife_flip"}},
    {WEAPON_KNIFE_GUT, {"Gut Knife", "weapon_knife_gut", "models/weapons/v_knife_gut.mdl", "knife_gut"}},
    {WEAPON_KNIFE_KARAMBIT, {"Karambit", "weapon_knife_karambit", "models/weapons/v_knife_karam.mdl", "knife_karambit"}},
    {WEAPON_KNIFE_M9_BAYONET, {"M9 Bayonet", "weapon_knife_m9_bayonet", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet"}},
    {WEAPON_KNIFE_TACTICAL, {"Huntsman Knife", "weapon_knife_tactical", "models/weapons/v_knife_tactical.mdl", "knife_tactical"}},
    {WEAPON_KNIFE_FALCHION, {"Falchion Knife", "weapon_knife_falchion", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion"}},
    {WEAPON_KNIFE_SURVIVAL_BOWIE, {"Bowie Knife", "weapon_knife_survival_bowie", "models/weapons/v_knife_survival_bowie.mdl", "knife_survival_bowie"}},
    {WEAPON_KNIFE_BUTTERFLY, {"Butterfly Knife", "weapon_knife_butterfly", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly"}},
    {WEAPON_KNIFE_PUSH, {"Shadow Daggers", "weapon_knife_push", "models/weapons/v_knife_push.mdl", "knife_push"}}
};

