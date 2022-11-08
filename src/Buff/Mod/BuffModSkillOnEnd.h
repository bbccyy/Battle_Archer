﻿/**********************************************************************************************************************
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
* @brief 持续时间结束时释放某技能
*
**/

#pragma once
#include "Buff/BuffMod.h"

class Skill;
enum class EBuffDisableType;

class BuffModSkillOnEnd : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mSkillId = 0;
		int mSkillIdBack= 0;
        SharedPtr<Skill> mSkill = nullptr;
		SharedPtr<Skill> mSkillBack = nullptr;
		int mSourceType = 0;
		EBuffDisableType mDisableType;
		bool mIgnoreNoSkill = false;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};