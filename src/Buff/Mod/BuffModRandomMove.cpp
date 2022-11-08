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

#include "BuffModRandomMove.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "BattleInstance.h"

const Vector3 BuffModRandomMove::DIRS[] = {
    Vector3(DENOM, 0, 0),
    Vector3(0, 0, DENOM),
    Vector3(-DENOM, 0, 0),
    Vector3(0, 0, -DENOM)
};

void BuffModRandomMove::StackAdded(int)
{
    //nothing
}

void BuffModRandomMove::StackRemoved(int)
{
    //nothing
}

void BuffModRandomMove::OnEnable()
{
    mControlState = ControlToken::Create(ControlledType::RandomMove, MakeFunction<>(*this, &BuffModRandomMove::Move), Unit::ANIM_NAME_RUN);
    GetOwner()->BeControlled(*mControlState);
    NextPos();
}

void BuffModRandomMove::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mControlState = nullptr;
		return;
	}
	auto& owner = GetOwner();
	owner->DisableMove();
	owner->ClearBeControlled(*mControlState);
	mControlState = nullptr;
	mMoveTarget = Vector3(0, 0, 0);
	mRefTarget.Reset();
}

bool BuffModRandomMove::Move(int aDeltaTime)
{
	if (mParams.initTarget == false) 
	{
		mMoveTarget = GetOwner()->GetPosition();
		mRefTarget.SetPos(mMoveTarget);
		mParams.initTarget = true;
	}
    //if (GetOwner()->MoveTowards(mMoveTarget, 0, aDeltaTime, 0))
	if(GetOwner()->Move(mRefTarget, GetOwner(), 0, aDeltaTime))
    {
        NextPos();
    }
    return false;
}

void BuffModRandomMove::NextPos()
{
    //通过4方向中随机(a)选取两个连续方向，通过线性插值选取随机(b)方向，最后随机(c)缩短移动距离 
    //4方向时，区域为菱形，提高方向数量可以更趋近于圆形 
    auto& battle = GetOwner()->GetBattleInstance();
    int a = battle.Rand(DIR_SIZE);
    int b = battle.Rand(DENOM);
    int64 c = battle.Rand(mParams.mRadius);
	mMoveTarget = (DIRS[a] * b + DIRS[(a + 1) % DIR_SIZE] * (DENOM - b)) / DENOM * c / DENOM;
	mRefTarget.SetPos(mMoveTarget);
}

void BuffModRandomMove::ResetValues()
{
	BuffMod::ResetValues();
	mControlState = nullptr;
	mMoveTarget = Vector3(0, 0, 0);
	mRefTarget.Reset();
}