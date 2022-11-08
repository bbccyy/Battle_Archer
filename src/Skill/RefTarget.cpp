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
 * @brief
 *
 **/

#pragma once

#include "Framework/SharedPtr.h"
#include "Framework/Transform.h"
#include "SkillDefine.h"
#include "Entity/Unit.h"
#include "RefTarget.h"

RefTarget::RefTarget()
    : mType(ERefTargetType::Invalid)
{
};

void RefTarget::Set(const RefTarget& aTarget)
{
    mType = aTarget.mType;
	if(mType == ERefTargetType::Unit)
	{
		mUnit = aTarget.mUnit;
	}
	mRot.Set(aTarget.mRot);
    mPos.Set(aTarget.mPos);
}
void RefTarget::SetUnit(const SharedPtr<Unit>& aUnit)
{
    mType = ERefTargetType::Unit;
    mUnit = aUnit;
	mRot.Set(0, 0, 0);
}
void RefTarget::SetPos(const Vector3& aPos)
{
    mType = ERefTargetType::Pos;
    mPos.Set(aPos);
	mRot.Set(0, 0, 0);
}
void RefTarget::SetRot(const Vector3& aRot)
{
	mRot.Set(aRot);
}
ERefTargetType RefTarget::GetType() const
{
    return mType;
}
void RefTarget::SetType(ERefTargetType aType)
{
	mType = aType;
}
const SharedPtr<Unit> RefTarget::GetUnit() const
{
    return mUnit;
}

uint32 RefTarget::GetEntityId() const
{
	if (mUnit)
		return mUnit->GetEntityId();
	return uint32(0);
}

int RefTarget::GetSize() const
{
    return mType == ERefTargetType::Unit ? mUnit->GetSize() : 0;
}

const Vector3& RefTarget::GetTargetPos() const
{
    return mType == ERefTargetType::Unit ? mUnit->GetPosition() : mPos;
}

const Vector3& RefTarget::GetTargetRot() const
{
	return mType == ERefTargetType::Unit ? mUnit->GetForward() : mRot;
}

void RefTarget::GetTargetSocketBodyPos(Vector3& aPos) const
{
	if (mType == ERefTargetType::Unit)
	{
		aPos.Set(mUnit->GetPosition());
		aPos.y += mUnit->GetIdleBodyHeight();		
	}
	else 
	{
		aPos.Set(mPos);
	}	
}

void RefTarget::Reset()
{
	mType = ERefTargetType::Invalid;
	if (mUnit)
		mUnit.Release();
	mPos.Set(0, 0, 0);
	mRot.Set(0, 0, 0);
}