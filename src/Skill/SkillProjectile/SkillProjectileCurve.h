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

#define SEG_NUM 3

enum EProjectileCurveStatus
{
    EProjectileCurveStatusForward,
    EProjectileCurveStatusForwardTrace, //在锁定目标，且移动过程中目标移动了，需要在曲线移动后加个直线追击的过程
    EProjectileCurveStatusBackward,
    EProjectileCurveStatusDone
};

class SkillProjectileCurve : public SkillProjectile , public EnableSharedFromThis<SkillProjectileCurve>
{
public:
    void Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget) override;
    bool OnTick(int) override;
    void Reset() override;

protected:
    void OnReachTarget();

protected:

	EMoveStatus mMoveStatus = EMoveStatus::EMoveDone;
	SharedPtr<MoveCurve> mMoveCurve = nullptr;
    
	int64 mSpeed0 = 0;
    EProjectileCurveStatus mStatus = EProjectileCurveStatus::EProjectileCurveStatusForward;
};
