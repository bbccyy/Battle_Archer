

#include "BuffModUnlimitedShield.h"
#include "Entity/Unit.h"
#include "Skill/HitHandler/HitHandler.h"
#include "Buff/Buff.h"

void BuffModUnlimitedShield::OnEnable()
{
	mCount = 1;
	auto& owner = GetOwner();
	owner->IncStateAdjust(StateAdjust::UnlimitedShield);
}

void BuffModUnlimitedShield::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mPercent = 0;
		mParams.mPeriod = 0;
		mCount = 0;
		return;
	}
	mCount = 0;
}

void BuffModUnlimitedShield::StackAdded(int const aChange)
{
	//do nothing
}

void BuffModUnlimitedShield::StackRemoved(int const aChange)
{
	//do nothing
}

bool BuffModUnlimitedShield::OnReset(Timer<BuffModUnlimitedShield>&)
{
	OnEnable();
	return false;
}

int64 BuffModUnlimitedShield::OnActive(int64 aValue, bool aIsPhysical)
{
	if (mCount <= 0 || !IsValid() || aValue == 0)
		return aValue;
	
	auto& owner = GetOwner();
	int64 mMaxHp = owner->GetMaxHp();
	if (aValue < IncByRate(mMaxHp, mParams.mPercent, DENOM))
	{
		return aValue;
	}

	if (!GetBuff()->HasLabelId())
	{
		owner->SendScreenTextCmd(ScreenTextType::DamageImmunityAll);
	}

	mCount = 0;
	aValue = 0;
	owner->DecStateAdjust(StateAdjust::UnlimitedShield);

	if (!mTimer)
		mTimer = SharedPool<Timer<BuffModUnlimitedShield>>::Get();
	mTimer->Execute(owner->GetTimerMgr(), this, &BuffModUnlimitedShield::OnReset, owner->GetUnitTime() + mParams.mPeriod);

	return aValue;
}
