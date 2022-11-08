/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author liyingbo
* @date $Date$
* @version $Revision$
* @brief
*
**/

#pragma once
#include "lua_bridge.h"
#include "string"
#include <vector>

namespace pb {
	class TBattleViewCmd;
}

using pb::TBattleViewCmd;


using namespace std;

class LuaRunner
{
public:
	static void Init(const char* aLuaPath, const char* aConfPath, const char* aLogPath, int aLogLevel);
	static string RunBattle(string aBattleArgStr);
	static void clearLog();
	static ofstream sLogFile;

	static string CmdPbToJson(vector<TBattleViewCmd*> aCmdArr);

private:
	static lua_State* getLuaState();
private:
	static thread_local lua_State* sLuaState;
	static string sLuaPath;
	static string sConfPath;
	static string sLogPath;
	static int sLogLevel;
	
};