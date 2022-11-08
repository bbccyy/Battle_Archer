

#include "BuffModRangeEffect.h"
#include "BattleInstance.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "BuffModCommonTool.h"

bool BuffModRangeEffect::addVisited(int aEntityId)
{
	for (int eid : mVisitList)
	{
		if (eid == aEntityId)
			return false;
	}
	mVisitList.emplace_back(aEntityId);
	return true;
}

void BuffModRangeEffect::removeVisited(int aEntityId)
{
	int p = mVisitList.size();
	for (int idx = 0; idx < p; )
	{
		if (mVisitList[idx] == aEntityId)
		{
			p--;
			mVisitList[idx] = mVisitList[p];
		}
		else
		{
			idx++;
		}
	}
	mVisitList.resize(p);
}

void BuffModRangeEffect::SetRecord(int aEntityId, int aTime)
{
	for (auto& pair : mRecorder)
	{
		if (pair.first == aEntityId)
		{
			pair.second = aTime;
			return;
		}
	}
	mRecorder.push_back(pair<int, int>(aEntityId, aTime));
	return;
}

int BuffModRangeEffect::GetRecord(int aEntityId)
{
	for (auto& pair : mRecorder)
	{
		if (pair.first == aEntityId)
		{
			if (pair.second < 0)
				return 0;
			else
				return pair.second;	
		}
	}
	return 0; 
}

void BuffModRangeEffect::CleanRecord(vector<SharedPtr<Unit>>& aWatchList)
{
	BattleInstance& battleInstance = GetOwner()->GetBattleInstance();
	for (auto& pair : mRecorder) //GetUnitByEntityId
	{
		if (pair.second >= 0)
		{
			bool exist = false;
			for (auto& unit : aWatchList)
			{
				int entityId = static_cast<int>(unit->GetEntityId());
				if (pair.first == entityId)
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				pair.second = -1;
				if (mParams.removeWhenOutOfRange)
				{
					removeVisited(pair.first);  //will trigger range effect once again entering this area 
					const auto& target = battleInstance.GetUnitByEntityId(pair.first);
					if (target)
						target->RemoveBuff(mParams.BuffId, 0);
				}
			}
		}
	}
}

void BuffModRangeEffect::GetUnitArrByRelation(vector<SharedPtr<Unit>>& aWatchList)
{
	const SharedPtr<Unit>& utilizer = GetOwner();
	BattleInstance& battleInstance = utilizer->GetBattleInstance();
	const vector<SharedPtr<Unit> >* arr;
	switch (mParams.TargetType)
	{
	case ESearchTargetRelationAll:  
	{
		const vector<SharedPtr<Unit> >* arr2;
		arr = &battleInstance.GetArmy1().GetUnitArr();
		arr2 = &battleInstance.GetArmy2().GetUnitArr();
		aWatchList.reserve(arr->size() + arr2->size());
		FilterUnit(arr, aWatchList, mParams.needSummon, mParams.needDead, utilizer.Get());
		FilterUnit(arr2, aWatchList, mParams.needSummon, mParams.needDead, utilizer.Get());
	}
	break;
	case ESearchTargetRelationEnemy:
	{
		arr = &battleInstance.TargetArmy(*utilizer.Get()).GetUnitArr();
		aWatchList.reserve(arr->size());
		FilterUnit(arr, aWatchList, mParams.needSummon, mParams.needDead, utilizer.Get());
	}
		break;
	case ESearchTargetRelationFriend:
	{
		arr = &utilizer->GetArmy().GetUnitArr();
		aWatchList.reserve(arr->size());
		FilterUnit(arr, aWatchList, mParams.needSummon, mParams.needDead, utilizer.Get());
	}
		break;
	}
}

bool BuffModRangeEffect::OnUpdate(Timer<BuffModRangeEffect>& aTimer)
{
	//phase #1: get watch list
	mWatchList.clear();
	GetUnitArrByRelation(mWatchList);
	mExclueSelfPtr = nullptr;
	if (mParams.excludeSelf)
	{
		mExclueSelfPtr = GetOwner().Get();
	}
	size_t num = mWatchList.size();
	const SharedPtr<Unit>& utilizer = GetOwner();
	
	bool circle = true;  //TODO: support rectangle and so
	if (circle)
	{
		int64 dist2;
		Vector2 delt;
		for (size_t i = 0; i < num; )
		{
			dist2 = mParams.mRadius + mWatchList[i]->GetSize();
			dist2 = dist2 * dist2;
			delt.x = utilizer->GetPosition().x - mWatchList[i]->GetPosition().x;
			delt.z = utilizer->GetPosition().z - mWatchList[i]->GetPosition().z;
			if (delt.Magnitude2() < dist2 &&  mWatchList[i].Get() != mExclueSelfPtr)
			{
				i++;
			}
			else
			{
				num--;
				mWatchList[i] = mWatchList[num];
			}
		}
		mWatchList.resize(num);
	}
	CleanRecord(mWatchList);  //clean records to those outside of range 
	
	//phase #2: refresh tick time & try send buff

	for (int i = 0; i < mWatchList.size(); i++)
	{
		auto& unit = mWatchList[i];
		uint32 entityId = unit->GetEntityId();
		int duration = GetRecord(static_cast<int>(entityId));
		if (addVisited(entityId))
		{ //not visited yet
			if (duration >= mParams.TimeBeforeEffect)
			{
				SetRecord(static_cast<int>(entityId), 0); //reset duration
				//notice: the following code may cause Disable mod effection 
				unit->TryReceiveBuff(utilizer, GetSourceUtilizer(), mParams.BuffId, GetBuff()->GetLevel(), GetBuff()->mAncestorSkill);
			}
			else
			{
				SetRecord(static_cast<int>(entityId), duration + 3000);
			}
		}
	}

	if (mWatchList.empty())  //this buff mod has been cancelled due to 'TryReceiveBuff'
		return true;

	//phase #3: loop till end of buff 
	if (aTimer.IsValid())
		aTimer.Reset(GetOwner()->GetUnitTime() + 3000);
	else
		LOG_WARN("found invalid timer in BuffModRangeEffect, owner=%d, isDead=%b, buffId=%d", 
			GetOwner()->GetTplId(), GetOwner()->IsDead(), GetBuff()->GetId());
	return true;
}

void BuffModRangeEffect::StackAdded(int)
{
	//nothing
}

void BuffModRangeEffect::StackRemoved(int)
{
	//nothing
}

void BuffModRangeEffect::OnEnable()
{
	auto& unit = GetOwner();
	mTimer = SharedPool<Timer<BuffModRangeEffect> >::Get();
	mTimer->Execute(unit->GetTimerMgr(), this, &BuffModRangeEffect::OnUpdate, 0);
}

void BuffModRangeEffect::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	mRecorder.clear();
	mWatchList.clear();
	mVisitList.clear();
	mExclueSelfPtr = nullptr;

}