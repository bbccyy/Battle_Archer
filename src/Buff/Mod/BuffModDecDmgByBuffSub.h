

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

struct ChangeDataByBuffSub;

class BuffModDecDmgByBuffSub : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		vector<ChangeDataByBuffSub> mArr;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};