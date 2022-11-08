

#pragma once
#include "Buff/BuffMod.h"


class BuffModRevertStateOnEnd : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		int mHpPercent = 0;
		int mRagePercent = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
private:
	int64 mHp = 0;
	int32 mRage = 0;
};