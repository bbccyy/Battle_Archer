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

#include "BuffModRageImmunity.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModRageImmunity::StackAdded(int)
{
    //nothing
}

void BuffModRageImmunity::StackRemoved(int)
{
    //nothing
}

void BuffModRageImmunity::OnEnable()
{
	switch (mParams.mType)
	{
	case 0:
		//only buff
		GetOwner()->IncStateAdjust(StateAdjust::RageImmunityBuffOnly);
		break;
	case 1:
		//only skill
		GetOwner()->IncStateAdjust(StateAdjust::RageImmunitySkillOnly);
		break;
	case 2:
		//all
		GetOwner()->IncStateAdjust(StateAdjust::RageImmunity);
		break;
	default:
		LOG_WARN("when OnEnable, found invalid type of BuffModRageImmunity %d", mParams.mType);
	}
}

void BuffModRageImmunity::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mType = 0;
		return;
	}

	switch (mParams.mType)
	{
	case 0:
		//only buff
		GetOwner()->DecStateAdjust(StateAdjust::RageImmunityBuffOnly);
		break;
	case 1:
		//only skill
		GetOwner()->DecStateAdjust(StateAdjust::RageImmunitySkillOnly);
		break;
	case 2:
		//all
		GetOwner()->DecStateAdjust(StateAdjust::RageImmunity);
		break;
	default:
		LOG_WARN("when OnDisable, found invalid type of BuffModRageImmunity %d", mParams.mType);
	}
}