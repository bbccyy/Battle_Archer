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
* @brief ÎüÑª
*
**/

#pragma once
#include "Buff/BuffMod.h"

enum class StealLifeType
{
    ByDamagePercent = 0,
    ByCurrentHpPercent = 1,
    ByMaxHpPercent = 2,
	ByRecordDataPercent = 3
};

enum class StealMoment
{
	OnActive = 0,
	OnDisable = 1
};

class BuffModStealHp : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        StealLifeType mType = StealLifeType::ByDamagePercent;
		StealMoment mMoment = StealMoment::OnActive;
		SharedPtr<vector<BuffSubType>> mFilterList = nullptr;
		int64 mPercent = 0;;
        int64 mAdd = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void OnActive(Unit&, Unit&, int64 aDamage, int64 aHp, int64 aMaxHp, int64 aPercent = 10000);
	bool Filter(Unit&);
};