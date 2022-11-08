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


#include "SkillProjectile.h"
#include "SkillProjectileLine.h"
#include "SkillProjectileExpansionLink.h"
#include "SkillProjectileCurve.h"
#include "Skill/SkillCarrier.h"
#include "Skill/SkillExecutor.h"
#include "Skill/SkillDefine.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Log/Log.h"
#include "ConfigMgr/ConfigMgr.h"
#include "View/BattleViewOutput.h"
#include "Framework/Util.h"


// init local member like: mCarrier, mOwner, SkillConf, etc.
// set skill attributes based on Conf: LockTar? IsBoomerang?
// if this SkillProjectile need to show flying effection: figure out targetPos,and init Entity so that able to do mView and mPhysic
void SkillProjectile::InitBase(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
    mCarrier = aCarrier;
    mOwner = mCarrier->GetOwner();
    mSkillConf = mCarrier->GetSkillConf();
	
    mRefTarget.Set(aRefTarget);

	const auto& curveConf = mSkillConf->curvadata();
    mLockTarget = curveConf.istrackcurve();
    mIsBoomerang = curveConf.iscurveback();
    mEffectOnBack = curveConf.effectonback();
	mNoVerticalMove = curveConf.noverticalmove();
	mCurveRadius = CONF_POS_CONVERT(curveConf.curveradiu());

	mIsSweepLine = curveConf.isline();
	mLineLength = CONF_POS_CONVERT(curveConf.shapeparam1());

    mCurCollisionNum = 0;
    mMaxCollisionNum = 0;
	mEndOnReachRefTarget = false;
    if(curveConf.isthroughcurve())
    {
        mMaxCollisionNum = curveConf.maxthroughnum();
        mCollisionCheckType = curveConf.throughcollisiondetectiontype();
		mEndOnReachRefTarget = curveConf.disappearonreachreftarget();
    }
    if(curveConf.isdisappearoncollision())
    {
        mMaxCollisionNum = 1; //碰撞即消失 == 贯穿数为1 
        mCollisionCheckType = curveConf.collisiondetectiontype();
    }
	/*if (curveConf.curveeffect().empty())
	{
		LOG_INFO("not found projectile effect for skill %d", mSkillConf->id());
	}*/
    int target = 0;
    auto unit = aRefTarget.GetUnit();
    if (unit)
    {
        target = unit->GetEntityId();
    }
    else
    {
        //TODO
    }
    InitEntity(*mOwner->GetView(), *mOwner->GetPhysics());

	//Vector3 forward = aRefTarget.GetTargetPos(); 
	Vector3 forward;
	aRefTarget.GetTargetSocketBodyPos(forward);
	forward -= aStartPos;
	//forward.y = 0;
    mView->Execute(ViewCommand::AddProjectile
        , mEntityId
        , aCarrier->GetSkill()->GetId()
        , curveConf.curvetype()
        , mOwner->GetEntityId()
        , target, aStartPos.x, aStartPos.y, aStartPos.z, forward.x, forward.y, forward.z);
    RestoreObjToPool(forward);
	mPosition = aStartPos;
    mTime = 0;    
}

void SkillProjectile::ResetBase()
{
	if (!mOwner) return;
	ResetEntity();
    mOwner.Release();
    mCarrier.Release();
    mSkillConf = nullptr;
    clearTouchedEntityIdArr();
	if (mCurExecutor)
		mCurExecutor = nullptr;

	mRefTarget.Reset();
	mTargetPos = Vector3(0, 0, 0);

	mLockTarget = false;
	mIsBoomerang = false;
	mEffectOnBack = false;
	mNoVerticalMove = false;
	mIsSweepLine = false;
	mEndOnReachRefTarget = false;

	mCurveRadius = 0;
	mLineLength = 0;
	mCollisionCheckType = 0;
	mCurCollisionNum = 0;
	mMaxCollisionNum = 0;
	mTime = 0;
}

int SkillProjectile::CollisionDetection(Vector3& aStart, Vector3& aEnd)
{
	int collisionNum = 0;
	vector<SharedPtr<Entity> > collisionArr;
	if (!mIsSweepLine)
	{
		mOwner->GetPhysics()->SwepCircle2D(PHYSICS_GROUP_UNIT, aStart, aEnd, mCurveRadius, collisionArr);
	}
	else
	{
		mOwner->GetPhysics()->SwepLineCircle2D(PHYSICS_GROUP_UNIT, aStart, aEnd, mLineLength, collisionArr);
	}
    for( size_t i = 0; i < collisionArr.size(); ++i )
    {
        bool canTouch = false;
        auto unit = DynamicPointerCast<Unit, Entity>(collisionArr[i]);
		int entityId = unit->GetEntityId();
        switch(mCollisionCheckType)
        {
            case ECollisionCheckTypeAll:
                canTouch = true;
                break;
            case ECollisionCheckTypeEnemy:
                canTouch = mOwner->IsEnemy(unit);
                break;
            case ECollisionCheckTypeFriend:
                canTouch = ! mOwner->IsEnemy(unit);
                break;
        }
        if( canTouch && mTouchedEntityIdArr.count(entityId) == 0 )
        {
			++mCurCollisionNum;
			++collisionNum;
			mTouchedEntityIdArr.emplace(entityId);
			RefTarget refTarget;
			refTarget.SetUnit(unit);
            mCarrier->OnReachRefTarget(refTarget);
        }
        
        if( mCurCollisionNum >= mMaxCollisionNum )
        {
            LOG_DEBUG("projectile of skill:%d collision. curCollisionNum:%d, maxCollisionNum:%d. disappeare", mSkillConf->id(), mCurCollisionNum, mMaxCollisionNum);
            break;
        }
    }
	return collisionNum;
}


void SkillProjectile::clearTouchedEntityIdArr()
{
	mTouchedEntityIdArr.clear();
}

SharedPtr<SkillProjectile> NewSkillProjectile(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
    SharedPtr<SkillProjectile> projectile;
    int projectileType = aCarrier->GetSkillConf()->curvadata().curvetype();
    switch(projectileType)
    {
        case EProjectileTypeLine:
            projectile = SharedPool<SkillProjectileLine>::Get();
            break;
        case EProjectileTypeExpansionLink:
            projectile = SharedPool<SkillProjectileExpansionLink>::Get();
            break;
        case EProjectileTypeCurve:
            projectile = SharedPool<SkillProjectileCurve>::Get();
            break;
        default:
            LOG_FATAL("invalidprojectileType:%d", projectileType);
    }
    projectile->Init(aCarrier, aStartPos, aRefTarget);
    return projectile;
}


SharedPtr<MoveCurve> SkillProjectile::BuildCurveExecutor(SharedPtr<Entity> aEntity)
{
	CurveParam param;
	param.mSelf = aEntity;
	param.mTarPos = mTargetPos;
	param.mAngle = mSkillConf->curvadata().angleoffset();
	param.mOffset1 = mSkillConf->curvadata().controlleroffset(0);
	param.mOffset2 = mSkillConf->curvadata().controlleroffset(1);
	if (mSkillConf->curvadata().isfixedtime() == false)
	{
		param.mSpeed = CONF_VEL_CONVERT(mSkillConf->curvadata().curvespeed());
		for (int i = 0; i < SEG_NUM; i++)
		{
			param.mAccInSec0[i] = CONF_ACC_CONVERT_SEC(mSkillConf->curvadata().curveacceleration(i).speed());
			param.mAccDInSec[i] = CONF_ACCD_CONVERT_SEC(mSkillConf->curvadata().curveacceleration(i).rate());
		}
	}
	else
	{
		auto dist = mTargetPos - mPosition;
		dist.y = 0;
		auto lineLen = dist.Magnitude();
		param.mSpeed = lineLen / CONF_TIME_CONVERT(mSkillConf->curvadata().curveflytime());
		memset(param.mAccInSec0, 0, sizeof(int64) * SEG_NUM);
		memset(param.mAccDInSec, 0, sizeof(int64) * SEG_NUM);
	}

	auto executor = CreateMoveExecutor(EMoveType::EMoveCurve);
	MoveCurve* toPtr = static_cast<MoveCurve*>(executor.Get());
	auto moveCurve = SharedPtr<MoveCurve>(executor, toPtr);
	moveCurve->Init(param);
	return moveCurve;
}

SharedPtr<MoveTrace> SkillProjectile::BuildTraceExecutor(SharedPtr<Entity> aEntity)
{
	TraceParam param;
	param.mSelf = aEntity;
	param.mTarPos = mTargetPos;  
	param.mRefTarget = &mRefTarget;
	param.mSpeed = CONF_VEL_CONVERT(mSkillConf->curvadata().curvespeed());
	param.mAccInSec0 = CONF_ACC_CONVERT_SEC(mSkillConf->curvadata().curveacceleration(0).speed());
	param.mAccDInSec = CONF_ACCD_CONVERT_SEC(mSkillConf->curvadata().curveacceleration(0).rate());
	param.mNoVerticalMove = mNoVerticalMove;
	param.mCastRange = 0;
	param.mFaceToTargetX = 0;
	param.mFaceToTargetZ = 0;
	param.mDontPlayAnim = false;

	if (mSkillConf->curvadata().isfixedtime())
	{//fixed flying time, so recompute speed-related params
		param.mSpeed = mRotation.Magnitude() / CONF_TIME_CONVERT(mSkillConf->curvadata().curveflytime());
		param.mAccInSec0 = 0;
		param.mAccDInSec = 0;
	}

	auto executor = CreateMoveExecutor(EMoveType::EMoveTrace);
	MoveTrace* toPtr = static_cast<MoveTrace*>(executor.Get());
	auto moveTrace = SharedPtr<MoveTrace>(executor, toPtr);
	moveTrace->Init(param);
	return moveTrace;
}

SharedPtr<MoveStraight> SkillProjectile::BuildStraightExecutor(SharedPtr<Entity> aEntity)
{
	StraightParam param;
	param.mSelf = aEntity;
	param.mTarPos = mTargetPos; 
	param.mSpeed = CONF_VEL_CONVERT(mSkillConf->curvadata().curvespeed());
	param.mAccInSec0 = CONF_ACC_CONVERT_SEC(mSkillConf->curvadata().curveacceleration(0).speed());
	param.mAccDInSec = CONF_ACCD_CONVERT_SEC(mSkillConf->curvadata().curveacceleration(0).rate());
	param.mNoVerticalMove = mNoVerticalMove;

	if (mSkillConf->curvadata().isfixedtime())
	{//fixed flying time, so recompute speed-related params
		param.mSpeed = mRotation.Magnitude() / CONF_TIME_CONVERT(mSkillConf->curvadata().curveflytime());
		param.mAccInSec0 = 0;
		param.mAccDInSec = 0;
	}

	if (mMaxCollisionNum > 0 && !mIsBoomerang)
	{   //projectile that has CollisionNum and is not Boomerang will fly to the final destination
		//unless the Ctrler gives terminate signal(run out of Collision Num)
		const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
		if (!mEndOnReachRefTarget)
		{
			auto totalMove = CONF_POS_CONVERT(battleConfig->GetPenetrateMaxDistance());
			mTargetPos = mTargetPos - mPosition;
			mTargetPos.ScaleToLen(totalMove);   //get final pos
			mTargetPos = mTargetPos + mPosition;
		}
		param.mTarPos = mTargetPos;
	}

	auto executor = CreateMoveExecutor(EMoveType::EMoveStraight);
	MoveStraight* toPtr = static_cast<MoveStraight*>(executor.Get());
	auto moveStraight = SharedPtr<MoveStraight>(executor, toPtr);
	moveStraight->Init(param);
	return moveStraight;
}


