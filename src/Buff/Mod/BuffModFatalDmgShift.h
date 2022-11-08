

#pragma once
#include "Buff/BuffMod.h"


class BuffModFatalDmgShift : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mCount = 0;
		int mCD = 0;
		int mTargetType = 0;
	}mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	int64 OnActive(SharedPtr<Unit> aFriend, int64 aDmg);
	bool IsUsedUp();
	int GetTargetType();
	bool IsInCD();

private:
	int mLastActiveTime = 0;
};