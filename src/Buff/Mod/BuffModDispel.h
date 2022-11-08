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
* @brief ÒÆ³ýbuff
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

class BuffModDispel : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mPartialClearCount;//0=clear all stack
        BuffDispelTarget mTargetType;
		vector<BuffType> mByMainType;
		vector<BuffSubType> mBySubType;
        vector<int> mById;
		int mCleanLevel = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
	void OnReset() override;
    void SendEvent(bool);
};