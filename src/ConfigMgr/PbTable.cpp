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
#include "PbTable.h"
#include "DBManager.h"
#include "Util.h"
#include "ConfigMgr.h"


PbTable::~PbTable()
{
    for(map<int32, google::protobuf::Message*>::iterator iter = mRowMap.begin(); iter != mRowMap.end(); iter++)
    {   
        delete iter->second;
    }
    mRowMap.clear();
}



int PbTable::LoadFromDbFile( const char * aDbFile, bool aInApk)
{
    QueryResult* queryRes;
    string sql = "SELECT * FROM ";
    sql.append( mName );

	string dbFile = aDbFile;
	string dbFilePath = dbFile.substr(0, dbFile.rfind("/"));
	string dbFileName = dbFile.substr(dbFile.rfind("/") + 1, dbFile.length() - (dbFile.rfind("/") + 1));

	vector<string> dbFileNames =  ConfigMgr::GetPartitionDbInfos(dbFileName);
	for (int idx=0;idx<dbFileNames.size();idx++)
	{
		string realQueryDb = dbFilePath;
		realQueryDb.append("/");
		realQueryDb.append(dbFileNames[idx]);
		
		int ret = DBManager::GetInstance()->Select(realQueryDb.c_str(), sql.c_str(), &queryRes, aInApk);
		if ( ret != 0 )
		{
			LOG_FATAL("select from %s failed", realQueryDb.c_str());
			return ret;
		}

		int columnNum = DBManager::GetInstance()->GetColumnCount(queryRes);
		if ( columnNum < 2 )
		{
			LOG_FATAL("need atleast 2 column. got:%d, dbFile:%s", columnNum, realQueryDb.c_str());
			return -1;
		}
		for( int i = 1; i < columnNum-1; i++)
		{
			if (mRowIndexer.size() == 0)// only the first add index use
			{
				RowIndexer rowIndexer;
				rowIndexer.columnName = DBManager::GetInstance()->GetColumnName(queryRes, i);
				rowIndexer.columnName[0] = toupper(rowIndexer.columnName[0]);
				mRowIndexer.push_back(rowIndexer);
			}
		}
    
		if( strcmp(mName.c_str(), "SkillData") == 0)
		{
			ConfigMgr::RegisterConfigTypeName<pb::SkillData>(mName);
		}
		else if( strcmp(mName.c_str(), "BuffData") == 0)
		{
			ConfigMgr::RegisterConfigTypeName<pb::BuffData>(mName);
		}
		else if( strcmp(mName.c_str(), "AvatarData") == 0)
		{
			ConfigMgr::RegisterConfigTypeName<pb::AvatarData>(mName);
		}
		else if( strcmp(mName.c_str(), "SceneConf3d") == 0)
		{
			ConfigMgr::RegisterConfigTypeName<pb::SceneConf3d>(mName);
		}
		else if (strcmp(mName.c_str(), "SceneConfArcher") == 0)
		{
			ConfigMgr::RegisterConfigTypeName<pb::SceneConfArcher>(mName);
		}
		else
		{
			LOG_FATAL("not found pb msg for %s", mName.c_str());
			return -1;
		}
    
		while (DBManager::GetInstance()->Step(queryRes))
		{
			int len;
			int type;
			const char* fieldStr = DBManager::GetInstance()->GetColumnString(queryRes, 0, len, type);
			uint32 id = convertFromStr<uint32>(fieldStr, 0);
			DBManager::GetInstance()->FinalizeGetColumnString(fieldStr, type);
			if ( id == 0 )
			{
				continue;
			}
			//默认最后一列是babeltime，需要解码
			fieldStr = DBManager::GetInstance()->GetColumnString(queryRes, columnNum-1, len, type);
			google::protobuf::Message* pbMsg = NULL;
			if( strcmp(mName.c_str(), "SkillData") == 0)
			{
				pbMsg = new pb::SkillData();
			}
			else if( strcmp(mName.c_str(), "BuffData") == 0)
			{
				pbMsg = new pb::BuffData();
			}
			else if( strcmp(mName.c_str(), "AvatarData") == 0)
			{
				pbMsg = new pb::AvatarData();
			}
			else if( strcmp(mName.c_str(), "SceneConf3d") == 0)
			{
				pbMsg = new pb::SceneConf3d();
			}
			else if (strcmp(mName.c_str(), "SceneConfArcher") == 0)
			{
				pbMsg = new pb::SceneConfArcher();
			}
			else
			{
				LOG_FATAL("not found pb msg for %s", mName.c_str());
				return -1;
			}

			//LOG_DEBUG("config:%s id:%d, data:%s", mName.c_str(), id, bin2hex(fieldStr, len).c_str());
			if( pbMsg->ParsePartialFromArray(fieldStr, len) == false)
			{
				delete pbMsg;
				DBManager::GetInstance()->FinalizeGetColumnString(fieldStr, type);
				LOG_FATAL("parse %s failed. id:%d", mName.c_str(), id);
				return -1;
			}
			DBManager::GetInstance()->FinalizeGetColumnString(fieldStr, type);
			mRowMap[id] = pbMsg;

			//处理索引字段
			for( int i = 1; i < columnNum-1; i++)
			{
				fieldStr = DBManager::GetInstance()->GetColumnString(queryRes, i, len, type);
				string columnValue(fieldStr, fieldStr+len);
				DBManager::GetInstance()->FinalizeGetColumnString(fieldStr, type);
				map<string, vector<google::protobuf::Message*> >::iterator iter = mRowIndexer[i-1].indexer.find(columnValue);
				if(iter ==  mRowIndexer[i-1].indexer.end())
				{
					vector<google::protobuf::Message*> vec;
					vec.push_back(pbMsg);
					mRowIndexer[i-1].indexer.insert( map<string,vector<google::protobuf::Message*> >::value_type(columnValue, vec) );
				}
				else
				{
					iter->second.push_back(pbMsg);
				}
			}
		}
		DBManager::GetInstance()->Finalize(queryRes);
	}
    return 0;
}
