/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wangyixun
* @date $Date$
* @version $Revision$
* @brief
*
**/

#include "BuffModReflectBuff.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"

void BuffModReflectBuff::StackAdded(int)
{
	//nothing
}

void BuffModReflectBuff::StackRemoved(int)
{
	//nothing
}

void BuffModReflectBuff::OnEnable()
{
	mLastActiveTime = 0;
	GetOwner()->IncStateAdjust(StateAdjust::ReflectBuff);
}

void BuffModReflectBuff::OnDisable(bool aShouldTrigger)
{
	mLastActiveTime = 0;
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mReflectable.clear();
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::ReflectBuff);
	mParams.mReflectable.clear();
}

bool BuffModReflectBuff::OnActive(int aBuffId)
{
	if (!IsValid())
		return false;
	auto& owner = GetOwner();
	int ownerTime = owner->GetUnitTime();
	if (mLastActiveTime > 0 && ownerTime - mLastActiveTime < mParams.mCD) 
		return false;
	auto&& buff = owner->GetBuff(aBuffId);
	if (!buff) return false;  //the target buff may be removed due to stack num change 
	BuffSubType type = buff->GetSubType();
	BuffType mainType = buff->GetType();
	if (mParams.mReflectable.empty())
	{
		if (mainType == BuffType::Negative)
		{
			mLastActiveTime = ownerTime;
			return true;
		}
	}
	else
	{
		for (auto subType : mParams.mReflectable)
		{
			if (type == subType)
			{
				mLastActiveTime = ownerTime;
				return true;
			}
		}
	}
	return false;
}