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

#include "BuffModDamageCopy.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Buff/Buff.h"

void BuffModDamageCopy::StackAdded(int)
{
    //nothing
}

void BuffModDamageCopy::StackRemoved(int)
{
    //nothing
}

void BuffModDamageCopy::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::DamageCopy);
	mParams.mSourceUtilizerId = GetSourceUtilizer()->GetEntityId();
	if (mParams.mIgnoreSelf)
	{
		if (GetOwner()->GetEntityId() != mParams.mSourceUtilizerId)
		{
			mParams.mIgnoreSelf = false;
		}
	}
}

void BuffModDamageCopy::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mUtilizer = nullptr;
		mParams.mPercent = 0;
		mParams.mIgnoreSelf = false;
		mParams.mSourceUtilizerId = 0;
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::DamageCopy);
}

void BuffModDamageCopy::OnActive(int64 aValue, int aUtilizerId)
{
    if (!IsValid())
        return;
	if (mParams.mIgnoreSelf && mParams.mSourceUtilizerId == aUtilizerId)
		return;
    HitResult result;
    result.mValue = GetBuff()->ScaledValue(aValue);
	result.mValue = result.mValue * mParams.mPercent / DENOM;
    int64 damage = GetOwner()->Damage(result, mParams.mUtilizer.Get(), nullptr, GetBuff());
    mParams.mUtilizer->DealingDamageByBuff(damage);
}

int BuffModDamageCopy::GetSourceUtilizerId()
{
	return mParams.mSourceUtilizerId;
}