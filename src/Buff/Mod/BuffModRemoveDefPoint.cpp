

#include "BuffModRemoveDefPoint.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"
#include "View/BattleViewOutput.h"

void BuffModRemoveDefPoint::StackAdded(int)
{
	//nothing
}

void BuffModRemoveDefPoint::StackRemoved(int)
{
	//nothing
}

void BuffModRemoveDefPoint::OnEnable()
{
	RegisterListener();
}

void BuffModRemoveDefPoint::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mEventKey = 0;
		TryRecycleFunction(mFunc);
		mParams.mSkill = nullptr;
		return;
	}
	if (!mFunc)
		return;
	UnRegisterListener();
	mEventKey = 0;
}

bool BuffModRemoveDefPoint::RegisterListener()
{
	mEventKey = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::AfterInterrupt));
	if (!mFunc)
	{
		mFunc = MakeFunction<>(*this, &BuffModRemoveDefPoint::TryTriggerMod, false);
	}
	auto& battleInstance = GetOwner()->GetBattleInstance();
	battleInstance.AddListener(mEventKey, mFunc);
	return true;
}

bool BuffModRemoveDefPoint::UnRegisterListener()
{
	if (mFunc && mParams.mTriggered == false)
	{
		auto& battleInstance = GetOwner()->GetBattleInstance();
		battleInstance.RemoveListener(mEventKey, mFunc);
	}
	mParams.mTriggered = true;
	return true;
}

void BuffModRemoveDefPoint::TryTriggerMod(const BattleEvent& aEvent)
{
	auto& owner = GetOwner();
	// check if match relation: Self
	if (owner->GetEntityId() != aEvent.mEntityId) return;

	UnRegisterListener();
	if (owner->mDefPointNum <= 0 || owner->mBossDefActive == false)
	{
		LOG_WARN("invalid register RemoveDefPoint Event Listener, owner's def point = %d, active = %b", owner->mDefPointNum, owner->mBossDefActive);
		return;
	}

	owner->mDefPointNum = owner->mDefPointNum - 1;
	if (owner->mDefPointNum <= 0)
	{
		owner->mBossDefActive = false;
		owner->mDefType = -1;
		owner->mDefPointNum = 0;
	}
	owner->GetView()->Execute(ViewCommand::DelDefendPoint, owner->GetEntityId(), 1, static_cast<int>(owner->mBossDefActive));

	// handle logic
	if (owner->mBossDefActive == false && mParams.mSkillId > 0 && mParams.mSkill->CanExecute() == CheckResult::Pass)
	{
		if (mParams.mSkill->RefreshRefTarget())
			GetOwner()->ExecuteSkill(mParams.mSkill, 0, nullptr, GetSourceUtilizer()); 
	}
}