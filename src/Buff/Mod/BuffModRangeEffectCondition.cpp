
#include "BuffModRangeEffectCondition.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "BattleInstance.h"
#include "BuffModCommonTool.h"


void BuffModRangeEffectCondition::ApplyStacked()
{
	auto& owner = GetOwner();

	for (auto& entry : mParams.mProperty)
	{
		entry.mValue = GetBuff()->ScaledValue(owner->GetAttr(entry.mProperty) * entry.mPercent / DENOM + entry.mAdd);
		if (entry.mValue < 0 && owner->IsImmuePropertyDec(entry.mProperty))
		{
			//block dec value modification 
			entry.mValue = 0;
		}
	}
	owner->ModifyAttr(mParams.mProperty, true, GetBuff()->GetId());
}

void BuffModRangeEffectCondition::ApplyStackedWithNum(int aNum)
{
	auto& owner = GetOwner();

	for (auto& entry : mParams.mProperty)
	{
		entry.mValue = GetBuff()->ScaledValue(owner->GetAttr(entry.mProperty) * entry.mPercent / DENOM + aNum * entry.mAdd);
		if (entry.mValue < 0 && owner->IsImmuePropertyDec(entry.mProperty))
		{
			//block dec value modification 
			entry.mValue = 0;
		}
	}
	owner->ModifyAttr(mParams.mProperty, true, GetBuff()->GetId());
}

void BuffModRangeEffectCondition::RevertValue()
{
	GetOwner()->RevertAttr(mParams.mProperty);
}

void BuffModRangeEffectCondition::OnEnable()
{
	auto& unit = GetOwner();
	mTimer = SharedPool<Timer<BuffModRangeEffectCondition> >::Get();
	mTimer->Execute(unit->GetTimerMgr(), this, &BuffModRangeEffectCondition::OnUpdate, 0);
}

bool BuffModRangeEffectCondition::OnUpdate(Timer<BuffModRangeEffectCondition>& aTimer)
{
	switch (mParams.mCondition)
	{
	case ERangeEffectConditionType::EHasAnemyInRange:
	case ERangeEffectConditionType::EHasAnyInRange:
	case ERangeEffectConditionType::EHasFriendInRange:
		{
			if (HasHeroInRange() > 0)
			{
				RevertValue();
				ApplyStacked();
			}
		}
		break;
	case ERangeEffectConditionType::EHasEnemyInRangeNum:
		{
			int num = HasHeroInRange();
			if (num > 0)
			{
				RevertValue();
				ApplyStackedWithNum(num);
			}
		}
		break;
	default:
		break;
	}

	if (aTimer.IsValid())
		aTimer.Reset(GetOwner()->GetUnitTime() + 3000);
	else
		LOG_WARN("found invalid timer in BuffModRangeEffectCondition, owner=%d, isDead=%b, buffId=%d",
			GetOwner()->GetTplId(), GetOwner()->IsDead(), GetBuff()->GetId());
	return true;
}

int BuffModRangeEffectCondition::HasHeroInRange()
{
	mWatchList.clear();
	GetUnitArrByRelation(mWatchList);
	if (mWatchList.empty()) return false;
	int64 dist2;
	Vector2 delt;
	size_t num = mWatchList.size();
	const SharedPtr<Unit>& utilizer = GetOwner();
	Unit * exclueSelfPtr = utilizer.Get();
	for (size_t i = 0; i < num; )
	{
		dist2 = mParams.mRadius + mWatchList[i]->GetSize();
		dist2 = dist2 * dist2;
		delt.x = utilizer->GetPosition().x - mWatchList[i]->GetPosition().x;
		delt.z = utilizer->GetPosition().z - mWatchList[i]->GetPosition().z;
		if (delt.Magnitude2() < dist2 &&  mWatchList[i].Get() != exclueSelfPtr)
		{
			i++;
			return i;
		}
		else
		{
			num--;
			mWatchList[i] = mWatchList[num];
		}
	}
	mWatchList.resize(num);
	return num;
}

void BuffModRangeEffectCondition::GetUnitArrByRelation(vector<SharedPtr<Unit>>& aWatchList)
{
	const SharedPtr<Unit>& utilizer = GetOwner();
	BattleInstance& battleInstance = utilizer->GetBattleInstance();
	const vector<SharedPtr<Unit> >* arr;
	switch (mParams.mCondition)
	{
	case EHasAnyInRange:
	{
		const vector<SharedPtr<Unit> >* arr2;
		arr = &battleInstance.GetArmy1().GetUnitArr();
		arr2 = &battleInstance.GetArmy2().GetUnitArr();
		aWatchList.reserve(arr->size() + arr2->size());
		FilterUnit(arr, aWatchList, ENeedSummon::EOnlyHero, false, utilizer.Get());
		FilterUnit(arr2, aWatchList, ENeedSummon::EOnlyHero, false, utilizer.Get());
	}
	break;
	case EHasAnemyInRange:
	case EHasEnemyInRangeNum:
	{
		arr = &battleInstance.TargetArmy(*utilizer.Get()).GetUnitArr();
		aWatchList.reserve(arr->size());
		FilterUnit(arr, aWatchList, ENeedSummon::EOnlyHero, false, utilizer.Get());
	}
	break;
	case EHasFriendInRange:
	{
		arr = &utilizer->GetArmy().GetUnitArr();
		aWatchList.reserve(arr->size());
		FilterUnit(arr, aWatchList, ENeedSummon::EOnlyHero, false, utilizer.Get());
	}
	break;
	}
}

void BuffModRangeEffectCondition::StackAdded(int)
{
	//RevertValue();
	//ApplyStacked();
}

void BuffModRangeEffectCondition::StackRemoved(int)
{
	//RevertValue();
	//ApplyStacked();
}

void BuffModRangeEffectCondition::OnDisable(bool aShouldTrigger)
{
	mWatchList.clear();
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	RevertValue();
	mParams.mProperty.clear();
}