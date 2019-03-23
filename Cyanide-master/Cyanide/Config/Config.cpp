//
//  Config.cpp
//  vHook
//

#include "../main.h"
#include "Config.h"
#include "skins.h"

using namespace std;

Config* config = new Config();
Config* skins_cfg = new Config();
Skins skin;

const char* ConfigName;
string user     = getenv("USER");
string dsk      = "/Users/" + user + "/Desktop/";
string fdr      = "/Users/" + user + "/Desktop/Cyanide";
string legit    = "/Users/" + user + "/Desktop/Cyanide/settings.ini";
string skins    = "/Users/" + user + "/Desktop/Cyanide/skins.ini";

bool GetBoolValue(bool Value)
{
    return Value;
}

int GetIntValue(bool Value)
{
    return Value;
}

float GetFloatValue(float Value)
{
    return Value;
}

void Config::getConfig(int ConfigNo) {
    if(ConfigNo == 0) ConfigName = legit.c_str();
}

bool fileExist(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}
void Config::LoadConfig() {
    
    cfg.SetUnicode(true);
    cfg.LoadFile(ConfigName);
    
    vars.aimbot.aimKey  = (ButtonCode_t)cfgget_f("Bindings", "Aimlock Key");
    vars.aimbot.triggerKey  = (ButtonCode_t)cfgget_f("Bindings", "Trigger Key");
    
    // Left Aimbot
    vars.aimbot.enabled     = cfgget_b("Aimbot", "Enabled");
    vars.aimbot.smooth      = cfgget_b("Aimbot", "Smoothing");
    vars.aimbot.smoothf     = cfgget_f("Aimbot", "Smoothf");
    vars.aimbot.rcs         = cfgget_b("Aimbot", "RCS");
    vars.aimbot.rcsf        = cfgget_f("Aimbot", "RCSf");
    vars.aimbot.fov         = cfgget_f("Aimbot", "FOV");
    vars.aimbot.hitbox      = cfgget_f("Aimbot", "Bone");
    vars.aimbot.trigger     = cfgget_b("Aimbot", "Trigger");
    
    // Right Aimbot
    vars.aimbot.silent      = cfgget_b("Aimbot", "Silent");
    
    //vars.aimbot.triggerKey  = (ButtonCode_t)cfgget_f("Aimbot", "Trigger Key");
    
    // Left Visuals
    //vars.visuals.enabled    = cfgget_b("Visuals", "Enabled");
    //vars.visuals.enemyonly  = cfgget_b("Visuals", "Enemy Only");
    //vars.visuals.name       = cfgget_b("Visuals", "Name ESP");
    //vars.visuals.cash       = cfgget_b("Visuals", "Show Money");
    //vars.visuals.Rescuing   = cfgget_b("Visuals", "Rescuing(Hostage)");
    //vars.visuals.Scoped     = cfgget_b("Visuals", "Scoped");
    //vars.visuals.grenade    = cfgget_b("Visuals", "Grenade ESP Box");
    
    
    // Right Visuals
    //vars.visuals.healthtext = cfgget_b("Visuals", "Health Text");
    vars.visuals.chams      = cfgget_b("Visuals", "Player Chams");
    //vars.visuals.box        = cfgget_b("Visuals", "Box");
    
    vars.visuals.playersType= cfgget_f("Visuals", "Players Type");
    
    // Misc Left
    vars.visuals.skinc          = cfgget_b("Misc", "Skinchanger");
    vars.misc.bhop          = cfgget_b("Misc", "Bhop");
    vars.misc.fov           = cfgget_f("Misc", "Fov");
    vars.misc.showrank      = cfgget_b("Misc", "Show Ranks");
    vars.misc.norecoil      = cfgget_b("Misc", "No Recoil");
    vars.misc.novisualrecoil= cfgget_b("Misc", "No Visual Recoil");
    
    //Misc Right
   // vars.misc.noflash       = cfgget_b("Misc", "No Flash Enable");
   // vars.misc.flashalpha    = cfgget_f("Misc", "Flash Alpha");
    
    /*
    Colours
    vars.colors.pchamr      = cfgget_f("Colours", "pChamr");
    vars.colors.pchamg      = cfgget_f("Colours", "pChamg");
    vars.colors.pchamb      = cfgget_f("Colours", "pChamb");
    
    
    vars.colors.boxr        = cfgget_f("Colours", "boxr");
    vars.colors.boxg        = cfgget_f("Colours", "boxg");
    vars.colors.boxb        = cfgget_f("Colours", "boxb");
    
    vars.colors.pignr       = cfgget_f("Colours", "cignr");
    vars.colors.pigng       = cfgget_f("Colours", "cigng");
    vars.colors.pignb       = cfgget_f("Colours", "cignb");
    
    vars.colors.bignr       = cfgget_f("Colours", "bignr");
    vars.colors.bigng       = cfgget_f("Colours", "bigng");
    vars.colors.bignb       = cfgget_f("Colours", "bignb");
    */
    
}



void Config::SaveConfig() {
    
    
    if(!fileExist(dsk.c_str()))
        mkdir(dsk.c_str(), 0775);
    
    if(!fileExist(fdr.c_str()))
        mkdir(fdr.c_str(), 0775);
    
    
    //CSimpleIniA cfg;
    cfg.SetUnicode(true);
    
    cfg.SetDoubleValue("Bindings", "Aimlock Key", GetFloatValue((int)vars.aimbot.aimKey));
    cfg.SetDoubleValue("Bindings", "Trigger Key", GetFloatValue((int)vars.aimbot.triggerKey));
    
    // Left Aimbot
    cfg.SetBoolValue("Aimbot", "Enabled", GetBoolValue(vars.aimbot.enabled));
    cfg.SetBoolValue("Aimbot", "Smoothing", GetBoolValue(vars.aimbot.smooth));
    cfg.SetDoubleValue("Aimbot", "Smoothf", GetFloatValue(vars.aimbot.smoothf));
    cfg.SetBoolValue("Aimbot", "RCS", GetBoolValue(vars.aimbot.rcs));
    cfg.SetDoubleValue("Aimbot", "RCSf", GetFloatValue(vars.aimbot.rcsf));
    cfg.SetDoubleValue("Aimbot", "FOV", GetFloatValue(vars.aimbot.fov));
    cfg.SetDoubleValue("Aimbot", "Bone", GetFloatValue(vars.aimbot.hitbox));
    cfg.SetBoolValue("Aimbot", "Trigger", GetBoolValue(vars.aimbot.trigger));
    
    // Right Aimbot
    cfg.SetBoolValue("Aimbot", "Silent", GetBoolValue(vars.aimbot.silent));
    
    
    // Left Visuals
    //cfg.SetBoolValue("Visuals", "Enabled", GetBoolValue(vars.visuals.enabled));
    //cfg.SetBoolValue("Visuals", "Enemy Only", GetBoolValue(vars.visuals.enemyonly));
    //cfg.SetBoolValue("Visuals", "Name ESP", GetBoolValue(vars.visuals.name));
    //cfg.SetBoolValue("Visuals", "Show Money", GetBoolValue(vars.visuals.cash));
    //cfg.SetBoolValue("Visuals", "Rescuing(Hostage)", GetBoolValue(vars.visuals.Rescuing));
    //cfg.SetBoolValue("Visuals", "Scoped", GetBoolValue(vars.visuals.Scoped));
    //cfg.SetBoolValue("Visuals", "Grenade ESP Box", GetBoolValue(vars.visuals.grenade));
    
    
    // Right Visuals
    //cfg.SetBoolValue("Visuals", "Health Text", GetBoolValue(vars.visuals.healthtext));
    cfg.SetBoolValue("Visuals", "Player Chams", GetBoolValue(vars.visuals.chams));
    //cfg.SetBoolValue("Visuals", "Box", GetBoolValue(vars.visuals.box));
    
    cfg.SetDoubleValue("Visuals", "Players Type", GetFloatValue(vars.visuals.playersType));
    
    // Misc Left
    cfg.SetBoolValue("Misc", "Bhop", GetBoolValue(vars.misc.bhop));
     cfg.SetBoolValue("Misc", "Skichanger", GetBoolValue(vars.visuals.skinc));
    cfg.SetBoolValue("Misc", "No Recoil", GetBoolValue(vars.misc.norecoil));
    
    cfg.SetBoolValue("Misc", "Show Rank", GetBoolValue(vars.misc.showrank));
    cfg.SetBoolValue("Misc", "No Visuals Recoil", GetBoolValue(vars.misc.novisualrecoil));
    
    // Misc Right
   // cfg.SetBoolValue("Misc", "No Flash Enable", GetBoolValue(vars.misc.noflash));
   // cfg.SetDoubleValue("Misc", "Flash Alpha", GetFloatValue(vars.misc.flashalpha));
    
    /*
    //Colours
    cfg.SetDoubleValue("Colors", "pChamr", GetFloatValue(vars.colors.pchamr));
    cfg.SetDoubleValue("Colors", "pChamg", GetFloatValue(vars.colors.pchamg));
    cfg.SetDoubleValue("Colors", "pChamb", GetFloatValue(vars.colors.pchamb));
    
    cfg.SetDoubleValue("Colors", "boxr", GetFloatValue(vars.colors.boxr));
    cfg.SetDoubleValue("Colors", "boxg", GetFloatValue(vars.colors.boxg));
    cfg.SetDoubleValue("Colors", "boxb", GetFloatValue(vars.colors.boxb));
    
    cfg.SetDoubleValue("Colors", "cignr", GetFloatValue(vars.colors.pignr));
    cfg.SetDoubleValue("Colors", "cigng", GetFloatValue(vars.colors.pigng));
    cfg.SetDoubleValue("Colors", "cignb", GetFloatValue(vars.colors.pignb));
    
    cfg.SetDoubleValue("Colors", "bignr", GetFloatValue(vars.colors.bignr));
    cfg.SetDoubleValue("Colors", "bigng", GetFloatValue(vars.colors.bigng));
    cfg.SetDoubleValue("Colors", "bignb", GetFloatValue(vars.colors.bignb));
    
    */
    
    
    
    
    
    cfg.SaveFile(ConfigName);
    
}

void Config::InitSkins() {
    
    if(fileExist(skins.c_str()))
        return;
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("weapon_deagle", "id", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("weapon_deagle", "seed", GetFloatValue(skin.deagle_Seed));
    skins_cfg.SetDoubleValue("weapon_deagle", "itemdef", GetFloatValue(1));
    
    skins_cfg.SetDoubleValue("weapon_elite", "id", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("weapon_elite", "seed", GetFloatValue(skin.dual_Seed));
    skins_cfg.SetDoubleValue("weapon_elite", "itemdef", GetFloatValue(2));
    
    skins_cfg.SetDoubleValue("weapon_fiveseven", "id", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "seed", GetFloatValue(skin.five7_Seed));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "itemdef", GetFloatValue(3));
    
    skins_cfg.SetDoubleValue("weapon_glock", "id", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("weapon_glock", "seed", GetFloatValue(skin.glock_Seed));
    skins_cfg.SetDoubleValue("weapon_glock", "itemdef", GetFloatValue(4));
    
    skins_cfg.SetDoubleValue("weapon_ak47", "id", GetFloatValue(skin.ak));
    skins_cfg.SetDoubleValue("weapon_ak47", "seed", GetFloatValue(skin.ak_Seed));
    skins_cfg.SetDoubleValue("weapon_ak47", "itemdef", GetFloatValue(7));
    
    skins_cfg.SetDoubleValue("weapon_aug", "id", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("weapon_aug", "seed", GetFloatValue(skin.aug_Seed));
    skins_cfg.SetDoubleValue("weapon_aug", "itemdef", GetFloatValue(8));
    
    skins_cfg.SetDoubleValue("weapon_awp", "id", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("weapon_awp", "seed", GetFloatValue(skin.awp_Seed));
    skins_cfg.SetDoubleValue("weapon_awp", "itemdef", GetFloatValue(9));
    
    skins_cfg.SetDoubleValue("weapon_famas", "id", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("weapon_famas", "seed", GetFloatValue(skin.famas_Seed));
    skins_cfg.SetDoubleValue("weapon_famas", "itemdef", GetFloatValue(10));
    
    skins_cfg.SetDoubleValue("weapon_g3sg1", "id", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "seed", GetFloatValue(skin.g3_Seed));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "itemdef", GetFloatValue(11));
    
    skins_cfg.SetDoubleValue("weapon_galilar", "id", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("weapon_galilar", "seed", GetFloatValue(skin.galil_Seed));
    skins_cfg.SetDoubleValue("weapon_galilar", "itemdef", GetFloatValue(13));
    
    skins_cfg.SetDoubleValue("weapon_m249", "id", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("weapon_m249", "seed", GetFloatValue(skin.m249_Seed));
    skins_cfg.SetDoubleValue("weapon_m249", "itemdef", GetFloatValue(14));
    
    skins_cfg.SetDoubleValue("weapon_m4a1", "id", GetFloatValue(skin.a4));
    skins_cfg.SetDoubleValue("weapon_m4a1", "seed", GetFloatValue(skin.a4_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a1", "itemdef", GetFloatValue(16));
    
    skins_cfg.SetDoubleValue("weapon_mac10", "id", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("weapon_mac10", "seed", GetFloatValue(skin.mac10_Seed));
    skins_cfg.SetDoubleValue("weapon_mac10", "itemdef", GetFloatValue(17));
    
    skins_cfg.SetDoubleValue("weapon_p90", "id", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("weapon_p90", "seed", GetFloatValue(skin.p90_Seed));
    skins_cfg.SetDoubleValue("weapon_p90", "itemdef", GetFloatValue(19));
    
    skins_cfg.SetDoubleValue("weapon_ump45", "id", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("weapon_ump45", "seed", GetFloatValue(skin.ump_Seed));
    skins_cfg.SetDoubleValue("weapon_ump45", "itemdef", GetFloatValue(24));
    
    skins_cfg.SetDoubleValue("weapon_xm1014", "id", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("weapon_xm1014", "seed", GetFloatValue(skin.xm_Seed));
    skins_cfg.SetDoubleValue("weapon_xm1014", "itemdef", GetFloatValue(25));
    
    skins_cfg.SetDoubleValue("weapon_bizon", "id", GetFloatValue(skin.bizon));
    skins_cfg.SetDoubleValue("weapon_bizon", "seed", GetFloatValue(skin.bizon_Seed));
    skins_cfg.SetDoubleValue("weapon_bizon", "itemdef", GetFloatValue(26));
    
    skins_cfg.SetDoubleValue("weapon_mag7", "id", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("weapon_mag7", "seed", GetFloatValue(skin.mag7_Seed));
    skins_cfg.SetDoubleValue("weapon_mag7", "itemdef", GetFloatValue(27));
    
    skins_cfg.SetDoubleValue("weapon_negev", "id", GetFloatValue(skin.negev));
    skins_cfg.SetDoubleValue("weapon_negev", "seed", GetFloatValue(skin.negev_Seed));
    skins_cfg.SetDoubleValue("weapon_negev", "itemdef", GetFloatValue(28));
    
    skins_cfg.SetDoubleValue("weapon_sawedoff", "id", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "seed", GetFloatValue(skin.sawed_Seed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "itemdef", GetFloatValue(29));
    
    skins_cfg.SetDoubleValue("weapon_tec9", "id", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("weapon_tec9", "seed", GetFloatValue(skin.tec9_Seed));
    skins_cfg.SetDoubleValue("weapon_tec9", "itemdef", GetFloatValue(30));
    
    skins_cfg.SetDoubleValue("weapon_hkp2000", "id", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "seed", GetFloatValue(skin.p2000_Seed));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "itemdef", GetFloatValue(32));
    
    skins_cfg.SetDoubleValue("weapon_mp7", "id", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("weapon_mp7", "seed", GetFloatValue(skin.mp7_Seed));
    skins_cfg.SetDoubleValue("weapon_mp7", "itemdef", GetFloatValue(33));
    
    skins_cfg.SetDoubleValue("weapon_mp9", "id", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("weapon_mp9", "seed", GetFloatValue(skin.mp9_Seed));
    skins_cfg.SetDoubleValue("weapon_mp9", "itemdef", GetFloatValue(34));
    
    skins_cfg.SetDoubleValue("weapon_nova", "id", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("weapon_nova", "seed", GetFloatValue(skin.nova_Seed));
    skins_cfg.SetDoubleValue("weapon_nova", "itemdef", GetFloatValue(35));
    
    skins_cfg.SetDoubleValue("weapon_p250", "id", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("weapon_p250", "seed", GetFloatValue(skin.p250_Seed));
    skins_cfg.SetDoubleValue("weapon_p250", "itemdef", GetFloatValue(36));
    
    skins_cfg.SetDoubleValue("weapon_scar20", "id", GetFloatValue(skin.scar));
    skins_cfg.SetDoubleValue("weapon_scar20", "seed", GetFloatValue(skin.scar_Seed));
    skins_cfg.SetDoubleValue("weapon_scar20", "itemdef", GetFloatValue(38));
    
    skins_cfg.SetDoubleValue("weapon_sg556", "id", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("weapon_sg556", "seed", GetFloatValue(skin.sg_Seed));
    skins_cfg.SetDoubleValue("weapon_sg556", "itemdef", GetFloatValue(39));
    
    skins_cfg.SetDoubleValue("weapon_ssg08", "id", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("weapon_ssg08", "seed", GetFloatValue(skin.scout_Seed));
    skins_cfg.SetDoubleValue("weapon_ssg08", "itemdef", GetFloatValue(40));
    
    skins_cfg.SetDoubleValue("weapon_knife", "id", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("weapon_knife", "seed", GetFloatValue(skin.CTknfieSeed));
    skins_cfg.SetDoubleValue("weapon_knife", "itemdef", GetFloatValue(skin.knifeCT));
    
    skins_cfg.SetDoubleValue("weapon_knife_t", "id", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("weapon_knife_t", "seed", GetFloatValue(skin.TknifeSeed));
    skins_cfg.SetDoubleValue("weapon_knife_t", "itemdef", GetFloatValue(skin.knifeT));
    
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "id", GetFloatValue(skin.a1));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "seed", GetFloatValue(skin.a1_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "itemdef", GetFloatValue(60));
    
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "id", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "seed", GetFloatValue(skin.usp_Seed));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "itemdef", GetFloatValue(61));
    
    skins_cfg.SetDoubleValue("weapon_cz75a", "id", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("weapon_cz75a", "seed", GetFloatValue(skin.cz_Seed));
    skins_cfg.SetDoubleValue("weapon_cz75a", "itemdef", GetFloatValue(63));
    
    skins_cfg.SetDoubleValue("weapon_revolver", "id", GetFloatValue(skin.r8));
    skins_cfg.SetDoubleValue("weapon_revolver", "seed", GetFloatValue(skin.r8_Seed));
    skins_cfg.SetDoubleValue("weapon_revolver", "itemdef", GetFloatValue(64));
    /*
     skins_cfg.SetDoubleValue("t glove", "id", GetFloatValue(skin.TgloveID));
     //skins_cfg.SetDoubleValue("t glove", "seed", GetFloatValue(skin.tgloveskin));
     skins_cfg.SetDoubleValue("t glove", "itemdef", GetFloatValue(skin.gloveT));
     
     skins_cfg.SetDoubleValue("ct glove", "id", GetFloatValue(skin.CTgloveID));
     //skins_cfg.SetDoubleValue("ct glove", "seed", GetFloatValue(skin.ctgloveskin));
     skins_cfg.SetDoubleValue("ct glove", "itemdef", GetFloatValue(skin.gloveCT));
     */
    
    
    skins_cfg.SaveFile(skins.c_str());
    
}

void Config::UpdateSkins() {
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("weapon_deagle", "id", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("weapon_deagle", "seed", GetFloatValue(skin.deagle_Seed));
    skins_cfg.SetDoubleValue("weapon_deagle", "itemdef", GetFloatValue(1));
    
    skins_cfg.SetDoubleValue("weapon_elite", "id", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("weapon_elite", "seed", GetFloatValue(skin.dual_Seed));
    skins_cfg.SetDoubleValue("weapon_elite", "itemdef", GetFloatValue(2));
    
    skins_cfg.SetDoubleValue("weapon_fiveseven", "id", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "seed", GetFloatValue(skin.five7_Seed));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "itemdef", GetFloatValue(3));
    
    skins_cfg.SetDoubleValue("weapon_glock", "id", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("weapon_glock", "seed", GetFloatValue(skin.glock_Seed));
    skins_cfg.SetDoubleValue("weapon_glock", "itemdef", GetFloatValue(4));
    
    skins_cfg.SetDoubleValue("weapon_ak47", "id", GetFloatValue(skin.ak));
    skins_cfg.SetDoubleValue("weapon_ak47", "seed", GetFloatValue(skin.ak_Seed));
    skins_cfg.SetDoubleValue("weapon_ak47", "itemdef", GetFloatValue(7));
    
    skins_cfg.SetDoubleValue("weapon_aug", "id", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("weapon_aug", "seed", GetFloatValue(skin.aug_Seed));
    skins_cfg.SetDoubleValue("weapon_aug", "itemdef", GetFloatValue(8));
    
    skins_cfg.SetDoubleValue("weapon_awp", "id", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("weapon_awp", "seed", GetFloatValue(skin.awp_Seed));
    skins_cfg.SetDoubleValue("weapon_awp", "itemdef", GetFloatValue(9));
    
    skins_cfg.SetDoubleValue("weapon_famas", "id", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("weapon_famas", "seed", GetFloatValue(skin.famas_Seed));
    skins_cfg.SetDoubleValue("weapon_famas", "itemdef", GetFloatValue(10));
    
    skins_cfg.SetDoubleValue("weapon_g3sg1", "id", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "seed", GetFloatValue(skin.g3_Seed));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "itemdef", GetFloatValue(11));
    
    skins_cfg.SetDoubleValue("weapon_galilar", "id", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("weapon_galilar", "seed", GetFloatValue(skin.galil_Seed));
    skins_cfg.SetDoubleValue("weapon_galilar", "itemdef", GetFloatValue(13));
    
    skins_cfg.SetDoubleValue("weapon_m249", "id", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("weapon_m249", "seed", GetFloatValue(skin.m249_Seed));
    skins_cfg.SetDoubleValue("weapon_m249", "itemdef", GetFloatValue(14));
    
    skins_cfg.SetDoubleValue("weapon_m4a1", "id", GetFloatValue(skin.a4));
    skins_cfg.SetDoubleValue("weapon_m4a1", "seed", GetFloatValue(skin.a4_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a1", "itemdef", GetFloatValue(16));
    
    skins_cfg.SetDoubleValue("weapon_mac10", "id", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("weapon_mac10", "seed", GetFloatValue(skin.mac10_Seed));
    skins_cfg.SetDoubleValue("weapon_mac10", "itemdef", GetFloatValue(17));
    
    skins_cfg.SetDoubleValue("weapon_p90", "id", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("weapon_p90", "seed", GetFloatValue(skin.p90_Seed));
    skins_cfg.SetDoubleValue("weapon_p90", "itemdef", GetFloatValue(19));
    
    skins_cfg.SetDoubleValue("weapon_ump45", "id", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("weapon_ump45", "seed", GetFloatValue(skin.ump_Seed));
    skins_cfg.SetDoubleValue("weapon_ump45", "itemdef", GetFloatValue(24));
    
    skins_cfg.SetDoubleValue("weapon_xm1014", "id", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("weapon_xm1014", "seed", GetFloatValue(skin.xm_Seed));
    skins_cfg.SetDoubleValue("weapon_xm1014", "itemdef", GetFloatValue(25));
    
    skins_cfg.SetDoubleValue("weapon_bizon", "id", GetFloatValue(skin.bizon));
    skins_cfg.SetDoubleValue("weapon_bizon", "seed", GetFloatValue(skin.bizon_Seed));
    skins_cfg.SetDoubleValue("weapon_bizon", "itemdef", GetFloatValue(26));
    
    skins_cfg.SetDoubleValue("weapon_mag7", "id", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("weapon_mag7", "seed", GetFloatValue(skin.mag7_Seed));
    skins_cfg.SetDoubleValue("weapon_mag7", "itemdef", GetFloatValue(27));
    
    skins_cfg.SetDoubleValue("weapon_negev", "id", GetFloatValue(skin.negev));
    skins_cfg.SetDoubleValue("weapon_negev", "seed", GetFloatValue(skin.negev_Seed));
    skins_cfg.SetDoubleValue("weapon_negev", "itemdef", GetFloatValue(28));
    
    skins_cfg.SetDoubleValue("weapon_sawedoff", "id", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "seed", GetFloatValue(skin.sawed_Seed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "itemdef", GetFloatValue(29));
    
    skins_cfg.SetDoubleValue("weapon_tec9", "id", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("weapon_tec9", "seed", GetFloatValue(skin.tec9_Seed));
    skins_cfg.SetDoubleValue("weapon_tec9", "itemdef", GetFloatValue(30));
    
    skins_cfg.SetDoubleValue("weapon_hkp2000", "id", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "seed", GetFloatValue(skin.p2000_Seed));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "itemdef", GetFloatValue(32));
    
    skins_cfg.SetDoubleValue("weapon_mp7", "id", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("weapon_mp7", "seed", GetFloatValue(skin.mp7_Seed));
    skins_cfg.SetDoubleValue("weapon_mp7", "itemdef", GetFloatValue(33));
    
    skins_cfg.SetDoubleValue("weapon_mp9", "id", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("weapon_mp9", "seed", GetFloatValue(skin.mp9_Seed));
    skins_cfg.SetDoubleValue("weapon_mp9", "itemdef", GetFloatValue(34));
    
    skins_cfg.SetDoubleValue("weapon_nova", "id", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("weapon_nova", "seed", GetFloatValue(skin.nova_Seed));
    skins_cfg.SetDoubleValue("weapon_nova", "itemdef", GetFloatValue(35));
    
    skins_cfg.SetDoubleValue("weapon_p250", "id", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("weapon_p250", "seed", GetFloatValue(skin.p250_Seed));
    skins_cfg.SetDoubleValue("weapon_p250", "itemdef", GetFloatValue(36));
    
    skins_cfg.SetDoubleValue("weapon_scar20", "id", GetFloatValue(skin.scar));
    skins_cfg.SetDoubleValue("weapon_scar20", "seed", GetFloatValue(skin.scar_Seed));
    skins_cfg.SetDoubleValue("weapon_scar20", "itemdef", GetFloatValue(38));
    
    skins_cfg.SetDoubleValue("weapon_sg556", "id", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("weapon_sg556", "seed", GetFloatValue(skin.sg_Seed));
    skins_cfg.SetDoubleValue("weapon_sg556", "itemdef", GetFloatValue(39));
    
    skins_cfg.SetDoubleValue("weapon_ssg08", "id", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("weapon_ssg08", "seed", GetFloatValue(skin.scout_Seed));
    skins_cfg.SetDoubleValue("weapon_ssg08", "itemdef", GetFloatValue(40));
    
    skins_cfg.SetDoubleValue("weapon_knife", "id", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("weapon_knife", "seed", GetFloatValue(skin.CTknfieSeed));
    skins_cfg.SetDoubleValue("weapon_knife", "itemdef", GetFloatValue(skin.knifeCT));
    
    skins_cfg.SetDoubleValue("weapon_knife_t", "id", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("weapon_knife_t", "seed", GetFloatValue(skin.TknifeSeed));
    skins_cfg.SetDoubleValue("weapon_knife_t", "itemdef", GetFloatValue(skin.knifeT));
    
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "id", GetFloatValue(skin.a1));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "seed", GetFloatValue(skin.a1_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "itemdef", GetFloatValue(60));
    
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "id", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "seed", GetFloatValue(skin.usp_Seed));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "itemdef", GetFloatValue(61));
    
    skins_cfg.SetDoubleValue("weapon_cz75a", "id", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("weapon_cz75a", "seed", GetFloatValue(skin.cz_Seed));
    skins_cfg.SetDoubleValue("weapon_cz75a", "itemdef", GetFloatValue(63));
    
    skins_cfg.SetDoubleValue("weapon_revolver", "id", GetFloatValue(skin.r8));
    skins_cfg.SetDoubleValue("weapon_revolver", "seed", GetFloatValue(skin.r8_Seed));
    skins_cfg.SetDoubleValue("weapon_revolver", "itemdef", GetFloatValue(64));
    
    skins_cfg.SaveFile(skins.c_str());
    
}


void Config::LoadSkins() {
    
    if(!fileExist(skins.c_str()))
        InitSkins();
    
    skins_cfg.SetUnicode(true);
    skins_cfg.LoadFile(skins.c_str());
    
    skin.TknifeID   = skin_cfgget_f("weapon_knife_t", "id");
    skin.CTknifeID  = skin_cfgget_f("weapon_knife", "id");
    
    skin.galil   = skin_cfgget_f("weapon_galilar", "id");
    skin.famas   = skin_cfgget_f("weapon_famas", "id");
    skin.ak      = skin_cfgget_f("weapon_ak47", "id");
    skin.a4      = skin_cfgget_f("weapon_m4a1", "id");
    skin.a1      = skin_cfgget_f("weapon_m4a1_silencer", "id");
    skin.scout   = skin_cfgget_f("weapon_ssg08", "id");
    skin.sg      = skin_cfgget_f("weapon_sg556", "id");
    skin.aug     = skin_cfgget_f("weapon_aug", "id");
    skin.awp     = skin_cfgget_f("weapon_awp", "id");
    skin.g3      = skin_cfgget_f("weapon_scar20", "id");
    skin.scar    = skin_cfgget_f("weapon_g3sg1", "id");
    
    skin.glock   = skin_cfgget_f("weapon_glock", "id");
    skin.usp     = skin_cfgget_f("weapon_usp_silencer", "id");
    skin.p2000   = skin_cfgget_f("weapon_hkp2000", "id");
    skin.dual    = skin_cfgget_f("weapon_elite", "id");
    skin.p250    = skin_cfgget_f("weapon_p250", "id");
    skin.tec9    = skin_cfgget_f("weapon_tec9", "id");
    skin.five7   = skin_cfgget_f("weapon_fiveseven", "id");
    skin.cz      = skin_cfgget_f("weapon_cz75a", "id");
    skin.deagle  = skin_cfgget_f("weapon_deagle", "id");
    skin.r8      = skin_cfgget_f("weapon_revolver", "id");
    
    skin.mac10   = skin_cfgget_f("weapon_mac10", "id");
    skin.mp9     = skin_cfgget_f("weapon_mp9", "id");
    skin.mp7     = skin_cfgget_f("weapon_mp7", "id");
    skin.ump     = skin_cfgget_f("weapon_ump45", "id");
    skin.p90     = skin_cfgget_f("weapon_p90", "id");
    skin.bizon   = skin_cfgget_f("weapon_bizon", "id");
    
    skin.nova    = skin_cfgget_f("weapon_nova", "id");
    skin.sawed   = skin_cfgget_f("weapon_sawedoff", "id");
    skin.mag7    = skin_cfgget_f("weapon_mag7", "id 7");
    skin.xm      = skin_cfgget_f("weapon_xm1014", "id");
    skin.m249    = skin_cfgget_f("weapon_m249", "id");
    skin.negev   = skin_cfgget_f("weapon_negev", "id");
    
}



bool Config::HasWeaponConfiguration(const char* section) {
    skins_cfg.LoadFile(skins.c_str());
    CSimpleIniA::TNamesDepend sections;
    skins_cfg.GetAllSections(sections);
    sections.sort(CSimpleIniA::Entry::LoadOrder());
    
    for (auto sect : sections) {
        if(!strcmp(section, sect.pItem)) {
            return true;
        }
    }
    
    return false;
}


cSkin Config::GetWeaponConfiguration(const char *section) {
    
    skins_cfg.LoadFile(skins.c_str());
    
    cSkin weapon_config;
    
    weapon_config.Paintkit      = (int)skin_cfgget_f(section, "id");
    weapon_config.Seed          = (int)skin_cfgget_f(section, "seed");
    weapon_config.ItemDefinition= (int)skin_cfgget_f(section, "itemdef");
    
    return weapon_config;
}


