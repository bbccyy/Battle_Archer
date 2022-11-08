
#include "BuffModDisable.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModDisable::StackAdded(int)
{
	//nothing
}

void BuffModDisable::StackRemoved(int)
{
	//nothing
}

void BuffModDisable::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::Disable);
}

void BuffModDisable::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
		return;
	GetOwner()->DecStateAdjust(StateAdjust::Disable);
}