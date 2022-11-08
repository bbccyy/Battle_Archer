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

#include "BuffModToughness.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModToughness::StackAdded(int)
{
    //nothing
}

void BuffModToughness::StackRemoved(int)
{
    //nothing
}

void BuffModToughness::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::Toughness);
}

void BuffModToughness::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::Toughness);
}


int64 BuffModToughness::OnActive(int64 aCurHp, int64 aMaxHp)
{
	if (aCurHp >= mParams.mInitHp)
	{
		return aCurHp;
	}
	if (mParams.mLockValue > 0)
	{
		return aCurHp < mParams.mLockValue ? mParams.mLockValue : aCurHp;
	}
	if (aCurHp * DENOM < mParams.mLockPercent * aMaxHp )
	{
		return aMaxHp * mParams.mLockPercent / DENOM;
	}
	return aCurHp;
}