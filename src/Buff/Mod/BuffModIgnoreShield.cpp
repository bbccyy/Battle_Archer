

#include "BuffModIgnoreShield.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModIgnoreShield::StackAdded(int)
{
    //nothing
}

void BuffModIgnoreShield::StackRemoved(int)
{
    //nothing
}

void BuffModIgnoreShield::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::IgnoreShield);
}

void BuffModIgnoreShield::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::IgnoreShield);
}