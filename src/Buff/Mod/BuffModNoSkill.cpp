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

#include "BuffModNoSkill.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNoSkill::StackAdded(int)
{
    //nothing
}

void BuffModNoSkill::StackRemoved(int)
{
    //nothing
}

void BuffModNoSkill::OnEnable()
{
	auto owner = GetOwner();
	switch (mParams.mType)
	{
	case 0:
		// no small skill and rage skill
		owner->IncStateAdjust(StateAdjust::NoSkill);
		owner->OtherSkillInterrupted();
		break;
	case 1:
		// no small skill
		owner->IncStateAdjust(StateAdjust::NoSmallSkill);
		owner->SmallSkillInterrupted();
		break;
	case 2:
		// no rage skill
		owner->IncStateAdjust(StateAdjust::NoRageSkill);
		owner->RageSkillInterrupted();
		break;
	default:
		LOG_WARN("unknown BuffModNoSkill type [%d]", mParams.mType);
		break;
	}

	if (!GetBuff()->HasLabelId())
		owner->SendScreenTextCmd(ScreenTextType::NoSkill);
}

void BuffModNoSkill::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
		return;
	switch (mParams.mType)
	{
	case 0:
		// no small skill and rage skill
		GetOwner()->DecStateAdjust(StateAdjust::NoSkill);
		break;
	case 1:
		// no small skill
		GetOwner()->DecStateAdjust(StateAdjust::NoSmallSkill);
		break;
	case 2:
		// no rage skill
		GetOwner()->DecStateAdjust(StateAdjust::NoRageSkill);
		break;
	default:
		break;
	}
}