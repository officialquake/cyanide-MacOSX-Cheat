#include "main.h"

void hkRunCommand(void* thisptr, C_BaseEntity* pLocal, CUserCmd* pCmd, void* pHelper) {
    
    predhook->GetOriginalMethod<tRunCommand>(20)(thisptr, pLocal, pCmd, pHelper);
    
    pMoveHelper = (IMoveHelper*)pHelper;
    
}
