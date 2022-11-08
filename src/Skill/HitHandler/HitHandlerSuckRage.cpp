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


#include "HitHandlerSuckRage.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"



void HitHandlerSuckRage::Reset()
{
	HitHandler::Reset();
    RelaseDmgOrHealHandler();
};



void HitHandlerSuckRage::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
}


void HitHandlerSuckRage::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{

    

    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillEnergyDrawData& suckRageConf = skillConf->energydrawdata();
    SharedPtr<Skill> skill = aSkillCarrier->GetSkill();

    int64 suckValue = 0;
    switch(suckRageConf.drawtype())
    {
        case ESuckRageTypeCurRagePercent:
            suckValue = aTarget->GetRage() * ( suckRageConf.drwaparam1() + suckRageConf.drawparam2() * skill->GetLevelMinus() ) / DENOM;
            break;
        case ESuckRageTypeMaxRagePercent:
            suckValue = aTarget->GetMaxRage() * ( suckRageConf.drwaparam1() + suckRageConf.drawparam2() * skill->GetLevelMinus() ) / DENOM;
            break;
        case ESuckRageTypeFixValue:
            suckValue = suckRageConf.drwaparam1() + suckRageConf.drawparam2() * skill->GetLevelMinus();
            break;
    }

    int64 recoverValue = 0;
    if( suckRageConf.recovertype() > 0 )
    {
        recoverValue = suckValue * ( suckRageConf.recoverparam1() + suckRageConf.recoverparam2() * skill->GetLevelMinus() ) / DENOM;
    }

    aTarget->SubRage(suckValue, ERageChangeCause::SkillBeSucked);

    if( recoverValue > 0 )
    {
        aUtilizer->AddRage(recoverValue, ERageChangeCause::SkillSuck);
    }

	if (mDmgOrHealHandler)
	{
		mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
	}
	else
	{
		TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, 0);
	}
}


