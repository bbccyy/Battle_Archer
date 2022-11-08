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
* @brief ¸Ä±äÊôÐÔ
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Entity/UnitDefine.h"

class BuffModProperty : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        vector<BuffModPropertyEntry> mEntries;
        int64 mMaxHpPercent;
        int64 mMaxHpAdd;
        int64 mHpChangePercent;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
private:
    int64 mMaxHpChange = 0;
    int64 mHpChange = 0;
    int64 mHpDiff = 0;
    void ApplyStacked(bool);
    void RevertValue();
};