

#include "BuffModNoRageRecover.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNoRageRecover::StackAdded(int)
{
	//nothing
}

void BuffModNoRageRecover::StackRemoved(int)
{
	//nothing
}

void BuffModNoRageRecover::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::NoRageRecover);
}

void BuffModNoRageRecover::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::NoRageRecover);
}