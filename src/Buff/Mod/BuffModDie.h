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
* @brief 持续时间结束时持有者死亡
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModDie : public BuffMod
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
};