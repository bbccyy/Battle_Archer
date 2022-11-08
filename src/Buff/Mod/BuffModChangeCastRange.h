

#pragma once
#include "Buff/BuffMod.h"


class BuffModChangeCastRange : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		int64 mRange = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};