
#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"
#include "Framework/FunctionContainer.h"

class Skill;
struct BattleEvent;

class BuffModRemoveDefPoint : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int32 mSkillId;
		SharedPtr<Skill> mSkill;
		bool mTriggered;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	void TryTriggerMod(const BattleEvent&);
	bool RegisterListener();
	bool UnRegisterListener() override;
private:
	int mEventKey = 0;
	const IFunctionContainer<void, const BattleEvent&>* mFunc = nullptr;
};