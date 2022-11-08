/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wangyixun
* @date $Date$
* @version $Revision$
* @brief
*
**/

#include "BuffModFatalDmgShift.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"


void BuffModFatalDmgShift::StackAdded(int)
{
	//nothing
}

void BuffModFatalDmgShift::StackRemoved(int)
{
	//nothing
}

void BuffModFatalDmgShift::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::FatalDmgShift);
}

void BuffModFatalDmgShift::OnDisable(bool aShouldTrigger)
{
	mLastActiveTime = 0;
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mCD = 0;
		mParams.mCount = 0;
		mParams.mTargetType = 0;
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::FatalDmgShift);
}

int BuffModFatalDmgShift::GetTargetType()
{
	return mParams.mTargetType;
}

bool BuffModFatalDmgShift::IsInCD()
{
	if (mLastActiveTime == 0) return false;
	int curTime = GetOwner()->GetUnitTime();
	if (mLastActiveTime > curTime) return false;   //可能是上一屏的 
	if (curTime >= mLastActiveTime + mParams.mCD) return false;
	return true;  //其余情况认为在CD中 
}

int64 BuffModFatalDmgShift::OnActive(SharedPtr<Unit> aUnit, int64 aDmg)
{
	if (!IsValid())
		return 0;
	if (mParams.mCount <= 0)
		return 0;
	mParams.mCount--;
	int64 ret = aUnit->GetHp();
	if (ret <= aDmg)
	{
		ret = ret - 1;
	}
	else
	{
		ret = aDmg;
	}
	mLastActiveTime = GetOwner()->GetUnitTime();
	return ret;
}

bool BuffModFatalDmgShift::IsUsedUp()
{
	return mParams.mCount <= 0;
}