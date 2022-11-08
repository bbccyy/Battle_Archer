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


#include "SkillProjectileLine.h"
#include "Skill/SkillCarrier.h"
#include "Skill/SkillExecutor.h"
#include "Skill/SkillDefine.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Log/Log.h"
#include "View/BattleViewOutput.h"
#include "ConfigMgr/ConfigMgr.h"

void SkillProjectileLine::Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
    InitBase(aCarrier, aStartPos, aRefTarget);

	InitMoveParam();
}

void SkillProjectileLine::InitMoveParam()
{
	mStatus = EProjectileLineStatusForward;
	mStayTimeOnReachTarget = 0;
	mRefTarget.GetTargetSocketBodyPos(mTargetPos);  //set target pos before Build Executor
	mRotation = mTargetPos - mPosition;

	if (mLockTarget)  //lock target -> use MoveTrace 
	{
		mMoveTrace = BuildTraceExecutor(SharedFromThis());
		mCurExecutor = mMoveTrace;
	}
	else  // use -> MoveStraight
	{
		mMoveStraight = BuildStraightExecutor(SharedFromThis());
		mCurExecutor = mMoveStraight;
	}
}

void SkillProjectileLine::Reset()
{
    ResetBase();
	if (mMoveStraight)
		mMoveStraight = nullptr;
	if (mMoveTrace)
		mMoveTrace = nullptr;

	mStayTimeOnReachTarget = 0;

	mStatus = EProjectileLineStatus::EProjectileLineStatusForward;
	mMoveStatus = EMoveStatus::EMoveDone;
}

bool SkillProjectileLine::OnTick(int aDeltaTime)
{
    if( EProjectileLineStatusStayOnReach == mStatus )
    {
		mTime += aDeltaTime;
        if( mTime < mStayTimeOnReachTarget )
        {
            return true;
        }
        AfterReachTarget();
        mTime = 0;
    }

    if(EProjectileLineStatusDone == mStatus)
    {
        return false;
    }

	Vector3 prePos = mPosition;

	mMoveStatus = mCurExecutor->OnTick(aDeltaTime);

	//贯穿弹道，通过碰撞检测确定参考目标 
	if (mMaxCollisionNum > 0)
	{
		if (mCurCollisionNum < mMaxCollisionNum
			&& ((EProjectileLineStatusForward == mStatus) || mEffectOnBack))
		{
			int collisionNum = CollisionDetection(prePos, mPosition);//TODO 碰撞到障碍物的处理 
			if (collisionNum > 0 && mCarrier && !mCarrier->IsEnded())
			{
				mCarrier->GetSkill()->mCollisionCount += collisionNum;
			}
		}
		if (mCurCollisionNum >= mMaxCollisionNum)
		{//disappear here
			mCurExecutor->Disable();
			mStatus = EProjectileLineStatusDone;
			return false;
		}
	}

    if(mMoveStatus == EMoveStatus::EMoveDone)
    {
        if( EProjectileLineStatusForward == mStatus )
        {
            LOG_DEBUG("projectile reach target. skill:%d", mSkillConf->id());
            if( mMaxCollisionNum == 0 ) //非贯穿弹道，需要在碰到目标的时候，触发OnReachRefTarget
            {
                mCarrier->OnReachRefTarget( mRefTarget );
            }
            if( mStayTimeOnReachTarget > 0 )
            {  //this must be ExpansionLink
                mStatus = EProjectileLineStatusStayOnReach;
				mTime = 0;
            }
            else
            {                
                AfterReachTarget();
            } 
        }
        else if( EProjectileLineStatusBackward == mStatus )
        {
            LOG_DEBUG("projectile back to self. skill:%d", mSkillConf->id());
            mStatus = EProjectileLineStatusDone;
        }
    }
    
    return mStatus != EProjectileLineStatusDone;
}


void SkillProjectileLine::AfterReachTarget()
{
    if(mIsBoomerang)
    {
		clearTouchedEntityIdArr();
        mStatus = EProjectileLineStatusBackward;
		if (mSkillConf->curvadata().isfixedtime() == false)
		{
			auto speed0 = CONF_VEL_CONVERT(mSkillConf->curvadata().curvebackspeed());
			auto acc0 = CONF_ACC_CONVERT_SEC(mSkillConf->curvadata().curvebackacceleration(0).speed());
			auto accD = CONF_ACCD_CONVERT_SEC(mSkillConf->curvadata().curvebackacceleration(0).rate());
			if (mMoveTrace)
			{//refresh target accordingly
				mRefTarget.SetUnit(mOwner);
				mMoveTrace->SetRefTarget(&mRefTarget);
			}
			else if (mMoveStraight)
			{
				mTargetPos = mOwner->GetIdleBodyPosition();
				mMoveStraight->SetTargetPos(mTargetPos);
			}
			mCurExecutor->SetSpeedParams(speed0, acc0, accD);
			mCurExecutor->RefreshStatus();
		} 
    }
    else
    {
        mStatus = EProjectileLineStatusDone;
    }
}