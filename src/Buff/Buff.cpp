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

#include "Buff.h"
#include "BuffAllMods.h"
#include "BuffMod.h"
#include "BuffMgr.h"
#include "Entity/Unit.h"
#include "Log/Log.h"
#include "ConfigMgr/ConfigMgr.h"
#include "Entity/Unit.h"
#include "View/BattleViewOutput.h"
#include "BattleInstance.h"
#include "Framework/Util.h"


int64 GetUnitAttr(Unit* const aUnit, BuffAttrId aAttrId)
{
	switch (aAttrId)
	{
	case BuffAttrId::Hp:
		return aUnit->GetMaxHp();
	case BuffAttrId::PhysicalAttack:
		return aUnit->GetPhysicalAtk();
	case BuffAttrId::PhysicalDefend:
		return aUnit->GetPhysicalDef();
	case BuffAttrId::MagicAttack:
		return aUnit->GetMagicAtk();
	case BuffAttrId::MagicDefend:
		return aUnit->GetMagicDef();
	default:
		LOG_FATAL("invalid attrId:%d", aAttrId);
	}	
	return 0;
}

bool BuffHitCondition::Valid(const BuffMgr& aBuffMgr, const BuffData* aConfig)
{
	UpdateStackCount(aBuffMgr);
	return mStackCount > 0 ? Dicing(aBuffMgr, aConfig) : false;
}

int BuffHitCondition::StackCount() const
{
    return mStackCount;
}

bool BuffHitCondition::Dicing(const BuffMgr& aBuffMgr, const BuffData* aConfig)
{
	int prob = aConfig->basedatamodel().hitrate();
	const SpecialHitModel* spConf = &aConfig->specialhitmodel();
	
	if ( spConf->buffhitrate_size() )
	{
		if (spConf->buffhitrate_size() % 2 != 0)
		{
			LOG_FATAL("invalid conf. special condition, buff prob. buff:%d", aConfig->id());
			return false;
		}
		for (int i = 0; i < spConf->buffhitrate_size(); i += 2)
		{
			if (mStackCount >= spConf->buffhitrate(i))
			{
				prob = spConf->buffhitrate(i + 1);
			}
			else
			{
				break;
			}
		}
	}
	
	if ( aBuffMgr.GetOwner()->GetBattleInstance().Rand(DENOM) > prob )
	{
		return false;
	}
	return true;
}

bool BuffHitNone::Valid(const BuffMgr& aBuffMgr, const BuffData* aConfig)
{
	return true;
}
void BuffHitNone::UpdateStackCount(const BuffMgr& aBuffMgr)
{
    mStackCount = 0;    
}

void BuffHitByType::UpdateStackCount(const BuffMgr& aBuffMgr)
{
    mStackCount = 0;    
    for (auto& buff : aBuffMgr.GetBuffMap())
    {
        if (buff.second->GetType() == mType)
        {
            mStackCount += buff.second->GetStack();//stack            
        }
    }
}

void BuffHitBySubType::UpdateStackCount(const BuffMgr& aBuffMgr)
{
    mStackCount = 0;    
    for (auto& buff : aBuffMgr.GetBuffMap())
    {
        if (buff.second->GetSubType() == mSubType)
        {
            mStackCount += buff.second->GetStack();//stack            
        }
    }
}

void BuffHitAllBuffExists::UpdateStackCount(const BuffMgr& aBuffMgr)
{//assume each buff id is unique in mBuffs and BuffMgr.mBuffArr
    mStackCount = 0;    
    for (auto& buff : aBuffMgr.GetBuffMap())
    {
        for (int id : mBuffs)
        {
            if (buff.second->GetId() == id)
            {
                mStackCount += buff.second->GetStack();//stack
                break;
            }
        }
    }	
}
void BuffHitAllBuffExists::Reset()
{
	mBuffs.clear();
}

void BuffHitAnyBuffExists::UpdateStackCount(const BuffMgr& aBuffMgr)
{
    mStackCount = 0;    
    for (auto& buff : aBuffMgr.GetBuffMap())
    {
        for (int id : mBuffs)
        {
            if (buff.second->GetId() == id)
            {
                if(mStackCount < buff.second->GetStack())
                    mStackCount = buff.second->GetStack();//max     
            }
        }
    }
}
void BuffHitAnyBuffExists::Reset()
{
	mBuffs.clear();
}

bool BuffHitByGender::Valid(const BuffMgr& aBuffMgr, const BuffData* aConfig)
{
	if (mUtilizer)
		return aBuffMgr.GetOwner()->mIsMale != mUtilizer->mIsMale;
	return false;
}
void BuffHitByGender::UpdateStackCount(const BuffMgr& aBuffMgr)
{
	mStackCount = 0;
}

void BuffHitByGender::Reset()
{
	mUtilizer = nullptr;
}

bool Buff::Init(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Unit>& aSourceUtilizer, const WeakPtr<Unit>& aOwner, BuffMgr& aMgr, int const aBuffId, int const aLevel, const BuffData* aConfig, const SharedPtr<BuffHitCondition>& aCondition)
{
    //SharedPtr<Buff> ptr = SharedFromThis();
    mConfig = aConfig;
    mAnimName = aConfig->basedatamodel().lastingaction().c_str();
	mType = static_cast<BuffType>(mConfig->basedatamodel().maintype());
	mSubType = static_cast<BuffSubType>(mConfig->basedatamodel().subtype());
	mOverrideType = static_cast<BuffOverrideType>(mConfig->basedatamodel().overlytype());
	mBeCleanLevel = static_cast<int>(mConfig->basedatamodel().becleanlevel());
	mOwner = aOwner;

    mTimeLength = mConfig->basedatamodel().lasttime() + mConfig->basedatamodel().lasttimegrowth() * (aLevel - 1);
	int64 timeLength = TryShrinkTimeLength();
	if (timeLength == 0) 
		return false;

    mSpConf = &aConfig->specialhitmodel();
	mSourceUtilizer = aSourceUtilizer.Get() == nullptr ? aUtilizer : aSourceUtilizer;
    mMgr = &aMgr;
    mId = aBuffId;
    mLevel = aLevel;
	mRemoveWhenBeControlled = false;
	mRemoveWhenShapeShifted = false;
	if (mConfig->basedatamodel().has_removewhenbecontrolled())
		mRemoveWhenBeControlled = mConfig->basedatamodel().removewhenbecontrolled();
	if (mConfig->basedatamodel().has_removewhenshapeshifted())
		mRemoveWhenShapeShifted = mConfig->basedatamodel().removewhenshapeshifted();
    mStack = 1;
    mBeClearByBuffType =static_cast<BuffBeClearByBuffType>( mConfig->basedatamodel().purgetype() );
	mCleanableBuffIdArr.reserve(mConfig->basedatamodel().purgebuffarr_size());
	for (int id : mConfig->basedatamodel().purgebuffarr())
	{
		mCleanableBuffIdArr.push_back(id);
	}

	mRecordData = 0;
	mLabelId = 0;
	if (mConfig->basedatamodel().has_labelid())
	{
		mLabelId = static_cast<int>(mConfig->basedatamodel().labelid());
		mLabelId = (mLabelId - 1) / 2 + 1;
	}
	
	mEffectNeedRealtimeRefresh = mConfig->specialhitmodel().updateeffect();
    mHitCondition = aCondition;
    SpecialConditionEffectMultiplier();
    SpecialConditionTimeMultiplier();
	mStatus = EBuffStatus::Using;
    mLifeTimer = SharedPool<Timer<Buff> >::Get();
	mExecuteTime = timeLength * mTimeMultiplier / DENOM + aOwner->GetUnitTime();
	mLifeTimer->Execute(aOwner->GetTimerMgr(), this, &Buff::OnTimeout, mExecuteTime); 
    RefreshUnitAnim();
	mAncestorSkill = nullptr;
	mDisableType = EBuffDisableType::None;
	//AddModsByConf(aUtilizer, ptr, aLevel - 1, aConfig);
	return true;
}

int64 Buff::GetRemainingTime()
{
	if (!mOwner || mExecuteTime == 0) return 0;
	return mExecuteTime - mOwner->GetUnitTime();
}

int64 Buff::TryShrinkTimeLength()
{
	bool needShrink = false;
	int64 ret = mTimeLength;
	switch (mSubType) {
	case BuffSubType::Dizziness:
	case BuffSubType::Freeze:
	case BuffSubType::Charmed:
	case BuffSubType::Chaos:
	case BuffSubType::RandomMove:
	case BuffSubType::Taunt:
	case BuffSubType::TransformToSheep:
		needShrink = true;
		break;
	default:
		break;
	}
	if (needShrink)
	{
		int32 shringRate = DENOM - int32(GetOwner()->TryGetShrinkControlSum());
		if (shringRate < 0) shringRate = 0;
		ret = ret * shringRate / DENOM;
	}
	return ret;
}

//shared pool reset
void Buff::Reset()
{
	mDisableType = EBuffDisableType::EBuffDisableByReset;
    mMods.clear();
	if (mLifeTimer)
	{
		mLifeTimer->Cancel();
		//mLifeTimer->Reset();  //should not reset Timer, otherwise this timer could not be removed from TimerMgr properly 
		mLifeTimer.Release();
	}
	if (mSetAnimTimer)
	{
		mSetAnimTimer->Cancel();
		//mSetAnimTimer->Reset();
		mSetAnimTimer.Release();
	}
	if (mOwner)
		mOwner.Release();
	if (mMgr)
		mMgr = nullptr;
	if (mHitCondition)
		mHitCondition.Release();

	mSourceUtilizer = nullptr;
	mId = 0;
	mLevel = 0;
	mBeCleanLevel = 0;
	mRemoveWhenBeControlled = false;
	mRemoveWhenShapeShifted = false;
	mStatus = EBuffStatus::Invalid;
	mDisableType = EBuffDisableType::EBuffDisableByTimeOut;
	mTimeLength = 0;
	mBeClearByBuffType = BuffBeClearByBuffType::Any;
	mCleanableBuffIdArr.clear();
	mType = BuffType::Positive;
	mSubType = BuffSubType::Heal;
	mOverrideType = BuffOverrideType::None;
	mStack = 0;
	mEffectMultiplier = 0;
	mTimeMultiplier = 0;
	mLabelId = 0;
	mRecordData = 0;
	
	mConfig = nullptr;
	mSpConf = nullptr;
	mAnimName = nullptr;
	mEffectNeedRealtimeRefresh = false;

	mExecuteTime = 0;

}

void Buff::CleanListener()
{
	for (auto& m : mMods)
	{
		m->UnRegisterListener();
	}
}

int Buff::IncreaseStack()
{
    mStack = mStack + 1;
    int max = mConfig->basedatamodel().maxoverlynum();
    if (mStack > max)
    {
        mStack = max;
    }
    else
    {
        StackAdded(1);
    }
    return mStack;
}

int Buff::RemoveStack(int const aCount)
{
    if (aCount >= mStack)
    {
        OnRemove(false);
        mMgr->RemoveBuffById(mId);
        return mStack;
    }
    else
    {
        mStack -= aCount;
        StackRemoved(aCount);
        return aCount;
    }
}

void Buff::StackAdded(int const aChange)
{
    for (auto& m : mMods)
    {
        m->StackAdded(aChange);
    }
}

void Buff::StackRemoved(int const aChange)
{
    for (auto& m : mMods)
    {
        m->StackRemoved(aChange);
    }
}

bool Buff::IsValid() const
{
	if (mStatus != EBuffStatus::Using)
	{
		return false;
	}
	return true;
}

void Buff::OnRemove(bool const aShouldTrigger)
{
    if(mStatus != EBuffStatus::Using)
    {
        //Disable BuffMode时可能会触发技能，从而导致owner死亡。owner死亡时会再次触发onRemove
        return;
    }
    mStatus = EBuffStatus::Removed;
	if (mDisableType != EBuffDisableType::EBuffDisableByTimeOut)
	{
		mDisableType = EBuffDisableType::EBuffDisableByManual;
	}
    for (auto& m : mMods)
        m->Disable(aShouldTrigger);
    mOwner->GetView()->Execute(ViewCommand::BuffDel, mOwner->GetEntityId(), mId);
    mLifeTimer->Cancel();
    if( mSetAnimTimer )
    {
        mSetAnimTimer->Cancel();
    }
}

void Buff::SpecialConditionEffectMultiplier() 
{
    mEffectMultiplier = DENOM;    
	if (mSpConf->buffeffect_size())
	{
		int stack = mHitCondition->StackCount();
		if (mSpConf->buffeffect_size() % 2 != 0)
		{
			LOG_FATAL("invalid conf. special condition, buff effect. buff:%d", mId);
			return;
		}
		for (int i = 0; i < mSpConf->buffeffect_size(); i += 2)
		{
			if (stack >= mSpConf->buffeffect(i))
			{
				mEffectMultiplier = mSpConf->buffeffect(i + 1);
			}
			else
			{
				break;
			}
		}
	}
}

void Buff::SpecialConditionTimeMultiplier() 
{
    mTimeMultiplier = DENOM;    
    if (mSpConf->bufflasttime_size())
    {
		int stack = mHitCondition->StackCount();
		if (mSpConf->bufflasttime_size() % 2 != 0)
		{
			LOG_FATAL("invalid conf. special condition, buff lasttime. buff:%d", mId);
			return;
		}
		for (int i = 0; i < mSpConf->bufflasttime_size(); i += 2)
		{
			if (stack >= mSpConf->bufflasttime(i))
			{
				mTimeMultiplier = mSpConf->bufflasttime(i + 1);
			}
			else
			{
				break;
			}
		}     
    }
}

void Buff::BuffReset(int const aTime)
{
    mTimeLength = aTime;
    BuffReset();
}

void Buff::BuffReset()
{
	if (mLabelId < 0)
	{
		GetOwner()->SendScreenTextCmd(static_cast<ScreenTextType>(-mLabelId));
	}
	mExecuteTime = GetOwner()->GetUnitTime() + mTimeLength * mTimeMultiplier / DENOM;
	if (mLifeTimer->IsValid())
		mLifeTimer->Reset(mExecuteTime);
	else
	{
		LOG_WARN("meet invalid mLifeTimer in Buff %d, owner %d", mId, GetOwner()->GetTplId());
		mExecuteTime = GetOwner()->GetUnitTime();
	}
	mRecordData = 0;
	for (auto& mod : mMods)
		mod->Reset(GetOwner()->GetUnitTime());
}

void Buff::Offset(int const aDiff)
{
    mLifeTimer->Offset(aDiff);
    for (auto& mod : mMods)
        mod->Offset(aDiff);
	mExecuteTime += aDiff;
}

bool Buff::CheckHitCondition(const BuffMgr& aTarget)
{
    return mHitCondition->Valid(aTarget, mConfig);
}

void Buff::AddMod(const SharedPtr<BuffMod>& aMod)
{
    mMods.push_back(aMod);
}

bool Buff::OnTimeout(Timer<Buff>&)
{
	mDisableType = EBuffDisableType::EBuffDisableByTimeOut;
    OnRemove(true);
    mMgr->RemoveBuffById(mId);
    return false;
}

const SharedPtr<BuffMod>* Buff::GetMod(BuffSubType const aType) const
{
    for (auto& m : mMods)
    {
        if (m->IsOfType(aType))
            return &m;
    }
    return nullptr;
}

BuffMgr* Buff::GetMgr() const
{
    return mMgr;
}

const char* Buff::GetAnimName() const
{
    return mAnimName;
}

int Buff::GetId() const
{
    return mId;
}
bool Buff::IsClearableByBuff(int aByBuffId) const
{
    return mBeClearByBuffType == BuffBeClearByBuffType::Any
		|| (mBeClearByBuffType == BuffBeClearByBuffType::SpecifyBuffId
			&& InVector(mCleanableBuffIdArr, aByBuffId) );
}
BuffType Buff::GetType() const
{
    return mType;
}
BuffSubType Buff::GetSubType() const
{
    return mSubType;
}
int Buff::GetLabelId() const
{
	return mLabelId;
}
bool Buff::HasLabelId() const
{
	return mLabelId != 0;
}
int64 Buff::GetRecordData() const
{
	return mRecordData;
}
void Buff::SetRecordData(int64 aData)
{
	mRecordData = aData;
}
void Buff::AddRecordData(int64 aData)
{
	mRecordData += aData;
}
EBuffDisableType Buff::GetDisableType() const
{
	return mDisableType;
}
int Buff::GetLevel() const
{
	return mLevel;
}
int Buff::GetStack() const
{
    return mStack;
}
int64 Buff::ScaledValue(int64 const aValue) const
{
	int64 NOM = int64(mStack) * int64(mEffectMultiplier);
	int64 ret = IncByRate(aValue, NOM, DENOM);
	//int ft = mOwner->GetBattleInstance().GetFrameTime();
	//LOG_WARN("ScaledValue ft[%d] id[%d], ret[%lld], NOM[%lld], val[%lld]", ft, mId, ret, NOM, aValue);
	return ret;
    //return int64(aValue * mStack * mEffectMultiplier / DENOM);     //TODO: fix this bug 
}
const WeakPtr<Unit>& Buff::GetOwner() const
{
    return mOwner;
}

WeakPtr<Unit>& Buff::GetSourceUtilizer()
{
	return mSourceUtilizer;
}

void Buff::WhenBuffNumberChanged()
{
	if (!mEffectNeedRealtimeRefresh)
	{
		return;
	}
	mHitCondition->UpdateStackCount(*mMgr);
	SpecialConditionEffectMultiplier();
}

int Buff::WhenAddSameBuff()
{
    int stack = GetStack();
    if (mOverrideType == BuffOverrideType::StackReset)
    {
        int stackNew = IncreaseStack();
        if (stackNew != stack)
        {  
            SpecialConditionEffectMultiplier();
        }
		BuffReset();
        return stackNew;
    }
    if (mOverrideType == BuffOverrideType::Reset)
    {
        SpecialConditionTimeMultiplier();
        BuffReset(); 
    } 
	if (mOverrideType >= BuffOverrideType::StackNoReset)
	{
		int stackNew = IncreaseStack();
		if (stackNew != stack)
		{
			SpecialConditionEffectMultiplier();
		}
		return stackNew;
	}
    return stack;
}

int Buff::WhenAddSameBuff(int aTimes)
{
	int stack = GetStack();
	if (aTimes <= 0) return stack;
	int maxStack = mConfig->basedatamodel().maxoverlynum();
	int wantStack = stack + aTimes;
	if (wantStack > maxStack)
		wantStack = maxStack;
	if (mOverrideType == BuffOverrideType::StackReset)
	{
		int stackNew = 0;
		int ct = 0;
		for (; stackNew <= wantStack && ct < aTimes; ct++)
		{
			stackNew = IncreaseStack();
		}
		if (stackNew != stack)
		{
			SpecialConditionEffectMultiplier();
			BuffReset();
		}
		return stackNew;
	}
	if (mOverrideType == BuffOverrideType::Reset)
	{
		SpecialConditionTimeMultiplier();
		BuffReset();
	}
	if (mOverrideType >= BuffOverrideType::StackNoReset)
	{
		int stackNew = IncreaseStack();
		if (stackNew != stack)
		{
			SpecialConditionEffectMultiplier();
		}
		return stackNew;
	}
	return stack;
}

void Buff::RefreshUnitAnim()
{
    auto& baseData = mConfig->basedatamodel();
	if (baseData.has_lastingaction())
	{
		int delay = 0;
		if (baseData.has_lastactiondelay())
		{
			delay = CONF_TIME_CONVERT(baseData.lastactiondelay());
		}
		mSetAnimTimer = SharedPool<Timer<Buff> >::Get();
		mSetAnimTimer->Execute(mOwner->GetTimerMgr(), this, &Buff::OnSetUnitAnimTimer, mOwner->GetUnitTime() + delay);
	}
}
bool Buff::OnSetUnitAnimTimer(Timer<Buff>&)
{
    auto& baseData = mConfig->basedatamodel();
    mOwner->SetAnim(baseData.lastingaction().c_str());
    return false;
}

bool Buff::NeedRemoveWhenBeControlled() const
{
	return mRemoveWhenBeControlled;
}

bool Buff::NeedRemoveWhenShapeShifted() const
{
	return mRemoveWhenShapeShifted;
}

bool Buff::IsControlType() const
{
	if (mType != BuffType::Negative)
		return false;
	switch (mSubType)
	{
	case BuffSubType::NoSkill:
	case BuffSubType::Dizziness:
	case BuffSubType::Freeze:
	case BuffSubType::Charmed:
	case BuffSubType::Chaos:
	case BuffSubType::RandomMove:
	case BuffSubType::Taunt:
	case BuffSubType::TransformToSheep:
	case BuffSubType::Numb:
		return true;
	default:
		return false;
	}
	return false;
}