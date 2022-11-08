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

#include "Entity.h"
#include "BattleInstance.h"
#include "View/BattleViewOutput.h"
#include "MoveExecutor/MovePath.h"
#include "MoveExecutor/MoveTrace.h"
#include "Path/PathFindingMgr.h"
#include "Framework/Util.h"

void Entity::InitEntity(BattleViewOutput& aView, PhysicsSystem& aPhysics, PathFindingMgr* aPathMgr)
{
    mView = &aView;
    mPhysics = &aPhysics;
	mPathMgr = aPathMgr;
  
    mEntityId = aView.NextId();
    mControlled = 0;
	mEntityRegister0 = 0;
    mPosition.Set(0,0,0);
    mRotation.Set(0,0,0);
	mIsMoving = false;
	mMoveRefTarget.SetType(ERefTargetType::Invalid);
	mCurrentAnimName = ANIM_NAME_IDLE;
}

bool Entity::Move2Ref(const RefTarget& aRefTarget, SharedPtr<Entity> aSelf, int aFiringRange, int aDeltaTime, ERefFaceTo aFaceTo, bool aIsArmy1)
{
	if (aRefTarget.GetType() == ERefTargetType::Invalid)
	{//if invalid, return directly 
		LOG_DEBUG("Entity %d Move receives invalid RefTarget", mEntityId);
		return true;
	}

	if (mPathMgr == nullptr)
	{
		LOG_DEBUG("Entity %d Move Path, but do not has PathMgr, is not Unit?", mEntityId);
		return true;
	}

	if (mMoveRefTarget == aRefTarget)
	{//it's just a consecutive call(tick) for previously determined movement
		if (mMovePath && mMovePath->GetMoveStatus() != EMoveStatus::EMoveDone)
		{
			auto ret = mMovePath->OnTick(aDeltaTime);
			if (ret == EMoveStatus::EMoveDone)
			{
				mMovePath->Disable();
				mMovePath = nullptr;
				mMoveRefTarget.SetType(ERefTargetType::Invalid); //if movement has done, negative its associated RefTarget
				return true;
			}
		}
		return false;
	}
	mCurrentAnimName = ANIM_NAME_RUN;
	mMoveRefTarget.Set(aRefTarget);  //load new order
	bool noVerticalMove = mMoveRefTarget.GetType() != ERefTargetType::Pos;

	//if target is already located in my cast range, no need to create any MoveExecutor	
	Vector3 tarPos;
	mMoveRefTarget.GetTargetSocketBodyPos(tarPos);
	Vector3 delt = tarPos - mPosition;
	if (noVerticalMove)
	{
		delt.y = 0;
	}
	int64 deltLen = delt.Magnitude();  //dist from A to B
	if (deltLen <= aFiringRange)
	{//Within Range
		if (ERefFaceTo::None != aFaceTo && deltLen > 0)
		{
			if (mMoveRefTarget.GetEntityId() != aSelf->GetEntityId())
			{//do not rot if target is self
				if (ERefFaceTo::OppTarget == aFaceTo)
				{
					delt.x = -delt.x;
					delt.y = -delt.y;
					delt.z = -delt.z;
				}
				//SetPosRot(mPosition, delt, false);
				SetRot(delt, true);
			}
		}
		mMoveRefTarget.SetType(ERefTargetType::Invalid);
		RestoreObjToPool(delt);
		return true;
	}
	RestoreObjToPool(delt);

	if (mMovePath)
	{//race to control, has another one in processing beforehand, disable it
		mMovePath->Disable();
		mMovePath = nullptr;
	}

	//create a brand new MoveTrace to follow orders
	mMovePath = SharedPool<MovePath>::Get();
	PathParam param;
	param.mSpeed = mSpeed;
	param.mCastRange = aFiringRange;
	param.mRefTarget = &mMoveRefTarget;
	param.mPathMgr = mPathMgr;
	param.mSelf = aSelf;
	param.mTarPos = tarPos;
	param.mIsArmy1 = aIsArmy1;
	//if target is a position, allow using y axis
	mMovePath->Init(param);

	RestoreObjToPool(tarPos);
	return false;
}

bool Entity::Move(const RefTarget& aRefTarget, SharedPtr<Entity> aSelf, int aFiringRange, int aDeltaTime, ERefFaceTo aFaceTo, int64 aSpeed, int64 aFaceX, int64 aFaceZ, bool aDontPlayAnim)
{
	if (aRefTarget.GetType() == ERefTargetType::Invalid)
	{//if invalid, return directly 
		LOG_DEBUG("Entity %d Move receives invalid RefTarget", mEntityId);
		return true;
	}

	if (mMoveRefTarget == aRefTarget)
	{//it's just a consecutive call(tick) for previously determined movement
		if (mMoveTrace && mMoveTrace->GetMoveStatus() != EMoveStatus::EMoveDone)
		{
			auto ret = mMoveTrace->OnTick(aDeltaTime);
			if (ret == EMoveStatus::EMoveDone)
			{
				mMoveTrace->Disable();
				mMoveTrace = nullptr;
				mMoveRefTarget.SetType(ERefTargetType::Invalid); //if movement has done, negative its associated RefTarget
				return true;
			}

			if (false)
			{ //used to help sync long distance MoveTrace, imporve accuracy
				mView->Execute(ViewCommand::Locate
					, mEntityId
					, mPosition.x, mPosition.y, mPosition.z
					, mRotation.x, mRotation.y, mRotation.z);
			}

		}
		return false;
	}
	mCurrentAnimName = ANIM_NAME_RUN;
	mMoveRefTarget.Set(aRefTarget);  //load new order
	bool noVerticalMove = mMoveRefTarget.GetType() != ERefTargetType::Pos;

	//if target is already located in my cast range, no need to create any MoveExecutor
	//Vector3 tarPos = mMoveRefTarget.GetTargetPos();
	Vector3 tarPos;
	mMoveRefTarget.GetTargetSocketBodyPos(tarPos);
	Vector3 delt = tarPos - mPosition;
	if (noVerticalMove)
	{
		delt.y = 0;
	}
	int64 deltLen = delt.Magnitude();  //dist from A to B
	if (deltLen <= aFiringRange)
	{//Within Range
		if (ERefFaceTo::None != aFaceTo && deltLen > 0)
		{
			if (mMoveRefTarget.GetEntityId() != aSelf->GetEntityId())
			{//do not rot if target is self
				if (ERefFaceTo::OppTarget == aFaceTo)
				{
					delt.x = -delt.x;
					delt.y = -delt.y;
					delt.z = -delt.z;
				}
				//SetPosRot(mPosition, delt, true);
				SetRot(delt, true);
			}
		}
		mMoveRefTarget.SetType(ERefTargetType::Invalid);
		RestoreObjToPool(delt);
		return true;
	}
	RestoreObjToPool(delt);

	if (mMoveTrace) 
	{//race to control, has another one in processing beforehand, disable it
		mMoveTrace->Disable();
		mMoveTrace = nullptr;
	}

	//create a brand new MoveTrace to follow orders
	mMoveTrace = SharedPool<MoveTrace>::Get();
	TraceParam param;
	param.mSpeed = mSpeed;
	if (aSpeed != 0)
		param.mSpeed = aSpeed;
	param.mAccInSec0 = 0;  //TODO: use conf value
	param.mAccDInSec = 0;
	param.mCastRange = aFiringRange;
	param.mFaceToTargetX = aFaceX;
	param.mFaceToTargetZ = aFaceZ;
	param.mDontPlayAnim = aDontPlayAnim;
	param.mRefTarget = &mMoveRefTarget;
	param.mSelf = aSelf;
	param.mTarPos = tarPos;
	//if target is a position, allow using y axis
	param.mNoVerticalMove = noVerticalMove;
	mMoveTrace->Init(param);

	//if (mMoveTrace->OnTick(aDeltaTime) == EMoveStatus::EMoveDone) //run first tick, send cmd
	//{
	//	mMoveTrace = nullptr;
	//	mMoveRefTarget.SetType(ERefTargetType::Invalid);  //don't forget to set RefTarget to Invalid state once after MoveDone
	//	return true;
	//}
	RestoreObjToPool(tarPos);
	return false;
}

// Legency: Delete it
// compute Dir and Len of Target based on Pos and Speed
// then UpdateAgent and mView->Exec(Move)
bool Entity::MoveTowards(const Vector3& aPos, int const aFiringRange, int const aDeltaTime, int const aTargetId, bool aNoRotWithinRange, int const aBehaviourMove)
{
    Vector3 delt = aPos - mPosition;
	if (aTargetId != 0)
	{
		delt.y = 0;  //only Behaviour move will consider Y axis
	}
    int64 deltLen = delt.Magnitude();
    int64 dist = deltLen - aFiringRange;
    int64 rotCondition = aNoRotWithinRange ? dist : deltLen;

	if (rotCondition > 0)
	{
		mRotation = delt;
		mRotation.y = 0;  //make sure behaviour move always face to horizon
	}

    bool reached = false;
    if (dist <= MIN_LEN)//太小的话ScaleToLen后，vector就变成0了 
    {
        reached = true;
		mIsMoving = false;
    }
    else
    {
        int64 move = mSpeed * aDeltaTime;    
        if (dist < move)
        {
            move = dist + MIN_LEN;
            reached = true;
        }
		
		delt.ScaleToLen(move);
        mPosition += delt;
		mIsMoving = true;
    }
	/*if (reached)
	{
		Vector3 tmp = aPos - mPosition;
		tmp.y = 0;
		int64 len = tmp.Magnitude();
		int64 len2 = tmp.Magnitude2();
	}*/
    
    UpdateAgent();
    mView->Execute(ViewCommand::Move
        , mEntityId
        , mPosition.x, mPosition.y, mPosition.z
        , mRotation.x, mRotation.y, mRotation.z
        , mIsMoving? mSpeed : 0, aBehaviourMove, aTargetId);  //TODO: remove param: aBehaviourMove 
        
	RestoreObjToPool(delt);
    LOG_DEBUG("Entity {entityId=%d} moved to (%d,%d,%d), target:(%d,%d,%d) firingRange:%d, reached=%d", 
                mEntityId, mPosition.x, mPosition.y, mPosition.z, aPos.x, aPos.y, aPos.z, aFiringRange, reached);
    return reached;
}

void Entity::DisableMove()
{
	if (mMoveTrace)
	{
		mMoveTrace->Disable();
		mMoveTrace = nullptr;
	}
	if (mMovePath)
	{
		mMovePath->Disable();
		mMovePath = nullptr;
	}
	mMoveRefTarget.SetType(ERefTargetType::Invalid);
	mOverLapRefTarget.SetType(ERefTargetType::Invalid);
}

bool Entity::IsMoving() const
{
	if (mMovePath || mMoveTrace || mMoveParabloa)  //the same with: mMoveRefTarget.GetType() != ERefTargetType::Invalid
		return true;
	return false;
}

RefTarget& Entity::GetMoveRefTarget()
{
	return mMoveRefTarget;
}

void Entity::ScaleOffset(int const aPercent, int const aDeltaTime)
{
    mSizeScale = mBaseSizeScale * (DENOM + aPercent) / DENOM;
    mSize = (int)(mBaseSize * mSizeScale / DENOM);
    mView->Execute(ViewCommand::Scale, mEntityId, mSizeScale, aDeltaTime);
}

void Entity::Scale(int const aScalePercent, int const aDeltaTime)
{
	mSizeScale = mBaseSizeScale * aScalePercent / DENOM;
    mSize = (int)(mBaseSize * mSizeScale / DENOM);
    mView->Execute(ViewCommand::Scale, mEntityId, mSizeScale, aDeltaTime);
}

void Entity::ClearView()
{
	if(mView)
	{
		mView->Execute(ViewCommand::DelEntity, mEntityId);
	}
    
}

uint32 Entity::GetEntityId() const
{
    return mEntityId;
}

BattleViewOutput* Entity::GetView() const
{
    return mView;
}

PhysicsSystem* Entity::GetPhysics() const
{
    return mPhysics;
}

bool Entity::GreaterEqualThan(int aArmy, Entity* aTarget)
{
	if (aArmy == 1)
	{
		if (mPosition.x < aTarget->mPosition.x && aTarget->mPosition.x - mPosition.x >= 200000) return true;
		if (mPosition.x > aTarget->mPosition.x && mPosition.x - aTarget->mPosition.x >= 200000) return false;
		if (Abs(mPosition.z) <= Abs(aTarget->mPosition.z)) return true;
		return false;
	}
	else
	{
		if (mPosition.x > aTarget->mPosition.x && mPosition.x - aTarget->mPosition.x >= 200000) return true;
		if (mPosition.x < aTarget->mPosition.x && aTarget->mPosition.x - mPosition.x >= 200000) return false;
		if (Abs(mPosition.z) <= Abs(aTarget->mPosition.z)) return true;
		return false;
	}
}

bool Entity::LessEqualThan(int aArmy, Entity* aTarget)
{
	if (aArmy == 1)
	{
		if (mPosition.x < aTarget->mPosition.x && aTarget->mPosition.x - mPosition.x >= 200000) return false;
		if (mPosition.x > aTarget->mPosition.x && mPosition.x - aTarget->mPosition.x >= 200000) return true;
		if (Abs(mPosition.z) <= Abs(aTarget->mPosition.z)) return false;
		return true;
	}
	else
	{
		if (mPosition.x > aTarget->mPosition.x && mPosition.x - aTarget->mPosition.x >= 200000) return false;
		if (mPosition.x < aTarget->mPosition.x && aTarget->mPosition.x - mPosition.x >= 200000) return true;
		if (Abs(mPosition.z) <= Abs(aTarget->mPosition.z)) return false;
		return true;
	}
}

void Entity::SetPosition(int64 const aX, int64 const aY, int64 const aZ, bool aCmd)
{
    mPosition.Set(aX, aY, aZ);
    LOG_DEBUG("Entity {id=%d} position set to (%d,%d,%d)", mEntityId, aX, aY, aZ);
    UpdateAgent();
	if (aCmd)
	{
		mView->Execute(ViewCommand::Locate
			, mEntityId
			, mPosition.x, mPosition.y, mPosition.z
			, mRotation.x, mRotation.y, mRotation.z);
	}
}
void Entity::SetPosition(const Vector3& aPos, bool aCmd)
{
    SetPosition(aPos.x, aPos.y, aPos.z, aCmd);
}
void Entity::InitLocation(const Vector3& aPos, const Vector3& aRot)
{
	mPosition.Set(aPos.x, aPos.y, aPos.z);
	LOG_DEBUG("Entity {id=%d} position init to (%d,%d,%d)", mEntityId, aPos.x, aPos.y, aPos.z);
	mRotation.Set(aRot.x, aRot.y, aRot.z);
	LOG_DEBUG("Entity {id=%d} rotation init to (%d,%d,%d)", mEntityId, aRot.x, aRot.y, aRot.z);
	UpdateAgent();
	mView->Execute(ViewCommand::InitLocation
		, mEntityId
		, mPosition.x, mPosition.y, mPosition.z
		, mRotation.x, mRotation.y, mRotation.z);
}
void Entity::SetRotation(const Vector3& aRot)
{
    mRotation.Set(aRot.x, aRot.y, aRot.z);
}
void Entity::SetPosRot(const Vector3& aPos, const Vector3& aRot, bool aSendViewCommand)
{
    mPosition.Set(aPos.x, aPos.y, aPos.z);
    LOG_DEBUG("Entity {id=%d} position set to (%d,%d,%d)", mEntityId, aPos.x, aPos.y, aPos.z);
    mRotation.Set(aRot.x, aRot.y, aRot.z);
    LOG_DEBUG("Entity {id=%d} rotation set to (%d,%d,%d)", mEntityId, aRot.x, aRot.y, aRot.z);
	UpdateAgent();
    if (aSendViewCommand)
    {
        mView->Execute(ViewCommand::Locate
            , mEntityId
            , mPosition.x, mPosition.y, mPosition.z
            , mRotation.x, mRotation.y, mRotation.z);
    }
}
void Entity::SetRot(const Vector3& aRot, bool aSendViewCommand)
{
	mRotation.Set(aRot.x, aRot.y, aRot.z);
	UpdateAgent();
	if (aSendViewCommand)
	{
		mView->Execute(ViewCommand::Locate
			, mEntityId
			, 0, 0, 0
			, mRotation.x, mRotation.y, mRotation.z, 1);
	}
}
const Vector3& Entity::GetPosition() const
{
    return mPosition;
}
const Vector3& Entity::GetForward() const
{
    return mRotation;
}
const Vector3 Entity::GetRight() const
{
    return Vector3(mRotation.z, mRotation.y, -mRotation.x);
}
int Entity::GetSpeed() const
{
    return mSpeed;
}
int Entity::GetSize() const
{
    return mSize;
}

void Entity::Reset()
{
	ResetEntity();
}

void Entity::ResetEntity()
{
	if (mMovePath)
		mMovePath.Release();
	if (mMoveTrace)
		mMoveTrace.Release();
	if (mMoveParabloa)
		mMoveParabloa.Release();

	mMoveRefTarget.Reset();
	mView = nullptr;
	mPhysics = nullptr;
	mEntityId = 0;
	mEntityRegister0 = 0;

	mPosition.Set(0,0,0);
	mRotation.Set(0, 0, 0);
	mSpeed = 0;
	mBaseSize = 0;
	mSize = 0;
	mBaseSizeScale = 0;
	mSizeScale = 0;
	mControlled = 0;  //TODO: Delete it 
	mIsMoving = false;//是否在主动移动  
	mCurrentAnimName = nullptr;
	mCurrentAnimStartTime = 0;
	mCurrentAnimLength = 0;

	mBehaviourRefTarget.Reset();
	mOverLapRefTarget.Reset();

	mPathMgr = nullptr;
	mPathTD = nullptr;
	mPathIndex = 0;
}

void Entity::TryUpdateMapLocation(bool aRetrieve)
{
	if (mPathMgr == nullptr || mPathMgr->mJustNavigate) return;
	Vector2 tmp;
	if (aRetrieve)
	{
		tmp.x = -1000000000;
		tmp.z = -1000000000;
	}
	else
	{
		tmp.x = mPosition.x;
		tmp.z = mPosition.z;
	}
	mPathMgr->UpdateLocation(mEntityId, tmp, mSize + AIPATH_RANGE);
}

void Entity::TryModifyMoveTrace(int aPosIndex)  //todo: delete it 
{
	if (mMoveTrace)
		mMoveTrace->SetRingPosition(aPosIndex, MELEE_RING_MAX_SLOT);
}

void Entity::WorldToLocal(Vector3& aPos) const
{
	//平移，处理后将只保留入参坐标aPos之于本地坐标原点mPosition的相对位置 
	aPos -= mPosition;

	//放缩
	if (mSizeScale != DENOM)
	{
		aPos *= DENOM;
		aPos /= mSizeScale;
	}

	//旋转 只考虑绕y轴的旋转
	int64 x = aPos.x;
	int64 z = aPos.z;
	int64 len = mRotation.Magnitude();
	if (len > 0)
	{
		aPos.x = (mRotation.z*x - mRotation.x*z) / len;
		aPos.z = (mRotation.x*x + mRotation.z*z) / len;
	}
}

void Entity::LocalToWorld(Vector3& aPos) const
{
	//旋转 只考虑绕y轴的旋转
	int64 x = aPos.x;
	int64 z = aPos.z;
	int64 len = mRotation.Magnitude();
	if (len > 0)
	{
		aPos.x = (mRotation.z*x + mRotation.x*z) / len;
		aPos.z = (-mRotation.x*x + mRotation.z*z) / len;
	}

	//放缩
	if (mSizeScale != DENOM)
	{
		aPos *= mSizeScale;
		aPos /= DENOM;
	}
	

	//平移
	aPos += mPosition;
}
