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

#include "BuffModDispel.h"
#include "Entity/Unit.h"

void BuffModDispel::StackAdded(int)
{
    //nothing
}

void BuffModDispel::StackRemoved(int)
{
    //nothing
}

void BuffModDispel::OnReset()
{
	BuffMod::OnReset();
	if (IsValid())
		OnEnable();
}

void BuffModDispel::OnEnable()
{
    switch (mParams.mTargetType)
    {
    case BuffDispelTarget::ByMainType:
    {
        bool suc = GetOwner()->RemoveByBuffType(mParams.mByMainType, mParams.mPartialClearCount, GetBuff()->GetId(), true, mParams.mCleanLevel);
		SendEvent(suc);
    }
    break;
    case BuffDispelTarget::BySubType:
    {
		bool suc = GetOwner()->RemoveByBuffSubType(mParams.mBySubType, mParams.mPartialClearCount, GetBuff()->GetId(), true, mParams.mCleanLevel);
		SendEvent(suc);
    }
    break;
    case BuffDispelTarget::ById:
    {
		bool suc = GetOwner()->RemoveBuff(mParams.mById, mParams.mPartialClearCount, GetBuff()->GetId(), true);
		SendEvent(suc);
    }
    break;
    default:
        LOG_FATAL("Unrecognized buff dispel target type");
        break;
    }
}

void BuffModDispel::OnDisable(bool aShouldTrigger)
{
    //nothing
	mParams.mById.clear();
	mParams.mByMainType.clear();
	mParams.mBySubType.clear();
	mParams.mCleanLevel = 0;
}

void BuffModDispel::SendEvent(bool aSuc)
{
	if (!aSuc || !IsValid())
		return;
	auto& owner = GetOwner();
	auto& utilizer = GetSourceUtilizer();
	if (owner && utilizer)
	{
		utilizer->OnDispelBuff(owner.Get());
	}
}