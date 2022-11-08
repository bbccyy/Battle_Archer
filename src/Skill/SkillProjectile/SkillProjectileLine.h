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

#include "SkillProjectile.h"

enum EProjectileLineStatus
{
    EProjectileLineStatusForward,
    EProjectileLineStatusStayOnReach,
    EProjectileLineStatusBackward,
    EProjectileLineStatusDone
};


class SkillProjectileLine : public SkillProjectile, public EnableSharedFromThis<SkillProjectileLine>
{
public:
    void Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget) override;
    bool OnTick(int) override;
    void Reset() override;

    void AfterReachTarget();
protected:
	void InitMoveParam();
protected:

	SharedPtr<MoveStraight> mMoveStraight = nullptr;

    int mStayTimeOnReachTarget = 0;

    EProjectileLineStatus mStatus = EProjectileLineStatus::EProjectileLineStatusForward;
	EMoveStatus mMoveStatus = EMoveStatus::EMoveDone;
};
