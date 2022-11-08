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

#include "BuffModReflectDamage.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModReflectDamage::StackAdded(int)
{
    //nothing
}

void BuffModReflectDamage::StackRemoved(int)
{
    //nothing
}

void BuffModReflectDamage::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::ReflectDamage);
}

void BuffModReflectDamage::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::ReflectDamage);
}

void BuffModReflectDamage::OnActive(Unit* aUtilizer, const Skill* aSkill, int64 aValue)
{
    if (!IsValid())
        return;
	if (aUtilizer->IsArmyShooter())
		return;
	if (mParams.mReflectType != ReflectType::PhysicalAndMagical
		&&( (mParams.mReflectType == ReflectType::Physical) != aSkill->IsPhysicalSkill()  ) )
	{
		return;
	}
    HitResult result;
	int64 damageValue = 0;
	if (mParams.mReflectValueType == ReflectValueType::FixValue)
	{
		damageValue = aValue * mParams.mPercent / DENOM + mParams.mAdd;
	}
	else
	{
		Unit* attrUnit = mParams.mAttrSource == BuffAttrSource::Owner ? GetBuff()->GetOwner().Get() : GetBuff()->GetSourceUtilizer().Get();
		damageValue = int64(GetUnitAttr(attrUnit, mParams.mAttrId)) * mParams.mPercentByAttr / DENOM;
	}
    result.mValue = GetBuff()->ScaledValue(damageValue);
    aUtilizer->Damage(result, GetOwner().Get(), nullptr, GetBuff());
    aUtilizer->DealingDamageByBuff(result.mValue);
}
