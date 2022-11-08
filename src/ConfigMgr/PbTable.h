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
#include "Log/Log.h"
#include "Pb/module/BuffData.pb.h"
#include "Pb/module/SkillData.pb.h"
#include "Pb/module/BuffData.pb.h"
#include "Pb/module/AvatarData.pb.h"
#include "Pb/module/SceneConf3d.pb.h"

using namespace std;




class PbTable
{
public:
    PbTable(const char * aName)
    {
        mName = aName;
    }
    ~PbTable();

    int LoadFromDbFile( const char * aDbFile, bool aInApk);

    inline google::protobuf::Message* GetRow(uint32 aId)
    {
        map<int32, google::protobuf::Message*>::iterator iter = mRowMap.find(aId);
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
        for( size_t i = 0; i < mRowIndexer.size(); i++ )
        {
            if (mRowIndexer[i].columnName.compare(aColumnName) == 0 )
            {
                map<string, vector<google::protobuf::Message*> >::iterator iter = mRowIndexer[i].indexer.find(aColumnValue);
                if ( iter == mRowIndexer[i].indexer.end() )
                {
                    LOG_FATAL("not found column %s:%s in config:%s", aColumnName.c_str(), aColumnValue.c_str(), mName.c_str());
                    throw "config";
                }
                vector<const T*> vec;
                vec.reserve(iter->second.size());
                for(size_t j = 0; j < iter->second.size(); j++)
                {
                    vec.push_back( (const T*)(iter->second[i]) );
                }
                return vec;
            }
        }
        LOG_FATAL("not found column:%s indexer in config:%s columnValue:%s", aColumnName.c_str(), mName.c_str(), aColumnValue.c_str());
        throw "config";
    }

	template<typename T>
	inline vector<const T*> getAllConf()
	{
		vector<const T*> vec;
		vec.reserve(mRowMap.size());
		for (auto& pair : mRowMap)
		{
			vec.push_back((const T*)(pair.second));
		}
		return vec;
	}

private:
    struct RowIndexer
    {
        string columnName;
        map<string, vector<google::protobuf::Message*> > indexer; //目前看只需要支持string类型的索引
    };

    string mName;
    map<int32, google::protobuf::Message*>  mRowMap;
    vector<RowIndexer>  mRowIndexer;  
};

