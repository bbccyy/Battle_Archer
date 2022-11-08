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

#include "BuffModAbsorbDamage.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Buff/Buff.h"

void BuffModAbsorbDamage::OnEnable()
{
	auto owner = GetOwner();
    owner->IncStateAdjust(StateAdjust::AbsorbDamage);
	if (!GetBuff()->HasLabelId())
	{
		owner->SendScreenTextCmd(ScreenTextType::ShieldApply, mAbsorbCount);
	}
	owner->OnShieldEnabled();
}

void BuffModAbsorbDamage::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mAbsorbLimit = 0;
		mAbsorbCount = 0;
		mParams.mCount = 0;
		mParams.mAbsorbLimit = 0;
		mParams.mAbsorbHeal = false;
		mParams.mHealPercent = 0;
		mParams.mThreshold = 0;
		mParams.mType = ShieldType::Physical;
		return;
	}
		
    GetOwner()->DecStateAdjust(StateAdjust::AbsorbDamage);
	if (mAbsorbLimit > 0)
	{ //remove non-used(remaining) shield
		GetOwner()->SubShieldByType(mParams.mType, mAbsorbLimit, 0, 0);
	}
	if (mAbsorbCount > 0)
	{ //send sign to front, sync shield number for world boss 
		GetOwner()->SendScreenTextCmd(ScreenTextType::ShieldAbsorb, 0);
	}
	mAbsorbLimit = 0;
	mAbsorbCount = 0;
}

//do when receive more buffmod with the same type
void BuffModAbsorbDamage::StackAdded(int const aChange)
{
	int64 plus = mParams.mAbsorbLimit * aChange;
    mAbsorbLimit += plus;
	GetOwner()->AddShieldByType(mParams.mType, plus);
}

void BuffModAbsorbDamage::StackRemoved(int const aChange)
{
	int64 subtract = mParams.mAbsorbLimit * aChange;
    if (mAbsorbLimit < subtract)
    {
		subtract = mAbsorbLimit;
        mAbsorbLimit = 0;
    }
	else
	{
		mAbsorbLimit -= subtract;
	}
	GetOwner()->SubShieldByType(mParams.mType, subtract, 0, 0);
}

//do when init a new buffmod
void BuffModAbsorbDamage::ResetValues()
{
    BuffMod::ResetValues();
    mAbsorbLimit = mParams.mAbsorbLimit;
	mAbsorbCount = mParams.mCount;
	GetOwner()->AddShieldByType(mParams.mType, mAbsorbLimit);
}

void BuffModAbsorbDamage::AddValues(int64 aValue)
{
	if (!IsValid())
		return;
	mAbsorbLimit += aValue;
	GetOwner()->AddShieldByType(mParams.mType, mAbsorbLimit);
}

bool BuffModAbsorbDamage::IsCounterShield()
{
	return mParams.mType == ShieldType::UniversalCount;
}

int64 BuffModAbsorbDamage::OnActive(int64 aValue, bool aIsPhysical, int aSkillId, int aUtilizerId)
{
    if (!IsValid() || aValue == 0)
        return aValue;
	if (aIsPhysical && mParams.mType == ShieldType::Magical)
		return aValue;
	if (!aIsPhysical && mParams.mType == ShieldType::Physical)
		return aValue;
	if (mParams.mType == ShieldType::UniversalCount)
	{
		if (mAbsorbCount <= 0)
			return aValue;

		if (mParams.mThreshold > 0)
		{
			int64 threshold = IncByRate(GetOwner()->GetMaxHp(), mParams.mThreshold, DENOM);
			//int64 threshold = mParams.mThreshold * GetOwner()->GetMaxHp() / DENOM;
			if (aValue <= threshold)
			{
				return 0;
			}
		}

		mAbsorbCount--;
		if (!GetBuff()->HasLabelId())
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::ShieldAbsorb, mAbsorbCount);
		}
		return 0;
	}

	int64 absorbDelta = 0;
    if (mAbsorbLimit < aValue)
    {
        aValue = aValue - mAbsorbLimit;
        TryHeal(mAbsorbLimit);
		absorbDelta = mAbsorbLimit;
        mAbsorbLimit = 0;
    }
	else
	{
		mAbsorbLimit = mAbsorbLimit - aValue;
		TryHeal(aValue);
		if (!GetBuff()->HasLabelId())
		{
			GetOwner()->SendScreenTextCmd(ScreenTextType::ShieldAbsorb);
		}
		absorbDelta = aValue;
		aValue = 0;
	}
	GetOwner()->SubShieldByType(mParams.mType, absorbDelta, aSkillId, aUtilizerId);
    return aValue;
}

void BuffModAbsorbDamage::TryHeal(int64 aValue)
{
    if (mParams.mAbsorbHeal)
    {
        HitResult result;
        result.mValue = aValue;
        GetOwner()->Heal(result, GetOwner().Get(), nullptr, GetBuff());
    }
}



/*if (mParams.mType == ShieldType::Magical)
owner->SendScreenTextCmd(ScreenTextType::DamageImmunityMagical);
else if (mParams.mType == ShieldType::Physical)
owner->SendScreenTextCmd(ScreenTextType::DamageImmunityPhysical);
else
owner->SendScreenTextCmd(ScreenTextType::AbsorbDamage);*/