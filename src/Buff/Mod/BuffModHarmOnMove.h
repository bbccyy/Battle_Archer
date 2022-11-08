
#pragma once
#include "Buff/BuffMod.h"

class Skill;

class BuffModHarmOnMove : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mSkillId = 0;
		SharedPtr<Skill> mSkill = nullptr;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
private:
	int64 mPrePosX = 0;
	int64 mPrePosZ = 0;
	SharedPtr<Timer<BuffModHarmOnMove> > mTimer = nullptr;
	bool ExecuteSkill(Timer<BuffModHarmOnMove>&);
};