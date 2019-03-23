extern ISurface* pSurface;
extern CEffects* pCEffects; //NY
extern IPanel* pPanel;
extern ICvar* pCvar;
extern IBaseClientDLL* pClient;
extern IClientEntityList* pEntList;
extern IVDebugOverlay* pOverlay;
extern IEngineClient* pEngine;
extern IVModelInfo* pModelInfo;
extern IEngineTrace* pEngineTrace;
extern IClientMode* pClientMode;
extern CGlobalVarsBase* pGlobals;
extern IInputSystem* pInputSystem;
extern CInput* pInput;
extern IMaterialSystem* pMatSystem;
extern IVModelRender* pModelRender;
extern IPrediction* pPrediction;
extern IGameMovement* pGameMovement;
extern IMoveHelper* pMoveHelper;
extern IPhysicsSurfaceProps* pPhysics;
//
extern IEngineVGui* pEngineVGui;
extern IGameEventManager2* pGameEventManager;
extern SendClanTagFn SetTag;
extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
extern StartDrawingFn StartDrawing;
extern FinishDrawingFn FinishDrawing;
extern RandomIntFn RandomInt;
extern CMoveData* MoveData;
extern int* nPredictionRandomSeed;

extern VMT* painthook;
extern VMT* createmovehook;
extern VMT* clientvmt;
extern VMT* modelhook;
extern VMT* predhook;
extern VMT* vguivmt;
extern VMT* materialVMT;
extern VMT* game_event_vmt;
extern VMT* prediction;


extern RecvVarProxyFn g_pSequence;
