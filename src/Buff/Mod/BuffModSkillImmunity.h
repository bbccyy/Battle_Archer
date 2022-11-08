/**********************************************************************************************************************
*
* Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author $Author$
* @date $Date$
* @version $Revision$
* @brief ÃâÒß¼¼ÄÜ
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Skill/SkillDefine.h"

class BuffModSkillImmunity : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		vector<ESkillSubType> mBySkillType;
        vector<int> mTargetSkillId;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
};