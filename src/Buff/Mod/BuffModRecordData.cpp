

#include "BuffModRecordData.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"

void BuffModRecordData::StackAdded(int)
{
	//nothing
}

void BuffModRecordData::StackRemoved(int)
{
	//nothing
}

void BuffModRecordData::OnEnable()
{
	RegisterListener();
}

void BuffModRecordData::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mEventKey = 0;
		TryRecycleFunction(mFunc);
		return;
	}
	if (!mFunc)
		return;
	UnRegisterListener();
	mEventKey = 0;
}

bool BuffModRecordData::RegisterListener()
{
	mEventKey = BattleInstance::GenerateEventKey(static_cast<int>(mParams.mMajor), mParams.mSub);
	if (mEventKey < static_cast<int>(ETriggerMajor::Enter))
	{
		return false;
	}
	if (!mFunc)
	{
		mFunc = MakeFunction<>(*this, &BuffModRecordData::TryTriggerMod, false);
	}
	auto& battleInstance = GetOwner()->GetBattleInstance();
	battleInstance.AddListener(mEventKey, mFunc);
	return true;
}

bool BuffModRecordData::UnRegisterListener()
{
	if (mFunc && GetBuff() && GetOwner())
	{
		auto& battleInstance = GetOwner()->GetBattleInstance();
		battleInstance.RemoveListener(mEventKey, mFunc);
	}
	return true;
}

void BuffModRecordData::TryTriggerMod(const BattleEvent& aEvent)
{
	auto& owner = GetOwner();
	// check if match relation 
	switch (mParams.mBody)
	{
	case ETriggerRelation::Self:
		if (owner->GetEntityId() != aEvent.mEntityId) return;
		break;
	case ETriggerRelation::Friend:
		if (owner->IsEnemy(aEvent.mArmyId)) return;
		break;
	case ETriggerRelation::Enemy:
		if (!owner->IsEnemy(aEvent.mArmyId)) return;
		break;
	case ETriggerRelation::Any:
		break;
	default:
		return;
	}

	// handle logic
	int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::WhenMatchRecordValue));
	switch (mParams.mMajor)
	{
	case ETriggerMajor::AfterDmg:
	{
		switch (mParams.mDataType)
		{
		case EBuffRecordDataType::Damage:
		{
			GetBuff()->AddRecordData(aEvent.mRegister2);
			//auto sendData = GetBuff()->GetRecordData();
			//owner->GetBattleInstance().DispatchEvent(key, owner->GetArmyId(), owner->GetEntityId(), GetBuff()->GetId(), sendData);
		}
		break;
		default:
			LOG_WARN("AfterDmg: buff[%d] found unexpected RecordDataType = %d", GetBuff()->GetId(), mParams.mDataType);
		}
	}
	break;
	case ETriggerMajor::WhenApplyDamage:
	{ //accumulate total damage made by mBody during lifetime of this buff
		switch (mParams.mDataType)
		{
		case EBuffRecordDataType::Damage:
		{
			GetBuff()->AddRecordData(aEvent.mRegister1);
			//auto sendData = GetBuff()->GetRecordData();
			//owner->GetBattleInstance().DispatchEvent(key, owner->GetArmyId(), owner->GetEntityId(), GetBuff()->GetId(), sendData);
		}
		break;
		case EBuffRecordDataType::DamageToSelfHpRate:
		{
			GetBuff()->AddRecordData(aEvent.mRegister1);
			//auto sendData = GetBuff()->GetRecordData() * DENOM / owner->GetMaxHp();
			//owner->GetBattleInstance().DispatchEvent(key, owner->GetArmyId(), owner->GetEntityId(), GetBuff()->GetId(), sendData);
		}
		break;
		default:
			LOG_WARN("WhenApplyDamage: buff[%d] found unexpected RecordDataType = %d", GetBuff()->GetId(), mParams.mDataType);
		}
	}
	break;
	default:
		LOG_WARN("buff[%d] found unexpected MajorType = %d", GetBuff()->GetId(), mParams.mMajor);
	}
}
