#ifndef main_h
#define main_h

#include <stdio.h>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <sys/mman.h>
#include <dlfcn.h>
#include <fstream>
#include <mach/mach_traps.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach.h>
#include <mach-o/dyld_images.h>
#include <mach-o/loader.h>
#include <libproc.h>
#include <sys/stat.h>
#include <cstddef>
#include <codecvt>
#include <cstring>
#include <sstream>
#include <vector>
#include <strings.h>
#include <ios>
#include <iomanip>
#include <pwd.h>
#include <zconf.h>
#include <cstdio>

using namespace std;

#include "SDK/CEffects.h"
#include "SDK/Vector.h"
#include "SDK/Others.h"
#include "SDK/common.h"
#include "SDK/Color.h"
#include "SDK/IBaseClientDLL.h"
#include "SDK/ISurface.h"
#include "SDK/IPanel.h"
#include "SDK/ICvar.h"
#include "SDK/netvarmanager.h"
#include "SDK/offsets.h"
#include "SDK/C_BaseEntity.h"
#include "SDK/IClientEntityList.h"
#include "SDK/IVDebugOverlay.h"
#include "SDK/IEngineClient.h"
#include "SDK/IEngineTrace.h"
#include "SDK/IMaterial.h"
#include "SDK/IVModelRender.h"
#include "SDK/IGameMovement.h"
#include "SDK/IVModelInfo.h"
#include "SDK/IMaterialSystem.h"
#include "SDK/CUserCmd.h"
#include "SDK/IPrediction.h"
#include "SDK/CGlobalVarsBase.h"
#include "SDK/IInputSystem.h"
#include "SDK/IPhysicsSurfaceProps.h"
#include "SDK/CViewSetup.h"
#include "SDK/CInput.h"
#include "SDK/VMT.h"
#include "SDK/IEngneVGui.h"
#include "SDK/GameEvent.h"
//
//#include "SDK/IBaseClientState.h"
//#include "SDK/CCSGameRules.h"

/* Variables */
#include "bvars.h"

/* Interfaces */
#include "interfaces.h"

/* Drawings */
#include "drawings.h"

/* Patternscanner */
#include "patternscan.h"

/* Utilities */
#include "utils.h"

/* Hakes */
#include "haker.h"

/* Hooks */
#include "Hooks.h"


#endif /* main_hpp */
