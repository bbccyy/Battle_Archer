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

#include <vector>
#include "Log/Log.h"
#include "ForServer/ExportForGo.h"
#include "tool.h"
#include "LuaRunner.h"
#include <fstream>

#ifdef GPERFTOOLS
#include <gperftools/profiler.h>
#endif


using namespace std;

struct ThreadParam
{
	vector<string>* argsPaths;
	int id;
};

string runBattle(string aBattleArgs, bool aToJson = false)
{
	BattleInstance battle;
	int ret = battle.InitWithPbStr(aBattleArgs.c_str(), aBattleArgs.size());
	if (ret != 0)
	{
		LOG_WARN("init battle failed");
		return "";
	}
	ofstream out("./benchCmd.json");
	int userInputIdx = 0;
	int userInputSize = battle.GetUserInputSize();
	TBattleFieldInput curInput;
	if (userInputSize > 0)
		curInput = battle.GetUserInput(userInputIdx);
	while (battle.TickEnterField(0));
	if (aToJson)
	{
		out << LuaRunner::CmdPbToJson(battle.FetchViewCmd());
		out.flush();
	}
	while (battle.GetResultType() == EBattleResult::None)
	{
		while (userInputIdx < userInputSize &&
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
			case EBattleInput::UnregisterSemi:
			case EBattleInput::None:
			default:
				LOG_WARN("Unexpected user input found: %d", curInput.event());
				break;
			}
			userInputIdx++;
			if (userInputIdx < userInputSize)
				curInput = battle.GetUserInput(userInputIdx);
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
		out.close();
	}
	return battle.ReportResult();
}

#ifdef BATTLE_SOCKET
void threadRunBattleSocket(ThreadParam aParam)
{
	char socketPath[256]; 
	sprintf(socketPath, "var/socket_%d", aParam.id);			
	int ret = startBattleThread(socketPath, 1);
	if(ret != 0)
	{
		LOG_WARN("startBattleThread failed. err:%d ", ret);
		return;
	}
	UnixSocketClient conn;
	ErrorNo err = conn.InitClient(socketPath);
	if(err != ErrorNo::Ok)
	{
		LOG_WARN("InitClient failed. err:%d ", err);
		return;
	}
	BattleMsg* msg;
	for( auto argsPath : *aParam.argsPaths )
	{
		struct timeval startTime, endTime, deltTime;
		LOG_INFO("start run %s thread:%d", argsPath.c_str(), std::this_thread::get_id());
		BattleMsgReq req;
		req.mBattleArgs = LoadBattleArgs(argsPath.c_str());
		req.mToken = "";
		gettimeofday(&startTime, NULL);					
		conn.Send(&req);		
		BattleMsgRsp* rspMsg = nullptr;
		while(rspMsg == nullptr)
		{
			int intRet = conn.Recv(msg);
			if(intRet != 0)
			{			
				LOG_WARN("read msg from battle failed");	
				break;				
			}
			switch(msg->mMsgId)
			{
				case MsgId::Log:					
					LOG_INFO( "%s", ((BattleMsgLog*)msg)->mContent.c_str() );
					delete msg;
					break;
				case MsgId::BattleRsp:
					rspMsg = (BattleMsgRsp*)msg;
					break;
			}			
		}
		if( rspMsg )
		{
			gettimeofday(&endTime, NULL);	
			timersub(&endTime, &startTime, &deltTime);	
			double cost = deltTime.tv_sec + (1.0 * deltTime.tv_usec)/1000000;
			LOG_INFO("run %s cost:%f ms ret:%s", 
					argsPath.c_str(), 
					cost,
					rspMsg->mErrMsg.c_str());
			delete rspMsg;
		}
		else
		{
			break;
		}
	}
	BattleMsgQuit quitMsg;
	conn.Send(&quitMsg);
	//要等战斗线程退出，可能那边有些日志在打印
	bool waiting = true;
	while(waiting)
	{
		int intRet = conn.Recv(msg);
		if(intRet != 0)
		{			
			LOG_WARN("read msg from battle failed");	
			break;				
		}		
		switch(msg->mMsgId)
		{
			case MsgId::Log:					
				LOG_INFO( "%s", ((BattleMsgLog*)msg)->mContent.c_str() );				
				break;
			case MsgId::QuitConfirm:
				waiting = false;
				break;
			default:
				LOG_INFO("ignore msg:%d", msg->mMsgId);
		}			
		delete msg;
	}
}
#endif

void threadRunBattleThreadPool(ThreadParam aParam)
{
	for( auto argsPath : *aParam.argsPaths )
	{
		struct timeval startTime, endTime, deltTime;
		LOG_INFO("start run %s thread:%d", argsPath.c_str(), std::this_thread::get_id());		

		auto args = LoadBattleArgs(argsPath.c_str());

		gettimeofday(&startTime, NULL);		
		int ret, retLen;			
		auto retStr = runBattle(args.c_str(), args.size(), argsPath.c_str(), argsPath.size(), &ret, &retLen );
		free(retStr);

		gettimeofday(&endTime, NULL);	
		timersub(&endTime, &startTime, &deltTime);	
		double cost = deltTime.tv_sec + (1.0 * deltTime.tv_usec)/1000000;
		LOG_INFO("run %s cost:%f ms", 
				argsPath.c_str(), 
				cost);

	}
}

void threadRunBattleDirect(ThreadParam aParam)
{
	int ct = 0;
	for( auto argsPath : *aParam.argsPaths )
	{
		struct timeval startTime, endTime, deltTime;
		LOG_INFO("start run %s thread:%d", argsPath.c_str(), std::this_thread::get_id()); 
		printf("start run %s thread:%d\n", argsPath.c_str(), std::this_thread::get_id());
		auto args = LoadBattleArgs(argsPath.c_str());

		gettimeofday(&startTime, NULL); 
		runBattle(args, ct == 5);
		gettimeofday(&endTime, NULL);	
		timersub(&endTime, &startTime, &deltTime);	
		double cost = deltTime.tv_sec + (1.0 * deltTime.tv_usec)/1000000;
		printf("args %d done\n", ct);
		LOG_INFO("run %s cost:%f ms", 
				argsPath.c_str(), 
				cost);
		ct++;
	}
}
void batchRun(int aBenchType, int aThreadNum, const char* aProf)
{
	printf("batchRun  type:%d, thread:%d\n", aBenchType, aThreadNum);
	//genTestArgs();

	#ifdef GPERFTOOLS
	if(aProf)
	{
		LOG_WARN("start gperftools");
		ProfilerStart(aProf);
	}
	#endif
	const char* argsDir = "test/args";
	DIR *foder = opendir(argsDir);	
	struct dirent *nextFile;
	char filepath[512];

	vector<vector<string> > argsFiles; 
	argsFiles.resize(aThreadNum);
	
	vector<thread*> concurrentThread;
	int index = 0;
	while ((nextFile = readdir(foder)) != NULL)
	{		
		if(strcmp(nextFile->d_name, ".") == 0 || strcmp(nextFile->d_name, "..") == 0)
		{
			continue;
		}
		sprintf(filepath, "%s/%s", argsDir, nextFile->d_name); 
		argsFiles[index%aThreadNum].push_back(filepath);
		index++;
	}
	struct timeval startTime, endTime, deltTime;
	gettimeofday(&startTime, NULL);					
	for(int i = 0; i < aThreadNum; i++)
	{
		ThreadParam param;
		param.argsPaths = &argsFiles[i];
		param.id = i;
		thread* t;
		switch(aBenchType)
		{
			case 1:
				t = new thread(threadRunBattleDirect, param );	
				break;
			case 2:
				t = new thread(threadRunBattleThreadPool, param );	
				break;
#ifdef BATTLE_SOCKET
			case 3:
				t = new thread(threadRunBattleSocket, param );	
				break;
#endif
			default:
				LOG_WARN("invalid benchType:%d", aBenchType);
				return;
		}
		
		concurrentThread.push_back(t);
	}
	
	for(int i = 0; i < concurrentThread.size(); i++)
	{
		concurrentThread[i]->join();
		delete concurrentThread[i];
	}
	gettimeofday(&endTime, NULL);	
	timersub(&endTime, &startTime, &deltTime);	
	double cost = deltTime.tv_sec + (1.0 * deltTime.tv_usec)/1000000;
	LOG_INFO("allNum:%d allCost:%f", index, cost);
	printf("allNum:%d allCost:%f\n", index, cost);
			
	stopBattle();
	#ifdef GPERFTOOLS
	if(aProf)
	{
		ProfilerStop();
	}	
	#endif
}

string getViewCmdFromResult(string aResultStr)
{
	TBattleResult* pbMsg = new TBattleResult;
	if (pbMsg->ParsePartialFromArray(aResultStr.c_str(), aResultStr.size()) == false)
	{
		delete pbMsg;
		LOG_FATAL("parse battle result failed");
		return "";
	}

	TBattleViewCmdList battleViewCmdList;
	if (battleViewCmdList.ParsePartialFromArray(pbMsg->battlereportstr().c_str(), pbMsg->battlereportstr().size()) == false)
	{
		LOG_FATAL("parse view command list result failed");
		return "";
	}
	std::vector<TBattleViewCmd*> vBattleViewCmd;
	for (int i = 0; i < battleViewCmdList.cmds().size(); i++)
	{
		vBattleViewCmd.push_back(new TBattleViewCmd(battleViewCmdList.cmds(i)));
	}
	string strJson = LuaRunner::CmdPbToJson(vBattleViewCmd);

	/*ofstream viewCmdFromLuaStream;
	viewCmdFromLuaStream.open((string("/view_cmd_lua.json")).c_str(), std::ios_base::out);
	viewCmdFromLuaStream << strJson;
	viewCmdFromLuaStream.close();
	Log::getInstance()->flush();*/

	return strJson;

	//return pbMsg->battlereportstr();
}

void benchCheckLua()
{	
	//genTestArgs();

	const char* argsDir = "test/args";
	DIR *foder = opendir(argsDir);
	struct dirent *nextFile;
	char filepath[512];
	struct timeval startTime, endTime, deltTime;
	int index = 0;
	while ((nextFile = readdir(foder)) != NULL)
	{
		Log::getInstance()->clear();
		LuaRunner::clearLog();
		if (strcmp(nextFile->d_name, ".") == 0 || strcmp(nextFile->d_name, "..") == 0)
		{
			continue;
		}
		index++;
		if (index > 3 && index < 0)
		{
			continue;
		}
		sprintf(filepath, "%s/%s", argsDir, nextFile->d_name);
		auto args = LoadBattleArgs(filepath);
		
		gettimeofday(&startTime, NULL);
		auto resultCpp = runBattle(args);
		gettimeofday(&endTime, NULL);
		timersub(&endTime, &startTime, &deltTime);
		double costCpp = deltTime.tv_sec + (1.0 * deltTime.tv_usec) / 1000000;

		gettimeofday(&startTime, NULL);
		string resultLua = LuaRunner::RunBattle(args);
		gettimeofday(&endTime, NULL);
		timersub(&endTime, &startTime, &deltTime);
		double costLua = deltTime.tv_sec + (1.0 * deltTime.tv_usec) / 1000000;

		auto cmdCpp = getViewCmdFromResult(resultCpp);
		auto cmdLua = getViewCmdFromResult(resultLua);

		if (cmdCpp == cmdLua)
		{
			LOG_INFO("[%d][%s]costCpp:%f costLua:%f", index, nextFile->d_name, costCpp, costLua);
			printf("[%d][%s]costCpp:%f costLua:%f\n", index, nextFile->d_name, costCpp, costLua);
		}
		else
		{
			LOG_WARN("[%d]%s diff", index, filepath);
			ofstream f;
			f.open("view_cmd_cpp", std::ios_base::out);
			f << cmdCpp;
			f.close();
			f.open("view_cmd_lua", std::ios_base::out);
			f << cmdLua;
			f.close();
			break;
		}

	}
}