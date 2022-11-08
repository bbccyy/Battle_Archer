
#include "BuffModSkillOnHp.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"
#include "Skill/SkillExecutor.h"
#include "Buff/Buff.h"

void BuffModSkillOnHp::StackAdded(int)
{
	//nothing
}

void BuffModSkillOnHp::StackRemoved(int)
{
	//nothing
}

void BuffModSkillOnHp::OnEnable()
{
	//add skill to unit
	//set trigger level
	auto entry = SharedPool<BuffModSkillOnHpEntry>::Get();
	mParams.mEntry = entry;
	entry->mHpType = mParams.mHpType;
	entry->mLifeValue = mParams.mLifeValue;
	entry->mSkill = mParams.mSkill;
	const auto& sourceUtilizer = mParams.mSourceType == 1 ? GetSourceUtilizer() : WeakPtr<Unit>();
	entry->mSourcer = sourceUtilizer;  //if source utilizer is nil, will use owner automaticaly 

	auto owner = GetOwner();
	owner->RegisterSkillOnHpEntry(entry.Get());
}

void BuffModSkillOnHp::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mSkill = nullptr;
		mParams.mEntry = nullptr;
		mParams.mSkillId = 0;
		mParams.mSourceType = 0;
		mParams.mLifeValue = 0;
		mParams.mHpType = EBuffTriggerSkillHpType::ETriggerSkillHpTypeFixValue;
		return;
	}
	auto owner = GetOwner();
	if (owner)
		owner->UnregisterSkillOnHpEntry(mParams.mEntry.Get());
}