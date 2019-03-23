#include "../main.h"
#include "../Hacks/esp.h"

bool qOnce = false;
bool bPanelOnce = false;

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce) {
    
    painthook->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    static VPANEL last = 0;
    
    if(!last) {
        
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel")) {
            
            framefont = draw->createfont(framefont, "Tahoma", 14, FONTFLAG_NONE);
            espfont = draw->createfont(espfont, "Tahoma", 12, FONTFLAG_OUTLINE);
            
            fontMenu = draw->createfont(fontMenu, "Courier New", 14, FONTFLAG_OUTLINE);
            titleFont = draw->createfont(titleFont, "Banco", 20, FONTFLAG_OUTLINE);
            last = panel;
            
        }
    }
    
    if(!bPanelOnce) {
        // Chams
        vars.colors.tchams = Color(0, 124, 255, 255);
        vars.colors.ctchams = Color(0, 124, 255, 255);
        // Chams Ignore
        vars.colors.tchams_ign = Color(255, 0, 83); // T Ign
        vars.colors.ctchams_ign = Color(255, 0, 83); // CT Ign
        // Box
        vars.colors.tbox = Color(0, 124, 255); // T Box
        vars.colors.ctbox = Color(0, 124, 255); // CT Box
        // Box Ignore
        vars.colors.tbox_ign = Color(255, 0, 83, 255); // T Box Ignore
        vars.colors.ctbox_ign = Color(255, 0, 83, 255); // CT Box Ignore
        // Hands
        vars.colors.hands = Color::Red();
        vars.colors.hands_ign = Color::Blue();
                
        //vars.colors.world = Color::Green  (); // WiP
        
        bPanelOnce = true;
        
    }

    if(panel == last) {
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
            return;
        
        pwnmymenu(); // Gets keypress to diplay menu
        DrawPlayerESP(); // Draws ESP

        
        if(vars.menu) {
            
            draw->drawmenu();
            draw->drawmouse();
            
        }
                
    }
}
