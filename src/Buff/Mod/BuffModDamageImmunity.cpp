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


#include "BuffModDamageImmunity.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModDamageImmunity::StackAdded(int)
{
    //nothing
}

void BuffModDamageImmunity::StackRemoved(int)
{
    //nothing
}

void BuffModDamageImmunity::OnEnable()
{
	auto owner = GetOwner();
	switch (mParams.mImmunityType)
	{
	case BuffDamageImmunityType::All:
		owner->IncStateAdjust(StateAdjust::DamageImmunityAll);
		if (!GetBuff()->HasLabelId())
			owner->SendScreenTextCmd(ScreenTextType::DamageImmunityAll);
		break;
	case BuffDamageImmunityType::Physical:
		owner->IncStateAdjust(StateAdjust::DamageImmunityPhysical);
		if (!GetBuff()->HasLabelId())
			owner->SendScreenTextCmd(ScreenTextType::DamageImmunityPhysical);
		break;
	case BuffDamageImmunityType::Magic:
		owner->IncStateAdjust(StateAdjust::DamageImmunityMagic);
		if (!GetBuff()->HasLabelId())
			owner->SendScreenTextCmd(ScreenTextType::DamageImmunityMagical);
		break;
	case BuffDamageImmunityType::Percent:
		owner->IncStateAdjust(StateAdjust::DamageImmunityPercent);
		break;
	}
	
}

void BuffModDamageImmunity::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	switch (mParams.mImmunityType)
	{
	case BuffDamageImmunityType::All:
		GetOwner()->DecStateAdjust(StateAdjust::DamageImmunityAll);
		break;
	case BuffDamageImmunityType::Physical:
		GetOwner()->DecStateAdjust(StateAdjust::DamageImmunityPhysical);
		break;
	case BuffDamageImmunityType::Magic:
		GetOwner()->DecStateAdjust(StateAdjust::DamageImmunityMagic);
		break;
	case BuffDamageImmunityType::Percent:
		GetOwner()->DecStateAdjust(StateAdjust::DamageImmunityPercent);
		break;
	}
}