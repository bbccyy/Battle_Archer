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
* @brief （拥有该buff的单位表示，其只能成为填写的这些ID的己方英雄的技能目标
*
**/

#pragma once
#include <vector>
#include "Buff/BuffMod.h"

using namespace std;

class BuffModSpecifyBeTargetSkill : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		vector<int> mSpecifyBeTargetSkills;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};