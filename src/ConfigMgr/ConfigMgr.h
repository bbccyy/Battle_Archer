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

#pragma once
#include <vector>
#include <map>

#include "Define.h"
#include "CsvTable.h"
#include "PbTable.h"
#include "Util.h"


using namespace std;

class ConfigMgr 
{
    struct ConfTypeInfo
    {
        const char* TypeIdName;
        string ConfName;
    };
public:    
	static string whiteList[];
	static int LoadConfig(vector<string> aCsvConfPathArr, vector<string> aPbConfPathArr)
	{
		return ConfigMgr::GetInstance()->loadConfig(aCsvConfPathArr, aPbConfPathArr);
	}

    template<typename T>
    static const T* GetConfById(uint32 aId)
    {
        return ConfigMgr::GetInstance()->getConfById<T>(aId);
    }

    template<typename T>
    static vector<const T*> GetConfByIndex(const string& aColumnName, const string& aColumnValue)
    {
        return ConfigMgr::GetInstance()->getConfByIndex<T>(aColumnName, aColumnValue);
    }

	template<typename T>
	static vector<const T*> GetAllConf()
	{
		return ConfigMgr::GetInstance()->getAllConf<T>();
	}

    template<typename T>
    static void RegisterConfigTypeName(const string& aConfName)
    {
        const type_info& info = typeid(T);
        ConfigMgr::GetInstance()->registerConfigTypeName(info.name(), aConfName);
    }

    static void RegisterConfigTypeName(const char* aTypeIdName, const string& aConfName)
    {
        ConfigMgr::GetInstance()->registerConfigTypeName(aTypeIdName, aConfName);
    }
    
//单例实现
public:
    static ConfigMgr* GetInstance()
    {
        static ConfigMgr instance;
        return &instance;
    }

	static void PrepareLoadEnv(string aPbDbPath, string aCsvDbPath = "");
	static vector<string> GetPartitionDbInfos(string aDbName);
private:
	static void AddPartitionDbInfo(string aPartitionDbName);
	static map<string, vector<string>> mPartitionDbInfo;
	static bool mInitedEnv;
	
	

protected:
    struct ObjectCreator
    {
        ObjectCreator()
        {
            ConfigMgr::GetInstance();
        }
    };
    static ObjectCreator gObjectCreator;

private:
	
	
	ConfigMgr(){};
    ~ConfigMgr()
    {
        ReleaseAllConfig();
    };
    void ReleaseAllConfig();

    int loadConfig(vector<string> aCsvConfPathArr, vector<string> aPbConfPathArr);
    void registerConfigTypeName(const char* aTypeIdName, const string& aConfName);
    const string* getConfigNameByTypeId(const char* aTypeIdName);

    template<typename T>
    const T* getConfById(uint32 aId)
    {
        const type_info& info = typeid(T);
        const string* clsName = getConfigNameByTypeId(info.name());
        if(clsName == nullptr)
        {
            LOG_FATAL("not found config:%s id:%d", info.name(), aId);
            throw "config";
        }

        LOG_DEBUG("getConfById:%s, id:%d", clsName->c_str(), aId);

        map<string, ConfigTable>::iterator iter = mTableMap.find(*clsName);
        if( iter == mTableMap.end() )
        {
            LOG_FATAL("not found config:%s id:%d", clsName->c_str(), aId);
            throw "config";
        }
        switch( iter->second.tableType )
        {
            case ETableTypeCsv:
                return (T*)(iter->second.csvTable->GetRow(aId));  
            case ETableTypePb:
                return (T*)(iter->second.pbTable->GetRow(aId));  
            default:
                LOG_FATAL("invalid config:%s id:%d", clsName->c_str(), aId);
                throw "config";//TODO: 是否用异常
        }
    }

	template<typename T>
	vector<const T*> getAllConf()
	{
		const type_info& info = typeid(T);
		const string* clsName = getConfigNameByTypeId(info.name());
		if (clsName == nullptr)
		{
			LOG_FATAL("not found config:%s", info.name());
			throw "config";
		}
		map<string, ConfigTable>::iterator iter = mTableMap.find(*clsName);
		if (iter == mTableMap.end())
		{
			LOG_FATAL("not found config:%s", clsName->c_str());
			throw "config";
		}
		switch (iter->second.tableType)
		{
		case ETableTypeCsv:
			return iter->second.csvTable->getAllConf<T>();
		case ETableTypePb:
			return iter->second.pbTable->getAllConf<T>();
		default:
			LOG_FATAL("invalid config:%s", clsName->c_str());
			throw "config"; 
		}
	}

    template<typename T>
    vector<const T*> getConfByIndex(const string& aColumnName, const string& aColumnValue)
    {
        const type_info& info = typeid(T);
        const string* clsName = getConfigNameByTypeId(info.name());
        if(clsName == nullptr)
        {
            LOG_FATAL("not found config:%s column %s:%s", info.name(), aColumnName.c_str(), aColumnValue.c_str());
            throw "config";
        }

        LOG_DEBUG("getConfByIndex:%s column %s:%s", clsName->c_str(), aColumnName.c_str(), aColumnValue.c_str());

        map<string, ConfigTable>::iterator iter = mTableMap.find(*clsName);
        if( iter == mTableMap.end() )
        {
            LOG_FATAL("not found config:%s column %s:%s", clsName->c_str(), aColumnName.c_str(), aColumnValue.c_str());
            throw "config";//TODO: 是否用异常
        }

        switch( iter->second.tableType )
        {
            case ETableTypeCsv:
                return iter->second.csvTable->getConfByIndex<T>(aColumnName, aColumnValue);  
            case ETableTypePb:
                return iter->second.pbTable->getConfByIndex<T>(aColumnName, aColumnValue);   
            default:
                LOG_FATAL("invalid config:%s column %s:%s", clsName->c_str(), aColumnName.c_str(), aColumnValue.c_str());
                throw "config";//TODO: 是否用异常
        }
    }

    

private:
    enum ETableType
    {
        ETableTypeCsv = 1,
        ETableTypePb = 2
    };
    struct ConfigTable
    {
        ETableType tableType;
        union 
        {
            CsvTable* csvTable;
            PbTable* pbTable;
        };
    };
    map<string, ConfigTable> mTableMap;
    vector<ConfTypeInfo> mConfTypeInfoArr;
};
