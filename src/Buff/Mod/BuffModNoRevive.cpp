

#include "BuffModNoRevive.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNoRevive::StackAdded(int)
{
    //nothing
}

void BuffModNoRevive::StackRemoved(int)
{
    //nothing
}

void BuffModNoRevive::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::NoRevive);
}

void BuffModNoRevive::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		return;
	}
	//should not retrive no revive! 
}