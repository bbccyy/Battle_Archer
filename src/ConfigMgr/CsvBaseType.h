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
#include<string>
#include<vector>
#include <typeinfo>
using namespace std;

class CsvStructBase
{
public:
    virtual int InitFromCsvRow(const vector<string>& aColArr) = 0;
    virtual int64 GetId() const = 0;
	virtual int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr) = 0;
    virtual const char* GetTypeIdName() = 0;
    //virtual const vector<string>& GetFieldNameArr() = 0;
    //virtual const vector<string>& GetFieldTypeArr() = 0;

    virtual ~CsvStructBase(){};
};