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
  
#include "BuffModLimitByMaxHpRate.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"

void BuffModLimitByMaxHpRate::StackAdded(int)
{
	//nothing
}

void BuffModLimitByMaxHpRate::StackRemoved(int)
{
	//nothing
}

void BuffModLimitByMaxHpRate::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::LimitByMaxHpRate);
}

void BuffModLimitByMaxHpRate::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mRate = 0;
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::LimitByMaxHpRate);
}

int64 BuffModLimitByMaxHpRate::OnActive(int64 aDmg)
{
	if (!IsValid())
		return aDmg;
	
	int64 maxHp = GetOwner()->GetMaxHp();
	int64 mCurLimit = IncByRate(maxHp, mParams.mRate, DENOM);

	if (aDmg > mCurLimit)
		return mCurLimit;

	return aDmg;
}
