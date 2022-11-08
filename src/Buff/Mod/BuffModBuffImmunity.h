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
* @brief £¨Çå³ý²¢£©ÃâÒßBuff
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

class BuffModBuffImmunity : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        BuffDispelTarget mTargetType;
		vector<BuffType> mByMainType;
		vector<BuffSubType> mBySubType;
        vector<int> mById;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};