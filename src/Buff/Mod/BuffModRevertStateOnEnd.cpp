

#include "BuffModRevertStateOnEnd.h" 
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModRevertStateOnEnd::StackAdded(int)
{
    //nothing
}

void BuffModRevertStateOnEnd::StackRemoved(int)
{
    //nothing
}

void BuffModRevertStateOnEnd::OnEnable()
{
	auto& owner = GetOwner();
	mHp = owner->GetHp();
	mRage = owner->GetRage();
}

void BuffModRevertStateOnEnd::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		return;
	}
	auto& owner = GetOwner();
	int64 curHp = owner->GetHp();
	int32 curRage = owner->GetRage();
	int64 nextHp = mHp * mParams.mHpPercent / DENOM;
	int32 nextRage = mRage * mParams.mRagePercent / DENOM;
	if (nextHp > curHp)
	{
		int64 realHeal = nextHp - curHp;
		realHeal += realHeal * (owner->GetAttr(EAttribute::HealPercentAdd) + owner->GetAttr(EAttribute::BeHealPercentAdd)) / DENOM;
		if (realHeal > 0)
			owner->HealByStealHp(realHeal, nullptr, GetBuff());
	}
	if (nextRage > curRage)
	{
		owner->AddRage(nextRage - curRage, ERageChangeCause::Buff);
	}
}