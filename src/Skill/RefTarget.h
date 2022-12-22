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

enum class EProjectileStartPointSlot
{
	NONE = 0,

	SLOT_FRONT_1 = 1,		//  -> 1,2,3,4,5 <-   +1弹道取3号；+2弹道取2和4号；+3弹道取1,3,5号 
	SLOT_FRONT_2 = 2,
	SLOT_FRONT_3 = 3,
	SLOT_FRONT_4 = 4,
	SLOT_FRONT_5 = 5,

	SLOT_ANGULAR_1 = 6,		//	-> 6,7,8,9 <-	+1弹道取左侧7和右侧8号；+2弹道取左侧6,7和右侧8,9号 
	SLOT_ANGULAR_2 = 7,
	SLOT_ANGULAR_3 = 8,
	SLOT_ANGULAR_4 = 9,

	SLOT_LEFT = 10,			// 就是左侧和右侧 
	SLOT_RIGHT = 11,

	SLOT_BACK_1 = 12,		// -> 11,12,13 <- +1弹道取12号； +2弹道取11，13号 
	SLOT_BACK_2 = 13,
	SLOT_BACK_3 = 14,
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
	EProjectileStartPointSlot GetSlot() const;
	void SetSlot(EProjectileStartPointSlot);
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
	EProjectileStartPointSlot mStartPointSlot = EProjectileStartPointSlot::NONE;
};
