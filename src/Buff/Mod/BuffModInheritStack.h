

#pragma once
#include "Buff/BuffMod.h"

class BuffModInheritStack : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mBuffId;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};