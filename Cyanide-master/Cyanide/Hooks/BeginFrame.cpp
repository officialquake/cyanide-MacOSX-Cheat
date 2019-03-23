#include "../main.h"

bool CreateMove::sendPacket = false;

void hkBeginFrame(void* thisptr, float frameTime) {
    
    if (!pEngine->IsInGame()) {
        CreateMove::sendPacket = true;
        *bSendPacket = CreateMove::sendPacket;
    }
    
    return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
    
}

