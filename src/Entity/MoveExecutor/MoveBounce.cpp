
#include "MoveBounce.h"
#include "Entity/Entity.h"
#include "Framework/Util.h"


void MoveBounce::Init(BounceParam& aParam)
{
	InitBase(aParam.mSelf->GetView(), aParam.mSelf, aParam.mTarPos);
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(1, 0, 0);
	mSpeed0 = aParam.mSpeed;
	mSpeed = mSpeed0;
	mCastRange = aParam.mCastRange;
	//mRefTarget = aParam.mRefTarget;
	for (auto point : aParam.mPath)
	{
		mPath.emplace_back(point);
	}

	RefreshStatus();
}


void MoveBounce::Reset()
{
	MoveExecutor::Reset();
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(0, 0, 0);
	mPath.clear();
}

void MoveBounce::RefreshStatus()
{
	mTime = 0;
	mEnabled = false;
	mStatus = EMoveStatus::EMoveInit;
	mPathIndex = 0;

	Vector3 curPos;
	GetPosition(curPos);

	if (mPath.size() > 0)
	{
		auto lastPos = mPath[mPath.size() - 1];
		mTargetPos.Set(lastPos.x, 0, lastPos.z);
	}
	else
	{
		mTargetPos.Set(curPos);
	}

	Enable();
}

void MoveBounce::Enable()
{
	Vector3 curPos;
	GetPosition(curPos);
	if (mView && mSelf && mSelf->GetEntityId() > 0)
	{
		mView->Execute(ViewCommand::Maneuver,
			mSelf->GetEntityId(),
			static_cast<int>(EMoveType::EMoveBounce),
			0,
			curPos, mTargetPos, 0,
			mSpeed, mCastRange, mPath);
	}
	mEnabled = true;
	mStatus = EMoveStatus::EMoveStart;
}

void MoveBounce::Disable()
{
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMoveBounce));
}


EMoveStatus MoveBounce::OnTick(int aDeltaTime)
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

	int64 deltLen = mSpeed * aDeltaTime;
	int64 deltLen2 = deltLen * deltLen;

	bool touchEnd = false;
	GetPosition(mCurPos);
	mCurPos.y = 0;
	Vector2 curP = Vector2(mCurPos.x, mCurPos.z);
	Vector2 tarP = Vector2(mTargetPos.x, mTargetPos.z);
	Vector2 d = Vector2(1, 0);
	int64 mag = 0;
	int64 mag2 = 0;

	int pSize = mPath.size();
	//Try trace along path first
	while (mPathIndex < pSize)
	{
		d.Set(mPath[mPathIndex]);
		d -= curP;
		mag2 = d.Magnitude2();
		if (mag2 > deltLen2)
		{ //stop on line segment
			d.ScaleToLen(deltLen + MIN_LEN);
			curP += d;
			deltLen = 0;
			mStatus = EMoveStatus::EMoveStart;
			break;
		}
		else if (mag2 < deltLen2)
		{ //finsih current line segment, seeking for the next
			mag = Sqrt(mag2);
			curP.Set(mPath[mPathIndex]);
			mPathIndex++;
			deltLen -= mag;
			deltLen2 = deltLen * deltLen;  //update deltLen2 
			mStatus = EMoveStatus::EMovePartDone; 
		}
		else
		{ //complete current line segment, but will not start the next 
			curP.Set(mPath[mPathIndex]);
			mPathIndex++;
			deltLen = 0;
			mStatus = EMoveStatus::EMovePartDone;
			break;
		}
	}

	Vector2 origD;
	origD.Set(d);		//path dir
	d.Set(tarP);
	d -= curP;			//target dir 

	mCurPos.x = curP.x;
	mCurPos.z = curP.z;
	mCurRot.x = origD.x;
	mCurRot.z = origD.z;

	touchEnd = false;
	if (mPathIndex >= pSize) //use up all path node 
	{
		mag2 = d.Magnitude2();
		if (mag2 <= mCastRange * mCastRange)
		{  //done
			touchEnd = true;
		}
	}
	
	SetPosAndRot(mCurPos, mCurRot); //fresh self entity
	
	if (touchEnd)
	{
		mStatus = EMoveStatus::EMoveDone;
	}

	RestoreObjToPool(curP);
	RestoreObjToPool(tarP);
	RestoreObjToPool(d);
	RestoreObjToPool(origD);
	return mStatus;
}


EMoveType MoveBounce::Type()
{
	return EMoveType::EMoveBounce;
}