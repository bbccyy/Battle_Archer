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

#include "BuffModShapeshift.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModShapeshift::StackAdded(int)
{
    //nothing
}

void BuffModShapeshift::StackRemoved(int)
{
    //nothing
}

void BuffModShapeshift::OnEnable()
{
	mShapeShift = GetOwner()->EnableShapeshift(*this);
}

void BuffModShapeshift::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mShapeShift = nullptr;
		mParams.mKeepChainOrder = false;
		mParams.mTplId = 0;
		mParams.mInheritBuff = ShapeshiftBuffInheritanceRule::AllBuff;
		mParams.mInheritAttributes = false;
		mParams.mInheritSkill = false;
		mParams.mInheritLevel = 0;
		mParams.mLevel = 0;
		mLastTplId = 0;
		mLastLevel = 0;
		mLastAttrArr.clear();
		return;
	}
	mShapeShift->mIsValid = false;
    GetOwner()->DisableShapeshift();
}