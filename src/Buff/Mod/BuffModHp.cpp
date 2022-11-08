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

#include "BuffModHp.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "Skill/HitHandler/HitHandler.h"
#include "BattleInstance.h"

void BuffModHp::StackAdded(int)
{
    //nothing
}

void BuffModHp::StackRemoved(int)
{
    //nothing
}

void BuffModHp::OnEnable()
{
    if (mParams.mInterval > 0)
    {
        mTimer = SharedPool<Timer<BuffModHp> >::Get();
        mTimer->Execute(GetOwner()->GetBattleInstance().GetTimerMgr(), this, &BuffModHp::OnPhase, mParams.mInterval);
    }
    else
    {
        OnActive(0);
    }
}

void BuffModHp::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
	}
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mCount = 0;
		mTimer = nullptr;
		mParams.mUtilizer = nullptr;
		return;
	}
	mTimer = nullptr;
	mCount = 0;
	mParams.mUtilizer = nullptr;
}

void BuffModHp::ResetValues()
{
    BuffMod::ResetValues();
    mCount = mParams.mCount;
}

bool BuffModHp::OnPhase(Timer<BuffModHp>& aTimer)
{
    --mCount;
    OnActive(mParams.mCount - mCount - 1);
    aTimer.Reset(GetOwner()->GetBattleInstance().GetFrameTime() + mParams.mInterval);
    return mCount > 0;
}

void BuffModHp::OnActive(int aPhase)
{
	if (!IsValid() || !mParams.mUtilizer)
		return;
    HitResult result;
    switch (mParams.mType)
    {
    case BuffModHpOrRageType::ByCurrentValue:
    {
        //result.mValue = GetOwner()->GetHp() * (mParams.mPercent[aPhase] + mParams.mPhasePercent * aPhase) / DENOM
        //    + mParams.mAdded[aPhase] + mParams.mPhaseAdded * aPhase;
		result.mValue = IncByRate(GetOwner()->GetHp(), (mParams.mPercent[aPhase] + mParams.mPhasePercent * aPhase), DENOM);
		result.mValue += mParams.mAdded[aPhase] + mParams.mPhaseAdded * aPhase;
    }
    break;
    case BuffModHpOrRageType::ByMaxValue:
    { //当选择为按血量上限 或 按血量百分比时 mParams.mPercent和mAdded 仅存储一个数值 取第一位 
        //result.mValue = GetOwner()->GetMaxHp() * (mParams.mPercent[0] + mParams.mPhasePercent * aPhase) / DENOM
        //    + mParams.mAdded[0] + mParams.mPhaseAdded * aPhase;
		result.mValue = IncByRate(GetOwner()->GetMaxHp(), (mParams.mPercent[0] + mParams.mPhasePercent * aPhase), DENOM);
		result.mValue += mParams.mAdded[0] + mParams.mPhaseAdded * aPhase;
    }
    break;
    default:
        LOG_FATAL("Invalid modify hp type %d", static_cast<int>(mParams.mType));
        break;
    }
    result.mValue = GetBuff()->ScaledValue(result.mValue);
    if (result.mValue < 0)
    {
        result.mValue = -result.mValue;
        int64 damage = GetOwner()->Damage(result, mParams.mUtilizer.Get(), nullptr, GetBuff());
		if (!IsValid() || !mParams.mUtilizer)
			return;
        mParams.mUtilizer->DealingDamageByBuff(damage);
    }
    else
    {
        GetOwner()->Heal(result, GetOwner().Get(), nullptr, GetBuff());
    }
}