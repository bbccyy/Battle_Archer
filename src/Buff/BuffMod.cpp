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

#include "BuffMod.h"
#include "Buff.h"
#include "Entity/Unit.h"
#include "View/BattleViewOutput.h"
#include "BattleInstance.h"

void BuffMod::Init(BuffSubType aModType, Buff& aBuff, int aDelay)
{
    mStatus = EBuffModStatus::Init;
    auto& unit = aBuff.GetOwner();
	mBuffModTimer = SharedPool<Timer<BuffMod> >::Get();
	mBuff = &aBuff;
	mModType = aModType;
	if (aDelay <= 0) 
	{
		//Enable(*mBuffModTimer);
		mBuffModTimer->Execute(unit->GetTimerMgr(), this, &BuffMod::Enable);
	}
	else
	{
		//unit->GetBattleInstance().GetTimerMgr() switch to unit's TimeMgr
		mBuffModTimer->Execute(unit->GetTimerMgr(), this, &BuffMod::Enable, aDelay + unit->GetUnitTime()); 
	}
}

void BuffMod::Reset()
{
	if (mBuffModTimer)
	{
		mBuffModTimer->Cancel();
		mBuffModTimer.Release();
	}
	if (mBuff)
		Disable(false);
	mId = 0;
	mModType = BuffSubType::Heal;
	mCommonParams = nullptr;
	mBuff = nullptr;
	mStatus = EBuffModStatus::Init;
}

void BuffMod::OnReset()
{
	//may be implemented by child
}

//此处aTime参数可以不用，直接使用unit的时间即可。但是为了和上面的SharedPool需要的Reset函数区分一下。暂时保留。
//等上面的Reset名字修改后，可以把这里也修改掉.   
void BuffMod::Reset(int aTime)
{
    if(mStatus == EBuffModStatus::Init)
    {
        mBuffModTimer->Reset(aTime + mCommonParams->mDelay);
    } 
	if (mStatus == EBuffModStatus::Enable)
	{
		OnReset();
	}
}

void BuffMod::ResetValues()
{
	mStatus = EBuffModStatus::Enable;
}

void BuffMod::Offset(int aTime)
{
	if(mBuffModTimer->IsValid())
		mBuffModTimer->Offset(aTime);
}

void BuffMod::SetCommonParams(CommonParams* aParams)
{
    mCommonParams = aParams;
}

bool BuffMod::IsOfType(BuffSubType aType) const
{
    return aType == mModType;
}

bool BuffMod::Enable(Timer<BuffMod>&)
{
	if (mStatus != EBuffModStatus::Init)
		return false;  //this mod has been canceled already
    ResetValues();
    OnEnable();
    if (mCommonParams->mEndWhenDamaged)
    {
        mBuff->GetMgr()->EndOnDamage(static_cast<BuffMod*>(this));
    }
	auto labelId = mBuff->GetLabelId();
	if (labelId > 0)
	{
		GetOwner()->SendScreenTextCmd(static_cast<ScreenTextType>(labelId));
	}
    auto& unit = GetOwner();
	auto& utilizer = GetSourceUtilizer();
    unit->GetView()->Execute(ViewCommand::BuffModEnable, unit->GetEntityId(), mBuff->GetId(), static_cast<int>(mModType), utilizer->GetEntityId());
	LOG_DEBUG("Unit %d buff mod {buffId=%d type=%d} enabled"
        , unit->GetEntityId()
        , mBuff->GetId()
        , mModType);
    return false;
}

void BuffMod::Disable(bool aShouldTrigger)
{
	if (!aShouldTrigger && mBuff->GetDisableType() == EBuffDisableType::EBuffDisableByReset) {
		mStatus = EBuffModStatus::End;  //迫使框架清理时再调用一次OnDisable，清除数据 
		OnDisable(aShouldTrigger);
		return;
	}
	if (mStatus != EBuffModStatus::Enable)
	{
		mStatus = EBuffModStatus::End;
		return;
	}
	mStatus = EBuffModStatus::End;
    OnDisable(aShouldTrigger);
	if (mBuff)
		LOG_DEBUG("Unit %d buff mod {buffId=%d type=%d} disabled {trigger=%d}"
			, GetOwner()->GetEntityId()
			, mBuff->GetId()
			, mModType
			, static_cast<int>(aShouldTrigger));
}

const WeakPtr<Unit>& BuffMod::GetOwner() const
{
    return mBuff->GetOwner();
}
const WeakPtr<Unit>& BuffMod::GetSourceUtilizer() const
{
	return mBuff->GetSourceUtilizer();
}
const WeakPtr<Skill>& BuffMod::GetAncestorSkill() const
{
	return mBuff->mAncestorSkill;
}
Buff* BuffMod::GetBuff() const
{
    return mBuff;
}

bool BuffMod::IsValid() const
{
    return mStatus == EBuffModStatus::Enable;
}