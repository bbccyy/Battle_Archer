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
* @brief ÉËº¦¸´ÖÆ
*
**/

#pragma once
#include "Buff/BuffMod.h"

class BuffModDamageCopy : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mPercent = 0;
		bool mIgnoreSelf = false;
        SharedPtr<Unit> mUtilizer = nullptr;
		int mSourceUtilizerId = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void OnActive(int64, int);
	int GetSourceUtilizerId();
};