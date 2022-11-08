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

#include "BuffModTransformScale.h"
#include "Entity/Unit.h"
#include "Define.h"
#include "Buff/Buff.h"

void BuffModTransformScale::StackAdded(int)
{
	int stk = GetBuff()->GetStack();
	int scale = mParams.mPercent + (stk - 1) * mParams.mBaseDelta;
    GetOwner()->Scale(scale, mParams.mTransformationTime);
}

void BuffModTransformScale::StackRemoved(int)
{
	int stk = GetBuff()->GetStack();
	int scale = mParams.mPercent + (stk - 1) * mParams.mBaseDelta;
	GetOwner()->Scale(scale, mParams.mTransformationTime);
}

void BuffModTransformScale::OnEnable()
{
	GetOwner()->Scale(mParams.mPercent, mParams.mTransformationTime);
}

void BuffModTransformScale::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->ScaleOffset(0, mParams.mTransformationTime);
}