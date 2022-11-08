
#pragma once
#include "Buff/BuffMod.h"
#include "Skill/SkillDefine.h"

class Skill;

class BuffModSkillOnHp : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mSkillId = 0;
		SharedPtr<Skill> mSkill = nullptr;
		int mSourceType = 0;
		EBuffTriggerSkillHpType mHpType = EBuffTriggerSkillHpType::ETriggerSkillHpTypeFixValue;
		int64 mLifeValue = 0;
		SharedPtr<BuffModSkillOnHpEntry> mEntry = nullptr;

	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};