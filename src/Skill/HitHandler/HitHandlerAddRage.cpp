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


#include "HitHandlerAddRage.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"



void HitHandlerAddRage::Reset()
{
	HitHandler::Reset();
    RelaseDmgOrHealHandler();
};



void HitHandlerAddRage::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
}


void HitHandlerAddRage::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillEnergyAssistData& addRageConf = skillConf->energyassisdata();
    SharedPtr<Skill> skill = aSkillCarrier->GetSkill();

    int64 costValue = 0;
    switch( addRageConf.assisttype() )
    {
        case EAddRageSkillCostTypeNoCost:
            costValue = 0;
            break;
        case EAddRageSkillCostTypeCurRagePercent:
            costValue = aUtilizer->GetRage() * ( addRageConf.assistparam1() + skill->GetLevelMinus()*addRageConf.assistparam2() )  / DENOM;
            break;
        case EAddRageSkillCostTypeMaxRagePercent:
            costValue = aUtilizer->GetMaxRage() * ( addRageConf.assistparam1() + skill->GetLevelMinus()*addRageConf.assistparam2() )  / DENOM;
            break;
        case EAddRageSkillCostTypeFixValue:
            costValue = addRageConf.assistparam1() + skill->GetLevelMinus()*addRageConf.assistparam2();
            break;
    }

    int64 addValue = 0;
    switch(addRageConf.addtype())
    {
        case EAddRageSkillAddTypeCostPercent:
            addValue = costValue * ( addRageConf.addparam1() + skill->GetLevelMinus()*addRageConf.addparam2() )  / DENOM;
            break;
        case EAddRageSkillAddTypeCurRagePercent:
            addValue = aTarget->GetRage() * ( addRageConf.addparam1() + skill->GetLevelMinus()*addRageConf.addparam2() )  / DENOM;
            break;
        case EAddRageSkillAddTypeMaxRagePercent:
            addValue = aTarget->GetMaxRage() * ( addRageConf.addparam1() + skill->GetLevelMinus()*addRageConf.addparam2() )  / DENOM;
            break;
    }

    if(costValue > 0)
    {
        aUtilizer->SubRage(costValue, ERageChangeCause::SkillGive);
    }  
    aTarget->AddRage(addValue, ERageChangeCause::SkillBeGiven);

	if (mDmgOrHealHandler)
	{
		mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
	}
	else
	{
		TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, 0);
	}
}


