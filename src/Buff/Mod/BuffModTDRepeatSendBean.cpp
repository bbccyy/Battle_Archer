

#include "BuffModTDRepeatSendBean.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"

enum class EValueType
{
	FixValue = 0,
	PhysicalAtk = 1
};

void BuffModTDRepeatSendBean::StackAdded(int)
{
    //nothing
}

void BuffModTDRepeatSendBean::StackRemoved(int)
{
    //nothing
}

void BuffModTDRepeatSendBean::OnEnable()
{
    auto& unit = GetOwner();
    mTimer = SharedPool<Timer<BuffModTDRepeatSendBean> >::Get();
	mTimer->Execute(unit->GetTimerMgr(), this, &BuffModTDRepeatSendBean::CheckInRange, 0);
}

void BuffModTDRepeatSendBean::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
}

bool BuffModTDRepeatSendBean::CheckInRange(Timer<BuffModTDRepeatSendBean>& aTimer)
{
	if (!IsValid())
		return false;

	auto& owner = GetOwner();
	owner->TrySendBeanInRange();

    if(IsValid())
    {
        aTimer.Reset(GetOwner()->GetUnitTime() + CONF_TIME_CONVERT(300));  //Delta time = 1s 
        return true;
    }
    return false;
}