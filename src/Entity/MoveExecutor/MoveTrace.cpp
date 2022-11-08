
#include "MoveTrace.h"
#include "Entity/Entity.h"
#include "Framework/Util.h"

void MoveTrace::Init(TraceParam& aParam)
{
	InitBase(aParam.mSelf->GetView(), aParam.mSelf, aParam.mTarPos);
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(1, 0, 0);
	mSpeed0 = aParam.mSpeed;
	mSpeed = mSpeed0;
	mAccInSec0 = aParam.mAccInSec0;
	mAccDInSec = aParam.mAccDInSec;
	mCastRange = aParam.mCastRange;
	mRefTarget = aParam.mRefTarget;
	mNoVerticalMove = aParam.mNoVerticalMove;
	mFaceToTargetX = aParam.mFaceToTargetX;
	mFaceToTargetZ = aParam.mFaceToTargetZ;
	mDontPlayAnim = 0;
	mRingIndex = -1;
	mTotalRingNum = 10;
	if (aParam.mDontPlayAnim) mDontPlayAnim = 1;
	if (mRefTarget->GetType() == ERefTargetType::Unit)
		mTargetEntityId = mRefTarget->GetEntityId();
	else
		mTargetEntityId = 0;

	RefreshStatus();
}


void MoveTrace::Reset()
{
	MoveExecutor::Reset();
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(0, 0, 0);
	//if (mSelf) mSelf.Release();
	//mView = nullptr;
}

void MoveTrace::RefreshStatus()
{
	mTime = 0;
	mEnabled = false;
	mStatus = EMoveStatus::EMoveInit;
	Enable();
}

void MoveTrace::SetSpeedParams(int64 aSpeed, int64 aAcc0, int64 aAccD)
{
	mSpeed0 = aSpeed;
	mSpeed = mSpeed0;
	mAccInSec0 = aAcc0;
	mAccDInSec = aAccD;
}

void MoveTrace::SetRefTarget(const RefTarget* aRefTarget)
{
	mRefTarget = aRefTarget;
	mTargetEntityId = mRefTarget->GetEntityId();
}

void MoveTrace::Enable()
{
	Vector3 curPos;
	GetPosition(curPos);
	if (mView && mSelf && mSelf->GetEntityId() > 0)
	{
		mView->Execute(ViewCommand::Maneuver,
			mSelf->GetEntityId(),
			static_cast<int>(EMoveType::EMoveTrace),
			curPos.x, curPos.y, curPos.z,
			mTargetPos.x, mTargetPos.y, mTargetPos.z, mTargetEntityId,
			mSpeed, mAccInSec0, mAccDInSec,
			mCastRange, mNoVerticalMove, mFaceToTargetX, mFaceToTargetZ, mDontPlayAnim);
	}
	mEnabled = true;
	mStatus = EMoveStatus::EMoveStart;
}

void MoveTrace::Disable()
{
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMoveTrace));
}


EMoveStatus MoveTrace::OnTick(int aDeltaTime)
{
	if (!mEnabled)
	{
		Enable();
	}
	if (mStatus == EMoveStatus::EMoveDone)
	{
		return mStatus;
	}
	mTime += aDeltaTime;

	bool isModified = (mRingIndex >= 0 && mRefTarget->GetType() == ERefTargetType::Unit);

	int64 deltLen = mSpeed * aDeltaTime + mAccInSec0 * aDeltaTime * aDeltaTime / (MS_OF_SEC2 * 2)
		+ mAccDInSec * aDeltaTime*aDeltaTime*aDeltaTime / (MS_OF_SEC3 * 6);
	//目前的时间单位是ms, mAccInSec 最小10^4，所以这里需要避免累计误差
	mSpeed = mSpeed0 + mAccInSec0 * mTime / MS_OF_SEC2 + mAccDInSec * mTime*mTime / (MS_OF_SEC3 * 2);

	GetPosition(mCurPos);
	Vector3 prePos = mCurPos;
	bool touchEnd = false;

	//Tracing unit, dynamicaly get target pos on every tick
	//Notice that MoveTrace is also used by Unit and Projectile, 
	//For Unit, we only care about it's foot position 
	//However for Projectile, we care about it's Idle Body socket position 
	//To unify these two positions, by far we choose to select target's foot position 
	//and then add its y axis value with body's height
	mRefTarget->GetTargetSocketBodyPos(mTargetPos);

	if (isModified)
	{
		Vector3 tarDir = mRefTarget->GetUnit()->GetForward();
		tarDir.y = 0;
		tarDir.ScaleToLen(mCastRange);
		tarDir = Vector3::RedirectTo(tarDir, mRingIndex, mTotalRingNum);
		mTargetPos += tarDir;
		RestoreObjToPool(tarDir);
	}

	Vector3 dist = mTargetPos - mCurPos;
	if (mNoVerticalMove)
	{
		dist.y = 0;
	}

	int64 rawMagn = dist.Magnitude();
	int64 distMagn = rawMagn - mCastRange;
	if (isModified) 
		distMagn = rawMagn;

	if (distMagn > 0)
	{
		if (distMagn <= deltLen)
		{
			deltLen = distMagn + MIN_LEN;
			touchEnd = true;
		}
		dist.ScaleToLen(deltLen);
		mCurPos += dist;
		mCurRot = dist;
	}
	else
	{
		touchEnd = true;
	}

	if (mFaceToTargetX != 0 || mFaceToTargetZ != 0)
	{
		
		mCurRot.x = mFaceToTargetX - mCurPos.x;
		mCurRot.z = mFaceToTargetZ - mCurPos.z;
		mCurRot.y = 0;
	}

	SetPosAndRot(mCurPos, mCurRot); //fresh self entity
	mSelf->TryUpdateMapLocation();

	if (touchEnd)
	{
		mStatus = EMoveStatus::EMoveDone;
	}
	RestoreObjToPool(dist);
	return mStatus;
}


EMoveType MoveTrace::Type()
{
	return EMoveType::EMoveTrace;
}

void MoveTrace::SetRingPosition(int aIndex, int aTotalNum)
{
	if ((mRingIndex < 0 && aIndex < 0)
		|| (mRingIndex >= 0 && mRingIndex == aIndex))  //if no changes, return directly 
		return;

	mRingIndex = aIndex;
	mTotalRingNum = aTotalNum;
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveModify), mRingIndex, mTotalRingNum);
}