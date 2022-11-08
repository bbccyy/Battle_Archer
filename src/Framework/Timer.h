/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author liyingbo
* @date $Date$
* @version $Revision$
* @brief Timer与TImer管理器
*
**/

#pragma once
#include <vector>
#include "SharedPool.h"
#include "Define.h"

using std::vector;

// Timer interface, for storage
struct ITimer
{
public:
	inline bool IsValid() const
	{
		return mInvalidMark == 0;
	}
    //returns: true=keep this timer, false=stop & remove this timer
    virtual int TryExecute(int const aTime) = 0;
protected:
	int mInvalidMark;
};

class TimerMgr
{
public:
    TimerMgr() = delete;
    TimerMgr(int aCap);
    TimerMgr(const TimerMgr&) = delete;
    //TimerMgr& operator=(TimerMgr& aRef) = delete;
    ~TimerMgr() = default;
    void Reset();
	void Check();
    void Register(const SharedPtr<ITimer>& aTimer);
    void OnTick(int aTime);
    void Duplicate();
    void Cleanup();
    int Size();
private:
    vector<SharedPtr<ITimer>> mTimerArr;
    vector<SharedPtr<ITimer>> mTimerArrLoopOn;
	int mInvalidCount = 0;
};

// Timer template
template<typename R>
class Timer : public ITimer, public EnableSharedFromThis<Timer<R> >, public IPoolable 
{
    using F = bool(R::*)(Timer<R>&);
public:
    Timer(){mInvalidMark = 1;};
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer& aRef) = delete;
    ~Timer() = default;

    void Execute(TimerMgr* const aMgr, R* const aOwner, F aFunc, int const aTime = 0)
    {
		LOG_ASSERT(aOwner);
        mOwner = aOwner;
		mInvalidMark = 0;
        mFunc = aFunc;
        mExecuteTime = aTime;
        aMgr->Register( this->SharedFromThis() );
		//为了满足SkillExecutor中的需求：先注册好，后面可以通过Reset(F aFunc, int const aTime)修改被执行的函数 TODO 讨论有没有更好的实现方式
		if (aTime == 0)
		{
			TryExecute(0);
		}
    }

    void Cancel()
    {
		mOwner = nullptr;
		mExecuteTime = BATTLE_TIME_UPPER_LIMIT;//assume the time value never approaches its limit
		mInvalidMark = 1;
    }

    //SharedPool需要的 
    void Reset() noexcept
    {
        mOwner = nullptr;
		mInvalidMark = 0;
    }

    void Reset(int const aTime)
    {
        LOG_ASSERT(mInvalidMark==0);
        mExecuteTime = aTime;
    }

    void Reset(F aFunc, int const aTime)
    {
        LOG_ASSERT(mInvalidMark==0);
        mFunc = aFunc;
        mExecuteTime = aTime;
    }

    void Offset(int const aTimeDiff)
    {
        LOG_ASSERT(mInvalidMark==0);
        mExecuteTime += aTimeDiff;
    }

    //returns: 0=timer valid, 1=timer invalid, other values are undefined
    int TryExecute(int const aTime)
    {
		auto holder = this->SharedFromThis(); //拉住this，防止调用栈深层触发Reset和PutToPool操作 
		//mExecuteTime must be kept to BATTLE_TIME_UPPER_LIMIT when mInvalidMark == 1 
        if (aTime >= mExecuteTime)
        {
            // member function pointer call
            if (((*mOwner).*mFunc)(*this))
            {
                
            }
            else
            {
				Cancel();
            }
        }
        return mInvalidMark;
    }
private:
    R* mOwner;
    F mFunc;
    int mExecuteTime;
};
