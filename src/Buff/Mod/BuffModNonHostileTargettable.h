/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief 不能被选为地方目标（参考目标，生效目标）
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModNonHostileTargettable : public BuffMod
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