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

#include "BuffModNoNormalSkill.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNoNormalSkill::StackAdded(int)
{
    //nothing
}

void BuffModNoNormalSkill::StackRemoved(int)
{
    //nothing
}

void BuffModNoNormalSkill::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::NoNormalSkill);
    GetOwner()->NormalSkillInterrupted();
}

void BuffModNoNormalSkill::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::NoNormalSkill);
}