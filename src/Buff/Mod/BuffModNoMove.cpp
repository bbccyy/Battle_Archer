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

#include "BuffModNoMove.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNoMove::StackAdded(int)
{
    //nothing
}

void BuffModNoMove::StackRemoved(int)
{
    //nothing
}

void BuffModNoMove::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::NoMove);
}

void BuffModNoMove::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::NoMove);
}