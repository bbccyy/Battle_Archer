

#include "MoveExecutor.h"
#include "MoveParabloa.h"
#include "MoveCurve.h"
#include "MoveStraight.h"
#include "MoveTrace.h"


void MoveExecutor::InitBase(BattleViewOutput* aView, SharedPtr<Entity> aSelf, Vector3 aTarPos)
{
	mSelf = aSelf;
	mTargetPos = aTarPos;
	mView = aView;
	mEnabled = false;
}

void MoveExecutor::SetTargetPos(Vector3 aPos)
{
	mTargetPos = aPos;
}

void MoveExecutor::RefreshStatus()
{
	//do nothing
}

void MoveExecutor::SetSpeedParams(int64 aSpeed, int64 aAcc0, int64 aAccD)
{
	//do nothing
}

void MoveExecutor::Reset()
{
	if (mSelf) mSelf.Release();
	mView = nullptr;

	mTargetPos.Set(0, 0, 0);
	mHitAreaBound = false;
	mEnabled = false;
	mStatus = EMoveStatus::EMoveInit;
}

EMoveType MoveExecutor::Type()
{
	return EMoveType::EMoveNone;
}

void MoveExecutor::Disable()
{
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMoveNone));
}

void MoveExecutor::GetPosition(Vector3& aPos)
{
	aPos.Set(mSelf->GetPosition());
}

void MoveExecutor::SetPosition(const Vector3& aPos)
{
	mSelf->SetPosition(aPos, false);
}

void MoveExecutor::SetPosAndRot(const Vector3& aPos, const Vector3& aRot)
{
	mSelf->SetPosRot(aPos, aRot, false);
}

EMoveStatus MoveExecutor::GetMoveStatus() const
{
	return mStatus;
}

SharedPtr<MoveExecutor> CreateMoveExecutor(EMoveType aType)
{
	SharedPtr<MoveExecutor> ret = nullptr;
	switch (aType)
	{
	case EMoveType::EMoveParabloa:
	{
		ret = SharedPool<MoveParabloa>::Get();
		break;
	}
	case EMoveType::EMoveCurve:
	{
		ret = SharedPool<MoveCurve>::Get();
		break;
	}
	case EMoveType::EMoveStraight:
	{
		ret = SharedPool<MoveStraight>::Get();
		break;
	}
	case EMoveType::EMoveTrace:
	{
		ret = SharedPool<MoveTrace>::Get();
		break;
	}
	default:
	{
		LOG_FATAL("unrecognized move executor type:%d", aType);
		break;
	}
	}
	return ret;
}