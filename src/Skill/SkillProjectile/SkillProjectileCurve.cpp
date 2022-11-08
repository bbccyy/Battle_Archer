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


#include "SkillProjectileCurve.h"
#include "Skill/SkillCarrier.h"
#include "Skill/SkillExecutor.h"
#include "Skill/SkillDefine.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Log/Log.h"
#include "Framework/IntMath.h"
#include "View/BattleViewOutput.h"


void SkillProjectileCurve::Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
    InitBase(aCarrier, aStartPos, aRefTarget);
	if (mSkillConf->curvadata().curveacceleration_size() != SEG_NUM)
	{
		LOG_FATAL("invalid conf. skill:%d need %d curveacceleration", mSkillConf->id(), SEG_NUM);
	}
	if (mSkillConf->curvadata().controlleroffset_size() != 2)
	{
		LOG_FATAL("invalid conf. skill:%d, need 2 controlleroffset", mSkillConf->id());
	}  
	mRefTarget.GetTargetSocketBodyPos(mTargetPos);
	mStatus = EProjectileCurveStatusForward;
	mSpeed0 = CONF_VEL_CONVERT(mSkillConf->curvadata().curvespeed());

	mMoveCurve = BuildCurveExecutor(SharedFromThis());
	mCurExecutor = mMoveCurve;
}

void SkillProjectileCurve::Reset()
{
    ResetBase();
	if (mMoveCurve)
		mMoveCurve.Release();
	if (mMoveTrace)
		mMoveTrace.Release();

	mMoveStatus = EMoveStatus::EMoveDone;
	mSpeed0 = 0;
	mStatus = EProjectileCurveStatus::EProjectileCurveStatusForward;
}

bool SkillProjectileCurve::OnTick(int aDeltaTime)
{

    if(EProjectileCurveStatusDone == mStatus)
    {
        return false;
    }

	auto prePos = mPosition;
    
	mMoveStatus = mCurExecutor->OnTick(aDeltaTime);
    
    if( mMaxCollisionNum > 0 )
    {//贯穿弹道，通过碰撞检测确定参考目标 
        if( mCurCollisionNum < mMaxCollisionNum && 
			( (EProjectileCurveStatusForward == mStatus) || 
			  ( EProjectileCurveStatusForwardTrace == mStatus ) || mEffectOnBack ) )
        {
            int collisionNum = CollisionDetection(prePos, mPosition);//TODO 碰撞到障碍物的处理 
			if (collisionNum > 0 && mCarrier && !mCarrier->IsEnded())
			{
				mCarrier->GetSkill()->mCollisionCount += collisionNum;
			}
        } 
    }

    if(mMoveStatus == EMoveStatus::EMoveDone)
    {
        if( EProjectileCurveStatusForward == mStatus )
        {
            //如果目标移动了且需要锁定目标，需要进入直线追击阶段
			Vector3 tarBodyPos;
			mRefTarget.GetTargetSocketBodyPos(tarBodyPos);
            if(tarBodyPos.y != mTargetPos.y || (mLockTarget && tarBodyPos != mTargetPos ))
            {
                mStatus = EProjectileCurveStatusForwardTrace; 
				//change to trace mode
				mMoveTrace = BuildTraceExecutor(SharedFromThis());
				mMoveTrace->SetSpeedParams(mSpeed0, 0, 0);
				mMoveTrace->RefreshStatus();
				mCurExecutor = mMoveTrace;
            }
            else
            {
                OnReachTarget();
            }
                     
        }
        else if( EProjectileCurveStatusForwardTrace == mStatus )
        {
            OnReachTarget();
        }
        else if( EProjectileCurveStatusBackward == mStatus )
        {
			mStatus = EProjectileCurveStatusDone;
        }
    }
    
    return mStatus != EProjectileCurveStatusDone;
}


void SkillProjectileCurve::OnReachTarget()
{
    if( mMaxCollisionNum == 0 ) //非贯穿弹道，需要在碰到目标的时候，触发OnReachRefTarget 
    {
        mCarrier->OnReachRefTarget( mRefTarget );
    }

	if (mIsBoomerang)
	{		
		mStatus = EProjectileCurveStatusBackward;
		clearTouchedEntityIdArr();
		mTargetPos = mOwner->GetIdleBodyPosition();

		if (mMoveCurve && mMoveCurve->Type() == EMoveType::EMoveCurve)
		{
			mMoveCurve->SetTargetPos(mTargetPos);
		}
		else
		{
			if (mMoveCurve)
			{
				int64 acc0[SEG_NUM]{ 0 };
				int64 accD[SEG_NUM]{ 0 };
				int64 speed = CONF_VEL_CONVERT(mSkillConf->curvadata().curvebackspeed());
				for (int i = 0; i < SEG_NUM && i < mSkillConf->curvadata().curvebackacceleration_size(); i++)
				{
					acc0[i] = CONF_ACC_CONVERT_SEC(mSkillConf->curvadata().curvebackacceleration(i).speed());
					accD[i] = CONF_ACCD_CONVERT_SEC(mSkillConf->curvadata().curvebackacceleration(i).rate());
				}
				mMoveCurve->SetSpeedParams(speed, acc0, accD);
				mMoveCurve->SetTargetPos(mTargetPos);
				mMoveCurve->RefreshStatus();
			}
			else
			{
				LOG_FATAL("no comming but has backing moveCurve executor, skillId = %d", mSkillConf->id());
			}
			mCurExecutor = mMoveCurve;
		}
	}
	else
	{
		mStatus = EProjectileCurveStatusDone;
	}
   
}
