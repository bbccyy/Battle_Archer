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

#include "HitHandler.h"

struct DamageIntermediateResult
{
	int64 baseAtk;
	int64 baseDef;
	int64 channelPercent;
	int64 attrPercent;
	int64 talentRate;
	int64 proTalent;
	int64 genderAmend;
	int64 armourPiercing;
	int64 pvpAmend;
	int64 pveAmend;
};


class HitHandlerDamage : public  HitHandler
{
public:
    void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
    void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) override;
	void AfterHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
	void Reset();

	int64 CalculateDamageNormal(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, HitResult& aHitResult, int64 aSpecialAdjust = DENOM, ESpecialAdjustTarget aTargetType = ESpecialAdjustDmgOrHeal);
    void CalculateDamageCoefPhysical(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, DamageIntermediateResult& aIntermedResult);
    void CalculateDamageCoefMagic(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, DamageIntermediateResult& aIntermedResult);
	int64 CalculateSpecialCoef(SharedPtr<Unit> aTarget, const SkillData*, const ESpecialAdjustTarget);

    inline int64 GetDamage()
    {
        return mDamage;
    }

private:
    int64 mAdjuestByTargetNumCoef; //根据人数的伤害调整系数
    int64 mDamage;
};




