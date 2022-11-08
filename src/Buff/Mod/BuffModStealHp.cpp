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

#include "BuffModStealHp.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModStealHp::StackAdded(int)
{
    //nothing
}

void BuffModStealHp::StackRemoved(int)
{
    //nothing
}

void BuffModStealHp::OnEnable()
{
    //nothing
}

void BuffModStealHp::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mFilterList = nullptr;
		mParams.mType = StealLifeType::ByDamagePercent;
		mParams.mMoment = StealMoment::OnActive;
		mParams.mPercent = 0;
		mParams.mAdd = 0;
		return;
	}
	if (mParams.mMoment != StealMoment::OnDisable)
	{
		return;
	}

	int64 v = 0;
	switch (mParams.mType)
	{
	case StealLifeType::ByRecordDataPercent:
	{
		v = GetBuff()->GetRecordData();
	}
	break;
	case StealLifeType::ByDamagePercent:
	case StealLifeType::ByCurrentHpPercent:
	case StealLifeType::ByMaxHpPercent:
	break;
	default:
		LOG_FATAL("Unrecognized steal life type %d", mParams.mType);
		break;
	}
	if (v != 0)
	{
		v = GetBuff()->ScaledValue(v * mParams.mPercent / DENOM + mParams.mAdd);
		GetOwner()->HealByStealHp(v, nullptr, GetBuff());
	}
}

void BuffModStealHp::OnActive(Unit& aUnit, Unit& aTarget, int64 aDamage, int64 aHp, int64 aMaxHp, int64 aPercent)
{
	if (mParams.mMoment != StealMoment::OnActive)
	{
		return;
	}

    int64 v = 0;
    switch (mParams.mType)
    {
    case StealLifeType::ByCurrentHpPercent:
    {
        v = aHp;
    }
    break;
    case StealLifeType::ByDamagePercent:
    {
		if (Filter(aTarget)) v = aDamage;
    }
    break;
    case StealLifeType::ByMaxHpPercent:
    {
        v = aMaxHp;
    }
    break;
	case StealLifeType::ByRecordDataPercent:
	{
		v = GetBuff()->GetRecordData();
		GetBuff()->SetRecordData(0);
	}
	break;
    default:
        LOG_FATAL("Unrecognized steal life type %d", mParams.mType);
        break;
    }
	if (v != 0)
	{
		int64 tarHp = IncByRate(v, mParams.mPercent, DENOM);
		tarHp = GetBuff()->ScaledValue(tarHp + mParams.mAdd);
		//v = GetBuff()->ScaledValue(v * mParams.mPercent / DENOM + mParams.mAdd);
		tarHp = IncByRate(tarHp, aPercent, DENOM);
		//v = v * aPercent / DENOM;
		aUnit.HealByStealHp(tarHp, nullptr, GetBuff());
	}
}

bool BuffModStealHp::Filter(Unit& aTarget)
{
	if (!mParams.mFilterList)
	{
		return true;
	}
	return aTarget.HasBuffBySubTypes(*mParams.mFilterList.Get());
}