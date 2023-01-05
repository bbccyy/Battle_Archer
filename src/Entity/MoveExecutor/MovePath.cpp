
#include "MovePath.h"
#include "Entity/Entity.h"
#include "Path/PathFindingMgr.h"
#include "Framework/Util.h"


void MovePath::Init(PathParam& aParam)
{
	InitBase(aParam.mSelf->GetView(), aParam.mSelf, aParam.mTarPos);
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(1, 0, 0);
	mSpeed0 = aParam.mSpeed;
	mSpeed = mSpeed0;
	mCastRange = aParam.mCastRange;
	mRefTarget = aParam.mRefTarget;
	mPathMgr = aParam.mPathMgr;
	mIsArmy1 = aParam.mIsArmy1;

	if (mRefTarget->GetType() == ERefTargetType::Unit)
		mTargetEntityId = mRefTarget->GetEntityId();
	else
		mTargetEntityId = 0;

	RefreshStatus();
}


void MovePath::Reset()
{
	MoveExecutor::Reset();
	mCurPos.Set(0, 0, 0);
	mCurRot.Set(0, 0, 0);
	mPath.clear();
}

void MovePath::RefreshStatus()
{
	mTime = 0;
	mEnabled = false;
	mStatus = EMoveStatus::EMoveInit;
	mPath.clear();
	mPathIndex = 0;
	mF = 0;
	mFT = mOutF;

	mPathMgr->TryApplyPreSetLocation(mIsArmy1);
	Vector3 curPos;
	GetPosition(curPos);
	auto& tarPos = mRefTarget->GetTargetPos();
	mPathMgr->StartPath(mSelf->GetEntityId(), Vector2(curPos.x, curPos.z), Vector2(tarPos.x, tarPos.z), mCastRange);
	mPathState = mPathMgr->GetPath(mSelf->GetEntityId(), mPath);

	if (mPathState == PathCompleteState::PathCompleteState_NotCalculated
		|| mPathState == PathCompleteState::PathCompleteState_Error)
	{
		LOG_WARN("unable to compute path");
		return;
	}

	if (mPath.size() > 0)
		mPathMgr->RegisterPreSetLocation(mPath[mPath.size() - 1], mSelf->GetSize() + AIPATH_RANGE, mSelf->GetEntityId(), mIsArmy1);
		//mPathMgr->PreSetLocation(mPath[mPath.size() - 1], mSelf->GetSize() + AIPATH_RANGE);

	if (mPath.size() == 1)
		mPath.clear();

	Enable();
}

void MovePath::Enable()
{
	Vector3 curPos;
	GetPosition(curPos);
	if (mView && mSelf && mSelf->GetEntityId() > 0)
	{
		mView->Execute(ViewCommand::Maneuver,
			mSelf->GetEntityId(),
			static_cast<int>(EMoveType::EMovePath),
			static_cast<int>(mPathState),
			curPos, mTargetPos, mTargetEntityId,
			mSpeed, mCastRange, mPath);
	}
	mEnabled = true;
	mStatus = EMoveStatus::EMoveStart;
}

void MovePath::Disable()
{
	mPathMgr->UnregisterPreSetLocation(mSelf->GetEntityId(), mIsArmy1);
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMovePath));
}


EMoveStatus MovePath::OnTick(int aDeltaTime)
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
	mF += aDeltaTime;

	int64 deltLen = mSpeed * aDeltaTime;
	int64 deltLen2 = deltLen * deltLen;

	mTargetPos = mRefTarget->GetTargetPos();

	bool touchEnd = false;
	GetPosition(mCurPos);
	mCurPos.y = 0;
	Vector2 curP = Vector2(mCurPos.x, mCurPos.z);
	Vector2 tarP = Vector2(mTargetPos.x, mTargetPos.z);
	Vector2 d = Vector2(1, 0);
	int64 mag;
	int64 mag2;

	int pSize = mPath.size();
	//Try trace along path first
	while (mPathIndex < pSize)
	{
		//d = mPath[mPathIndex] - curP;
		d.Set(mPath[mPathIndex]);
		d -= curP;
		mag2 = d.Magnitude2();
		if (mag2 > deltLen2)
		{ //stop on line segment
			d.ScaleToLen(deltLen + MIN_LEN);
			curP += d;
			deltLen = 0;
			break;
		}
		else if (mag2 < deltLen2)
		{ //finsih current line segment, seeking for the next
			mag = Sqrt(mag2);
			curP.Set(mPath[mPathIndex]);
			mPathIndex++;
			deltLen -= mag;
			deltLen2 = deltLen * deltLen;
		}
		else
		{ //complete current line segment, but will not start the next 
			curP.Set(mPath[mPathIndex]);
			mPathIndex++;
			deltLen = 0;
			break;
		}
	}

	Vector2 origD;
	origD.Set(d);
	d.Set(tarP);
	d -= curP;
	mag2 = d.Magnitude2();
	int64 castRange2 = mCastRange * mCastRange;
	if (mag2 <= castRange2)
	{  //done
		mCurPos.x = curP.x;
		mCurPos.z = curP.z;
		mCurRot.x = d.x;
		mCurRot.z = d.z;
		touchEnd = true;
	}
	else if (mPathIndex == pSize && deltLen > 0)
	{  //no path to trace, do origin MoveTrace logic
		mag = Sqrt(mag2);
		if (mag - deltLen <= mCastRange)
		{
			deltLen = mag - mCastRange + MIN_LEN;
			touchEnd = true;
		}
		d.ScaleToLen(deltLen);
		curP += d;
		mCurPos.x = curP.x;
		mCurPos.z = curP.z;
		mCurRot.x = d.x;
		mCurRot.z = d.z;
	}
	else
	{  //not reach yet, and still on path, so we use path dir
		mCurPos.x = curP.x;
		mCurPos.z = curP.z;
		mCurRot.x = origD.x;
		mCurRot.z = origD.z;
	}

	SetPosAndRot(mCurPos, mCurRot); //fresh self entity
	//mPathMgr->UpdateLocation(mSelf->GetEntityId(), curP, mSelf->GetSize() + 50000); 

	if (touchEnd)
	{
		mStatus = EMoveStatus::EMoveDone;
		mPathMgr->UnregisterPreSetLocation(mSelf->GetEntityId(), mIsArmy1);
	}
	else if (mRefTarget->GetType() == ERefTargetType::Unit) //skip refresh path when target is unmovable 
	{
		//try refresh path if any
		if (mag2 <= mThreshouldDist2)
		{
			mFT = mInF;
			if (mPathState == PathCompleteState::PathCompleteState_Partial)
			{  //if found path state is partial within certain range, do origin MoveTrace directly 
				mPathIndex = mPath.size();
				mFT = 999999;  //almost infinit time to avoid recalculate path 
				if (mSelf->mPathTD)
				{
					int prgNextIdx = mPathMgr->SyncPathProgress(mSelf->GetEntityId(), mPath[mPath.size() - 1]);
					mSelf->OnPathIndexChange(prgNextIdx);
				}
			}
		}
		else
		{
			mFT = mOutF;
		}

		if (mF >= mFT)
		{
			RefreshStatus();
		}
	}
	RestoreObjToPool(curP);
	RestoreObjToPool(tarP);
	RestoreObjToPool(d);
	RestoreObjToPool(origD);
	return mStatus;
}


EMoveType MovePath::Type()
{
	return EMoveType::EMovePath;
}