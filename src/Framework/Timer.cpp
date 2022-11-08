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
* @brief
*
**/

#include "Timer.h"

using std::vector;

TimerMgr::TimerMgr(int aCap):
	mTimerArr(vector<SharedPtr<ITimer> >(0)), 
	mTimerArrLoopOn(vector<SharedPtr<ITimer>>(0))
{
    mTimerArr.reserve(aCap);
	mTimerArrLoopOn.reserve(aCap);
    Reset();
}

void TimerMgr::Reset()
{
    mTimerArr.clear();
	mTimerArrLoopOn.clear();
}

void TimerMgr::Register(const SharedPtr<ITimer>& aTimer)
{
	Check();
    mTimerArr.push_back(aTimer);
}

void TimerMgr::Check()
{
	if (mInvalidCount * TIMER_CLEANUP_RATIO_DENOM < mTimerArr.size())
		return;
	//inactive ones will be swapped to last and poped
	int r = 0, k = 0;
	for (; r < mTimerArr.size(); ++r)
	{
		if (mTimerArr[r]->IsValid())
		{
			if (r != k)
			{
				mTimerArr[k] = mTimerArr[r];
			}
			++k;
		}
	}
	r = r - k;
	for (k = 0; k < r; ++k)
	{
		mTimerArr.pop_back();
	}
}

void TimerMgr::OnTick(int aTime)
{
    //try execute every timer & count invalid
	mInvalidCount = 0;
	Duplicate();
	int size = mTimerArr.size();
	for (int r = 0; r < size; ++r)
	{
		mInvalidCount += mTimerArrLoopOn[r]->TryExecute(aTime);
	}
	Cleanup();
}

void TimerMgr::Duplicate()
{
	if (mTimerArrLoopOn.size() < mTimerArr.size())
		mTimerArrLoopOn.resize(mTimerArr.size());
	for (int r = 0; r < mTimerArr.size(); ++r)
	{
		mTimerArrLoopOn[r] = mTimerArr[r];
	}
}

void TimerMgr::Cleanup()
{
	for (int r = 0; r < mTimerArrLoopOn.size(); ++r)
	{
		mTimerArrLoopOn[r] = nullptr;
	}
}

int TimerMgr::Size()
{
	return mTimerArr.size();
}