#include "main.h"

void hkOverrideView(void* thisptr, CViewSetup& setup) {
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    createmovehook->GetOriginalMethod<tOverrideView>(19)(thisptr, setup);
    
}
