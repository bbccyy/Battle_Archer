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

#include "BuffModAttackSpeed.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModAttackSpeed::StackAdded(int const aChange)
{
	auto percent = mParams.mPercent * aChange;
    GetOwner()->ModifyActionSpeed(percent);
	if (!GetBuff()->HasLabelId())
	{
		if (percent > 0)
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::SpeedUp);
		}
		else if (percent < 0)
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::SpeedDown);
		}
	}
}

void BuffModAttackSpeed::StackRemoved(int const aChange)
{
    GetOwner()->ModifyActionSpeed(-mParams.mPercent * aChange);
}

void BuffModAttackSpeed::OnEnable()
{
	GetOwner()->ModifyActionSpeed(mParams.mPercent);
	if (!GetBuff()->HasLabelId())
	{
		if (mParams.mPercent > 0)
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::SpeedUp);
		}
		else if (mParams.mPercent < 0)
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::SpeedDown);
		}
	}
}

void BuffModAttackSpeed::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->ModifyActionSpeed(-mParams.mPercent*GetBuff()->GetStack());
}