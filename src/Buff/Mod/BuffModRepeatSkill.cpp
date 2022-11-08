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

#include "BuffModRepeatSkill.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"
#include "Skill/SkillExecutor.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"

enum class ECastCondition 
{
	MustTrigger = 0,
	RecordDataMeets = 1
};

enum class EValueType
{
	FixValue = 0,
	PhysicalAtk = 1
};

void BuffModRepeatSkill::StackAdded(int)
{
    //nothing
}

void BuffModRepeatSkill::StackRemoved(int)
{
    //nothing
}

void BuffModRepeatSkill::OnReset()
{
	BuffMod::OnReset();
	ResetValues();
	if (!mTimer) 
		mTimer = SharedPool<Timer<BuffModRepeatSkill> >::Get();
	auto& unit = GetOwner();
	//check cast condition
	switch (static_cast<ECastCondition>(mParams.mCastCondition))
	{
	case ECastCondition::MustTrigger:
		mTimer->Execute(unit->GetTimerMgr(), this, &BuffModRepeatSkill::ExecuteSkill, 0);
		break;
	case ECastCondition::RecordDataMeets:
	{
		mRecordCount = 1;
		switch (static_cast<EValueType>(mParams.mValueType))
		{
		case EValueType::FixValue:
			mFixValue = mParams.mValue;
			break;
		case EValueType::PhysicalAtk:
			mFixValue = unit->GetPhysicalAtk() * mParams.mValue / DENOM;
			break;
		default:
			LOG_FATAL("unknow value type %d", mParams.mValueType);
		}
		mTimer->Execute(unit->GetTimerMgr(), this, &BuffModRepeatSkill::ExecuteSkillUsingRecordData, unit->GetUnitTime() + mParams.mInterval);
	}
	break;
	default:
		LOG_FATAL("unknown cast condition %d", mParams.mCastCondition);
		return;
	}
}

void BuffModRepeatSkill::OnEnable()
{
    auto& unit = GetOwner();
    unit->IncStateAdjust(StateAdjust::RepeatSkill);
    mTimer = SharedPool<Timer<BuffModRepeatSkill> >::Get();
	//check cast condition
	switch (static_cast<ECastCondition>(mParams.mCastCondition))
	{
	case ECastCondition::MustTrigger:
		mTimer->Execute(unit->GetTimerMgr(), this, &BuffModRepeatSkill::ExecuteSkill, 0);
		break;
	case ECastCondition::RecordDataMeets:
	{
		mRecordCount = 1;
		switch (static_cast<EValueType>(mParams.mValueType))
		{
		case EValueType::FixValue:
			mFixValue = mParams.mValue;
			break;
		case EValueType::PhysicalAtk:
			mFixValue = unit->GetPhysicalAtk() * mParams.mValue / DENOM;
			break;
		default:
			LOG_FATAL("unknow value type %d", mParams.mValueType);
		}
		mTimer->Execute(unit->GetTimerMgr(), this, &BuffModRepeatSkill::ExecuteSkillUsingRecordData, unit->GetUnitTime() + mParams.mInterval);
	}
		break;
	default:
		LOG_FATAL("unknown cast condition %d", mParams.mCastCondition);
		return;
	}
}

void BuffModRepeatSkill::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	mCount = 0;
	mFixValue = 0;
	mRecordCount = 0;
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mSkill = nullptr;
		mParams.mSkillId = 0;
		mParams.mInterval = 0;
		mParams.mCount = 0;
		mParams.mSourceType = 0;
		mParams.mCastCondition = 0;
		mParams.mValueType = 0;
		mParams.mValue = 0;
		mParams.mIgnoreNoSkill = false;
		return;
	}
	if (GetSourceUtilizer() && mParams.mSkill)
	{
		GetSourceUtilizer()->SetBuffSkillInfo(mParams.mSkill->GetId(), mParams.mSkill->mBeginCount, mParams.mSkill->mEffectTargetCount);
	}
    GetOwner()->DecStateAdjust(StateAdjust::RepeatSkill);
}

void BuffModRepeatSkill::ResetValues()
{
    BuffMod::ResetValues();
    mCount = mParams.mCount;
}

bool BuffModRepeatSkill::ExecuteSkillUsingRecordData(Timer<BuffModRepeatSkill>& aTimer)
{
	//check if able to do something 
	auto record = GetBuff()->GetRecordData();
	if (mFixValue * mRecordCount <= record)
	{
		mRecordCount = record % mFixValue + 1;
	}
	else
	{
		aTimer.Reset(GetOwner()->GetUnitTime() + mParams.mInterval);
		return true;
	}
	mParams.mSkill->isTriggeredByBuff = true;
	mParams.mSkill->mAncestorSkill = GetBuff()->mAncestorSkill;
	
	const auto& sourceUtilizer = mParams.mSourceType == 1 ? GetSourceUtilizer() : WeakPtr<Unit>();
	for (int r = 0; r < GetBuff()->GetStack(); ++r)
	{
		if (mParams.mSkill->RefreshRefTarget())
			GetOwner()->ExecuteSkill(mParams.mSkill, 0, nullptr, sourceUtilizer);
	}
	if (!IsValid() && !mParams.mSkill)
		return false;
	mParams.mSkill->isTriggeredByBuff = false;
	--mCount;
	if (mCount > 0 && IsValid())
	{
		aTimer.Reset(GetOwner()->GetUnitTime() + mParams.mInterval);
		return true;
	}
	return false;
}

bool BuffModRepeatSkill::ExecuteSkill(Timer<BuffModRepeatSkill>& aTimer)
{
	mParams.mSkill->isTriggeredByBuff = true;
	mParams.mSkill->mAncestorSkill = GetBuff()->mAncestorSkill;
	if (mParams.mIgnoreNoSkill)
		GetOwner()->mSkillIdSpecial = mParams.mSkill->GetId();
   
	const auto& sourceUtilizer = mParams.mSourceType == 1 ? GetSourceUtilizer() : WeakPtr<Unit>();
    for (int r = 0; r < GetBuff()->GetStack(); ++r)
    {
		if (mParams.mSkill->RefreshRefTarget())
			GetOwner()->ExecuteSkill(mParams.mSkill, 0, nullptr, sourceUtilizer);
    }
    
	if (mParams.mIgnoreNoSkill)
		GetOwner()->mSkillIdSpecial = 0;
	mParams.mSkill->isTriggeredByBuff = false;
    --mCount;
    if( mCount > 0 && IsValid() )
    {
        aTimer.Reset(GetOwner()->GetUnitTime() + mParams.mInterval);
        return true;
    }
    return false;
}