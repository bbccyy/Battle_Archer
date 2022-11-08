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
* @brief （嘲讽），强制选择带有指定id的buff的单位为目标
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModTaunt : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mBuffId;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};