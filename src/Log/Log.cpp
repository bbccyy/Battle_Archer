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
#include <stdio.h>  
#include <stdarg.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Log.h"
#ifdef _MSC_VER
//#include <windows.h>
#include <Winsock2.h>
#else
#include <sys/time.h>
#endif

#ifdef _MSC_VER
inline int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif



char THREAD_LOCAL Log::mBasicInfo[MAX_BASIC_INFO_LEN];
char THREAD_LOCAL Log::mBuff[BUFF_LEN];

Log* Log::sInstance = new LogPrint();

Log* Log::getInstance()
{
    return sInstance;
}


void Log::setLogInstance(Log* aLogPtr)
{
    if (sInstance)
    {
        delete sInstance;
    }
    sInstance = aLogPtr;
}

Log::Log():mLogLevel(ELogLevelDebug)
{
    mBasicInfo[0] = 0;
}

void Log::setLogLevel(int aLevel)
{
    mLogLevel = aLevel;
}

int Log::getLogLevel()
{
    return mLogLevel;
}

void Log::setBasicInfo(const char* aFmt, ...)
{
    va_list ap;
    va_start(ap, aFmt);
    vsnprintf(mBasicInfo,MAX_BASIC_INFO_LEN, aFmt, ap);
    va_end(ap);
}

void LogPrint::log(int aLevel, const char* aFileName, int aLineno, const char* aFmt, ...)
{
    if (mLogLevel > aLevel)
    {
        return;
    }
    int wrote = 0;
    std::string logLevelStr = getStrByLogLevel(aLevel);
    
    wrote += snprintf(mBuff, BUFF_LEN, "[%s][%s:%d]%s", logLevelStr.c_str(), aFileName, aLineno, mBasicInfo);
    va_list ap;
    va_start(ap, aFmt);
    wrote += vsnprintf(mBuff + wrote, BUFF_LEN - wrote, aFmt, ap);
    va_end(ap);
    mBuff[wrote] = '\n';

    if ( ELogLevelFatal == aLevel )
    {
        const int bufLen = 1024;
        char buf[bufLen];
        va_list ap;
        va_start(ap, aFmt);
        vsnprintf(buf, bufLen, aFmt, ap);
        va_end(ap);

        throw std::string(buf);
    }
}


LogToFile::LogToFile(const char* aFilePath)
{
    mFilePath = aFilePath;
    restart();
}

LogToFile::~LogToFile()
{

}

void LogToFile::restart()
{
    std::lock_guard<std::mutex> lck(mMutex);
    if (mFile.is_open())
    {
        mFile.close();
    }
    mFile.open(mFilePath, std::ios_base::app | std::ios_base::out);
    if (!mFile.good())
    {
        std::cerr << "open log file " << mFilePath.c_str() << " failed" << std::endl;
        exit(0);
    }

    std::string warnFilePath = mFilePath + ".wf";    
    if (mWFile.is_open())
    {
        mWFile.close();
    }
    mWFile.open(warnFilePath.c_str(), std::ios_base::app | std::ios_base::out);
    if (!mWFile.good())
    {
        std::cerr << "open log file " << warnFilePath.c_str() << " failed" << std::endl;
        exit(0);
    }
}

void LogToFile::flush()
{
    if (mFile.is_open())
    {
        mFile.flush();
    }
    if (mWFile.is_open())
    {
        mWFile.flush();
    }
}

void LogToFile::clear()
{
	{
		std::lock_guard<std::mutex> lck(mMutex);
		if (mFile.is_open())
		{
			mFile.close();
		}
		if (mWFile.is_open())
		{
			mWFile.close();
		}
		remove(mFilePath.c_str());
		std::string warnFilePath = mFilePath + ".wf";
		remove(warnFilePath.c_str());
	}	
	restart();
}

void LogToFile::log(int aLevel, const char* aFileName, int aLineno, const char* aFmt, ...)
{
    if (mLogLevel > aLevel)
    {
        return;
    }
	
    int wrote = 0;
    std::string logLevelStr = getStrByLogLevel(aLevel);
	
	struct timeval tv;
	time_t t = time(NULL);
	gettimeofday(&tv, NULL);	
	tm* localTime = localtime(&t);

    wrote += snprintf(mBuff, BUFF_LEN, "[%04d%02d%02d %02d:%02d:%02d %06d][%s][%s:%d]%s", 
		localTime->tm_year+1900, localTime->tm_mon+1, localTime->tm_mday,
		localTime->tm_hour, localTime->tm_min, localTime->tm_sec, tv.tv_usec,
		logLevelStr.c_str(), aFileName, aLineno, mBasicInfo);
    va_list ap;
    va_start(ap, aFmt);
    wrote += vsnprintf(mBuff + wrote, BUFF_LEN - wrote, aFmt, ap);
    va_end(ap);
	wrote = wrote >= (BUFF_LEN - 2) ? (BUFF_LEN - 2) : wrote;
    mBuff[wrote] = '\n';
    mBuff[wrote+1] = 0;

    std::lock_guard<std::mutex> lck(mMutex);
    mFile << mBuff;
	mFile.flush();
    if(aLevel <= ELogLevelInfo)
    {
        return;
    }
    mWFile << mBuff;
    mWFile.flush();
    if (ELogLevelFatal == aLevel)
    {
        mFile.flush();
        mWFile.flush();

        const int bufLen = 1024;
        char buf[bufLen];
        va_list ap;
        va_start(ap, aFmt);
        vsnprintf(buf, bufLen, aFmt, ap);
        va_end(ap);

        throw std::string(buf);
    }
}

