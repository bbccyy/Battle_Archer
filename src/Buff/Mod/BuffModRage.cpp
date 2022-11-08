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

#include "BuffModRage.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "Skill/HitHandler/HitHandler.h"
#include "BattleInstance.h"

void BuffModRage::StackAdded(int)
{
    //nothing
}

void BuffModRage::StackRemoved(int)
{
    //nothing
}

void BuffModRage::OnEnable()
{
    if (mParams.mInterval > 0)
    {
        mTimer = SharedPool<Timer<BuffModRage> >::Get();
        mTimer->Execute(GetOwner()->GetBattleInstance().GetTimerMgr(), this, &BuffModRage::OnPhase, mParams.mInterval);
    }
    else
    {
        OnActive(0);
    }
}

void BuffModRage::OnDisable(bool aShouldTrigger)
{
	if (mTimer)  //the mTimer may very well be NULL if this ModRage has no Interval
	{
		mTimer->Cancel();
	}
	mTimer = nullptr;
	mCount = 0;
}

void BuffModRage::ResetValues()
{
    BuffMod::ResetValues();
    mCount = mParams.mCount;
}

bool BuffModRage::OnPhase(Timer<BuffModRage>& aTimer)
{
    --mCount;
    OnActive(mParams.mCount - mCount - 1);
    aTimer.Reset(GetOwner()->GetBattleInstance().GetFrameTime() + mParams.mInterval);
    return mCount > 0;
}

void BuffModRage::OnActive(int aPhase)
{
    int64 value = 0;
    switch (mParams.mType)
    {
    case BuffModHpOrRageType::ByCurrentValue:
    {
        value = GetOwner()->GetRage() * (mParams.mPercent[aPhase] + mParams.mPhasePercent * aPhase)
            + mParams.mAdded[aPhase] + mParams.mPhaseAdded * aPhase;
    }
    break;
    case BuffModHpOrRageType::ByMaxValue:
    {
        value = GetOwner()->GetMaxRage() * (mParams.mPercent[aPhase] + mParams.mPhasePercent * aPhase)
            + mParams.mAdded[aPhase] + mParams.mPhaseAdded * aPhase;
    }
    break;
    default:
        LOG_FATAL("Invalid modify hp type %d", static_cast<int>(mParams.mType));
        break;
    }
    value = GetBuff()->ScaledValue(value);
    if(value < 0)
        GetOwner()->SubRage(-value, ERageChangeCause::Buff);
    else
        GetOwner()->AddRage(value, ERageChangeCause::Buff);
}