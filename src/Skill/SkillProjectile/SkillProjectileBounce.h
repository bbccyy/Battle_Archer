#pragma once

#include "SkillProjectile.h"

class SkillProjectileBounce : public SkillProjectile, public EnableSharedFromThis<SkillProjectileBounce>
{
public:
    void Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget) override;
    bool OnTick(int) override;
    void Reset() override;

    void AfterReachTarget();
protected:
    void InitMoveParam();
protected:
    SharedPtr<MovePath> mMovePath = nullptr;
    EMoveStatus mMoveStatus = EMoveStatus::EMoveDone;
};