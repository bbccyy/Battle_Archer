

#pragma once
#include "Buff/BuffMod.h"

class BuffModAdjustBuffHitRate : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int64 mPercent = 0;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	int64 OnActive();
private:
	int64 mTotalRate;
};