

#pragma once
#include "Buff/BuffMod.h"

class BuffModSetMaxLoseHP : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mPercent = 0;
    } mParams;
public:
    int64 mUndertakeLimit = 0;
	int64 mUndertaked = 0;
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void ResetValues() override;
    int64 OnActive(int64, bool);
};