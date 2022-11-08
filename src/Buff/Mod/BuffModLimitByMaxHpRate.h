

#pragma once
#include "Buff/BuffMod.h"


class BuffModLimitByMaxHpRate : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int64 mRate = 0;
	}mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	int64 OnActive(int64 aDmg);
};