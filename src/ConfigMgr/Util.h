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

#include <string>
#include <vector>
using namespace std;

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

struct handle {
    char* p;
    handle(char* ptr) : p(ptr) { }
    ~handle() { std::free(p); }
};

inline string demangle(const char* name) 
{
    int status = -4; // some arbitrary value to eliminate the compiler warning
    handle result( abi::__cxa_demangle(name, NULL, NULL, &status) );
    return (status==0) ? result.p : name ;
}

#else

// does nothing if not g++
inline string demangle(const char* name) 
{
    if( strncmp(name, "class ", 6) == 0 )
    {
        return name+6;
    }
    return name;
}

#endif

string bin2hex(const char* aBuf, int aLen);

void splitStr(const std::string& aStr, const std::string& aDelim, std::vector<std::string>& aResult);