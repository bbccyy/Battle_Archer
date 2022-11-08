
#include "BuffModPropertyDecImmunity.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModPropertyDecImmunity::StackAdded(int)
{
	//nothing
}

void BuffModPropertyDecImmunity::StackRemoved(int)
{
	//nothing
}

void BuffModPropertyDecImmunity::OnEnable()
{
	auto owner = GetOwner();
	owner->PropertyChangeImmunity(mParams.mAttr);
}

void BuffModPropertyDecImmunity::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	auto owner = GetOwner();
	owner->RevokePropertyChangeImmunity(mParams.mAttr);
}