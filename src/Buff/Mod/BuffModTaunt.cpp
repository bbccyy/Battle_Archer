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

#include "BuffModTaunt.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModTaunt::StackAdded(int)
{
    //nothing
}

void BuffModTaunt::StackRemoved(int)
{
    //nothing
}

void BuffModTaunt::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::Taunted);
    GetOwner()->TauntedTarget(mParams.mBuffId);
    GetOwner()->CurrentSkillInterrupted();
	if (!GetBuff()->HasLabelId())
		GetOwner()->SendScreenTextCmd(ScreenTextType::Taunt);
	
}

void BuffModTaunt::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::Taunted);
    GetOwner()->ClearTauntedTarget();
}