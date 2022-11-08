/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author liyingbo
* @date $Date$
* @version $Revision$
* @brief ¸Ä±äÅ­Æø
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Framework/Timer.h"

class BuffModRage : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mCount;
        int mInterval;
        BuffModHpOrRageType mType;
        vector<int> mPercent;
        vector<int> mAdded;
        int mPhasePercent;
        int mPhaseAdded;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void ResetValues() override;
    bool OnPhase(Timer<BuffModRage>&);
    void OnActive(int);
private:
    SharedPtr<Timer<BuffModRage> > mTimer;
    int mCount = 0;
};