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

#include "BuffModDamageShare.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Buff/Buff.h"

void BuffModDamageShare::StackAdded(int)
{
    //nothing
}

void BuffModDamageShare::StackRemoved(int)
{
    //nothing
}

void BuffModDamageShare::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::DamageShare);
}

void BuffModDamageShare::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mUtilizer = nullptr;
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::DamageShare);
}

int64 BuffModDamageShare::OnActive(int64 aValue, vector<BuffMod*>& aMods, Unit* aUtilizer)
{
    if (!IsValid())
        return aValue;
	int64 modSize = aMods.size();
	if (modSize <= 0)
		return aValue;
    HitResult result;
    int64 sharedDmg = GetBuff()->ScaledValue(aValue * mParams.mPercent / DENOM);
	if (sharedDmg > aValue) 
		sharedDmg = aValue;
	int64 damage = aValue - sharedDmg;
    result.mValue = sharedDmg / modSize;
	int64 damageOther;
    for (auto& m : aMods)
    {
		damageOther = m->GetOwner()->Damage(result, mParams.mUtilizer.Get(), nullptr, GetBuff());
        mParams.mUtilizer->DealingDamageByBuff(damageOther);
    }
    return damage;
}