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
#include <mutex>

#ifdef MULTI_THREAD
#define THREAD_LOCAL thread_local
#else
#define THREAD_LOCAL
#endif

class Log
{   

public:
    enum ELogLevel
    {
        ELogLevelDebug,
        ELogLevelInfo,
        ELogLevelWarn,
        ELogLevelFatal,
        ELogLevelNone
    };

public:
    static Log* getInstance();
    static void setLogInstance(Log* aLogPtr);
    void setBasicInfo(const char* aFmt, ...);

    Log();
    virtual ~Log(){};
    virtual void log(int aLevel, const char* aFileName, int aLineno, const char* aFmt, ...) = 0;

    virtual void setLogLevel(int aLevel);
    virtual int getLogLevel();
    virtual void restart(){};
    virtual void flush(){};
	virtual void clear(){};

    inline std::string getStrByLogLevel(int aLevel)
    {
        switch (aLevel)
        {
            case ELogLevelDebug: return "DEBUG";
            case ELogLevelInfo: return "INFO";
            case ELogLevelWarn: return "WARNING";
            case ELogLevelFatal: return "FATAL";
        }

        return "INVALID_LOG_LEVEL";
    }

protected:
    enum 
    { 
        MAX_BASIC_INFO_LEN = 256,
        BUFF_LEN = 2048
    };

    static Log* sInstance;

    int mLogLevel;
    static char THREAD_LOCAL mBasicInfo[MAX_BASIC_INFO_LEN];
    static char THREAD_LOCAL mBuff[BUFF_LEN];
};


class LogPrint : public Log
{   

public:
    virtual void log(int aLevel, const char* aFileName, int aLineno, const char* aFmt, ...);
};


class LogToFile : public Log
{

public:
	LogToFile(const char* aFilePath);
    ~LogToFile();
	virtual void log(int aLevel, const char* aFileName, int aLineno, const char* aFmt, ...);
	void restart();
    void flush();
	void clear();
private:
    std::string mFilePath;
	std::ofstream mFile;
    std::ofstream mWFile;
    mutable std::mutex mMutex;
};



#define LOG_DEBUG(...) Log::getInstance()->log(Log::ELogLevelDebug, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) Log::getInstance()->log(Log::ELogLevelInfo, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) Log::getInstance()->log(Log::ELogLevelWarn, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) Log::getInstance()->log(Log::ELogLevelFatal, __FILE__, __LINE__, __VA_ARGS__)

#define LOG_ASSERT(a)  if( !(a) ) Log::getInstance()->log(Log::ELogLevelFatal, __FILE__, __LINE__, "assert failed")
#define CHECK_POSITIVE(v, a, e)  if( v < 0 ) \
							{\
								Log::getInstance()->log(Log::ELogLevelWarn, __FILE__, __LINE__, "check positive failed %d, %d", a, e); \
								v = 0; \
							}

