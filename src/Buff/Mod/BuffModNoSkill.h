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
* @brief 不能释放技能
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModNoSkill : public BuffMod
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