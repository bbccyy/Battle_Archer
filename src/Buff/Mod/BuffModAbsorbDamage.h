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
* @brief ÎüÊÕÉËº¦
*
**/

#pragma once
#include "Buff/BuffMod.h"

enum class BuffAbsorbDamageValueType
{
	FixValue = 0,
	ByAttribute = 1
};

enum class ShieldType;

class BuffModAbsorbDamage : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int64 mAbsorbLimit = 0;
        bool mAbsorbHeal = false;
        int mHealPercent = 0;
		ShieldType mType;
		int mCount = 0;
		int mThreshold = 0;
    } mParams;
public:
    int64 mAbsorbLimit = 0;
	int mAbsorbCount = 0;
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void ResetValues() override;
    int64 OnActive(int64, bool, int, int);
    void TryHeal(int64);
	void AddValues(int64);
	bool IsCounterShield();
};