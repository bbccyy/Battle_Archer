

#include "BuffModChangeCastRange.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModChangeCastRange::StackAdded(int)
{
    //nothing
}

void BuffModChangeCastRange::StackRemoved(int)
{
    //nothing
}

void BuffModChangeCastRange::OnEnable()
{
	GetOwner()->mExtraCastRange = mParams.mRange;
}

void BuffModChangeCastRange::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		mParams.mRange = 0;
		return;
	}
	GetOwner()->mExtraCastRange = 0;
}