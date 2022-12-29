#pragma once

#include "SkillProjectile.h"

enum class EProjectileBounceStatus
{
    EProjectileBounceStatusNormal,
    EProjectileBounceStatusDone
};

class SkillProjectileBounce : public SkillProjectile, public EnableSharedFromThis<SkillProjectileBounce>
{
public:
    void Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget) override;
    bool OnTick(int) override;
    void Reset() override;

protected:
    void InitMoveParam();

protected:
    SharedPtr<MoveBounce> mMoveBounce = nullptr;
    EMoveStatus mMoveStatus = EMoveStatus::EMoveDone;

    EProjectileBounceStatus mStatus = EProjectileBounceStatus::EProjectileBounceStatusNormal;
};