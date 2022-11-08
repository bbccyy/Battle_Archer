
#include <stdio.h>

//#include "Socket.h"

#ifdef _MSC_VER  
    #define BATTLE_EXPORT_FOR_GO_API _declspec(dllexport)
#elif defined(__APPLE__)
    #define BATTLE_EXPORT_FOR_GO_API  extern
#else
	#define BATTLE_EXPORT_FOR_GO_API
#endif


typedef void(*LogFunc)(int, void*, int);



extern "C"
{
    BATTLE_EXPORT_FOR_GO_API void initLog(const char* aPath, int aLogLevel);
    
    BATTLE_EXPORT_FOR_GO_API void restartLog();

    BATTLE_EXPORT_FOR_GO_API int initBattle(const char* aDbFromExecelPath, 
                    const char* aDbFromEditorPath, int aThreadNum);

    #ifdef BATTLE_SOCKET
    BATTLE_EXPORT_FOR_GO_API int startBattleThread(const char* aUnixSocketPath, int aLogLevel);
    #endif 

    BATTLE_EXPORT_FOR_GO_API char* runBattle(const char*aBattleArgsPtr, int aBatleArgsLen,
        const char* aToken, int aTokenLen, int* aRetCode, int* aRetLen);

    BATTLE_EXPORT_FOR_GO_API void stopBattle();
    BATTLE_EXPORT_FOR_GO_API char * getVersionInfo();
    BATTLE_EXPORT_FOR_GO_API char * getBattleCodeVersion();
	BATTLE_EXPORT_FOR_GO_API char * getBattleVer();
	BATTLE_EXPORT_FOR_GO_API char * getDesignConfVer();
}