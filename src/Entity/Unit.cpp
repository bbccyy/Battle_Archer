

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
#include <algorithm>
#include "Framework/Util.h"
#include "Unit.h"
#include "Skill/Skill.h"
#include "Framework/SharedPool.h"
#include "Log/Log.h"
#include "View/BattleViewOutput.h"
#include "Framework/Physics/PhysicsSystem.h"
#include "Framework/Physics/BoundingVolume.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Army.h"
#include "BattleInstance.h"
#include "Skill/Skill.h"
#include "Skill/RefTarget.h"
#include "Skill/SkillExecutor.h"
#include "Buff/Buff.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ConfigMgr/Pb/net/Battle.pb.h"
#include "Buff/Mod/BuffModAbsorbDamage.h"
#include "Buff/Mod/BuffModProperty.h"
#include "Entity/Barrier/SceneBarrier.h"
//#include "MeleeRingMgr.h"

using std::string;

int Unit::slgCoef1 = 0;
int Unit::slgCoef2 = 1;
int Unit::slgCoef3 = 0;
int Unit::slgCoef4 = 1;
int Unit::slgCoef5 = 0;
int Unit::slgCoef6 = 1;

// return True if select aSkill1, skill Priority:
//   NormalXXX < Others;    NormalAtk < RandomNormalAtk < NormalAtkNum;
//   NormalAtkNum.LargeNum < NormalAtkNum.LessNum;    Others.LargeID < Others.LessID
bool cmpSkillCandiate(const SharedPtr<Skill>& aSkill1, const SharedPtr<Skill>& aSkill2)  //TODO: Delete it
{
    static int skillTriggerMethodPriority[static_cast<int>(ECastType::_Count)];
    skillTriggerMethodPriority[static_cast<int>(ECastType::NormalAtkSpecial)] = 1;
    skillTriggerMethodPriority[static_cast<int>(ECastType::RandomNormalAtk)] = 2;
    skillTriggerMethodPriority[static_cast<int>(ECastType::NormalAtk)] = 3;
    int ret = skillTriggerMethodPriority[aSkill1->GetSkillConf()->basedata().skillcasttype().casttype()]
        - skillTriggerMethodPriority[aSkill2->GetSkillConf()->basedata().skillcasttype().casttype()];
    if (ret != 0)
    {
        return ret < 0;
    }
    if ( aSkill1->GetSkillConf()->basedata().skillcasttype().casttype() == static_cast<int>(ECastType::NormalAtkSpecial) )
    {
        return aSkill1->GetLastExecuteNormalAtkNum() <  aSkill2->GetLastExecuteNormalAtkNum();
    }
    return aSkill1->GetId() < aSkill2->GetId();
}

// return True if aState.Priority < aOther.Priority
bool CompareByAnimPriority(const ControlToken* aState, const ControlToken* aOther)
{
    if (aState->mPriority == aOther->mPriority)
        return aState->mStartTime < aOther->mStartTime;
    return aState->mPriority < aOther->mPriority;
}

void ShapeShift::Reset()
{
	mTplId = 0;
	mLevel = 0;
	mLastTplId = 0;
	mLastLevel = 0;
	mLastAttrArr.clear();
	mInheritLevel = 0;
	mInheritAttributes = false;
	mInheritSkill = false;
	mNormalAtkNumBeforeChangeAvatar = 0;
	mSkillNumBeforeChangeAvatar = 0;
	mSkillLv = 0;
	mChainSkillIndex = 0;
	isBattleSoulMode = false;
	mBuffId = 0;
	mIsValid = false;
}

void ControlToken::Reset()
{
	mType = ControlledType::None;//控制类型 
	mIsValid = false;//该状态是否生效 
	mName = nullptr;//（动作）名称 
	mPriority = 0;//（动作）表现优先级，用于排序 
	mStartTime = 0;//开始生效的时间点，用于排序 
	mTimeOut = 0;  //this state will be abandoned at <mTimeOut> Unit time
	mReplayable = false;
	if (OnTick)
	{
		OnTick->Recycle();
		OnTick = nullptr;//该状态的持续处理方法 
	}
}

void ControlToken::CalculatePriority()
{
    mPriority = 0;
    if (strncmp(mName, Unit::ANIM_NAME_IDLE, 4) == 0)
    {
        mPriority = 0;
    }
	else if (string(mName).empty())  //empty anim name is a trick that allows frontend skip this anim(ie, play pre-anim longer) 
	{
		mPriority = 0;
	}
	else if (strncmp(mName, Unit::ANIM_NAME_WEAK, 7) == 0)
	{
		mPriority = 100;
	}
	else if (strncmp(mName, Unit::ANIM_NAME_WEAK2, 7) == 0)
	{
		mPriority = 101;
	}
	else if (strncmp(mName, Unit::ANIM_NAME_WALK, 4) == 0)
	{
		mPriority = 12;
	}
    else if (strncmp(mName, Unit::ANIM_NAME_RUN, 3) == 0 )
    {
        mPriority = 15;
    }
    else if (strncmp(mName, Unit::ANIM_NAME_STUN_PREFIX, 4) == 0)  //strncmp(str1, str2) returns 0 iff str1 eq to str2
    {
        mPriority = 20;
    }
	else if (strncmp(mName, Unit::ANIM_NAME_HIT_PREFIX, 3) == 0)
	{
		mPriority = 30;
	}
    else if (strncmp(mName, Unit::ANIM_NAME_DOWN, 4) == 0)
    {
		//mPriority = 50;
        mPriority = 35;
    }
	else if (strncmp(mName, Unit::ANIM_NAME_KNOCK, 5) == 0 )
	{
		mPriority = 40;
	}
	else if (strncmp(mName, Unit::ANIM_NAME_FLOAT, 5) == 0 )
	{
		mPriority = 41;
		//mPriority = 60;
	}
	else if (strncmp(mName, Unit::ANIM_NAME_DEAD, 5) == 0 )
	{
		mPriority = 50;
	}
}

ControlToken::~ControlToken()
{
	TryRecycleFunction(OnTick);
}

SharedPtr<ControlToken> ControlToken::Create(ControlledType const aType, const IFunctionContainer<bool, int>* aFunc, const char* aAnimName)
{
    auto state = SharedPool<ControlToken>::Get();
    state->mType = aType;
    state->mIsValid = false;
    state->mName = aAnimName;
    state->OnTick = aFunc;
    state->CalculatePriority();
	state->mReplayable = false;
	state->mStartTime = 0;
	state->mTimeOut = 0;  //anim Float does not has duration 
	if (strncmp(aAnimName, Unit::ANIM_NAME_HIT_PREFIX, 3) == 0 ||
		strncmp(aAnimName, Unit::ANIM_NAME_KNOCK_PREFIX, 5) == 0)
	{
		state->mReplayable = true;
	}
    return state;
}

DieCause::DieCause(EUnitDieCause aCause)
{
	cause = aCause;
	rageBonus = 0;
	data = 0;
}

void DieCause::Reset()
{
	cause = EUnitDieCause::Invalid;
	animName = nullptr;
	moveConf.clear();
	data = 0;
}

// init Unit's environmental related settings, like Physical param, self restriction and mFsm, mArmy etc.
void Unit::InitFields(Army& aArmy, BattleViewOutput& aView, PhysicsSystem& aPhysics)
{
    mUnitTime = 0;
    mActionSpeedFactor = 0;
	mRealSpeedFactor = 0;
    mFallSpeed = 0;
    mArmy = &aArmy;
	mArmyId = mArmy->GetId();
    mTimedLife = nullptr;
    mBeHitTimer = nullptr;
	mClearOnCutscene = false;
    mNormalAtkNum = 0;
    mTauntedTargetBuffId = 0;
    mRageSkillManualReady = false;
	mUnparalleledSkillReady = false;
    mFloatWithoutBeingMoved = false;
	mRageSkillStatus = RageSkillStatus::RageNotReady;
	mUnparallelSkillStatus = RageSkillStatus::RageNotReady;
    mDamageInTotal = 0;
	mDamageInWithOverflow = 0;
    mDamageOutTotal = 0;
	mHealOutTotal = 0;
	mView = &aView;
    InitEntity(aView, aPhysics, GetBattleInstance().GetPathMgr());
    InitPhysics();
	mStateAdjustPropertyArr = vector<int>(static_cast<int>(StateAdjust::_Count)); 
	fill(mStateAdjustPropertyArr.begin(), mStateAdjustPropertyArr.end(), 0); 
    if (!mFsm)
    {
        mFsmName = string(FSM_NAME) + to_string((int)mEntityId);
        mFsm = SharedPtr<Fsm>(new Fsm(mFsmName.c_str()));
		mTimerMgr = SharedPtr<TimerMgr>(new TimerMgr(16));
		mBuffMgr = SharedPtr<BuffMgr>(new BuffMgr(SharedFromThis(), *mView));
        mImmueBuffArr = vector<pair<int, int>>(0);
		mImmuePropertyArr.resize(static_cast<int>(EAttribute::_Count), 0);
        mImmueBuffTypeArr.resize(static_cast<int>(BuffType::_Count), 0);
        mImmueBuffSubTypeArr.resize(static_cast<int>(BuffSubType::_Count), 0);
        mImmueSkillArr = vector<pair<int, int>>(0);
		mTextShiftCounter = vector<pair<int, int>>(0);
		mTextShiftSkill = vector<int>(0);
        mImmueSkillTypeArr.resize(static_cast<int>(ESkillMainType_Count), 0);
		mTableChgDataByBuffSub = vector<ChangeDataByBuffSub*>(0);
		InitFsm();
    }
	if (IsDummy())
	{
		IncStateAdjust(StateAdjust::InvisibleDummy);
	}
	
}

void Unit::Born()
{
	if (!mIsBorn)
		mStateIdle->SetOnEnter(MakeFunction<>(*this, &Unit::ActionEnterBorn));
	mIsBorn = true;
	if (!mFsm->IsInState(mStateBehaviour->GetId()))
		mFsm->DoTransition(mTransResetToIdle);
}

bool Unit::hasBorn()
{
	return mIsBorn;
}
void Unit::OnDelete()
{
	mIsDeleted = true;
}
bool Unit::HasDeleted()
{
	return mIsDeleted;
}

SharedPtr<ControlToken> Unit::GetControlToken(const char* aAnimName)
{
	for (auto token : mControlTokens)
	{
		if (token->mName == aAnimName)
		{
			return token;
		}
	}
	auto token = ControlToken::Create(ControlledType::MoveBySkill, nullptr, aAnimName);
	mControlTokens.emplace_back(token);
	return token;
}

int Unit::GetTimeLengthByAnimName(const char* aAnimName)
{
	if (aAnimName == ANIM_NAME_HIT)
	{
		return mHitTimeLength;
	}
	if (aAnimName == ANIM_NAME_DOWN)
	{
		return mDownTimeLength;
	}
	if (aAnimName == ANIM_NAME_DOWN_2)
	{
		return mDownTimeLength2;
	}
	if (aAnimName == ANIM_NAME_KNOCK)
	{
		return mKnockTimeLength;
	}
	if (aAnimName == ANIM_NAME_KNOCK_2)
	{
		return mKnockTimeLength2;
	}
	return 0;
}

const char* Unit::GetAnimNameByConf(const char* aAnimName)
{
	if (strncmp(aAnimName, ANIM_NAME_HIT_PREFIX, 3) == 0)
	{
		return ANIM_NAME_HIT;
	}
	else if (strncmp(aAnimName, ANIM_NAME_DOWN_PREFIX, 4) == 0)
	{
		if (strncmp(aAnimName, ANIM_NAME_DOWN, 7) == 0)
		{
			return ANIM_NAME_DOWN;
		}
		else if(strncmp(aAnimName, ANIM_NAME_DOWN_2, 7) == 0)
		{
			return ANIM_NAME_DOWN_2; 
		}
		else
		{
			return ANIM_NAME_DOWN;
		}
	}
	else if (strncmp(aAnimName, ANIM_NAME_KNOCK_PREFIX, 5) == 0)
	{
		if (strncmp(aAnimName, ANIM_NAME_KNOCK, 5) == 0)
		{
			return ANIM_NAME_KNOCK;
		}
		else if (strncmp(aAnimName, ANIM_NAME_KNOCK_2, 8) == 0)
		{
			return ANIM_NAME_KNOCK_2;
		}
		else
		{
			return ANIM_NAME_KNOCK; 
		}
	}
	else if (strncmp(aAnimName, ANIM_NAME_FLOAT, 8) == 0)
	{
		return ANIM_NAME_FLOAT;
	}
	else if (strncmp(aAnimName, ANIM_NAME_FLOAT_2, 8) == 0)
	{
		return ANIM_NAME_FLOAT_2;
	}
	else if (strncmp(aAnimName, ANIM_NAME_IDLE, 4) == 0)
	{
		return ANIM_NAME_IDLE;
	}
	LOG_DEBUG("no matching anim name from given %s", aAnimName);
	return ANIM_NAME_IDLE;
}

void Unit::InitPhysics()
{
    if (mConfig->GetIgnoreCollision() == 0)
    {
        mAgent = mPhysics->AddAgent(SharedFromThis(), EBVTypeCylinder, PHYSICS_GROUP_UNIT);
        auto* bv = mAgent->GetBV();
        mBV = static_cast<Cylinder*>(bv);
    }
}

// general Init entry, use pb::Args info to set base data of this Unit, then InitFields and InitAvatar
void Unit::Init(const TUnitInfo& aUnitInfo, Army& aArmy, BattleViewOutput& aView, PhysicsSystem& aPhysics, int aBornPoint)
{
    mInfo = &aUnitInfo;
    mTplId = aUnitInfo.htid();
	mHid = aUnitInfo.hid();
    mLevel = aUnitInfo.level();
	mStar = aUnitInfo.star();
	mBornPoint = aBornPoint;

	mArmy = &aArmy;
	mArmyId = mArmy->GetId();

	mBaseSizeScale = aUnitInfo.basesizescale() > 0 ? aUnitInfo.basesizescale() : DENOM;
	mIsPVP = !aArmy.GetBattleInstance().IsPVE();
	mIsDeleted = false;
	mRecoveryTime = 0;
	mIsBorn = false;
	mProvideKillRage = true;
	mIsMale = true;
	mFirstHitDone = false;
	mDieCause.Reset();
	mCurrentAnimLength = 0;
	mCurrentAnimStartTime = 0;
	mCurrentAnimName = ANIM_NAME_IDLE;
	mChainSkillIndex = 0;
	if (aUnitInfo.has_advlv())
		mAdvLevel = aUnitInfo.advlv();
	else
		mAdvLevel = 0;

	mBeControlledStack = vector<ControlToken*>(0);
	mShapeShiftStack.clear();
	mView = nullptr;
    LoadConfig(mTplId);
	InitAvatar();
	InitFields(aArmy, aView, aPhysics);
	LoadSkill(aUnitInfo);	

	//LOG_WARN("init unit %d", GetEntityId());

    if (aUnitInfo.has_curhp())
        mHp = aUnitInfo.curhp();
    if (aUnitInfo.has_currage())
        mRage = aUnitInfo.currage();

	if (mHp > mMaxHp)
	{
		LOG_WARN("Invalid mHp %d for TplId %d, > mMaxHp %d", mHp, mTplId, mMaxHp);
		mHp = mMaxHp;
	}

	//LoadSlgAttr(aUnitInfo);

	CheckRageSkill();	//TODO: Delete it in all cases 

	LOG_DEBUG("Unit %d created from TUnitInfo. {tplId=%d name=%s skills=%d hp=%d}"
        , mEntityId
        , mTplId
        , mAvatarName->c_str()
        , mSkillArr.size()
        , mHp);
}

// overloading of origin Init method, not using pb::aArgs but a list of base info params
void Unit::Init(int const aTplId, int const aLevel, int aSkillLevel, int aAdvLv, int const aBornPoint, Army& aArmy, BattleViewOutput& aView, PhysicsSystem& aPhysics, const vector<int>& aSkillList)
{
    mTplId = aTplId;
    mLevel = aLevel;
	mStar = 0;
    mBornPoint = aBornPoint;
	mBaseSizeScale = DENOM;
	mArmy = &aArmy;
	mArmyId = mArmy->GetId();
	mIsPVP = !aArmy.GetBattleInstance().IsPVE();
	mDontInitToBornPos = false;
	mIsDeleted = false;
	mRecoveryTime = 0;
	mIsBorn = false;
	mProvideKillRage = true;
	mIsMale = true;
	mFirstHitDone = false;
	mDieCause.Reset();
	mCurrentAnimLength = 0;
	mCurrentAnimStartTime = 0;
	mCurrentAnimName = ANIM_NAME_IDLE;
	mChainSkillIndex = 0;
	mAdvLevel = aAdvLv;
	mBeControlledStack = vector<ControlToken*>(0);
	mShapeShiftStack.clear();

    LoadConfig(mTplId);
	mBaseSizeScale = mConfig->GetHeroBattleZoom() > 0 ? mConfig->GetHeroBattleZoom() : mBaseSizeScale;
	InitAvatar();
    InitFields(aArmy, aView, aPhysics);
	if (aSkillList.empty())
		LoadSkill(aSkillLevel);
	else
		LoadSkill(aSkillList, aSkillLevel);

	//LOG_WARN("init unit %d", GetEntityId());
    
	LOG_DEBUG("Unit %d created from tplId. {tplId=%d name=%s skills=%d hp=%d}"
        , mEntityId
        , mTplId
        , mAvatarName->c_str()
        , mSkillArr.size()
        , mHp);
}

void Unit::InitDummy(Army& aArmy, BattleViewOutput& aView, PhysicsSystem& aPhysics)
{
	//this dummy unit is for summon position only
	mUnitTime = 0;
	mActionSpeedFactor = 0;
	mRealSpeedFactor = 0;
	mFallSpeed = 0;
	mTimedLife = nullptr;
	mBeHitTimer = nullptr;
	mClearOnCutscene = false;
	mNormalAtkNum = 0;
	mTauntedTargetBuffId = 0;
	mRageSkillManualReady = false;
	mUnparalleledSkillReady = false;
	mFloatWithoutBeingMoved = false;
	mRageSkillStatus = RageSkillStatus::RageNotReady;
	mUnparallelSkillStatus = RageSkillStatus::RageNotReady;
	mProvideKillRage = false;
	mIsMale = true;
	mFirstHitDone = true;
	mBornPoint = 1;
	mBaseSizeScale = DENOM;
	mIsPVP = !aArmy.GetBattleInstance().IsPVE();
	mDontInitToBornPos = false;
	mRecoveryTime = 0;
	mIsBorn = true;
	mDieCause.Reset();
	mCurrentAnimLength = 0;
	mCurrentAnimStartTime = 0;
	mCurrentAnimName = ANIM_NAME_IDLE;
	mChainSkillIndex = 0;

	InitEntity(aView, aPhysics);
	mLevel = 1;
	mStar = 0;
	mTplId = -1;  //denotes it's special dummy
	mCountry = ECountry::None;
	mAdvLevel = 0;
	mArmy = &aArmy;
	mArmyId = mArmy->GetId();
	mIsDummy = true;
	mIsDeleted = false;
	mDieCause.Reset();
	mAttrArr.resize(static_cast<int>(EAttribute::_Count), 0);
	mStateAdjustPropertyArr = vector<int>(static_cast<int>(StateAdjust::_Count));
	fill(mAttrArr.begin(), mAttrArr.end(), 0);
	fill(mStateAdjustPropertyArr.begin(), mStateAdjustPropertyArr.end(), 0);
	
	mFsmName = string(FSM_NAME) + to_string((int)mEntityId) + to_string((int)mArmy->GetId());
	mFsm = SharedPtr<Fsm>(new Fsm(mFsmName.c_str()));
	mTimerMgr = SharedPtr<TimerMgr>(new TimerMgr(16));
	mBuffMgr = SharedPtr<BuffMgr>(new BuffMgr(SharedFromThis(), *mView));
	mImmueBuffArr = vector<pair<int, int>>(0);
	mImmuePropertyArr.resize(static_cast<int>(EAttribute::_Count), 0);
	mImmueBuffTypeArr.resize(static_cast<int>(BuffType::_Count), 0);
	mImmueBuffSubTypeArr.resize(static_cast<int>(BuffSubType::_Count), 0);
	mImmueSkillArr = vector<pair<int, int>>(0);
	mTextShiftCounter = vector<pair<int, int>>(0);
	mTextShiftSkill = vector<int>(0);
	mTableChgDataByBuffSub = vector<ChangeDataByBuffSub*>(0);
	mImmueSkillTypeArr.resize(static_cast<int>(ESkillMainType_Count), 0);
	mBeControlledStack = vector<ControlToken*>(0);
	mShapeShiftStack.clear();
	InitFsm();
	IncStateAdjust(StateAdjust::InvisibleDummy);
	
}

void Unit::AddViewEntity(int aBornPointIndex, int const aShowOnUI, int const aIsBoss, int const aParent)
{	
	int isSummoned = 0;
	if (IsSummoned())
	{
		isSummoned = 1;
	}
	int skillId = 0;
	if (mAncestorSkill)
	{
		skillId = mAncestorSkill->GetId();
	}
    mView->Execute(ViewCommand::AddAvatar, mEntityId, mTplId, mArmy->GetId(), mHp, mMaxHp, mRage, mRageSkillThreshold, aBornPointIndex, mSpeed, mBaseSizeScale, aShowOnUI, aIsBoss, isSummoned, aParent, skillId, mHid);
}

void Unit::UnRegisterAllEvents()
{
	for (auto& skill : mTriggerSkillArr)
	{
		skill->UnRegisterListener();
	}
}

void Unit::Reset()
{
	mIsDeleted = false;
    if (mArmy == nullptr)
    {
        //LOG_DEBUG("unit:%d tpl:%d already reset", mEntityId, mTplId);
        return;
    }
    mArmy = nullptr;
	mArmyId = 0;
    mSummoner = nullptr;
	ClearConditionChangeArr();
	ClearChgDataByBuffSubArr();
    if (mTimedLife)
    {
        mTimedLife = nullptr;
        ClearView();
    }
    if (mAgent)
    {
        mPhysics->RemoveAgent(mAgent);
        mBV = nullptr;
        mAgent = nullptr;
    }
	if (mKiller)
	{
		mKiller = nullptr;
	}
	if (mBehaviourSkill)
		mBehaviourSkill.Release();
    if (mBeHitTimer)
		mBeHitTimer.Release();
	if (mLastNormalTarget)
		mLastNormalTarget.Release();
	if (mLastRefTarget)
		mLastRefTarget.Release();
	if (mSkillSourceUtilizer)
		mSkillSourceUtilizer.Release();

	mLevel = 0;  
	mStar = 0;
	mMaxHpOrig = 0;  
	mMaxHpDeltaSum = 0;
	mRageSkillThreshold = 0; 
	mMaxRage = 0;
	mDieCause.Reset();
	mOverlap = false;
	mUnitTime = 0; 
	mActionSpeedFactor = 0;
	mRealSpeedFactor = 0;

	mNoTargetCounter = 0;
	mKillNum = 0;

	mBornPoint = 0;
	mIsDummy = false;
	mIsBorn = false;
	mDontInitToBornPos = false;

	mFallSpeed = 0;
	mFloatWithoutBeingMoved = false; 
	mRecoveryTime = 0;
	mClearOnCutscene = false;

	mProvideKillRage = false;

    mSkillArr.clear();
	mRandomNormalSkillArr.clear();
	mChainSkillArr.clear();
	mChainSkillOrder.clear();
    mTriggerSkillArr.clear();
	mTriggerOnHpSkillArr.clear(); 
	if (mRageSkill)
		mRageSkill.Release();
    mRageSkillArr.clear();
	if (mCurSkill)
		mCurSkill.Release();
	if(mChoosedSkill)
		mChoosedSkill.Release();
	if(mCurSkillExecutor)
		mCurSkillExecutor.Release();
	if(mUnparalleledSkill)
		mUnparalleledSkill.Release();

    mFsm.Release();
    mTimerMgr.Release();
    mBuffMgr.Release();
    fill(mAttrArr.begin(), mAttrArr.end(), 0);
    mSkillExecutorArr.clear();
    mSceneBarrierArr.clear();
    mCurSkillExecutor.Release();
    TryRecycleFunction(mOnMoveBySkillCancel);
    mImmueBuffArr.clear();
    mImmueSkillArr.clear();
	mTextShiftCounter.clear();
	mTextShiftSkill.clear();
	mImmueBuffSubTypeArr.clear();
	mImmuePropertyArr.clear();
	mImmueBuffTypeArr.clear();
    mControlTokens.clear();
    mControlStateByHitArr.clear();
	mImmueSkillTypeArr.clear();
	mOverLapRefTarget.Reset();
	mSpecifyBeTargetSkillMap.clear();
    fill(mStateAdjustPropertyArr.begin(), mStateAdjustPropertyArr.end(), 0);
	SetRageSkillState(nullptr);
    ResetEntity();
	mAvatarConf = nullptr;
	mChainSkillIndex = 0;
	mPosType = EPosType::None;
	mCountry = ECountry::None;
	mSkillIdSpecial = 0;
	mBeControlledStack.clear();
	mShapeShiftStack.clear();
	mDownTimeLength = 0;
	mDownTimeLength2 = 0;
	mHitTimeLength = 0;
	mKnockTimeLength = 0;
	mKnockTimeLength2 = 0;
	mRegister0 = 0;
	mRegister1 = 0;
	mTplId = 0;
	mHid = 0;
	mIsMale = false;
	mFirstHitDone = false;
	mLastCastRange = 0;
	mMaxHp = 0;
	mHp = 0;
	mRage = 0;
	mPhyicalShield = 0;
	mMagicalShield = 0;
	mUniversalShield = 0;
	mDamageInTotal = 0;
	mDamageInWithOverflow = 0;
	mDamageOutTotal = 0;
	mHealOutTotal = 0;
	mLastDir.Set(0, 0, 0);
	mNumOfAvoidOverlapMovement = 0;

	if (mAvatarName)
		mAvatarName.Release();
	mSocketBody.Set(0,0,0);  
	mHitPosition.Set(0, 0, 0);
	mBehaviourMoveTarget.Set(0, 0, 0);
	mBehaviourSpeed = 0;
	mBehaviourRange = 0;
	mBehaviourAnim = "";
	mBehaviourMark = false;
	mTauntedTargetBuffId = 0;
	mRageSkillExecuteState = nullptr;

	mUnparalleledSkillReady = false;
	mNormalAtkNum = 0;
	mNormalAtkNumBeforeChangeAvatar = 0;
	mRageSkillManualReady = false; 
	mRageSkillAutoReady = false;

	mAdvLevel = 0;

	mTotalPhycialDamage = 0;
	mTotalMagicalDamage = 0;
	mTotalHeal = 0;
	mPhycialDamageUndertake = 0;
	mMagicalDamageUndertake = 0;
	mSkillExecuteCount = 0;

	mProAttTalent = 100;
	mProDefTalent = 100;

	mDodgeCount = 0;
	mPhysicalBase = 0;
	mExemptionCount = 0;
	mMagicalBase = 0;
	mParryCount = 0;
	mResistCount = 0;
	mCriticalDamageCount = 0;
	mTotalDamageBase = 0;
	mCriticalHealCount = 0;
	mTotalHealBase = 0;
	mBeCriticalDamageCount = 0;
	mTotalBeDamageBase = 0;
	mTotalSuckBlood = 0;
	mRealHeal = 0;
	mTotalAbsorbBlood = 0;
	mAncestorSkill = nullptr;

	mConfig = nullptr; 
	mInfo = nullptr;

	mBossDefActive = false;
	mDefPointNum = 0;
	mDefType = 0;
	mTTL = 0;
	mLastAppliedSpeedFactor = SPEED_FACTOR_BASE;
	mBuffSkillStatistics.clear();
	mBeanReceiverList.clear();
	mIsEnemyMelee = 0;
	mTimeWhenDead = 0;
	mExtraCastRange = 0;
	mDeadStateId = 0;

	mAbleToChooseSkill = false;
}


const vector<vector<int64>>& Unit::getChainListConf(int aIndex)
{
	auto heroConf = ConfigMgr::GetConfById<ConfigHero>(mTplId);
	switch (aIndex)
	{
	case 0:
		return heroConf->GetChainSkillList();
	case 1:
		return heroConf->GetTDChainSkillList1();
	case 2:
		return heroConf->GetTDChainSkillList2();
	default:
		return heroConf->GetChainSkillList();
	}
}


void Unit::LoadChainSkillOrder(int aIndex)
{
	mChainSkillOrder.clear();
	auto& chainList = getChainListConf(aIndex);

	if (chainList.size() == 0)
		LOG_FATAL("empty chain list for tplid=%d", mTplId);
	int idx = 0;
	while (idx < chainList.size())
	{
		int confAdvLv = chainList[idx][0];
		if (confAdvLv == mAdvLevel)
			break;
		if (mAdvLevel < confAdvLv)
		{
			--idx;
			break;
		}
		else
			++idx;
	}
	if (idx == chainList.size())
		--idx;
	auto& subList = chainList[idx];
	idx = 1;
	for (int data : subList)
	{
		if (idx == 1)
		{
			idx++;
			continue;
		}
		if (data >= CHAIN_SKILL_NUM)
		{
			LOG_FATAL("invalid chain list elem, given mark = %d, maximum <= %d", data, CHAIN_SKILL_NUM);
		}
		mChainSkillOrder.emplace_back(data);
	}
	if (mChainSkillOrder.size() == 0)
		LOG_FATAL("chain skill order is empty for tplid = %d", mTplId);
}

// load skills from pb::aArgs
void Unit::LoadSkill(const TUnitInfo& aUnitInfo)
{
    int skillNum = aUnitInfo.skillarr_size();
	mSkillArr.clear();
    mSkillArr.reserve(skillNum);
	mChainSkillArr.clear();
	mChainSkillArr.resize(CHAIN_SKILL_NUM);
    for (int i = 0; i < skillNum; ++i)
    {
        auto skill = AddSkill(aUnitInfo.skillarr(i).id(), aUnitInfo.skillarr(i).level());
    }
    //mCurrentSkillNum = static_cast<int>(mSkillArr.size());
	LoadChainSkillOrder();
}

void Unit::LoadSkill(const vector<int>& aSkillList, int aLevel)
{
	mSkillArr.clear();
	mSkillArr.reserve(aSkillList.size());
	mChainSkillArr.clear();
	mChainSkillArr.resize(CHAIN_SKILL_NUM);
	for (int i = 0; i < aSkillList.size(); ++i)
	{
		AddSkill(aSkillList[i], aLevel);
	}
	//mCurrentSkillNum = static_cast<int>(aSkillList.size());
	LoadChainSkillOrder();
}

// load skills from conf
void Unit::LoadSkill(int const aLevel)
{
    auto& skills = mConfig->GetSkillID();
	mSkillArr.clear();
    mSkillArr.reserve(skills.size());
	mChainSkillArr.clear();
	mChainSkillArr.resize(CHAIN_SKILL_NUM);
    for (int i = 0; i < skills.size(); ++i)
    {
        AddSkill(skills[i], aLevel);
    }
	auto& addtionalSkills = mConfig->GetAddtionalSkill();
	for (int i = 0; i < addtionalSkills.size(); ++i)
	{
		//auto& tmp = addtionalSkills[i];
		for (auto val : addtionalSkills[i])
		{
			AddSkill(val, aLevel);
		}
	}
    //mCurrentSkillNum = static_cast<int>(skills.size());
	LoadChainSkillOrder();
}

void Unit::LoadAttr(const TUnitInfo& aUnitInfo)
{
	int size = static_cast<int>(EAttribute::_Count);
    mAttrArr.resize(size, 0);
    for (auto& attr : aUnitInfo.attrarr())
    {
		if (attr.id() < size)
		{
			mAttrArr[attr.id()] = attr.value();
		}
    }
}

void Unit::LoadAttr(int const aTplId, int const aLevel)
{
	LoadAttr(aTplId);
	auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(aTplId);
	auto* heroAttr = ConfigMgr::GetConfById<ConfigHeroAttribute>(heroConf->GetAttributeID());
	mAttrArr[static_cast<int>(EAttribute::HpBase)] += heroAttr->GetGrowHp() * aLevel;
	mAttrArr[static_cast<int>(EAttribute::PhysicalAtkBase)] += heroAttr->GetGrowPhysicalAttack() * aLevel;
	mAttrArr[static_cast<int>(EAttribute::PhysicalDefBase)] += heroAttr->GetGrowPhysicalDefend() * aLevel;
	mAttrArr[static_cast<int>(EAttribute::MagicAtkBase)] += heroAttr->GetGrowMagicAttack() * aLevel;
	mAttrArr[static_cast<int>(EAttribute::MagicDefBase)] += heroAttr->GetGrowMagicDefend() * aLevel;
}

// overloading, used for Summoned Units
void Unit::LoadAttr(int const aTplId)
{
	auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(aTplId);
	auto* heroAttr = ConfigMgr::GetConfById<ConfigHeroAttribute>(heroConf->GetAttributeID());
    mAttrArr.resize(static_cast<int>(EAttribute::_Count), 0);
    //TODO
	mAttrArr[static_cast<int>(EAttribute::Leadership)] = heroAttr->GetBaseCommand();
	mAttrArr[static_cast<int>(EAttribute::Force)] = heroAttr->GetBaseStrength();
	mAttrArr[static_cast<int>(EAttribute::Intelligence)] = heroAttr->GetBaseIntelligence();
	mAttrArr[static_cast<int>(EAttribute::Politics)] = heroAttr->GetBasePolity();
	mAttrArr[static_cast<int>(EAttribute::Charm)] = heroAttr->GetBaseFashion();
	mAttrArr[static_cast<int>(EAttribute::CriticalProb)] = heroAttr->GetBaseCritical();
	mAttrArr[static_cast<int>(EAttribute::PhysicalHitProb)] = heroAttr->GetBasePhysicalHit();
	mAttrArr[static_cast<int>(EAttribute::MagicHitProb)] = heroAttr->GetBaseMagicHit();
	mAttrArr[static_cast<int>(EAttribute::DodgeProb)] = heroAttr->GetBaseDodge();
	mAttrArr[static_cast<int>(EAttribute::ExemptionProb)] = heroAttr->GetExemption();
	mAttrArr[static_cast<int>(EAttribute::BlockProb)] = heroAttr->GetBaseBlock();
	mAttrArr[static_cast<int>(EAttribute::ResilienceProb)] = heroAttr->GetBaseToughness();
	mAttrArr[static_cast<int>(EAttribute::CriticalPercentAdd)] = heroAttr->GetBaseCriticalMultiple();
	mAttrArr[static_cast<int>(EAttribute::MoveSpeed)] = heroAttr->GetBaseSpeed();
	mAttrArr[static_cast<int>(EAttribute::HpBase)] = heroAttr->GetBaseHp();
	mAttrArr[static_cast<int>(EAttribute::PhysicalAtkBase)] = heroAttr->GetBasePhysicalAttack();
	mAttrArr[static_cast<int>(EAttribute::PhysicalDefBase)] = heroAttr->GetBasePhysicalDefend();
	mAttrArr[static_cast<int>(EAttribute::MagicAtkBase)] = heroAttr->GetBaseMagicAttack();
	mAttrArr[static_cast<int>(EAttribute::MagicDefBase)] = heroAttr->GetBaseMagicDefend();
	mAttrArr[static_cast<int>(EAttribute::PhysicalAtkTalent)] = heroAttr->GetPhysicalAttackTalent();
	mAttrArr[static_cast<int>(EAttribute::PhysicalDefTalent)] = heroAttr->GetPhysicalDefendTalent();
	mAttrArr[static_cast<int>(EAttribute::MagicAtkTalent)] = heroAttr->GetMagicAttackTalent();
	mAttrArr[static_cast<int>(EAttribute::MagicDefTalent)] = heroAttr->GetMagicDefendTalent();
	mAttrArr[static_cast<int>(EAttribute::UniversalHitProb)] = heroAttr->GetUniversalHitProb();
	mAttrArr[static_cast<int>(EAttribute::UniversalDodgeProb)] = heroAttr->GetUniversalDodgeProb();
	mAttrArr[static_cast<int>(EAttribute::UniversalBlockProb)] = heroAttr->GetUniversalBlockProb();
}

void Unit::LoadAttr(const vector<Unit*> aUnitList, int aPercent, int const aTplId)
{
	mAttrArr.resize(static_cast<int>(EAttribute::_Count), 0);
	int size = aUnitList.size();
	if (size <= 0)
	{
		LOG_WARN("Invalid UnitList Size == 0, battleId = %d", GetBattleInstance().mBattleId);
		return;
	}
	for (int i = 0; i < size; ++i)
	{
		Unit* aUnit = aUnitList[i];
		int64 maxAtk = 0;
		for (int a = 0; a < mAttrArr.size(); ++a)
		{
			EAttribute key = static_cast<EAttribute>(a);
			if (key == EAttribute::PhysicalAtkBase || key == EAttribute::MagicAtkBase)
			{
				int64 val = aUnit->mAttrArr[a] * aPercent / DENOM;
				if (maxAtk < val) 
					maxAtk = val;
			}
			else if (key == EAttribute::HpBase || key == EAttribute::PhysicalDefBase || key == EAttribute::MagicDefBase)
			{
				mAttrArr[a] += aUnit->mAttrArr[a] * aPercent / DENOM;
			}
			else
			{
				mAttrArr[a] += aUnit->mAttrArr[a];
			}
		}
		mAttrArr[static_cast<int>(EAttribute::PhysicalAtkBase)] += maxAtk;
		mAttrArr[static_cast<int>(EAttribute::MagicAtkBase)] += maxAtk;
	}
	for (int a = 0; a < mAttrArr.size(); ++a)
	{
		mAttrArr[a] = mAttrArr[a] / size;
	}

	if (aTplId == 0)
	{
		mAttrArr[static_cast<int>(EAttribute::MoveSpeed)] = 0;
		mProAttTalent = static_cast<int64>(10000);
		mProDefTalent = static_cast<int64>(10000);
		mAttrArr[static_cast<int>(EAttribute::PhysicalAtkTalent)] = DENOM * 2;
		mAttrArr[static_cast<int>(EAttribute::MagicAtkTalent)] = DENOM * 2;
	}
	else
	{
		auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(aTplId);
		auto* heroAttr = ConfigMgr::GetConfById<ConfigHeroAttribute>(heroConf->GetAttributeID());
		mAttrArr[static_cast<int>(EAttribute::MoveSpeed)] = heroAttr->GetBaseSpeed();
		mProAttTalent = static_cast<int64>(heroAttr->GetProAttTalent());
		mProDefTalent = static_cast<int64>(heroAttr->GetProDefTalent());
		mAttrArr[static_cast<int>(EAttribute::PhysicalAtkTalent)] = DENOM * 2;
		mAttrArr[static_cast<int>(EAttribute::MagicAtkTalent)] = DENOM * 2;
	}
}

void Unit::LoadAttr(const Unit* aUnit, int const aPercent, int const aTplId, bool aUseFixedRate)
{
	if (aUseFixedRate)
	{
		LoadAttr(aTplId);
	}
	else
	{
		mAttrArr.resize(static_cast<int>(EAttribute::_Count), 0);
	}
    for (int a = 0; a < mAttrArr.size(); ++a)
    {
		EAttribute key = static_cast<EAttribute>(a);
		if (key == EAttribute::HpBase || key == EAttribute::PhysicalAtkBase ||
			key == EAttribute::PhysicalDefBase || key == EAttribute::MagicAtkBase ||
			key == EAttribute::MagicDefBase)
		{
			mAttrArr[a] = aUnit->mAttrArr[a] * aPercent / DENOM;
		}
		else
		{
			if (!aUseFixedRate || (key != EAttribute::UniversalDodgeProb && key != EAttribute::UniversalBlockProb))
			{
				mAttrArr[a] = aUnit->mAttrArr[a];
			}
		}
    }
	auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(aTplId);
	auto* heroAttr = ConfigMgr::GetConfById<ConfigHeroAttribute>(heroConf->GetAttributeID());
	mAttrArr[static_cast<int>(EAttribute::MoveSpeed)] = heroAttr->GetBaseSpeed();
	mProAttTalent = static_cast<int64>(heroAttr->GetProAttTalent());
	mProDefTalent = static_cast<int64>(heroAttr->GetProDefTalent());
}

// init mHitTimeLength and mBaseSize
void Unit::InitAvatar()
{
	//mMeleeRingMgr = nullptr;
	mDownTimeLength = 0;
	mDownTimeLength2 = 0;
	mHitTimeLength = 0;
	mKnockTimeLength = 0;
	mKnockTimeLength2 = 0;
    auto& path = mConfig->GetAnimateResourcePath();
    auto lastSlash = path.find_last_of('/') + 1;
    constexpr int suffixLength = 7;//".prefab"
    mAvatarName = SharedPtr<string>(new string(path.substr(lastSlash, path.length() - lastSlash - suffixLength)));
    if (mAvatarName->compare(SUMMONED_DUMMY_NAME) != 0)
    {
		/*mMeleeRingMgr = SharedPool<MeleeRingMgr>::Get();
		mMeleeRingMgr->Init(this);*/
		mIsDummy = false;
        const auto& avatarConfArr = ConfigMgr::GetConfByIndex<AvatarData>(AVATAR_CONF_KEY, *mAvatarName);
        mAvatarConf = avatarConfArr[0];
        for (auto& anim : mAvatarConf->animdatas())
        {
            if (anim.animname().compare(0, 3, ANIM_NAME_HIT_PREFIX) == 0)
            {
                mHitTimeLength = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
            }
			else if (anim.animname().compare(0,4, ANIM_NAME_DOWN_PREFIX) == 0)
			{
				if (anim.animname().compare(0, 7, ANIM_NAME_DOWN) == 0)
					mDownTimeLength = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
				else if (anim.animname().compare(0, 7, ANIM_NAME_DOWN_2) == 0)
					mDownTimeLength2 = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
				else
					mDownTimeLength = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
			}
			else if (anim.animname().compare(0, 5, ANIM_NAME_KNOCK_PREFIX) == 0)
			{
				if (anim.animname().compare(0, 8, ANIM_NAME_KNOCK) == 0)
					mKnockTimeLength = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
				else if (anim.animname().compare(0, 8, ANIM_NAME_KNOCK_2) == 0)
					mKnockTimeLength2 = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
				else
					mKnockTimeLength = EDITOR_CONF_TIME_CONVERT(anim.animtimelength());
			}
			else if (anim.animname().compare(ANIM_NAME_IDLE) == 0)
			{  // try to get Unit's Socket pos at Body, it's used for the target of skill carrier
				for (auto& socketpos : anim.initsocketposition())
				{
					if (socketpos.socketname().compare(ANIM_SOCKET_BODY) == 0)
					{
						mSocketBody = Vector3();
						mSocketBody.x = EDITOR_CONF_POS_CONVERT(socketpos.position().x());
						mSocketBody.y = EDITOR_CONF_POS_CONVERT(socketpos.position().y());
						mSocketBody.z = EDITOR_CONF_POS_CONVERT(socketpos.position().z());
					}
				}
			}
        }
        if (mHitTimeLength <= 0)
        {
			LOG_WARN("Unit %d: invalid hit anim time length %d", mTplId, mHitTimeLength);
        }
    }
    else
    {     
		mSocketBody.Set(0, 0, 0);
		mIsDummy = true;
        mHitTimeLength = 0;
    }

	mPosType = static_cast<EPosType>(mConfig->GetPosType());

	auto* battleConf = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
	mBaseSizeScale = mBaseSizeScale * battleConf->GetZoomRole() / DENOM;
	mSizeScale = mBaseSizeScale;
    mBaseSize = CONF_POS_CONVERT(mConfig->GetBodySize());
    mSize = mBaseSize * mSizeScale / DENOM;
	mBehaviourMark = false;

	auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(mTplId);
	auto* heroAttr = ConfigMgr::GetConfById<ConfigHeroAttribute>(heroConf->GetAttributeID());
	mProAttTalent = static_cast<int64>(heroAttr->GetProAttTalent());
	mProDefTalent = static_cast<int64>(heroAttr->GetProDefTalent());
	mSpeed = CONF_VEL_CONVERT(heroAttr->GetBaseSpeed());

	if (!mIsDummy)
	{
		mCountry = static_cast<ECountry>(heroConf->GetNation());
	}

	mSkillIdSpecial = 0;

	mBossDefActive = false;
	mDefPointNum = 0;
	mDefType = -1;

	mLastAppliedSpeedFactor = SPEED_FACTOR_BASE;

}

Vector3 Unit::GetSocketPos(const char* aAnimName, const char* aSocketName) const
{
	if (mAvatarConf)
	{
		for (auto& anim : mAvatarConf->animdatas())
		{
			if (anim.animname().compare(aAnimName) == 0)
			{
				for (auto& socketpos : anim.initsocketposition())
				{
					if (socketpos.socketname().compare(aSocketName) == 0)
					{
						Vector3 pos = Vector3();
						int v = EDITOR_CONF_POS_CONVERT(socketpos.position().x());
						if (v > MIN_LEN)
						{
							Vector3 x = GetRight();
							x.ScaleToLen(v);
							pos += x;
						}
						v = EDITOR_CONF_POS_CONVERT(socketpos.position().z());//z axis is forward in models
						if (v > MIN_LEN)
						{
							Vector3 z = GetForward();
							z.ScaleToLen(v);
							pos += z;
						}
						pos.y = EDITOR_CONF_POS_CONVERT(socketpos.position().y());
						return pos;
					}
				}
			}
		}
	}
    
#ifdef DEBUG
    LOG_WARN("socket: %s in animation: %s tplId: %d not found!", aSocketName, aAnimName, mTplId);
#else
    LOG_DEBUG("socket: %s in animation: %s tplId: %d not found! use idle body socket instead", aSocketName, aAnimName, mTplId);
#endif
    return mSocketBody;
}

// init heroConf, set some base info of this Unit such as: mMaxHp, mHp, mRageSkillThreshold and so
void Unit::LoadConfig(int const aTplId)
{
    mConfig = ConfigMgr::GetConfById<ConfigHero>(aTplId);
	if (mConfig->GetGender() == 1)
		mIsMale = true;
	else
		mIsMale = false;

    auto* battleConf = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
	mMaxHp = CountMaxHpRPG();
    mHp = mMaxHp;
    mRageSkillThreshold = battleConf->GetRageSkillThreshold();
    mMaxRage = battleConf->GetMaxRage();
    mRage = 0;  //TODO
    //mSpeed = CONF_VEL_CONVERT(GetAttr(EAttribute::MoveSpeed));
    //if (mSpeed == 0) mSpeed = CONF_VEL_CONVERT(500);   //TODO compatability 
}

//retrun MaxHp from HpBase * HpPercent + HpFinal
//if PVP, also apply Hp Adjust 
int64 Unit::CountMaxHpRPG() const
{
	//int64 hp = static_cast<int64>(GetAttr(EAttribute::HpBase)) * (DENOM + GetAttr(EAttribute::HpPercent)) / DENOM + GetAttr(EAttribute::HpExtra);
	int64 hpbase = static_cast<int64>(GetAttr(EAttribute::HpBase));
	int64 hprate = DENOM + GetAttr(EAttribute::HpPercent);
	int64 hp = IncByRate(hpbase, hprate, DENOM) + GetAttr(EAttribute::HpExtra);
	return hp;
}

int64 Unit::CountMaxHpSLG() const
{
	return Sqrt(mTroopNum + slgCoef1) * CountMaxHpRPG() / slgCoef2;
}

int64 Unit::CountSoldierHpSLG() const
{
	return CountMaxHpSLG() / mTroopNum;
}

//test all rage skills, try return a valid one or nullptr
SharedPtr<Skill> Unit::GetRageSkill()
{
	if (mRageSkillArr.empty())
	{
		LOG_DEBUG("Unit %d not found Rage skill", mEntityId);
		return nullptr;
	}
	mRageSkill = nullptr;
	if (mRageSkillArr.size() == 1)
	{
		if (mRageSkillArr[0]->CanExecute() == CheckResult::Pass
			&& mRageSkillArr[0]->RefreshRefTarget()
			&& mRageSkillArr[0]->HasRefTarget())
		{
			mRageSkill = mRageSkillArr[0];
			return mRageSkill;
		}
	}
	else
	{
		for (auto skill : mRageSkillArr) //mRageSkillArr is sorted already
		{
			if (skill->CanExecute() == CheckResult::Pass
				&& skill->RefreshRefTarget()
				&& skill->HasRefTarget())
			{
				mRageSkill = skill;
				return mRageSkill;  //return first founded skill
			}
		}
	}

	return mRageSkill;
}

void Unit::TryCleanUpWarRiderRelatedSkills()
{
	vector<int> tmp;
	for (size_t i = 0; i < mSkillArr.size(); ++i)
	{
		if (mSkillArr[i]->mWarRiderRelated)
		{
			tmp.emplace_back(mSkillArr[i]->GetId());
		}
	}
	for (auto sid : tmp)
	{
		RemoveSkill(sid);
	}
}

//Only buff mod "add skill" will invoke this call 
void Unit::RemoveSkill(int const aSkillId)
{
	SharedPtr<Skill> skill;
	for (size_t i = 0; i < mSkillArr.size(); ++i)
	{
		if (aSkillId == mSkillArr[i]->GetId())
		{
			skill = mSkillArr[i];
			break;
		}
	}
	if (!skill)
	{
		LOG_DEBUG("try to remove an non-existing skill:%d", aSkillId);
		return;
	}
	auto type = skill->GetSkillConf()->basedata().skillcasttype().casttype();
	switch (static_cast<ECastType>(type))
	{
	case ECastType::NormalAtk:
	case ECastType::NormalAtkSpecial:
	{
		int mark = static_cast<int>(skill->GetSkillConf()->basedata().chainskillmark());
		for (size_t i = 0; i < mSkillArr.size(); ++i)
		{
			if (aSkillId != mSkillArr[i]->GetId() 
				&& mSkillArr[i]->GetSkillConf()->basedata().skillcasttype().casttype() == type
				&& static_cast<int>(mSkillArr[i]->GetSkillConf()->basedata().chainskillmark()) == mark)
			{
				if (mark < CHAIN_SKILL_NUM)
				{
					mChainSkillArr[mark] = mSkillArr[i];
				}
				break;
			}
		}
		break;
	}
	case ECastType::RandomNormalAtk:
	{
		int p = mRandomNormalSkillArr.size();
		for (int idx = 0; idx < p; )
		{
			if (mRandomNormalSkillArr[idx]->GetId() == aSkillId)
			{
				p--;
				mRandomNormalSkillArr[idx] = mRandomNormalSkillArr[p];
			}
			else
			{
				idx++;
			}
		}
		mRandomNormalSkillArr.resize(p);
		break;
	}
	case ECastType::Rage:
	{
		auto it = mRageSkillArr.begin();
		for (; it != mRageSkillArr.end(); ++it)
		{
			if (it->Get()->GetId() == aSkillId)
			{
				break; 
			}
		}
		if (it != mRageSkillArr.end())
		{
			mRageSkillArr.erase(it);
		}
		break;
	}
	case ECastType::Unparalleled:
	{
		mUnparalleledSkill = nullptr;
		for (size_t i = 0; i < mSkillArr.size(); ++i)
		{
			if (aSkillId != mSkillArr[i]->GetId()
				&& mSkillArr[i]->GetSkillConf()->basedata().chainskillmark() == type)
			{
				mUnparalleledSkill = mSkillArr[i];
				break;
			}
		}
		break;
	}
	case ECastType::WithBuff:
	{
		break;
	}
	case ECastType::EventTrigger:
	{
		auto triggerType = skill->GetSkillConf()->basedata().skillcasttype().eventmajor();
		switch (static_cast<ETriggerMajor>(triggerType))
		{
		case ETriggerMajor::Enter:
		case ETriggerMajor::Born:
		case ETriggerMajor::Death:
		case ETriggerMajor::Revive:
		case ETriggerMajor::AfterDmg:
		case ETriggerMajor::AfterHeal:
		case ETriggerMajor::AfterDodge:
		case ETriggerMajor::AfterImmune:
		case ETriggerMajor::AfterParry:
		case ETriggerMajor::AfterResist:
		case ETriggerMajor::BuffNumber:
		case ETriggerMajor::BeforeDeath:
		case ETriggerMajor::WhenApplyDamage:
		case ETriggerMajor::WithSkill:
		case ETriggerMajor::WhenMatchRecordValue:
		case ETriggerMajor::AfterKill:
		case ETriggerMajor::AfterShield:
		case ETriggerMajor::AfterCritical:
		case ETriggerMajor::AfterBeCritical:
		case ETriggerMajor::AfterInterrupt:
		case ETriggerMajor::AfterDispelEnemyBuff:
		case ETriggerMajor::AfterHitHandlerMove:
		case ETriggerMajor::AfterBuffSubtype:
		case ETriggerMajor::AfterApplyUnlimitedShield:
		case ETriggerMajor::AfterSkillReflected:
		case ETriggerMajor::AfterRageSkill:
		case ETriggerMajor::SummonWithRefTarget:
		case ETriggerMajor::ReviveWithRefTarget:
		case ETriggerMajor::AfterSkillWithAnim:
		case ETriggerMajor::AfterRageSkillWithRefTarget:
		case ETriggerMajor::WhenFirstApplyDamage:
		case ETriggerMajor::OnCheckCountryHeroNumber:
		case ETriggerMajor::OnCHeckCountryHeroNumberRuntime:
		case ETriggerMajor::AfterSubRage:
		{
			int p = mTriggerSkillArr.size();
			for (int idx = 0; idx < p; )
			{
				if (mTriggerSkillArr[idx]->GetId() == aSkillId)
				{
					p--;
					mTriggerSkillArr[idx]->UnRegisterListener();
					mTriggerSkillArr[idx] = mTriggerSkillArr[p];
				}
				else
				{
					idx++;
				}
			}
			mTriggerSkillArr.resize(p);
			break;
			/*auto it = mTriggerSkillArr.begin();
			for (; it != mTriggerSkillArr.end(); ++it)
			{
				if ((*it)->GetId() == aSkillId)
				{
					(*it)->UnRegisterListener();
					it = mTriggerSkillArr.erase(it);
					if (it == mTriggerSkillArr.end())
						break;
				}
			}
			break;*/
		}
		}
	}
	}
}

SharedPtr<Skill> Unit::AddSkill(int const aSkillId, int const aLevel)
{
	SharedPtr<Skill> skill;
    for (size_t i = 0; i < mSkillArr.size(); ++i)
    {
        if (aSkillId == mSkillArr[i]->GetId())
        {
            LOG_DEBUG("already has skill:%d", aSkillId);
			skill = mSkillArr[i];
			break;
        }
    }
	if (!skill)
	{
		skill = SharedPool<Skill>::Get();
		skill->Init(SharedFromThis(), aSkillId, aLevel);
		mSkillArr.emplace_back(skill);
	}

	auto type = skill->GetSkillConf()->basedata().skillcasttype().casttype();
    switch (static_cast<ECastType>(type))
    {
    case ECastType::NormalAtk:
    case ECastType::NormalAtkSpecial:
		{
			int mark = static_cast<int>(skill->GetSkillConf()->basedata().chainskillmark());
			if (mark >= CHAIN_SKILL_NUM)
			{
				LOG_FATAL("skill %d has invalid mark num = %d, maximum num <= %d", aSkillId, mark, CHAIN_SKILL_NUM);
			}
			mChainSkillArr[mark] = skill;  //inject the skill to its place 
		}
        break;
	case ECastType::RandomNormalAtk:
	{
		mRandomNormalSkillArr.emplace_back(skill);
	}
	break;
    case ECastType::Rage:
		{//insert based on priority
			auto it = mRageSkillArr.begin();
			for (; it != mRageSkillArr.end(); ++it)
			{
				if (it->Get()->GetPriority() < skill->GetPriority())
				{
					break;  //break when meet first lower-rank Rage skill
				}
			}
			mRageSkillArr.insert(it, skill);
		}
        break;
	case ECastType::Unparalleled:
		mUnparalleledSkill = skill;
		break;
	case ECastType::WithBuff:
	{
		LOG_DEBUG("should not add buff-triggered-skill %d here", skill->GetSkillConf()->id());
	}
	break;
	case ECastType::EventTrigger:
	{
		auto eventType = skill->GetSkillConf()->basedata().skillcasttype().eventmajor();
		switch (static_cast<ETriggerMajor>(eventType))
		{
		case ETriggerMajor::Enter:
		case ETriggerMajor::Born:
		case ETriggerMajor::Death:
		case ETriggerMajor::Revive:
		case ETriggerMajor::AfterDmg:
		case ETriggerMajor::AfterHeal:
		case ETriggerMajor::AfterDodge:
		case ETriggerMajor::AfterImmune:
		case ETriggerMajor::AfterParry:
		case ETriggerMajor::AfterResist:
		case ETriggerMajor::BuffNumber:
		case ETriggerMajor::BeforeDeath:
		case ETriggerMajor::WhenApplyDamage:
		case ETriggerMajor::WithSkill:
		case ETriggerMajor::WhenMatchRecordValue:
		case ETriggerMajor::AfterKill:
		case ETriggerMajor::AfterShield:
		case ETriggerMajor::AfterCritical:
		case ETriggerMajor::AfterBeCritical:
		case ETriggerMajor::AfterInterrupt:
		case ETriggerMajor::AfterDispelEnemyBuff:
		case ETriggerMajor::AfterHitHandlerMove:
		case ETriggerMajor::AfterBuffSubtype:
		case ETriggerMajor::AfterApplyUnlimitedShield:
		case ETriggerMajor::AfterSkillReflected:
		case ETriggerMajor::AfterRageSkill:
		case ETriggerMajor::SummonWithRefTarget:
		case ETriggerMajor::ReviveWithRefTarget:
		case ETriggerMajor::AfterSkillWithAnim:
		case ETriggerMajor::AfterRageSkillWithRefTarget:
		case ETriggerMajor::WhenFirstApplyDamage:
		case ETriggerMajor::OnCheckCountryHeroNumber:
		case ETriggerMajor::OnCHeckCountryHeroNumberRuntime:
		case ETriggerMajor::AfterSubRage:
		{
			mTriggerSkillArr.emplace_back(skill);
			skill->RegisterListener();
		}
		break;
		}
	}
	break;
    }
	return skill;
}

bool Unit::ActionTickIdle(int)
{
	//TODO1 检测当前位置和上一次位置 
	//TODO2 确保完成了所有的SkillRecovery 
	return mAbleToChooseSkill;
}

void Unit::InitFsmCommon()
{
	//todo del semi_auto skill logic 
	//States
	mStateIdle = mFsm->AddState(STATE_IDLE);	//Idle 
	mStateIdle->SetOnTick(MakeFunction<>(*this, &Unit::ActionTickIdle));

	//Player 需要确保: 1)技能可达目标, 2)如果有问题，直接调用ANY->IDLE归位 
	mStateChooseSkill = mFsm->AddState(STATE_CHOOSESKILL);	//Choose skill
	mStateChooseSkill->SetOnTick(MakeFunction<>(*this, &Unit::ActionChooseSkill));

	mStateMoveToRef = mFsm->AddState(STATE_MOVETONEAREST_REFTARGET);  //Move2Ref 
	mStateMoveToRef->SetOnTick(MakeFunction<>(*this, &Unit::ActionMoveToRefTarget));
	mStateMoveToRef->SetOnExit(MakeFunction<>(*this, &Unit::ActionExitMoveToRefTarget));

	mStateExecuteSkill = mFsm->AddState(STATE_EXECUTESKILL);	//Execute skill
	mStateExecuteSkill->SetOnEnter(MakeFunction<>(*this, &Unit::ActionExecuteSkill));
	mStateExecuteSkill->SetOnExit(MakeFunction<>(*this, &Unit::ActionExitExecuteSkill));

	mStateSkillRecovery = mFsm->AddState(STATE_SKILLRECOVERY);	//Recovery skill
	mStateSkillRecovery->SetOnEnter(MakeFunction<>(*this, &Unit::ActionEnterSkillRecovery));
	mStateSkillRecovery->SetOnTick(MakeFunction<>(*this, &Unit::ActionTickSkillRecovery));
	mStateSkillRecovery->SetOnExit(MakeFunction<>(*this, &Unit::ActionExitSkillRecovery));

	mStateBeControlled = mFsm->AddState(STATE_BECONTROLLED);	//Be Controlled
	mStateBeControlled->SetOnTick(MakeFunction<>(*this, &Unit::ActionTickBeControlled));

	mStateDying = mFsm->AddState(STATE_DYING);	//Dying 
	mStateDying->SetOnEnter(MakeFunction<>(*this, &Unit::ActionEnterDying));
	mStateDying->SetOnTick(MakeFunction<>(*this, &Unit::ActionTickDying));

	mStateDead = mFsm->AddState(STATE_DEAD);	//Dead
	mStateDead->SetOnEnter(MakeFunction<>(*this, &Unit::ActionEnterDead));
	mStateDead->SetOnTick(MakeFunction<>(*this, &Unit::ActionTickDead));

	mRevive = mFsm->AddState(STATE_REVIVE);		//Revive
	mRevive->SetOnEnter(MakeFunction<>(*this, &Unit::ActionEnterRevive));

	mStateBehaviour = mFsm->AddState(STATE_BEHAVIOUR);	//Behaviour

	mDeadStateId = mStateDead->GetId();
}

void Unit::LinkFsmCommon()
{
	//Start -> Idle (Auto)
	mFsm->AddTransition(mFsm->GetStartState(), *mStateIdle, TransitionMode::Auto);
	//Idle -> ChooseSkl (AfterActionDone)
	mFsm->AddTransition(*mStateIdle, *mStateChooseSkill, TransitionMode::AfterActionDone);

	//ExecuteSkl -> SkillRecovery (Manual) 当技能执行完毕（失败或成功时） 
	mTransNoSkillToExecute = mFsm->AddTransition(*mStateExecuteSkill, *mStateSkillRecovery, TransitionMode::Manual);
	mTransSkillEnded = mFsm->AddTransition(*mStateExecuteSkill, *mStateSkillRecovery, TransitionMode::Manual);

	//Any -> ExecuteSkl (Manual) 行为导向 
	mTransToExecuteSkill = mFsm->AddTransition(mFsm->GetAnyState(), *mStateExecuteSkill, TransitionMode::Manual);
	//SkillRecovery -> Idle (AfterActionDone) 
	mFsm->AddTransition(*mStateSkillRecovery, *mStateIdle, TransitionMode::AfterActionDone);
	//Any -> BeControlled (Manual)
	mTransBeControlled = mFsm->AddTransition(mFsm->GetAnyState(), *mStateBeControlled, TransitionMode::Manual);
	//BeControlled -> Idle (Manual) 
	mTransBeControlledEnd = mFsm->AddTransition(*mStateBeControlled, *mStateIdle, TransitionMode::Manual);
	//Any -> Dying (Manual) 
	mTransDead = mFsm->AddTransition(mFsm->GetAnyState(), *mStateDying, TransitionMode::Manual);
	//Dying -> Dead (Manual) 
	mTransRealDead = mFsm->AddTransition(*mStateDying, *mStateDead, TransitionMode::Manual);
	//Any -> Dead (Manual) 行为导向 
	mTransAnyToDead = mFsm->AddTransition(mFsm->GetAnyState(), *mStateDead, TransitionMode::Manual);
	//Dying -> Dead (AfterActionDone) 
	mFsm->AddTransition(*mStateDying, *mStateDead, TransitionMode::AfterActionDone);
	//Dead -> Revive (Manual) 
	mTransRevive = mFsm->AddTransition(*mStateDead, *mRevive, TransitionMode::Manual);
	//Revive -> Idle (Auto)
	mFsm->AddTransition(*mRevive, *mStateIdle, TransitionMode::Auto);
	//Any -> Behaviour (Manual) 
	mTransBehaviour = mFsm->AddTransition(mFsm->GetAnyState(), *mStateBehaviour, TransitionMode::Manual);
	//Behaviour -> Idle (AfterActionDone)
	mFsm->AddTransition(*mStateBehaviour, *mStateIdle, TransitionMode::AfterActionDone);
	//Behaviour -> Idle (Manual) 
	mTransBehaviourToIdle = mFsm->AddTransition(*mStateBehaviour, *mStateIdle, TransitionMode::Manual);
	//Any -> Idle (Manual) 切换场景用 
	mTransCutscene = mFsm->AddTransition(mFsm->GetAnyState(), *mStateIdle, TransitionMode::Manual);
	//Any -> Idle (Manual) 备用  
	mTransResetToIdle = mFsm->AddTransition(mFsm->GetAnyState(), *mStateIdle, TransitionMode::Manual);
}

void Unit::InitPlayerFsm()
{
	mUnitType = UnitType::Player; //这个在一早要找地方赋值 

	InitFsmCommon();

	//Transitions
	LinkFsmCommon();
	//ChooseSkl -> ExecuteSkl (AfterActionDone)
	mTransChooseToExecute = mFsm->AddTransition(*mStateChooseSkill, *mStateExecuteSkill, TransitionMode::Auto);
	mTransChooseToExecute->SetCondition(MakeFunction<>(*this, &Unit::CondiTargetInRange));
	
	//Any -> Move2Ref (Manual) 行为导向 -> 强制执行技能专用 
	mTransMoveToRefTarget = mFsm->AddTransition(mFsm->GetAnyState(), *mStateMoveToRef, TransitionMode::Manual);
	
	//Move2Ref -> ExecuteSkl (AfterActionDone)
	mFsm->AddTransition(*mStateMoveToRef, *mStateExecuteSkill, TransitionMode::AfterActionDone);
	
}

void Unit::InitFsm()
{
	mUnitType = UnitType::Monster; //这个在一早要找地方赋值 

	InitFsmCommon();

	//Transitions
	LinkFsmCommon();
	//ChooseSkl -> Move2Ref (Auto) with condition 
	mTransAutoMoveToRefTarget = mFsm->AddTransition(*mStateChooseSkill, *mStateMoveToRef, TransitionMode::Auto);
	mTransAutoMoveToRefTarget->SetCondition(MakeFunction<>(*this, &Unit::CondiTargetOutOfRange));
	//ChooseSkl -> ExecuteSkl (AfterActionDone)
	mTransChooseToExecute = mFsm->AddTransition(*mStateChooseSkill, *mStateExecuteSkill, TransitionMode::Auto);
	mTransChooseToExecute->SetCondition(MakeFunction<>(*this, &Unit::CondiTargetInRange));

	//Any -> Move2Ref (Manual) 行为强制执行技能专用
	mTransMoveToRefTarget = mFsm->AddTransition(mFsm->GetAnyState(), *mStateMoveToRef, TransitionMode::Manual);
	//Move2Ref -> ExecuteSkl (AfterActionDone)
	mFsm->AddTransition(*mStateMoveToRef, *mStateExecuteSkill, TransitionMode::AfterActionDone);
}


bool Unit::CondiDying(bool aIsDone)
{
	if (!aIsDone)
	{
		return false;
	}
	if (mHp <= 0)
	{
		mHp = 0;
		return true;
	}
	return false;
}

bool Unit::CondiTargetInRange(bool aIsDone)
{
	if (!aIsDone)
	{
		return false;
	}
	if (mChoosedSkill)
	{
		return mChoosedSkill->IsRefTargetInRange();
	}
	LOG_FATAL("after choose skill done, curSkill is nil");
	return false;
}

bool Unit::CondiTargetOutOfRange(bool aIsDone) 
{
	if (!aIsDone)
	{
		return false;
	}
	if (mChoosedSkill)
	{
		if (!mChoosedSkill->IsRefTargetInRange())
		{
			return true;
		}
		return false;
	}
	LOG_FATAL("after choose skill done, curSkill is nil");
	return false;
}


// OnTick Method of ChooseSkill State
// try to choose a valid skill as mCurSkill from chain skill list
bool Unit::ActionChooseSkill(int const aDeltaTime)
{
	if (CondiDying(true))
	{
		mFsm->DoTransition(mTransDead);
		return false;
	}
	if (mChoosedSkill)
	{
		mChoosedSkill.Release();
	}
    if (mSkillArr.size() == 0)
	{
		LOG_DEBUG("Unit %d has no skill to choose from! {state=%s}"
			, mEntityId
			, mFsm->GetCurrentState().GetName());
		return false;
	}
    mSkillSourceUtilizer = nullptr;
	if (mCurSkill)
	{
		mCurSkill.Release(); //release before choosing
	}

	//mRageSkill's validation depends on mRageSkillAutoReady flag, so check this flag first
    if (mRageSkill && mRageSkillAutoReady && (GetBattleInstance().IsAuto() || (mArmy->GetId() == 2) || mRageSkill->mAutoRageSkill)
		&& mRageSkill->CanExecute() == CheckResult::Pass)
    {
		mChoosedSkill = mRageSkill;
    }
    else
    {
		int mark = 0;
		if (mChainSkillIndex < mChainSkillOrder.size())
		{
			mark = mChainSkillOrder[mChainSkillIndex];
		}
		else
		{
			LOG_FATAL("invalid chian skill for tplId = %d, chainIdx = %d, chainSkillOrder.Size = %d", 
				mTplId, mChainSkillIndex, mChainSkillOrder.size());
		}
		
		if (mark >= mChainSkillArr.size() || !mChainSkillArr[mark])
		{
			LOG_WARN("invalid chain skill for tplid = %d", mTplId);
			IncreaseSkillIndex();
			return false;
		}
		if (mChainSkillArr[mark]->IsNormalSkill())
		{
			for (size_t i = 0; i < mRandomNormalSkillArr.size(); i++)
			{//test every random normal skill, use it as long as passes all testings 
				if (mRandomNormalSkillArr[i]->CanExecute() == CheckResult::Pass
					&& mRandomNormalSkillArr[i]->RefreshRefTarget())
				{
					mRandomNormalSkillArr[i]->CheckReplacement();
					mChoosedSkill = mRandomNormalSkillArr[i];
					IncreaseSkillIndex();
					break;
				}
			}
			if (!mChoosedSkill)
			{//after failing to choose any random normal skill, check normal 
				auto ret = mChainSkillArr[mark]->CanExecute();
				switch (ret)
				{
				case CheckResult::Pass:
					break;
				case CheckResult::NoNormalSkill:
				case CheckResult::CD:
					return false;
				default:
					LOG_WARN("hero %d, skill %d, normal skill fail to pass CanExecute. ret = %d", mTplId, mChainSkillArr[mark]->GetId(), static_cast<int>(ret));
				}
				if (!mChainSkillArr[mark]->RefreshRefTarget())
				{
					mNoTargetCounter++;
					return false;	//do not incerase skill index
				}
				mChainSkillArr[mark]->CheckReplacement();
				mChoosedSkill = mChainSkillArr[mark];
				IncreaseSkillIndex();
			}
		}
		else
		{// non-normal skill
			auto ret = mChainSkillArr[mark]->CanExecute();
			switch (ret)
			{
			case CheckResult::Pass:
				break;
			case CheckResult::NoSkill:
				{ //try replace with normal skill this time 
					if (mChainSkillArr[0] && mChainSkillArr[0]->CanExecute() == CheckResult::Pass
						&& mChainSkillArr[0]->RefreshRefTarget())
					{ //replace OK
						mChainSkillArr[0]->CheckReplacement();
						mChoosedSkill = mChainSkillArr[0];  //do not incerase index 
						IncreaseSkillIndex();
					}
					else
					{ //replace fail, do not execute any skill 
						mNoTargetCounter++;
						return false;
					}
				}
				break;
			default:
				LOG_DEBUG("hero %d, skill %d, non-normal skill fail to pass CanExecute. ret = %d", mTplId, mChainSkillArr[mark]->GetId(), static_cast<int>(ret));
				IncreaseSkillIndex(); //skip this skill 
				return false;
			}
			if (!mChoosedSkill)
			{
				if (!mChainSkillArr[mark]->RefreshRefTarget())
				{
					IncreaseSkillIndex(); //skip this skill 
					mNoTargetCounter++;
					return false;
				}
				mChainSkillArr[mark]->CheckReplacement();
				mChoosedSkill = mChainSkillArr[mark];
				IncreaseSkillIndex();
			}
		}
    }

    if (mChoosedSkill)
    {
        //嘲讽状态下，只能选择普攻。策划会通过配置保证这一点。这里做个检查 
        if (CheckStateAdjust(StateAdjust::Taunted))
        {
			if (!CheckStateAdjust(StateAdjust::NoSkill))
			{
				LOG_DEBUG("Unit %d taunted, NoSkill=false", mEntityId);
			}
            if (mChoosedSkill->IsNormalSkill() == false)
            {
                LOG_FATAL("Unit %d(tid=%d) taunted, need choose normal skill, curSkill %d", mEntityId, mTplId, mChoosedSkill->GetId());
            }
			else
			{//do not redirect a positive type skill to an enemy when self taunted 
				if (mChoosedSkill->isPositiveType())
				{
					mChoosedSkill.Release();
					return false;
				}
			}
        }
		mNoTargetCounter = 0;
        return true;
    }
	mNoTargetCounter++;
    return false;
}

void Unit::IncreaseSkillIndex()
{
	++mChainSkillIndex;
	if (mChainSkillIndex >= mChainSkillOrder.size())
	mChainSkillIndex = 0;
}

// OnTick Method of MoveToNearestRefTar State
// try find refTarget, then do MoveTowards
bool Unit::ActionMoveToRefTarget(int const aDeltaTime)
{
	if (!mChoosedSkill)
	{  //maybe cancelled when check semi auto skill  
		mFsm->DoTransition(mTransResetToIdle);
		return false;
	}
    if (!mChoosedSkill->RefreshRefTarget())
    {
		mChoosedSkill.Release();  //release in case of forgotten
        mFsm->DoTransition(mTransResetToIdle);
        return false;
    }
	if (IsTowerLike() && !mChoosedSkill->IsRefTargetInRangeDynamic())
	{  //for summoned cannon tower 
		mChoosedSkill.Release();
		mFsm->DoTransition(mTransResetToIdle);
		return false;
	}
    if (CheckStateAdjust(StateAdjust::NoMove) && !IsTowerLike())
    {
		if (mChoosedSkill->IsRefTargetInRangeDynamic())
		{
			return true;
		}
		else
		{
			mChoosedSkill.Release();
			mFsm->DoTransition(mTransResetToIdle);
			return false;
		}
    }
    const RefTarget& refTarget = mChoosedSkill->GetNearestRefTarget();  

	ERefFaceTo faceTo = static_cast<ERefFaceTo>(mChoosedSkill->GetSkillConf()->basedata().needfacetowhencast());
	bool reach = false;
	MoveStrategy ret = HowToMove(refTarget);
	if (ret == MoveStrategy::AIPath)
		reach = Move2Ref(refTarget, SharedFromThis(), mChoosedSkill->GetCastRange() + refTarget.GetSize() + GetSize(), aDeltaTime, faceTo, mArmy->GetId() == 1);
	else
		reach = Move(refTarget, SharedFromThis(), mChoosedSkill->GetCastRange() + refTarget.GetSize() + GetSize(), aDeltaTime, faceTo);
	
	if (reach)
	{
		return true;
		//TryUpdateMapLocation();
	}
	return false;
}

//OnExit Method of MoveToNearestRefTarget State
void Unit::ActionExitMoveToRefTarget()
{
	if (IsMoving())
	{
		DisableMove();
	}
}

// OnEnter Method of ExecSkill State
// let Skill Obj TryExecute the skill, if failed, trans to Idle directly
void Unit::ActionExecuteSkill()
{
	if (mCurSkillExecutor)
		mCurSkillExecutor.Release();
	mCurSkill = mChoosedSkill;
	mCurSkillExecutor = SharedPool<SkillExecutor>::Get();
    bool suc = mCurSkill->TryExecute(0, SharedPtr<SkillExecutor>(), mSkillSourceUtilizer, mCurSkillExecutor);
    mSkillSourceUtilizer = nullptr;
	if(suc)
	{
		if (mCurSkillExecutor && !mCurSkillExecutor->IsInactive())
		{
			//mSkillTimer = SharedPool<Timer<Unit> >::Get();
			int time = mCurSkill->GetTimeLength();
			//mSkillTimer->Execute(mTimerMgr, SharedFromThis(), &Unit::CallbackSkillEnded, mUnitTime + time);
			LOG_DEBUG("Unit %d executing skill {state=%s skillId=%d skillTime=%d/%d}"
				, mEntityId
				, mFsm->GetCurrentState().GetName()
				, mCurSkill->GetId()
				, time
				, mUnitTime + time);  
		}
		else if(mCurSkillExecutor)
		{//this skill is Done all in one stack call, aka mCurSkill->TryExecute finishs all jobs
			mCurSkillExecutor.Release();
		}
		CheckSkillExecutor();
	}    
    else
    {
		LOG_DEBUG("Unit %d failed to execute skill {state=%s skillId=%d}"
            , mEntityId
            , mFsm->GetCurrentState().GetName()
            , mCurSkill->GetId());
		mCurSkillExecutor.Release();
        mFsm->DoTransition(mTransNoSkillToExecute);
    }
}


void Unit::ActionExitExecuteSkill()
{
	mSkillSourceUtilizer = nullptr;
	if (!mCurSkillExecutor)
	{
		return;
	}

	if (!mCurSkillExecutor->IsInactive())
	{
		SkillInterrupted(mCurSkillExecutor, false, true);
	}
	else if (mCurSkill)
	{
		mCurSkill->CleanRefTargetArr();
	}

	if (mCurSkill && mCurSkill->IsRageSkill())
	{
		GetBattleInstance().EndRageSkill(*this);
	}

	if (!mCurSkillExecutor)
	{ //after SkillInterrupted, current SkillExecutor may be released already 
		return;
	}

	int64 recoveryStdTime = int64(mCurSkillExecutor->GetSkill()->GetStandTime());
	if (mRealSpeedFactor != 0)
	{
		recoveryStdTime = recoveryStdTime * DENOM / (DENOM + mRealSpeedFactor);
	}
	mRecoveryTime = recoveryStdTime + mUnitTime;
	int skillId = mCurSkillExecutor->GetSkill()->GetId();

	mCurSkill.Release();
	mCurSkillExecutor.Release();

    mView->Execute(ViewCommand::SkillEnd, mEntityId, skillId);
	LOG_DEBUG("Unit {entityId=%d,state=%s} skill ended {skillId=%d,recoveryTime=%d/%d}"
        , mEntityId
        , mFsm->GetCurrentState().GetName()
        , skillId
        , mRecoveryTime - mUnitTime
        , mRecoveryTime);
}

void Unit::ActionEnterSkillRecovery()
{
	SetAnim(ANIM_NAME_IDLE);
	mOverLapRefTarget.SetType(ERefTargetType::Invalid);
	mNumOfAvoidOverlapMovement = 2;
	mLastDir.Set(0, 0, 0);
	ConditionSendActionSpeedCMD(ActionSpeedCondition::OnRecoverBegin);
	if (!mIsDummy)
		mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::SkillRecovery, mCurrentAnimName);
}

void Unit::ActionExitSkillRecovery()
{
	LOG_DEBUG("Unit {entityId=%d,state=%s} recovered"
        , mEntityId
        , mFsm->GetCurrentState().GetName());
	SetAnim(ANIM_NAME_IDLE);
	ConditionSendActionSpeedCMD(ActionSpeedCondition::OnRecoverEnd);
}

bool Unit::ActionTickSkillRecovery(int const aDeltaTime)
{    
    bool ret = mRecoveryTime <= mUnitTime; 
    if (!mAgent)
    {
        return ret;
    }

	if (TryExecuteRageSkillAuto() == 1) 
	{  //success to execute rage skill 
		return false;
	}

	//last reftarget in range?
	if (mLastRefTarget)
	{
		auto dist = GetPosition() - mLastRefTarget->GetPosition();
		dist.y = 0;
		auto length = dist.Magnitude2();
		RestoreObjToPool(dist);
		auto stdDit2 = (mLastCastRange + COMMON_REACHOUT_MODIFIER) * (mLastCastRange + COMMON_REACHOUT_MODIFIER);
		if (length > stdDit2 || (mLastRefTarget->IsDead() && mLastRefTarget->IsEnemy(SharedFromThis())))
		{  //when out of view range Or when target enemy is dead
			mLastRefTarget.Release();
			mLastCastRange = 0;
			return true;
		}
	}

	//AvoidOverlap2(aDeltaTime);

	return ret;
}


void Unit::AvoidOverlap2(int const aDeltaTime)
{
	if (IsTowerLike())  //tower can not move! 
		return;

	if (mConfig && mConfig->GetImmuneOverlap() == 1)
		return;

	if (IsMoving())
	{//is in process of cancel-overlap, so wait
		Move(mOverLapRefTarget, SharedFromThis(), 0, aDeltaTime, ERefFaceTo::None, 0, 0, 0); 
	}

	if (mUnitTime % 700 != 0 && mNumOfAvoidOverlapMovement < 2) return;
	else if (mNumOfAvoidOverlapMovement == 2) mNumOfAvoidOverlapMovement--;

	if (mNumOfAvoidOverlapMovement <= 0)
		return;

	vector<SharedPtr<Entity> > result;
	mPhysics->IntersectionTest2D(PHYSICS_GROUP_UNIT, mAgent, nullptr, result);
	if (result.size() < 1)
	{
		RestoreVectorToPool(result);
		return DoAvoidOverlap();
	}

	Vector3 myTarget(0,0,0);
	bool hasTarget = false;
	int mTargetBodySize = 100000;
	if (HasInRangeSkillTarget())
	{
		auto myRefTarget = GetInRangeSkillTarget();
		myTarget.Set(myRefTarget.GetTargetPos());
		hasTarget = true;
		if (myRefTarget.GetType() == ERefTargetType::Unit)
		{
			mTargetBodySize = myRefTarget.GetUnit()->GetSize();
		}
	}

	auto mpos = GetPosition();
	auto msize = GetSize();
	int64 dx = 0, dz = 0, dl = 0;
	Vector3 sumforce(0,0,0);
	vector<Vector3> coTargetUnits;
	int64 totalLimits = 0;
	for (auto& entity : result)
	{
		auto unit = DynamicPointerCast<Unit, Entity>(entity);
		if (unit->mOnMoveBySkillCancel || unit->IsDummy() || unit->IsDead())
		{
			continue;
		}
		int64 maxForce = msize + unit->GetSize() - 15000;  
		if (maxForce > totalLimits) totalLimits = maxForce;
		auto fpos = unit->GetPosition();

		dx = mpos.x - fpos.x + 1;
		dz = mpos.z - fpos.z + 1;
		dl = Sqrt(dx * dx + dz * dz) + 1;

		int64 realForce = maxForce - dl;

		dx = dx * realForce / dl;  //scale to length = realForce
		dz = dz * realForce / dl;

		sumforce.x += dx;
		sumforce.z += dz;

		if (hasTarget && unit->HasInRangeSkillTarget())
		{  //try pick up all co-target units
			auto unitTarget = unit->GetInRangeSkillTarget();
			if (myTarget == unitTarget.GetTargetPos())
			{
				coTargetUnits.emplace_back(fpos);
			}
		}
	}
	RestoreVectorToPool(result);

	int64 rawMag = sumforce.Magnitude();
	if (rawMag == 0)
	{
		RestoreObjToPool(myTarget);
		RestoreObjToPool(sumforce);
		RestoreVectorToPool(coTargetUnits);
		return DoAvoidOverlap();
	}
	if (rawMag < BattleInstance::AvoidOverlapCoef2) rawMag = 0;
	else rawMag = BattleInstance::AvoidOverlapCoef2;
	Vector3 finalPos = sumforce + mpos;
	
	if (hasTarget)
	{ //do not move surpass somebody from one side to the other
		//finalPos = sumforce + mpos - myTarget;
		finalPos -= myTarget;
		int64 len = (mpos - myTarget).Magnitude();
		if (len < msize + mTargetBodySize)
		{  //set min len from self to target
			len = msize + mTargetBodySize;
		}
		finalPos.ScaleToLen(len);
		finalPos += myTarget;
		Vector3 tmpDir = finalPos - mpos;
		if (tmpDir.Magnitude() < BattleInstance::AvoidOverlapCoef2)  //todo mag2
		{ // ignore minor movement request
			if (rawMag == 0)
			{				
				RestoreObjToPool(sumforce);
				RestoreObjToPool(myTarget);
				RestoreObjToPool(finalPos);
				RestoreVectorToPool(coTargetUnits);
				return DoAvoidOverlap();
			}				
			else
			{
				tmpDir.ScaleToLen(rawMag);
				//finalPos = mpos + tmpDir;
				finalPos.Set(mpos);
				finalPos += tmpDir;
			}
		}
		RestoreObjToPool(tmpDir);
		Vector3 collisionPoint;
		for (auto v : coTargetUnits)
		{
			if (mPhysics->IntersectionSegSeg2D(finalPos, mpos, v, myTarget, collisionPoint))
			{
				finalPos = v;
			}
		}
		RestoreObjToPool(collisionPoint);
	}

	auto moveVector = finalPos - mpos;
	int64 moveDistance = moveVector.Magnitude();
	if (moveDistance > totalLimits)
	{  //limit max move distance to sum of both unit's size
		moveVector.ScaleToLen(totalLimits);
		//finalPos = moveVector + mpos;
		finalPos.Set(moveVector);
		finalPos += mpos;
		if (hasTarget)
		{			
			int64 len = Vector3::Dist( mpos, myTarget);			
			Vector3 tmp = finalPos - myTarget;
			if (len < msize)
			{
				len = msize;
			}
			tmp.ScaleToLen(len);
			//finalPos = myTarget + tmp;
			finalPos.Set(myTarget);
			finalPos += tmp;
			RestoreObjToPool(tmp);
		}
	}
	RestoreObjToPool(moveVector);
	auto& battleInstance = GetBattleInstance();
	bool restrained = false;
	if(battleInstance.RestrainToBattleArea(mpos, finalPos, GetSize(), &finalPos) == true)
	{
		restrained = true;
	}
	finalPos.y = 0;  //not allow vertical move at all!!!
	moveDistance = Vector3::Dist(finalPos, mpos);

	DoAvoidOverlap(&finalPos, moveDistance, aDeltaTime, &myTarget);
	RestoreVectorToPool(coTargetUnits);
	RestoreObjToPool(myTarget);
	RestoreObjToPool(sumforce);
	RestoreObjToPool(finalPos);
}

void Unit::DoAvoidOverlap(const Vector3* aFinalPos, int64 aMoveDist, int aDeltaTime, const Vector3* aMyTarget)
{
	if (aFinalPos && aMyTarget)
	{
		if (mOverLapRefTarget.GetType() == ERefTargetType::Invalid && mLastDir.Magnitude2() == 0)
		{  //first move cmd for this recover period
			mNumOfAvoidOverlapMovement--;
			//mLastDir = *aFinalPos - GetPosition();
			mLastDir.Set(*aFinalPos);
			mLastDir -= GetPosition();
			mOverLapRefTarget.SetPos(*aFinalPos);
			if (aMoveDist < BattleInstance::AvoidOverlapCoef3)  //move without run anim
				Move(mOverLapRefTarget, SharedFromThis(), 0, aDeltaTime, ERefFaceTo::None, BattleInstance::AvoidOverlapCoef4, aMyTarget->x, aMyTarget->z, true);
			else  //move using run anim 
				Move(mOverLapRefTarget, SharedFromThis(), 0, aDeltaTime, ERefFaceTo::None, BattleInstance::AvoidOverlapCoef5, aMyTarget->x, aMyTarget->z, false);
			return;
		}
		else
		{
			Vector3 myDir = *aFinalPos - GetPosition();
			if (!IsSameDir(myDir, mLastDir))
			{ //new final pos is on the opposite direction
				mNumOfAvoidOverlapMovement = 0;
				if (IsMoving())
				{
					DisableMove();
				}
			}
			else
			{
				mNumOfAvoidOverlapMovement--;
				mOverLapRefTarget.SetPos(*aFinalPos);
				if (aMoveDist < BattleInstance::AvoidOverlapCoef3)
					Move(mOverLapRefTarget, SharedFromThis(), 0, aDeltaTime, ERefFaceTo::None, BattleInstance::AvoidOverlapCoef4, aMyTarget->x, aMyTarget->z, true);
				else
					Move(mOverLapRefTarget, SharedFromThis(), 0, aDeltaTime, ERefFaceTo::None, BattleInstance::AvoidOverlapCoef5, aMyTarget->x, aMyTarget->z, false);
				return;
			}
			RestoreObjToPool(myDir);
		}
	}
	else
	{
		if (IsMoving())
		{
			DisableMove();
		}
	}
}

bool Unit::IsSameDir(Vector3& aDir1, Vector3& aDir2)
{
	int base = 100000;
	auto abMag = aDir1.Magnitude() * aDir2.Magnitude();
	if (abMag == 0)
	{
		LOG_DEBUG("IsSameDir has zero input vector");
		return true;
	}
	auto ab = Vector3::Dot(aDir1, aDir2);
	if (ab > abMag) ab = abMag;
	auto cosValue = ab * base / abMag;
	//auto theta = ArccosInt(cosValue, base, base);
	//return theta < 45 * base;

	//use "cosValue > 0.707107 * base" to replace "theta < 45 * base" 
	return cosValue > 70710;
}

bool Unit::HasInRangeSkillTarget()
{
	if (mChoosedSkill && mChoosedSkill->HasRefTarget() && mChoosedSkill->IsRefTargetInRange())
	{
		return true;
	}
	return false;
}

RefTarget& Unit::GetInRangeSkillTarget()
{
	return mChoosedSkill->GetRefTargetArr()[0];
}

// set back mOverlap, change Anim to Idle, then View Exec Cmd::ControlledStateChange
void Unit::CancelOverlapMove()
{
    if (mOverlap)
    {
        mOverlap = false;
		SetAnim(ANIM_NAME_IDLE);
		if (!mIsDummy)
			mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::None, mCurrentAnimName);
    }
}

void Unit::ActionEnterDying()
{
	//注意Player需要进行判断，是否使用复活券 
	if (mDieCause.cause == EUnitDieCause::Timeout ||
		mDieCause.cause == EUnitDieCause::Buff ||
		GetBattleInstance().IsDyingValid(GetArmy().GetId())) 
	{
		mFsm->DoTransition(mTransRealDead);
	}
}

bool Unit::ActionTickDying(int aDeltaTime)
{
	if (!GetBattleInstance().IsDyingValid(GetArmy().GetId()))
	{ 
		return false;
	}
	return true;
}


void Unit::DetermineDeathAnim(Unit* aKiller)
{
	mDieCause.moveConf.clear();
	mDieCause.mDir = GetPosition() - aKiller->GetPosition();
	mDieCause.mDir.y = 0;
	mDieCause.animName = ANIM_NAME_DEAD;
	if (mDieCause.mDir.x == mDieCause.mDir.z && mDieCause.mDir.x == 0)
	{
		mDieCause.mDir.x = 1;
	}
	return;
}

// OnEnter Method of Dead State
// Interrupt its Skill, clean up Buff and mPhysics_mAgent, notice mArmy, and View Exec Cmd::Die
void Unit::ActionEnterDead()
{
	DetermineDeathAnim(mKiller);  //run it nomatter what the killer is
	int killerId = 0;
	bool killerIsShooter = false;
	auto& battleInstance = GetBattleInstance();
	if (mKiller) 
	{
		//add rage to utilizer here
		if (!IsSummoned() && !IsDummy())
			mKiller->IncKillNum(1);
		int r = BattleInstance::KillToRage;
		if (mDieCause.rageBonus > 0) r = mDieCause.rageBonus;
		if(mProvideKillRage && !mKiller->IsDead() && !mKiller->IsDying())
			mKiller->AddRage(r, ERageChangeCause::Kill);
		killerId = mKiller->GetEntityId();
		killerIsShooter = mKiller->IsArmyShooter();
		//trigger event after Kill 
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterKill)); 
		battleInstance.DispatchEvent(key, mKiller->GetArmyId(), killerId, GetEntityId());
		mKiller = nullptr;
	}
    
    if (mTimedLife)
    {
        mTimedLife->Cancel();
    }
	mHp = 0;  //make sure set to 0
	mRageSkillManualReady = false;
	DisableMove();
	TryUpdateMapLocation(true);
	mBuffMgr->Clear(true);

	if (true)
	{
		int key1 = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Death));
		battleInstance.DispatchEvent(key1, GetArmyId(), GetEntityId(), killerId);
		if (!IsDummy() && !IsSummoned())
		{
			int key4 = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Death), static_cast<int>(ETriggerDeathSub::NoHeroLeft));
			battleInstance.DispatchEvent(key4, GetArmyId(), GetEntityId(), killerId);
		}
	}
	if (!IsDummy() && killerId > 0 && !killerIsShooter)
	{
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Death), static_cast<int>(ETriggerDeathSub::UseKillerAsRefTarget));
		battleInstance.DispatchEvent(key, GetArmyId(), GetEntityId(), killerId);
	}
	if (!IsDummy() && IsSummoned() && mDieCause.cause == EUnitDieCause::Timeout)
	{ //召唤物超时死亡（既正常死亡） 
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Death), static_cast<int>(ETriggerDeathSub::UseAncestorAsRefTarget));
		battleInstance.DispatchEvent(key, GetArmyId(), GetEntityId(), GetAncestor());
	}

	if (mOnMoveBySkillCancel)
		mOnMoveBySkillCancel->operator()(SharedFromThis());  //resolve current movement
	//if (mDieCause.cause != EUnitDieCause::ClearSummonWhenCutScene)
	mView->Execute(ViewCommand::Die, mEntityId, (int)mDieCause.cause, mDieCause.data);
	if (!IsDummy() && mDieCause.animName)
	{
		SetAnim(mDieCause.animName);
		mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::None, mDieCause.animName);
	}
}

// OnEnter Method of Idle State
// set OnEnter to null after first Enter
// Try Trigger Skill marked as Born
void Unit::ActionEnterBorn()
{
    mStateIdle->SetOnEnter(nullptr);
	SetAnim(ANIM_NAME_IDLE);
    //TryTriggerSkill(ETriggerMajor::Born);
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Born));
	GetBattleInstance().DispatchEvent(key, GetArmyId(), GetEntityId());
}

// OnEnter Method of Revive State
// notice mArmy, add agent to Physics_mAgent, View Exec Cmd::Revive, try to Trigger Revive Skill
void Unit::ActionEnterRevive()
{
    //TODO summoned unit revive?
	mKiller = nullptr;
	mBeControlledStack.clear();
    mArmy->UnitDeadStatusChanged(this);
    mView->Execute(ViewCommand::Revive, mEntityId);
    InitPhysics();
    //TryTriggerSkill(ETriggerMajor::Revive);
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Revive));
	GetBattleInstance().DispatchEvent(key, GetArmyId(), GetEntityId());
	OnBeRevived();
	mTimeWhenDead = 0;
}

// OnTick method of BeControlled State
// handle One ControlState every Tick, if not on Ground, TryFallToGround first
bool Unit::ActionTickBeControlled(int const aDeltaTime)
{
    auto& state = mBeControlledStack.back();
    if (state->OnTick)
    {
        (*(state->OnTick))(aDeltaTime);
    }
    return false;
}

// OnTick method of Dead State
// just TryFallToGround
bool Unit::ActionTickDead(int const aDeltaTime)
{
	//是否在这里设置一个配置时间，让前端有时间播放Dead动画? 
	mArmy->UnitDeadStatusChanged(this);
	if (mAgent)
	{
		mPhysics->RemoveAgent(mAgent);
		mAgent = nullptr;
		mBV = nullptr;
	}
	return true;
}

// called by skillExecutor when onKeyframe
// decide if Execute a skill based on its TriggerWithSkillArr 
void Unit::OnSkillKeyframe(const SkillExecutor& aSkillExecutor)
{
	auto& skill = aSkillExecutor.GetSkill();
	if (skill->IsNormalSkill())
	{  //normal skill, may trigger some sort of skills later on 
		mNormalAtkNum++;
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WithSkill), static_cast<int>(ETriggerWithSkillSub::Normal));
		GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, skill->GetId());
	}
	else
	{  //non-normal skill, including triggering skill
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WithSkill), static_cast<int>(ETriggerWithSkillSub::NonNormal));
		GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, skill->GetId());
	}

	{ //dispatch event for Self + WithSkill [note that subtype uses None]
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WithSkill), static_cast<int>(ETriggerWithSkillSub::None));
		GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, skill->GetId());
		key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WithSkill), static_cast<int>(ETriggerWithSkillSub::SkillList));
		GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, skill->GetId());
	}

}

// called by skillExecutor when OnEnd
void Unit::OnSkillEnd(const SkillExecutor& aSkillExecutor)
{
	if (&aSkillExecutor == mCurSkillExecutor.Get()) 
	{
		mFsm->DoTransition(mTransSkillEnded);
	}
	else
	{
		//at least send cmd to notice front 
		mView->Execute(ViewCommand::SkillEnd, mEntityId, aSkillExecutor.GetSkill()->GetId());
	}
}

void Unit::OnTick(int const aDeltaTime)
{
    //int unitTime = aDeltaTime * (DENOM + mActionSpeedFactor) / DENOM;
    int unitTime = aDeltaTime;
    mUnitTime += unitTime;
    CheckRageSkill();
	CheckUnparalleledSkill();
    mFsm->OnTick(unitTime);
    mTimerMgr->OnTick(mUnitTime);
	TickBarrier(unitTime); 
	TryExecuteRageSkillBreakNormalAuto();
}

void Unit::OnEnterField()
{
	//behaviour stop dominate everything
	//if (!CheckStateAdjust(StateAdjust::BehaviourStopped))
	if (!mFsm->IsInState(mStateBehaviour->GetId()))
	{
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Enter));
		GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
		int key2 = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::OnCheckCountryHeroNumber));
		GetBattleInstance().DispatchEvent(key2, mArmy->GetId(), mEntityId);

	}
	for (auto& sk : mSkillArr)
	{
		sk->CleanRefTargetArr();
	}
}


void Unit::OnEnterCutscene()
{
	//CurrentSkillInterrupted();
	for (int i = 0; i < mSkillExecutorArr.size(); i++)
	{
		mSkillExecutorArr[i]->Interrupt();
	}
	mSkillExecutorArr.clear();
	if (IsDead() && mArmyId == 2)
	{
		RemoveAllListener();
	}
    if (mBeHitTimer)
    {
        mBeHitTimer->Cancel();
    }
	if (mBuffMgr)
	{
		mBuffMgr->Clear(true);
	}
	if (mTimedLife)
	{//Above mBuffMgr->Clear may cause this unit die, which will cancel(invalid) mTimedLife as results, 
	 //so we need to check isdead before appling offset 
		if (IsDead())
			mTimedLife = nullptr;
		else
			mTimedLife->Offset(-mUnitTime);
	}
    for (auto& skill : mSkillArr)
    {
        skill->OffsetCD(-mUnitTime);
    }
    if (mRageSkill)
    {
        mRageSkill->OffsetCD(-mUnitTime);
    }
    for (auto& buff : mBuffMgr->GetBuffMap())
    {
        buff.second->Offset(-mUnitTime);
    }
	if (mTimerMgr)
	{
		mTimerMgr->Check();
	}
    mUnitTime = 0;
	mRecoveryTime = 0;
	mChainSkillIndex = 0;
	if (mLastNormalTarget)
		mLastNormalTarget.Release();
	if (mLastRefTarget)
		mLastRefTarget.Release();
	mDontInitToBornPos = false;
    if (IsDead() || IsHidden())
    {
        return;
    }
    mFsm->DoTransition(mTransCutscene);
}

//will check for every Unit::OnTick
//return true if this method changes any field value
bool Unit::CheckRageSkill()
{
	if ((IsDead() || IsHidden()))  //this unit may be in Dead state due to FallToGround requirements
	{
		return false;
	}
    if (mRage >= mRageSkillThreshold)
    { //has enough Rage
		if (mCurSkill && mCurSkill->IsRageSkill()) 
		{  //防止大招在扣除Rage前进入下面分支，刷新并改变RefTarget
			return false;
		}

		if (!mFsm->IsInState(mStateBeControlled->GetId()) 
			&& !CheckStateAdjust(StateAdjust::Taunted) 
			&& !CheckStateAdjust(StateAdjust::NoSkill)
			&& !CheckStateAdjust(StateAdjust::NoRageSkill))
		{ // must not in control state, must has reftarget, and more 
			if (GetRageSkill()) //check if get any available rage skill right now
			{
				mRageSkillAutoReady = true;
				if (mRageSkill->mAutoRageSkill)
					return true;
				if (mRageSkill->IsRefTargetInRange())
				{
					if (!mRageSkillManualReady)
					{
						mRageSkillStatus = RageSkillStatus::RageReadyToCast;
						mRageSkillManualReady = true;
						mView->Execute(ViewCommand::RageSkillStatus, mEntityId, int(mRageSkillStatus));
					}
					return true;
				}
				else
				{
					mRageSkillStatus = RageSkillStatus::RageNotReady;  //out of range 
				}
			}
			else
			{ //no skill stands by 
				mRageSkillStatus = RageSkillStatus::RageNotReady;
			}
        }
		else
		{
			mRageSkillStatus = RageSkillStatus::RageReadyButBeControlled;
		}
    }
	else
	{
		mRageSkillStatus = RageSkillStatus::RageNotReady;  //insufficient rage 
	}
    mRageSkillAutoReady = false;
    if (mRageSkillManualReady)
    {
        mRageSkillManualReady = false;
        mView->Execute(ViewCommand::RageSkillStatus, mEntityId, int(mRageSkillStatus));
    }
	return true;
}


void Unit::CheckUnparalleledSkill()
{
	if ((IsDead() || IsHidden()))
	{
		return;
	}
	if (mArmy->CanExecuteUnparallel() && mUnparalleledSkill)
	{ //has enough Rage, and has UnparalleledSkill
		if (mCurSkill && mCurSkill->IsUnparallelledRageSkill())  //防止大招在扣除Rage前进入下面分支，刷新并改变RefTarget
		{
			return;
		}

		if (!mFsm->IsInState(mStateBeControlled->GetId()))
		{ // must not in control state and behit state
			if (mUnparalleledSkill->CanExecute() == CheckResult::Pass
				&& mUnparalleledSkill->RefreshRefTarget()
				&& mUnparalleledSkill->HasRefTarget())
			{ // must has reftarget, and more 
				if (mUnparalleledSkill->IsRefTargetInRange())
				{
					if (!mUnparalleledSkillReady)
					{
						mUnparalleledSkillReady = true;
						mUnparallelSkillStatus = RageSkillStatus::RageReadyToCast;
						mView->Execute(ViewCommand::UnparalleledSkillStatus, mEntityId, int(mUnparallelSkillStatus));
					}
					return;
				}
			}
			else
			{
				mUnparallelSkillStatus = RageSkillStatus::RageNotReady;
			}
		}
		else
		{
			mUnparallelSkillStatus = RageSkillStatus::RageReadyButBeControlled;
		}
	}
	else
	{
		mUnparallelSkillStatus = RageSkillStatus::RageNotReady;
	}
	if (mUnparalleledSkillReady)
	{
		mUnparalleledSkillReady = false;
		mView->Execute(ViewCommand::UnparalleledSkillStatus, mEntityId, int(mUnparallelSkillStatus));
	}
}

void Unit::ExecuteSkill(const SharedPtr<Skill> aSkill, int const aDelay, SharedPtr<SkillExecutor> aParentExecutor, SharedPtr<Unit> aSourceUtilizer, SharedPtr<Unit> aReflecter)
{
    if (aSkill->HasAnim() && !aParentExecutor && !aReflecter)
    {
		//对于有动画的技能，需要unit处在idle状态，然后进入完整的技能执行流程。即从移向目标开始。 
		//如果unit不在idle状态，就警告 
        if ( mFsm->IsInState(mStateIdle->GetId()) == false 
			&& mFsm->IsInState(mStateSkillRecovery->GetId()) == false 
			&& mFsm->IsInState(mStateBehaviour->GetId()) == false) 
			
        {
			LOG_DEBUG("Unit %d cannot execute skill with animation {skillId=%d} when not in idle or SkillRecovery or BehaviourStopped {state=%s}"
                , mEntityId
                , aSkill->GetId()
                , mFsm->GetCurrentState().GetName());
            return;
        }
		mChoosedSkill = aSkill;
        mCurSkill = aSkill;
        mCurSkillExecutor.Release();
		mSkillSourceUtilizer = aSourceUtilizer;
		if (!mChoosedSkill->RefreshRefTarget())
		{
			return;
		}
		if (mFsm->IsInState(mStateBehaviour->GetId()))
		{
			mFsm->DoTransition(mTransBehaviourToIdle); 
		}
        mFsm->DoTransition(mTransMoveToRefTarget);  
    }
    else
    {
		auto skillExecutor = SharedPool<SkillExecutor>::Get();
        bool suc = aSkill->TryExecute(aDelay, aParentExecutor, aSourceUtilizer, skillExecutor, aReflecter);
		if ( suc && !skillExecutor->IsInactive())
		{
			mSkillExecutorArr.emplace_back(skillExecutor);	
		}
		LOG_DEBUG("Skill {skillId=%d} is executed by Unit %d  suc:%d"
				, aSkill->GetId()
				, mEntityId
				, suc);
    }    
}

void Unit::TryTriggerSkillOnHp()
{
	if (mTriggerOnHpSkillArr.size() < 1)
		return;
	int j = 0;
	for (int i = 0; i < mTriggerOnHpSkillArr.size();) 
	{
		j = mTriggerOnHpSkillArr.size() - 1;
		auto entry = mTriggerOnHpSkillArr[i];
		if (!entry)
		{
			LOG_WARN("empty entry found in SkillOnHpArr");
			mTriggerOnHpSkillArr[i] = mTriggerOnHpSkillArr[j];
			j--;
			mTriggerOnHpSkillArr.resize(j + 1);
			continue;
		}
		auto skill = entry->mSkill;
		if (entry->mHpType == EBuffTriggerSkillHpType::ETriggerSkillHpTypeFixValue)
		{
			if (mHp < entry->mLifeValue && skill->RefreshRefTarget())
			{
				mTriggerOnHpSkillArr[i] = mTriggerOnHpSkillArr[j];
				j--;
				mTriggerOnHpSkillArr.resize(j + 1);
				ExecuteSkill(skill, 0, nullptr, entry->mSourcer);
				continue;
			}
		}
		else if (entry->mHpType == EBuffTriggerSkillHpType::ETriggerSkillHpTypeMaxHpPercent)
		{
			if ((mHp * DENOM / mMaxHp) < entry->mLifeValue && skill->RefreshRefTarget())
			{
				mTriggerOnHpSkillArr[i] = mTriggerOnHpSkillArr[j];
				j--;
				mTriggerOnHpSkillArr.resize(j + 1);
				ExecuteSkill(skill, 0, nullptr, entry->mSourcer);
				continue;
			}
		}
		i++;
	}
	mTriggerOnHpSkillArr.resize(j + 1);
}


// order by input cmd
int Unit::ManuallyExecuteRageSkill()
{

	bool hasChgFieldValue = false;
	if (CheckRageSkill())
	{
		hasChgFieldValue = true;
	}

	if (!mRageSkillManualReady || (mCurSkill && mCurSkill->IsRageSkill()))
		return hasChgFieldValue ? 1 : 0;

	int ret = TryExecuteRageSkill();
	if (ret == 0 && !hasChgFieldValue)
		return 0;
	else
		return 1;
}

int Unit::TryExecuteRageSkill()
{
	ERefFaceTo faceTo = static_cast<ERefFaceTo>(mRageSkill->GetSkillConf()->basedata().needfacetowhencast());
	if (ERefFaceTo::None != faceTo)
	{
		if (!mRageSkill->HasRefTarget())
		{
			LOG_WARN("rage skill not has refTarget");
			return 0;
		}
		RefTarget refTarget = mRageSkill->GetNearestRefTarget();
		auto dir = refTarget.GetTargetPos() - mPosition;
		dir.y = 0;
		if (ERefFaceTo::OppTarget == faceTo)
		{
			dir.x = -dir.x;
			dir.y = -dir.y;
			dir.z = -dir.z;
		}
		SetPosRot(mPosition, dir, false);
		SetRot(dir, true);
	}

	mChoosedSkill = mRageSkill;
	//Try cancel current skill executor if exists
	SkillInterrupted(mCurSkillExecutor);
	mFsm->DoTransition(mTransToExecuteSkill);

	return 1;
}

void Unit::TryExecuteRageSkillBreakNormalAuto()
{
	if (!mRageSkillAutoReady) 
		return;
	if (!mRageSkill) //mRageSkill could be removed by ShapeShifting process 
		return;

	if (mCurSkill && (mCurSkill->IsNormalSkill() || mCurSkill->mRageSkillInterruptable || (mHp * DENOM / mMaxHp <= 1000)))
		TryExecuteRageSkillAuto();
}

int Unit::TryExecuteRageSkillAuto()
{
	if (GetBattleInstance().IsInRageSkill(1) || GetBattleInstance().IsInRageSkill(2))
		return 0;
	if (mRageSkillAutoReady && mRageSkill)
	{
		if (mArmy->GetId() == 2)
		{  //enemy
			if (mCurSkill && mCurSkill->IsRageSkill())
				return 0;
			if (mFsm->IsInState(mStateBeControlled->GetId()) ||  //TODO: DELETE IT 
				mFsm->IsInState(mStateBehaviour->GetId()))
			{
				return 0;
			}
			if (mRageSkill->CanExecute() == CheckResult::Pass && TryExecuteRageSkill() == 1)
			{
				mRageSkillAutoReady = false;
				return 1;
			}
		}
		else if (GetBattleInstance().IsAuto() || mRageSkill->mAutoRageSkill)
		{  //friend
		   if (!mRageSkillManualReady || (mCurSkill && mCurSkill->IsRageSkill()))
				return 0;
		   if (mFsm->IsInState(mStateBeControlled->GetId()) ||
			   mFsm->IsInState(mStateBehaviour->GetId()))
		   {
			   return 0;
		   }
		   if (mRageSkill->CanExecute() == CheckResult::Pass && TryExecuteRageSkill() == 1)
		   {
			   mRageSkillAutoReady = false;
			   return 1;
		   }
		}
	}
	return 0;
}

int Unit::ManuallyExecuteUnparalleledSkill()
{
	if (!mUnparalleledSkillReady || (mCurSkill && mCurSkill->IsUnparallelledRageSkill()))
	{
		return 0;
	}
	mChoosedSkill = mUnparalleledSkill;
	//Try cancel current skill executor if exists
	SkillInterrupted(mCurSkillExecutor);
	mFsm->DoTransition(mTransToExecuteSkill);

	return 1;
}

void Unit::SetRageSkillState(RageSkillExecuteState* aState)
{
    mRageSkillExecuteState = aState;
}

RageSkillExecuteState* Unit::GetRageSkillState()
{
    return mRageSkillExecuteState;
}

bool Unit::IsInRageSkillMaskTime() const
{
	return mCurSkill && mCurSkill->IsRageSkill()
		&& mCurSkillExecutor
		&& (mUnitTime <= mCurSkillExecutor->GetStartTime() + mCurSkill->GetSkillConf()->basedata().skillshowtime() );
    
}

void Unit::TryReceiveBuff(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aSourceUtilizer, int const aBuffId, int const aLevel, WeakPtr<Skill> aAncestorSkill, int aBTDel, bool aAbleToInterrupt)
{
	if (IsDead() || IsDying())
	{
		return;  //a Dead Unit should not receive any buff(confirmed with jialing)
	}
    bool received = mBuffMgr->TryAddBuff(aUtilizer, aSourceUtilizer, aBuffId, aLevel, aAncestorSkill, aBTDel, aAbleToInterrupt);
	LOG_DEBUG("Unit %d try receive buff {id=%d received=%d}", mEntityId, aBuffId, received);
	
}

void Unit::SkillInterrupted(const SharedPtr<SkillExecutor>& aSkillExecutor, bool aIsPassive, bool aNoEvent)
{
    if (!aSkillExecutor)
        return;
	int skillId = aSkillExecutor->GetSkill()->GetId();
    if (mCurSkillExecutor.Get() == aSkillExecutor.Get())
    {       
		LOG_DEBUG("unit:%d skill:%d interrupted", GetEntityId(), mCurSkillExecutor->GetSkill()->GetId()); 
        mView->Execute(ViewCommand::SkillInterrupted, mEntityId, aSkillExecutor->GetSkill()->GetId()); 
		if (!GetBattleInstance().IsFieldEnd()
			&& !mFsm->IsInState(mStateDead->mId)
			&& !mFsm->IsInState(mStateDying->mId)
			&& !IsEmptyHp())
		{
			if (mCurSkillExecutor->GetSkill()->IsMasterRageSkill())
			{
				if (mCurSkillExecutor->mBeginTime + mCurSkillExecutor->GetSkill()->GetPerfectInterruptDuration() >= mUnitTime)
				{ //perfect interrupt only happens within certain duration 
					SendScreenTextCmd(mRage >= mRageSkillThreshold ? ScreenTextType::Interrupt : ScreenTextType::PerfectInterrupt, int64(mCurSkillExecutor->GetSkill()->mIsIgnoreInterruptEffect));
				}
			}
			if (!aNoEvent)
			{
				int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterInterrupt));
				GetBattleInstance().DispatchEvent(key, GetArmyId(), mEntityId, skillId);
			}
		}
    }
	//in case cur skill has been interrupted later in the func call stack 
	if (mCurSkillExecutor && aSkillExecutor)
	{
		for (auto& exec : mSkillExecutorArr)
		{
			if (!mCurSkillExecutor)
				return;
			exec->WhenSomeSkillInterrupted(aSkillExecutor);
		}
		if (!mCurSkillExecutor)
			return;
		aSkillExecutor->Interrupt();
		CheckSkillExecutor();
	}
}

void Unit::CurrentSkillInterrupted(bool aNoEvent)
{
    SkillInterrupted(mCurSkillExecutor, false, aNoEvent);
	mFsm->DoTransition(mTransSkillEnded);
}

void Unit::NormalSkillInterrupted()
{
    if (mCurSkillExecutor && mCurSkillExecutor->GetSkill()->IsNormalSkill())
    {
        SkillInterrupted(mCurSkillExecutor);
		mFsm->DoTransition(mTransSkillEnded);
    }
}

void Unit::OtherSkillInterrupted()
{
    if (mCurSkillExecutor && !mCurSkillExecutor->GetSkill()->IsNormalSkill())
    {
        SkillInterrupted(mCurSkillExecutor);
		mFsm->DoTransition(mTransSkillEnded);
    }
}

void Unit::SmallSkillInterrupted()
{
	if (mCurSkillExecutor && 
		!mCurSkillExecutor->GetSkill()->IsNormalSkill() && 
		!mCurSkillExecutor->GetSkill()->IsRageSkill())
	{
		SkillInterrupted(mCurSkillExecutor);
		mFsm->DoTransition(mTransSkillEnded);
	}
}

void Unit::RageSkillInterrupted()
{
	if (mCurSkillExecutor &&
		mCurSkillExecutor->GetSkill()->IsRageSkill())
	{
		SkillInterrupted(mCurSkillExecutor);
		mFsm->DoTransition(mTransSkillEnded);
	}
}

bool Unit::AbleToInterrupt(int aAtkerEnergyLv, bool aIsPhysical)
{
	if (!mBossDefActive || !mCurSkillExecutor || !mCurSkillExecutor->GetSkill()->mGroundMeshSkill)
		return true;

	if (aAtkerEnergyLv < mCurSkillExecutor->GetSkill()->mEnergyLv)
		return false;

	switch (mDefType)
	{
	case 0:
		//all
		return true;
	case 1:
		//phy
		return aIsPhysical;
	case 2:
		//mag
		return !aIsPhysical;
	default:
		return true;
	}
	return true;
}

// clean up mSkillExecutorArr, drop all InActived SkillExecutors
void Unit::CheckSkillExecutor()
{
    if (mSkillExecutorArr.size() <= 0)
        return;
    for (int i = 0; i < mSkillExecutorArr.size() - 1;)
    {
        if (mSkillExecutorArr[i]->IsInactive())
        {
    		mSkillExecutorArr[i] = mSkillExecutorArr.back();
            mSkillExecutorArr.pop_back();
        }
        else
        {
            ++i;
        }
    }
    if (mSkillExecutorArr.back()->IsInactive())
    {
        mSkillExecutorArr.pop_back();
    }
}

void Unit::RegisterSkillOnHpEntry(BuffModSkillOnHpEntry* aEntry)
{
	mTriggerOnHpSkillArr.emplace_back(aEntry);
	TryTriggerSkillOnHp();
}

void Unit::UnregisterSkillOnHpEntry(BuffModSkillOnHpEntry* aEntry)
{
	auto size = mTriggerOnHpSkillArr.size();
	for (int i = 0; i < size; i++)
	{
		if (mTriggerOnHpSkillArr[i] == aEntry)
		{
			mTriggerOnHpSkillArr[i] = mTriggerOnHpSkillArr[size - 1];
			size--;
			break;
		}
	}
	mTriggerOnHpSkillArr.resize(size);
}

void Unit::AddBarrier(SharedPtr<SceneBarrier> aBarrier)
{
	mSceneBarrierArr.emplace_back(aBarrier);
}

void Unit::TickBarrier(int const aDeltaTime)
{
	if (mSceneBarrierArr.size() <= 0)
	{
		return;
	}
	auto j = mSceneBarrierArr.size();
	for (int i = 0; i < j; )
	{
		mSceneBarrierArr[i]->OnTick(aDeltaTime);
		if (mSceneBarrierArr[i]->IsValid() == false)
		{
			j--;
			auto tmp = mSceneBarrierArr[i];
			if (i < j)
			{
				mSceneBarrierArr[i] = mSceneBarrierArr[j];
			}
			tmp->ClearView();
			SharedPool<SceneBarrier>::PutRaw(tmp.Get());
		}
		else
		{
			i++;
		}
	}
	mSceneBarrierArr.resize(j);
}

void Unit::OnDodge(const SharedPtr<Unit>& aUtilizer, int aSkillId)
{
	auto dir = GetPosition() - aUtilizer->GetPosition();
    mView->Execute(ViewCommand::Dodge, mEntityId, dir.x, dir.y, dir.z);
	//No need to SendScreenTextCmd
    //TryTriggerSkill(ETriggerMajor::AfterDodge);
	int key1 = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterDodge));
	GetBattleInstance().DispatchEvent(key1, mArmy->GetId(), mEntityId, aSkillId);
	int key2 = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterDodge), static_cast<int>(ETriggerAfterDodgeSub::Skill));
	GetBattleInstance().DispatchEvent(key2, mArmy->GetId(), mEntityId, aSkillId);
	int key3 = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterDodge), static_cast<int>(ETriggerAfterDodgeSub::SkillWithRef));
	GetBattleInstance().DispatchEvent(key3, mArmy->GetId(), mEntityId, aSkillId);
}

void Unit::OnExemption(const SharedPtr<Unit>& aUtilizer)
{
	auto dir = GetPosition() - aUtilizer->GetPosition();
    mView->Execute(ViewCommand::Exemption, mEntityId, dir.x, dir.y, dir.z);
    //TryTriggerSkill(ETriggerMajor::AfterImmune);
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterImmune));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnParry(ETriggerAfterParrySub aSub, int aSkillId, int aUtilizerId)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterParry), static_cast<int>(aSub));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, aSkillId, aUtilizerId);
}

void Unit::OnSkillMoveDone(int aSkillId)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterHitHandlerMove));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, aSkillId);
}

void Unit::OnRageSkill()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterRageSkill));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnRageSkillWithRef()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterRageSkillWithRefTarget));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnReflectSkill(int aSkillId)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterSkillReflected));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, aSkillId);
}

void Unit::OnApplyUnlimitedShield(int aUtilizerId)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterApplyUnlimitedShield));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, aUtilizerId);
}

void Unit::OnShieldEnabled()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterShield));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnCritical(Unit* aUtilizer)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterCritical));
	GetBattleInstance().DispatchEvent(key, aUtilizer->GetArmyId(), aUtilizer->GetEntityId());
}

void Unit::OnBeCritical()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterBeCritical));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnDizzy()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterDizzy));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnBuffSubtypeActive(BuffSubType aSubType)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterBuffSubtype));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, static_cast<int>(aSubType));
}

void Unit::OnResist()
{
    //mView->Execute(ViewCommand::Resist, mEntityId);
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterResist));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnDispelBuff(Unit* aTarget)
{
	if (mArmy->GetId() != aTarget->GetArmy().GetId())
	{ //驱散敌方buff时 
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterDispelEnemyBuff));
		GetBattleInstance().DispatchEvent(key, GetArmyId(), mEntityId);
	}
}

void Unit::OnDamage(ETriggerAfterDmgSub aSub, int aSkillId, int aUtilizerId, int64 aDmg)
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterDmg), static_cast<int>(aSub));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId, aSkillId, aUtilizerId, aDmg);
}

void Unit::OnBeSummoned()
{
	if (!mIsDummy)
	{
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::SummonWithRefTarget));
		GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
	}
}

void Unit::OnAnimSkill()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterSkillWithAnim));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnBeRevived()
{
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::ReviveWithRefTarget));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
}

void Unit::OnHealOverflow(int aBuffId, int64 aOverFlow)
{
	if (!mBuffMgr->HasBuff(aBuffId))
	{
		TryReceiveBuff(SharedFromThis(), SharedFromThis(), aBuffId, 1);
	}
	vector<BuffMod*> modArr = mBuffMgr->SearchMod(BuffSubType::AbsorbDamage);
	for (auto& m : modArr)
	{
		auto* shieldMod = static_cast<BuffModAbsorbDamage*>(m);
		if (shieldMod->GetBuff()->GetId() == aBuffId)
		{
			shieldMod->AddValues(aOverFlow);
		}
	}
	RestoreVectorToPool(modArr);
}

void Unit::OnHit(const SharedPtr<Unit>& aUtilizer, int const aSkillId, BeHitType aShouldPlayHitAnim, const bool aSkipDmg)
{
    bool willPlayHitAnim = static_cast<bool>(aShouldPlayHitAnim) && !CheckStateAdjust(StateAdjust::HitDownImmunity);
    if (mCurSkillExecutor)
    {
		auto skillNeedPlayHitAnim = mCurSkillExecutor->WillPlayHitAnim();
		if (skillNeedPlayHitAnim && static_cast<bool>(aShouldPlayHitAnim) && CheckStateAdjust(StateAdjust::HitDownImmunity))
		{
			SendScreenTextCmd(ScreenTextType::HitDownImmunity);
		}
		else
		{
			willPlayHitAnim = willPlayHitAnim ? skillNeedPlayHitAnim : willPlayHitAnim;
		}
    }
	else
	{
		if (static_cast<bool>(aShouldPlayHitAnim) && CheckStateAdjust(StateAdjust::HitDownImmunity))
		{
			SendScreenTextCmd(ScreenTextType::HitDownImmunity);
		}
	}
    Vector3 dir;
	if (aUtilizer.Get() == this)
	{
		dir.Set(GetForward());
		dir *= -1;
	}
	else
	{
		dir.Set(GetPosition());
		dir -= aUtilizer->GetPosition();
	}

    if (!willPlayHitAnim)
    {  //TODO: remove the third param from SkillHit CMD 
        mView->Execute(ViewCommand::SkillHit, mEntityId, aSkillId, static_cast<int>(false), dir.x, dir.y, dir.z);
		if (!aSkipDmg && 
			!CheckStateAdjust(StateAdjust::HitDownImmunity) && 
			strcmp(GetCurrentAnimName(), ANIM_NAME_IDLE) == 0 &&
			!IsInRageSkillMaskTime())
		{//play hit anim anyway if current anim is Idle
			mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::MoveBySkill, ANIM_NAME_HIT_FAKE);
		}
		RestoreObjToPool(dir);
        return;
    }

	//the forth param equals "false" means only play effect at front end
	mView->Execute(ViewCommand::SkillHit, mEntityId, aSkillId, static_cast<int>(false), dir.x, dir.y, dir.z);
	RestoreObjToPool(dir);

	if (aSkipDmg)
	{
		return;
	}
	
	//Check if: From None-BeCtrl to BeCtrl caused Directly by "Hit"
    if (!mFsm->IsInState(mStateBeControlled->GetId()))
    {
		SkillInterrupted(mCurSkillExecutor, true);
		DisableMove();
		mFsm->DoTransition(mTransBeControlled);  // it's better to merge behit into bectrl state
    }
	//Now: From BeCtrl state
	auto anim = ANIM_NAME_HIT;
	auto duration = mHitTimeLength;
	switch (aShouldPlayHitAnim)
	{
    case BeHitType::Hit:
		break;
	case BeHitType::Down:
		anim = ANIM_NAME_DOWN;
		duration = mDownTimeLength;
		break;
	case BeHitType::Knock:
		anim = ANIM_NAME_KNOCK;
		duration = mKnockTimeLength;
		break;
	default:
		LOG_WARN("unknow BeHitType:%d", aShouldPlayHitAnim);
	}
	ScheduleControlToken(anim, duration);
}

SharedPtr<ControlToken> Unit::ScheduleControlToken(const char* aAnimName, int aDuration)
{
	auto beHitTimer = SharedPool<Timer<Unit> >::Get();
	auto controlStateByHit = GetControlToken(aAnimName);
	bool hasToken = false;
	int expireTime = mUnitTime + aDuration;
	LOG_DEBUG("Unit %d ScheduleControlToken, name=%s, duration=%d, expireTime=%d, HitArrSize=%d",
		mEntityId, aAnimName, aDuration, expireTime, mControlStateByHitArr.size());
	for (auto token : mControlStateByHitArr)  //make sure no duplicated elems in arr
	{
		if (token == controlStateByHit)
		{
			hasToken = true;
			break;
		}
	}
	if (hasToken)
	{
		if (controlStateByHit->mReplayable)
		{
			controlStateByHit->mTimeOut = expireTime;  //reset time if is replayable
		}
		else
		{
			expireTime = controlStateByHit->mTimeOut;  //keep old one
		}
	}
	else
	{
		controlStateByHit->mTimeOut = expireTime;
		mControlStateByHitArr.emplace_back(controlStateByHit);
	}
	BeControlled(*controlStateByHit);
	beHitTimer->Execute(mTimerMgr.Get(), this, &Unit::CleanUpBeCtrlState, expireTime);
	return controlStateByHit;
}

//TODO: DELETE IT
//no need to use CallbackBeHitEnded to trans FSM back from BeCtrl state, wheneven mCtrlStateStack is clean, it will trans automaticly
//bool Unit::CallbackBeHitEnded(Timer<Unit>&)
//{
//    //mFsm->DoTransition(mTransBeHitEnd);
//	mFsm->DoTransition(mTransBeControlledEnd);
//	mBeHitTimer.Release();
//    return false;
//}

//callback func when a ctrlstate times up
//will find out correct struct from vector mControlStateByHitArr based on time point
bool Unit::CleanUpBeCtrlState(Timer<Unit>&)
{
	int p = mControlStateByHitArr.size()-1;
	for (int idx = 0; idx <= p; idx++)
	{
		if (mControlStateByHitArr[idx]->mTimeOut <= mUnitTime)
		{
			if (idx != p)
			{
				auto tmp = mControlStateByHitArr[idx];
				mControlStateByHitArr[idx] = mControlStateByHitArr[p];
				mControlStateByHitArr[p] = tmp;
			}
			p--;
		}
	}
	int newSize = p + 1;
	LOG_DEBUG("Unit %d CleanUpBeCtrlState, newSize=%d, hitArrSize=%d", mEntityId, newSize, mControlStateByHitArr.size());
	for (int idx = p + 1; idx < mControlStateByHitArr.size(); idx++)
	{
		ClearBeControlled(*mControlStateByHitArr[idx]);
	}
	mControlStateByHitArr.resize(newSize);
	return false;
}



void Unit::DealingDamageByBuff(int64 const aDamage)
{
    mDamageOutTotal += aDamage;
	if (GetBattleInstance().NeedDoStatistics())
	{
		mTotalPhycialDamage += aDamage;
	}
}

void Unit::DealingDamage(int64 const aDamage, int64 const aHp, int64 const aMaxHp, Unit* aTarget, bool aIsPhy)
{
    mDamageOutTotal += aDamage;

	if (IsSummoned())
	{
		mSummoner->mDamageOutTotal += aDamage;
		if (GetBattleInstance().NeedDoStatistics())
		{
			if (aIsPhy)
			{
				mSummoner->mTotalPhycialDamage += aDamage;
			}
			else
			{
				mSummoner->mTotalMagicalDamage += aDamage;
			}
		}
	}
}

bool Unit::HasBuffBySubType(BuffSubType aSubType)
{
	if (mBuffMgr)
		return mBuffMgr->CheckBuffExistenceBySubType(aSubType);
	return false;
}

bool Unit::HasBuffBySubTypes(vector<BuffSubType>& aList)
{
	if (mBuffMgr)
		return mBuffMgr->CheckBuffExistenceBySubTypeOR(aList);
	return false;
}

int64 Unit::Damage(HitResult& aResult, Unit* aUtilizer, const Skill* aSkill, const Buff* aBuff, bool aIgnoreRage)
{
	if (aUtilizer == nullptr)
	{
		LOG_FATAL("aUtilizer is null");
		return 0;
	}
    if (IsDead())
        return 0;
    if (!aResult.mIsHit && !aBuff)
        return 0;
	int skillId = 0;
	if (aSkill) skillId = aSkill->GetId();
	int buffId = 0;
	if (aBuff) buffId = aBuff->GetId();
	int utilizerId = aUtilizer->GetEntityId();
	if (aResult.mIsBlock)
	{
		if (aResult.mIsPhysical)
		{
			OnParry(ETriggerAfterParrySub::Any, skillId, utilizerId);
			if (aResult.mIsMelee)
			{
				OnParry(ETriggerAfterParrySub::Melee, skillId, utilizerId);
			}
			else
			{
				OnParry(ETriggerAfterParrySub::Range, skillId, utilizerId);
			}
			if (skillId > 0)
			{
				OnParry(ETriggerAfterParrySub::Skill, skillId, utilizerId);
				OnParry(ETriggerAfterParrySub::SkillWithRef, skillId, utilizerId);
			}
		}
		else
		{
			OnResist();
		}
	}
    int64 damage = aResult.mValue;
	if (CheckStateAdjust(StateAdjust::DamageImmunityAll))
	{
		damage = 0;
		SendScreenTextCmd(ScreenTextType::DamageImmunityAll);
	}
	
    if (damage > 0 && aSkill)
    {
		if (aSkill->IsPhysicalSkill() && CheckStateAdjust(StateAdjust::DamageImmunityPhysical))
		{
			damage = 0;
			SendScreenTextCmd(ScreenTextType::DamageImmunityPhysical);
		}
		else if (!aSkill->IsPhysicalSkill() && CheckStateAdjust(StateAdjust::DamageImmunityMagic))
		{
			damage = 0;
			SendScreenTextCmd(ScreenTextType::DamageImmunityMagical);
		}
		
    }
	
	if (damage > 0 && CheckStateAdjust(StateAdjust::AbsorbDamage) && !aUtilizer->CheckStateAdjust(StateAdjust::IgnoreShield))
	{
		if (!aSkill || !aSkill->mIsIgnoreShield)
		{
			vector<BuffMod*> modArr = mBuffMgr->SearchMod(BuffSubType::AbsorbDamage);
			for (auto& m : modArr)
			{
				auto origDmg = damage;
				auto modAbsorb = static_cast<BuffModAbsorbDamage*>(m);
				damage = modAbsorb->OnActive(damage, aResult.mIsPhysical, skillId, utilizerId);
				if (damage == origDmg && !modAbsorb->IsCounterShield())
				{ //absorb damage type mis-match, just skip
					continue;
				}
				if (GetBattleInstance().NeedDoStatistics())
				{
					auto& sourceUtilizer = m->GetBuff()->GetSourceUtilizer();
					if (sourceUtilizer && !sourceUtilizer.Expired())
					{
						sourceUtilizer->mTotalAbsorbBlood += (origDmg - damage);
					}
				}
				if (damage > 0)  //an absorbMod has just used up! so remove it immediately.
				{
					auto id = m->GetBuff()->GetId();
					mBuffMgr->RemoveBuff(id, false, true); //the last true allows BuffModSkillOnEnd tryExecute skill at the end
				}
				else
				{
					break;
				}
			}
			RestoreVectorToPool(modArr);
		}
	}
    if (damage > 0)
    {
		//auto origDeadMan = mDeadNum;  //TODO: DELETE IT 
		auto displayDamage = damage;  //for display
        damage = DamageBy(damage, aIgnoreRage);   //actual damage 
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WhenApplyDamage));
		GetBattleInstance().DispatchEvent(key, aUtilizer->GetArmyId(), aUtilizer->GetEntityId(), 0, damage);
		if (aUtilizer->mFirstHitDone == false)
		{
			aUtilizer->mFirstHitDone = true;
			int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WhenFirstApplyDamage));
			GetBattleInstance().DispatchEvent(key, GetArmyId(), GetEntityId(), aUtilizer->GetEntityId(), damage);
		}
		//aUtilizer->IncKillNum(mDeadNum - origDeadMan);
        mBuffMgr->CheckEndOnDamage();
        aUtilizer->DealingDamage(damage, mHp, mMaxHp, this, aResult.mIsPhysical);
        auto& dir = aResult.mSkillDir;
		if (GetBattleInstance().NeedDoStatistics())
		{
			if (aResult.mIsPhysical)
			{
				aUtilizer->mTotalPhycialDamage += damage;
			}
			else 
			{
				aUtilizer->mTotalMagicalDamage += damage;
			}
		}
		if (aResult.mIsCrit)
		{ // try trigger crit events 
			OnCritical(aUtilizer);
			OnBeCritical();
		}
        if (aSkill)
        {
			int textShiftCt = 0;
			if (aUtilizer->HasTextShift(aSkill->GetId())) {
				textShiftCt = aUtilizer->GetTextShift(mEntityId) + 1;  //just make sure this ct > 0
			}
            mView->Execute(ViewCommand::Damage, mEntityId, displayDamage, mHp, aUtilizer->GetEntityId(), aSkill->GetId(), 0, static_cast<int>(aResult.mIsCrit), dir.x, dir.y, dir.z, aResult.mDamageSpecialType, textShiftCt);
			LOG_DEBUG("Unit %d damaged {value=%d current=%d} by skill {utilizer=%d skillId=%d}"
                , mEntityId
                , displayDamage
                , mHp
                , aUtilizer->GetEntityId()
                , aSkill->GetId());
        }
        if (aBuff)
        {
			//TODO: add block info
            mView->Execute(ViewCommand::Damage, mEntityId, displayDamage, mHp, aUtilizer->GetEntityId(), 0, aBuff->GetId(), static_cast<int>(aResult.mIsCrit), dir.x, dir.y, dir.z, aResult.mDamageSpecialType, 0);
			LOG_DEBUG("Unit %d damaged {value=%d current=%d} by buff {utilizer=%d buffId=%d}"
                , mEntityId
                , displayDamage
                , mHp
                , aUtilizer->GetEntityId()
                , aBuff->GetId());
        }
        if (mHp <= 0)
        {
            mHp = 0;
            //TryTriggerSkill(ETriggerMajor::BeforeDeath);
			int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::BeforeDeath));
			GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
            if (mHp <= 0)
            {
				mDieCause.rageBonus = 0;
				if (!mKiller)
				{  //TODO: use owner of <aSkill or aBuff>'s ancestor skill
					mKiller = aUtilizer;
				}
				if (aSkill)
				{
					mDieCause.cause = EUnitDieCause::Skill;
					mDieCause.data = aSkill->GetId();
					if (aSkill->GetSkillConf()->basedata().has_deathanim())
					{
						mDieCause.animName = aSkill->GetSkillConf()->basedata().deathanim().c_str();
					}
					if (aSkill->GetSkillConf()->basedata().has_ragebonusafterkill())
					{
						mDieCause.rageBonus = aSkill->GetSkillConf()->basedata().ragebonusafterkill();
					}
				}
				else if (aBuff)
				{
					mDieCause.cause = EUnitDieCause::Buff;	
					mDieCause.data = aBuff->GetId();
				} 
				if (!IsDead())
				{
					mTTL = GetBattleInstance().GetGameTime();
					mFsm->DoTransition(mTransDead);
				}
				/*else
				{
					if (aSkill)
						LOG_WARN("Deal Dmg to a dead man: %d, SkillId = %d", mTplId, aSkill->GetId());
					if (aBuff)
						LOG_WARN("Deal Dmg to a dead man: %d, BuffId = %d", mTplId, aBuff->GetId());
				}*/
            }
        }
		else
		{
			OnDamage(ETriggerAfterDmgSub::Any, skillId, utilizerId, damage);
			if (aResult.mIsMelee)
			{
				OnDamage(ETriggerAfterDmgSub::Melee, skillId, utilizerId, damage);
			}
			else
			{
				OnDamage(ETriggerAfterDmgSub::Range, skillId, utilizerId, damage);
			}
			if (skillId > 0)
			{
				OnDamage(ETriggerAfterDmgSub::Skill, skillId, utilizerId, damage);
			}
			if (aSkill && aSkill->IsPartOfRageSkill())
			{
				OnDamage(ETriggerAfterDmgSub::RageSkill, skillId, utilizerId, damage); 
			}
			if (aResult.mIsPhysical)
			{
				OnDamage(ETriggerAfterDmgSub::Phy, skillId, utilizerId, damage);
			}
			else
			{
				OnDamage(ETriggerAfterDmgSub::Mag, skillId, utilizerId, damage);
			}
			TryTriggerSkillOnHp();
		}
    }
	if (damage > 0 && GetBattleInstance().NeedDoStatistics())
	{
		if (aResult.mIsPhysical)
		{
			mPhycialDamageUndertake += damage;
			if (aSkill && aSkill->mAncestorSkill && !aSkill->mAncestorSkill.Expired())
				aSkill->mAncestorSkill->mTotalPhysicalDamge += damage;
			else if (aBuff && aBuff->mAncestorSkill && !aBuff->mAncestorSkill.Expired())
				aBuff->mAncestorSkill->mTotalPhysicalDamge += damage;
			if (IsSummoned())
			{
				mSummoner->mPhycialDamageUndertake += damage;
			}
		}
		else
		{
			mMagicalDamageUndertake += damage;
			if (aSkill && aSkill->mAncestorSkill && !aSkill->mAncestorSkill.Expired())
				aSkill->mAncestorSkill->mTotalMagicalDamge += damage;
			else if (aBuff && aBuff->mAncestorSkill && !aBuff->mAncestorSkill.Expired())
				aBuff->mAncestorSkill->mTotalMagicalDamge += damage;
			if (IsSummoned())
			{
				mSummoner->mMagicalDamageUndertake += damage;
			}
		}
	}
    return damage;
}

int64 Unit::Heal(HitResult& aResult, Unit* aUtilizer, const Skill* aSkill, const Buff* aBuff)
{
	if (aUtilizer == nullptr)
	{
		LOG_FATAL("aUtilizer is null");
		return 0;
	}
    if (IsDead())
        return 0;
    int64 heal = aResult.mValue;
    int64 actHeal = HealBy(heal);
	aUtilizer->RecordHealOut(actHeal);
    //TryTriggerSkill(ETriggerMajor::AfterHeal);
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterHeal));
	GetBattleInstance().DispatchEvent(key, mArmy->GetId(), mEntityId);
	if (GetBattleInstance().NeedDoStatistics())
	{
		aUtilizer->mTotalHeal += actHeal;
		if (aSkill && aSkill->mAncestorSkill && !aSkill->mAncestorSkill.Expired())
			aSkill->mAncestorSkill->mTotalHeal += actHeal;
		else if (aBuff && aBuff->mAncestorSkill && !aBuff->mAncestorSkill.Expired())
			aBuff->mAncestorSkill->mTotalHeal += actHeal;
	}
    if (aSkill)
    {
        mView->Execute(ViewCommand::Heal, mEntityId, heal, mHp, aUtilizer->GetEntityId(), aSkill->GetId(), 0, static_cast<int>(aResult.mIsCrit), 0);
		LOG_DEBUG("Unit %d healed {value=%d current=%d} by skill {utilizer=%d skillId=%d}"
            , mEntityId
            , heal
            , mHp
            , aUtilizer->GetEntityId()
            , aSkill->GetId());
    }
    if (aBuff)
    {
        mView->Execute(ViewCommand::Heal, mEntityId, heal, mHp, aUtilizer->GetEntityId(), 0, aBuff->GetId(), static_cast<int>(aResult.mIsCrit), 0);
		LOG_DEBUG("Unit %d healed {value=%d current=%d} by buff {utilizer=%d buffId=%d}"
            , mEntityId
            , heal
            , mHp
            , aUtilizer->GetEntityId()
            , aBuff->GetId());
    }
    return actHeal;
}

void Unit::HealByStealHp(int64 const aHpDelta, const Skill* aSkill, const Buff* aBuff)
{
	if (mHp <= 0)
		return;
    if (IsDead())
        return;

	int64 actHeal = IncByRate(aHpDelta, DENOM, DENOM);
    actHeal = HealBy(actHeal);
	RecordHealOut(actHeal);
    if (aSkill)
    {
		if (GetBattleInstance().NeedDoStatistics())
		{
			mTotalSuckBlood += actHeal;
			if (aSkill->mAncestorSkill && !aSkill->mAncestorSkill.Expired())
				aSkill->mAncestorSkill->mTotalSuckBlood += aHpDelta;
		}
        mView->Execute(ViewCommand::Heal, mEntityId, aHpDelta, mHp, mEntityId, aSkill->GetId(), 0, 0, 1);
		LOG_DEBUG("Unit %d healed(steal hp) {value=%d current=%d} by skill {skillId=%d}"
            , mEntityId
            , aHpDelta
            , mHp
            , aSkill->GetId());
    }
    if (aBuff)
    {
		if (GetBattleInstance().NeedDoStatistics())
		{
			mTotalSuckBlood += aHpDelta;
			if (aBuff->mAncestorSkill && !aBuff->mAncestorSkill.Expired())
				aBuff->mAncestorSkill->mTotalSuckBlood += aHpDelta;
		}
        mView->Execute(ViewCommand::Heal, mEntityId, aHpDelta, mHp, mEntityId, 0, aBuff->GetId(), 0, 1);
		LOG_DEBUG("Unit %d healed(steal hp) {value=%d current=%d} by buff {buffId=%d}"
            , mEntityId
            , aHpDelta
            , mHp
            , aBuff->GetId());
    }
}

int64 Unit::DamageBy(int64 const aValue, bool aIgnoreRage)
{
    int64 actualDamage = aValue;
    mHp -= aValue;
    mDamageInTotal += aValue;
	mDamageInWithOverflow += aValue;
	if (mHp <= 0)
    {
        actualDamage += mHp;
        mDamageInTotal += mHp;
        mHp = 0;
    }
    if (mMaxHp > 0 && !aIgnoreRage)
    {
        int64 r = actualDamage * BattleInstance::HpToRageDenom * mRageSkillThreshold / (BattleInstance::HpToRageNum * mMaxHp);//percent denom 
		if (r > 0)
		{ 
			AddRage(r, ERageChangeCause::OnDamage); 
		} 
    }
    if (mMaxHp <= 0)
    {
        mHp = 0;
        actualDamage = 0;
        LOG_WARN("unit:%d maxHp=0", mEntityId);
    }

    return actualDamage;
}

inline void Unit::SlgDamage(int const aValue)
{
	if (mSoldierStdHp <= 0)
	{
		LOG_DEBUG("unintialized SoldierStdHp or dummyUnit be hitted by others");
		mSoldierStdHp = 1;
	}
	int64 curTroopNum = mHp / mSoldierStdHp;
	if (curTroopNum * mSoldierStdHp < mHp) // ceil
		curTroopNum += 1;

	if (curTroopNum > mCurTroopNum) //compare with previous troop size
	{
		LOG_DEBUG("after damage %d, nextTroopNum[%d] > curTroopNum[%d]", aValue, curTroopNum, mCurTroopNum);
		curTroopNum = mCurTroopNum;
	}
	int64 affectedMan = mCurTroopNum - curTroopNum;
	int64 deadMan = affectedMan * mDeathRate / DENOM;
	int64 injuredMan = affectedMan - deadMan;

	mCurTroopNum = curTroopNum;
	mInjuredNum += injuredMan;
	mDeadNum += deadMan;

	mMaxHp = mSoldierStdHp * (mCurTroopNum + mInjuredNum);  //refresh slg Hp uplimits
}

int64 Unit::HealBy(int64 const aValue)
{
	int64 actualHeal = aValue;
	if (mHp + actualHeal > mMaxHp)
	{
		actualHeal = mMaxHp - mHp;
	}
    mHp += actualHeal;
	mRealHeal += actualHeal;

	return actualHeal;
}

void Unit::RecordHealOut(int64 aValue)
{
	mHealOutTotal += aValue;
}

inline void Unit::SlgHeal()
{
	int64 curTroopNum = mHp / mSoldierStdHp;
	if (curTroopNum * mSoldierStdHp < mHp) // ceil
		curTroopNum += 1;

	int healedSoldier = curTroopNum - mCurTroopNum;
	if (healedSoldier < 0)
	{
		LOG_DEBUG("healed Soldier num < 0, curTroopNum=%d, origTroopNum = %d", curTroopNum, mCurTroopNum);
		//healedSoldier = 0;
		SlgDamage(0);
	}

	mCurTroopNum = curTroopNum;
	mInjuredNum -= healedSoldier;
	if (mHp == mMaxHp && mInjuredNum != 0)
	{
		LOG_DEBUG("full heal, but still has injured soldier: %d", mInjuredNum);
		mInjuredNum = 0;
	}
}

void Unit::AddRage(int64 const aAmount, ERageChangeCause aCause)
{
	if (CheckStateAdjust(StateAdjust::NoRageRecover))
	{
		return;
	}
	int64 upRate = GetAttr(EAttribute::RageGrowthRate) + DENOM;
	int64 addValue = aAmount * upRate / DENOM;
	if (addValue < 0) addValue = 0;
    mRage = mRage + addValue;
    if (mRage >= mMaxRage)
        mRage = mMaxRage;
    mView->Execute(ViewCommand::AddRage, mEntityId, addValue, mRage, int(aCause) );
}

void Unit::SubRage(int64 const aAmount, ERageChangeCause aCause)
{
	if (aCause == ERageChangeCause::Buff)
	{
		if (CheckStateAdjust(StateAdjust::RageImmunity) || CheckStateAdjust(StateAdjust::RageImmunityBuffOnly))
			return;
	}
	if (aCause == ERageChangeCause::SkillBeSucked)
	{
		if (CheckStateAdjust(StateAdjust::RageImmunity) || CheckStateAdjust(StateAdjust::RageImmunitySkillOnly))
			return;
	}

	int64 decRate = GetAttr(EAttribute::RageDecRate) + DENOM;
	if (decRate < 0) decRate = 0;
	int64 decValue = aAmount * decRate / DENOM;
    mRage = mRage - decValue;
    if (mRage < 0)
        mRage = 0;
    mView->Execute(ViewCommand::SubRage, mEntityId, decValue, mRage, int(aCause));

	if (aCause == ERageChangeCause::Buff || aCause == ERageChangeCause::SkillBeSucked)
	{
		GetArmy().mSubRage += decValue;
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterSubRage));
		GetBattleInstance().DispatchEvent(key, GetArmyId(), mEntityId);
	}
}

void Unit::AddRageUnparallel(int64 const aAmount)
{
	mArmy->AddRage(aAmount);
}

void Unit::SubRageUnparallel(int64 const aAmount)
{
	mArmy->SubRage(aAmount);
}

void Unit::SkillUseRage(int64 aSubRageTime)
{
	if (aSubRageTime > 0)
	{
		mView->Execute(ViewCommand::SubRage, mEntityId, aSubRageTime, 0, int(ERageChangeCause::RageSkillCostSmoothly));
	}
	else
	{
		mView->Execute(ViewCommand::SubRage, mEntityId, mRage, 0, int(ERageChangeCause::RageSkillCost));
	}
	mRage = 0;
}

void Unit::SkillUseRageUnparallel()
{
	mArmy->SkillUseRage();
}

void Unit::ModifyActionSpeed(int const aPercent)
{
    mActionSpeedFactor += aPercent;
	mRealSpeedFactor = mActionSpeedFactor;
	if (mRealSpeedFactor < SPEED_FACTOR_DOWNLIMIT)
	{	//avoid DENOM + mActionSpeedFactor == 0 case
		mRealSpeedFactor = SPEED_FACTOR_DOWNLIMIT;
	}
	else if (mRealSpeedFactor > SPEED_FACTOR_UPLIMIT)
	{
		mRealSpeedFactor = SPEED_FACTOR_UPLIMIT;
	}
	if (mRealSpeedFactor == SPEED_FACTOR_BASE)
		ConditionSendActionSpeedCMD(ActionSpeedCondition::OnRevertSpeed);
}

/*
Rules of Sending Action Speed CMD:
	OnNormalBegin = 0,		//need apply factor if has
	OnNonnormalBegin = 1,   //need retrive factor to normal
	OnRecoverBegin = 2,     //need apply factor if has
	OnRecoverEnd = 3,		//need retrive factor to normal
	OnInterrupt = 4			//need retrive factor if has
	OnRevertSpeed = 5       //need send anyway
*/
void Unit::ConditionSendActionSpeedCMD(ActionSpeedCondition aCond)
{
	switch (aCond)
	{
	case ActionSpeedCondition::OnRevertSpeed:
		mLastAppliedSpeedFactor = mRealSpeedFactor;
		mView->Execute(ViewCommand::ActionSpeed, mEntityId, mRealSpeedFactor);
		break;
	case ActionSpeedCondition::OnNormalBegin:
		{
			if (mRealSpeedFactor != SPEED_FACTOR_BASE)
			{
				mLastAppliedSpeedFactor = mRealSpeedFactor;
				mView->Execute(ViewCommand::ActionSpeed, mEntityId, mRealSpeedFactor);
			}
		}
		break;
	case ActionSpeedCondition::OnNonnormalBegin:
		{
			if (mLastAppliedSpeedFactor != SPEED_FACTOR_BASE)
			{
				mLastAppliedSpeedFactor = SPEED_FACTOR_BASE;
				mView->Execute(ViewCommand::ActionSpeed, mEntityId, SPEED_FACTOR_BASE);
			}
		}
		break;
	case ActionSpeedCondition::OnRecoverBegin:
		{
			if (mLastAppliedSpeedFactor == SPEED_FACTOR_BASE && mRealSpeedFactor != SPEED_FACTOR_BASE)
			{
				mLastAppliedSpeedFactor = mRealSpeedFactor;
				mView->Execute(ViewCommand::ActionSpeed, mEntityId, mRealSpeedFactor);
			}
		}
		break;
	case ActionSpeedCondition::OnRecoverEnd:
		{
			if (mLastAppliedSpeedFactor != SPEED_FACTOR_BASE)
			{
				mLastAppliedSpeedFactor = SPEED_FACTOR_BASE;
				mView->Execute(ViewCommand::ActionSpeed, mEntityId, SPEED_FACTOR_BASE);
			}
		}
		break;
	case ActionSpeedCondition::OnInterrupt:
		{
			if (mLastAppliedSpeedFactor != SPEED_FACTOR_BASE)
			{
				mLastAppliedSpeedFactor = SPEED_FACTOR_BASE;
				mView->Execute(ViewCommand::ActionSpeed, mEntityId, SPEED_FACTOR_BASE);
			}
		}
		break;
	default:
		break;
	}
}

bool Unit::CheckStateAdjust(StateAdjust const aIndexEnum) const
{
    return mStateAdjustPropertyArr[static_cast<int>(aIndexEnum)] > 0;
}

void Unit::IncStateAdjust(StateAdjust const aIndexEnum)
{
    mStateAdjustPropertyArr[static_cast<int>(aIndexEnum)] += 1;
    LOG_DEBUG("Unit %d state adjust %d increased to %d", mEntityId, static_cast<int>(aIndexEnum), mStateAdjustPropertyArr[static_cast<int>(aIndexEnum)]);
}

void Unit::DecStateAdjust(StateAdjust const aIndexEnum)
{
    mStateAdjustPropertyArr[static_cast<int>(aIndexEnum)] -= 1;
    LOG_DEBUG("Unit %d state adjust %d decreased to %d", mEntityId, static_cast<int>(aIndexEnum), mStateAdjustPropertyArr[static_cast<int>(aIndexEnum)]);
}

bool Unit::CanBeRefTargetOfUtilizer(Unit* aUtilizer, Skill* aSkill)
{
	if ( CheckStateAdjust(StateAdjust::NonRefTarget)
		|| (CheckStateAdjust(StateAdjust::NonHostileRefTarget) && mArmy != &(aUtilizer->GetArmy()) ) )
	{
		return false;
	}
	if ( mSpecifyBeTargetSkillMap.empty() == false && aSkill )
	{  // this unit can only be target of certain skills 
		return mSpecifyBeTargetSkillMap.find(aSkill->GetId()) != mSpecifyBeTargetSkillMap.end();
	}
	return true;
}

bool Unit::CanBeEffTargetOfUtilizer(Unit* aUtilizer, Skill* aSkill)
{
	if (CheckStateAdjust(StateAdjust::NonEffTarget)
		|| (CheckStateAdjust(StateAdjust::NonHostileEffTarget) && mArmy != &(aUtilizer->GetArmy())) )
	{
		return false;
	}
	if (mSpecifyBeTargetSkillMap.empty() == false)
	{
		return mSpecifyBeTargetSkillMap.find(aSkill->GetId()) != mSpecifyBeTargetSkillMap.end();
	}
	return true;
}

bool Unit::IsLastAliveHeroInArmy()
{
	if (mIsDummy || IsSummoned() || IsEmptyHp()) return false;
	if (mArmy->CountNonSummonNonDummyUnit() == 1) return true;
	return false;
}

bool Unit::IsArmy2PVE()
{
	return mArmy->GetId() == 2 && mArmy->GetBattleInstance().IsPVE();
}

bool Unit::IsImmueToBuff(int const aBuffId, BuffType const aType, BuffSubType const aSubType) const
{
    if (mImmueBuffTypeArr[static_cast<int>(aType)] > 0)
        return true;
    if (mImmueBuffSubTypeArr[static_cast<int>(aSubType)] > 0)
        return true;
    for (auto p : mImmueBuffArr)
    {
        if (aBuffId == p.first)
            return true;
    }
    return false;
}

bool Unit::IsImmueToSkill(int const aSkillId, ESkillSubType const aType) const
{
    if (mImmueSkillTypeArr[static_cast<int>(aType)] > 0)
        return true;

    for (auto p : mImmueSkillArr)
    {
        if (aSkillId == p.first)
            return true;
    }
    return false;
}

bool Unit::IsImmuePropertyDec(EAttribute aAttr) const
{
	return mImmuePropertyArr[static_cast<int>(aAttr)] > 0;
}

void Unit::Revive(int const aHp, int const aLifeTime, bool const aClearOnCutscene, bool const aResetSkillCD)
{
	mDieCause.Reset();
	DisableMove();
	if (IsDead())
		mArmy->UnitDeadStatusChanged(this);  //prevent this unit is dead, but still in ActionTickDead state
    mFsm->DoTransition(mTransRevive);
    mHp = aHp;
	UpdateAgent();
    mView->Execute(ViewCommand::Heal, mEntityId, aHp, mHp, 0, 0, 0, 0, 0);
    if (aLifeTime > 0)
    {
        SetTimedLife(aLifeTime, aClearOnCutscene);
    }
    if (aResetSkillCD)
    {
        for (auto& skill : mSkillArr)
        {
            skill->ResetCD();
        }
    }
}

void Unit::SetSummoner(Unit* aSummoner)
{
    mSummoner = aSummoner;
}

void Unit::SetAncestorSkill(WeakPtr<Skill> aSkill)
{
	mAncestorSkill = aSkill;
}


bool Unit::IsSummonedBy(const Unit* aUnit) const
{
    return mSummoner == aUnit;
}

bool Unit::IsEnemyRageShow() const
{
	if (mRageSkill)
	{
		return mRageSkill->mEnemyShowRage;
	}
	return false;
}

void Unit::SetTimedLife(int const aTime, bool const aKeepOnCutscene)
{
    mClearOnCutscene = !aKeepOnCutscene;
    auto& battle = GetBattleInstance();
    mTimedLife = SharedPtr<Timer<Unit> >(new Timer<Unit>);
    mTimedLife->Execute(battle.GetTimerMgr(), this, &Unit::TimedUnitExpire, battle.GetFrameTime() + aTime);
}

bool Unit::TimedUnitExpire(Timer<Unit>& aTimer)
{
	LOG_DEBUG("Unit %d summon expired", mEntityId);
	if (mFsm)
	{
		mDieCause.cause = EUnitDieCause::Timeout;
		mFsm->DoTransition(mTransDead);
		//ClearView();
	}
    return false;
}

void Unit::Die(const DieCause& aDieCause)
{
	if (IsDead())
		return;
	if (aDieCause.cause != EUnitDieCause::Invalid)
	{
		mDieCause = aDieCause;
	}
	mTTL = GetBattleInstance().GetGameTime();
    mFsm->DoTransition(mTransDead);
}

void Unit::SetDie()
{
	mFsm->SetState(mStateDead);
}

void Unit::EnableMoveBySkill(const IFunctionContainer<void, SharedPtr<Unit> >* aWhenCancel, ControlToken* aState, const Unit* aUtilizer, bool const aValidRefTarget, bool const aValidEffTarget)
{
	if (mOnMoveBySkillCancel)
	{
		mOnMoveBySkillCancel->operator()(SharedFromThis());
		TryRecycleFunction(mOnMoveBySkillCancel);
	}
		
	mOnMoveBySkillCancel = aWhenCancel;
	mFloatWithoutBeingMoved = false;

	//move is handled by the SkillExecutor
	if (!aValidRefTarget)
		IncStateAdjust(StateAdjust::NonRefTarget);
	if (!aValidEffTarget)
		IncStateAdjust(StateAdjust::NonEffTarget);

	//自己位移自己的时候，不进入被控制状态    
	if (aUtilizer != this)
	{
		if (aState)
		{
			BeControlled(*aState);
		}
		SkillInterrupted(mCurSkillExecutor);
	}
}


//TODO: DELETE IT
//void Unit::EnableMoveBySkill(SharedPtr<IFunctionContainer<void, SharedPtr<Unit> > > aWhenCancel, const Unit* aUtilizer, bool const aValidRefTarget, bool const aValidEffTarget)
//{
//	EnableMoveBySkill(aWhenCancel, *mControlTokenIdle, aUtilizer, aValidRefTarget, aValidEffTarget);
//}

void Unit::DisableMoveBySkill(bool aClearControl, SharedPtr<Unit> aUtilizer, ControlToken* aState, bool const aValidRefTarget, bool const aValidEffTarget)
{
	if (mOnMoveBySkillCancel)
	{
		TryRecycleFunction(mOnMoveBySkillCancel);
		mOnMoveBySkillCancel = nullptr;
	}
	else
	{
		LOG_DEBUG("Entity %d DisableMoveBySkill but not found mOnMoveBySkillCancel", mEntityId);
	}
	if (!aValidRefTarget)
		DecStateAdjust(StateAdjust::NonRefTarget);
	if (!aValidEffTarget)
		DecStateAdjust(StateAdjust::NonEffTarget);

	if (aUtilizer.Get() != this && aClearControl)
	{
		if (aState)
		{
			ClearBeControlled(*aState);
		}
	}
	if (mPosition.y > 0)
	{
		mFloatWithoutBeingMoved = true;
	}
}

//TODO: DELETE IT
//void Unit::DisableMoveBySkill(bool aClearControl, SharedPtr<Unit> aUtilizer, bool const aValidRefTarget, bool const aValidEffTarget)
//{
//	DisableMoveBySkill(aClearControl, aUtilizer, *mControlTokenIdle, aValidRefTarget, aValidEffTarget);
//}

SharedPtr<Unit> Unit::GetLastNormalSkillTarget() const
{
	return mLastNormalTarget;
}

void Unit::SetLastNormalSkillTarget(SharedPtr<Unit> aRefTarget)
{
	mLastNormalTarget = aRefTarget;
}
void Unit::SetLastRefTarget(SharedPtr<Unit> aRefTarget, int64 aCastRange)
{
	mLastRefTarget = aRefTarget;
	mLastCastRange = aCastRange;
}

bool Unit::HasBuff(int const aBuffId) const
{
	return mBuffMgr->HasBuff(aBuffId);
}

WeakPtr<Buff> Unit::GetBuff(int aBuffId) 
{
	return mBuffMgr->GetBuff(aBuffId);
}

int64 Unit::GetBuffRecordData(int aBuffId)
{
	if (!mBuffMgr->HasBuff(aBuffId))
		return 0;
	return mBuffMgr->GetBuff(aBuffId)->GetRecordData();
}

bool Unit::RemoveByBuffType(const vector<BuffType>& aTypeArr, int const aPartialCount, int aByBuffId, bool aShouldTrigger, int aCleanLv)
{
    return mBuffMgr->RemoveByBuffType(aTypeArr, aPartialCount, aByBuffId, aShouldTrigger, aCleanLv);
}

bool Unit::RemoveByBuffSubType(const vector<BuffSubType>& aSubTypeArr, int const aPartialCount, int aByBuffId, bool aShouldTrigger, int aCleanLv)
{
    return mBuffMgr->RemoveByBuffSubType(aSubTypeArr, aPartialCount, aByBuffId, aShouldTrigger, aCleanLv);
}

bool Unit::RemoveBuff(int const aBuffId, int const aPartialCount)
{
    return mBuffMgr->RemoveBuff(aBuffId, aPartialCount, false);
}

bool Unit::RemoveBuffAndTrigger(int const aBuffId, int const aPartialCount)
{
	return mBuffMgr->RemoveBuff(aBuffId, aPartialCount, true);
}

bool Unit::RemoveBuff(const vector<int>& aBuffArr, int const aPartialCount, int aByBuffId, bool aShouldTrigger)
{
	return mBuffMgr->RemoveBuff(aBuffArr, aPartialCount, aByBuffId, aShouldTrigger);
}

int Unit::CountBuffLayerByMainType(BuffType aType) const
{
	return mBuffMgr->CountBuffLayerByMainType(aType);
}
int Unit::CountBuffLayerBySubType(BuffSubType aType) const
{
	return mBuffMgr->CountBuffLayerBySubType(aType);
}
int Unit::CountBuffLayerByBuffIdOR(const vector<int>& aIds) const
{
	return mBuffMgr->CountBuffLayerByBuffIdOR(aIds);
}
int Unit::CountBuffLayerByBuffIdAND(const vector<int>& aIds) const
{
	return mBuffMgr->CountBuffLayerByBuffIdAND(aIds);
}

bool Unit::IsInMove2RefST() const
{
	return mFsm->IsInState(mStateMoveToRef->GetId());
}

bool Unit::HasRefTarget(int aEntityId)
{
	if (mChoosedSkill && mFsm->IsInState(mStateMoveToRef->GetId()))
	{
		const RefTarget& nearestRefTarget = mChoosedSkill->GetNearestRefTarget();
		if (nearestRefTarget.GetEntityId() == aEntityId)
		{
			return true;
		}
	}
	return false;
}

int64 Unit::TryGetCastRange()
{
	int64 castRage = 0;
	if (mChoosedSkill)
	{
		castRage = mChoosedSkill->GetCastRange();
	}
	return castRage;
}

int Unit::TryGetCurrentRefTarget() 
{
	if (mChoosedSkill && mFsm->IsInState(mStateMoveToRef->GetId()))
	{
		return mChoosedSkill->GetNearestRefTarget().GetEntityId();
	}
	return 0;
}

//void Unit::TickMeleeRingMgr(const vector<Unit*>& aAllActiveUnits)  //TODO: Delete it
//{
//	if (mMeleeRingMgr)
//	{
//		mMeleeRingMgr->OnTick(aAllActiveUnits);
//	}
//}

int Unit::TauntedTargetBuffId() const
{
    return mTauntedTargetBuffId;
}

void Unit::TauntedTarget(int const aBuffId)
{
    mTauntedTargetBuffId = aBuffId;
}

void Unit::ClearTauntedTarget()
{
    mTauntedTargetBuffId = 0;
}

void Unit::SetSpecifyBeTargetSkills(const vector<int>& aHtids)
{
	for (int htid : aHtids)
	{
		const auto& iter = mSpecifyBeTargetSkillMap.find(htid);
		if (iter == mSpecifyBeTargetSkillMap.end())
		{
			mSpecifyBeTargetSkillMap.insert( {htid, 1} );
		}
		else
		{
			iter->second += 1;
		}
	}

}
void Unit::ResetSpecifyBeTargetSkills(const vector<int>& aHtids)
{
	for (int htid : aHtids)
	{
		const auto& iter = mSpecifyBeTargetSkillMap.find(htid);
		if (iter == mSpecifyBeTargetSkillMap.end())
		{
			LOG_FATAL("not found htid:%d in mSpecifyBeTargetSkillMap", htid);
			return;
		}
		else
		{
			if (iter->second <= 0)
			{
				LOG_FATAL("invalid mSpecifyBeTargetSkillMap htid:%d  num:%d", htid, iter->second);
				return;
			}
			iter->second -= 1;
			if (iter->second <= 0)
			{
				mSpecifyBeTargetSkillMap.erase(iter);
			}
		}
	}
}

void Unit::BeControlled(ControlToken& aState)
{
    SkillInterrupted(mCurSkillExecutor);
	DisableMove();
	mBuffMgr->FilterBuffByBeControlledMark();
	if (IsDead() || IsDying())
	{
		//the guy has been killed right after FilterBuffByBeControlledMark
		return;
	}
    aState.mStartTime = mUnitTime;
    aState.mIsValid = true;
	ControlToken *origLast = nullptr;
	if (mBeControlledStack.size() > 0)
	{
		origLast = mBeControlledStack.back();
	}
    mBeControlledStack.emplace_back(&aState);
	selectionSort(mBeControlledStack, CompareByAnimPriority);
    if(!mFsm->IsInState(mStateBeControlled->GetId()))
        mFsm->DoTransition(mTransBeControlled);
	if (origLast != mBeControlledStack.back())   //do view cmd only when latest state changes
	{
		SetAnim(mBeControlledStack.back()->mName);
		mView->Execute(ViewCommand::ControlledStateChange, mEntityId, aState.mType, mCurrentAnimName);
	}
	else if (origLast && aState.mReplayable && strncmp(origLast->mName, aState.mName, 3) == 0)
	{
		//special for ctrl state "Knock" and "Hit" 
		SetAnim(aState.mName);
		mView->Execute(ViewCommand::ControlledStateChange, mEntityId, aState.mType, mCurrentAnimName);
	}

    mControlled = 1;
    LOG_DEBUG("Unit %d be controlled {type=%d,anim=%s}"
        , mEntityId
        , aState.mType
        , mCurrentAnimName
    );
}

void Unit::ClearBeControlled(ControlToken& aState)
{
	aState.mIsValid = false;
    if (mBeControlledStack.size() <= 0)
    {
		//when a buffmod A call beControlled() but before emplace state to BeControlledStack, 
		//the trigger bufmod A ends(due to die or so on) and call this method
		//will has chance to hit into this branch
		return;
    }
	ControlToken *origLast = nullptr;
	if (mBeControlledStack.size() > 0)
	{
		origLast = mBeControlledStack.back();
	}
	LOG_DEBUG("Unit %d ClearBeControlled, origLast=%s, size=%d", mEntityId, origLast->mName, mBeControlledStack.size());
	unsigned int idx = 0, p = 0;
	for (; idx < mBeControlledStack.size(); idx++)
	{
		if (mBeControlledStack[idx]->mIsValid)
		{
			if (idx != p) mBeControlledStack[p] = mBeControlledStack[idx];
			p++;
		}
	}
	mBeControlledStack.resize(p);

    if (IsDead() || IsDying())
    {
		LOG_DEBUG("clear be control when dead, eid = %d", mEntityId);
        return;
    }
    
    if (mBeControlledStack.size() == 0)
    {
		SetAnim(ANIM_NAME_IDLE);
        mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::None, mCurrentAnimName);
        mFsm->DoTransition(mTransBeControlledEnd);
        mControlled = 0;
        LOG_DEBUG("Unit %d be controlled all cleared {clear:type=%d,anim=%s final:anim=%s}"
            , mEntityId
            , aState.mType
            , aState.mName
            , mCurrentAnimName
        );
    }
    else if (origLast != mBeControlledStack.back())   //send notification only when current state has been changed 
    {
        ControlToken* state = mBeControlledStack.back();
		if (strncmp(state->mName, ANIM_NAME_KNOCK, 5) == 0)
		{
			LOG_DEBUG("clear be control has knock, eid = %d", mEntityId);
			return;  //ignore knock, otherwise frontend will play anim_knock 
		}
		SetAnim(state->mName);
        mView->Execute(ViewCommand::ControlledStateChange, mEntityId, state->mType, mCurrentAnimName); 
        LOG_DEBUG("Unit %d be controlled clear {clear:type=%d,anim=%s to:type=%d,anim=%s final:anim=%s}" 
            , mEntityId
            , aState.mType
            , aState.mName
            , state->mType
            , state->mName
            , mCurrentAnimName
        );
    }
	else
	{
		LOG_DEBUG("clear be control, origLast == stack.back, eid = %d, size = %d, name = %s", mEntityId, mBeControlledStack.size(), origLast->mName);
	}
}


const vector<SharedPtr<Skill> >& Unit::GetSkillArr() const
{
	return mSkillArr;
}

void Unit::SkillImmunityByType(const vector<ESkillSubType>& aTypeArr)
{
	for (auto t : aTypeArr)
	{
		mImmueSkillTypeArr[static_cast<int>(t)]++;
	}    
}

void Unit::SkillImmunity(int const aSkillId)
{
	for (auto& p : mImmueSkillArr)
	{
		if (aSkillId == p.first)
		{
			p.second += 1;
			return;
		}
	}
	mImmueSkillArr.emplace_back(pair<int, int>(aSkillId, 1));
}

void Unit::SkillImmunity(const vector<int>& aSkillIdArr)
{
    for (auto& id : aSkillIdArr)
    {
		SkillImmunity(id);
    }
}

void Unit::RevokeSkillImmunityByType(const vector<ESkillSubType>& aTypeArr)
{    
	for (auto t : aTypeArr)
	{
		mImmueSkillTypeArr[static_cast<int>(t)]--;
	}
}

void Unit::RevokeSkillImmunity(int const aSkillId)
{
	int len = mImmueSkillArr.size();
	for (int i = 0; i < len; i++)
	{
		auto& p = mImmueSkillArr[i];
		if (aSkillId == p.first)
		{
			p.second -= 1;
			if (p.second == 0)
			{
				mImmueSkillArr[i] = mImmueSkillArr[len - 1];
				mImmueSkillArr.resize(len - 1);
			}
			return;
		}
	}
	LOG_DEBUG("RevokeSkillImmunity fail, not found skillId %d in ImmueSkillArr", aSkillId);
}

void Unit::RevokeSkillImmunity(const vector<int>& aSkillIdArr)
{
    for (auto& id : aSkillIdArr)
    {
		RevokeSkillImmunity(id);
    }
}

void Unit::BuffImmunityByType(const vector<BuffType>& aTypeArr)
{
	for (auto t : aTypeArr)
	{
		mImmueBuffTypeArr[static_cast<int>(t)]++;
	}    
}

void Unit::BuffImmunityBySubType(const vector<BuffSubType>& aSubTypeArr)
{
	for (auto t : aSubTypeArr)
	{
		mImmueBuffSubTypeArr[static_cast<int>(t)]++;
	}    
}

void Unit::BuffImmunity(int const aBuffId)
{
	for (auto& p : mImmueBuffArr)
	{
		if (aBuffId == p.first)
		{
			p.second += 1;
			return;
		}
	}
	mImmueBuffArr.emplace_back(pair<int, int>(aBuffId, 1));
}

void Unit::BuffImmunity(const vector<int>& aBuffIdArr)
{
    for (auto& id : aBuffIdArr)
    {
		BuffImmunity(id);
    }
}

void Unit::RevokeBuffImmunityByType(const vector<BuffType>& aTypeArr)
{
	for (auto& t : aTypeArr)
	{
		mImmueBuffTypeArr[static_cast<int>(t)]--;
	}    
}

void Unit::RevokeBuffImmunityBySubType(const vector<BuffSubType>& aSubTypeArr)
{
	for (auto& t : aSubTypeArr)
	{
		mImmueBuffSubTypeArr[static_cast<int>(t)]--;
	}    
}

void Unit::RevokeBuffImmunity(int const aBuffId)
{
	int len = mImmueBuffArr.size();
	for (int i = 0; i < len; i++)
	{
		auto& p = mImmueBuffArr[i];
		if (aBuffId == p.first)
		{
			p.second -= 1;
			if (p.second == 0)
			{
				mImmueBuffArr[i] = mImmueBuffArr[len - 1];
				mImmueBuffArr.resize(len - 1);
			}
			return;
		}
	}
	LOG_DEBUG("RevokeBuffImmunity fail, not found buffId %d in mImmueBuffArr", aBuffId);
}

void Unit::RevokeBuffImmunity(const vector<int>& aBuffIdArr)
{
    for (auto& id : aBuffIdArr)
    {
		RevokeBuffImmunity(id);
    }
}

void Unit::PropertyChangeImmunity(EAttribute aAttr)
{
	mImmuePropertyArr[static_cast<int>(aAttr)]++;
}

void Unit::RevokePropertyChangeImmunity(EAttribute aAttr)
{
	mImmuePropertyArr[static_cast<int>(aAttr)]--;
}

bool Unit::hasBuffModifyDamage() const
{
	return mTableChgDataByBuffSub.size() > 0;
}

void Unit::ModifyAttr(const vector<BuffModPropertyEntry>& aEntryArr, bool aNeedSendText, int aBuffId)
{
	bool IsPhysicalUp = false;
	bool IsMagicalUp = false;
	bool IsPhysicalDown = false;
	bool IsMagicalDown = false;
	bool IsPhysicalDamageIncreaseUp = false;
	bool IsPhysicalDamageIncreaseDown = false;
	bool IsPhysicalDamageAvoidUp = false;
	bool IsPhysicalDamageAvoidDown = false;
	bool IsMagicalDamageIncreaseUp = false;
	bool IsMagicalDamageIncreaseDown = false;
	bool IsMagicalDamageAvoidUp = false;
	bool IsMagicalDamageAvoidDown = false;
	//NOTE: mShapeshiftMod->mLastAttrArr in some cases will replace mAttrArr
	//which will lead to inconsistency problem
    for (auto& entry : aEntryArr)
    {
		if (entry.mValue == 0) continue;

        mAttrArr[static_cast<int>(entry.mProperty)] += entry.mValue;
		if (IsInvalidAttr(entry.mProperty))
		{
			LOG_DEBUG("Invalid Attr Modification: Attr = %d, Value = %d, BuffId = %d", entry.mProperty, entry.mValue, aBuffId);
			int64 upLimit = BattleInstance::ATTR_LIMITS_UP[static_cast<int>(entry.mProperty)];
			int64 downLimit = BattleInstance::ATTR_LIMITS[static_cast<int>(entry.mProperty)];
			int64 tmp = mAttrArr[static_cast<int>(entry.mProperty)];
			if (tmp < downLimit) mAttrArr[static_cast<int>(entry.mProperty)] = downLimit;
			else if (upLimit > 0 && tmp > upLimit) mAttrArr[static_cast<int>(entry.mProperty)] = upLimit;
		}

		if (entry.mProperty == EAttribute::PhysicalDefBase || 
			entry.mProperty == EAttribute::PhysicalDefPercent || 
			entry.mProperty == EAttribute::PhysicalDefExtra) 
		{
			if (entry.mValue > 0)
			{
				IsPhysicalUp = true;
			}
			else if (entry.mValue < 0)
			{
				IsPhysicalDown = true;
			}
		}
		else if (entry.mProperty == EAttribute::MagicDefBase ||
			entry.mProperty == EAttribute::MagicDefPercent ||
			entry.mProperty == EAttribute::MagicDefExtra)
		{
			if (entry.mValue > 0)
			{
				IsMagicalUp = true;
			}
			else if (entry.mValue < 0)
			{
				IsMagicalDown = true;
			}
		}
		else if (entry.mProperty == EAttribute::PhysicalPercentAdd)
		{
			if (entry.mValue > 0)
			{
				IsPhysicalDamageIncreaseUp = true;
			}
			else if (entry.mValue < 0)
			{
				IsPhysicalDamageIncreaseDown = true;
			}
		}
		else if (entry.mProperty == EAttribute::PhysicalPercentSub)
		{
			if (entry.mValue > 0)
			{
				IsPhysicalDamageAvoidUp = true;
			}
			else if (entry.mValue < 0)
			{
				IsPhysicalDamageAvoidDown = true;
			}
		}
		else if (entry.mProperty == EAttribute::MagicPercentAdd)
		{
			if (entry.mValue > 0)
			{
				IsMagicalDamageIncreaseUp = true;
			}
			else if (entry.mValue < 0)
			{
				IsMagicalDamageIncreaseDown = true;
			}
		}
		else if (entry.mProperty == EAttribute::MagicPercentSub)
		{
			if (entry.mValue > 0)
			{
				IsMagicalDamageAvoidUp = true;
			}
			else if (entry.mValue < 0)
			{
				IsMagicalDamageAvoidDown = true;
			}
		}

    }
	if (aNeedSendText)
	{
		if (IsPhysicalUp)
		{
			SendScreenTextCmd(ScreenTextType::DefenseUpPhysical); 
		}
		if (IsPhysicalDown)
		{
			SendScreenTextCmd(ScreenTextType::DefenseDownPhysical); 
		}
		if (IsMagicalUp)
		{
			SendScreenTextCmd(ScreenTextType::DefenseUpMagical); 
		}
		if (IsMagicalDown)
		{
			SendScreenTextCmd(ScreenTextType::DefenseDownMagical); 
		}
		if (IsPhysicalDamageIncreaseUp)
		{
			SendScreenTextCmd(ScreenTextType::PhysicalDamageIncreaseUp);
		}
		if (IsPhysicalDamageIncreaseDown)
		{
			SendScreenTextCmd(ScreenTextType::PhysicalDamageIncreaseDown);
		}
		if (IsPhysicalDamageAvoidUp)
		{
			SendScreenTextCmd(ScreenTextType::PhysicalDamageAvoidUp);
		}
		if (IsPhysicalDamageAvoidDown)
		{
			SendScreenTextCmd(ScreenTextType::PhysicalDamageAvoidDown);
		}
		if (IsMagicalDamageIncreaseUp)
		{
			SendScreenTextCmd(ScreenTextType::MagicalDamageIncreaseUp);
		}
		if (IsMagicalDamageIncreaseDown)
		{
			SendScreenTextCmd(ScreenTextType::MagicalDamageIncreaseDown);
		}
		if (IsMagicalDamageAvoidUp)
		{
			SendScreenTextCmd(ScreenTextType::MagicalDamageAvoidUp);
		}
		if (IsMagicalDamageAvoidDown)
		{
			SendScreenTextCmd(ScreenTextType::MagicalDamageAvoidDown);
		}
	}
}

void Unit::RevertAttr(const vector<BuffModPropertyEntry>& aEntryArr)
{
	//NOTE: mShapeshiftMod->mLastAttrArr in some cases will replace mAttrArr
	//which will lead to inconsistency problem 
    for (auto& entry : aEntryArr)
    {
        mAttrArr[static_cast<int>(entry.mProperty)] -= entry.mValue;
    }
}

int64 Unit::ModifyMaxHp(int64 const aMaxHpChange, int64 const aHpChange, int64 const aHpDiff, bool aNeedSendCmd)
{
	if (aMaxHpChange == 0 && aHpChange == 0 && aHpDiff == 0)
	{
		return 0;
	}
	//RPG
	int64 ret = 0;
	mMaxHp += aMaxHpChange;//changed by buff
	if (mHp > mMaxHp)//record overflowed hp diff
	{
		ret = mHp - mMaxHp;
	}
	mHp += aHpChange;//changed by buff
	mHp += aHpDiff;//hp diff compensation
	if (mHp > mMaxHp)
		mHp = mMaxHp;

	if (mHp < 0)
		mHp = 1;

	if (aNeedSendCmd)
		SendMaxHpChangeCmd();
	//mView->Execute(ViewCommand::MaxHpChange, mEntityId, mHp, mMaxHp);
	return ret;
}

//unit is born if fsm is initialized
bool Unit::NeedFieldInit() const
{
	if (IsHidden()) return false;  //skip behaviour hidden and removed Units
	if (mArmy->GetId() == 2 && IsDead()) return false;  //skip enemy Dead Units
	//all self included
	return true;
}
bool Unit::IsBorn() const
{//fsm is initialized if the states are instantiated
    return (bool)mStateIdle;
}
bool Unit::IsDead() const
{
    //return !mFsm || mFsm->IsInState(mStateDead->mId) || IsHidden();
    return !mFsm || mFsm->mCurStateId == mDeadStateId || CheckStateAdjust(StateAdjust::BehaviourHidden);
}
bool Unit::IsDying() const
{
	return !mFsm || mFsm->IsInState(mStateDying->GetId());
}
bool Unit::IsEmptyHp() const
{
	return mHp <= 0;
}
bool Unit::IsHidden() const
{
    return CheckStateAdjust(StateAdjust::BehaviourHidden);
}
bool Unit::IsSummoned() const
{
	if (mSummoner) return true;
	return false;
}
int Unit::GetAncestor() const
{
	int eid = 0;
	Unit* holder = mSummoner;
	while (holder)
	{
		eid = holder->GetEntityId();
		holder = holder->mSummoner;
	}
	return eid;
}
bool Unit::IsDummy() const
{
	return mIsDummy;
}
bool Unit::IsRefDummy() const
{
	if (mIsDummy && mTplId == -1)
	{
		return true;
	}
	return false;
}
bool Unit::IsClearOnCutscene() const
{
    return mClearOnCutscene;
}
bool Unit::IsEnemy(const SharedPtr<Unit>& aUnit) const
{
    //(normal condition) is not (inverted)
    return (aUnit->mArmy != mArmy) != (CheckStateAdjust(StateAdjust::Charmed));
}
bool Unit::IsEnemy(const int aArmyId) const
{
	return (aArmyId != mArmy->GetId()) != (CheckStateAdjust(StateAdjust::Charmed));
}
bool Unit::IsHero(const int aEntityId) const
{
	const auto& unit = GetBattleInstance().GetUnitByEntityId(aEntityId, true);
	if (unit)
		return !unit->IsSummoned() && !unit->IsDummy();
	return false;
}
bool Unit::IsSlg() const
{
	return false;
}
bool Unit::IsTowerLike() const
{
	return mSpeed <= 0;
}

const char* Unit::GetCurrentAnimName() const
{
    return mCurrentAnimName;
}

bool Unit::HasCurrentAnimName() const
{
	if (!mCurrentAnimName || strlen(mCurrentAnimName) == 0)
		return false;
	return true;
}

const char * Unit::GetDeathAnimName(string aName) const
{
	if (strcmp(aName.c_str(), ANIM_NAME_DEAD) == 0 )
		return ANIM_NAME_DEAD;
	else if (strcmp(aName.c_str(), ANIM_NAME_DEAD_2) == 0)
		return ANIM_NAME_DEAD_2;
	else if (strcmp(aName.c_str(), ANIM_NAME_DEAD_3) == 0)
		return ANIM_NAME_DEAD_3;
	else if (strcmp(aName.c_str(), ANIM_NAME_DEAD_4) == 0)
		return ANIM_NAME_DEAD_4;
	else
	{
		if (mPosition.y > 0)
			return ANIM_NAME_DEAD_3;
		else
			return ANIM_NAME_DEAD;
	}
}

int64 Unit::GetCurrentAnimStartTime() const
{
	return mCurrentAnimStartTime;
}

int64 Unit::GetCurrentAnimTotalTime() const
{
	return mCurrentAnimLength;
}

int Unit::GetNormalAtkNum() const
{
    return mNormalAtkNum;
}
bool Unit::IsInvalidAttr(EAttribute aAttr) const
{
	int64 ret = mAttrArr[static_cast<int>(aAttr)];
	int64 upLimit = BattleInstance::ATTR_LIMITS_UP[static_cast<int>(aAttr)];
	int64 downLimit = BattleInstance::ATTR_LIMITS[static_cast<int>(aAttr)];
	if (ret < downLimit || (upLimit > 0 && ret > upLimit))
		return true;
	return false;
}
int64 Unit::GetAttr(EAttribute const aAttr) const
{
	int64 ret = mAttrArr[static_cast<int>(aAttr)];
	if (IsInvalidAttr(aAttr))
	{
		//LOG_DEBUG("Get Invalid Attr %d, at hero %d, with value %d", static_cast<int>(aAttr), mTplId, ret);
		return 0;
	}
    return ret;
}
void Unit::DirectAddAttr(EAttribute aAttr, int64 aValue)
{
	mAttrArr[static_cast<int>(aAttr)] += aValue;
}
int Unit::GetHeroId() const
{
	return mHid;
}
int Unit::GetTplId() const
{
	if (!mShapeShiftStack.empty())
		return mShapeShiftStack[0]->mLastTplId;
	return mTplId;
}
int Unit::GetCurTplId() const
{
	return mTplId;
}
int Unit::GetKnockTimeLength() const
{
	return mKnockTimeLength;
}
int64 Unit::GetPhysicalAtk() const
{
    auto atk = GetAttr(EAttribute::PhysicalAtkBase)
        * (DENOM + GetAttr(EAttribute::PhysicalAtkPercent)) / DENOM
        + GetAttr(EAttribute::PhysicalAtkExtra);
	return atk;
}
int64 Unit::GetMagicAtk() const
{
    int64 atk = GetAttr(EAttribute::MagicAtkBase)
        * (DENOM + GetAttr(EAttribute::MagicAtkPercent)) / DENOM
        + GetAttr(EAttribute::MagicAtkExtra);
	return atk;
}
int64 Unit::GetPhysicalDef() const
{
    int64 def = GetAttr(EAttribute::PhysicalDefBase)
        * (DENOM + GetAttr(EAttribute::PhysicalDefPercent)) / DENOM
        + GetAttr(EAttribute::PhysicalDefExtra);
	return def;
}
int64 Unit::GetMagicDef() const
{
	int64 def = GetAttr(EAttribute::MagicDefBase)
        * (DENOM + GetAttr(EAttribute::MagicDefPercent)) / DENOM
        + GetAttr(EAttribute::MagicDefExtra);
	return def;
}

int64 Unit::GetFinalDamage() const
{
	int64 dmg = GetAttr(EAttribute::FinalDamage);
	return dmg;
}

int64 Unit::GetFinalAvoid() const
{
	int64 avd = GetAttr(EAttribute::FinalAvoidInjury);
	return avd;
}

int Unit::GetSpeedFactor() const
{
	return mRealSpeedFactor;
}

int Unit::GetCurTroopNum() const
{
	return mCurTroopNum;
}

int Unit::GetDeadSoldierNum() const
{
	return mDeadNum;
}

int Unit::GetInjuredNum() const
{
	return mInjuredNum;
}
int Unit::GetKillNum() const
{
	return mKillNum;
}

void Unit::IncKillNum(int aNum)
{
	mKillNum += aNum;
}

int Unit::GetBornPoint() const
{
    return mBornPoint;
}

int Unit::GetSpotGroupId() const
{
	auto& bp = mArmy->GetBornPointByIndex(mBornPoint);
	return bp.mGroupId;
}

BoundingVolume* Unit::GetBV() const
{
    return mBV;
}

TimerMgr* Unit::GetTimerMgr() const
{
    return mTimerMgr.Get();
}
BattleInstance& Unit::GetBattleInstance() const
{
    return mArmy->GetBattleInstance();
}
Army& Unit::GetArmy() const
{
    return *mArmy;
}
const TUnitInfo* Unit::GetUnitInfo() const
{
    return mInfo;
}
string& Unit::GetAvatarName() const
{
    return *mAvatarName;
}
Agent* Unit::GetAgent() const
{
    return mAgent;
}
Cylinder& Unit::GetBVDerived() const
{
    return *mBV;
}
int Unit::GetUnitTime() const
{
    return mUnitTime;
}
int64 Unit::GetHp() const
{
	if (mHp < 0)
	{
		LOG_INFO("Entity %d mHp < 0", mEntityId);
		return 0;
	}
    return mHp;
}
int64 Unit::GetLostHp() const
{
    return mMaxHp - mHp;
}
int64 Unit::GetMaxHp() const
{
	if (mMaxHp < 0)
	{
		LOG_WARN("Entity %d mMaxHp < 0", mEntityId);
		return 0;
	}
    return mMaxHp;
}
int64 Unit::GetRage() const
{
	if (mRage < 0)
	{
		LOG_WARN("Entity %d mRage < 0", mEntityId);
		return 0;
	}
    return mRage;
}
int64 Unit::GetMaxRage() const
{
    return mMaxRage;
}
int64 Unit::GetShieldByType(ShieldType aType) const
{
	switch (aType)
	{
	case ShieldType::Physical:
		return mPhyicalShield;
	case ShieldType::Magical:
		return mMagicalShield;
	case ShieldType::Universal:
		return mUniversalShield;
	default:
		LOG_WARN("unknow shield type: %d", static_cast<int>(aType));
	}
	return 0;
}
int Unit::GetProfession() const
{
	auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(mTplId);
	return heroConf->GetProfession()[0];
}
void Unit::AddShieldByType(ShieldType aType, int64 aValue)
{
	switch (aType)
	{
	case ShieldType::Physical:
		mPhyicalShield += aValue;
		break;
	case ShieldType::Magical:
		mMagicalShield += aValue;
		break;
	case ShieldType::Universal:
		mUniversalShield += aValue;
		break;
	case ShieldType::UniversalCount:
		mUniversalShield += aValue;
		break;
	default:
		LOG_WARN("unknow shield type: %d", static_cast<int>(aType));
	}
	if (aValue != 0)
		SendMaxHpChangeCmd();
}
void Unit::SubShieldByType(ShieldType aType, int64 aValue, int aSkillId, int aUtilizerId)
{
	switch (aType)
	{
	case ShieldType::Physical:
		mPhyicalShield -= aValue;
		break;
	case ShieldType::Magical:
		mMagicalShield -= aValue;
		break;
	case ShieldType::Universal:
		mUniversalShield -= aValue;
		break;
	default:
		LOG_WARN("unknow shield type: %d", static_cast<int>(aType));
	}
	if (aValue != 0)
		SendMaxHpChangeCmd(aSkillId, aUtilizerId);
	return;
}
int Unit::GetLevel() const
{
    return mLevel;
}
int Unit::GetArmyId() const
{
	return mArmyId;
}
int Unit::GetAdvLevel() const
{
	return mAdvLevel;
}
int Unit::GetStar() const
{
	return mStar;
}
int64 Unit::GetDamageInTotal() const
{
	if (mDamageInTotal < 0)
	{
		LOG_WARN("Get Damage In Total < 0");
		return 0;
	}
    return mDamageInTotal;
}
int64 Unit::GetDamageInWithOverflow() const
{
	return mDamageInWithOverflow;
}
int64 Unit::GetDamageOutTotal() const
{
	if (mDamageOutTotal < 0)
	{
		LOG_WARN("Get Damage Out Total < 0");
		return 0;
	}
    return mDamageOutTotal;
}
int64 Unit::GetHealOutTotal() const
{
	if (mHealOutTotal < 0)
	{
		LOG_WARN("mHealOutTotal < 0");
		return 0;
	}
	return mHealOutTotal;
}
int Unit::GetOrigTplId()
{
	if (mShapeShiftStack.empty())
	{
		return mTplId;
	}
	return mShapeShiftStack[0]->mLastTplId;
}
void Unit::UpdateAgent()
{
    if (!mAgent)
        return;
    int64 size = GetSize();
    mBV->Update(&mPosition, &size);
}

void Unit::WriteViewInfo(ostream& aWriter, TArmyUnitInfo* pArmyUnitInfo) const
{
	//assert(pArmyUnitInfo != nullptr);
	if (pArmyUnitInfo == nullptr)
	{
		LOG_FATAL("pArmyUnitInfo is nil when WriteViewInfo");
		return;
	}
	pArmyUnitInfo->add_unitinfo(mEntityId);
	pArmyUnitInfo->add_unitinfo(mTplId);
	pArmyUnitInfo->add_unitinfo(mBornPoint);
	pArmyUnitInfo->add_unitinfo(mHp);
	pArmyUnitInfo->add_unitinfo(mRage);
	pArmyUnitInfo->add_unitinfo(mMaxHp);
	pArmyUnitInfo->add_unitinfo(mRageSkillThreshold);
	pArmyUnitInfo->add_unitinfo(mSpeed);
	pArmyUnitInfo->add_unitinfo(mBaseSizeScale);
	pArmyUnitInfo->add_unitinfo(mTroopId);
	pArmyUnitInfo->add_unitinfo(mHid);  //change from mTroopNum to mHid 
	for (auto& skill : mSkillArr)
	{
		pArmyUnitInfo->add_unitinfo(skill->GetId());
	}
}


void Unit::AddRageSkillUnpausedTarget(const SharedPtr<Unit>& aTarget)
{
	if (mRageSkillExecuteState == nullptr)
	{
		return;
	}	
	GetBattleInstance().UnpauseUnit(aTarget.Get(), false);

	bool exist = false;
	for (auto& target : mRageSkillExecuteState->mUnpausedTargetArr)
	{
		if (target == aTarget)
		{
			exist = true;
			break;
		}
	}
	if (!exist)
	{
		mRageSkillExecuteState->mUnpausedTargetArr.emplace_back(aTarget);
	}	
}

bool Unit::CallbackBehaviourExecuteSkill(Timer<Unit>&)
{
	if (mBehaviourSkill->HasAnim() && !CheckStateAdjust(StateAdjust::BehaviourStopped) && mFsm->IsInState(mStateIdle->GetId()) == false)
	{ //wait till idle state before executing Rage skill
		LOG_DEBUG("Entity:%d curState:%s cant executeSkill:%d", GetEntityId(), mFsm->GetCurrentState().GetName(), mBehaviourSkill->GetId());
		return true;
	}
	mBehaviourSkill->RefreshRefTarget();
    ExecuteSkill(mBehaviourSkill, 0, nullptr, nullptr);
    //mStateBehaviour->SetOnTick(nullptr);
    //mFsm->DoTransition(mTransBehaviour);
    return false;
}

bool Unit::ActionBehaviourMoveToStandPoint(int const aDeltaTime)
{
	bool ret = Move(mBehaviourRefTarget, SharedFromThis(), mBehaviourRange, aDeltaTime, ERefFaceTo::None, mBehaviourSpeed);
	//LOG_WARN("Unit %d Move to Target %s [%ld, %ld, %ld], [%ld, %ld, %ld], t = %d", GetEntityId(), mBehaviourMoveTarget->mName.c_str(), target.x, target.y, target.z, pos.x, pos.y, pos.z, ret);
    if (ret)
    {
        mView->Execute(ViewCommand::BehaviourStandPointReached, mEntityId);
		mBehaviourRefTarget.SetType(ERefTargetType::Invalid);
    }
    return ret;
}

bool Unit::ActionBehaviourStopped(int const aDeltaTime)
{
    return !CheckStateAdjust(StateAdjust::BehaviourStopped);
}

void Unit::BehaviourExecuteSkill(int const aSkillId, int const aDelay)
{
	if (aSkillId > 0)
	{
		mBehaviourSkill = SharedPool<Skill>::Get();
		mBehaviourSkill->Init(SharedFromThis(), aSkillId, 1);
		auto timer = SharedPool<Timer<Unit> >::Get();
		timer->Execute(mTimerMgr.Get(), this, &Unit::CallbackBehaviourExecuteSkill, aDelay);
	}
	else
	{
		//dispatch enter skill event
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::Enter));
		GetBattleInstance().DispatchEvent(key, GetArmyId(), mEntityId);
	}
}

void Unit::BehaviourMoveToStandPoint(Vector3 aStandPoint, int aSpeed, int aRange)
{
	SkillInterrupted(mCurSkillExecutor);
    mBehaviourMoveTarget = Vector3(aStandPoint.x, aStandPoint.y, aStandPoint.z);
    mStateBehaviour->SetOnTick(MakeFunction<>(*this, &Unit::ActionBehaviourMoveToStandPoint));
	aSpeed = CONF_VEL_CONVERT(aSpeed);
	if (aSpeed <= 0)
	{
		aSpeed = GetSpeed();
	}
	aRange = CONF_POS_CONVERT(aRange);
	if (aRange <= 0)
	{
		aRange = 0;
	}
	mBehaviourSpeed = aSpeed;
	mBehaviourRange = aRange;
	mBehaviourRefTarget.SetPos(mBehaviourMoveTarget);
    mFsm->DoTransition(mTransBehaviour);
	//auto tmp = aStandPoint.mPos;
	//LOG_WARN("Unit %d Move to Target %s [%ld, %ld, %ld]", GetEntityId(), aStandPoint.mName.c_str(), tmp.x, tmp.y, tmp.z);
}

void Unit::BehaviourHide(int const aHiding)
{
    mStateAdjustPropertyArr[static_cast<int>(StateAdjust::BehaviourHidden)] = aHiding;
    mArmy->UnitHiddenStatusChanged(this);
}

bool Unit::CallbackBehaviourStop(Timer<Unit>&)
{
	if (IsDead())
	{
		return false;
	}
	int stop = mStateAdjustPropertyArr[static_cast<int>(StateAdjust::BehaviourStopped)];
	if (stop <= 0)
	{
		return false;  //not in stop state, so do nothing and finish
	}
	if (mFsm->IsInState(mStateBehaviour->GetId()))
	{
		return false;  //already in behaviour state by other op, so quit here
	}
	if (stop == 1 && !mFsm->IsInState(mStateBeControlled->GetId()))
	{ 
		doBehaviourStop();
		return false;  //Done
	}
	if (stop > 1 )
	{
		if (mFsm->IsInState(mStateChooseSkill->GetId())
			|| mFsm->IsInState(mStateSkillRecovery->GetId()) )
		{
			doBehaviourStop();
			return false;  //Done
		}
	}
	return true;  //wait until current state is not BeControlled
}

void Unit::BehaviourStop(int const aStopped)
{
	//a dead unit should not be consided as a behaviourer
	if (IsDead())
	{
		return;
	}
    mStateAdjustPropertyArr[static_cast<int>(StateAdjust::BehaviourStopped)] = aStopped;
    if (aStopped > 1)
    {   //do not stop unless in chooseSkill or skillRecovery state 
		if (mFsm->IsInState(mStateChooseSkill->GetId()) 
			|| mFsm->IsInState(mStateSkillRecovery->GetId())
			|| aStopped == 2)
		{
			doBehaviourStop();
		}
		else
		{
			auto timer = SharedPool<Timer<Unit> >::Get();
			timer->Execute(mTimerMgr.Get(), this, &Unit::CallbackBehaviourStop);
		}
    }
	else if (aStopped > 0)
	{   //wait be-control state before stop, otherwise stop right now 
		if (!mFsm->IsInState(mStateBeControlled->GetId()))
		{
			doBehaviourStop();
		}
		else
		{
			auto timer = SharedPool<Timer<Unit> >::Get();
			timer->Execute(mTimerMgr.Get(), this, &Unit::CallbackBehaviourStop);
		}
	}
}
bool Unit::BehaviourAnim(const char* aAnim)
{
	if (!CheckStateAdjust(StateAdjust::BehaviourStopped))
	{
		LOG_WARN("BehaviourAnim only work at BehaviourStopped status");
		return false;
	}
	mBehaviourAnim = aAnim;
	SetAnim(mBehaviourAnim.c_str());
	//mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::None, mCurrentAnimName);
	return true;
}

void Unit::doBehaviourStop()
{
	SkillInterrupted(mCurSkillExecutor);
	mStateBehaviour->SetOnTick(MakeFunction<>(*this, &Unit::ActionBehaviourStopped));
	mFsm->DoTransition(mTransBehaviour);
	SetAnim(ANIM_NAME_IDLE);
	mRecoveryTime = mUnitTime; 
	//mView->Execute(ViewCommand::ControlledStateChange, mEntityId, ControlledType::None, mCurrentAnimName);
}

void Unit::BehaviourAddBuff(int const aBuffId, int const aBuffLv, int aBTDel)
{
	TryReceiveBuff(SharedFromThis(), SharedFromThis(), aBuffId, aBuffLv, WeakPtr<Skill>(), aBTDel);
}

void Unit::BehaviourRemoveBuff(int const aBuffId, int const aBuffLv)
{
	RemoveBuffAndTrigger(aBuffId, false);
}

void Unit::SetBehaviourMark(bool aFlag)
{
	mBehaviourMark = aFlag;
}

bool Unit::IsBehaviourUnit() const
{
	return mBehaviourMark;
}

const int64 Unit::GetIdleBodyHeight()
{
	return mSocketBody.y;
}

const Vector3& Unit::GetIdleBodyPosition() 
{
	if (mSocketBody == Vector3::ZERO)
	{
		mHitPosition.x = 0;
		mHitPosition.y = 0;
		mHitPosition.z = 0;
	}
	else
	{
		mHitPosition.x = mSocketBody.x;
		mHitPosition.y = mSocketBody.y;
		mHitPosition.z = mSocketBody.z;
	}
	LocalToWorld(mHitPosition);
	return mHitPosition;
}

void Unit::DontSetToBornPosWhenCutscene()
{
	mDontInitToBornPos = true;
}
bool Unit::SetToBornPos()
{
	return !mDontInitToBornPos;
}

void Unit::SendScreenTextCmd(ScreenTextType aType, int64 aExtraData)
{
	mView->Execute(ViewCommand::ScreenText, mEntityId, static_cast<int>(aType), aExtraData);
}

void Unit::SendMaxHpChangeCmd(int aSkillId, int aUtilizerId)
{
	mView->Execute(ViewCommand::MaxHpChange, mEntityId, mHp, mMaxHp, mPhyicalShield, mMagicalShield, mUniversalShield, aSkillId, aUtilizerId);
}

void Unit::SetAnim(const char* aAnim)
{
	mCurrentAnimName = aAnim;
	mCurrentAnimStartTime = mUnitTime;
}

void Unit::SetAnimLenth(int aLength)
{
	mCurrentAnimLength = aLength;
}


void Unit::InvokeBuffModifyDamage(ChangeDataByBuffSub& aData)
{
	for (auto* data : mTableChgDataByBuffSub)
	{
		if (data->mType == aData.mType && data->mAttr == aData.mAttr)
		{
			data->mValue += aData.mValue;
			return;
		}
	}
	ChangeDataByBuffSub* tmp = new ChangeDataByBuffSub;
	tmp->mType = aData.mType;
	tmp->mAttr = aData.mAttr;
	tmp->mValue = aData.mValue;
	mTableChgDataByBuffSub.emplace_back(tmp);
}

void Unit::RevokeBuffModifyDamage(ChangeDataByBuffSub& aData)
{
	int size = mTableChgDataByBuffSub.size();
	for (int i = 0; i < size; i++)
	{
		if (mTableChgDataByBuffSub[i]->mType == aData.mType && mTableChgDataByBuffSub[i]->mAttr == aData.mAttr)
		{
			mTableChgDataByBuffSub[i]->mValue -= aData.mValue;
			if (mTableChgDataByBuffSub[i]->mValue == 0)
			{
				delete mTableChgDataByBuffSub[i];
				mTableChgDataByBuffSub[i] = mTableChgDataByBuffSub[size - 1];
				mTableChgDataByBuffSub.pop_back();
			}
			return;
		}
	}
}

void Unit::ClearChgDataByBuffSubArr()
{
	if (mTableChgDataByBuffSub.empty())
		return;
	for (int i = 0; i < mTableChgDataByBuffSub.size(); ++i)
		delete mTableChgDataByBuffSub[i];
	mTableChgDataByBuffSub.clear();
}

int Unit::BuildConditionChangeKey(int aMainType, int aRel, int aTar, int64 aParam, const vector<int>& aParamArr)
{
	int key = aMainType * 1000 + aRel * 100 + aTar * 10 + aParamArr.size();
	return key;
}

void Unit::RegisterConditionChange(int aMainType, int aRel, int aTar, int64 aParam, const vector<int>& aParamArr)
{
	int key = BuildConditionChangeKey(aMainType, aRel, aTar, aParam, aParamArr);
	for (auto v : mConditionChangeArr)
	{
		if (v->mKey == key)
		{  //simply cover the original data, todo: add upon or not 
			v->mParam1 = aParam;
			return;
		}
	}
	ConditionChangeData* tmp = new ConditionChangeData;
	tmp->mKey = key;
	tmp->mMainType = aMainType;
	tmp->mRelation = aRel;
	tmp->mTarget = aTar;
	tmp->mParam1 = aParam;
	tmp->mParamArr = vector<int>(aParamArr);
	mConditionChangeArr.emplace_back(tmp);
}

void Unit::UnregisterConditionChange(int aMainType, int aRel, int aTar, int64 aParam, const vector<int>& aParamArr)
{
	int key = BuildConditionChangeKey(aMainType, aRel, aTar, aParam, aParamArr);
	int num = mConditionChangeArr.size();
	for (int i = 0; i < num; ++i)
	{
		if (mConditionChangeArr[i]->mKey == key)
		{
			if (mConditionChangeArr[i]->mParam1 != aParam)
			{
				return;
			}
			else
			{
				--num;
				delete mConditionChangeArr[i];
				mConditionChangeArr[i] = mConditionChangeArr[num];
				break;
			}
		}
	}
	mConditionChangeArr.resize(num);
}

void Unit::ClearConditionChangeArr()
{
	if (mConditionChangeArr.empty())
		return;
	for (int i = 0; i < mConditionChangeArr.size(); ++i)
		delete mConditionChangeArr[i];
	mConditionChangeArr.clear();
}

int64 Unit::GetAttrByCondition(EAttribute aAttr, SharedPtr<Unit>& aTarget, SharedPtr<Skill> aSkill)
{
	int64 attr = GetAttr(aAttr);
	for (auto* data : mTableChgDataByBuffSub)
	{
		if (data->mAttr == aAttr && aTarget->CountBuffLayerBySubType(data->mType) > 0)
		{
			attr += data->mValue;
		}
	}
	if (mConditionChangeArr.empty()) 
		return attr;
	for (auto data : mConditionChangeArr)
	{
		if (static_cast<int>(aAttr) == data->mTarget)
		{
			switch (static_cast<EConditionChangeMainType>(data->mMainType))
			{
			case EConditionChangeMainType::TargetRageToSelf:
				if (data->mRelation == static_cast<int>(EConditionRelation::Greater) &&
					aTarget->GetRage() > GetRage())
				{
					attr += data->mParam1;
				}
				else if (data->mRelation == static_cast<int>(EConditionRelation::Less) &&
					aTarget->GetRage() < GetRage())
				{
					attr += data->mParam1;
				}
				break;
			case EConditionChangeMainType::CurHp:
				if (data->mRelation == static_cast<int>(EConditionRelation::Greater)
					&& mHp >= aTarget->GetHp())
				{  //self > target
					attr += data->mParam1;
				}
				else if(data->mRelation == static_cast<int>(EConditionRelation::Less)
					&& mHp <= aTarget->GetHp())
				{  //self < target
					attr += data->mParam1;
				}
				break;
			case EConditionChangeMainType::MaxHp:
				if (data->mRelation == static_cast<int>(EConditionRelation::Greater)
					&& mMaxHp > aTarget->GetMaxHp())
				{ 
					attr += data->mParam1;
				}
				else if (data->mRelation == static_cast<int>(EConditionRelation::Less)
					&& mMaxHp < aTarget->GetMaxHp())
				{ 
					attr += data->mParam1;
				}
				break;
			case EConditionChangeMainType::CurRage:
				if (data->mRelation == static_cast<int>(EConditionRelation::Greater)
					&& mRage > aTarget->GetRage())
				{
					attr += data->mParam1;
				}
				else if (data->mRelation == static_cast<int>(EConditionRelation::Less)
					&& mRage < aTarget->GetRage())
				{
					attr += data->mParam1;
				}
				break;
			case EConditionChangeMainType::MemberNumber:
				{
					int number = GetArmy().CountNonDummyUnit();
					attr += number * data->mParam1;
				}
				break;
			case EConditionChangeMainType::MemberNumberSelfLess:
				{
					int64 number = GetArmy().CountNonSummonNonDummyUnit();
					int64 coef = Max(0, SQUAD_STD_NUMBER - number);
					attr += coef * data->mParam1 / SQUAD_STD_NUMBER;
				}
				break;
			case EConditionChangeMainType::MemberNumberEnemyMore:
				{
					int64 number = GetBattleInstance().TargetArmy(*this).CountNonSummonNonDummyUnit();
					number = Min(SQUAD_STD_NUMBER, number);
					attr += number * data->mParam1 / SQUAD_STD_NUMBER;
				}
				break;
			case EConditionChangeMainType::SelfToTargetDistFar:
				{
					int64 Dist = (GetPosition() - aTarget->GetPosition()).Magnitude();
					attr += Dist * data->mParam1 / CONF_POS_CONVERT(100);
					if (attr < 0) attr = 0;
				}
				break;
			case EConditionChangeMainType::SelfToTargetDistNear:
				{
					int64 Dist = (GetPosition() - aTarget->GetPosition()).Magnitude();
					attr += data->mParam1 - data->mParam1 * Dist / CONF_POS_CONVERT(1000);
					if (attr < 0) attr = 0;
				}
				break;
			case EConditionChangeMainType::EffTargetNumber:
				if (aSkill) {
					int number = aSkill->GetEffTargetArr().size();
					attr += number * data->mParam1;
				}
				break; 
			case EConditionChangeMainType::TargetCurHp:
				{
					int64 curHpRate = BigARateB(aTarget->GetHp(), aTarget->GetMaxHp());
					//int64 curHpRate = aTarget->GetHp() * 100 / aTarget->GetMaxHp();
					attr += curHpRate * data->mParam1;
				}
				break;
			case EConditionChangeMainType::TargetCurHpLess:
				{
					int64 curHpRate = BigARateB(aTarget->GetMaxHp() - aTarget->GetHp(), aTarget->GetMaxHp());
					//int64 curHpRate = (aTarget->GetMaxHp() - aTarget->GetHp()) * 100 / aTarget->GetMaxHp();
					attr += curHpRate * data->mParam1;
				}
				break;
			case EConditionChangeMainType::TargetCurRage:
				{
					int64 invertRage = 1000 - aTarget->GetRage();
					invertRage = invertRage >= 0 ? invertRage : 0;
					attr += invertRage * data->mParam1 / 10;
				}
				break;
			case EConditionChangeMainType::TargetHasShield:
				{
					if (aTarget->HasShield())
						attr = data->mParam1;
				}
				break;
			case EConditionChangeMainType::TargetIsSummoned:
				{
					if (aTarget->IsSummoned())
						attr = data->mParam1;
				}
				break;
			case EConditionChangeMainType::TargetHasGivenSubTypes:
				{
					for (auto v : data->mParamArr)
					{
						if (aTarget->HasBuffBySubType(BuffSubType(v)))
						{
							attr += data->mParam1;
							break;
						}
					}
				}
				break;
			}
		}
	}
	return attr;
}

void Unit::AnyToDead(DieCause aCase)
{
	if (mFsm->IsInState(mStateDead->GetId()))
		return;
	CurrentSkillInterrupted();
	mDieCause = aCase;
	mFsm->DoTransition(mTransAnyToDead);
	if (mAgent)
	{
		mPhysics->RemoveAgent(mAgent);
		mAgent = nullptr;
		mBV = nullptr;
	}
}

void Unit::TryInterruptBossSkill()
{
	if (mCurSkill && mCurSkillExecutor)
	{
		if (mCurSkill->HasDefPoint())
		{
			CurrentSkillInterrupted();
		}
	}
}

int Unit::TryGetDyingEnd()
{
	if (mCurSkillExecutor && !mCurSkillExecutor->IsInactive())
	{
		return mCurSkillExecutor->mRegisterDyingTime;
	}
	return 0;
}

//获取当前角色最高"免疫位移"能级 
uint32 Unit::TryGetLargestEnergyLevel()
{
	uint32 largestLv = 1;
	return largestLv;
}

//获取当前角色累加受控减免系数  
uint32 Unit::TryGetShrinkControlSum()
{
	uint32 sum = 0;
	return sum;
}

//判断当前是否属于飘字渐变时间 
bool Unit::HasTextShift(int aSkillId)
{
	if (mTextShiftSkill.empty()) 
		return false;
	for (int i = 0; i < mTextShiftSkill.size(); i++)
	{
		if (mTextShiftSkill[i] == aSkillId)
			return true;
	}
	return false;
}
//尝试获取飘字渐变级数 
int Unit::GetTextShift(int aEntityId)
{
	if (mTextShiftSkill.empty())
		return 0;
	for (int i = 0; i < mTextShiftCounter.size(); ++i)
	{
		if (mTextShiftCounter[i].first == aEntityId)
			return mTextShiftCounter[i].second;
	}
	return 0;
}
//设置飘字渐变级数 
void Unit::SetTextShift(int aEntityId)
{
	if (mTextShiftSkill.empty())
		return;
	for (int i = 0; i < mTextShiftCounter.size(); ++i)
	{
		if (mTextShiftCounter[i].first == aEntityId)
		{
			mTextShiftCounter[i].second += 1;
			return;
		}
	}
	mTextShiftCounter.emplace_back(pair<int, int>(aEntityId, 0));
}
void Unit::CleanTextShift()
{
	mTextShiftCounter.clear();
	mTextShiftSkill.clear();
}

void Unit::SetBuffSkillInfo(int aSkillId, int aBeginCount, int aEffectCount)
{
	if (aBeginCount > 0 && GetBattleInstance().NeedDoStatistics())
	{
		for (auto& sk : mBuffSkillStatistics)
		{
			if (sk->mSkillId == aSkillId)
			{
				sk->mBeginCount += aBeginCount;
				sk->mEffectCount += aEffectCount;
				return;
			}
		}
		auto tmp = SharedPool<BuffSkillInfo>::Get();
		tmp->mSkillId = aSkillId;
		tmp->mBeginCount = aBeginCount;
		tmp->mEffectCount = aEffectCount;
		mBuffSkillStatistics.emplace_back(tmp);
	}
}

const vector<SharedPtr<BuffSkillInfo>>& Unit::GetBuffSkillInfo()
{
	return mBuffSkillStatistics;
}

bool Unit::HasShield()
{
	int ct = mBuffMgr->CountBuffLayerBySubType(BuffSubType::AbsorbDamage);
	return ct > 0;
}

bool Unit::IsArmyShooter()
{
	return mTplId == -1;
}

//------------- Old Good TD -------------

const DirectedPosition Unit::GetBornPointPosition()
{
	return mArmy->GetBornPointByIndex(mBornPoint);
}

MoveStrategy Unit::HowToMove(const RefTarget& aRefTarget)
{
	if (GetBattleInstance().UseAIPath())
	{
		return MoveStrategy::AIPath;
	}
	return MoveStrategy::Trace;
}


void Unit::RemoveAllListener()
{
	UnRegisterAllEvents();
	if (mBuffMgr)
	{
		mBuffMgr->CleanListener();
		mBuffMgr->Clear(false);
	}
}