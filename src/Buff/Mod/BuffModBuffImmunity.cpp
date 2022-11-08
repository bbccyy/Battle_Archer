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

#include "BuffModBuffImmunity.h"
#include "Entity/Unit.h"

void BuffModBuffImmunity::StackAdded(int)
{
    //nothing
}

void BuffModBuffImmunity::StackRemoved(int)
{
    //nothing
}

void BuffModBuffImmunity::OnEnable()
{
    switch (mParams.mTargetType)
    {
    case BuffDispelTarget::ByMainType:
    {
        GetOwner()->RemoveByBuffType(mParams.mByMainType, 0, GetBuff()->GetId(), true);
        GetOwner()->BuffImmunityByType(mParams.mByMainType);
    }
    break;
    case BuffDispelTarget::BySubType:
    {
        GetOwner()->RemoveByBuffSubType(mParams.mBySubType, 0, GetBuff()->GetId(), true);
        GetOwner()->BuffImmunityBySubType(mParams.mBySubType);
    }
    break;
    case BuffDispelTarget::ById:
    {
        GetOwner()->RemoveBuff(mParams.mById, 0, GetBuff()->GetId(), true);
        GetOwner()->BuffImmunity(mParams.mById);
    }
    break;
    default:
        LOG_FATAL("Unrecognized buff dispel target type");
        break;
    }
}

void BuffModBuffImmunity::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mById.clear();
		mParams.mByMainType.clear();
		mParams.mBySubType.clear();
		return;
	}
    switch (mParams.mTargetType)
    {
    case BuffDispelTarget::ByMainType:
    {
        GetOwner()->RevokeBuffImmunityByType(mParams.mByMainType);
    }
    break;
    case BuffDispelTarget::BySubType:
    {
        GetOwner()->RevokeBuffImmunityBySubType(mParams.mBySubType);
    }
    break;
    case BuffDispelTarget::ById:
    {
        GetOwner()->RevokeBuffImmunity(mParams.mById);
    }
    break;
    default:
        LOG_FATAL("Unrecognized buff dispel target type");
        break;
    }
}