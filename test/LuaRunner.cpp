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
#include <sstream>
#include "LuaRunner.h"
#include "Log/Log.h"
#include "tool.h"
#include "net/BattleViewCmd.pb.h"
#ifdef _MSC_VER
#include <windows.h>
#else
#include <dlfcn.h>
#endif

thread_local lua_State* LuaRunner::sLuaState = nullptr;
string LuaRunner::sLuaPath;
string LuaRunner::sConfPath;
string LuaRunner::sLogPath;
ofstream LuaRunner::sLogFile;
int LuaRunner::sLogLevel;

#ifdef _MSC_VER
typedef int(__stdcall *luaopenFunc)(lua_State*);
#else
typedef int(*luaopenFunc)(lua_State*);
#endif

luaopenFunc luaopen_misc;
luaopenFunc luaopen_rng;
luaopenFunc luaopen_pb;
luaopenFunc luaopen_SQLite3;
luaopenFunc luaopen_xlua;

#ifdef _MSC_VER
#define LOAD_FUNC_FROM_DLL(f, lib) \
f = (luaopenFunc)GetProcAddress(lib, #f);\
if (!f)\
{\
	LOG_FATAL("not found %s", #f);\
	return;\
}
#else
#define LOAD_FUNC_FROM_DLL(f, lib) \
f = (luaopenFunc)dlsym(lib, #f);\
if (!f)\
{\
	LOG_FATAL("not found %s", #f);\
	return;\
}
#endif


void addCLib(lua_State* aL, luaopenFunc aOpenFunc, const char* aLibName)
{
	lua_getglobal(aL, "package");
	lua_getfield(aL, -1, "loaded");	
	aOpenFunc(aL);	
	lua_setfield(aL, -2, aLibName);	
}
int luaPrint(lua_State* aL)
{
	const char* msg = luaL_checkstring(aL, 1);
	LuaRunner::sLogFile << msg << std::endl;
	LuaRunner::sLogFile.flush();
	return 0;
}


void LuaRunner::Init(const char* aLuaPath, const char* aConfPath, const char* aLogPath, int aLogLevel)
{
	sLuaPath = aLuaPath;
	sConfPath = aConfPath;
	sLogLevel = aLogLevel;
	sLogPath = aLogPath;
	sLogFile.open(aLogPath, std::ios_base::out);

#ifdef _MSC_VER
	string nativePath = sLuaPath + "/native/native.dll";
	HINSTANCE nativeLib = LoadLibrary(nativePath.c_str());
	if (!nativeLib)
	{
		LOG_FATAL("load native.dll failed");
		return;
	}
	HINSTANCE xluaLib = LoadLibrary("xlua");
	if (!xluaLib)
	{
		LOG_FATAL("load xlua.dll failed");
		return;
	}
#else
	string nativePath = sLuaPath + "/native/libnative.so";
	void* nativeLib = dlopen(nativePath.c_str(), RTLD_LAZY);
    if (!nativeLib) 
	{
     	LOG_FATAL("load native.dll failed");
		return;
    }
	void* xluaLib = dlopen("libxlua.so", RTLD_LAZY);
	if (!xluaLib)
	{
		LOG_FATAL("load xlua.dll failed");
		return;
	}
#endif
	LOAD_FUNC_FROM_DLL(luaopen_misc, nativeLib)
	LOAD_FUNC_FROM_DLL(luaopen_rng, nativeLib)
	LOAD_FUNC_FROM_DLL(luaopen_pb, nativeLib)
	LOAD_FUNC_FROM_DLL(luaopen_SQLite3, nativeLib)
	LOAD_FUNC_FROM_DLL(luaopen_xlua, xluaLib)
}

void LuaRunner::clearLog()
{
	sLogFile.close();
	remove(sLogPath.c_str());
	sLogFile.open(sLogPath, std::ios_base::out);
}

string LuaRunner::RunBattle(string aBattleArgStr)
{
	lua_State* L = getLuaState();
	lua_getglobal(L, "RunBattle");
	lua_pushlstring(L, aBattleArgStr.c_str(), aBattleArgStr.size());	
	int ret = lua_pcall(L, 1, 2, 0);
	if (ret)
	{
		LOG_WARN("failed:%s", luaL_checkstring(L, -1));
		lua_pop(L, 1);
		return "";
	}
	size_t retLen;
	const char* pRet = luaL_checklstring(sLuaState, -1, &retLen);
	int suc = luaL_checkinteger(sLuaState, -2);	
	if (suc)
	{
		string str(pRet, retLen);
		return str;
	}
	LOG_WARN("call lua failed. %s", pRet);
	
	return "";
}


lua_State* LuaRunner::getLuaState()
{
	if (sLuaState)
	{
		return sLuaState;
	}
	sLuaState = luaL_newstate();
	luaL_openlibs(sLuaState);
	addCLib(sLuaState, luaopen_misc, "misc");
	addCLib(sLuaState, luaopen_rng, "rng");
	addCLib(sLuaState, luaopen_SQLite3, "SQLite3");
	addCLib(sLuaState, luaopen_pb, "pb");
	luaopen_xlua(sLuaState);

	lua_pushstring(sLuaState, sConfPath.c_str());
	lua_setglobal(sLuaState, "SQLITE_PATH");

	lua_pushinteger(sLuaState, sLogLevel);
	lua_setglobal(sLuaState, "LOG_LEVEL");

	lua_getglobal(sLuaState, "package");
	lua_getfield(sLuaState, -1, "path");
	std::string curPath = lua_tostring(sLuaState, -1);
	curPath.append(";");
	curPath.append(sLuaPath);
	curPath.append("/?.lua");
	curPath.append(";");
	curPath.append(sLuaPath);
	curPath.append("/env/?.lua");
	lua_pop(sLuaState, 1);
	lua_pushstring(sLuaState, curPath.c_str()); 
	lua_setfield(sLuaState, -2, "path");
	lua_pop(sLuaState, 1);
	lua_pushcfunction(sLuaState, luaPrint);
	lua_setglobal(sLuaState, "print");

	string initLuaPath = sLuaPath + "/env/init.lua";
	int ret = luaL_dofile(sLuaState, initLuaPath.c_str());
	if (ret != 0)
	{
		auto str = luaL_checkstring(sLuaState, -1);
		LOG_FATAL("init.lua failed:%s", str);
		lua_pop(sLuaState, 1);
	}
	return sLuaState;
}



string LuaRunner::CmdPbToJson(vector<TBattleViewCmd*> aCmdArr)
{

	lua_State* L = getLuaState();
	lua_getglobal(L, "ParserPbToJson");

	lua_createtable(L, aCmdArr.size(), 0);
	for (size_t i = 0; i < aCmdArr.size(); i++)
	{
		std::stringbuf sb;
		std::ostream os(&sb);
		aCmdArr[i]->SerializeToOstream(&os);
		string str = sb.str();
		lua_pushlstring(L, str.c_str(), str.size());		
		lua_rawseti(L, -2, i + 1);
	}

	int ret = lua_pcall(L, 1, 1, 0);
	if (ret)
	{
		LOG_WARN("failed:%s", luaL_checkstring(L, -1));
		lua_pop(L, 1);
		return "";
	}
	size_t retLen;
	const char* pRet = luaL_checklstring(sLuaState, -1, &retLen);
	string str(pRet, retLen);
	return  str;
}