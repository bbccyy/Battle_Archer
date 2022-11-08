/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief
*
**/

#include "BuffModNonHostileTargettable.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNonHostileTargettable::StackAdded(int)
{
    //nothing
}

void BuffModNonHostileTargettable::StackRemoved(int)
{
    //nothing
}

void BuffModNonHostileTargettable::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::NonHostileRefTarget);
    GetOwner()->IncStateAdjust(StateAdjust::NonHostileEffTarget);
}

void BuffModNonHostileTargettable::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::NonHostileRefTarget);
    GetOwner()->DecStateAdjust(StateAdjust::NonHostileEffTarget);
}