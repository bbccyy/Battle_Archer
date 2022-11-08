

#include "BuffModFear.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"

void BuffModFear::StackAdded(int)
{
    //nothing
}

void BuffModFear::StackRemoved(int)
{
    //nothing
}

void BuffModFear::OnEnable()
{
	mControlState = ControlToken::Create(ControlledType::RandomMove, MakeFunction<>(*this, &BuffModFear::Move), Unit::ANIM_NAME_RUN);
	GetOwner()->BeControlled(*mControlState);
}

void BuffModFear::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mControlState = nullptr;
		mMoveTarget = Vector3(0, 0, 0);
		mRefTarget.Reset();
		mInitTarget = false;
		mMoveDone = false;
		mParams.mType = 0;
		return;
	}
	auto& owner = GetOwner();
	owner->DisableMove();  //disable move to sync frontend with logicinstance 
	owner->ClearBeControlled(*mControlState);
	mControlState = nullptr;
	mMoveTarget = Vector3(0, 0, 0);
	mRefTarget.Reset();
	mInitTarget = false;
}

bool BuffModFear::Move(int aDeltaTime)
{
	auto& owner = GetOwner();
	if (mInitTarget == false)
	{
		if (mParams.mType == 0)
		{ // type == 0
			if (owner->GetBattleInstance().mIsTD && owner->GetArmyId() == 2)
			{ //in TD army2 case, aim to opposite direction 
				//mRefTarget.SetPos(owner->GetPosition());
				auto& lastP = owner->GetFirstPathPoint();
				mRefTarget.SetPos(Vector3(lastP.x, 0, lastP.z));
				mRefTarget.SetRot(Vector3(100, 0, 0)); 
				mMoveTarget = Vector3(lastP.x, 0, lastP.z); 
			}
			else
			{ //in none TD army2 case: use random self summon point
				const auto& pos = owner->GetArmy().GetSummonPointByRand();
				mMoveTarget = pos.mPos;
				mRefTarget.SetPos(mMoveTarget);
			}
			mInitTarget = true;
		}
		else
		{ // type == 1, use nearest enemy summon point
			if (owner->CheckStateAdjust(StateAdjust::Charmed))
			{
				auto& lastP = owner->GetFirstPathPoint();
				mRefTarget.SetPos(Vector3(lastP.x, 0, lastP.z));
				mRefTarget.SetRot(Vector3(100, 0, 0));
			}
			else
			{
				auto& firstP = owner->GetLastPathPoint();
				mRefTarget.SetPos(Vector3(firstP.x, 0, firstP.z));
				mRefTarget.SetRot(Vector3(100, 0, 0));
			}
			mInitTarget = true;
		}
	}
	if (mMoveDone)
	{
		return true;
	}
	if (mParams.mType == 0)
	{
		if (owner->Move(mRefTarget, owner, 0, aDeltaTime))
		{
			mMoveDone = true;
		}
	}
	else
	{
		if (owner->Move2Ref(mRefTarget, owner, 0, aDeltaTime))
		{
			mMoveDone = true;
		}
	}
	return mMoveDone;
}

void BuffModFear::ResetValues()
{
	BuffMod::ResetValues();
	mControlState = nullptr;
	mMoveTarget = Vector3(0, 0, 0);
	mRefTarget.Reset();
	mInitTarget = false;
	mMoveDone = false;
}