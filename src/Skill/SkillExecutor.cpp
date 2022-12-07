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
#include "SkillExecutor.h"
#include "Entity/Unit.h"
#include "Framework/SharedPool.h"
#include "Skill.h"
#include "SkillDefine.h"
#include "SkillCarrier.h"
#include "Define.h"
#include "Log/Log.h"
#include "BattleInstance.h"
#include "View/BattleViewOutput.h"
#include "Framework/Util.h"


// init skill executor's base data, figure out its mStartTime, register it to timeMgr
// master skill starts from onShow state, while others start from begin state
int SkillExecutor::Init(SharedPtr<Unit> aOwner, SharedPtr<Skill> apSkill, int aDelay, WeakPtr<SkillExecutor> aParent)
{
    mOwner = aOwner;
    mSkill = apSkill;
    mParent = aParent;
	mAncestors = mParent;
	if (mAncestors)
	{
		while (mAncestors->GetParent())
		{
			mAncestors = mAncestors->GetParent();
		}
		mSkill->SetAncestorSkill(mAncestors->mSkill);
	}
	else
	{
		if (!mSkill->mAncestorSkill)
			mSkill->SetAncestorSkill(mSkill);
	}
	mIsChild = (bool)mParent;
	mSkillConf = mSkill->GetSkillConf();
	mAnimConf = mSkill->GetAnimConf();
	
	if (mReflecter)
	{  //a reflect skill is a self target self skill
		mAnimConf = nullptr;
		aDelay = 0;
	}
    const vector<RefTarget>& refTargetArr = apSkill->GetRefTargetArr();
	mRefTargetArr.reserve(refTargetArr.size());
	for (int i = 0; i < refTargetArr.size(); ++i)
	{
		mRefTargetArr.emplace_back(refTargetArr[i]);
	}
	mSkill->GetEffTargetArr().clear();  //clean previous effect targets before really exec this skill

    mStatus = ESkillStatus::Init;
    mCurPhase = 0;

	RefreshSpeedFactor();

	if (aDelay != 0 && mSpeedFactor != 0)
	{ //shrink delay time 
		if (!mIsChild || mSpeedFactor > 0) //child skill is able to boost up 
			aDelay = aDelay * DENOM / (DENOM + mSpeedFactor);
	}
	mStartTime = mOwner->GetUnitTime() + aDelay;
	
    if(mTimer)
    {
        mTimer.Release();
    }
    mTimer = SharedPool<Timer<SkillExecutor> >::Get();
    if ( mSkill->IsMasterRageSkill() )
    {
		mTimer->Execute(mOwner->GetTimerMgr(), this, &SkillExecutor::OnShow, aDelay == 0 ? 0 : mStartTime);
    }
    else
    {
		mTimer->Execute(mOwner->GetTimerMgr(), this, &SkillExecutor::OnBegin, aDelay == 0 ? 0 : mStartTime);
    }
    return 0;
}

void SkillExecutor::Reset()
{
    if( !mOwner  )
    {
        return;
    }
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer.Release();
	}
	if (mParent)
		mParent.Release();
	if (mAncestors)
		mAncestors.Release();
    mCarrierArr.clear();
    mRefTargetArr.clear();
	if (mSourceUnit)
		mSourceUnit.Release();
	mOwner.Release();
	if (mReflecter)
		mReflecter.Release();
	if (mSkill)
		mSkill.Release();
	mSpeedFactor = 0;

	mBeginTime = 0;
	mSkillConf = nullptr;
	mAnimConf = nullptr;

	mIsChild = false;
	mAncestorSkill = nullptr;

	mStatus = ESkillStatus::End;
	mCurPhase = 0;

	mStartTime = 0;
	mKeyFrameTime = 0;
	mRegisterDyingTime = 0;
}

// a MasterRageSkill will start from here
// will figure out its beginTime, reset ITimer's func to OnBegin, 
// meanwhile let BattleIns do OnShow RageSkill stuff, also start child skill
bool SkillExecutor::OnShow(Timer<SkillExecutor>& aTimer)
{
	//if ( mStatus != ESkillStatus::Init )  //out date
	//	return true;
    mStatus = ESkillStatus::Show;
    int pausetime = mAnimConf ? EDITOR_CONF_TIME_CONVERT(mAnimConf->pauseendeventtime()) : 0;  // pauseendeventtime其实是show的时间，名字不合适 
	mBeginTime = mStartTime + pausetime;  // 大招开始时间（前摇开始） 
    mTimer->Reset(&SkillExecutor::OnBegin, mBeginTime);
	if (mAnimConf)
		mOwner->ConditionSendActionSpeedCMD(ActionSpeedCondition::OnNonnormalBegin);
    
	if (mSkill->IsMasterRageSkill())
	{
		//此处配合一下view层，先发出field层的指令（fullScreenMask），再触发当前技能的指令 
		auto& battleInstance = mOwner->GetBattleInstance(); 
		battleInstance.TryShowRageSkill(*mOwner); // let BattleIns pause stuffs and handle Maskcoundown etc. 
		mOwner->GetView()->Execute(ViewCommand::SkillShow, mOwner->GetEntityId(), mSkill->GetId(), mRefTargetArr);
		startChildSkill();
		int dyingtime = EDITOR_CONF_TIME_CONVERT(mSkillConf->basedata().keepdyingduration());
		if (dyingtime > 0)
		{
			mRegisterDyingTime = battleInstance.RegisterDyingTime(dyingtime, mOwner->GetArmyId());
		}
		if (mStatus == ESkillStatus::Show)
			mOwner->OnRageSkill();
		if (mStatus == ESkillStatus::Show)
			mOwner->OnRageSkillWithRef();
	}
	else
	{
		mOwner->GetView()->Execute(ViewCommand::SkillShow, mOwner->GetEntityId(), mSkill->GetId(), mRefTargetArr);
	}
    return true;
}

// will sub Rage and let BattleIns do exec OnBegin view cmd
// also find out KeyFrame and set to TimeMgr 
bool SkillExecutor::OnBegin(Timer<SkillExecutor>& aTimer)
{
	//if (mStatus != ESkillStatus::Init || mStatus != ESkillStatus::Show) //out date
	//	return true;
    mStatus = ESkillStatus::Begin;
	LOG_DEBUG("skillBegin:%d eff:%d", mSkill->GetId(), mRefTargetArr.size());
	if (mAnimConf)
	{
		if(mSkill->IsNormalSkill())
			mOwner->ConditionSendActionSpeedCMD(ActionSpeedCondition::OnNormalBegin);
		else if(!mSkill->IsMasterRageSkill())
			mOwner->ConditionSendActionSpeedCMD(ActionSpeedCondition::OnNonnormalBegin);
	}
    mOwner->GetView()->Execute(ViewCommand::SkillBegin, mOwner->GetEntityId(), mSkill->GetId(), mRefTargetArr); // 执行前摇动作 
    if(mOwner->GetBattleInstance().NeedDoStatistics())
	{   //TODO: do not use mod skillId as judgement
		if (mSkill->GetId() % 10 == 0)
		{
			mOwner->mSkillExecuteCount++;
			mSkill->mBeginCount++;
		}
		else if (mSkillConf->effectdata().recordeffecttarget())
		{
			mSkill->mBeginCount++;
		}
	}
	//deal Defend Point Logic 
	TryAddDefPointEvent();
	//try apply skill dmg text info 
	TryRegisterTextShiftInfo();
	//deal rage skill, unparallel skill or child skill 
    if (mSkill->IsMasterRageSkill())
    {
		if (mSkill->mSubRageSmoothly)
			mOwner->SkillUseRage(mSkill->mSubRageTime);  // sub all Rage from owner smoothly
		else
			mOwner->SkillUseRage(0);  // sub all Rage from owner in no duration 
        mOwner->GetBattleInstance().TryBeginRageSkill(*mOwner);
    }
	else
	{
		if (!mReflecter)
			startChildSkill();  // a child skill may also has subskills to execute
		if (mStatus != ESkillStatus::Begin)
		{ //skill is end, probabily owner is dead 
			return true;
		}
	}
    mKeyFrameTime = mStartTime; // keyframe would be right now
    if( mAnimConf )
    {
		if (mAnimConf->skilltriggerevents_size() == 0)
		{
			LOG_FATAL("Unit %d Skill %d missing conf data: skilltriggerevents", mOwner->GetEntityId(), mSkill->GetId());
		}
		int delay = 0;
		if (mSkill->HasDefPoint())
		{
			delay = mSkill->GetDefPointDuration();
		}
		else
		{
			delay = EDITOR_CONF_TIME_CONVERT(mAnimConf->skilltriggerevents(0).starttime());
			if (delay != 0 && mSpeedFactor != 0 && !mReflecter)
			{
				delay = delay * DENOM / (DENOM + mSpeedFactor);
			}
		}
        mKeyFrameTime += delay; //adjust keyframe based on conf and speed factor
        mTimer->Reset(&SkillExecutor::OnKeyFrame, mKeyFrameTime);
		mOwner->SetAnim(mAnimConf->animname().c_str());
		int animTimeLen = EDITOR_CONF_TIME_CONVERT(mAnimConf->animtimelength());
		if (!mReflecter && mSpeedFactor != 0)
		{
			animTimeLen = animTimeLen * DENOM / (DENOM + mSpeedFactor);
		}
		mOwner->SetAnimLenth(animTimeLen);
    }
    else
    { //non-MasterRageSkill (include UnparalleledSkill) will visit this branch
        return OnKeyFrame(aTimer);  // if keyframe time is right now, do it now! 
    }
    return true;
}

bool SkillExecutor::OnKeyFrame(Timer<SkillExecutor>& aTimer)
{
	if (mSkill->IsNonNormalNonRageAnimSkill())
	{ // send event at key frame if current skill is animated special normal skill 
		mOwner->OnAnimSkill();
		if (mStatus != ESkillStatus::Begin)
		{  
			return false;
		}
	}

	//DefPoint Buff's life time: SkillBegin -> KeyFrame
	CleanDefPointEvent();

	//Reflect Skill will skip KeyFrame phrase 
	if (mReflecter)
	{ //a reflect skill need skip key frame 
		SendSkillEmitCMD();
		return OnPhase(aTimer);
	}

    //恢复施放者怒气 
	int64 rageCoef = 1;
	if (mSkillConf->energyrecoverdata().adjustbytargetcount())
	{
		rageCoef = 0;  //used to cancel following addRage data, leave it till OnHitBatch for each carrier
	}
    int64 addRage = rageCoef * (mSkillConf->energyrecoverdata().param1() + int64(mSkillConf->energyrecoverdata().param2()) * mSkill->GetLevelMinus());
	if (addRage > 0)
	{
		mOwner->AddRage(addRage, ERageChangeCause::ExecuteSkill);
	}

	if (IsChild())
	{
		mSkill->RefreshRefTarget();
        vector<RefTarget>& refTargetArr = mSkill->GetRefTargetArr();
		if (refTargetArr.empty())
		{
			mStatus = ESkillStatus::End;
			LOG_DEBUG("childSkill:%d not found refTarget, ignore", mSkill->GetId());
			return false;
		}
		mRefTargetArr.swap(refTargetArr);
	}
    else
    {
		mOwner->OnSkillKeyframe(*this);  // handle triggerWithSkillArr
		if (mStatus != ESkillStatus::Begin)
		{ //make sure this skill is still actived after doing OnSkillKeyframe(which will trigger events...)
			return false;
		}
    }

	SendSkillEmitCMD();
	int firstPhaseDelay = mSkillConf->effectdata().isbysection() ? CONF_TIME_CONVERT(mSkillConf->effectdata().effectdelay()) : 0;
    LOG_DEBUG("Skill {id=%d} first phase delay=%d keyframetime=%d unittime=%d", mSkill->GetId(), firstPhaseDelay, mKeyFrameTime, mOwner->GetUnitTime());
	if (firstPhaseDelay != 0 && mSpeedFactor != 0 && !mReflecter)
	{
		firstPhaseDelay = firstPhaseDelay * DENOM / (DENOM + mSpeedFactor);
	}
	if (firstPhaseDelay > 0)
	{//delayed rage skill or has first phase delay
    	mTimer->Reset(&SkillExecutor::OnPhase, mKeyFrameTime + firstPhaseDelay);
		return true;
	}

    return OnPhase(aTimer);
}

bool SkillExecutor::OnPhase(Timer<SkillExecutor>& aTimer)
{ 
    mStatus = ESkillStatus::Emit;
    EmitCarrier();
	if (mStatus != ESkillStatus::Emit)
	{
		LOG_DEBUG("skill:%d status:%d maybe cancel", mSkill->GetId(), mStatus);
		return false;
	}
    mCurPhase++;
    if( !mReflecter &&  mSkillConf->effectdata().isbysection() && mCurPhase < mSkillConf->effectdata().effectcount() )
    {
		int phaseTimeGap = CONF_TIME_CONVERT(mSkillConf->effectdata().effectdelay()) 
                    + mCurPhase * CONF_TIME_CONVERT(mSkillConf->effectdata().effectinterval());
		if (phaseTimeGap != 0 && mSpeedFactor != 0)
		{
			phaseTimeGap = phaseTimeGap * DENOM / (DENOM + mSpeedFactor);
		}
		int nextPhaseTime = mKeyFrameTime + phaseTimeGap;
        mTimer->Reset( &SkillExecutor::OnPhase, nextPhaseTime);
        return true;
    }
	int skillTimeLen = mSkill->GetTimeLength();
	if (mSpeedFactor != 0 && !mReflecter)
	{
		skillTimeLen = skillTimeLen * DENOM / (DENOM + mSpeedFactor);
	}
	int skillEndTime = mStartTime + skillTimeLen;
	if (mOwner->GetUnitTime() >= skillEndTime)
	{
		OnEnd(aTimer);
		return false;
	}
	else
	{
		mTimer->Reset(&SkillExecutor::OnEnd, skillEndTime);
	}
    return true;
}

bool SkillExecutor::OnEnd(Timer<SkillExecutor>& aTimer)
{
	mStatus = ESkillStatus::End;
	if (mRegisterDyingTime > 0) 
	{  //revert dying time after skill done/interrupted 
		mOwner->GetBattleInstance().CleanDyingTime(mRegisterDyingTime, mOwner->GetArmyId()); 
		mRegisterDyingTime = 0; 
	}
	mSkill->CleanRefTargetArr();
	TryUnregisterTextShiftInfo();
	LOG_DEBUG("unit:%d skill:%d end", mOwner->GetEntityId(), mSkill->GetId());
	if (mAnimConf)
		mOwner->ConditionSendActionSpeedCMD(ActionSpeedCondition::OnInterrupt);
	if (IsChild() == false)
	{
		mOwner->OnSkillEnd(*this);
	}
	return false;
}

void SkillExecutor::EmitCarrier()
{
    int entityId = mOwner->GetEntityId();
    int skillId = mSkill->GetId();
	LOG_DEBUG("Skill emitting carriers {ownerId=%d,skillId=%d,refTargetCount=%d}",
        entityId,
        skillId,
        mRefTargetArr.size());
    for(size_t i = 0; i < mRefTargetArr.size(); i++)
    {
        RefTarget& refTarget = mRefTargetArr[i];

        if (refTarget.GetType() != ERefTargetType::Unit || mSkill->mNeedDead == refTarget.GetUnit()->IsDead())
        {
            LOG_DEBUG("entity:%d skill:%d generate SkillCarrier", entityId, skillId);
            //auto& targetPos = refTarget.GetTargetPos();  //FIX ME: get but not use

			Vector3 startPos;
			if (mReflecter)
			{
				startPos.Set(mOwner->GetIdleBodyPosition());
			}
			else
			{
				//startPos = mOwner->GetPosition(); //默认用角色原点位置 
				startPos.Set(mOwner->GetIdleBodyPosition());
			}
            if (mSkillConf->curvadata().iscurve() && !mReflecter)
            {
                const string& socketName = mSkillConf->curvadata().curveparent();
                if (socketName.empty() == false)
                {
                    const AnimData* animConf = mAnimConf;
					int animStartTime = mStartTime;
					if (IsChild())
					{
						if (!mParent)
						{
							LOG_FATAL("Dangling Subskill[%d]!, May results to inconsistency between cpp and lua", skillId);
						}
						else
						{
							WeakPtr<SkillExecutor> parent = mParent;
							while (animConf == nullptr && parent)
							{
								animConf = parent->GetAnimConf();
								animStartTime = parent->GetStartTime();
								parent = parent->GetParent();
							}
						}
					}
                    //当前在播的动作和技能无关  
                    if (animConf == nullptr && mOwner->HasCurrentAnimName())
                    {
						animStartTime = -1;
                        animConf = FindAnimConf(mOwner->GetAvatarName(), mOwner->GetCurrentAnimName());
                        if (animConf == nullptr && !mOwner->IsDummy())
                        {
                            LOG_WARN("not found animconf. avatar:[%s], skillId:[%d], current anim name:[%s]", mOwner->GetAvatarName().c_str(), skillId, mOwner->GetCurrentAnimName());
                        }
                    }
                    int phaseIndex = mCurPhase;
                    if (IsChild())
                    {
                        phaseIndex = -1;
                    }
                    if (GetSocketPos(animConf, animStartTime, socketName, phaseIndex, startPos))
						mOwner->LocalToWorld(startPos);
                }
                else
                {
                    LOG_WARN("skill:%d has curve, not set socketName", mSkillConf->id());
                }
            }

            SharedPtr<SkillCarrier> carrier = mOwner->GetBattleInstance().AddSkillCarrier();
			//引导性技能需要记录一下carrier，好在技能被打断的时候，取消弹道 
			if (mSkillConf->basedata().islasting() || mSkillConf->basedata().subtype() == ESkillSubTypeMove || mSkillConf->basedata().subtype() == ESkillSubTypeGrab)
			{
				mCarrierArr.emplace_back(carrier);
			}
            carrier->Init(mOwner, SharedFromThis(), startPos, refTarget);
			RestoreObjToPool(startPos);
        }
    }
}



void SkillExecutor::Interrupt()
{
	if ((mStatus == ESkillStatus::End && mCarrierArr.empty()) || mStatus == ESkillStatus::Interrupted)
	{
		return;
	}
    mStatus = ESkillStatus::Interrupted;
	mSkill->CleanRefTargetArr();
	CleanDefPointEvent();
    mTimer->Cancel();
    for (auto& carrier : mCarrierArr)
    {
		if (!carrier.Expired())
		{
			carrier->Cancel();
		}        
    }
    mCarrierArr.clear();
}

void SkillExecutor::CleanDefPointEvent()
{
	if (!mSkill->HasDefPoint())
		return;
	int defPointBuffId = mSkill->GetDefPointBuffId();
	if (defPointBuffId > 0)
	{ //remove add defpoint buff 
		mOwner->RemoveBuffAndTrigger(defPointBuffId, false);
	}
}

void SkillExecutor::TryAddDefPointEvent()
{
	if (!mSkill->HasDefPoint())
		return;
	int defPointBuffId = mSkill->GetDefPointBuffId();
	if (defPointBuffId > 0)
	{ //auto add defpoint buff 
		mOwner->TryReceiveBuff(mOwner, mOwner, defPointBuffId, 1, mSkill);
	}
}

void SkillExecutor::WhenSomeSkillInterrupted(const SharedPtr<SkillExecutor>& aSkillExecutor )
{
    //if( mSkillConf->subskilldata().islistenbreak() && aSkillExecutor.Get() == mAncestors.Get() )
	if (aSkillExecutor.Get() == mAncestors.Get())
    {
        LOG_DEBUG("skill:%d unit:%d interrupted becauseof parent interrupted", mSkillConf->id(), mOwner->GetEntityId());
        Interrupt();
    }
}

void SkillExecutor::startChildSkill()
{
    
    const vector<SharedPtr<Skill> >& childSkillArr = mSkill->GetChildSkill();

	for (size_t i = 0; i < childSkillArr.size(); i++)
	{
		int childSkillDelay = childSkillArr[i]->GetSkillConf()->subskilldata().delaytime();
		mOwner->ExecuteSkill(childSkillArr[i], childSkillDelay, SharedFromThis(), mSourceUnit);
	}

	const vector<SharedPtr<Skill> >& probabilisticSkillArr = mSkill->GetProbabilisticSkill();

	vector<int> choosedskills;
	for (int idx = 0; idx < probabilisticSkillArr.size(); idx++)
	{
		choosedskills.emplace_back(idx);
	}

	if (mSkillConf->subskilldata().useprobabilisticsubskill())
	{
		//auto& arr = mSkillConf->subskilldata().probabilisticparams();
		auto& arr = mSkill->mProbabilisticParams;
		if (arr.size() == 0 || arr.size() % 2 != 0)
		{
			LOG_WARN("ileagel subskillconf, skill Id %d", mSkill->GetId());
			return;
		}
		//get num of wanted subskills
		int totalWeight = 0;
		for (size_t idx = 1, size = arr.size(); idx < size; idx += 2)
		{
			totalWeight += static_cast<int>(arr[static_cast<int>(idx)]);
		}
		auto& battleInstance = mOwner->GetBattleInstance();
		int threshold = battleInstance.Rand(totalWeight);
		int numOfSubs = 0;
		for (size_t idx = 1, size = arr.size(); idx < size; idx += 2)
		{
			int weight = static_cast<int>(arr[static_cast<int>(idx)]);
			if (weight >= threshold)
			{
				numOfSubs = static_cast<int>(arr[static_cast<int>(idx - 1)]);
				break;
			}
			else
			{
				threshold -= weight;
			}
		}

		// choose N from M
		int M = choosedskills.size();
		int N = numOfSubs;
		if (M < N)
		{
			LOG_FATAL("in skill[%d], subskill total num[%d] < wanted num[%d]", mSkill->GetId(), M, N);
			return;
		}
		for (int idx = 0; idx < N; idx++)
		{
			//pick random idx in range
			int choosedIdx = battleInstance.Rand(M);
			//swap
			int tmp = choosedskills[choosedIdx];
			choosedskills[choosedIdx] = choosedskills[M - 1];
			choosedskills[M - 1] = tmp;
			//shrink
			M--;
		}
		M = choosedskills.size();
		for (int idx = 0; idx < M - N; idx++)
		{
			choosedskills[idx] = -1;  //dewarf rest skills
		}
	}

	for (int idx : choosedskills)
	{
		if (idx >= 0)
		{
			SharedPtr<Skill> childSkill = probabilisticSkillArr[idx];
			int childSkillDelay = childSkill->GetSkillConf()->subskilldata().delaytime();
			mOwner->ExecuteSkill(probabilisticSkillArr[idx], childSkillDelay, SharedFromThis(), mSourceUnit); 
		}
	}
	RestoreVectorToPool(choosedskills);
}

void SkillExecutor::SendSkillEmitCMD()
{
	for (int i = 0; i < mRefTargetArr.size(); ++i)
	{
		RefTarget& refTarget = mRefTargetArr[i];
		auto& targetPos = refTarget.GetTargetPos();
		mOwner->GetView()->Execute(ViewCommand::SkillEmit, mOwner->GetEntityId(), mSkill->GetId(),
			targetPos.x, targetPos.y, targetPos.z, i);
	}
}

bool SkillExecutor::GetSocketPos(const AnimData* aAnimConf, int aAnimStartTime, const string& aSocketName, int aPhaseIndex, Vector3& aPos)  const
{
    if (aAnimConf == nullptr)
    {//TODO  如果当前是非技能动作需要使用一个默认的挂点位置 
        aPos.x = 0;
        aPos.y = 0;
        aPos.z = 0;
        return true;
    }
	if (aAnimConf->skilltriggerevents_size() <= 0 || aAnimStartTime < 0)
	{
		for (int i = 0; i < aAnimConf->initsocketposition_size(); i++)
		{
			const SocketPosition& socketPos = aAnimConf->initsocketposition(i);
			if (socketPos.socketname() == aSocketName)
			{
				aPos.x = EDITOR_CONF_POS_CONVERT(socketPos.position().x());
				aPos.y = EDITOR_CONF_POS_CONVERT(socketPos.position().y());
				aPos.z = EDITOR_CONF_POS_CONVERT(socketPos.position().z());
				return true;
			}
		}
	}
	if (aAnimConf->skilltriggerevents_size() <= 0 || aAnimStartTime < 0)
	{
		for (int i = 0; i < aAnimConf->initsocketposition_size(); i++)
		{
			const SocketPosition& socketPos = aAnimConf->initsocketposition(i);
			if (socketPos.socketname() == "slot_logic_body")
			{
				aPos.x = EDITOR_CONF_POS_CONVERT(socketPos.position().x());
				aPos.y = EDITOR_CONF_POS_CONVERT(socketPos.position().y());
				aPos.z = EDITOR_CONF_POS_CONVERT(socketPos.position().z());
				return true;
			}
		}

		LOG_FATAL("skill %d has invalid anim:%s no triggerevents and inittriggerevent", mSkill->GetId(), aAnimConf->animname().c_str());
	}
    //如果没有指定是第几段，就需要根据时间找配置 
    if( aPhaseIndex < 0 )
    {
        int now = mOwner->GetUnitTime();
        aPhaseIndex = 0;
        for(int i = 0; i < aAnimConf->skilltriggerevents_size(); i++)
        {
            if( now < aAnimStartTime + EDITOR_CONF_TIME_CONVERT(aAnimConf->skilltriggerevents(i).starttime()) )
            {
                break;
            }
            aPhaseIndex = static_cast<int>(i);
        }
    }
	else if (aPhaseIndex >= aAnimConf->skilltriggerevents_size())
	{
		aPos.x = 0;
		aPos.y = 0;
		aPos.z = 0;
		LOG_FATAL("invalid phaseIndex:%d anim:%s", aPhaseIndex, aAnimConf->animname().c_str());
		return false;
	}
    const SkillTriggerEvent& skillTriggerEvent = aAnimConf->skilltriggerevents(aPhaseIndex);
    for(int i = 0; i < skillTriggerEvent.positions_size(); i++)
    {
        const SocketPosition& socketPos = skillTriggerEvent.positions(i);
        if( socketPos.socketname() == aSocketName )
        {
            aPos.x = EDITOR_CONF_POS_CONVERT( socketPos.position().x() );
            aPos.y = EDITOR_CONF_POS_CONVERT( socketPos.position().y() );
            aPos.z = EDITOR_CONF_POS_CONVERT( socketPos.position().z() );
            return true;
        }
    }
    return false;
}

const SkillData* SkillExecutor::GetSkillConf() const
{
    return mSkillConf;
}
const AnimData* SkillExecutor::GetAnimConf() const
{
    return mAnimConf;
}
const SharedPtr<Skill> SkillExecutor::GetSkill() const
{
    return mSkill;
}
bool SkillExecutor::IsChild() const
{
	return mIsChild;    
}
const WeakPtr<SkillExecutor> SkillExecutor::GetParent() const
{
    return mParent;
}
int SkillExecutor::GetStartTime() const
{
    return mStartTime;
}
const vector<RefTarget>& SkillExecutor::GetRefTargetArr() const
{
    return mRefTargetArr;
}
int SkillExecutor::GetCurPhase() const
{
    return mCurPhase;
}
bool SkillExecutor::IsInactive() const
{
    return mStatus == ESkillStatus::End || mStatus == ESkillStatus::Interrupted;
}
bool SkillExecutor::WillPlayHitAnim() const
{
    if (mStatus == ESkillStatus::Begin && !mSkillConf->basedata().isplayhitanim())
    {
		return false;
    }
	return true;
}

void SkillExecutor::SetSourceUnit(SharedPtr<Unit> aSourceUnit)
{
	mSourceUnit = aSourceUnit;
}

void SkillExecutor::SetReflecter(SharedPtr<Unit> aReflecter)
{
	mReflecter = aReflecter;
}

SharedPtr<Unit> SkillExecutor::GetSourceUnit()
{
	return mSourceUnit ? mSourceUnit : mOwner;
}

void SkillExecutor::RefreshSpeedFactor()
{
	mSpeedFactor = mOwner->GetSpeedFactor();
	if (!mSkill->IsNormalSkill())
	{
		mSpeedFactor = 0;
	}
}

//try register text shift info to skill owner
void SkillExecutor::TryRegisterTextShiftInfo()
{
	if (!mSkillConf->basedata().skillspecialdata().activetextshift())
		return;
	auto& list = mSkillConf->basedata().skillspecialdata().textshiftskillarr();
	mOwner->CleanTextShift();
	for (auto skillId : list)
	{
		mOwner->mTextShiftSkill.emplace_back(skillId);
	}
}

//try unregister text shift info
void SkillExecutor::TryUnregisterTextShiftInfo()
{
	if (!mSkillConf->basedata().skillspecialdata().activetextshift())
		return;
	mOwner->CleanTextShift();
}