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


#include "HitHandlerDamage.h"
#include "HitHandlerSuckBlood.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"



void HitHandlerSuckBlood::Reset()
{
	HitHandler::Reset();
    RelaseDmgOrHealHandler();
};



void HitHandlerSuckBlood::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
}

bool HitHandlerSuckBlood::CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
	/*if (aUtilizer->CheckStateAdjust(StateAdjust::NoSuckBlood))
	{
		return false;
	}*/
	return DefaultHitDecision(aUtilizer, aTarget, aSkillCarrier);
}


void HitHandlerSuckBlood::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillLifeStealData& suckBloodConf = skillConf->lifestealdata();
    SharedPtr<Skill> skill = aSkillCarrier->GetSkill();
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
		if (aSkillCarrier && aSkillCarrier->IsEnded())
		{
			return;
		}
    }
    else
    {
        LOG_FATAL("suckblood skill need damage. skill:%d", skillConf->id());
    }

	if (suckBloodConf.buffsubtypefilter_size() > 0)
	{
		vector<BuffSubType> list;
		list.reserve(suckBloodConf.buffsubtypefilter_size());
		for (auto type : suckBloodConf.buffsubtypefilter())
		{
			list.emplace_back(static_cast<BuffSubType>(type));
		}
		if (!aTarget->HasBuffBySubTypes(list))
		{ //mismatch buff sub type, so abandon 
			return;
		}
	}

    int64 suckValue = 0;
    int typ = suckBloodConf.type();
    switch(typ)
    {
        case ESuckBloodSkillSuckTypeDamagePercent:
            suckValue =  DynamicPointerCast<HitHandlerDamage, HitHandler>(mDmgOrHealHandler)->GetDamage() 
                            * ( suckBloodConf.param1() + suckBloodConf.param2() * skill->GetLevelMinus() ) / DENOM;
            break;
        case ESuckBloodSkillSuckTypeTargetCurHpPercent:
            suckValue = IncByRate(aTarget->GetHp(), suckBloodConf.param1() + suckBloodConf.param2() * skill->GetLevelMinus(), DENOM);
            //suckValue = aTarget->GetHp() * ( suckBloodConf.param1() + suckBloodConf.param2() * skill->GetLevelMinus() ) / DENOM;
            break;
        case ESuckBloodSkillSuckTypeTargetMaxHpPercent:
            suckValue = IncByRate(aTarget->GetMaxHp(), suckBloodConf.param1() + suckBloodConf.param2() * skill->GetLevelMinus(), DENOM);
            //suckValue = aTarget->GetMaxHp() * ( suckBloodConf.param1() + suckBloodConf.param2() * skill->GetLevelMinus() ) / DENOM;
            break;
        case ESuckBloodSkillSuckTypeFixValue:
            suckValue = suckBloodConf.param1() + suckBloodConf.param2() * skill->GetLevelMinus();
            break;
    }
    if(  suckBloodConf.upperlimit() && 
        ( ESuckBloodSkillSuckTypeTargetCurHpPercent == typ 
            || ESuckBloodSkillSuckTypeTargetMaxHpPercent == typ ) )
    {
        int64 baseAtk = aUtilizer->GetMagicAtk();
        int64 limit = baseAtk * suckBloodConf.upperlimitparam() / DENOM;
        if( suckValue > limit )
        {
            suckValue = limit;
            LOG_DEBUG("reach limit:%d", limit);
        }
    }
    aUtilizer->HealByStealHp(suckValue, skill.Get(), nullptr);    
}


