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


class Unit;

//reference target counld be a unit or position
enum class ERefTargetType
{
    Invalid,
    Unit,
    Pos
};

enum class ERefFaceTo
{
	None = 0,
	Target = 1,
	OppTarget = 2
};

class RefTarget
{
public:
    RefTarget();
    void Set(const RefTarget& aTarget);
    void SetUnit(const SharedPtr<Unit>& aUnit);
    void SetPos(const Vector3& aPos);
	void SetRot(const Vector3& aRot);
    ERefTargetType GetType() const;
	void SetType(ERefTargetType);
    const SharedPtr<Unit> GetUnit() const;
    int GetSize() const;
    const Vector3& GetTargetPos() const;
	const Vector3& GetTargetRot() const;
	void GetTargetSocketBodyPos(Vector3&) const;
	uint32 GetEntityId() const;
	void Reset();
public:
	bool operator ==(const RefTarget& d)
	{
		if (mType != d.GetType())
		{
			return false;
		}
		if (mType == ERefTargetType::Pos)
		{
			if (mPos != d.GetTargetPos())
			{
				return false;
			}
		}
		else
		{
			if (mUnit != d.GetUnit())
			{//TODO: compare between two shared ptrs?
				return false;
			}
		}
		return true;
	}
private:
    //RefTarget(const RefTarget&);
    //void operator=(const RefTarget &);  

private:
    ERefTargetType mType = ERefTargetType::Invalid;
    SharedPtr<Unit> mUnit = nullptr;
    Vector3 mPos = Vector3(0,0,0);
	Vector3 mRot = Vector3(0, 0, 0);
};
