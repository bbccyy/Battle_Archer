

#pragma once
#include "Buff/BuffMod.h"

class BuffModConditionChange : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int mMainType = 0;
		int mRelation = 0;
		int mTarget = 0;
		int64 mAdd = 0;
		vector<int> mParamArr;
	} mParams;
public:
	int64 mAddData = 0;
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};