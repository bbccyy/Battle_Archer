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
* @brief ·´Éä¼¼ÄÜ
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Skill/SkillDefine.h"

class Skill;

class BuffModReflectSkill : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mSkillType;
		EDamageChannel mChannelType;
        int mCount;
    } mParams;
public:
    int mCount = 0;
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void ResetValues() override;
    bool OnActive(Unit* aUtilizer, const Skill*);
};