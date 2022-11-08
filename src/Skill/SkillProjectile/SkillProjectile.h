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
#include "Framework/SharedPool.h"
#include "module/SkillData.pb.h"
#include "Framework/Transform.h"
#include "Skill/RefTarget.h"
#include "Entity/Entity.h"
#include "Entity/MoveExecutor/MoveStraight.h"
#include "Entity/MoveExecutor/MoveTrace.h"
#include "Entity/MoveExecutor/MoveCurve.h"
#include <unordered_set>

using namespace pb;
using std::unordered_set;

class SkillCarrier;


class SkillProjectile : public Entity
{
public:
    virtual void InitBase(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget);
    virtual void Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget) = 0;
    virtual bool OnTick(int) = 0;
    virtual void Reset() = 0;
    void ResetBase();
    int CollisionDetection(Vector3& aStart, Vector3& aEnd);

	void clearTouchedEntityIdArr();

	SharedPtr<MoveCurve> BuildCurveExecutor(SharedPtr<Entity>);
	SharedPtr<MoveTrace> BuildTraceExecutor(SharedPtr<Entity>);
	SharedPtr<MoveStraight> BuildStraightExecutor(SharedPtr<Entity>);

protected:
    SharedPtr<Unit> mOwner = nullptr;
    WeakPtr<SkillCarrier> mCarrier = nullptr;
    const SkillData* mSkillConf = nullptr;
    RefTarget mRefTarget;
	SharedPtr<MoveExecutor> mCurExecutor = nullptr;

	Vector3 mTargetPos  = Vector3(0,0,0);

    bool mLockTarget = false;
    bool mIsBoomerang = false;
    bool mEffectOnBack = false;
	bool mNoVerticalMove = false;
	bool mIsSweepLine = false;
	bool mEndOnReachRefTarget = false;

	int mCurveRadius = 0;
	int mLineLength = 0;
    int mCollisionCheckType = 0;
    int mCurCollisionNum = 0;
    int mMaxCollisionNum = 0;
    int mTime = 0;    

	unordered_set<int> mTouchedEntityIdArr;
};


SharedPtr<SkillProjectile> NewSkillProjectile(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget);
