#pragma once
#include "Buff/BuffMod.h"
#include "Entity/UnitDefine.h"

class BuffModChgArcherSkill : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        vector<int> mKeyList;
        vector<int> mValueList;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};