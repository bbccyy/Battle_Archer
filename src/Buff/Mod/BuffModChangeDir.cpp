


#include "BuffModChangeDir.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "BattleInstance.h"

void BuffModChangeDir::StackAdded(int)
{
	// do nothing
}

void BuffModChangeDir::StackRemoved(int)
{
	// do nothing
}

void BuffModChangeDir::OnEnable()
{
	auto& owner = GetOwner();
	int ownerArmyId = owner->GetArmyId();
	if (mParams.mType == 0)
	{ //Type == 0, ʹ��buffЯ�������߳��� 
		vector<Unit*> list;
		owner->GetBattleInstance().GetAllActiveUnits(list);
		Vector3 pos;
		bool find = false;
		for (auto* u : list)
		{
			if (mParams.mArmyId == 1)
			{ //���� 
				if (u->GetArmyId() == ownerArmyId &&
					u->HasBuff(mParams.mBuffId) &&
					owner->GetEntityId() != u->GetEntityId())
				{
					find = true;
					pos = u->GetPosition();
					break;
				}
			}
			else
			{ //�з� 
				if (u->GetArmyId() != ownerArmyId &&
					u->HasBuff(mParams.mBuffId) &&
					owner->GetEntityId() != u->GetEntityId())
				{
					find = true;
					pos = u->GetPosition();
					break;
				}
			}
		}
		if (find)
		{
			Vector3 dir = pos - owner->GetPosition();
			if (dir != Vector3::ZERO)
				owner->SetRot(dir, true);
		}
	}
	else
	{ //Type == 1, ʹ����������㳯�� 
		const auto& point = owner->GetArmy().GetBornPointByIndex(owner->GetBornPoint());
		owner->SetRot(point.mRot, true);
	}
}

void BuffModChangeDir::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mType = 0;
		mParams.mArmyId = 0;
		mParams.mBuffId = 0;
		return;
	}
}