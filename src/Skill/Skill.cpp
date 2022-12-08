/**********************************************************************************************************************
 *
 * Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
 * $Id$
 *
 **********************************************************************************************************************/
 
/**
 * @file $HeadURL$
 * @author $Author$
 * @date $Date$
 * @version $Revision$
 * @brief
 *
 **/

#include "Skill.h"
#include "Entity/Entity.h"
#include "Entity/Unit.h"
#include "SkillExecutor.h"
#include "ConfigMgr/ConfigMgr.h"
#include "Framework/SharedPool.h"
#include "Skill/HitHandler/HitHandler.h"
#include "SearchTarget.h"
#include "BattleInstance.h"
#include "Entity/Army.h"
#include "Framework/Util.h"


Skill::~Skill()
{
    Reset();
}

//aOrigin -> [Front_priority | Middle | Back]
//aOutput -> []
bool TryGenPoolFromPosType(vector<int>& aOrigin, vector<EPosType>& aOutput)
{
	int max = -1;
	for (auto v : aOrigin)
	{
		if (v > max)
			max = v;
	}

	if (max < 0)
		return false;

	for (int idx = 0; idx < aOrigin.size(); ++idx)
	{
		if (aOrigin[idx] == max)
		{
			aOutput.emplace_back(static_cast<EPosType>(idx + 1));
			aOrigin[idx] = -1;
		}
	}

	aOutput.emplace_back(EPosType::None);

	return true;
}
int Skill::GetId() const
{
    return mSkillId;
}
int Skill::GetTimeLength() const
{
    return mTimeLength;
}
int Skill::GetDefPointBuffId() const
{
	return mSkillConf->basedata().skillspecialdata().slowbuffid();
}
bool Skill::HasDefPoint() const
{
	return mGroundMeshSkill;
}
int Skill::GetDefPointDuration() const
{
	return CONF_TIME_CONVERT(mSkillConf->basedata().skillspecialdata().groundmeshduration());
}
int Skill::GetPerfectInterruptDuration() const
{
	int t = CONF_TIME_CONVERT(mSkillConf->basedata().perfectinterruptduration());
	if (t <= 0)
		return 2000;
	return t;
}
int Skill::GetStandTime() const
{
    return mStandTime;
}
int Skill::GetPriority() const
{
	return mPriority;
}
bool Skill::isPositiveType()
{
	return mIsPositiveType;
}
const char* Skill::GetAnimName() const
{
    if (mParentSkill)
    {
        return mParentSkill->GetAnimName();
    }
    return mSkillConf->basedata().skillanim().c_str();
}
bool Skill::IsNonNormalNonRageAnimSkill() const
{
	if ((static_cast<int>(ECastType::NormalAtkSpecial) == mCastType ||
		static_cast<int>(ECastType::EventTrigger) == mCastType) && 
		!mParentSkill && mAnimConf != nullptr)
	{
		return true;
	}
	return false;
}
bool Skill::IsNormalSkill() const
{
    int triggerMethod = mCastType;
    return  static_cast<int>(ECastType::NormalAtk) == triggerMethod
            || static_cast<int>(ECastType::RandomNormalAtk) == triggerMethod;
}
bool Skill::IsPartOfRageSkill() const
{
	return mIsPartOfRageSkill;
	//return mSkillConf->basedata().partofrageskill();
}
bool Skill::IsRageSkill() const
{
	return  static_cast<int>(ECastType::Rage) == mCastType;
}
bool Skill::IsMasterRageSkill() const
{
	return  static_cast<int>(ECastType::Rage) == mCastType && !mParentSkill;
}
bool Skill::IsPhysicalSkill() const
{
	return EDamageChannelPhysical == mSkillConf->basedata().skilltunnel();
}
bool Skill::IsChildSkill() const
{
	if (mParentSkill)
		return true;
	return false;
}
bool Skill::HasAnim() const
{
    return mAnimConf != nullptr;
}

const vector<SharedPtr<Skill> >& Skill::GetChildSkill() const
{
    return mChildSkillArr;
}
const vector<SharedPtr<Skill> >& Skill::GetProbabilisticSkill() const
{
	return mProbabilisticSkillArr;
}
const vector<EPosType>& Skill::GetRefPosType() const
{
	return mRefPos;
}
const vector<EPosType>& Skill::GetEffPosType() const
{
	return mEffPos;
}
const vector<EPosType>& Skill::GetRerOrEffPosType(bool aIsRef) const
{
	return aIsRef ? mRefPos : mEffPos;
}

WeakPtr<Skill> Skill::GetParentSkill()
{
	return mParentSkill;
}
void Skill::SetAncestorSkill(WeakPtr<Skill> aSkill)
{
	mAncestorSkill = aSkill;
}
WeakPtr<Skill> Skill::GetAncestorSkill()
{
	if (mAncestorSkill)
		return mAncestorSkill;
	return SharedFromThis();
}
SharedPtr<Unit> Skill::GetOwner()
{
	return mOwner;
}
const SharedPtr<Unit> Skill::GetConstOwner() const
{
	return mOwner;
}
int Skill::GetCastRange() const
{
	if (mOwner && mOwner->mExtraCastRange > 0)
	{
		return mCastRange + mOwner->mExtraCastRange;
	}
    return mCastRange;
}

void Skill::OffsetCD(int aTime)
{
    mLastExecuteTime += aTime;
}

void Skill::ResetCD()
{
    mLastExecuteTime = -mCDTime;
}

const SkillData* Skill::GetSkillConf() const
{
    return mSkillConf;
}
const AnimData* Skill::GetAnimConf() const
{
    return mAnimConf;
}
int Skill::GetLevel() const
{
    return mLevel;
}
int Skill::GetLevelMinus() const
{
	return mLevel - 1;
}
const SharedPtr<HitHandler> Skill::FetchHitHandler()
{
	if (mHitHandlerArr.empty() == false)
	{
		SharedPtr<HitHandler> handler = mHitHandlerArr.back();
		mHitHandlerArr.pop_back();
		return handler;
	}
	SharedPtr<HitHandler> handler = NewHitHandler(mSkillSubType);
	handler->Init(mOwner, SharedFromThis());
	return handler;
}

void Skill::ReturnHitHandler(SharedPtr<HitHandler> aHitHandler)
{
	mHitHandlerArr.emplace_back(aHitHandler);
}

bool Skill::IsTargetDeadBody() const
{
    return mSkillConf->basedata().subtype() == ESkillSubTypeRevive;
}
bool Skill::HasRefTarget() const
{
    return mRefTargetArr.size() > 0;
}
void Skill::CleanRefTargetArr()
{
	RestoreVectorElementToPool<RefTarget>(mRefTargetArr);
	mRefTargetArr.clear();	
}
bool Skill::IsRefTargetInRange() const
{
    return mRefTargetInRange;
}
bool Skill::IsRefTargetInRangeDynamic()
{
	if (mRefTargetArr.size() <= 0) return false;
	mNearestRefTargetIndex = 0;
	Vector3 delt = mOwner->GetPosition();
	delt -= mRefTargetArr[0].GetTargetPos();
	delt.y = 0;
	int64 minDist2 = delt.Magnitude2();
	int64 dist2;
	for (size_t i = 1; i < mRefTargetArr.size(); i++)
	{
		delt = mOwner->GetPosition();
		delt -= mRefTargetArr[i].GetTargetPos();
		delt.y = 0;
		dist2 = delt.Magnitude2();
		if (dist2 < minDist2)
		{
			minDist2 = dist2;
			mNearestRefTargetIndex = static_cast<int>(i);
		}
	}
	int64 castRange = GetCastRange()
		+ mRefTargetArr[mNearestRefTargetIndex].GetSize()
		+ mOwner->GetSize() + MIN_LEN; 
	mRefTargetInRange = minDist2 <= (castRange*castRange);
	return mRefTargetInRange;
}
vector<RefTarget>& Skill::GetRefTargetArr()
{
    return mRefTargetArr;
}
void Skill::SetReflectRefTargetArr(const SharedPtr<Unit> aUnit)
{
	RefTarget tmp;
	tmp.SetUnit(aUnit);
	CleanRefTargetArr();
	mRefTargetArr.emplace_back(tmp);
}
const RefTarget& Skill::GetNearestRefTarget() const
{
    return mRefTargetArr[mNearestRefTargetIndex];
}

const RefTarget* Skill::GetNearestRefTargetPtr() const
{
	return &mRefTargetArr[mNearestRefTargetIndex];
}

bool Skill::HasEffTarget() const
{
	return mEffTargetArr.size() > 0;
}

vector<SharedPtr<Unit> >& Skill::GetEffTargetArr()
{
	return mEffTargetArr;
}

void Skill::CopyInit(SharedPtr<Unit> aUnit, const Skill* aBase)
{ // used to reply reflect skill, will ignore all child skills and conf anim 
	mOwner = aUnit;  //stands for the reflecter 
	mSkillId = aBase->GetId();
	mLevel = aBase->GetLevel();
	mSkillMainType = 0;
	mSkillChannelType = aBase->mSkillChannelType;
	mParentSkill = nullptr;
	mAncestorSkill = nullptr;
	mTimeLength = aBase->mTimeLength;
	mStandTime = aBase->mStandTime;
	mBeginCount = 0;
	mEffectTargetCount = 0;
	mTotalPhysicalDamge = 0;
	mTotalMagicalDamge = 0;
	mCollisionCount = 0;
	mTotalHeal = 0;
	mExtraDmgCoef = DENOM;
	mTotalSuckBlood = 0;
	mSkillSubType = aBase->mSkillSubType;
	mTriggerRegister1 = 0;
	mTriggerRegister2 = 0;
	mRealCastRange = 0;
	mNearestRefTargetIndex = 0;
	mNeedDead = aBase->mNeedDead;
	mIsBlockPriority = aBase->mIsBlockPriority;
	mAutoRageSkill = aBase->mAutoRageSkill;
	mEnemyShowRage = aBase->mEnemyShowRage;
	mSubRageSmoothly = aBase->mSubRageSmoothly;
	mSubRageTime = aBase->mSubRageTime;
	mSkillConf = aBase->mSkillConf;
	mPriority = aBase->mPriority;
	mCastType = aBase->mCastType;
	mEventMajor = aBase->mEventMajor;
	mEventSub = aBase->mEventSub;
	mEventRelation = aBase->mEventRelation;
	mEventKey = aBase->mEventKey;
	mAnimConf = nullptr;  //need init? 
	mLockonTarget = nullptr;
	mLockon = false;
	mIsPartOfRageSkill = false;
	mGroundMeshSkill = false;
	mRageSkillInterruptable = false;
	mRefPos = aBase->mRefPos;
	mEffPos = aBase->mEffPos;
	mEnergyLv = aBase->mEnergyLv;
	mEnergyLvMove = aBase->mEnergyLvMove;
	mIsPositiveType = aBase->mIsPositiveType;
	mIsIngoreNoSkill = aBase->mIsIngoreNoSkill;
	mCastRange = aBase->mCastRange;
	mHitHandlerArr.clear();
	mChildSkillArr.clear();
	mProbabilisticParams.clear();
	mProbabilisticSkillArr.clear();
	mCDTime = aBase->mCDTime;
	mLastExecuteTime = aBase->mLastExecuteTime;
	mIsIgnoreShield = aBase->mIsIgnoreShield;
	mIsIgnoreInterruptEffect = aBase->mIsIgnoreInterruptEffect;
	mEffTargetArr.clear();
	CleanRefTargetArr();
	InitChildSkill();
}

int Skill::Init( SharedPtr<Unit> aUnit, int aSkillId, int aSkillLevel, WeakPtr<Skill> aParentSkill)
{
    mOwner = aUnit;
    mSkillId = aSkillId;
    mLevel = aSkillLevel;
	if (mLevel < 1)
	{
		LOG_WARN("Invalid Skill lv found!, skillId = %d, lv = %d", mSkillId, mLevel);
		mLevel = 1;
	}
    mParentSkill = aParentSkill;
	mAncestorSkill = nullptr;
	CleanRefTargetArr();
    mTimeLength = 0;

	mBeginCount = 0;
	mEffectTargetCount = 0;
	mTotalPhysicalDamge = 0;
	mTotalMagicalDamge = 0;
	mCollisionCount = 0;
	mTotalHeal = 0;
	mTotalSuckBlood = 0;
	mNeedDead = false;
	mIsBlockPriority = false;
	mRageSkillInterruptable = false;
	mAutoRageSkill = false;
	mEnemyShowRage = false;
	mSubRageSmoothly = false;
	mSubRageTime = 0;
	mNearestRefTargetIndex = 0;
	mRealCastRange = 0;
	mRefTargetInRange = false;
	mFocuseOnRand = false;
	mIsPositiveType = false;
	mIsIngoreNoSkill = false;
	mIsArmySkill = false;
	mArmySkillTiming = 0;
	mArmySkillStrategy = 0;

	mGroundMeshSkill = false;

	mTriggerRegister1 = 0;
	mTriggerRegister2 = 0;
	mExtraDmgCoef = DENOM;

	mSkillSubType = ESkillSubTypeDamage;

	mLockonTarget = nullptr;

    LOG_DEBUG("Skill:Init unit:%d, skillId:%d, skillLevel:%d, parent:%d", 
            aUnit->GetEntityId(), aSkillId, aSkillLevel, mParentSkill ? mParentSkill->GetId() : 0 );

    return DoInit();
}

int Skill::DoInit()
{
    mSkillConf = ConfigMgr::GetConfById<SkillData>(mSkillId);
    if( nullptr == mSkillConf )
    {
        LOG_FATAL("not found conf of skill:%d", mSkillId);
    }
	const SkillBaseData& baseConf = mSkillConf->basedata();
	switch ( static_cast<ESearchRefTargetMethod>(baseConf.reftargettype()) )
	{
		case ESearchRefTargetMethodRandFriendDead:
		case ESearchRefTargetMethodRandEnemyDead:
		case ESearchRefTargetMethodRandDead:
		case ESearchRefTargetMethodRandFriendHeroDead:
		case ESearchRefTargetMethodRandFriendSummonDead:
		case ESearchRefTargetMethodRandEnemyHeroDead:
		case ESearchRefTargetMethodRandEnemySummonDead:
		case ESearchRefTargetMethodRandHeroDead:
		case ESearchRefTargetMethodRandSummonDead:
			mNeedDead = true;
			break;
		default:
			mNeedDead = false;
	}

	mEnergyLv = 1;
	mEnergyLvMove = 1;
	if (baseConf.skillenergylevel().size() > 1)
	{
		mEnergyLv = baseConf.skillenergylevel().Get(0);
		mEnergyLvMove = baseConf.skillenergylevel().Get(1);
	}

	if (baseConf.armyskillinfo_size() > 1)
	{
		mIsArmySkill = true;
		mArmySkillTiming = baseConf.armyskillinfo().Get(0);
		mArmySkillStrategy = baseConf.armyskillinfo().Get(1);
	}

	mGroundMeshSkill = baseConf.skillspecialdata().needshowgroundmesh();
	mIsBlockPriority = baseConf.isblockpriority();
	mPriority = baseConf.skillpriority();
	mAutoRageSkill = baseConf.autorageskill();

	if (baseConf.subragesmoothly())
	{
		mSubRageSmoothly = true;
		mSubRageTime = CONF_TIME_CONVERT(baseConf.subrageduration());
	}

	if (baseConf.has_skillcasttype())
	{
		mCastType = baseConf.skillcasttype().casttype();
		if (mCastType == static_cast<int>(ECastType::EventTrigger))
		{
			mEventMajor = baseConf.skillcasttype().eventmajor();
			if (baseConf.skillcasttype().has_eventsub())
				mEventSub = baseConf.skillcasttype().eventsub();
			else
				mEventSub = 0;
		}
		else
		{
			mEventMajor = static_cast<int>(ETriggerMajor::None);
			mEventSub = 0;
		}

		if (baseConf.skillcasttype().has_eventrelation())
			mEventRelation = baseConf.skillcasttype().eventrelation();
		else
			mEventRelation = 0;
	}
	else
	{
		LOG_FATAL("fail to get skill cast type, skill id=%d", mSkillId);
	}
	mEventKey = mEventMajor * 100 + mEventSub;
    mAnimConf = nullptr;
    if( !baseConf.skillanim().empty() )
    {
        mAnimConf = FindAnimConf( mOwner->GetAvatarName(), baseConf.skillanim());
        if( nullptr == mAnimConf )
        {
            LOG_FATAL("not found animdata:%s of avatar:%s, skillId:%d", baseConf.skillanim().c_str(), mOwner->GetAvatarName().c_str(), mSkillId);
        }
		mTimeLength = EDITOR_CONF_TIME_CONVERT(baseConf.skillactionlasttime() );
		if (mTimeLength == 0)
		{
			mTimeLength = EDITOR_CONF_TIME_CONVERT(mAnimConf->animtimelength());
		}        
        mStandTime = CONF_TIME_CONVERT(baseConf.intervaltime()) - mTimeLength;
        if (mStandTime < 0)
        {
            //LOG_DEBUG("Skill {id=%d} stand time is negative, will default to 0.", mSkillId);
            mStandTime = 0;
        }
    }
	else
	{
		mTimeLength = EDITOR_CONF_TIME_CONVERT(baseConf.skillactionlasttime());
	}
	if (mParentSkill)//处理一下子技能的等级
	{		
		//此处要使用子技能的配置，这样才能支持不同的子技能使用不同的配置
		const SkillSubSkillData& subSkillConf = mSkillConf->subskilldata();
		switch (subSkillConf.leveltype())
		{
		case ESubSkillLevelCalculateMethodEqMaster:
			mLevel = mParentSkill->GetLevel();
			break;
		case ESubSkillLevelCalculateMethodMasterPercent:
			mLevel = mParentSkill->GetLevel() * subSkillConf.levelparam() / DENOM;
			break;
		case ESubSkillLevelCalculateMethodFixValue:
			mLevel = subSkillConf.levelparam();
			break;
		}
	}

	//mRefPos;
	mRefPos.clear();
	vector<int> tp(3);  //<tp> target priority in skill conf 
	auto& refConf = baseConf.refpriority();
	tp[0] = static_cast<int>(refConf.front());  //idx 0 stands for 'front' which stores the priority of 'front' 
	tp[1] = static_cast<int>(refConf.middle());  //idx 1 stands for 'middle' 
	tp[2] = static_cast<int>(refConf.back());  //stands for 'back' 
	while (TryGenPoolFromPosType(tp, mRefPos));

	mEffPos.clear();
	auto& effConf = mSkillConf->effectdata().effectpriority();
	tp[0] = static_cast<int>(effConf.front());
	tp[1] = static_cast<int>(effConf.middle());
	tp[2] = static_cast<int>(effConf.back());
	while (TryGenPoolFromPosType(tp, mEffPos));
	RestoreVectorToPool(tp);
	
	mCastRange = CONF_POS_CONVERT(baseConf.castrange());

    if(mHitHandlerArr.empty() == false || mChildSkillArr.empty() == false || mProbabilisticSkillArr.empty() == false)
    {
        LOG_WARN("not reset when init");
        Reset();
    }
	mIsIgnoreShield = mSkillConf->damagedata().ignoreshield();
	mIsIgnoreInterruptEffect = mSkillConf->basedata().ignoreinterrupteffect();
	mRageSkillInterruptable = mSkillConf->basedata().rageskillinterruptable();
	mIsIngoreNoSkill = mSkillConf->basedata().ignorenoskill();
	mLockon = mSkillConf->basedata().lockon(); 
	mIsPartOfRageSkill = mSkillConf->basedata().partofrageskill();
    mCDTime = CONF_TIME_CONVERT(baseConf.coolingtime() + (mLevel - 1) * baseConf.levelcoolingtimegrowth());
    mLastExecuteTime = -mCDTime;
	mEnemyShowRage = baseConf.skillspecialdata().enemyrageheadershow();
	mSkillMainType = baseConf.maintype();
	switch (static_cast<ESkillMainType>(mSkillMainType))
	{
	case ESkillMainType::ESkillMainTypeRangedCrowdPositive:
	case ESkillMainType::ESkillMainTypeRangedSinglePositive:
	case ESkillMainType::ESkillMainTypeMeleeCrowdPositive:
	case ESkillMainType::ESkillMainTypeMeleeSinglePositive:
		mIsPositiveType = true;
		break;
	default:
		mIsPositiveType = false;
	}
	mSkillSubType = mSkillConf->basedata().has_subtype() ? (ESkillSubType)(mSkillConf->basedata().subtype()) : ESkillSubTypeDamage;
	mSkillChannelType = baseConf.skilltunnel();
	InitChildSkill();
    return 0;
}

void Skill::InitChildSkill()
{
    const SkillSubSkillData& subSkillConf = mSkillConf->subskilldata();
	WeakPtr<Skill> thisPtr = SharedFromThis();
	bool found = false;
	
	for (int i = subSkillConf.levelsubskill_size() - 1; i >= 0; i--)
	{  //添加技能等级关联的子技能 
		auto& levelSubSkillInfo = subSkillConf.levelsubskill(i);
		if (levelSubSkillInfo.level() <= mLevel)
		{
			for (int j = 0; j < levelSubSkillInfo.id_size(); j++)
			{
				SharedPtr<Skill> skill = SharedPool<Skill>::Get();
				skill->Init(mOwner, levelSubSkillInfo.id(j), mLevel, thisPtr);
				mChildSkillArr.emplace_back(skill);
				found = true;
			}
			break;
		}
	}

	if (!found)
	{
		for (int i = 0; i < subSkillConf.id_size(); i++)
		{
			SharedPtr<Skill> skill = SharedPool<Skill>::Get();
			skill->Init(mOwner, subSkillConf.id(i), mLevel, thisPtr);
			mChildSkillArr.emplace_back(skill);
		}
	}

	for (int i = mSkillConf->subskilldata().levelprobskill_size() - 1; i >= 0; i--)
	{
		auto& levelProbSkillInfo = mSkillConf->subskilldata().levelprobskill(i);
		if (levelProbSkillInfo.level() <= mLevel)
		{
			for (int j = 0; j < levelProbSkillInfo.probabilisticskills_size(); j++)
			{
				SharedPtr<Skill> skill = SharedPool<Skill>::Get();
				skill->Init(mOwner, levelProbSkillInfo.probabilisticskills(j), mLevel, thisPtr);
				mProbabilisticSkillArr.emplace_back(skill);
			}
			for (int j = 0; j < levelProbSkillInfo.probabilisticparams_size(); j++)
			{
				mProbabilisticParams.emplace_back(levelProbSkillInfo.probabilisticparams(j));
			}
			break;
		}

	}

}

bool Skill::CheckTriggerWithCountryHeroRuntime() const
{
	auto& castConf = mSkillConf->basedata().skillcasttype();
	int needNum = int(castConf.param2());
	int realNum = mOwner->GetArmy().CountCountryHeroNumber(static_cast<ECountry>(castConf.param1()));
	return realNum <= needNum;
}

bool Skill::CheckArmySubRage(int aArmyId) const
{
	auto& castConf = mSkillConf->basedata().skillcasttype();
	int needRage = int(castConf.param1());
	return mOwner->GetBattleInstance().GetArmy(aArmyId).mSubRage > needRage;
}

bool Skill::CheckTriggerWithCountryHero() const
{
	auto& castConf = mSkillConf->basedata().skillcasttype();
	int needNum = int(castConf.param2());
	int realNum = mOwner->GetArmy().CountCountryHeroNumber(static_cast<ECountry>(castConf.param1()));
	return realNum >= needNum;
}

bool Skill::CheckTriggerWithSkill(int const aSkillId) const
{
    for (const auto& id : mSkillConf->basedata().skillcasttype().triggerskillarr())
    {
        if (id == aSkillId)
        {
            return true;
        }
    }
    return false;
}

bool Skill::CheckEventSubWithSkill(int aSkillId) const
{
	for (const auto& id : mSkillConf->basedata().skillcasttype().eventsubskillarr())
	{
		if (id == aSkillId)
		{
			return true;
		}
	}
	return false;
}

bool Skill::CheckEventBuffSub(int aBuffSubType) const
{
	for (const auto& id : mSkillConf->basedata().skillcasttype().eventbuffsubarr())
	{
		if (id == aBuffSubType)
		{
			return true;
		}
	}
	return false;
}

bool Skill::CheckEventDeathSub(int flag) const
{
	if (flag == 0)
		return mOwner->GetArmy().CountAlivedHero() == 1 && !mOwner->IsDead();
	else
		return mOwner->GetArmy().CountAlivedHero() == 0;
}

void Skill::tryExecuteSkill(bool aNeedInterrupt)
{
	if (aNeedInterrupt)
	{
		mOwner->CurrentSkillInterrupted();
		mOwner->ExecuteSkill(SharedFromThis(), 0, nullptr, mOwner);
	}
	else
	{
		mOwner->ExecuteSkill(SharedFromThis(), 0, nullptr, mOwner);
	}
}

void Skill::Reset()
{
	mRefPos.clear();
	mEffPos.clear();
	if (!mOwner) 
		return;
	mOwner.Release();
    mHitHandlerArr.clear();
    mChildSkillArr.clear();
	mProbabilisticParams.clear();
	mProbabilisticSkillArr.clear();
	isTriggeredByBuff = false;
	mAncestorSkill = nullptr;
	mLockonTarget = nullptr;

	mNeedDead = false;
	mAutoRageSkill = false;
	mSubRageSmoothly = false;
	mSubRageTime = 0;
	mEnemyShowRage = false;
	mIsBlockPriority = false;
	mIsIgnoreShield = false;
	mIsIgnoreInterruptEffect = false;
	mRageSkillInterruptable = false;

	mEnergyLv = 1;
	mEnergyLvMove = 1;
	mGroundMeshSkill = false;

	mBeginCount = 0;  //技能释放次数 
	mEffectTargetCount = 0;  //生效目标总数 
	mTotalPhysicalDamge = 0;
	mTotalMagicalDamge = 0;
	mCollisionCount = 0;
	mTotalHeal = 0;
	mTotalSuckBlood = 0;

	mSkillMainType = 0;
	mSkillChannelType = 0;

	mTriggerRegister1 = 0;
	mTriggerRegister2 = 0;

	mParentSkill = nullptr;
	mSubRageTime = 0;

	mSkillId = 0;
	mLevel = 0;
	mPriority = 0;
	mLockon = false;
	mIsPartOfRageSkill = false;
	mEventKey = 0;
	mEventRelation = 0; 
	mCastType = 0; 
	mEventMajor = 0;
	mEventSub = 0;   

	mSkillConf = nullptr;
	mAnimConf = nullptr;
	mTimeLength = 0;
	mStandTime = 0;  
	mCastRange = 0;

	mLastExecuteTime = 0;
	mCDTime = 0;

	mTriggerType = ETriggerMajor::None;  //TODO: Delete it? 
	mSkillSubType = ESkillSubTypeDamage;

	CleanRefTargetArr();
	mEffTargetArr.clear();  //ADD
	mNearestRefTargetIndex = 0;
	mRealCastRange = 0;
	mRefTargetInRange = false;

	mFocuseOnRand = true; 
	mIsPositiveType = false;
	mIsIngoreNoSkill = false;

	mIsArmySkill = false; 
	mArmySkillTiming = 0; 
	mArmySkillStrategy = 0; 

	mExtraDmgCoef = DENOM; 

	mWarRiderRelated = false; 
	mBattleSoulRelated = false; 
	if (mFunc)
	{
		mFunc->Recycle();
		mFunc = nullptr;
	}
}

CheckResult Skill::CanExecuteCommon() const
{
	//技能次数限制
	const SkillBaseData& baseConf = mSkillConf->basedata();
	if (baseConf.maxcastcountinonescene() > 0 || baseConf.maxcastcountinonebattle() > 0)
	{
		SkillCount& skillCount = mOwner->GetBattleInstance().GetSkillCount(mSkillId);
		int screenTotal = skillCount.mScreenTotal;
		int total = skillCount.mTotal;
		if (mOwner->GetArmyId() == 2)
		{
			screenTotal = skillCount.mScreenTotal2;
			total = skillCount.mTotal2;
		}
		if (baseConf.maxcastcountinonescene() > 0 && baseConf.maxcastcountinonescene() <= screenTotal)
		{
			//LOG_DEBUG("skill:%d reach onescene limit:%d", mSkillId, screenTotal);
			return CheckResult::SurpassCountNum;
		}
		if (baseConf.maxcastcountinonebattle() > 0 && baseConf.maxcastcountinonebattle() <= total)
		{
			//LOG_DEBUG("skill:%d reach total limit:%d", mSkillId, total);
			return CheckResult::SurpassCountNum;
		}
	}

	//技能CD判断
	if (mLastExecuteTime + mCDTime > mOwner->GetUnitTime())
	{
		return CheckResult::CD;
	}

	return CanExecuteNow();
}

bool Skill::PassTriggerChance() const
{ // test if pass common trigger chance 
	auto threshold = GetLevelMinus() * mSkillConf->basedata().skillcasttype().triggerchancecoef() + 
		mSkillConf->basedata().skillcasttype().triggerchance(); 
	return mOwner->GetBattleInstance().Rand(DENOM) < threshold; 
}

//only include Non-trigger type
bool Skill::CanExecuteSpecial() const
{
	//不同技能的特殊逻辑  
	const SkillBaseData& baseConf = mSkillConf->basedata();
	switch (static_cast<ECastType>(mCastType))
	{
	case ECastType::RandomNormalAtk: //概率触发
		return mOwner->GetBattleInstance().Rand(DENOM) < baseConf.normalattackchance();
	}
	return true;
}

CheckResult Skill::CanExecute() const
{
	auto ret = CanExecuteCommon();
	if (ret != CheckResult::Pass)
	{
		return ret;
	}

	if (mCastType == static_cast<int>(ECastType::EventTrigger)) 
	{ //is trigger type
		if (!PassTriggerChance())
		{
			return CheckResult::Porbability;
		}
	}
	else
	{ //for non-trigger type
		if (!CanExecuteSpecial())
		{
			return CheckResult::Porbability;
		}
	}

    return CheckResult::Pass;
}

bool Skill::CheckReplacement()
{
	//考虑技能替换 
	const SkillBaseData& baseConf = mSkillConf->basedata();
	if (baseConf.skillreplace_size() == 3
		&& HasRefTarget())  //TODO
	{
		auto& replaceData = baseConf.skillreplace();
		auto& refTarget = mRefTargetArr[0];
		auto& localPos = mOwner->GetPosition();
		int replaceSkillId = static_cast<int>(replaceData.Get(2));
		switch (static_cast<ESkillReplaceType>(replaceData.Get(0)))
		{
		case ESkillReplaceLessThan:
			{
				auto param = CONF_POS_CONVERT(replaceData.Get(1));
				auto& targetPos = refTarget.GetTargetPos();
				if ((targetPos - localPos).Magnitude() <= param)
				{
					Replace(replaceSkillId);
				}
			}
			break;
		case ESkillReplaceGreatThan:
			{
				auto param = CONF_POS_CONVERT(replaceData.Get(1));
				auto& targetPos = refTarget.GetTargetPos();
				if ((targetPos - localPos).Magnitude() > param)
				{
					Replace(replaceSkillId);
				}
			}
			break;
		case ESkillReplaceHasBuff:
			{
				auto param = static_cast<int>((replaceData.Get(1))); //buffId
				if (mOwner->HasBuff(param))
				{
					Replace(replaceSkillId);
				}
			}
			break;
		case ESkillReplaceNotHasBuff:
			{
				auto param = static_cast<int>((replaceData.Get(1))); //buffId
				if (!mOwner->HasBuff(param))
				{
					Replace(replaceSkillId);
				}
			}
			break;
		case ESkillReplaceIsLastTarget:
			{
				if (refTarget.GetType() == ERefTargetType::Unit && refTarget.GetUnit()->IsLastAliveHeroInArmy())
				{
					Replace(replaceSkillId);
				}
			}
		}

	}
	return true;
}

bool Skill::RegisterListener()
{
	if (mEventKey < 0)
	{
		return false;
	}
	if (!mFunc)
	{
		mFunc = MakeFunction<>(*this, &Skill::TryTriggerSkill, false);
	}
	auto& battleInstance = mOwner->GetBattleInstance();
	battleInstance.AddListener(mEventKey, mFunc);
	return true;
}

bool Skill::UnRegisterListener()
{
	if (mFunc)
	{
		auto& battleInstance = mOwner->GetBattleInstance();
		battleInstance.RemoveListener(mEventKey, mFunc);
		//TryRecycleFunction(mFunc);
	}
	return true;
}

void Skill::TryTriggerSkill(const BattleEvent& aEvent) 
{
	if (mCastType != static_cast<int>(ECastType::EventTrigger))
	{ // direct return for non-trigger type
		LOG_WARN("skill[%d] found unexpected event, eventId = %d", GetId(), aEvent.GetEventId());
		return; 
	}

	auto relation = static_cast<ETriggerRelation>(mEventRelation);

	// check if match relation of Body type 
	switch (relation)
	{
	case ETriggerRelation::Self:
		if (mOwner->GetEntityId() != aEvent.mEntityId) return;
		break;
	case ETriggerRelation::Friend:
		if (mOwner->IsEnemy(aEvent.mArmyId)) return;
		break;
	case ETriggerRelation::Enemy:
		if (!mOwner->IsEnemy(aEvent.mArmyId)) return;
		break;
	case ETriggerRelation::Any:
		break;
	case ETriggerRelation::FriendHeroOnly:
		if (mOwner->IsEnemy(aEvent.mArmyId)) return;
		if (!mOwner->IsHero(aEvent.mEntityId)) return;
		break;
	case ETriggerRelation::EnemyHeroOnly:
		if (!mOwner->IsEnemy(aEvent.mArmyId)) return;
		if (!mOwner->IsHero(aEvent.mEntityId)) return;
		break;
	default:
		return;
	}

	ETriggerMajor majorType = static_cast<ETriggerMajor>(mEventMajor);
	if (majorType != ETriggerMajor::Death || relation != ETriggerRelation::Self)
	{
		if (mOwner->IsDead())
		{
			return;
		}
	}

	//set event reg
	mTriggerRegister1 = aEvent.mRegister0;
	mTriggerRegister2 = aEvent.mRegister1;

	// try execute this skill
	auto& castConf = mSkillConf->basedata().skillcasttype();
	bool needInterrupt = castConf.needinterrupt();

	switch (majorType)
	{
	case ETriggerMajor::WithSkill:
		switch (static_cast<ETriggerWithSkillSub>(mEventSub))
		{
		case ETriggerWithSkillSub::Normal:
		case ETriggerWithSkillSub::NonNormal:
		case ETriggerWithSkillSub::Any:
		case ETriggerWithSkillSub::None:
			if (CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerWithSkillSub::SkillList:
			if (CheckTriggerWithSkill(aEvent.mRegister0) && CanExecute()== CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::AfterHitHandlerMove:
		if (CheckTriggerWithSkill(aEvent.mRegister0) && CanExecute() == CheckResult::Pass && RefreshRefTarget())
		{
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::OnCHeckCountryHeroNumberRuntime:
		if (CheckTriggerWithCountryHero() && CanExecute() == CheckResult::Pass && RefreshRefTarget())
		{
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::OnCheckCountryHeroNumber:
		if (CheckTriggerWithCountryHero() && CanExecute() == CheckResult::Pass && RefreshRefTarget())
		{
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::AfterSubRage:
		if (CheckArmySubRage(aEvent.mArmyId) && CanExecute() == CheckResult::Pass && RefreshRefTarget())
		{
			mOwner->GetBattleInstance().GetArmy(aEvent.mArmyId).mSubRage = 0; 
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::BuffNumber:
		{  //register0 = buff id, register1 == buff layer # 
			if (CanExecute() == CheckResult::Pass &&
				aEvent.mRegister0 == static_cast<int64>(castConf.triggerbuffid()) &&
				aEvent.mRegister1 == static_cast<int64>(castConf.triggerbufflayer()) &&
				RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::AfterShield:
		{
			if (CanExecute() == CheckResult::Pass)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::SummonWithRefTarget:
	{
		if (CanExecute() == CheckResult::Pass)
		{
			RefTarget target;
			const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
			if (!refUnit) return;
			target.SetUnit(refUnit);
			CleanRefTargetArr();
			mRefTargetArr.emplace_back(target);
			tryExecuteSkill(needInterrupt);
		}
	}
	break;
	case ETriggerMajor::ReviveWithRefTarget:
	{
		if (CanExecute() == CheckResult::Pass)
		{
			RefTarget target;
			const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
			if (!refUnit) return;
			target.SetUnit(refUnit);
			CleanRefTargetArr();
			mRefTargetArr.emplace_back(target);
			tryExecuteSkill(needInterrupt);
		}
	}
	break;
	case ETriggerMajor::AfterSkillWithAnim:
	{
		if (CanExecute() == CheckResult::Pass)
		{
			RefTarget target;
			const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
			if (!refUnit) return;
			target.SetUnit(refUnit);
			CleanRefTargetArr();
			mRefTargetArr.emplace_back(target);
			tryExecuteSkill(needInterrupt);
		}
	}
	break;
	case ETriggerMajor::AfterRageSkillWithRefTarget:
	{
		if (CanExecute() == CheckResult::Pass)
		{
			RefTarget target;
			const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
			if (!refUnit) return;
			target.SetUnit(refUnit);
			CleanRefTargetArr();
			mRefTargetArr.emplace_back(target);
			tryExecuteSkill(needInterrupt);
		}
	}
	break;
	case ETriggerMajor::AfterApplyUnlimitedShield:
		{
			if (CanExecute() == CheckResult::Pass)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mRegister0);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::AfterParry:
		switch (static_cast<ETriggerAfterParrySub>(mEventSub))
		{
		case ETriggerAfterParrySub::Skill:
			if (CheckEventSubWithSkill(aEvent.mRegister0) && CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerAfterParrySub::SkillWithRef:
			if (CheckEventSubWithSkill(aEvent.mRegister0) && CanExecute() == CheckResult::Pass)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerAfterParrySub::Melee:
		case ETriggerAfterParrySub::Range:
		case ETriggerAfterParrySub::Any:
		case ETriggerAfterParrySub::None:
			if (CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::AfterDodge:
		switch (static_cast<ETriggerAfterDodgeSub>(mEventSub))
		{
		case ETriggerAfterDodgeSub::Skill:
			if (CheckEventSubWithSkill(aEvent.mRegister0) && CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerAfterDodgeSub::SkillWithRef:
			if (CheckEventSubWithSkill(aEvent.mRegister0) && CanExecute() == CheckResult::Pass)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerAfterDodgeSub::Any:
		case ETriggerAfterDodgeSub::None:
			if (CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::WhenFirstApplyDamage:
		if (CanExecute() == CheckResult::Pass)
		{
			RefTarget target;
			const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mRegister0);
			if (!refUnit) return;
			target.SetUnit(refUnit);
			CleanRefTargetArr();
			mRefTargetArr.emplace_back(target);
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::WhenApplyDamage: 
		if (CanExecute() == CheckResult::Pass && RefreshRefTarget())
		{
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::WhenMatchRecordValue:
		if (CanExecute() == CheckResult::Pass &&
			aEvent.mRegister0 == static_cast<int64>(castConf.recordbuffid()) &&
			aEvent.mRegister1 >= static_cast<int64>(castConf.recordthreshold()) &&
			RefreshRefTarget())
		{
			tryExecuteSkill(needInterrupt);
		}
		break;
	case ETriggerMajor::Death:
		switch (static_cast<ETriggerDeathSub>(mEventSub))
		{
		case ETriggerDeathSub::None:
			if (CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerDeathSub::OnlySkillOwnerLeft:
			if (CheckEventDeathSub(0) && CanExecute() == CheckResult::Pass && RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerDeathSub::NoHeroLeft:
			if (CheckEventDeathSub(1) && CanExecute() == CheckResult::Pass && RefreshRefTarget()) 
			{
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerDeathSub::UseKillerAsRefTarget:
			if (CanExecute() == CheckResult::Pass && aEvent.mRegister0 > 0)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mRegister0);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
			break;
		case ETriggerDeathSub::UseAncestorAsRefTarget:
			if (CanExecute() == CheckResult::Pass && aEvent.mRegister0 > 0)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mRegister0, true);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::AfterBuffSubtype:
		if (CheckEventBuffSub(aEvent.mRegister0) && CanExecute() == CheckResult::Pass)
		{
			auto reftargettype = mSkillConf->basedata().reftargettype();
			ESearchRefTargetMethod type = static_cast<ESearchRefTargetMethod>(reftargettype);
			if (type == ESearchRefTargetMethod::ESearchRefTargetMethodChoosedAtTriggerTime)
			{
				RefTarget target;
				const auto& refUnit = mOwner->GetBattleInstance().GetUnitByEntityId(aEvent.mEntityId);
				if (!refUnit) return;
				target.SetUnit(refUnit);
				CleanRefTargetArr();
				mRefTargetArr.emplace_back(target);
				tryExecuteSkill(needInterrupt);
			}
			else if (RefreshRefTarget())
			{
				tryExecuteSkill(needInterrupt);
			}
		}
		break;
	case ETriggerMajor::AfterDmg:
	case ETriggerMajor::AfterHeal:
	case ETriggerMajor::AfterImmune:
	case ETriggerMajor::AfterResist:
	case ETriggerMajor::BeforeDeath:
	case ETriggerMajor::Born:
	case ETriggerMajor::Enter:
	case ETriggerMajor::Revive:
	case ETriggerMajor::AfterCritical:
	case ETriggerMajor::AfterDizzy:  //TODO: DELETE IT 
	case ETriggerMajor::AfterBeCritical:
	case ETriggerMajor::AfterKill:
	case ETriggerMajor::AfterDispelEnemyBuff:
	case ETriggerMajor::AfterInterrupt:
	case ETriggerMajor::AfterSkillReflected:
	case ETriggerMajor::AfterRageSkill:
		if (CanExecute() == CheckResult::Pass && RefreshRefTarget())
		{
			tryExecuteSkill(needInterrupt);
		}
		break;
	default:
		LOG_WARN("unknow type of TriggerMajor, %d", mEventMajor);
		break;
	}
}

void Skill::Replace(int aSkillId)
{
	if (aSkillId <= 0)
		return;
	mSkillId = aSkillId;
	mSkillConf = ConfigMgr::GetConfById<SkillData>(mSkillId);
	if (nullptr == mSkillConf)
	{
		LOG_FATAL("not found conf of skill:%d", mSkillId);
	}
	const SkillBaseData& baseConf = mSkillConf->basedata();
	mPriority = baseConf.skillpriority();
	mAnimConf = nullptr;
	mTimeLength = EDITOR_CONF_TIME_CONVERT(baseConf.skillactionlasttime());
	if (!baseConf.skillanim().empty())
	{
		mAnimConf = FindAnimConf(mOwner->GetAvatarName(), baseConf.skillanim());
		if (nullptr == mAnimConf)
		{
			LOG_FATAL("not found animdata:%s of avatar:%s", baseConf.skillanim().c_str(), mOwner->GetAvatarName().c_str());
		}
		if (mSkillConf->effectdata().isbysection()
			&& mSkillConf->curvadata().iscurve()
			&& mAnimConf->skilltriggerevents_size() != mSkillConf->effectdata().effectcount())
		{
			//技能表中显示是分段生效的有弹道的技能，那么动画表中的关键帧个数必须等于技能表中配置的技能生效次数 
			LOG_FATAL("animdata:%s of avatar:%s skilltriggerevents num %d not match skill:%d",
				baseConf.skillanim().c_str(), mOwner->GetAvatarName().c_str(),
				mAnimConf->skilltriggerevents_size(), mSkillConf->effectdata().effectcount());
		}
		mTimeLength = EDITOR_CONF_TIME_CONVERT(baseConf.skillactionlasttime());
		if (mTimeLength == 0)
		{
			mTimeLength = EDITOR_CONF_TIME_CONVERT(mAnimConf->animtimelength());
		}
		mStandTime = CONF_TIME_CONVERT(baseConf.intervaltime()) - mTimeLength;
		if (mStandTime < 0)
		{
			//LOG_DEBUG("Skill {id=%d} stand time is negative, will default to 0.", mSkillId);
			mStandTime = 0;
		}
	}

	mCastRange = CONF_POS_CONVERT(baseConf.castrange());

	if (mHitHandlerArr.empty() == false || mChildSkillArr.empty() == false || mProbabilisticSkillArr.empty() == false)
	{
		Reset();
	}

	mCDTime = CONF_TIME_CONVERT(mSkillConf->basedata().coolingtime());
	mLastExecuteTime = -mCDTime;
	InitChildSkill();

	return;
}

bool Skill::HasProjectile() const
{
	if (mSkillConf)
	{
		return mSkillConf->curvadata().iscurve();
	}
	return false;
}


CheckResult Skill::CanExecuteNow() const
{	
	//unit状态影响
	if (IsNormalSkill())
	{
		if (mOwner->CheckStateAdjust(StateAdjust::NoNormalSkill))
		{
			return CheckResult::NoNormalSkill;
		}
	}
	else
	{
		if (mOwner->CheckStateAdjust(StateAdjust::NoSkill) && !mIsIngoreNoSkill)
		{
			if(mOwner->mSkillIdSpecial != mSkillId)
				return CheckResult::NoSkill;
		}

		if (mOwner->CheckStateAdjust(StateAdjust::NoSmallSkill) &&
			!IsRageSkill())
		{
			return CheckResult::NoSkill;
		}

		if (mOwner->CheckStateAdjust(StateAdjust::NoRageSkill) &&
			IsRageSkill())
		{
			return CheckResult::NoSkill;
		}
	} 
	return CheckResult::Pass;
}

bool Skill::RefreshRefTarget()
{
	if (mSkillConf->basedata().reftargettype() == ESearchRefTargetMethodRandEnemy
		|| mSkillConf->basedata().reftargettype() == ESearchRefTargetMethodRangeRandEnemy
		|| mSkillConf->basedata().reftargettype() == ESearchRefTargetMethodRangeRandFriend
		|| mSkillConf->basedata().reftargettype() == ESearchRefTargetMethodRandEnemySummon)
	{ //随机目标一般只选第一次，之后Tick OnMove都朝向那个目标 
		if (mFocuseOnRand == true ) 
		{
			mFocuseOnRand = false; //该技能释放周期内，一般情况下不再重复随机 
			CleanRefTargetArr();
		}
		if (!mRefTargetArr.empty())
		{
			for (auto& refTarget : mRefTargetArr)
			{
				if (refTarget.GetType() != ERefTargetType::Pos && mNeedDead != refTarget.GetUnit()->IsDead())
				{
					CleanRefTargetArr();
					break;
				}
			}
		}
	}
	else
	{
		CleanRefTargetArr();
	}

    if(mParentSkill)
    { //subskill case, try shotcut setting
        if(mSkillConf->subskilldata().isfollow() )
        {
            const vector<RefTarget>& parentTargetArr = mParentSkill->GetRefTargetArr();        
            mRefTargetArr.reserve(parentTargetArr.size());
            for(auto& refTarget : parentTargetArr)
            {
                //继承目标时再次确认目标的死亡状态 
                if (refTarget.GetType() == ERefTargetType::Pos || mParentSkill->mNeedDead == refTarget.GetUnit()->IsDead())
                {
                    mRefTargetArr.emplace_back(refTarget);
                }
            }
        }
        else
        { //or do it from very beginning
            SearchRefTarget(mOwner, SharedFromThis(), mRefTargetArr);
        }
    }
    else
    { //master skill case
        if ( mOwner->CheckStateAdjust(StateAdjust::Taunted) 
			&& !mIsIngoreNoSkill
			&& !isTriggeredByBuff
			&& !mOwner->IsSummoned())
        { // a taunted unit only be able to emit normal skill to certain target
			if (!IsNormalSkill())
			{
				// owner is taunted, skill is triggered neighter by buff nor by subskill,
				// we should block any non-normal skill here
				LOG_DEBUG("RefreshRefTarget, Unit %d taunted, is not triggered by Buff or Subskill, this skillId = %d", mOwner->GetEntityId(), mSkillId);
				return false;
			}
			else if (mIsPositiveType)
			{
				return false;
			}
            const SkillBaseData& baseConf = mSkillConf->basedata();
            int specBuffId = mOwner->TauntedTargetBuffId();

			RefTargetParam param;
			param.mExcludeSelf = false;
			param.mFilter = ESearchTargetFilterBuff;
			param.mFilterParam = specBuffId;
			param.mNeedDead = false;
			param.mNeedSummon = ESummonAndHero;
			param.mRelation = ESearchTargetRelationEnemy;
			param.mSpace = ESearchRefTargetSpaceAll;
			SearchRefTargetParam(mOwner, SharedFromThis(), mRefTargetArr, param);
        }
        if( mRefTargetArr.empty() ) 
        { 
			if (mLockon)
			{
				DealLockon();
			}
			else
			{
				SearchRefTarget(mOwner, SharedFromThis(), mRefTargetArr);
			}
        } 
    }
    
    if( mRefTargetArr.empty() )
    {
		//TODO: a master skill with conf "allowNilTarget" on, should do something else
        return false;		
    }
    mNearestRefTargetIndex = GetNearestFromRefTargetArr();
    Vector3 delt = mOwner->GetPosition() - mRefTargetArr[mNearestRefTargetIndex].GetTargetPos();
	delt.y = 0;
    int64 minDist2 = delt.Magnitude2();
	RestoreObjToPool(delt);

	mRealCastRange = GetCastRange()
			+ mRefTargetArr[mNearestRefTargetIndex].GetSize()
			+ mOwner->GetSize() + MIN_LEN;  //according to Entity.MoveTowards, must make the same amendment here by adding MIN_LEN 

	//此处必须开方后比较否则和Entity::MoveTowards不一致，存在精度误差，导致某些情况下，移动到目前旁边，但是认为目标不在范围内 
    mRefTargetInRange = minDist2 <= (mRealCastRange*mRealCastRange);

	if (IsNormalSkill() && mRefTargetArr[mNearestRefTargetIndex].GetUnit())
	{
		mOwner->SetLastNormalSkillTarget(mRefTargetArr[mNearestRefTargetIndex].GetUnit());  //select idx=0 as default 
	}

    return true;
}


int Skill::GetNearestFromRefTargetArr()
{
	if (mRefTargetArr.size() == 1) return 0;
	int idx = 0;
	Vector3 myPos = mOwner->GetPosition();
	int64 minDist2 = GetDist2(myPos, mRefTargetArr[0].GetTargetPos());
	int64 dist2;
	for (size_t i = 1; i < mRefTargetArr.size(); i++)
	{
		dist2 = GetDist2(myPos, mRefTargetArr[i].GetTargetPos());
		if (dist2 < minDist2)
		{
			minDist2 = dist2;
			idx = static_cast<int>(i);
		}
	}
	return idx;
}

int64 Skill::GetDist2(const Vector3& aA, const Vector3& aB)
{
	Vector3 delt = aA - aB;
	delt.y = 0;
	int64 dist2 = delt.Magnitude2();
	RestoreObjToPool(delt);
	return dist2;
}


void Skill::DealLockon()
{
	if (mLockonTarget && 
		!mLockonTarget->IsDead() && 
		!mOwner->CheckStateAdjust(StateAdjust::Charmed))
	{
		int64 castRange = GetCastRange();
			+ mLockonTarget->GetSize()
			+ mOwner->GetSize() + MIN_LEN;
		int64 dist2 = GetDist2(mLockonTarget->GetPosition(), mOwner->GetPosition());
		if ((mOwner->IsInMove2RefST() || dist2 <= castRange * castRange) &&
			mLockonTarget->CanBeRefTargetOfUtilizer(mOwner.Get(), this))
		{
			RefTarget target;
			target.SetUnit(mLockonTarget);
			mRefTargetArr.emplace_back(target);
		}
	}

	if (mRefTargetArr.empty())
	{
		mLockonTarget = nullptr;
		SearchRefTarget(mOwner, SharedFromThis(), mRefTargetArr);
		if (!mRefTargetArr.empty())
		{
			int idx = GetNearestFromRefTargetArr();
			if (idx >= 0 && 
				mRefTargetArr[idx].GetType() == ERefTargetType::Unit && 
				!mOwner->CheckStateAdjust(StateAdjust::Charmed))
			{
				mLockonTarget = mRefTargetArr[idx].GetUnit();
			}
		}
	}
}

bool Skill::TryExecute(int aDelay, WeakPtr<SkillExecutor> aParentExecutor, const SharedPtr<Unit>& aSourceUtilizer, const SharedPtr<SkillExecutor> aCurExecutor, SharedPtr<Unit> aReflecter)
{
	if (!aReflecter && CanExecuteNow() != CheckResult::Pass)
	{
		return false; 
	}
	if (aSourceUtilizer && aSourceUtilizer->IsSummoned())
		mAncestorSkill = aSourceUtilizer->mAncestorSkill;
    mLastExecuteTime = mOwner->GetUnitTime();
	aCurExecutor->SetSourceUnit(aSourceUtilizer);
	aCurExecutor->SetReflecter(aReflecter);
	aCurExecutor->Init(mOwner, SharedFromThis(), aDelay, aParentExecutor);
	if (mNearestRefTargetIndex >= 0 && mNearestRefTargetIndex < mRefTargetArr.size())
		mOwner->SetLastRefTarget(mRefTargetArr[mNearestRefTargetIndex].GetUnit(), mRealCastRange);
	if (!aReflecter)
		mOwner->GetBattleInstance().AddSkillCount(mSkillId, mOwner->GetArmyId());
	mFocuseOnRand = true;
    return true;
}


const AnimData* FindAnimConf(const string& aAvatarName, const string& aAnimName)
{
    vector<const AvatarData* > avatarDataArr = ConfigMgr::GetConfByIndex<AvatarData>(AVATAR_CONF_KEY, aAvatarName);
    if(avatarDataArr.empty())
    {
        return nullptr;
    }
    const AvatarData* avatarData = avatarDataArr[0];
    for( int i = 0; i < avatarData->animdatas_size(); i++ )
    {
        if( avatarData->animdatas(i).animname().compare( aAnimName ) == 0 )
        {
            return &avatarData->animdatas(i);            
        }
    }
    return nullptr;
}
