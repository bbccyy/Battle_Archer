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

#include "BuffModSetMaxLoseHP.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Buff/Buff.h"

void BuffModSetMaxLoseHP::OnEnable()
{
	auto owner = GetOwner();
    owner->IncStateAdjust(StateAdjust::SetMaxLoseHP);
	//mUndertakeLimit = owner->GetHp() * mParams.mPercent / DENOM;
	mUndertakeLimit = IncByRate(owner->GetHp(), mParams.mPercent, DENOM);
}

void BuffModSetMaxLoseHP::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mUndertakeLimit = 0;
		mUndertaked = 0;
		mParams.mPercent = 0;
		return;
	}	
    GetOwner()->DecStateAdjust(StateAdjust::SetMaxLoseHP);
	mUndertakeLimit = 0;
	mUndertaked = 0;
	mParams.mPercent = 0;
}

//do when receive more buffmod with the same type
void BuffModSetMaxLoseHP::StackAdded(int const aChange)
{
	//do nothing 
}

void BuffModSetMaxLoseHP::StackRemoved(int const aChange)
{
	//do nothing 
}

//do when init a new buffmod
void BuffModSetMaxLoseHP::ResetValues()
{
    BuffMod::ResetValues();
	mUndertakeLimit = 0;
	mUndertaked = 0;
}

int64 BuffModSetMaxLoseHP::OnActive(int64 aValue, bool aIsPhysical)
{
    if (!IsValid() || aValue == 0)
        return aValue;

	if (mUndertakeLimit <= mUndertaked)
	{
		if (!GetBuff()->HasLabelId())
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::ShieldAbsorb);
		}
		return 0;
	}
	int64 rest = mUndertakeLimit - mUndertaked;
	mUndertaked = mUndertaked + aValue;
	
	if (rest <= aValue)
	{
		return rest;
	}
	
    return aValue;
}


