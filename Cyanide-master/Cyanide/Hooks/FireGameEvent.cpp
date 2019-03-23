#include "../main.h"
#include "../Hacks/skinchanger.h"

bool hkFireEventClientSide(void* thisptr, IGameEvent* event){
    
    
    
    return game_event_vmt->GetOriginalMethod< tFireGameEvent >(11)(thisptr, event);
}
