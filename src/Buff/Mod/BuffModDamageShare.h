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
* @brief ÉËº¦·Öµ£
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModDamageShare : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mPercent;
        SharedPtr<Unit> mUtilizer;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    int64 OnActive(int64, vector<BuffMod*>&, Unit*);
};