

#pragma once
#include "Buff/BuffMod.h"
#include "Skill/SkillDefine.h"

class BuffModRageImmunity : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		int mType = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};