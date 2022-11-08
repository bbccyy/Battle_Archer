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

#include "BuffModHealCopy.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Buff/Buff.h"

void BuffModHealCopy::StackAdded(int)
{
    //nothing
}

void BuffModHealCopy::StackRemoved(int)
{
    //nothing
}

void BuffModHealCopy::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::HealCopy);
}

void BuffModHealCopy::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mUtilizer = nullptr;
		mParams.mPercent = 0;
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::HealCopy);
	mParams.mUtilizer = nullptr;
	mParams.mPercent = 0;
}

void BuffModHealCopy::OnActive(int aValue)
{
    if (!IsValid())
        return;
    HitResult result;
    result.mValue = GetBuff()->ScaledValue(aValue);
    GetOwner()->Heal(result, mParams.mUtilizer.Get(), nullptr, GetBuff());
}