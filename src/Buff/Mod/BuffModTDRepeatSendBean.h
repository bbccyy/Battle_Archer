

#pragma once
#include "Buff/BuffMod.h"

class Skill;

class BuffModTDRepeatSendBean : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
private:
    SharedPtr<Timer<BuffModTDRepeatSendBean> > mTimer = nullptr;
    bool CheckInRange(Timer<BuffModTDRepeatSendBean>&);
};