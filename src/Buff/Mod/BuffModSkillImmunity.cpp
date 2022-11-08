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
* @brief
*
**/

#include "BuffModSkillImmunity.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModSkillImmunity::StackAdded(int)
{
    //nothing
}

void BuffModSkillImmunity::StackRemoved(int)
{
    //nothing
}

void BuffModSkillImmunity::OnEnable()
{
    if (mParams.mTargetSkillId.size() > 0)
    {
        GetOwner()->SkillImmunity(mParams.mTargetSkillId);
    }
    else
    {
        GetOwner()->SkillImmunityByType(mParams.mBySkillType);
    }
}

void BuffModSkillImmunity::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mTargetSkillId.clear();
		mParams.mBySkillType.clear();
		return;
	}
    if (mParams.mTargetSkillId.size() > 0)
    {
        GetOwner()->RevokeSkillImmunity(mParams.mTargetSkillId);
    }
    else
    {
        GetOwner()->RevokeSkillImmunityByType(mParams.mBySkillType);
    }
	mParams.mTargetSkillId.clear();
	mParams.mBySkillType.clear();
}