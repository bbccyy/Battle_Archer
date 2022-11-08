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


#include "HitHandlerMove.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"
#include "ConfigMgr/ConfigMgr.h"
#include "Framework/FunctionContainer.h"

void MoveController::Reset()
{
	if (mControlledUnit)
		mControlledUnit.Release();
	if (mMoveTargetUnit)
		mMoveTargetUnit.Release();
	if (mUtilizer)
		mUtilizer.Release();
	if (mSkillTargetUnit)
		mSkillTargetUnit.Release();	
	mDamageOrBuffDone = false;
	if (mMoveParabloa)
		mMoveParabloa = nullptr;
	mControlStates.clear();
	mTime = 0;
	mTotalTime = 0;
	mDownTime = 0;
	mStayTimeOnPeak = 0;
	mAnimFallDownTimeLength = 0;
	mParent = nullptr;
	mRelativeDist = 0;
	mDirection = EDirection::Forward;
	Vector3 mTargetPos = Vector3(0,0,0);
	mMoveConf = nullptr;
	mSpeedV = 0; 
	mHasUp = 0;
	mHasPeak = 0;
	mHasDown = 0;
	mHasFall = 0;
	mIsMoveSelf = 0;
	mHitAreaBound = 0;
	mDamageOrBuffDone = 0;
	mSpeedH = 0;
	mSpeedHAcc = 0;
	mMoveUpHeight = 0;  //位移高度
	mMoveDownHeight = 0;  //位移下降高度
	mSpeedUp = 0;     //位移上升速度
	mSpeedDown = 0;   //位移下落速度
	mAccUpInSec0 = 0; // 上移加速度 
	mAccDUpInSec = 0;
	mAccDownInSec0 = 0; // 下落加速度
	mAccDDownInSec = 0;
	mAccFallInSec0 = 0;
}

void MoveController::Cancel(bool aDisableMove)
{
	mControlledUnit.Release();
	if (aDisableMove && mMoveParabloa)
		mMoveParabloa->Disable();
}

bool MoveController::IsValid()
{
	if (mControlledUnit)
	{
		return true;
	}
	return false;
}

void MoveController::Init(const SkillMoveData* aConf)
{
    mMoveConf = aConf;
	mMoveStatus = EMoveStatus::EMoveInit;
	
	mSpeedH = CONF_VEL_CONVERT(mMoveConf->movespeed());
	mSpeedHAcc = CONF_ACC_CONVERT_SEC(mMoveConf->moveacceleration());
	if (mSpeedH <= 0 && mSpeedHAcc <= 0)
	{
		mSpeedH = 0;
		mSpeedHAcc = 0;
	}
	mTargetPos = GetTargetPos(); //get target pos for horizontal movement
	mStayTimeOnPeak = CONF_TIME_CONVERT(mMoveConf->staytimeonpeak());
	mHasPeak = mStayTimeOnPeak > 0;
	mAnimFallDownTimeLength = 0;
	mTime = 0;
	mDownTime = 0;
	mTotalTime = 0;
	LoadAndAnalyzeUpData();  //load and determine if has move Up phase
	LoadAndAnalyzeDownData(); // ... move Down phase
	LoadAndAnalyzeFallData(); // ... move Fall to Ground phase

	//check initial status
	ParaParam param;
	param.mSelf = mControlledUnit;
	param.mTarPos = mTargetPos;
	param.mSpeedH = mSpeedH;
	param.mSpeedHAcc = mSpeedHAcc;
	param.mTerminateV = 0;
	if (mHasUp)
	{
		mMoveStatus = EMoveStatus::EMoveParabloaUp;
		param.mSpeedV = mSpeedUp;
		param.mAccInSec0V = mAccUpInSec0;
		param.mAccDInSecV = mAccDUpInSec;
		param.mTerminateV = mControlledUnit->GetPosition().y + mMoveUpHeight;
		param.mTotalMoveV = mMoveUpHeight;  //TODO: DELETE
	}
	else if (mHasDown)
	{
		mMoveStatus = EMoveStatus::EMoveParabloaDown;
		param.mSpeedV = mSpeedDown;
		param.mAccInSec0V = mAccDownInSec0;
		param.mAccDInSecV = mAccDDownInSec;
		param.mTerminateV = mControlledUnit->GetPosition().y - mMoveDownHeight;
		param.mTotalMoveV = mMoveDownHeight;  //TODO: DELETE
	}
	else if (mHasFall)
	{
		mMoveStatus = EMoveStatus::EMoveParabloaFall;
		param.mSpeedV = mSpeedDown;  //use down speed as init
		param.mAccInSec0V = mAccFallInSec0;
		param.mAccDInSecV = mAccDDownInSec;
		param.mTerminateV = 0;
		param.mTotalMoveV = mControlledUnit->GetPosition().y;  //TODO: DELETE
		param.mTotalMoveV = param.mTotalMoveV < 0 ? 0 : param.mTotalMoveV;
		if (mControlledUnit->GetPosition().y == 0)
		{//start from fall to ground, but already on gound
			param.mSpeedV = 0;
			param.mAccInSec0V = 0;
			param.mTerminateV = 1;  //enable horizontal move in parabloa as only movement 
			param.mTotalMoveV = -1;  //TODO: DELETE
		}
	}
	else if(mSpeedH != 0 || mSpeedHAcc > 0)
	{
		// only horizontal movement, do nothing
		mMoveStatus = EMoveStatus::EMovePreDone;
		param.mSpeedV = 0;
		param.mAccInSec0V = 0;
		param.mAccDInSecV = 0;
		param.mTotalMoveV = -1;  //moveParabloa accept mTotalMoveV < 0 as no vertical movement at all
	}
	else
	{
		int skillId = 0;
		if (mParent && mParent->mSkillConf)
			skillId = mParent->mSkillConf->id();
		LOG_FATAL("unit %d has invalid move conf(skillId:%d), no case could run", mUtilizer->GetTplId(), skillId);
	}

	if (mControlledUnit->GetPosition().y < 0 && !mHasFall)
	{
		auto pos = mControlledUnit->GetPosition();
		LOG_WARN("When utilizer[%d] Execute Move handler on target[%d], current pos.y=%d while parabloa movement not include FallToGround", 
			mUtilizer->GetTplId(), mControlledUnit->GetTplId(), pos.y);
		pos.y = 0;
		mControlledUnit->SetPosition(pos, true);
	}

	//get init state moveExecutor
	auto executor = CreateMoveExecutor(EMoveType::EMoveParabloa);
	MoveParabloa* toPtr = static_cast<MoveParabloa*>(executor.Get());
	mMoveParabloa = SharedPtr<MoveParabloa>(executor, toPtr);
	mMoveParabloa->Init(param);
}

void MoveController::LoadAndAnalyzeUpData()
{
	mSpeedUp = CONF_VEL_CONVERT(mMoveConf->moveupspeed());
	mAccUpInSec0 = CONF_ACC_CONVERT_SEC(mMoveConf->moveupacceleration().speed());
	mAccDUpInSec = CONF_ACCD_CONVERT_SEC(mMoveConf->moveupacceleration().rate());
	if (mSpeedUp < 0)
	{
		int skillId = 0;
		if (mParent && mParent->mSkillConf)
			skillId = mParent->mSkillConf->id();
		LOG_FATAL("unit %d has invalid move up conf, speed = %d, skillId = %d", mUtilizer->GetEntityId(), mSpeedUp, skillId);
	}
	if (mSpeedUp == 0 && mAccUpInSec0 == 0 && mAccDUpInSec == 0)
	{ //No way to move up
		mHasUp = false;
		return;
	}
	mMoveUpHeight = CONF_POS_CONVERT(mMoveConf->moveheight());
	if (mMoveUpHeight != 0)
	{
		mHasUp = true;
		return;
	}
	//this case parabloa will never terminate automatically, must pay attention
	if (mAccUpInSec0 < 0 && mAccDUpInSec <= 0)
	{//make n trun, will hit peak
		int skillId = 0;
		if (mParent && mParent->mSkillConf)
			skillId = mParent->mSkillConf->id();
		LOG_FATAL("unit %d has invalid move up conf, it will never terminate automatically, skillId = %d", mUtilizer->GetEntityId(), skillId);
		mHasUp = true;
		return;
	}
	int skillId = 0;
	if (mParent && mParent->mSkillConf)
		skillId = mParent->mSkillConf->id();
	LOG_FATAL("unit %d has invalid move up conf, skillId = %d", mUtilizer->GetEntityId(), skillId);
	return;
}

void MoveController::LoadAndAnalyzeDownData()
{
	mSpeedDown = -CONF_VEL_CONVERT(mMoveConf->movedownspeed());  //raw conf value is positive
	mAccDownInSec0 = -CONF_ACC_CONVERT_SEC(mMoveConf->movedownacceleration().speed());
	mAccDDownInSec = -CONF_ACCD_CONVERT_SEC(mMoveConf->movedownacceleration().rate());
	if (mSpeedDown > 0)
	{
		int skillId = 0;
		if (mParent && mParent->mSkillConf)
			skillId = mParent->mSkillConf->id();
		LOG_FATAL("unit %d has invalid move down conf, speed = %d, skillId = %d", mUtilizer->GetEntityId(), mSpeedDown, skillId);
	}
	if (mSpeedDown == 0 && mAccDownInSec0 == 0 && mAccDDownInSec == 0)
	{ //No way to move down, unless fall
		mHasDown = false;
		return;
	}
	mMoveDownHeight = CONF_POS_CONVERT(mMoveConf->movedownheight());
	if (mMoveDownHeight > 0)
	{
		mHasDown = true;
		return;
	}
	if (mMoveConf->falltoground())
	{// no moveDownHeight, but has falltoground
		mHasDown = false;
		return;
	}
	//this case parabloa will never terminate automatically, must pay attention
	if (mAccDownInSec0 > 0 && mAccDDownInSec >= 0)
	{ //make U trun, will hit buttom(peak)
		mHasUp = true;
		return;
	}
	int skillId = 0;
	if (mParent && mParent->mSkillConf)
		skillId = mParent->mSkillConf->id();
	LOG_FATAL("unit %d has invalid move down conf, skillId = %d", mUtilizer->GetEntityId(), skillId);
	return;
}

void MoveController::LoadAndAnalyzeFallData()
{
	mHasFall = mMoveConf->falltoground();
	if (!mHasFall)
	{
		return;
	}
	mAccFallInSec0 = mAccDownInSec0; //make sure LoadAndAnalyzeDownData run beforehand
	if (mAccFallInSec0 == 0 && mSpeedDown == 0)
	{
		const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
		mAccFallInSec0 = -CONF_ACC_CONVERT_SEC(battleConfig->GetDefaultDownAcceleration());
	}
}

Vector3 MoveController::GetTargetPos()
{
	auto mRet = mTargetPos;
    if( mMoveTargetUnit )
    {
        Vector3 ret;
        switch( mDirection )
        {
        case EDirection::Forward:
                ret = mMoveTargetUnit->GetForward();
                ret.ScaleToLen( mRelativeDist );
                break;
        case EDirection::Backward:
                ret = mMoveTargetUnit->GetForward();
                ret.ScaleToLen( -mRelativeDist );
                break;
        case EDirection::Left:
                ret = mMoveTargetUnit->GetRight();
                ret.ScaleToLen( -mRelativeDist );
                break;
        case EDirection::Right:
                ret = mMoveTargetUnit->GetRight();
                ret.ScaleToLen( mRelativeDist );
                break;
            default:
                LOG_FATAL("invalid direction:%d", mDirection);
        }
        ret += mMoveTargetUnit->GetPosition();
		mRet = ret;
		//return ret;
    }

	if (mMoveConf->movespeed() > 0 || mMoveConf->moveacceleration() > 0)
	{ //check hit boundary condition
		auto curPos = mControlledUnit->GetPosition();
		Vector3 dest;
		//TODO: 优化该项 
		if (mUtilizer->GetBattleInstance().RestrainWithBlockLines(curPos, mRet, mControlledUnit->GetSize(), &dest) == true)
		{ // if block suc, then no need to check with RestrainToBattleArea 
			return dest;
		}
		if (mUtilizer->GetBattleInstance().RestrainToBattleArea(curPos, mRet, mControlledUnit->GetSize(), &dest) == true)
		{
			LOG_DEBUG("new pos {from=(%d,%d,%d) to=(%d,%d,%d)} out of battle area, restrict to (%d,%d,%d)"
				, curPos.x, curPos.y, curPos.z
				, mRet.x, mRet.y, mRet.z
				, dest.x, dest.y, dest.z
			);
			return dest;
		}
	}

    return mRet;
}

EMoveStatus MoveController::OnTick(int aDeltaTime)
{
	mTime += aDeltaTime;
	mTotalTime += aDeltaTime;
	auto prePos = mControlledUnit->GetPosition();
    switch(mMoveStatus)
    {
		case EMoveStatus::EMoveParabloaUp:
		{
			mParabloaStatus = mMoveParabloa->OnTick(aDeltaTime);
			if (mParabloaStatus != EMoveStatus::EMoveParabloaUp)
			{
				mTime = 0;
				mHasUp = false; //set false once "Up" done
				if (mHasPeak)
				{
					mMoveStatus = EMoveStatus::EMoveParabloaPeak;
				}
				else if (mHasDown)
				{
					mMoveStatus = EMoveStatus::EMoveParabloaDown;
					SetExecutorDown();
				}
				else if (mHasFall)
				{
					mMoveStatus = EMoveStatus::EMoveParabloaFall;
					SetExecutorFall();
				}
				else
				{
					mMoveStatus = EMoveStatus::EMovePreDone;
				}
			}
			break;
		}
		case EMoveStatus::EMoveParabloaPeak:
        {
			if (mTime >= mStayTimeOnPeak)
			{
				mTime = 0;
				mHasPeak = false; //set false once "Peak" done
				if (mHasDown)
				{
					mMoveStatus = EMoveStatus::EMoveParabloaDown;
					SetExecutorDown();
				}
				else if (mHasFall)
				{
					mMoveStatus = EMoveStatus::EMoveParabloaFall;
					SetExecutorFall();
				}
				else
				{
					mMoveStatus = EMoveStatus::EMovePreDone;
				}

				if (mUtilizer != mControlledUnit && mMoveConf->playfloatctrlainm())  // unit is dropping down to ground
				{
					//be controlled state changes here, send CMD
					//auto anim = mControlledUnit->ANIM_NAME_KNOCK;
					if (mControlStates.size() > 0)  //clean up old ctrl states for the incoming one
					{
						for (auto state : mControlStates)
						{
							state->mIsValid = false;
						}
						mControlledUnit->ClearBeControlled(*mControlStates.back());
					}
					auto anim = mMoveConf->animonfloatdown().c_str();
					auto controlStateFloatDown = ControlToken::Create(ControlledType::MoveBySkill, nullptr, anim);
					mControlStates.emplace_back(controlStateFloatDown);
					mControlledUnit->BeControlled(*controlStateFloatDown);
					mAnimFallDownTimeLength = mControlledUnit->GetKnockTimeLength();
				}
			}
            break;
        }            
		case EMoveStatus::EMoveParabloaDown:
		{
			mDownTime += aDeltaTime;
			mParabloaStatus = mMoveParabloa->OnTick(aDeltaTime);
			if (mParabloaStatus != EMoveStatus::EMoveParabloaDown)
			{
				mTime = 0;
				mHasDown = false; //set false once "Down" done
				if (mHasFall)
				{
					mMoveStatus = EMoveStatus::EMoveParabloaFall;
					SetExecutorFall();
				}
				else
				{
					mMoveStatus = EMoveStatus::EMovePreDone;
					if (mMoveParabloa->IsHorizontalDone())
					{ //exit in time
						mMoveStatus = EMoveStatus::EMoveDone;
					}
				}
			}
			break;
		}
		case EMoveStatus::EMoveParabloaFall:
		{
			mDownTime += aDeltaTime;
			//notice that, moveParabloa still consides this "Falling" request as "Down"
			mParabloaStatus = mMoveParabloa->OnTick(aDeltaTime);
			if (mParabloaStatus != EMoveStatus::EMoveParabloaDown)
			{
				SetTime();
				mHasFall = false;
				mMoveStatus = EMoveStatus::EMovePreDone;
				if (mTime >= mAnimFallDownTimeLength && mMoveParabloa->IsHorizontalDone())
				{ //exit in time
					mMoveStatus = EMoveStatus::EMoveDone;
				}
			}
			break;
		}
		case EMoveStatus::EMovePreDone:
		{
			if (!mMoveParabloa->IsHorizontalDone())
			{
				mParabloaStatus = mMoveParabloa->OnTick(aDeltaTime);
			}
			if (mTime >= mAnimFallDownTimeLength && mMoveParabloa->IsHorizontalDone())
			{
				mMoveStatus = EMoveStatus::EMoveDone;
			}
			break;
		}
		case EMoveStatus::EMoveDone:
            break;
        default:
            LOG_FATAL("invalid status:%d", mMoveStatus);
    }

	//if (mMoveParabloa->HasHorizontalMove() )// && !mMoveParabloa->IsHorizontalDone())
	//{ //check hit boundary condition
	//	auto curPos = mControlledUnit->GetPosition();
	//	Vector3 dest;
	//	if (mUtilizer->GetBattleInstance().RestrainToBattleArea(prePos, curPos, mControlledUnit->GetSize(), &dest) == true)
	//	{
	//		LOG_DEBUG("new pos {from=(%d,%d,%d) to=(%d,%d,%d)} out of battle area, restrict to (%d,%d,%d)"
	//			, prePos.x, prePos.y, prePos.z
	//			, curPos.x, curPos.y, curPos.z
	//			, dest.x, dest.y, dest.z
	//		);
	//		mMoveParabloa->SetHorizontalStatus(true);
	//		mControlledUnit->SetPosition(dest, true);
	//	}
	//}
	
	return mMoveStatus;
}

void MoveController::SetExecutorDown()
{
	mMoveParabloa->SetVerticalParam(mSpeedDown, mAccDownInSec0, mAccDDownInSec);
	mMoveParabloa->SetTotalMoveV(mMoveDownHeight);  //TODO DELETE
	mMoveParabloa->SetTerminateV(mControlledUnit->GetPosition().y - mMoveDownHeight);
	mMoveParabloa->RefreshStatus();
}

void MoveController::SetExecutorFall()
{
	mMoveParabloa->SetVerticalParam(mSpeedDown, mAccFallInSec0, mAccDDownInSec);
	mMoveParabloa->SetTotalMoveV(mControlledUnit->GetPosition().y);  //TODO DELETE
	mMoveParabloa->SetTerminateV(0);
	mMoveParabloa->RefreshStatus();
}

void MoveController::SetTime()
{
	if (mMoveConf->playfloatawayanim() == true)
	{
		mTime = mTotalTime;   //knock out should consider total time, aka from very begining
	}
	else if (mMoveConf->playfloatctrlainm() == true)
	{
		mTime = mDownTime;  //float and down only consider down time
	}
	else
	{
		mTime = 0;  //common case
	}
}

HitHandlerMove::HitHandlerMove()
{
    mIsDurative = true;
	mSetVulnerable = false;
	mSkillConf = nullptr;
	mMoveConf = nullptr;
}

void HitHandlerMove::Reset()
{
	HitHandler::Reset();
    RelaseDmgOrHealHandler();
    mMoveCtrlerArr.clear();
	if (mUtilizer)
		mUtilizer.Release();
	if (mSkillCarrier)
		mSkillCarrier.Release();
	mSkillConf = nullptr;
	mMoveConf = nullptr;
	mSetVulnerable = false;
};

bool HitHandlerMove::CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
	const SkillData* skillConf = aSkillCarrier->GetSkillConf();
	const SkillMoveData& moveConf = skillConf->movedata();
    if (aTarget->IsImmueToSkill(skillConf->id(), ESkillSubType(skillConf->basedata().subtype())))
    {
        LOG_DEBUG("unit:%d immueskill:%d from %d", aTarget->GetEntityId(), skillConf->id(), aUtilizer->GetEntityId());
        return false;
    }
	//移动前伤害的，技能效果前做命中判断 
	if (moveConf.damagetime() == EMoveSkillDamageTimeBeforeMove)
	{
		return DefaultHitDecision(aUtilizer, aTarget, aSkillCarrier);
	}
	return true;
}

void HitHandlerMove::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    mUtilizer = aUtilizer;
    mSkillCarrier = aSkillCarrier;
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
    mMoveCtrlerArr.clear();
}


void HitHandlerMove::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillMoveData& moveConf = skillConf->movedata();

    if( moveConf.damagetime() == EMoveSkillDamageTimeBeforeMove) //BeforeMove inplies there will be <Hit> Event
    {
		if (mDmgOrHealHandler)
		{
			mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
			if (aTarget->IsDead() || aSkillCarrier->IsEnded())
			{
				return;
			}
		}
		else
		{
			TriggerOnHitEvent(mUtilizer, aTarget, mSkillCarrier, 0); //even if no damage in real, try trigger Hit event anyway
		}
    }

	mMoveConf = &moveConf;
	mSkillConf = skillConf;
	mIsDurative = true;

	if (mSkillCarrier->IsEnded())
	{
		return;
	}

	if (aTarget->CheckStateAdjust(StateAdjust::MoveControlImmunity))
	{
		bool needReturn = false;
		/*switch (moveConf.movetype())
		{
		case EMoveSkillMoveTypeSelfToTargetForward:
		case EMoveSkillMoveTypeSelfToTargetBackward:
		case EMoveSkillMoveTypeRadialDirection:
			break;
		default:
			needReturn = true;
		}*/
		if (aUtilizer->GetEntityId() != aTarget->GetEntityId())
		{
			needReturn = true;
		}
		if (needReturn && aTarget->TryGetLargestEnergyLevel() >= mSkillCarrier->GetSkill()->mEnergyLvMove) {
			return;
		}
	}

	bool isPhysical = skillConf->basedata().skilltunnel() == EDamageChannelPhysical;
	int energyLv = aSkillCarrier->GetSkill()->mEnergyLv;
	if (!aTarget->AbleToInterrupt(energyLv, isPhysical))
	{ //no interrupt, so no controlled movement 
		return; 
	}

    SharedPtr<MoveController> moveCtrler = SharedPool<MoveController>::Get();
	moveCtrler->mUtilizer = aUtilizer;
	moveCtrler->mSkillTargetUnit = aTarget;
	moveCtrler->mParent = this;
	int64 moveTypeParam = CONF_POS_CONVERT(moveConf.movetypeparam());
	int64 tmpY;

    switch( moveConf.movetype() )
    {
        case EMoveSkillMoveTypeBackwardFixValue:
            moveCtrler->mControlledUnit = aTarget;
            moveCtrler->mTargetPos = aTarget->GetForward();
            moveCtrler->mTargetPos.ScaleToLen( -moveTypeParam);
            moveCtrler->mTargetPos += aTarget->GetPosition();
            break;
        case EMoveSkillMoveTypeForwardFixValue:
            moveCtrler->mControlledUnit = aTarget;
            moveCtrler->mTargetPos = aTarget->GetForward();
            moveCtrler->mTargetPos.ScaleToLen(moveTypeParam);
            moveCtrler->mTargetPos += aTarget->GetPosition();
            break;
        case EMoveSkillMoveTypeTargetToSelfForward:
            moveCtrler->mControlledUnit = aTarget;
            if( aTarget == aUtilizer )
            {            
                moveCtrler->mTargetPos = aUtilizer->GetForward();
                moveCtrler->mTargetPos.ScaleToLen(moveTypeParam);
                moveCtrler->mTargetPos += aUtilizer->GetPosition();
            }
            else
            {
                moveCtrler->mMoveTargetUnit = aUtilizer;
                moveCtrler->mDirection = EDirection::Forward;
                moveCtrler->mRelativeDist = moveTypeParam + aUtilizer->GetSize() + aTarget->GetSize();
            }            
            break;
        case EMoveSkillMoveTypeSelfToTargetForward:
            moveCtrler->mControlledUnit = aUtilizer;
            if( aTarget == aUtilizer )
            {                
                moveCtrler->mTargetPos = aTarget->GetForward();
                moveCtrler->mTargetPos.ScaleToLen(moveTypeParam + aUtilizer->GetSize() + aTarget->GetSize());
                moveCtrler->mTargetPos += aTarget->GetPosition();
            }
            else
            {
                moveCtrler->mMoveTargetUnit = aTarget;
                moveCtrler->mDirection = EDirection::Forward;
                moveCtrler->mRelativeDist = moveTypeParam + aUtilizer->GetSize() + aTarget->GetSize();
            }            
            break;
        case EMoveSkillMoveTypeSelfToTargetBackward:
            moveCtrler->mControlledUnit = aUtilizer;
            if( aTarget == aUtilizer )
            {                
                moveCtrler->mTargetPos = aTarget->GetForward();
                moveCtrler->mTargetPos.ScaleToLen( -moveTypeParam - aUtilizer->GetSize() - aTarget->GetSize());
                moveCtrler->mTargetPos += aTarget->GetPosition();
            }
            else
            {
                moveCtrler->mMoveTargetUnit = aTarget;
                moveCtrler->mDirection = EDirection::Backward;
                moveCtrler->mRelativeDist = moveTypeParam + aUtilizer->GetSize() + aTarget->GetSize();
            } 
            break;
		case EMoveSkillMoveTypeTargetLeft:
			moveCtrler->mControlledUnit = aUtilizer;
			moveCtrler->mMoveTargetUnit = aTarget;
			moveCtrler->mDirection = EDirection::Left;
			moveCtrler->mRelativeDist = moveTypeParam + aUtilizer->GetSize() + aTarget->GetSize();
			break;
		case EMoveSkillMoveTypeTargetRight:
			moveCtrler->mControlledUnit = aUtilizer;
			moveCtrler->mMoveTargetUnit = aTarget;
			moveCtrler->mDirection = EDirection::Right;
			moveCtrler->mRelativeDist = moveTypeParam + aUtilizer->GetSize() + aTarget->GetSize();
			break;
        case EMoveSkillMoveTypeSkillDir:
            moveCtrler->mControlledUnit = aTarget;
			if (aTarget == aUtilizer)
			{
				moveCtrler->mTargetPos = aUtilizer->GetForward();
			}
			else
			{
				moveCtrler->mTargetPos = aTarget->GetPosition() - aUtilizer->GetPosition();
			}            
            moveCtrler->mTargetPos.ScaleToLen(moveTypeParam);
            moveCtrler->mTargetPos += aTarget->GetPosition();
            break;
		case EMoveSkillMoveTypeSelfForwardOnly:
			moveCtrler->mControlledUnit = aTarget;
			moveCtrler->mTargetPos = aUtilizer->GetForward();
			moveCtrler->mTargetPos.ScaleToLen(moveTypeParam);
			moveCtrler->mTargetPos += aTarget->GetPosition();
			break;
        case EMoveSkillMoveTypeNegSkillDir:
            moveCtrler->mControlledUnit = aTarget;            
			if (aTarget == aUtilizer)
			{
				moveCtrler->mTargetPos = aUtilizer->GetForward();
			}
			else
			{
				moveCtrler->mTargetPos = aTarget->GetPosition() - aUtilizer->GetPosition();
			}
            moveCtrler->mTargetPos.ScaleToLen( -moveTypeParam);
            moveCtrler->mTargetPos += aTarget->GetPosition();
            break;
        case EMoveSkillMoveTypeRadialDirection:
			moveCtrler->mControlledUnit = aTarget;
			moveCtrler->mTargetPos = aTarget->GetPosition();
			tmpY = moveCtrler->mTargetPos.y;
            moveCtrler->mTargetPos -= aSkillCarrier->GetRefTarget().GetTargetPos();
			moveCtrler->mTargetPos.y = 0;
			//如果参数为正，表示正向移动，需要加上各自的半径；如果参数为负，表示移到参考目标后面    
			if (moveTypeParam > 0)
			{
				moveCtrler->mTargetPos.ScaleToLen(moveTypeParam + aTarget->GetSize() + aSkillCarrier->GetRefTarget().GetSize());
			}
			else if (moveTypeParam < 0)
			{
				moveCtrler->mTargetPos.ScaleToLen(moveTypeParam - aTarget->GetSize() - aSkillCarrier->GetRefTarget().GetSize());
			}
			else
			{
				moveCtrler->mTargetPos.ScaleToLen(0);
			}
            
            moveCtrler->mTargetPos += aSkillCarrier->GetRefTarget().GetTargetPos();
			moveCtrler->mTargetPos.y = tmpY;
            break;
		case EMoveSkillMoveTypeSelfArmyForward:
			moveCtrler->mControlledUnit = aTarget;
			{
				int dir = 1;
				if (aUtilizer->GetArmyId() == 1)
				{
					dir = -1;
				}
				moveCtrler->mTargetPos = aTarget->GetPosition();
				moveCtrler->mTargetPos.x += dir * moveTypeParam;
			}
			break;
        default:
            LOG_FATAL("invalid movetype:%d, skill:%d", moveConf.movetype(), skillConf->id());
            break;
    }
    moveCtrler->Init(&moveConf);
	if (moveConf.playfloatawayanim() == true)
	{//unit is in knock out state
		moveCtrler->mControlledUnit->EnableMoveBySkill(MakeFunction<>(*this, &HitHandlerMove::ExternalCancelRequest), nullptr, aUtilizer.Get(), moveConf.canbereftarget(), moveConf.canbeeffecttarget());
		auto controlStateKnock = aTarget->ScheduleControlToken(Unit::ANIM_NAME_KNOCK, aTarget->GetKnockTimeLength());
		//moveExecutor->mControlStates.emplace_back(controlStateKnock);
		moveCtrler->mAnimFallDownTimeLength = aTarget->GetKnockTimeLength(); //set knock anim time from begining
	}
	else if (moveConf.playfloatctrlainm() == true && !moveConf.animonfloatupandkeep().empty()) 
	{//unit is in float up and keep state, going to up
		auto anim = moveConf.animonfloatupandkeep().c_str();
		anim = aTarget->GetAnimNameByConf(anim);  //get static counterpart
		moveCtrler->mAnimFallDownTimeLength = aTarget->GetTimeLengthByAnimName(anim); //float will return 0 length 
		auto controlStateFloat = aTarget->GetControlToken(anim);
		moveCtrler->mControlStates.emplace_back(controlStateFloat);
		moveCtrler->mControlledUnit->EnableMoveBySkill(MakeFunction<>(*this, &HitHandlerMove::ExternalCancelRequest), controlStateFloat.Get(), aUtilizer.Get(), moveConf.canbereftarget(), moveConf.canbeeffecttarget());
	}
	else if (moveConf.playfloatctrlainm() == true && !moveConf.animonfloatdown().empty())
	{//unit is in float up and keep state, is now droping down to ground
		auto anim = moveConf.animonfloatdown().c_str();
		anim = aTarget->GetAnimNameByConf(anim);  //get static counterpart
		moveCtrler->mAnimFallDownTimeLength = aTarget->GetTimeLengthByAnimName(anim);
		auto controlStateFloat = aTarget->GetControlToken(anim);
		moveCtrler->mControlStates.emplace_back(controlStateFloat);
		moveCtrler->mControlledUnit->EnableMoveBySkill(MakeFunction<>(*this, &HitHandlerMove::ExternalCancelRequest), controlStateFloat.Get(), aUtilizer.Get(), moveConf.canbereftarget(), moveConf.canbeeffecttarget());
	}
	else  //no one punch this unit, simply push idle state to Unit's stack, meanwhile trans unit to fsm ctrlstate and set <canbereftarget> based on conf
	{
		//this branch gurantees that at least func EnableMoveBySkill will be executed once
		auto controlStateNormal = aTarget->GetControlToken(Unit::ANIM_NAME_IDLE);
		moveCtrler->mControlledUnit->EnableMoveBySkill(MakeFunction<>(*this, &HitHandlerMove::ExternalCancelRequest), controlStateNormal.Get(), aUtilizer.Get(), moveConf.canbereftarget(), moveConf.canbeeffecttarget());
		moveCtrler->mControlStates.emplace_back(controlStateNormal);
	}
	
    mMoveCtrlerArr.emplace_back(moveCtrler);

	if (moveConf.breakbyobstacle())
	{
		aUtilizer->IncStateAdjust(StateAdjust::VulnerableToBarrier);
		mSetVulnerable = true;
	}

}

void HitHandlerMove::DealDamageOrBuff(const SharedPtr<MoveController>& aMoveCtrler)
{
	if (aMoveCtrler->mDamageOrBuffDone)
	{
		return;
	}
	aMoveCtrler->mDamageOrBuffDone = true;
	if (mDmgOrHealHandler)
	{
		if (aMoveCtrler->mMoveConf->damagetime() == EMoveSkillDamageTimeAfterMove)
		{
			if (DefaultHitDecision(mUtilizer, aMoveCtrler->mSkillTargetUnit, mSkillCarrier))
			{
				mDmgOrHealHandler->OnHit(mUtilizer, aMoveCtrler->mSkillTargetUnit, mSkillCarrier);
			}
		}
	}
	else
	{
		if (aMoveCtrler->mMoveConf->damagetime() == EMoveSkillDamageTimeAfterMove)
		{
			TriggerOnHitEvent(mUtilizer, aMoveCtrler->mControlledUnit, mSkillCarrier, 0);  //adding buff etc...
		}
	}
}

void HitHandlerMove::CleanUpMoveExecutor(const SharedPtr<MoveController>& aMoveCtrler, bool aDisableMove)
{
	if (!aMoveCtrler || !aMoveCtrler->IsValid())
	{
		return;
	}
	
	if (aMoveCtrler->mControlStates.size() > 0)  //clean up all control states cased by this moveEcecutor
	{
		for (auto state : aMoveCtrler->mControlStates)
		{
			state->mIsValid = false;
		}
		auto state = aMoveCtrler->mControlStates.back();
		aMoveCtrler->mControlledUnit->DisableMoveBySkill(true, aMoveCtrler->mUtilizer, state.Get(), mMoveConf->canbereftarget(), mMoveConf->canbeeffecttarget());
	}
	else
	{
		aMoveCtrler->mControlledUnit->DisableMoveBySkill(true, aMoveCtrler->mUtilizer, nullptr, mMoveConf->canbereftarget(), mMoveConf->canbeeffecttarget());
	}
	aMoveCtrler->mControlStates.clear();
	aMoveCtrler->Cancel(aDisableMove);
}

bool HitHandlerMove::OnTick(int aDeltaTime)
{
	bool hasMoveDone = false;
    for(int i = 0; i < mMoveCtrlerArr.size(); i++)
    {
        auto moveCtrler = mMoveCtrlerArr[i];

		if (moveCtrler && moveCtrler->IsValid())
		{
			auto result = moveCtrler->OnTick(aDeltaTime);
			if (result == EMoveStatus::EMovePreDone)
			{
				DealDamageOrBuff(moveCtrler);
			}
			else if (result == EMoveStatus::EMoveDone)
			{
				DealDamageOrBuff(moveCtrler);
				CleanUpMoveExecutor(moveCtrler); 
				hasMoveDone = true;
			}
		}	
    }

	if (!mMoveCtrlerArr.empty() && hasMoveDone)
		mUtilizer->OnSkillMoveDone(mSkillConf->id());  //send skill move done event 

	TryCleanUpMoveCtrlerArr();

	if (!mMoveCtrlerArr.empty())
	{
		return true;
	}
	if (mSetVulnerable && mSkillConf && mSkillConf->movedata().breakbyobstacle()) 
	{
		mUtilizer->DecStateAdjust(StateAdjust::VulnerableToBarrier);
		mSetVulnerable = false;
	}
    return false;
}


void HitHandlerMove::TryCleanUpMoveCtrlerArr()
{
	size_t s = mMoveCtrlerArr.size();
	for (size_t i = 0; i < s;)
	{
		auto moveCtrl = mMoveCtrlerArr[i];
		if (!moveCtrl || !moveCtrl->IsValid())
		{
			mMoveCtrlerArr[i] = mMoveCtrlerArr[s - 1];
			--s;
		}
		else
		{
			++i;
		}
	}
	mMoveCtrlerArr.resize(s);
}


void HitHandlerMove::ExternalCancelRequest(SharedPtr<Unit> aControlledUnit)
{
    for(size_t i = 0; i < mMoveCtrlerArr.size(); i++)
    {
        auto moveCtrler = mMoveCtrlerArr[i];
        if(moveCtrler && moveCtrler->IsValid() && moveCtrler->mControlledUnit == aControlledUnit )
        {
			CleanUpMoveExecutor(moveCtrler, aControlledUnit->IsDead());
        }
    }

	if (mSetVulnerable && mSkillConf && mSkillConf->movedata().breakbyobstacle())
	{
		mUtilizer->DecStateAdjust(StateAdjust::VulnerableToBarrier);
		mSetVulnerable = false;
	}
}

void HitHandlerMove::Cancel()
{
    for (size_t i = 0; i < mMoveCtrlerArr.size(); i++)
    {
        auto moveCtrler = mMoveCtrlerArr[i];
		if (moveCtrler && moveCtrler->IsValid())
		{
			bool hasState = false;
			for (auto state : moveCtrler->mControlStates)
			{
				state->mIsValid = false;
				hasState = true;
			}
			if (hasState)
			{
				auto state = moveCtrler->mControlStates.back();
				moveCtrler->mControlledUnit->DisableMoveBySkill(true, moveCtrler->mUtilizer, state.Get(), mMoveConf->canbereftarget(), mMoveConf->canbeeffecttarget());
			}
			else
			{
				moveCtrler->mControlledUnit->DisableMoveBySkill(true, moveCtrler->mUtilizer, nullptr, mMoveConf->canbereftarget(), mMoveConf->canbeeffecttarget());
			}
			moveCtrler->Cancel(true);
		} 
    }
    mMoveCtrlerArr.clear();

	if (mSetVulnerable && mSkillConf && mSkillConf->movedata().breakbyobstacle())
	{
		mUtilizer->DecStateAdjust(StateAdjust::VulnerableToBarrier);
		mSetVulnerable = false;
	}
}