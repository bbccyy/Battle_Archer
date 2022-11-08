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
 * @brief  测试代码
 *
 **/
#pragma once

#include "CsvHelper.h"
#include "ConfigMgr.h"


using namespace pb;

#define CHECK_VECTOR( a1, t, ... )  \
{ \
    t arr[] = { __VA_ARGS__ };\
    vector<t> va2(arr, arr+sizeof(arr)/sizeof(t)); \
    if( compareVector(a1, va2) != 0 ) \
    {\
        LOG_DEBUG("not match a1:%s, a2:%s", vectorToString(a1).c_str(), vectorToString(va2).c_str() ); \
        return -1; \
    }\
}

#define CHECK_VECTOR2( a1, a2 )  \
if( compareVector2(a1, a2) != 0 ) \
{\
    LOG_DEBUG("not match a1:%s, a2:%s", vector2ToString(a1).c_str(), vector2ToString(a2).c_str() ); \
    return -1; \
}


int testConvert()
{
 
    vector<int>arr1 = convertToVector<int>("[]", 0);
    if( !arr1.empty() )
    {
        LOG_DEBUG("expect empty");
        return -1;
    }
    arr1 = convertToVector<int>("[1]", 0);
    CHECK_VECTOR(arr1, int, 1 )

    arr1 = convertToVector<int>("[1,2]", 0);
    CHECK_VECTOR(arr1, int, 1, 2 )

    arr1 = convertToVector<int>("[1,2,]", 0);
    CHECK_VECTOR(arr1, int, 1,2,0 );

    arr1 = convertToVector<int>("[1,2,,4,]", 0);
    CHECK_VECTOR(arr1, int, 1,2,0,4,0 );
  
    arr1 = convertToVector<int>(" [  1,  2,  ,4  ,]", 0);
    CHECK_VECTOR(arr1, int, 1,2,0,4,0 );

    arr1 = convertToVector<int>(" [  1,  2,  ,4  ,]", 100);
    CHECK_VECTOR(arr1, int, 1,2,100,4,100 );

    vector<vector<int> >arr2 = convertToVector2<int>("[[11.2,12,13],[22,23],[31,32,33,34]]", 0);
    int expectArr[][4] = {{11,12,13},{22,23},{31,32,33,34}};
    vector<vector<int> > expectVector;
    expectVector.push_back( vector<int>(expectArr[0], expectArr[0]+3) );
    expectVector.push_back( vector<int>(expectArr[1], expectArr[1]+2) );
    expectVector.push_back( vector<int>(expectArr[2], expectArr[2]+4) );
    CHECK_VECTOR2(arr2, expectVector);

    arr2 = convertToVector2<int>(" [ [11.2,12 , 13],[22,23],[31,32,33,34]  ]", 0);
    CHECK_VECTOR2(arr2, expectVector);

    vector<vector<float> > arr2f = convertToVector2<float>(" [ [11.2,12 , 13],[22,23],[31,32,33,34]  ]", 0);
    float expectArrf[][4] = {{11.2,12,13},{22,23},{31,32,33,34}};
    vector<vector<float> > expectVectorf;
    expectVectorf.push_back( vector<float>(expectArrf[0], expectArrf[0]+3) );
    expectVectorf.push_back( vector<float>(expectArrf[1], expectArrf[1]+2) );
    expectVectorf.push_back( vector<float>(expectArrf[2], expectArrf[2]+4) );
    CHECK_VECTOR2(arr2f, expectVectorf);
    
    return 0;
}

int testReadCsv(const char* aPath)
{
    CsvReader csvReader;
    csvReader.StartReadFile(aPath);

    vector<string> arrCol;
    while(true)
    {
        arrCol.clear();
        int ret = csvReader.NextRow(arrCol);
        if (ret != 0)
        {
            LOG_FATAL("NextRow. ret:%d", ret);
            return ret;
        }
        if( arrCol.empty() )
        {
            break;
        }
    }
    return 0;
}

int testLoadConfig(vector<string> aCsvConfPathArr, vector<string> aPbConfPathArr)
{
    int ret = ConfigMgr::LoadConfig(aCsvConfPathArr, aPbConfPathArr);
    if (ret != 0)
    {
        LOG_FATAL("load config failed. ret:%d", ret);
        return ret;
    }

    const ConfigHero* hero = ConfigMgr::GetConfById<ConfigHero>(10001);
    if( hero->GetId() != 10001)
    {
        LOG_FATAL("invalid data");
        return -1;
    }

    const BuffData* buff = ConfigMgr::GetConfById<BuffData>(10001);
    if( buff->id() != 10001  )
    {
        LOG_FATAL("invalid data");
        return -1;
    }

    //vector<const AvatarData*> avatar = ConfigMgr::GetConfByIndex<AvatarData>("Avatarname", "Avatar_BOSS_01" );


    return 0;
}