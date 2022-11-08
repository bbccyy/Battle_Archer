

#pragma once
#include "Buff/BuffMod.h"

class BuffModReflectBuff : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mCD = 0;
		vector<BuffSubType> mReflectable;
	}mParams;
public:
	int mLastActiveTime = 0;
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	bool OnActive(int);
};