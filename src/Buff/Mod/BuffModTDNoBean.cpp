

#include "BuffModTDNoBean.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModTDNoBean::StackAdded(int)
{
    //nothing
}

void BuffModTDNoBean::StackRemoved(int)
{
    //nothing
}

void BuffModTDNoBean::OnEnable()
{
    auto& owner = GetOwner();
	owner->ReturnBean();
	owner->IncStateAdjust(StateAdjust::TDBeanImmunity);
}

void BuffModTDNoBean::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::TDBeanImmunity);
}