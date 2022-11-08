

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

class BuffModResetBuffTime : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		SharedPtr<vector<int>> mBuffIdArr;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};