
#include "BuffModDecDmgByBuffSub.h"
#include "Entity/Unit.h"

void BuffModDecDmgByBuffSub::StackAdded(int)
{
	//nothing
}

void BuffModDecDmgByBuffSub::StackRemoved(int)
{
	//nothing
}

void BuffModDecDmgByBuffSub::OnEnable()
{
	for (auto& data : mParams.mArr)
	{
		GetOwner()->InvokeBuffModifyDamage(data);
	}
}

void BuffModDecDmgByBuffSub::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mArr.clear();
		return;
	}
	for (auto& data : mParams.mArr)
	{
		GetOwner()->RevokeBuffModifyDamage(data);
	}
}