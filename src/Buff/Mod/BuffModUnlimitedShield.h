

#pragma once
#include "Buff/BuffMod.h"

class BuffModUnlimitedShield : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mPeriod = 0;
		int mPercent = 0;
	} mParams;
public:
	int mCount = 0;
	SharedPtr<Timer<BuffModUnlimitedShield>> mTimer = nullptr;
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	int64 OnActive(int64, bool);
	bool OnReset(Timer<BuffModUnlimitedShield>&);
};