#include "cfg.h"
#include "skinchanger.h"

class Config
{
public:
    
    template<typename type>
    type GetSetting(const char* section, const char* key, bool menu = false) {
        type value = NULL;
        
        if (typeid(type) == typeid(float))
            value = (float)cfg.GetDoubleValue(section, key);
        
        else if (typeid(type) == typeid(bool))
            value = cfg.GetBoolValue(section, key);
        
        else if (typeid(type) == typeid(int))
            value = (int)cfg.GetLongValue(section, key);
        
        return value;
    }
    
    template<typename type>
    void SetSetting(const char* section, const char* key, type value, bool menu = false) {
        
        if (typeid(type) ==  typeid(float))
            cfg.SetDoubleValue(section, key, value);
        
        else if (typeid(type) ==  typeid(bool))
            cfg.SetBoolValue(section, key, value);
        
        else if (typeid(type) ==  typeid(int))
            cfg.SetLongValue(section, key, value);
        
    }
    
    template<typename type>
    type GetSkinSetting(const char* section, const char* key, bool menu = false) {
        type value = NULL;
        
        if (typeid(type) == typeid(float))
            value = (float)skins_cfg.GetDoubleValue(section, key);
        
        else if (typeid(type) == typeid(bool))
            value = skins_cfg.GetBoolValue(section, key);
        
        else if (typeid(type) == typeid(int))
            value = (int)skins_cfg.GetLongValue(section, key);
        
        return value;
    }
    
    template<typename type>
    void SetSkinSetting(const char* section, const char* key, type value, bool menu = false) {
        
        if (typeid(type) ==  typeid(float))
            skins_cfg.SetDoubleValue(section, key, value);
        
        else if (typeid(type) ==  typeid(bool))
            skins_cfg.SetBoolValue(section, key, value);
        
        else if (typeid(type) ==  typeid(int))
            skins_cfg.SetLongValue(section, key, value);
        
    }
    
    void LoadConfig();
    void SaveConfig();
    void LoadSkins();
    void InitSkins();
    void UpdateSkins();
    void getConfig(int ConfigNo);
    cSkin GetWeaponConfiguration(const char *section);
    bool HasWeaponConfiguration(const char* section);
    
    bool loadconfig = false;
    bool saveconfig = false;
    
    int cfgcombo    = 0;
    CSimpleIniA cfg;
    CSimpleIniA skins_cfg;
    
};

extern Config* config;
extern Config* skins_cfg;
extern const char* ConfigName;

#define cfgget_f(section, key) GetSetting<float>(section, key)
#define cfgget_i(section, key) GetSetting<int>(section, key)
#define cfgget_b(section, key) GetSetting<bool>(section, key)
#define cfgget_s(section, key) GetStringSetting(section, key)
#define cfgget_c(section, key) GetColorSetting(section, key)

#define skin_cfgget_f(section, key) GetSkinSetting<float>(section, key)
#define skin_cfgget_i(section, key) GetSkinSetting<int>(section, key)
#define skin_cfgget_b(section, key) GetSkinSetting<bool>(section, key)
#define skin_cfgget_s(section, key) GetSkinStringSetting(section, key)
#define skin_cfgget_c(section, key) GetSkinColorSetting(section, key)

