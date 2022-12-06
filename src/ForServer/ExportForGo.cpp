/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief
*
**/

#include <stdarg.h>
#include <thread>
#include "ExportForGo.h"
#include "Log/Log.h"
#include "ConfigMgr/ConfigMgr.h"
#include "BattleInstance.h"
#include "../test/tool.h"
#include "Framework/ThreadPool.h"
#include "net/Battle.pb.h"
#include "Framework/Util.h"
//need load the conf ver
#include "DBManager.h"
#include <stdio.h>
#include<sstream>
#include "stdio.h"


void getDbVer(string strDbPath, std::string &strDbVer);
void getCsvVer(const char* strCsvPath, std::string &strCsvVer);
string parseDesignConfVer(string aAppSettingPath);


using namespace std;
using pb::TBattleFieldInput;

ThreadPool gThreadPool;

string gBattleVer = "";
string gDesignConfVer = "";


void initLog(const char* aPath, int aLogLevel)
{
    LogToFile* log  = new LogToFile(aPath);
    log->setLogLevel(aLogLevel);
    Log::setLogInstance(log);
}

void restartLog()
{
    Log::getInstance()->restart();
}

int initBattle(const char * aCsvFromExecelPath, const char * aDbFromEditorPath, int aThreadNum)
{
	string dbFromEditor(aDbFromEditorPath);
	string csvFromExcel(aCsvFromExecelPath);
	vector<string> pbFiles = {
		dbFromEditor + "/AvatarData.db",
		dbFromEditor + "/BuffData.db",
		dbFromEditor + "/SceneConf3d.db",
		dbFromEditor + "/SkillData.db",
	};
	vector<string> csvFiles = {
		csvFromExcel + "/BattleConfig.csv",
		csvFromExcel + "/Hero.csv",
		csvFromExcel + "/HeroAttribute.csv",
		csvFromExcel + "/DestructiveObjects.csv",
		csvFromExcel + "/DestructiveObjectsEvent.csv",
		csvFromExcel + "/Troop.csv",
	};

    int ret = 0;
	try
	{
		ConfigMgr::PrepareLoadEnv(dbFromEditor);
		ret = ConfigMgr::LoadConfig(csvFiles, pbFiles);
        if (ret != 0)
        {
            return ret;
        }
        BattleInstance::LoadGlobalConfig();    
        gThreadPool.Start([] {
            //nothing            
		}, []{
            //nothing
        }, aThreadNum);

		//load the ver to register etcd
		string dbPath = dbFromEditor + "/SkillData.db";
		string strSkillDataVer;
		getDbVer(dbPath, strSkillDataVer);
		
		
		dbPath = dbFromEditor + "/BuffData.db";
		string strBuffDataVer;
		getDbVer(dbPath, strBuffDataVer);
		

		
		dbPath = dbFromEditor + "/AvatarData.db";
		string strAvatarDataVer;
		getDbVer(dbPath, strAvatarDataVer);

 		dbPath = dbFromEditor + "/SceneConf3d.db";
 		string strSceneConf3dVer;
 		getDbVer(dbPath, strSceneConf3dVer);


		dbPath = csvFromExcel + "/Hero.csv";
		string strHeroVer;
		getCsvVer(dbPath.c_str(), strHeroVer);
		

		dbPath = csvFromExcel + "/HeroAttribute.csv";
		string strHeroAttributeVer;
		getCsvVer(dbPath.c_str(), strHeroAttributeVer);
		

		
		dbPath = csvFromExcel + "/BattleConfig.csv";
		string strBattleConfigVer;
		getCsvVer(dbPath.c_str(), strBattleConfigVer);

		

		stringstream ss;
		ss << strSkillDataVer << "_" << strBuffDataVer << "_" << strAvatarDataVer<< "_"<< strSceneConf3dVer << "_" <<strHeroVer<<"_" << strHeroAttributeVer << "_" << strBattleConfigVer;
		//ss << strSkillDataVer << "_" << strBuffDataVer << "_" << strAvatarDataVer << "_" << strHeroVer << "_" << strHeroAttributeVer << "_" << strBattleConfigVer;
		
		gBattleVer = ss.str();
		LOG_WARN("skillData : %s", strSkillDataVer.c_str());
		LOG_WARN("buffData : %s", strBuffDataVer.c_str());
		LOG_WARN("avatarData : %s", strAvatarDataVer.c_str());
		LOG_WARN("sceneConf3D : %s", strSceneConf3dVer.c_str());
		LOG_WARN("hero : %s", strHeroVer.c_str());
		LOG_WARN("heroAttribute : %s", strHeroAttributeVer.c_str());
		LOG_WARN("battleConfig : %s", strBattleConfigVer.c_str());
		LOG_WARN("battleVer : %s", gBattleVer.c_str());
		
		parseDesignConfVer(dbFromEditor + "/../../misc/AppSetting.ini");

		return 0;
	}
	catch (const char* message)
	{
		LOG_WARN("loadBattleConfig faield:%s", message);
	}
    catch (const string message)
    {
        LOG_WARN("loadBattleConfig faield:%s", message.c_str());
    }
	catch (...)
	{
		LOG_WARN("loadBattleConfig faield:%s", "unknown error");
	}

	return -1;
}


void doBattle(const char *aBattleArgsPtr, int aBatleArgsLen, string& aResultStr, string& aErrMsg)
{
    try 
    {
		struct timeval startTime, endTime, deltTime;
		gettimeofday(&startTime, NULL);

        BattleInstance battle;
        int ret = battle.InitWithPbStr(aBattleArgsPtr, aBatleArgsLen);
        if(ret != 0)
        {
            aErrMsg = "init battle failed";
            return;
        }

		int userInputIdx = 0;
		int userInputSize = battle.GetUserInputSize();
		battle.mRecordMode = false;
		TBattleFieldInput curInput;
		if (userInputSize > 0)
			curInput = battle.GetUserInput(userInputIdx);
		
		while (battle.GetResultType() == EBattleResult::None)
        {
			while (userInputIdx < userInputSize &&
				battle.GetCurField() > curInput.fieldnum())
			{
				userInputIdx++;
				if (userInputIdx < userInputSize)
					curInput = battle.GetUserInput(userInputIdx);
			}
			while(userInputIdx < userInputSize && 
				battle.GetCurField() == curInput.fieldnum() && 
				battle.GetFrameTime() == curInput.frametime())
			{
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
			battle.OnTick();            
        }
        
		aResultStr = battle.ReportResult(); 
		gettimeofday(&endTime, NULL);
		timersub(&endTime, &startTime, &deltTime);
		double cost = deltTime.tv_sec + (1.0 * deltTime.tv_usec) / 1000000;
		LOG_INFO("run cost: %f s", cost);
    }
	catch (const char* message)
    {
        aErrMsg = message;
        LOG_WARN("battle failed:%s", message); 
    }
    catch (const string message)
    {
        aErrMsg = message;
        LOG_WARN("battle failed:%s", message.c_str());   
    }
    catch (std::runtime_error error)
    {
        LOG_WARN("battle faield:%s", error.what());
        aErrMsg = error.what();
    }    
    catch (...)
    {        
        LOG_WARN("battle faield:%s", "unknown error");
        aErrMsg = "unknown error";
    } 
}

char * runBattle(const char*aBattleArgsPtr, int aBatleArgsLen, const char* aToken, int aTokenLen, int* aRetCode, int* aRetLen)
{
    string resultStr;
    string errMsg;
    try 
    {
        char token[128];
        int copyLen = aTokenLen <= 127 ? aTokenLen : 127;
        strncpy(token, aToken, copyLen);//防止传非法指针崩溃
        auto ret = gThreadPool.Enqueue([aBattleArgsPtr, aBatleArgsLen, token, &resultStr, &errMsg] { 
                Log::getInstance()->setBasicInfo("[thread:%d][token:%s]", 
                            std::this_thread::get_id(), token);    
                doBattle(aBattleArgsPtr, aBatleArgsLen, resultStr, errMsg);
			}
        );    
        ret.get();
    }
    catch (std::runtime_error error)
    {
        errMsg= error.what();
    }    
    catch (...)
    {
        errMsg = "unknown error in threadPool";
    }    
    
    char * outChar;
    if ( errMsg.size() <= 0)
    {
        *aRetLen = resultStr.size();
        outChar = (char *) malloc(*aRetLen);
        resultStr.copy(outChar, *aRetLen, 0);
        *aRetCode = 0;
    } 
    else
    {
        *aRetLen = errMsg.size();
        outChar = (char *) malloc(*aRetLen);
        errMsg.copy(outChar, *aRetLen, 0);
        *aRetCode = -1;
    }    
    return outChar;
}

#ifdef BATTLE_SOCKET
std::mutex gThreadMutex;
vector<std::thread*> gThreadArr;
struct TRunnerParam
{
    UnixSocketServer* server;
    int logLevel;
    int threadIndex;
};
#endif

void stopBattle()
{
    #ifdef BATTLE_SOCKET
    std::lock_guard<std::mutex> lck(gThreadMutex);
    for( auto* thread : gThreadArr)
    {
        thread->join();
        delete thread;
    }
    gThreadArr.clear();    
    #endif

    gThreadPool.StopThreadPool();
    SharedPoolBase::ReleaseAllPool();
}

char * getVersionInfo()
{
	int len = strlen(VERSION);
	char * outChar = (char *)malloc(strlen(VERSION) + 1);
	strcpy(outChar, VERSION);
	return outChar;
}

char * getBattleCodeVersion()
{
    int len = strlen(BATTLE_CODE_VERSION);
    char * outChar = (char *) malloc(strlen(BATTLE_CODE_VERSION)+1);
    strcpy(outChar, BATTLE_CODE_VERSION);    
    return outChar;
}

char * getBattleVer() {
	char * outChar = (char *)malloc(gBattleVer.size() + 1);
	gBattleVer.copy(outChar, gBattleVer.size(), 0);
	outChar[gBattleVer.size()] = 0;
	return outChar;
}

char * getDesignConfVer() {
	char * outChar = (char *)malloc(gDesignConfVer.size() + 1);
	gDesignConfVer.copy(outChar, gDesignConfVer.size(), 0);
	outChar[gDesignConfVer.size()] = 0;
	return outChar;

}


size_t getCsvLinePos(string str) {
	size_t pos = 0;
	bool entry_str = false;
	enum csv_state {
		csv_nomal,
		csv_incontent,
		csv_lineend
	};
	csv_state s = csv_nomal;
	int length = str.size();
	for (pos = 0; pos < length; pos++) {
		char cur = str[pos];
		char next = ' ';
		if (pos < (length - 1)) {
			next = str[pos + 1];
		}
		if (s == csv_nomal && cur == '"')
		{
			s = csv_incontent;
			continue;
		}
		if (s == csv_incontent && cur == '"' && next != '"') {
			s = csv_nomal;
			continue;
}
		if (s == csv_incontent && cur == '"' && next == '"') {
			pos = pos + 1;
			continue;
		}
		if (s == csv_nomal && cur == '\n') {
			return pos;
		}
	}
	return -1;
}


void getDbVer(string strDbPath,std::string &strDbVer) {
	
	string dbDir = strDbPath.substr(0, strDbPath.rfind("/"));
	string dbName = strDbPath.substr(strDbPath.rfind("/") + 1, strDbPath.length() - (strDbPath.rfind("/") + 1));
	string tableName = dbName.substr(0, dbName.find("."));
	vector<string> partitionDbNames = ConfigMgr::GetPartitionDbInfos(dbName); 
	int MaxVer = 0;
	for (int idx = 0;idx < partitionDbNames.size();idx++)
	{
		string realDbPath = dbDir;
		realDbPath.append("/");
		realDbPath.append(partitionDbNames[idx]);
	
		QueryResult* queryRes;

		string sql = "SELECT babeltime FROM " + tableName;
		sql = sql + " WHERE Id='0'";
		int ret = DBManager::GetInstance()->Select(realDbPath.c_str(), sql.c_str(), &queryRes, false);
		if (ret != 0)
		{
			throw sprintf("select from %s failed", realDbPath.c_str());
			return;
		}
	
		int count = DBManager::GetInstance()->GetColumnCount(queryRes);
		DBManager::GetInstance()->Step(queryRes);
		int len;
		int type;
		const char * s = DBManager::GetInstance()->GetColumnString(queryRes, 0, len, type);
		string babelTime(s, len);
		size_t pos = babelTime.find(":") + 1;
		strDbVer = babelTime.substr(pos, babelTime.length() - pos);
		if (MaxVer < atoi(strDbVer.c_str()))
		{
			MaxVer = atoi(strDbVer.c_str());
		}
	}
	char szbuf[11];
	memset(szbuf, 0, sizeof(szbuf));
	//itoa(MaxVer, szbuf, 10);
	
	snprintf(szbuf, sizeof(szbuf), "%d", MaxVer);
	strDbVer = szbuf;
}


void getCsvVer(const char* strCsvPath, std::string &strCsvVer) {
	ifstream inf(strCsvPath);
	assert(inf);
	inf.seekg(0,ios::end);
	int64 filesize = inf.tellg();
	inf.seekg(0,ios::beg);
	char* csvFileBuf = new char[filesize+1];
	memset(csvFileBuf, 0, filesize + 1);
	inf.read(csvFileBuf, filesize);
	inf.close();
	string strCsv = string(csvFileBuf);
	delete[] csvFileBuf;
	for (int i = 0; i <= 3; i++) {
		int pos = getCsvLinePos(strCsv);
		if (pos == -1)
		{
			throw "csv file error";
		}
		pos = pos + 1;
		if (i == 3) {
			string verLine = strCsv.substr(0, pos);
			int verPos = verLine.rfind(',') + 1;
			strCsvVer = verLine.substr(verPos, verLine.length() - verPos - 2);
			break;
		}
		strCsv = strCsv.substr(pos, strCsv.length() - pos);
	}
}

string parseDesignConfVer(string aAppSettingPath) {
	ifstream inf(aAppSettingPath);
	assert(inf);

	inf.seekg(0, ios::end);
	int64 filesize = inf.tellg();
	inf.seekg(0, ios::beg);
	char* csvAppSettingBuf = new char[filesize + 1];
	memset(csvAppSettingBuf, 0, filesize + 1);
	inf.read(csvAppSettingBuf, filesize);
	inf.close();

	string strIni = string(csvAppSettingBuf);
	delete[] csvAppSettingBuf;
	enum INI_STATE {
		parse_find_field,
		parse_in_field,
	};
	struct IniParser {
		string curField;
		INI_STATE curParseState;
		string needFindField;
		string needFindKey;
	};
	
	IniParser* parser = new IniParser;
	parser->needFindField = "VersionConf";
	parser->needFindKey = "ConfVersion";
	parser->curParseState = parse_find_field;

	

	while (true)
	{
		if (strIni.find("\n") == strIni.npos) {
			LOG_FATAL("cat find the design conf ver in appsetting");
			break;
		}
		int pos = strIni.find("\n")+1;
		string strLine = strIni.substr(0, pos);
		
		// so here analyze the line
		if (parser->curParseState == parse_find_field) {
			if (strLine[0] == '[') {
				string field = strLine.substr(1, strLine.find(']')-1);
				if (parser->needFindField == field) {
					parser->curParseState = parse_in_field;
				}
			}
		}
		else if (parser->curParseState == parse_in_field) {
			if (strLine[0] == '[') {
				throw "not find the key";
			}
			else {
				int keypos = strLine.find('=');
				string key = strLine.substr(0, keypos);
				if (key == parser->needFindKey)
				{
					//oh ye finded the value
					gDesignConfVer = strLine.substr(keypos + 1, strLine.length() - (keypos + 2));
					break;
				}
			}
		}
		strIni = strIni.substr(pos, strIni.length() - pos);
	}

	delete parser;
	return gDesignConfVer;
}

//void getCurDesignConfVer()




#ifdef BATTLE_SOCKET

void battleRunnerFunc(TRunnerParam aParam)
{
    UnixSocket conn;
    auto ret = aParam.server->Accept(&conn);
    if( ret != ErrorNo::Ok)
    {
        LOG_FATAL("accept failed");
        return;
    }

    int threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());  
    LOG_INFO("thread:%d start server", threadId);
    int intRet;
    bool running = true;
    while(running)
    {
        BattleMsg* msg;
        LOG_DEBUG("wait req");
        intRet = conn.Recv(msg);
        if(intRet != 0)
        {				
            LOG_WARN("read msg failed. ret:%d", intRet);
            break;				
        }
        switch(msg->mMsgId)
        {
            case MsgId::BattleReq:					
                {
                    BattleMsgReq* reqMsg = (BattleMsgReq*)msg;      
                    BattleMsgRsp rspMsg;
                    Log::getInstance()->setBasicInfo("[thread:%d][token:%s]", threadId, reqMsg->mToken.c_str());
                    doBattle(reqMsg->mBattleArgs.c_str(), reqMsg->mBattleArgs.size(), rspMsg.mBattleResult, rspMsg.mErrMsg);       
                    conn.Send(&rspMsg);
                    LOG_DEBUG("send rsp");
                }                
                break;
            case MsgId::Quit:
                running = false;
                break;
        }		
        delete msg;
    }
    LOG_INFO("thread:%d quit", threadId);
    SharedPoolBase::ReleaseAllPool();
    delete aParam.server;  

    BattleMsgQuitConfirm quitConfirmMsg;
    conn.Send(&quitConfirmMsg);     
}

int startBattleThread(const char* aUnixSocketPath, int aLogLevel)
{
    UnixSocketServer* server = new UnixSocketServer();
    ErrorNo ret;
    ret = server->InitServer(aUnixSocketPath, 1);
    if( ret != ErrorNo::Ok )
    {
        return (int)ret;
    }
    LOG_INFO("start battle thread at:%s", aUnixSocketPath);
    std::lock_guard<std::mutex> lck(gThreadMutex);
    TRunnerParam param;
    param.server = server;
    param.logLevel = aLogLevel;
    param.threadIndex = gThreadArr.size();
    std::thread* threadPtr = new thread(battleRunnerFunc, param);  
    gThreadArr.push_back(threadPtr);
    return 0;  
}
#endif

