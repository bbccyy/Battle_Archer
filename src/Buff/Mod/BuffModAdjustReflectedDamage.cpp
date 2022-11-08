

#include "BuffModAdjustReflectedDamage.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModAdjustReflectedDamage::OnEnable()
{
	auto& owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::AdjustReflectedDmg);
}

void BuffModAdjustReflectedDamage::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mPercent = 0;
		return;
	}
	auto& owner = GetOwner();
	owner->DecStateAdjust(StateAdjust::AdjustReflectedDmg);
}

void BuffModAdjustReflectedDamage::StackAdded(int const aChange)
{
	//do nothing
}

void BuffModAdjustReflectedDamage::StackRemoved(int const aChange)
{
	//do nothing
}

int64 BuffModAdjustReflectedDamage::OnActive(int64 aValue, bool aIsPhysical)
{
	if (!IsValid() || aValue == 0)
		return aValue;

	int64 curPercent = GetBuff()->ScaledValue(mParams.mPercent);
	curPercent = DENOM - curPercent;
	if (curPercent < 1000) curPercent = 1000;

	return aValue * curPercent / DENOM;
}
