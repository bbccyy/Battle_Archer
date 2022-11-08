#pragma once

#include <vector>
#include <mutex>
#include "Log/Log.h"
#include "net/Battle.pb.h"
#include <time.h>

#ifdef _MSC_VER
#include "dirent.h"
#include <windows.h>
#include <Winsock2.h>
#else
#include <dirent.h>
#include <sys/time.h>
#endif
#include <fstream>
#include <stdarg.h>

using namespace pb;
using namespace std;



enum EInputCmd
{
	EUserInputCmdExecuteRageSkill,
	EBehaviourInputCmdAddUnit,
	EBehaviourInputCmdGotoResult,
	EBehaviourInputCmdGotoNextField,
	EBehaviourInputCmdMoveToStandPoint,
	EBehaviourInputCmdExecuteSkill,
	EBehaviourInputCmdObstacleVisible,
	EBehaviourInputCmdHideUnit,
	EBehaviourInputCmdDeleteUnit,
	EBehaviourInputCmdUnitAnim,
	EBehaviourInputCmdStopUnit,
	EBehaviourInputCmdAddBuff,
	EBehaviourInputCmdSetTime,
	EBehaviourInputCmdSetExtraTime,
	EUserInputCmdExecuteUnparalleledSkill,
	EBehaviourInputCmdSyncLocation,
	EUserInputCmdUnregisterSemiAutoSkill,
	EBehaviourInputCmdSyncDirection,
	EUserInputCmdAddUnitTD,
	EUserInputCmdDeleteDeadUnitTD,
	EUserInputCmdInitNextWaveTD,
	EUserInputCmdExecuteBattleSoulSkill,
};

struct UserInput
{
	int time;
	int cmd;
	int field;
	int py;
	int pz;
	int dx;
	int dy;
	int dz;
	int commen1;   //armyId or entityId etc...
	int commen2;   //tplId
	int commen3;   //level
	int commen4;   //px
	char name[128];
};

int Mkdir(const char* aPath);
string Dirname(const char* aPath);

string LoadBattleArgs(const char* file);
void LoadUserInput(const char* file, vector<UserInput>& inputArr);
void LoadBehaviourInput(const char* file, vector<UserInput>& inputArr);
void WriteToFile(string aStr, const char* aName);

void perm(int* aArr, int aN, int aM, vector<vector<int> >& aRet);
void genTestArgs();


#ifdef _MSC_VER
inline int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}

inline void timersub(struct timeval *endPre, struct timeval *beginPre, struct timeval *result)
{
	do
	{
		(result)->tv_sec = (endPre)->tv_sec - (beginPre)->tv_sec;
		(result)->tv_usec = (endPre)->tv_usec - (beginPre)->tv_usec;
		if ((result)->tv_usec < 0)
		{
			--(result)->tv_sec;
			(result)->tv_usec += 1000000;
		}
	} while (0);

}

#endif

