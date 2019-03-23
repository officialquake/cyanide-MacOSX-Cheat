extern Vector tpangles;

typedef void(*tPaintTraverse)(void*, VPANEL panel, bool forceRepaint, bool allowForce);
typedef bool(*tCreateMove)(void*, float flSampleInput, CUserCmd* cmd);
typedef int(*tKeyEvent)(void*, int, int, const char*);
typedef void(*tOverrideView)(void*, CViewSetup& setup);
typedef void(*tFrameStage)(void*, ClientFrameStage_t);
typedef void(*tDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
typedef void(* tRunCommand)(void*, C_BaseEntity*, CUserCmd*, void*);
typedef void (*PaintFn) (void*, PaintMode_t);
typedef void (*BeginFrameFn) (void*, float);
typedef bool(*tFireGameEvent)(void*, IGameEvent*);


extern void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce);
extern bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd);
extern int hkKeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding);
extern void hkOverrideView(void* thisptr, CViewSetup& setup);
extern void hkFrameStage(void* thisptr, ClientFrameStage_t curStage);
extern void hkDrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);
extern void hkRunCommand(void* thisptr, C_BaseEntity* pLocal, CUserCmd* pCmd, void* pHelper);
extern void hkPaint(void* thisptr, PaintMode_t mod);
extern void hkBeginFrame(void* thisptr, float frameTime);
extern bool hkFireEventClientSide(void* thisptr, IGameEvent* event);

extern Vector vViewAngles;
extern void getModule(task_t task, mach_vm_address_t * start, off_t * length, const char * module, Byte * buffer, bool readBuffer);
extern uintptr_t GetLibraryAddress(const char* moduleName);
extern bool* bSendPacket;

extern RecvVarProxyFn OldProxy_X, OldProxy_Y, OldProxy_Z, OldProxy_Velocity, VeloProx1, VeloProx2, VeloProx3;

namespace CreateMove {
    extern bool sendPacket;
}
