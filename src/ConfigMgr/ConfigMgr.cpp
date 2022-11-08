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
#include <iostream>  
#include <string>  

#include "ConfigMgr.h"
#include "Log/Log.h"
#include "CsvHelper.h"
#include "DBManager.h"

#if defined(__linux) || defined(__linux__) || defined(linux)
#define LINUX_CPP
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#else
#include <io.h>
#endif



ConfigMgr::ObjectCreator ConfigMgr::gObjectCreator;

map<string, vector<string>> ConfigMgr::mPartitionDbInfo ;
bool	ConfigMgr::mInitedEnv = false;

string ConfigMgr::whiteList[] = { "Attribute", "BattleConfig", "Hero", "HeroAttribute", "DestructiveObjects", "DestructiveObjectsEvent", "Troop" };


#ifdef LINUX_CPP
void ConfigMgr::PrepareLoadEnv(string aPbDbPath, string aCsvPbPath)
{
	if (mInitedEnv == true)
	{
		return;
	}
	struct stat s;
	lstat(aPbDbPath.c_str(), &s);
	if (!S_ISDIR(s.st_mode))
	{
		LOG_WARN("prepare load env scan pb dir %s error ", aPbDbPath.c_str());
		return;
	}
	struct dirent * filename;
	DIR * dir;
	dir = opendir(aPbDbPath.c_str());
	if (NULL == dir)
	{
		LOG_WARN("prepare load env scan pb open dir %s error ", aPbDbPath.c_str());
		return;
	}
	while ((filename = readdir(dir)) != NULL)
	{
		if (strcmp(filename->d_name, ".") == 0 ||
			strcmp(filename->d_name, "..") == 0)
			continue;
		string dbName = filename->d_name;
		if (dbName.find("_") != string::npos)
		{
			AddPartitionDbInfo(dbName);
		}
	}
	mInitedEnv = true;
}
#else
void ConfigMgr::PrepareLoadEnv(string aPbDbPath, string aCsvPbPath )
{
	if (mInitedEnv == true)
	{
		return;
	}
	intptr_t handle;
	_finddata_t findData;
	string dbPath = aPbDbPath;
	dbPath.append("/*.*");
	handle = _findfirst(dbPath.c_str(),&findData);
	if (handle == -1)
	{
		LOG_WARN("prepare load env scan pb dir %s error ", aPbDbPath.c_str());
		return;
	}
	do 
	{
		if (findData.attrib & _A_ARCH
			&& strcmp(findData.name,".") != 0
			&& strcmp(findData.name, "..") != 0
			)
		{
			string dbName = findData.name;
			if (dbName.find("_")!= string::npos)
			{
				AddPartitionDbInfo(dbName);
			}
		}
	} while (_findnext(handle,&findData) == 0);
	_findclose(handle);
	mInitedEnv = true;
}
#endif
vector<string> ConfigMgr::GetPartitionDbInfos(string aDbName)
{
	vector<string> partitionInfo;
	string confName = aDbName.substr(0, aDbName.find("."));
	map<string, vector<string>>::iterator iter = mPartitionDbInfo.find(confName);
	if (iter != mPartitionDbInfo.end())
	{
		for (int i=0; i < iter->second.size();i++)
		{
			partitionInfo.emplace_back(iter->second[i]);
		}
	}
	else {
		partitionInfo.emplace_back(aDbName);
	}
	
	return partitionInfo;
}

string GetFileNameFromPath(string aPath)
{
	//AdventureMap_d3ccddf9dfee7c82eed723adf92df5fd9972da3d.db
	size_t startIndex = aPath.find_last_of("/\\");
	startIndex = startIndex == string::npos ? 0 : startIndex +1;

	size_t lastUnderlineIndex = aPath.find_last_of('_');
	size_t lastDotIndex = aPath.find_last_of('.');
	lastUnderlineIndex = lastUnderlineIndex > startIndex ? lastUnderlineIndex : string::npos;
	lastDotIndex = lastDotIndex > startIndex ? lastDotIndex : string::npos;

	size_t endPos = std::min(lastUnderlineIndex, lastDotIndex);
	size_t len = endPos == string::npos ? string::npos : (endPos-startIndex);
	return aPath.substr(startIndex, len);
}

void ConfigMgr::registerConfigTypeName(const char* aTypeIdName, const string& aConfName)
{
	const string* confName = getConfigNameByTypeId(aTypeIdName);
	if( confName != nullptr )
	{
		LOG_WARN("typeId:%s already register as %s ", aTypeIdName, (*confName).c_str());
		return;
	}
	ConfTypeInfo info;
	info.TypeIdName = aTypeIdName;
	info.ConfName = aConfName;
	mConfTypeInfoArr.push_back(info);
	LOG_DEBUG("registerConfigTypeName %s %s", aTypeIdName, aConfName.c_str());
}

const string* ConfigMgr::getConfigNameByTypeId(const char* aTypeIdName)
{
	for(int i = 0; i < mConfTypeInfoArr.size(); i++)
	{
		if(mConfTypeInfoArr[i].TypeIdName == aTypeIdName)
		{
			return &mConfTypeInfoArr[i].ConfName;
		}
	}
	return nullptr;
}


bool checkIsInApk(string& aPath)
{
	if (aPath.rfind("_inapk") == (aPath.length() - 6))
	{
		aPath.resize(aPath.length() - 6);
		return true;
	}
	return false;
}

int ConfigMgr::loadConfig(vector<string> aCsvConfPathArr, vector<string> aPbConfPathArr)
{
	bool inApk = false;
	for (size_t i = 0; i < aCsvConfPathArr.size(); i++)
	{
		string filePath = aCsvConfPathArr[i];
		LOG_DEBUG("load csv %s", filePath.c_str());
		//inApk = checkIsInApk(filePath);

		string configName = GetFileNameFromPath(filePath);
		string configStructName = "Config" + configName;

		CsvTable* csvTable = new CsvTable(configStructName.c_str());
		int ret = csvTable->LoadFromCsvFile(filePath.c_str());
		if (ret != 0)
		{
			LOG_FATAL("load %s failed", filePath.c_str());
			return ret;
		}
		ConfigTable configTable;
		configTable.tableType = ETableTypeCsv;
		configTable.csvTable = csvTable;
		mTableMap[configStructName] = configTable;

	}
	for (size_t i = 0; i < aPbConfPathArr.size(); i++)
	{
		string filePath = aPbConfPathArr[i];
		LOG_DEBUG("load pb %s", filePath.c_str());
		inApk = checkIsInApk(filePath);

		string configName = GetFileNameFromPath(filePath);

		PbTable* pbTable = new PbTable(configName.c_str());
		int ret = pbTable->LoadFromDbFile(filePath.c_str(), inApk);
		if (ret != 0)
		{
			LOG_FATAL("load %s failed", filePath.c_str());
			return ret;
		}
		ConfigTable configTable;
		configTable.tableType = ETableTypePb;
		configTable.pbTable = pbTable;
		mTableMap[configName] = configTable;
    }
    int ret = DBManager::GetInstance()->CloseAllDBPtr();
	if (ret != 0)
	{
		LOG_WARN("Close all db failed");
	}
	
    return 0;
}



void ConfigMgr::AddPartitionDbInfo(string aPartitionDbName)
{
	string ConfName = aPartitionDbName.substr(0, aPartitionDbName.find("_"));
	map<string, vector<string>>::iterator iter = mPartitionDbInfo.find(ConfName);
	if (iter != mPartitionDbInfo.end())
	{
		iter->second.emplace_back(aPartitionDbName);
	}
	else {
		mPartitionDbInfo[ConfName].emplace_back(aPartitionDbName);
	}
}

void ConfigMgr::ReleaseAllConfig()
{
	for(auto iter = mTableMap.begin(); iter != mTableMap.end(); iter++ )
	{
		switch( iter->second.tableType )
        {
            case ETableTypeCsv:
                delete iter->second.csvTable;
				break;
            case ETableTypePb:
                delete iter->second.pbTable;
				break;
        }
	}
	
	mTableMap.clear();
}