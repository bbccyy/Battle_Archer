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

#include "BuffModDie.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"

void BuffModDie::StackAdded(int)
{
    //nothing
}

void BuffModDie::StackRemoved(int)
{
    //nothing
}

void BuffModDie::OnEnable()
{
    //nothing
}

void BuffModDie::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    if (aShouldTrigger && !GetOwner()->IsDead())
    {
		DieCause dieCause(EUnitDieCause::Buff);
		dieCause.data = GetBuff()->GetId();
        GetOwner()->Die(dieCause);
    }
}