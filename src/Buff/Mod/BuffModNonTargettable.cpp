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

#include "BuffModNonTargettable.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModNonTargettable::StackAdded(int)
{
    //nothing
}

void BuffModNonTargettable::StackRemoved(int)
{
    //nothing
}

void BuffModNonTargettable::OnEnable()
{
    if (mParams.mWhiteList.size() > 0)
    {
        GetOwner()->IncStateAdjust(StateAdjust::NonRefTargetWithWhiteList); 
        GetOwner()->IncStateAdjust(StateAdjust::NonEffTargetWithWhiteList); 
    }
    else
    {
        GetOwner()->IncStateAdjust(StateAdjust::NonRefTarget); 
        GetOwner()->IncStateAdjust(StateAdjust::NonEffTarget); 
    }
}

void BuffModNonTargettable::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
    bool hasWhiteList = mParams.mWhiteList.size() > 0;
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
        mParams.mWhiteList.clear();
		return;
	}

    if (hasWhiteList)
    {
        GetOwner()->DecStateAdjust(StateAdjust::NonRefTargetWithWhiteList);
        GetOwner()->DecStateAdjust(StateAdjust::NonEffTargetWithWhiteList);
    }
    else
    {
        GetOwner()->DecStateAdjust(StateAdjust::NonRefTarget);
        GetOwner()->DecStateAdjust(StateAdjust::NonEffTarget);
    }
}

bool BuffModNonTargettable::InWhiteList(int64 aSkillId)
{
    if (mParams.mWhiteList.size() > 0)
    {
        for (int i = 0; i < mParams.mWhiteList.size(); ++i)
        {
            if (mParams.mWhiteList[i] == aSkillId)
            {
                return true;
            }
        }
    }
    return false;
}