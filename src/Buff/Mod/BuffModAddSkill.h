

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

class BuffModAddSkill : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int32 mSkillLevel;
		SharedPtr<vector<int>> mSkillIdArr;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};