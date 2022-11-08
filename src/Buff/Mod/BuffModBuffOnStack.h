

#pragma once
#include "Buff/BuffMod.h"

struct BuffOnStack {
	int mStack = 0;
	vector<int> mBuffArr;
};

class BuffModBuffOnStack : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		vector<BuffOnStack> mActionArr;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
	void OnStackNumberChange();
	void CleanAllBuff();
private:
	int mLastStack = 0;
	bool mInProcessing = false;
};