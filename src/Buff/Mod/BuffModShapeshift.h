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
* @brief ±äÐÎ
*
**/

#pragma once
#include "Buff/BuffMod.h"

enum class ShapeshiftBuffInheritanceRule
{
    AllBuff = 0,
    AllBuffResetTime = 1,
    ClearAll = 2,
    PositiveOnly = 3,
    PositiveOnlyResetTime = 4,
    NegativeOnly = 5,
    NegativeOnlyResetTime = 6
};

struct ShapeShift;

class BuffModShapeshift : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		bool mKeepChainOrder = false;
        int mTplId = 0;
        ShapeshiftBuffInheritanceRule mInheritBuff = ShapeshiftBuffInheritanceRule::AllBuff;
        bool mInheritAttributes = false;
		bool mInheritSkill = false;
        int mInheritLevel = 0;
        int mLevel = 0;
    } mParams;
public:
    int mLastTplId = 0;
    int mLastLevel = 0;
    vector<int64> mLastAttrArr;

	SharedPtr<ShapeShift> mShapeShift = nullptr;

    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};