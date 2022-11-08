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
* @brief 不能被选为目标（参考目标，生效目标）
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModNonTargettable : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        vector<int64> mWhiteList; 
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    bool InWhiteList(int64 aSkillId);
};