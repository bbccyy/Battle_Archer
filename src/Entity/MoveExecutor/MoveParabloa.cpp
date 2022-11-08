

#include "MoveParabloa.h"

//Notice: this parabloa executor
//Leads by vertical movement, aka v-move, and once v-move done, we
//conside this parabloa session has done and thus will return value:
//EMoveDone. The Horizontal movement may not complete yet, the user
//should take this situation into consideration.
//Another important setting is its terminate condition:
//it's totally controlled by the variable mTotalMoveV, user should 
//bare in mind that if you choose not setting this mTotalMoveV, the 
//parabloa movement will never eventually stop(like an open curve formula)

void MoveParabloa::Init(ParaParam& aParam)
{
	InitBase(aParam.mSelf->GetView(), aParam.mSelf, aParam.mTarPos); //the tarPos denotes the end of Horizontal move
	mSpeedH = aParam.mSpeedH;
	mSpeedHAcc = aParam.mSpeedHAcc;
	mSpeedV = aParam.mSpeedV;
	mAccInSec0V = aParam.mAccInSec0V;
	mAccDInSecV = aParam.mAccDInSecV;
	mTotalMoveV = aParam.mTotalMoveV;
	mTerminateV = aParam.mTerminateV;

	reachH = mSpeedH <= 0 && mSpeedHAcc <= 0; //reach target if no horizontal speed
	RefreshStatus();
}

void MoveParabloa::RefreshStatus()
{
	mTime = 0;
	mEnabled = false;
	if (mSpeedV > 0)
	{
		mStatus = EMoveStatus::EMoveParabloaUp;
	}
	else if (mSpeedV < 0)
	{
		mStatus = EMoveStatus::EMoveParabloaDown;
	}
	else if (mAccInSec0V > 0)
	{
		mStatus = EMoveStatus::EMoveParabloaUp;
	}
	else
	{
		mStatus = EMoveStatus::EMoveParabloaDown;
	}
	Enable(); //TODO: check correctness
}

void MoveParabloa::Enable()
{
	Vector3 curPos;
	GetPosition(curPos);
	if (mView && mSelf && mSelf->GetEntityId() > 0)
	{
		mView->Execute(ViewCommand::Maneuver,
			mSelf->GetEntityId(),
			static_cast<int>(EMoveType::EMoveParabloa),
			curPos.x, curPos.y, curPos.z,
			mTargetPos.x, mTargetPos.y, mTargetPos.z,
			mSpeedH, mSpeedV,
			mAccInSec0V, mAccDInSecV,
			mTerminateV,
			reachH, mSpeedHAcc);
	}
	mEnabled = true;
}

void MoveParabloa::Disable()
{
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMoveParabloa));
}

void MoveParabloa::Reset()
{
	MoveExecutor::Reset();
}

EMoveStatus MoveParabloa::OnTick(int aDeltaTime)
{
	if (!mEnabled)
	{
		Enable();
	}
	if (mStatus == EMoveStatus::EMoveDone && reachH)
	{
		return mStatus;
	}
	mTime += aDeltaTime;

	int64 deltH = mSpeedH * aDeltaTime + mSpeedHAcc * aDeltaTime * aDeltaTime / (MS_OF_SEC2 * 2);
	mSpeedH = mSpeedH + mSpeedHAcc * aDeltaTime  / MS_OF_SEC2;
	int64 deltV = mSpeedV * aDeltaTime + mAccInSec0V * aDeltaTime * aDeltaTime / (MS_OF_SEC2 * 2)
		+ mAccDInSecV * aDeltaTime * aDeltaTime * aDeltaTime / (MS_OF_SEC3 * 6);
	mSpeedV = mSpeedV + mAccInSec0V * aDeltaTime / MS_OF_SEC2 + mAccDInSecV * aDeltaTime*aDeltaTime / (MS_OF_SEC3 * 2);

	Vector3 curPos;
	GetPosition(curPos);
	auto curV = curPos.y;
	switch (mStatus)
	{
	case EMoveStatus::EMoveParabloaUp:
	{
		if (mSpeedV <= 0)
		{
			mStatus = EMoveStatus::EMoveParabloaPeak;
		}
		if (deltV < 0)
		{  //in case mTerminateV is unreachable using given init speed and acc
			curV = mTerminateV;
		}
		if (curV <= mTerminateV) 
		{
			curV += deltV;  
			if (curV >= mTerminateV)   
			{
				//adjust deltV
				//deltV -= (curV - mTerminateV);
				curV = mTerminateV;
				mStatus = EMoveStatus::EMoveDone;
			}
		}
		break;
	}
	case EMoveStatus::EMoveParabloaPeak:
	{
		if (mSpeedV > 0)
		{
			mStatus = EMoveStatus::EMoveParabloaUp;
		}
		else if(mSpeedV < 0)
		{
			mStatus = EMoveStatus::EMoveParabloaDown;
		}
		break;
	}
	case EMoveStatus::EMoveParabloaDown:
	{
		if (mSpeedV >= 0)
		{
			mStatus = EMoveStatus::EMoveParabloaPeak;
		}
		if (deltV > 0)
		{ 
			curV = mTerminateV;
		}
		if (curV >= mTerminateV)
		{
			curV += deltV;
			if (curV <= mTerminateV)
			{
				//deltV += (mTerminateV - curV);
				curV = mTerminateV;
				mStatus = EMoveStatus::EMoveDone;
			}
		}
		break;
	}
	case EMoveStatus::EMoveDone:  //EMoveDone == Vertical requests Done
		deltV = 0;  //since vertical movement is done, do not make any change!
		break;
	default:
		LOG_FATAL("invalid status:%d", mStatus);
	}

	if (!reachH)
	{
		Vector3 distH = mTargetPos - curPos;
		distH.y = 0;
		int64 distHMagn = distH.Magnitude();
		if (distHMagn <= deltH)
		{
			deltH = distHMagn;
			reachH = true;
		}
		if (deltH <= 0)
		{// set reached when speed reduced below ZERO (in which no case could ever reach target)
			deltH = 0;
			reachH = true;
		}
		distH.ScaleToLen(deltH);
		curPos += distH;
		if (reachH && mStatus == EMoveStatus::EMoveParabloaPeak)
		{  //check if no vertical movement at all
			if (mSpeedV == 0 && mAccInSec0V == 0 && mAccDInSecV == 0)
			{
				mStatus = EMoveStatus::EMoveDone;
			}
		}
	}


	curPos.y = curV;
	if (curPos.y > MAX_UP_LIMIT)
	{
		LOG_WARN("move parabloa entity[%d] raise to altitude[%d], it's invalid, set to 0", mSelf->GetEntityId(), curPos.y);
		curPos.y = 0;
		mStatus = EMoveStatus::EMoveDone;
	}
	if (curPos.y < MAX_DOWN_LIMIT)
	{
		LOG_WARN("move parabloa entity[%d] drop down to altitude[%d], it's invalid, set to 0", mSelf->GetEntityId(), curPos.y);
		curPos.y = 0;
		mStatus = EMoveStatus::EMoveDone;
	}
	SetPosition(curPos);
	if (deltH > 0)
	{
		mSelf->TryUpdateMapLocation();
	}

	//may return Done even if not reachH yet, 
	//it's OK in that we determine status based on vertical movements 
	//so EMoveDone == Vertical requests Done
	return mStatus;
}


EMoveType MoveParabloa::Type()
{
	return EMoveType::EMoveParabloa;
}

void MoveParabloa::SetSpeedH(int64 aSpeedH)
{
	mSpeedH = aSpeedH;
}

void MoveParabloa::SetVerticalParam(int64 aSpeedV, int64 aAcc0, int64 aAccD)
{
	mSpeedV = aSpeedV;
	mAccInSec0V = aAcc0;
	mAccDInSecV = aAccD;
}

void MoveParabloa::SetTerminateV(int64 aTerminateV)
{
	mTerminateV = aTerminateV;
}

void MoveParabloa::SetSpeedV(int64 aSpeed)
{
	mSpeedV = aSpeed;
}

bool MoveParabloa::HasTerminateV()
{
	return mTerminateV != 0;
}

void MoveParabloa::SetTotalMoveV(int64 aTotalMove)
{
	mTotalMoveV = aTotalMove;
}

bool MoveParabloa::IsHorizontalDone()
{
	return reachH;
}

void MoveParabloa::SetHorizontalStatus(bool aStatus)
{
	reachH = aStatus;
}

bool MoveParabloa::HasHorizontalMove()
{
	return mSpeedH != 0 || mSpeedHAcc != 0;
}