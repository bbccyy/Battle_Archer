
#pragma once
#include "Buff/BuffMod.h"
#include "Skill/SkillDefine.h"

class BuffModMoveControlImmunity : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		uint32 mEnergyLevel = 1;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	uint32 GetEnergyLevel();
};