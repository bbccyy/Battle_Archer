

#include "BuffModAdjustBuffHitRate.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModAdjustBuffHitRate::OnEnable()
{
	auto& owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::AdjustBuffHitRate);
	mTotalRate = mParams.mPercent;
}

void BuffModAdjustBuffHitRate::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	mTotalRate = 0;
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mPercent = 0;
		return;
	}
	auto& owner = GetOwner();
	owner->DecStateAdjust(StateAdjust::AdjustBuffHitRate);
}

void BuffModAdjustBuffHitRate::StackAdded(int const aChange)
{
	mTotalRate += mParams.mPercent * aChange;
}

void BuffModAdjustBuffHitRate::StackRemoved(int const aChange)
{
	mTotalRate -= mParams.mPercent * aChange;
}

int64 BuffModAdjustBuffHitRate::OnActive()
{
	if (!IsValid())
		return 0;
	int64 curPercent = GetBuff()->ScaledValue(mTotalRate);
	return curPercent;
}
