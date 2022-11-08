

#pragma once
#include "Buff/BuffMod.h"

class BuffModChangeDir : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mArmyId = 0;
		int mBuffId = 0;
		int mType = 0;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};