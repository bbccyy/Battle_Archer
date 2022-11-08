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


class HitHandlerHeal : public  HitHandler
{
public:
    virtual void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
    virtual void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier);
    void Reset();
    
	int64 CalculateHealNormal(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, HitResult& aHitResult);
	int64 CalculateSpecialCoef(SharedPtr<Unit> aTarget, const SkillData* aSkillConf, const ESpecialAdjustTarget aTargetType);
    
private:
    int64 mAdjuestByTargetNumCoef; //根据人数的伤害调整系数
};




