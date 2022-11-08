/**********************************************************************************************************************
 *
 * Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
 * $Id$
 *
 **********************************************************************************************************************/
 
/**
 * @file $HeadURL$
 * @author $Author$
 * @date $Date$
 * @version $Revision$
 * @brief
 *
 **/
#include <time.h>
#include <vector>
#include "net/Battle.pb.h"
#include "net/BattleViewCmd.pb.h"
#include "BattleInstance.h"
#include <fstream>
#include <stdarg.h>
#include "tool.h"
#include "ConfigMgr/test.h"
#include <thread> 
#include <ctime>
#include <stdlib.h>
#include "bench.h"
#include "LuaRunner.h"
using namespace pb;
using namespace std;

void RunOnBattle(string aOutPath, string aBattleArgs, vector<UserInput>& aInputArr, vector<UserInput>& aBehaviourArr, bool aToJson = true, bool aUseArgsInput = false, int aSeed = 0, bool aUseResult = false)
{
	try
	{
		ofstream out(aOutPath);
		
		int curInputIndex = 0;
		UserInput* nextInput = aInputArr.size() > 0 ? &aInputArr[curInputIndex] : nullptr; 
		int curBehaviourIndex = 0;
		UserInput* nextBehaviour = aBehaviourArr.size() > 0 ? &aBehaviourArr[curBehaviourIndex] : nullptr;

		struct timeval startTime, endTime, deltTime;
		gettimeofday(&startTime, NULL);
		BattleInstance battle;
		if (aUseResult)
		{
			if (battle.InitWithRetPbStr(aBattleArgs.c_str(), aBattleArgs.size()) != 0)
			{
				LOG_FATAL("init battle from results failed");
				return;
			}
		}
		else
		{
			if (battle.InitWithPbStr(aBattleArgs.c_str(), aBattleArgs.size()) != 0)
			{
				LOG_FATAL("init battle from args failed");
				return;
			}
		}
		if (aSeed != 0)
			battle.SetRandSeed(aSeed);
		//use user inputs from args
		int userInputIdx = 0;
		int userInputSize = battle.GetUserInputSize();
		TBattleFieldInput curInput;
		if (userInputSize > 0 )
			curInput = battle.GetUserInput(userInputIdx);

		//battle.SetAuto(false); 
		//battle.SetAuto(true);    
		while (battle.TickEnterField(0)); 
		if (aToJson)
		{
			out << LuaRunner::CmdPbToJson(battle.FetchViewCmd());
			out.flush();
		}
		while (battle.GetResultType() == EBattleResult::None)
		{
			while (userInputIdx < userInputSize &&
				battle.GetCurField() > curInput.fieldnum())
			{
				userInputIdx++;
				if (userInputIdx < userInputSize)
					curInput = battle.GetUserInput(userInputIdx);
			}
			while (aUseArgsInput && userInputIdx < userInputSize && 
				battle.GetCurField() == curInput.fieldnum() && 
				battle.GetFrameTime() == curInput.frametime()) 
			{
				battle.mRecordMode = false;
				LOG_WARN("userInput=[Id:%d, fnum:%d, time:%d, event:%d, eid:%d]", 
					curInput.index(), curInput.fieldnum(), curInput.frametime(), curInput.event(), curInput.eid());
				switch (static_cast<EBattleInput>(curInput.event()))
				{
				case EBattleInput::ExecuteSkill:
					battle.ExecuteRageSkill(curInput.eid());
					break;
				case EBattleInput::EnableAuto:
					battle.SetAuto(true);
					break;
				case EBattleInput::DisableAuto:
					battle.SetAuto(false);
					break;
				case EBattleInput::None:
				default:
					LOG_WARN("Unexpected user input found: %d", curInput.event());
					break;
				}
				userInputIdx++;
				if (userInputIdx < userInputSize)
					curInput = battle.GetUserInput(userInputIdx);
			}

			while (!aUseArgsInput && nextInput && 
				battle.GetCurField() == nextInput->field  && 
				battle.GetFrameTime() >= nextInput->time)
			{
				switch (nextInput->cmd)
				{
				case EUserInputCmdExecuteRageSkill:
					battle.ExecuteRageSkill(nextInput->commen1);
					break;
				default:
					LOG_WARN("invalid cmd:%d", nextInput->cmd);
				}
				curInputIndex++;
				nextInput = curInputIndex < aInputArr.size() ? &aInputArr[curInputIndex] : nullptr;
			}

			while (nextBehaviour && 
				battle.GetCurField() == nextBehaviour->field  && 
				battle.GetFrameTime() == nextBehaviour->time)
			{
				switch (nextBehaviour->cmd)
				{
				case EBehaviourInputCmdAddUnit:
					battle.BehaviourAddUnit(nextBehaviour->commen1, nextBehaviour->commen2, nextBehaviour->commen3,
						nextBehaviour->commen4, nextBehaviour->py, nextBehaviour->pz, nextBehaviour->dx, nextBehaviour->dy, nextBehaviour->dz, false, false);
					break;
				case EBehaviourInputCmdGotoResult:
					battle.BehaviourGotoResult(nextBehaviour->commen1);
					break;
				case EBehaviourInputCmdGotoNextField:
					battle.BehaviourGotoNextField();
					break;
				case EBehaviourInputCmdMoveToStandPoint:
					battle.BehaviourMoveToStandPoint(nextBehaviour->commen1, string(nextBehaviour->name).c_str(), nextBehaviour->commen2, 
						nextBehaviour->commen3, nextBehaviour->commen4, nextBehaviour->dx, nextBehaviour->dy, nextBehaviour->dz);
					break;
				case EBehaviourInputCmdExecuteSkill:
					battle.BehaviourExecuteSkill(nextBehaviour->commen1, nextBehaviour->commen2, nextBehaviour->commen3);
					break;
				case EBehaviourInputCmdObstacleVisible:
					//battle.BehaviourObstacleVisible(nextBehaviour->name, nextBehaviour->commen2);
					break;
				case EBehaviourInputCmdHideUnit:
					battle.BehaviourHideUnit(nextBehaviour->commen1, nextBehaviour->commen2);
					break;
				case EBehaviourInputCmdDeleteUnit:
					battle.BehaviourDeleteUnit(nextBehaviour->commen1);
					break;
				case EBehaviourInputCmdUnitAnim:
					battle.BehaviourUnitAnim(nextBehaviour->commen1, nextBehaviour->name);
					break;
				case EBehaviourInputCmdStopUnit:
					battle.BehaviourStopUnit(nextBehaviour->commen1, nextBehaviour->commen2);
					break;
				case EBehaviourInputCmdAddBuff:
					battle.BehaviourAddBuff(nextBehaviour->commen1, nextBehaviour->commen2, nextBehaviour->commen3, nextBehaviour->commen4, 0);
					break;
				case EBehaviourInputCmdSetTime:
					battle.BehaviourSetTime(nextBehaviour->commen1);
					break;
				case EBehaviourInputCmdSetExtraTime:
					battle.BehaviourSetExtraTime(nextBehaviour->commen1);
					break;
				case EBehaviourInputCmdSyncLocation:
					battle.BehaviourSyncLocation(nextBehaviour->commen1, nextBehaviour->commen2, nextBehaviour->commen3, nextBehaviour->commen4);
					break;
				case EBehaviourInputCmdSyncDirection:
					battle.BehaviourSyncDirection(nextBehaviour->commen1, nextBehaviour->commen2, nextBehaviour->commen3, nextBehaviour->commen4);
					break;
				default:
					LOG_WARN("invalid cmd:%d", nextBehaviour->cmd);
				}
				curBehaviourIndex++;
				nextBehaviour = curBehaviourIndex < aBehaviourArr.size() ? &aBehaviourArr[curBehaviourIndex] : nullptr;
			}

			battle.OnTick();

			if (aToJson)
			{
				out << LuaRunner::CmdPbToJson(battle.FetchViewCmd());
				out.flush();
			}
		}
		if (aToJson)
		{
			out << LuaRunner::CmdPbToJson(battle.FetchViewCmd());
			out.flush();
		}
		string resultStr = battle.ReportResult();
		WriteToFile(resultStr, "gen_results_cpp"); 
		gettimeofday(&endTime, NULL);
		timersub(&endTime, &startTime, &deltTime);
		double cost = deltTime.tv_sec + (1.0 * deltTime.tv_usec) / 1000000;		
		LOG_WARN("Battle ended {reason=%s} cost:%f", EBattleResultNames[static_cast<int>(battle.GetResultType())], cost);
		out.close();
	}
	catch (const char* message)
	{
		LOG_WARN("battle faield:%s", message);
	}
	catch (const string message)
    {
        LOG_WARN("battle failed:%s", message.c_str()); 
    }
	catch (...)
	{
		LOG_WARN("battle faield:");
	}
}


int main(int argc,char *argv[])
{	
	//参数解析
	int benchType = 0;
	int threadNum = 1;
	if (argc > 1)
	{
		benchType = atoi(argv[1]);
	}
	if (argc > 2)
	{
		threadNum = atoi(argv[2]);
	}
	const char* profPath = nullptr;
	if (argc > 3)
	{
		profPath = argv[3];
	}

	//初始化日志
	remove("log");
	remove("log.wf");
	int logLevel = Log::ELogLevelInfo;
	//int logLevel = Log::ELogLevelDebug;
	//int logLevel = Log::ELogLevelWarn;
	initLog("log", logLevel);
    int ret = testConvert();
    if ( ret !=  0)
    {
        LOG_FATAL("testConvert failed");
        return ret;
    }
	
	//找配置目录  
	string srcDir = Dirname(__FILE__);	
	auto branchProgramDir = srcDir.append("/../../../../../");
	auto sqlitePath = branchProgramDir;
	auto csvPath = branchProgramDir;
	sqlitePath.append("client_core/game/game_dev/confdb/sqlite/");
	csvPath.append("client_core/game/game_dev/confdb/csv/");
	//csvPath.append("/../Design/conf/conf_dev/confdb/csv");
	auto csvFromExcel = csvPath;
	auto dbFromEditor = sqlitePath + "dbFromEditor";
	if (initBattle(csvFromExcel.c_str(), dbFromEditor.c_str(), threadNum) != 0)
	{
		LOG_WARN("initBattle failed");
		return -1;
	}
	
	string luaPath = Dirname(__FILE__);
	luaPath = Dirname(luaPath.c_str());
	luaPath.append("/cpp2lua/lua");
	LuaRunner::Init(luaPath.c_str(), sqlitePath.c_str(), "lua_log", logLevel);

	benchType = 0;
	threadNum = 1;

	//启动批量测试
	if (benchType > 0)
	{
		if (benchType >= 10)
		{
			benchCheckLua();
		}
		else
		{
			batchRun(benchType, threadNum, profPath);
		}	
		SharedPoolBase::ReleaseAllPool();
		Log::getInstance()->flush();
		printf("done\n");
		return 0;
	}
	
	//开发用
	
	auto gameLogDir = branchProgramDir.append("client_core/game/game_dev/Log");
	auto argsInGame = gameLogDir + string("/record_battle_args");
	//argsInGame = "args/args__10014_10011_10040_10016_11000__10003_10005_10016_10023_11000_1_0";
	string battleArgsStr = LoadBattleArgs(argc > 2 ? argv[2] : argsInGame.c_str());

	//T:155000
	//{"E":"Damage","A":[10,7524179104504,4270642882349084,2,1114613,0,1,-755079,0,0,5,0]},
	vector<UserInput> inputArr;
	LoadUserInput((gameLogDir + string("/record_battle_input")).c_str(), inputArr);
	vector<UserInput> behaviourArr;
	LoadBehaviourInput((gameLogDir + string("/record_battle_behaviour")).c_str(), behaviourArr);

	bool runLua = false;
	bool toJson = true;
	bool useArgsInput = true;
	bool needResults = true;
	bool useResults = false;

	if (runLua)
	{
		string retInLua = LuaRunner::RunBattle(battleArgsStr);
		TBattleResult* pbMsg = new TBattleResult;
		if (pbMsg->ParsePartialFromArray(retInLua.c_str(), retInLua.size()) == false)
		{
			delete pbMsg;
			LOG_FATAL("parse battle result failed");
			return -1;
		}

		TBattleViewCmdList battleViewCmdList;
		if (battleViewCmdList.ParsePartialFromArray(pbMsg->battlereportstr().c_str(), pbMsg->battlereportstr().size()) == false)
		{
			LOG_FATAL("parse view command list result failed");
			return -1;
		}
		std::vector<TBattleViewCmd *> vBattleViewCmd;
		for (int i = 0; i < battleViewCmdList.cmds().size(); i++)
		{
			vBattleViewCmd.push_back(new TBattleViewCmd(battleViewCmdList.cmds(i)));
		}
		string strJson = LuaRunner::CmdPbToJson(vBattleViewCmd);

		ofstream viewCmdFromLuaStream;
		viewCmdFromLuaStream.open((gameLogDir + string("/view_cmd_lua.json")).c_str(), std::ios_base::out);
		viewCmdFromLuaStream << strJson;
		viewCmdFromLuaStream.close();
		Log::getInstance()->flush();
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	auto st = int(std::time(nullptr));
	for (int i = 0; i < 1; i++)
	{
		RunOnBattle((gameLogDir + string("/view_cmd.json")).c_str(), battleArgsStr, inputArr, behaviourArr, toJson, useArgsInput, 0, useResults);
		printf("done %d, %d \n", i, i+st);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	float span = float((t2 - t1).count()) / 1000000000;
	LOG_WARN("total cost %f in s", span);

	SharedPoolBase::ReleaseAllPool();
	Log::getInstance()->flush();
	printf("done\n");
	return 0;
}
