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

#include "BuffModDizziness.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModDizziness::StackAdded(int)
{
    //nothing
}

void BuffModDizziness::StackRemoved(int)
{
    //nothing
}

void BuffModDizziness::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::Dizziness);
    mControlState = ControlToken::Create(ControlledType::Dizziness, nullptr, GetBuff()->GetAnimName());
    GetOwner()->BeControlled(*mControlState);
	GetOwner()->OnDizzy();  //TODO: DELETE IT 
}

void BuffModDizziness::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mControlState = nullptr;
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::Dizziness);
    GetOwner()->ClearBeControlled(*mControlState);
	mControlState = nullptr;
}