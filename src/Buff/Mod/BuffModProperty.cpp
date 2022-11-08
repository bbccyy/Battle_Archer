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

#include "BuffModProperty.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModProperty::ApplyStacked(bool aSendCmd)
{
	auto& owner = GetOwner();
	for (auto& entry : mParams.mEntries)
	{
		entry.mValue = GetBuff()->ScaledValue(owner->GetAttr(entry.mProperty) * entry.mPercent / DENOM + entry.mAdd);
		if (entry.mValue < 0 && owner->IsImmuePropertyDec(entry.mProperty))
		{
			//block dec value modification 
			entry.mValue = 0;
			//owner->SendScreenTextCmd(ScreenTextType::HitDownImmunity);
		}
	}
	owner->ModifyAttr(mParams.mEntries, aSendCmd, GetBuff()->GetId());
	int64 maxHp = owner->GetMaxHp();
	//mMaxHpChange = GetBuff()->ScaledValue(mParams.mMaxHpPercent * maxHp / DENOM + mParams.mMaxHpAdd);
	mMaxHpChange = GetBuff()->ScaledValue(IncByRate(maxHp, mParams.mMaxHpPercent, DENOM) + mParams.mMaxHpAdd);
	//mHpChange = GetBuff()->ScaledValue(mParams.mHpChangePercent * mMaxHpChange / DENOM);
	mHpChange = GetBuff()->ScaledValue(IncByRate(mMaxHpChange, mParams.mHpChangePercent, DENOM));
	mHpDiff = owner->ModifyMaxHp(mMaxHpChange, mHpChange, mHpDiff, aSendCmd);
}

void BuffModProperty::RevertValue()
{
	GetOwner()->RevertAttr(mParams.mEntries);
	mHpDiff = GetOwner()->ModifyMaxHp(-mMaxHpChange, 0, mHpDiff, false);
}

void BuffModProperty::OnEnable()
{
	ApplyStacked(true);
}

void BuffModProperty::StackAdded(int)
{
	RevertValue();
	ApplyStacked(true);
}

void BuffModProperty::StackRemoved(int)
{
	RevertValue();
	ApplyStacked(false);
}

void BuffModProperty::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mMaxHpChange = 0;
		mHpChange = 0;
		mHpDiff = 0;
		mParams.mEntries.clear();
		mParams.mMaxHpPercent = 0;
		mParams.mMaxHpAdd = 0;
		mParams.mHpChangePercent = 0;
		return;
	}
	RevertValue();
	mMaxHpChange = 0;
	mHpChange = 0;
	mHpDiff = 0;
	mParams.mEntries.clear();
}