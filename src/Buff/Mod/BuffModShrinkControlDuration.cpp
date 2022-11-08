

#include "BuffModShrinkControlDuration.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModShrinkControlDuration::StackAdded(int)
{
	//nothing
}

void BuffModShrinkControlDuration::StackRemoved(int)
{
	//nothing
}

void BuffModShrinkControlDuration::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::ShrinkControlDuration);
}

uint32 BuffModShrinkControlDuration::GetShrinkRate()
{
	return mParams.mShrinkRate;
}

void BuffModShrinkControlDuration::OnDisable(bool aShouldTrigger)
{
	GetOwner()->DecStateAdjust(StateAdjust::ShrinkControlDuration);
}