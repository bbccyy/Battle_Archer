

#include "MoveStraight.h"


void MoveStraight::Init(StraightParam& aParam)
{
	InitBase(aParam.mSelf->GetView(), aParam.mSelf, aParam.mTarPos);
	
	mSpeed0 = aParam.mSpeed;
	mSpeed = mSpeed0;
	mNoVerticalMove = aParam.mNoVerticalMove;  //use y axis or not
	mAccInSec0 = aParam.mAccInSec0;
	mAccDInSec = aParam.mAccDInSec;

	RefreshStatus();
}


void MoveStraight::SetTargetPos(Vector3 aPos)
{
	mTargetPos = aPos;
}

void MoveStraight::RefreshStatus()
{
	mTime = 0;
	mEnabled = false;
	mStatus = EMoveStatus::EMoveInit;
	Enable();
}

void MoveStraight::SetSpeedParams(int64 aSpeed, int64 aAcc0, int64 aAccD)
{
	mSpeed0 = aSpeed;
	mSpeed = mSpeed0;
	mAccInSec0 = aAcc0;
	mAccDInSec = aAccD;
}


void MoveStraight::Enable()
{
	Vector3 curPos;
	GetPosition(curPos);
	if (mView && mSelf && mSelf->GetEntityId() > 0)
	{
		mView->Execute(ViewCommand::Maneuver,
			mSelf->GetEntityId(),
			static_cast<int>(EMoveType::EMoveStraight),
			curPos.x, curPos.y, curPos.z,
			mTargetPos.x, mTargetPos.y, mTargetPos.z,
			mSpeed, mAccInSec0, mAccDInSec,
			mNoVerticalMove);
	}
	mEnabled = true;
	mStatus = EMoveStatus::EMoveStart;
}


void MoveStraight::Disable()
{
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMoveStraight));
}


void MoveStraight::Reset()
{
	MoveExecutor::Reset();
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(0, 0, 0);
}


EMoveStatus MoveStraight::OnTick(int aDeltaTime)
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

	int64 deltLen = mSpeed * aDeltaTime + mAccInSec0 * aDeltaTime * aDeltaTime / (MS_OF_SEC2 * 2)
		+ mAccDInSec * aDeltaTime*aDeltaTime*aDeltaTime / (MS_OF_SEC3 * 6);
	//目前的时间单位是ms, mAccInSec 最小10^4，所以这里需要避免累计误差
	mSpeed = mSpeed0 + mAccInSec0 * mTime / MS_OF_SEC2 + mAccDInSec * mTime*mTime / (MS_OF_SEC3 * 2); 

	bool touchEnd = false;
	GetPosition(mCurPos);
	
	Vector3 prePos = mCurPos;
	Vector3 dist = mTargetPos - mCurPos;

	if (mNoVerticalMove)
	{
		dist.y = 0;
	}
	int64 distMagn2 = dist.Magnitude2();
	if (distMagn2 > 0)
	{
		Vector3 delt = dist;
		delt.ScaleToLen(deltLen);
		if (distMagn2 <= delt.Magnitude2())
		{
			delt = dist;
			touchEnd = true;
		}
		mCurPos += delt;
		mCurRot = delt;
	}
	else
	{
		touchEnd = true;
	}

	//if (mView)  //INFO: this part is only for testing, will remove later on
	//{
	//	mView->Execute(ViewCommand::Move
	//		, mSelf->GetEntityId()
	//		, mCurPos.x, mCurPos.y, mCurPos.z
	//		, mCurRot.x, mCurRot.y, mCurRot.z
	//		, mSpeed, 0, 0);
	//}

	SetPosAndRot(mCurPos, mCurRot); //fresh self entity

	if (touchEnd)
	{
		mStatus = EMoveStatus::EMoveDone;
	}

	return mStatus;
}


EMoveType MoveStraight::Type()
{
	return EMoveType::EMoveStraight;
}