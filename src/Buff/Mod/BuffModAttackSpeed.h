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
* @brief ¸Ä±ä¹¥ËÙ
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModAttackSpeed : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mPercent;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};