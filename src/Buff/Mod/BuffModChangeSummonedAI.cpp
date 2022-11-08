

#include "BuffModChangeSummonedAI.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModChangeSummonedAI::StackAdded(int)
{
    //nothing
}

void BuffModChangeSummonedAI::StackRemoved(int)
{
    //nothing
}

void BuffModChangeSummonedAI::OnEnable()
{
	auto& owner = GetOwner();
	if (!owner->IsSummoned())
	{
		LOG_WARN("try add BuffModChangeSummonedAI onto a non-summoned unit, tid = %d, buffId = %d", owner->GetTplId(), GetBuff()->GetId());
		return;
	}
	auto* summoner = owner->mSummoner;
	if (!summoner || summoner->IsDead())
	{
		LOG_DEBUG("try add BuffModChangeSummonedAI, but summoner is invalid");
		return;
	}

	auto ownerPos = Vector3(owner->GetPosition());
	summoner->WorldToLocal(ownerPos);
	mLocalDelta.Set(ownerPos);

	mControlState = ControlToken::Create(ControlledType::RandomMove, MakeFunction<>(*this, &BuffModChangeSummonedAI::Move), Unit::ANIM_NAME_IDLE);
	GetOwner()->BeControlled(*mControlState);
}

void BuffModChangeSummonedAI::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mControlState = nullptr;
		mRefTarget.Reset();
		mLocalDelta.Set(Vector3::ZERO);
		return;
	}
	auto& owner = GetOwner();
	owner->DisableMove();  //disable move to sync frontend with logicinstance 
	if (mControlState)
		owner->ClearBeControlled(*mControlState);
	mControlState = nullptr;
	mRefTarget.Reset();
	mLocalDelta.Set(Vector3::ZERO);
}

bool BuffModChangeSummonedAI::Move(int aDeltaTime)
{
	auto& owner = GetOwner();
	auto* summoner = owner->mSummoner;
	if (!summoner || summoner->IsDead())
	{
		return false;
	}

	Vector3 tmp;
	tmp.Set(mLocalDelta);
	summoner->LocalToWorld(tmp);
	auto& curPos = owner->GetPosition();
	if (Abs(curPos.x - tmp.x) + Abs(curPos.z - tmp.z) < 5000)
	{//already in position
		owner->DisableMove();
		owner->SetRot(summoner->GetForward(), true);
		return false;
	}

	mRefTarget.SetPos(tmp);
	owner->Move(mRefTarget, owner, 0, aDeltaTime);
	return false;
}

void BuffModChangeSummonedAI::ResetValues()
{
	BuffMod::ResetValues();
	mControlState = nullptr;
	mRefTarget.Reset();
	mLocalDelta.Set(Vector3::ZERO);
}