

#include "BuffModTDRepeatCheckBean.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"


void BuffModTDRepeatCheckBean::StackAdded(int)
{
    //nothing
}

void BuffModTDRepeatCheckBean::StackRemoved(int)
{
    //nothing
}

void BuffModTDRepeatCheckBean::OnEnable()
{
    auto& unit = GetOwner();
    mTimer = SharedPool<Timer<BuffModTDRepeatCheckBean> >::Get();
	mTimer->Execute(unit->GetTimerMgr(), this, &BuffModTDRepeatCheckBean::CheckInRange, 0);
}

void BuffModTDRepeatCheckBean::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mType = 0;
		return;
	}
}

bool BuffModTDRepeatCheckBean::CheckInRange(Timer<BuffModTDRepeatCheckBean>& aTimer)
{
	if (!IsValid())
		return false;

	auto& owner = GetOwner();

	if (mParams.mType == 0)
	{  //周期性检测是否在区域内，出圈则归还豆子 
		if (owner->mMarkedBean && !owner->TDIsEnemyInActiveRange())
		{ //has bean, but not in Zone, so return it! 
			owner->ReturnBean();
		}

		if (IsValid())
		{
			aTimer.Reset(GetOwner()->GetUnitTime() + CONF_TIME_CONVERT(300));  //Delta time = 1s 
			return true;
		}
	}
	else
	{  //抵近目标一定距离后替换AI 
		if (!owner->mMarkedBean)
		{
			LOG_WARN("owner %d BuffModTDRepeatCheckBean mType == 1, but has no markedBean!", owner->GetEntityId());
			return false;
		}
		if (owner->mMarkedBean->mOwner->mCurrentBase->mType == EActiveBaseType::Distance)
		{ //豆子拥有者当前站在远程位置，不停靠 
			return false;
		}
		int64 myX = owner->GetPosition().x;
		int64 myZ = owner->GetPosition().z;
		int64 tarX = owner->mMarkedBean->mOwner->GetPosition().x;
		int64 tarZ = owner->mMarkedBean->mOwner->GetPosition().z;
		if (Abs(myX - tarX) <= BattleInstance::TDMinX || Abs(myZ - tarZ) <= BattleInstance::TDMinX)
		{
			owner->OnBeanStateChanged(BeanState::AnyToNone);
			owner->OnBeanStateChanged(BeanState::NoneToMelee);
			return false;
		}
		if (IsValid())
		{
			aTimer.Reset(GetOwner()->GetUnitTime() + CONF_TIME_CONVERT(300));   
			return true;
		}
	}
	return false;
}