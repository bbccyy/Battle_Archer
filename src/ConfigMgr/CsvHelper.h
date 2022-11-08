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


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Log/Log.h"
using namespace std;

string trim(const string& input);

class CsvReader
{
public:

    ~CsvReader()
    {
        if(mFile.is_open())
        {
            mFile.close();
        }
    }

    int StartReadFile(const char* aFilePath)
    {
        if(mFile.is_open())
        {
            mFile.close();
        }
        mFile.open(aFilePath);
        if(!mFile.good())
        {
            LOG_FATAL("read %s failed", aFilePath);
            return -1;
        }
        //处理bom头
        if( mFile.get() == 0xef && mFile.get() == 0xbb && mFile.get() == 0xbf )
        {
            LOG_DEBUG("ignore bom in %s", aFilePath);
        }
        else
        {
            mFile.seekg(0, std::ios::beg);
        }
        return 0;
    }
    

    int NextRow(vector<string>& aColumnArr)
    {
        bool inQuote = false;
        bool addLast = false;
        string str = "";
        if ( mFile.eof() )
        {
            return 0;
        }
        char cur;
        char nxt;
        do
        {
            cur = mFile.get();
            nxt = mFile.peek();
            if (cur == ',')
            {
                if (inQuote)
                {
                    str.push_back(cur);
                }
                else
                {
                    aColumnArr.push_back(trim(str));
                    str.clear();
                }
            }
            else if (cur == '"')
            {
                if (inQuote)
                {
                    if (nxt == '"')
                    {
                        str.push_back(cur);
                        cur = mFile.get(); //忽略一个"
                    }
                    else
                    {
                        inQuote = false;
                    }
                }
                else
                {
                    inQuote = true;
                }
            }
            else if (cur == '\n')
            {
                if (inQuote)
                {
                    str.push_back(cur);
                }
                else
                {
                    aColumnArr.push_back(trim(str));
                    addLast = true;
                    break;
                    str = "";
                }
            }
            else if (cur == '\r')
            {
                if (inQuote)
                {
                    str.push_back(cur);
                }
            }
            else
            {
                str.push_back(cur);
            }
        }while( !mFile.eof() );
        if( !addLast )
        {
            aColumnArr.push_back(trim(str));
        }
        
        return 0;
    }
private:
    ifstream mFile;
};


int findEnclosure(const string& aIn, char aLeft, char aRight, std::size_t& start, std::size_t& end);

template<typename TOutput, typename TInput>
TOutput convertFromStr(const TInput& aIn, TOutput aOut)
{
    istringstream ( aIn ) >> aOut;
    return aOut;
}


template<typename T>
vector<T> convertToVector(const string& aIn, T aDefault, char aSep = ',', char aLeft = '[', char aRight = ']' )
{
    vector<T> ret;
    ret.reserve(16);
    std::size_t start = 0, end = 0, nxt = 0;

    findEnclosure(aIn, aLeft, aRight, start, end);

    //空数组判断
    if (start >= end)
    {
        return ret;
    }

    while ((nxt = aIn.find(aSep, start)) != string::npos ) 
    {
        ret.push_back(convertFromStr<T>(aIn.substr(start, nxt - start), aDefault));
        start = nxt + 1;
    }

    ret.push_back(convertFromStr<T>(aIn.substr(start, end - start), aDefault));
    ret.shrink_to_fit();
    
    return ret;
}


template<typename T>
vector<vector<T> > convertToVector2(const string& aIn, T aDefault, char aSep = ',', char aLeft = '[', char aRight = ']')
{
    vector<vector<T> > ret;
    ret.reserve(16);
    std::size_t start = 0, end = 0, nxt = 0;

    findEnclosure(aIn, aLeft, aRight, start, end);

    //空数组判断
    if (start >= end)
    {
        return ret;
    }

    while ((nxt = aIn.find(aRight, start)) != string::npos ) 
    {
        ret.push_back(convertToVector<T>(aIn.substr(start, nxt - start + 1), aDefault, aSep, aLeft, aRight));
        nxt = aIn.find(aSep, nxt + 1); 
        if ( nxt != string::npos )
        {
            start = nxt + 1;
        }
        else
        {
            return ret;//如果右包围符']'后面没有找到分隔符',' 就结束了
        }
    }

    ret.push_back(convertToVector<T>(aIn.substr(start, end - start), aDefault, aSep, aLeft, aRight));
    ret.shrink_to_fit();
    return ret;
}



template<typename T>
string vectorToString(vector<T> a)
{
    stringstream ss;
    ss << '[';
    for( int i = 0; i < int(a.size()-1); i++)
    {
        ss << a[i] << ',';
    }
    if ( a.size() > 0 )
    {
        ss << a[a.size()-1];
    }

    ss << ']';
    return ss.str();
}

template<typename T>
string vector2ToString(vector<vector<T> > a)
{
    stringstream ss;
    ss << '[';
    for( int i = 0; i < int(a.size()-1); i++)
    {
        ss << vectorToString(a[i])<< ',';
    }
    if ( a.size() > 0 )
    {
        ss << vectorToString(a[a.size()-1]) ;
    }

    ss << ']';
    return ss.str();
}

template<typename T>
int compareVector( vector<T> a1, vector<T> a2  )
{
    if( a1.size() != a2.size() )
    {
        LOG_DEBUG("size not match a1:%d, a2:%d", a1.size(), a2.size() );
        return -1;
    }
    for( int i = 0; i < a1.size(); i++)
    {
        if ( a1[i] != a2[i] )
        {
            return -1;
        }
    }

    return 0;
}

template<typename T>
int compareVector2( vector<vector<T> > a1, vector<vector<T> > a2  )
{
    if( a1.size() != a2.size() )
    {
        LOG_DEBUG("size not match a1:%d, a2:%s", a1.size(), a2.size() );
        return -1;
    }
    for( int i = 0; i < a1.size(); i++)
    {
        if ( compareVector(a1, a2) != 0)
        {
            return -1;
        }
    }

    return 0;
}

int ReadCsvRow(const char*aRowStr, const int aRowSize, vector<string>& aColumnArr);