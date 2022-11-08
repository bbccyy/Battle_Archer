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

#include "BuffModChaos.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModChaos::StackAdded(int)
{
    //nothing
}

void BuffModChaos::StackRemoved(int)
{
    //nothing
}

void BuffModChaos::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::Chaos);
    GetOwner()->CurrentSkillInterrupted();
}

void BuffModChaos::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::Chaos);
}