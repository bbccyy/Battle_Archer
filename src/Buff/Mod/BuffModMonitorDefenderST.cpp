

#include "BuffModMonitorDefenderST.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"

void BuffModMonitorDefenderST::StackAdded(int)
{
    //nothing
}

void BuffModMonitorDefenderST::StackRemoved(int)
{
    //nothing
}

void BuffModMonitorDefenderST::OnEnable()
{
	auto& owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::MoveControlImmunity);
	mIsPlat = owner->TDIsOnPlat();
	RegisterListener();
}

void BuffModMonitorDefenderST::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mIsPlat = false;
		mEventKey = 0;
		TryRecycleFunction(mFunc);
		return;
	}
	if (!mFunc)
		return;
	if(mIsPlat)
		GetOwner()->DecStateAdjust(StateAdjust::MoveControlImmunity);
	UnRegisterListener();
	mEventKey = 0;
}

bool BuffModMonitorDefenderST::RegisterListener()
{
	mEventKey = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterHitHandlerMoveAnyWay));
	if (!mFunc)
	{
		mFunc = MakeFunction<>(*this, &BuffModMonitorDefenderST::TryTriggerMod, false);
	}
	auto& battleInstance = GetOwner()->GetBattleInstance();
	battleInstance.AddListener(mEventKey, mFunc);
	return true;
}

bool BuffModMonitorDefenderST::UnRegisterListener()
{
	if (mFunc && GetBuff() && GetOwner())
	{
		auto& battleInstance = GetOwner()->GetBattleInstance();
		battleInstance.RemoveListener(mEventKey, mFunc);
	}
	return true;
}

void BuffModMonitorDefenderST::TryTriggerMod(const BattleEvent& aEvent)
{
	auto& owner = GetOwner();
	// check if match relation 
	// need self: event should send be-moved-target's entity Id
	if (owner->GetEntityId() != aEvent.mEntityId) return;

	//Check current position(in or out platform)
	//If state changes:
	//Set owner new speed accordingly
	//Retrive all beans
	//Set State Immunity accordingly 
	bool curIsPlat = owner->TDIsOnPlat();
	if (mIsPlat == curIsPlat)
	{ //no state changes, so remain the same
		return;
	}
	mIsPlat = curIsPlat;
	if (curIsPlat)
	{
		owner->TDChangeStateTo(EActiveBaseType::Distance);
		owner->IncStateAdjust(StateAdjust::MoveControlImmunity);
	}
	else
	{
		owner->TDChangeStateTo(EActiveBaseType::Melee);
		owner->DecStateAdjust(StateAdjust::MoveControlImmunity);
	}
}