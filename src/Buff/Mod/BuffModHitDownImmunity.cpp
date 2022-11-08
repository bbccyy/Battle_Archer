/**********************************************************************************************************************
*
* Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author $Author$
* @date $Date$
* @version $Revision$
* @brief ÃâÒßÉËº¦
*
**/


#include "BuffModHitDownImmunity.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModHitDownImmunity::StackAdded(int)
{
    //nothing
}

void BuffModHitDownImmunity::StackRemoved(int)
{
    //nothing
}

void BuffModHitDownImmunity::OnEnable()
{
	auto owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::HitDownImmunity);
}

void BuffModHitDownImmunity::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::HitDownImmunity);
}