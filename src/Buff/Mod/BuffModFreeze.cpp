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

#include "BuffModFreeze.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModFreeze::StackAdded(int)
{
    //nothing
}

void BuffModFreeze::StackRemoved(int)
{
    //nothing
}

void BuffModFreeze::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::Freeze);
    mControlState = ControlToken::Create(ControlledType::Freeze, nullptr, GetBuff()->GetAnimName());
    GetOwner()->BeControlled(*mControlState);
}

void BuffModFreeze::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		mControlState = nullptr;
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::Freeze);
    GetOwner()->ClearBeControlled(*mControlState);
	mControlState = nullptr;
}