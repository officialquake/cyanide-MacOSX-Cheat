#include "main.h"
#include "Config.h"


int __attribute__((constructor)) Init() {
    /* do shiz her. */
    
    
    InitializeInterfaces();
    
    InitializeVMTs();
    
    InitializeHooks();
    
    NetVarManager::DumpNetvars();
    
    Offsets::getOffsets();
    
    pCvar->ConsoleColorPrintf(Color::Blue(), "Welcome to Cyanide V2.2!\n");
    pCvar->ConsoleColorPrintf(Color::White(), "Press ");
    pCvar->ConsoleColorPrintf(Color::Green(), "ALT ");
    pCvar->ConsoleColorPrintf(Color::Yellow(), "To Open The Menu\n");
    pCvar->ConsoleColorPrintf(Color::White(), "New Mods In This Version...\n");
    pCvar->ConsoleColorPrintf(Color::Green(), "Main Mods Added:\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Slightly Better Aimbot\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Higher Aimbot FOV\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Longer Rendering Chams/WH\n");
    pCvar->ConsoleColorPrintf(Color::Green(), "Visual Mods Added:\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Box ESP\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Name ESP\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Health Text\n");
    pCvar->ConsoleColorPrintf(Color::Blue(), "Updated By Breadstick And Manigamer22\n");

    
    return 0;
}

void __attribute__((constructor)) DeInit() {
}

