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

#pragma once
#include "HitHandler.h"
struct ControlToken;

class HitHandlerGrab : public HitHandler
{
public:
    HitHandlerGrab();
    void Reset();

    bool CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) override;
    void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
    void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) override;
    bool OnTick(int aDeltaTime) override;
    void Cancel() override;
private:
    SharedPtr<Unit> mUtilizer;
    SharedPtr<Unit> mTarget;
    WeakPtr<SkillCarrier> mSkillCarrier;
    const SkillData* mSkillConf;
    const SkillGrabData* mGrabConf;
    SharedPtr<ControlToken> mControlState;
    int mGrabTime;
    Vector3 mRelativePosition;

    inline void TriggerOnEnd();
    void ExternalCancelRequest(SharedPtr<Unit> aControlledUnit);
};