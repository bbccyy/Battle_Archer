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
* @brief 底力（持续期间，无论受到多少伤害，hp最小值保持为1）。扩展为锁血，能在持续期间保持一个指定血量值，或者血量百分比
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModToughness : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		int64 mInitHp;
		int64 mLockValue;
		int mLockPercent;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
	int64 OnActive(int64 aCurHp, int64 aMaxHp);
};