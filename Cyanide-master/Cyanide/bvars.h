class ccombobox {
public:
    /* this class only handles all the open checks for the combo boxes, nothing more. */
    bool esp_opend;
    bool hitbox_opend;
    bool aaY_opend;
    bool aaX_opend;
    bool hands_opend;
    bool players_opend;
    bool rc_opend;
    bool playerlist_opend_x[64];
    bool playerlist_opend_y[64];
    bool colors_opend;
    
    bool cfg_opend;
    
    bool misc_clantag, misc_name, misc_changename;
    int inputIndex = 0;
};

/* Change values for settings to be active on startup */
class cVariables : public ccombobox {
public:
    bool menu = false;
    int buttonPadding = 24;
    int tabIndex;
    int menueffect = 0;
    bool cfgInit = false;
    
    class cAimbot {
    public:
        bool enabled    = false;
        bool silent        = false;
        bool psilent    = false;
        bool smooth        = false;
        bool rcs        = false;
        float smoothf    = .0f;
        int rcsf        = 25;
        int fov            = 180;                // 20
        int hitbox        = 0;
        int pointscale    = 0;
        int bone        = 0;
        bool hitscan    = false;
        bool autowall    = false;
        bool autoshoot    = false;
        bool autopistol = false;
        bool autocrouch = false;
        bool autostop    = false;
        bool trigger    = true;
        bool prediciton = false;
        int aimKey = 107;
        int triggerKey = 110;
        int selected;
    }aimbot;
    
    class cVisuals {
    public:
        bool enabled    = true;
        bool box        = true;
        bool name        = true;
        bool healthtext = true;
        bool armourtext = false;
        bool weapon        = true;
        bool chams        = false;
        bool wallhack   = true; // Visble Chams
        bool enemyonly    = true;
        bool cash       = false;
        bool Scoped     = false;
        bool Rescuing   = false;
        bool Defusing   = true;
        bool skinc      = true;
        bool watermark  = true;
        
        bool whenshooting = false;
        
        int handsType    = 0; // 0 - lit, 1 - texture, 2 - wireframe, 3 - nohands
        int playersType = 0;
        
        int handchams_alpha        = 255;
        int playerchams_alpha    = 255;
        
        int coltab;
        
        int tchams[4] = { 0, 124, 255, 255 }; // T
        int ctchams[4] = { 0, 124, 255, 255 }; // CT
        
        int tchams_ignore[4] = { 255, 0, 83, 255 };// T Ign
        int ctchams_ignore[4] = { 255, 0, 83, 255 }; // CT Ign this color is soo fucking p100!
        
        int tbox[4] = { 0, 124, 255, 255 }; // T Box
        int ctbox[4] = { 0, 124, 255, 255 }; // CT Box
        
        int tbox_ignore[4] = { 255, 0, 83, 255 }; // T Box Ign
        int ctbox_ignore[4] = { 255, 0, 83, 255 }; // CT Box Ign  this color is soo fucking p100!
        
    }visuals;
    
    class cMisc {
    public:
        bool enabled = true;
        bool antiuntrust = true;
        bool norecoil = false;
        bool novisualrecoil = false;
        bool nightsky = false;
        bool nosky = false;
        bool worldpaint = false;
        bool bhop = true;
        bool autostrafe = true;
        bool circlestrafe = false;
        bool thirdpersonmode = false;
        bool antiscreenshot = true;
        int fov = 13;
        bool airstuck = false;
        bool showrank = true;
        int fakelagfactor = 0;
        bool fakelag = false;
        bool adaptive = false;
        bool noflash = true;
        float flashalpha = 0.f;
        bool findtarget = false;
        bool spammer = false;
        bool clantag = true;
        // Anti Aim
        int aaY = 0;
        int aaX = 0;
        bool attargets = false;
        int customaa = 0;
        int fakeyaw = 180;
        int realyaw = 20;
        bool fakeaa = true;
        
        bool hitmarker = true;
        bool showspectators  = true;
    }misc;
    
    class cColors {
    public:
        int tab = 0;
        /*
         class cColors {
         public:
         int tab = 0;
         */
        Color chamscolor;
        
        Color ctchams;
        Color tchams;
        
        Color ctchams_ign;
        Color tchams_ign;
        
        Color tbox;
        Color tbox_ign;
        
        Color ctbox;
        Color ctbox_ign;
        
        Color hands;
        Color hands_ign;
        
        Color world;
        
        
    }colors;
    
    class cMain {
    public:
        int tab = 0;
    }main;
    
    int playerTab = 0;
    bool canmodify;
};

struct Corrections {
    float x, y;
    bool prefer;
    bool whitelist;
    bool resolved;
    
    int dropdown_x = 0;
    int dropdown_y = 0;
};

extern Corrections gCorrections[64];

extern cVariables vars;
