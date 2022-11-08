

#include "BuffModNoSuckBlood.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNoSuckBlood::StackAdded(int)
{
    //nothing
}

void BuffModNoSuckBlood::StackRemoved(int)
{
    //nothing
}

void BuffModNoSuckBlood::OnEnable()
{
	auto owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::NoSuckBlood);
}

void BuffModNoSuckBlood::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::NoSuckBlood);
}

int64 BuffModNoSuckBlood::GetPercent()
{
	return mCurPercent;
}