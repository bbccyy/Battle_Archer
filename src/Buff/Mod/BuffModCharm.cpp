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

#include "BuffModCharm.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModCharm::StackAdded(int)
{
    //nothing
}

void BuffModCharm::StackRemoved(int)
{
    //nothing
}

void BuffModCharm::OnEnable()
{
	auto owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::Charmed);
	owner->CurrentSkillInterrupted();
	if (!GetBuff()->HasLabelId())
		owner->SendScreenTextCmd(ScreenTextType::Charmed);
}

void BuffModCharm::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
		return;
    GetOwner()->DecStateAdjust(StateAdjust::Charmed);
	GetOwner()->TDCharmEnd();
}