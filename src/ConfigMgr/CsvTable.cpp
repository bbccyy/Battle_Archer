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

#include "CsvHelper.h"
#include "CsvTable.h"
#include "DBManager.h"
#include "Util.h"
#include "ConfigMgr.h"


CsvTable::~CsvTable()
{
    for(map<int32, CsvStructBase*>::iterator iter = mRowMap.begin(); iter != mRowMap.end(); iter++)
    {   
        delete iter->second;
    }
    mRowMap.clear();
}


int CsvTable::LoadFromDbFile(const char * aDbFile, const char* aTableName, bool aInApk)
{
	int len, type;
	const char* colName, *fieldStr;
	QueryResult* queryRes;
	string sql = "SELECT * FROM ";
	sql.append(aTableName);
	sql.append(" WHERE id = 0");
	int ret = DBManager::GetInstance()->Select(aDbFile, sql.c_str(), &queryRes, aInApk);
	if (ret != 0)
	{
		LOG_FATAL("select from %s failed sql:%s", aDbFile, sql.c_str());
		return ret;
	}

	int columnNum = DBManager::GetInstance()->GetColumnCount(queryRes);
	if (columnNum < 2)
	{
		LOG_FATAL("need atleast 2 column. got:%d, dbFile:%s", columnNum, aDbFile);
		return -1;
	}

	//分析csv结构信息  
	int babeltimeCol = -1;
	vector<string> arrCol, arrName, arrType, arrDefault;
	arrName.push_back("id");
	arrType.push_back("int");
	DBManager::GetInstance()->Step(queryRes);
	for (int i = 1; i < columnNum; i++)
	{
		colName = DBManager::GetInstance()->GetColumnName(queryRes, i);
		fieldStr = DBManager::GetInstance()->GetColumnString(queryRes, i, len, type);
		if (strcmp(colName, "babeltime") == 0)
		{
			babeltimeCol = i;
			vector<string> arrRow;
			splitStr(fieldStr, "/~", arrRow);
			if (arrRow.size() != 3)
			{
				LOG_FATAL("invalid csv db file:%s, need 3 row header", mName.c_str());
				return -1;
			}
			ReadCsvRow(arrRow[0].c_str(), arrRow[0].size(), arrName);
			ReadCsvRow(arrRow[1].c_str(), arrRow[1].size(), arrType);
			ReadCsvRow(arrRow[2].c_str(), arrRow[2].size(), arrDefault);
		}
		else
		{
			arrName.push_back(colName);
			arrType.push_back(fieldStr);
			RowIndexer rowIndexer;
			rowIndexer.columnName = colName;
			rowIndexer.columnName[0] = toupper(rowIndexer.columnName[0]);
			mRowIndexer.push_back(rowIndexer);
		}
	}
    //名字首字母大写
	for (int i = 0; i < arrName.size(); i++)
	{
		arrName[i][0] = toupper(arrName[i][0]);
	}

	CsvStructBase* tableStruct = ConfStructHelper::NewStruct(mName.c_str());
	if (tableStruct == NULL)
	{
		LOG_FATAL("invalid csv config name:%s", mName.c_str());
		return -1;
	}
	ret = tableStruct->InitFieldMap(arrName, arrType);
	if (ret != 0)
	{
		LOG_FATAL("InitFieldMap %s faield", aDbFile);
		return ret;
	}
	ConfigMgr::RegisterConfigTypeName(tableStruct->GetTypeIdName(), mName);
	delete tableStruct;
	tableStruct = NULL;

	DBManager::GetInstance()->Finalize(queryRes);
	sql = "SELECT * FROM ";
	sql.append(aTableName);
	ret = DBManager::GetInstance()->Select(aDbFile, sql.c_str(), &queryRes, aInApk);
	if (ret != 0)
	{
		LOG_FATAL("select from %s failed sql:%s", aDbFile, sql.c_str());
		return ret;
	}
	while (DBManager::GetInstance()->Step(queryRes))
	{
		fieldStr = DBManager::GetInstance()->GetColumnString(queryRes, 0, len, type);
		uint32 id = convertFromStr<uint32>(fieldStr, 0);
		DBManager::GetInstance()->FinalizeGetColumnString(fieldStr, type);
		if (id == 0)
		{
			continue;
		}
		arrCol.clear();
		arrCol.push_back(fieldStr);

		tableStruct = ConfStructHelper::NewStruct(mName.c_str());
		int index = 0;
		for (int i = 1; i < columnNum; i++)
		{
			fieldStr = DBManager::GetInstance()->GetColumnString(queryRes, i, len, type);
			string columnValue(fieldStr, fieldStr + len);
			if (i == babeltimeCol)
			{				 
				ReadCsvRow(fieldStr, len, arrCol);			
			}
			else
			{
				//处理索引字段 
				arrCol.push_back(fieldStr);
				DBManager::GetInstance()->FinalizeGetColumnString(fieldStr, type);
				map<string, vector<CsvStructBase*> >::iterator iter = mRowIndexer[index].indexer.find(columnValue);
				if (iter == mRowIndexer[index].indexer.end())
				{
					vector<CsvStructBase*> vec;
					vec.push_back(tableStruct);
					mRowIndexer[index].indexer.insert(map<string, vector<CsvStructBase*> >::value_type(columnValue, vec));
				}
				else
				{
					iter->second.push_back(tableStruct);
				}
			}			
		}
		ret = tableStruct->InitFromCsvRow(arrCol);
		if (ret != 0)
		{
			delete tableStruct;
			LOG_FATAL("InitFromCsvRow failed. ret:%d", ret);
			return ret;
		}
		mRowMap[id] = tableStruct;
	}
	DBManager::GetInstance()->Finalize(queryRes);

	return 0;
}


int CsvTable::LoadFromCsvFile( const char * aCsvFile )
{
    CsvStructBase* tableStruct =  ConfStructHelper::NewStruct(mName.c_str());
    if( tableStruct == NULL )
    {
        LOG_FATAL("invalid csv config name:%s", mName.c_str());
        return -1;
    }
    CsvReader csvReader;
    int ret = csvReader.StartReadFile(aCsvFile);
    if ( ret != 0 )
    {
        return ret;
    }
    vector<string> arrCol, arrName, arrType, arrDefault;
    csvReader.NextRow(arrName);//第一行：字段名
    csvReader.NextRow(arrType);//第二行：字段类型
    csvReader.NextRow(arrDefault);//第三行：字段默认值
    //名字首字母大写
    for(int i = 0; i < arrName.size(); i++)
    {
        arrName[i][0] = toupper(arrName[i][0]);
    }
	ret = tableStruct->InitFieldMap(arrName, arrType);
	if (ret != 0)
	{
		LOG_FATAL("InitFieldMap %s faield", aCsvFile);
		return ret;
	}
	ConfigMgr::RegisterConfigTypeName(tableStruct->GetTypeIdName(), mName);
    delete tableStruct;
    tableStruct = NULL;

    while(true)
    {
        arrCol.clear();
        int ret = csvReader.NextRow(arrCol);
        if (ret != 0)
        {
            LOG_FATAL("NextRow failed. ret:%d", ret);
            return ret;
        }
        if( arrCol.empty() )
        {
            break;
        }

        tableStruct =  ConfStructHelper::NewStruct(mName.c_str());
        ret = tableStruct->InitFromCsvRow(arrCol);
        if ( ret != 0)
        {
            delete tableStruct;
            LOG_FATAL("InitFromCsvRow failed. ret:%d", ret);
            return ret;
        }
        mRowMap[tableStruct->GetId()] = tableStruct;
        
    }

    return 0;
}
