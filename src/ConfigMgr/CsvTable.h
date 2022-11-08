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
#include <map>
#include "Define.h"
#include "CsvBaseType.h"
#include "CsvType_auto.h"

using namespace std;




class CsvTable
{
public:
    CsvTable(const char * aName)
    {
        mName = aName;
    }
    ~CsvTable();
    int LoadFromCsvFile( const char * aCsvFile );
	int LoadFromDbFile(const char * aDbFile, const char* aTableName, bool aInApk);

    inline CsvStructBase* GetRow(uint32 aId)
    {
        map<int32, CsvStructBase*>::iterator iter = mRowMap.find(aId);
        if ( iter == mRowMap.end() )
        {
            LOG_FATAL("not found id:%d in config:%s", aId, mName.c_str());
            throw "config";
        }
        return iter->second;
    }

    template<typename T>
    inline vector<const T*> getConfByIndex(const string& aColumnName, const string& aColumnValue)
    {
        LOG_FATAL("not support getConfByIndex. config:%s column %s:%s", mName.c_str(), aColumnName.c_str(), aColumnValue.c_str());
        throw "config";
    }

	template<typename T>
	inline vector<const T*> getAllConf()
	{
		LOG_FATAL("not support getAllConf:%s", mName.c_str());
		throw "config";
	}

private:

	struct RowIndexer
	{
		string columnName;
		map<string, vector<CsvStructBase*> > indexer;
	};

    string mName;
    map<int32, CsvStructBase*>  mRowMap;
	vector<RowIndexer>  mRowIndexer;
};

