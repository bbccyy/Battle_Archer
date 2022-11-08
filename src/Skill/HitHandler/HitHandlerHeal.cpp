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


#include "HitHandlerHeal.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "ConfigMgr/ConfigMgr.h"
#include "BattleInstance.h"


void HitHandlerHeal::Reset()
{
	HitHandler::Reset();
	mAdjuestByTargetNumCoef = 0;
}

void HitHandlerHeal::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillHealData& healConf = skillConf->healdata();
	const SkillEnergyRecoverData& rageConf = skillConf->energyrecoverdata();

    mAdjuestByTargetNumCoef = DENOM;

    if( healConf.adjustbytargetcount() )
    {
        int targetNum = static_cast<int>(aEffTargetArr.size());
        if( healConf.adjustdata_size() % 2 != 0 )
        {
            LOG_FATAL("invalid conf. AdjustData. skill:%d", skillConf->id());
        }
        for( int i = 0; i < healConf.adjustdata_size(); i+=2 )
        {
            if( targetNum >= healConf.adjustdata(i) )
            {
                mAdjuestByTargetNumCoef = healConf.adjustdata(i+1);
            }
            else
            {
                break;
            }
        }
    }

	if (rageConf.adjustbytargetcount())
	{
		int64 rageCoef = DENOM;
		int targetNum = static_cast<int>(aEffTargetArr.size());
		if (rageConf.adjustdata_size() % 2 != 0)
		{
			LOG_FATAL("invalid conf. AdjustData. skill:%d", skillConf->id());
		}
		for (int i = 0; i < rageConf.adjustdata_size(); i += 2)
		{
			if (targetNum >= rageConf.adjustdata(i))
			{
				rageCoef = rageConf.adjustdata(i + 1);
			}
			else
			{
				break;
			}
		}
		int64 addRage = rageCoef * (int64(rageConf.param1()) + int64(rageConf.param2()) * aSkillCarrier->GetSkill()->GetLevelMinus()) / DENOM;
		if (addRage > 0)
			aUtilizer->AddRage(addRage, ERageChangeCause::ExecuteSkill);
	}
}

void HitHandlerHeal::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillHealData& healConf = skillConf->healdata();
    int healType = healConf.healtype();

    SharedPtr<Skill> skill = aSkillCarrier->GetSkill();

    HitResult hitResult;
    hitResult.mIsHit = true;
	hitResult.mIsPhysical = skillConf->basedata().skilltunnel() == EDamageChannelPhysical;

    int64 skillFinal = int64(healConf.extraparam1()) + int64(healConf.extraparam1()) * skill->GetLevelMinus();
    int64 value = 0;

	int64 specialAdjust = DENOM;
	ESpecialAdjustTarget targetType = ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal;

	if (healConf.has_specialadjust() && healConf.specialadjust().enable())
	{
		auto& adjConf = healConf.specialadjust();
		if (adjConf.has_adjusttarget())
		{
			targetType = static_cast<ESpecialAdjustTarget>(adjConf.adjusttarget());
		}
		specialAdjust = CalculateSpecialCoef(aTarget, skillConf, targetType);
	}
	int64 healRate = aUtilizer->GetAttr(EAttribute::HealPercentAdd) + aTarget->GetAttr(EAttribute::BeHealPercentAdd);
	SharedPtr<Unit> skillSourceUnit = aSkillCarrier->GetSkillExecutor()->GetSourceUnit();
    switch(healType)
    {
        case EHealCalculateMethodNormal:
		case EHealCalculateMethodNoOverflow:
            value = CalculateHealNormal(skillSourceUnit, aTarget, skill, hitResult) + skillFinal;
            break;
        case EHealCalculateMethodMaxHpPercent:
			value = IncByRate(aTarget->GetMaxHp(), int64(healConf.typeparam1()) + skill->GetLevelMinus() * int64(healConf.typeparam2()), DENOM);
            //value = aTarget->GetMaxHp() * (int64(healConf.typeparam1()) + skill->GetLevelMinus() * int64(healConf.typeparam2()))  / DENOM;
			value = ApplySpecialAdjustCommon(value, specialAdjust, targetType, ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal);
			value = value + skillFinal;
            break;
        case EHealCalculateMethodCurHpPercent:
			value = IncByRate(aTarget->GetHp(), (int64(healConf.typeparam1()) + skill->GetLevelMinus() * int64(healConf.typeparam2())), DENOM);
            //value = aTarget->GetHp() * (int64(healConf.typeparam1()) + skill->GetLevelMinus() * int64(healConf.typeparam2())) / DENOM;
			value = ApplySpecialAdjustCommon(value, specialAdjust, targetType, ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal);
			value = value + skillFinal;
            break;
        case EHealCalculateMethodFixValue:
            value = healConf.typeparam1() + skill->GetLevelMinus() * int64(healConf.typeparam2()) + skillFinal;
            break;
        case EHealCalculateMethodAddToMax:
			if (healRate <= 0) value = 0;
            else value = aTarget->GetMaxHp() - aTarget->GetHp();
            break;
		case EHealCalculateMethodRecordData:
			value = aUtilizer->GetBuffRecordData(healConf.buffid()) * (int64(healConf.typeparam1()) + skill->GetLevelMinus()* int64(healConf.typeparam2())) / DENOM;
			break;
		case EHealCalculateMethodSelfLoseHpPercent:
			value = IncByRate(aUtilizer->GetMaxHp() - aUtilizer->GetHp(), int64(healConf.typeparam1()) + skill->GetLevelMinus() * int64(healConf.typeparam2()), DENOM);
			//value = (aUtilizer->GetMaxHp() - aUtilizer->GetHp()) * (int64(healConf.typeparam1()) + skill->GetLevelMinus()* int64(healConf.typeparam2())) / DENOM;
			break;
        default:
            LOG_FATAL("invalid heal calculate method:%d", healConf.healtype());
    }
    if(  healConf.upperlimit() && 
        ( EHealCalculateMethodMaxHpPercent == healType 
            || EHealCalculateMethodCurHpPercent == healType ) )
    {
        int64 baseAtk = hitResult.mIsPhysical ? skillSourceUnit->GetPhysicalAtk() : skillSourceUnit->GetMagicAtk();
        int64 limit = baseAtk * healConf.upperlimitparam() / DENOM;
        if( value > limit )
        {
            value = limit;
            LOG_DEBUG("reach heal limit:%d", limit);
        }
    }

	if (healConf.lowerlimit()
		&& (EHealCalculateMethodMaxHpPercent == healType
			|| EHealCalculateMethodCurHpPercent == healType
			|| EHealCalculateMethodAddToMax == healType))
	{
		int64 lowerHeal = 0;
		switch (static_cast<EDamageLimitType>(healConf.lowerlimittype()))
		{
		case EDamageLimitFixValue:
			lowerHeal = static_cast<int64>(healConf.lowerlimitparam());
			break;
		case EDamageLimitPhysical:
			lowerHeal = skillSourceUnit->GetPhysicalAtk() * healConf.lowerlimitparam() / DENOM;
			break;
		case EDamageLimitMagical:
			lowerHeal = skillSourceUnit->GetMagicAtk() * healConf.lowerlimitparam() / DENOM;
			break;
		default:
			LOG_WARN("unknow damage limit type %d", healConf.lowerlimittype());
		}
		if (value < lowerHeal)
		{
			value = lowerHeal;
		}
	}

	if (value < 0)
	{
		value = 0;  // no negtive heal value 
	}
    hitResult.mValue = value;
    int64 realHeal = aTarget->Heal(hitResult, skillSourceUnit.Get(), skill.Get(), nullptr);
	if (healType == EHealCalculateMethodNoOverflow && realHeal < value)
	{  //溢出型治疗需要考虑添加护盾buff和更新护盾血量等需求 
		aTarget->OnHealOverflow(healConf.buffid(), value - realHeal); 
	}
	TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, 0);
}


int64 HitHandlerHeal::CalculateHealNormal(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, HitResult& aHitResult)
{
    BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
	if (battleInstance.NeedDoStatistics()) aUtilizer->mTotalHealBase++;
    const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
    const SkillData* skillConf = aSkill->GetSkillConf();
    const SkillHealData& healConf = skillConf->healdata();

	int64 baseAtk = aHitResult.mIsPhysical ? aUtilizer->GetPhysicalAtk() : aUtilizer->GetMagicAtk();

    int64 skillFloatCoef = int64(healConf.typeparam1()) + aSkill->GetLevelMinus() * int64(healConf.typeparam2());
    skillFloatCoef += battleInstance.Rand(healConf.typeparam3()*2) - int64(healConf.typeparam3());
    skillFloatCoef = skillFloatCoef * mAdjuestByTargetNumCoef / DENOM;

    int64 intellCoef = DENOM + aUtilizer->GetAttr(EAttribute::Intelligence) * battleConfig->GetIntelligenceCureCoef();
    if( intellCoef > battleConfig->GetIntelligenceCureCoefLimit())
    {
        intellCoef = battleConfig->GetIntelligenceCureCoefLimit();
    }

    //爆击
    int64 criticalProb = 0;
	int64 criticalAddBySkill = 0;
    switch(healConf.crittype() )
    {
        case ECritTypeNorm:
            criticalProb = aUtilizer->GetAttr(EAttribute::HealCriticalProb);
            break;
        case ECritTypePositive:
            criticalProb = DENOM;
            break;
        case ECritTypeAddSkillPortion:
            criticalProb = aUtilizer->GetAttr(EAttribute::HealCriticalProb) + healConf.critparam();
			criticalAddBySkill = healConf.critparam2();
            break;
        case ECritTypeOnlySkillPortion:
            criticalProb = healConf.critparam();
			criticalAddBySkill = healConf.critparam2();
            break;
    }
    int64 criticalCoef = 0;
    if( criticalProb >= DENOM || criticalProb >= battleInstance.Rand(DENOM) )
    {
        criticalCoef = aUtilizer->GetAttr(EAttribute::HealCriticalPercentAdd) + criticalAddBySkill;
        aHitResult.mIsCrit = true;
		if (battleInstance.NeedDoStatistics()) aUtilizer->mCriticalHealCount++;
    }
    int64 floatCoef = battleInstance.Rand(battleConfig->GetCureFloatCoef()*2) - battleConfig->GetCureFloatCoef();
    
    int64 healValue = baseAtk * skillFloatCoef / DENOM;
    healValue = healValue * intellCoef / DENOM;
    healValue += healValue * ( aUtilizer->GetAttr(EAttribute::HealPercentAdd) + aTarget->GetAttr(EAttribute::BeHealPercentAdd) ) / DENOM;
    healValue += healValue * criticalCoef / DENOM;
    healValue += healValue * floatCoef / DENOM;

    healValue += aUtilizer->GetAttr(EAttribute::HealAdd) + aTarget->GetAttr(EAttribute::BeHealAdd);

    LOG_DEBUG("CalculateHealNormal baseAtk:%d, skillFloatCoef:%d, intellCoef:%d, criticalCoef:%d, floatCoef:%d, healValue:%d", 
                    baseAtk, skillFloatCoef, intellCoef, criticalCoef, floatCoef, healValue);

    return healValue;
}

int64 HitHandlerHeal::CalculateSpecialCoef(SharedPtr<Unit> aTarget, const SkillData* aSkillConf, const ESpecialAdjustTarget aTargetType)
{
	auto& healConf = aSkillConf->healdata();
	if (!healConf.has_specialadjust())
		return DENOM;
	auto& adjConf = healConf.specialadjust();

	bool enable = false;
	switch (adjConf.effecttype())
	{
	case EDamageSpecialAdjustEnable:
		enable = true;
		break;
	case EDamageSpecialAdjustNeedContainBuff:
		if (!adjConf.has_targetbuffid())
			LOG_FATAL("adjust type is needContainBuffId, but not found target buffId");
		if (aTarget->HasBuff(adjConf.targetbuffid()))
			enable = true;
		break;
	default:
		LOG_FATAL("invalid damage special adjust type:%d", adjConf.effecttype());
		break;
	}

	if (!enable)
		return DENOM;

	if (adjConf.buffparam_size() < 1)
	{
		LOG_WARN("invalid damage special adjust buffParam size:%d", adjConf.buffparam_size());
		return DENOM;
	}

	int layer = 0;
	auto& paramList = adjConf.buffparam();
	vector<int> param;
	for (auto data : paramList)
		param.push_back(data);

	switch (adjConf.bufftype())
	{
	case EDamageSpecialAdjustWithBuffMainType:
		layer = aTarget->CountBuffLayerByMainType(static_cast<BuffType>(paramList.Get(0)));
		break;
	case EDamageSpecialAdjustWithBuffSubType:
		layer = aTarget->CountBuffLayerBySubType(static_cast<BuffSubType>(paramList.Get(0)));
		break;
	case EDamageSpecialAdjustWithBuffIdOR:
		layer = aTarget->CountBuffLayerByBuffIdOR(param);
		break;
	case EDamageSpecialAdjustWithBuffIdAND:
		layer = aTarget->CountBuffLayerByBuffIdAND(param);
		break;
	default:
		LOG_FATAL("invalid damage special adjust sub type:%d", adjConf.bufftype());
		break;
	}

	if (layer == 0)
		return DENOM;

	if (adjConf.adjustdata_size() < 2 && (adjConf.adjustdata_size() % 2 != 0))
	{
		LOG_WARN("invalid damage special adjust table, adjustdata size :%d", adjConf.adjustdata_size());
		return DENOM;
	}

	if (adjConf.has_isusestateadjust() && adjConf.isusestateadjust())
	{
		return -DENOM;  //use negtive value as a denotation of modifing defandent value
	}

	auto& adjList = adjConf.adjustdata();
	int64 rawCoef = int64(adjList.Get(adjConf.adjustdata_size() - 1));
	for (int i = 0; i < adjList.size(); i += 2)
	{
		if (layer <= adjList.Get(i))
			rawCoef = int64(adjList.Get(i + 1));
		else
			break;
	}

	switch (aTargetType)
	{
	case ESpecialAdjustCrit:
		return rawCoef;
	case ESpecialAdjustDmgOrHeal:
		return rawCoef + int64(DENOM);
	default:
		LOG_FATAL("ileagle adjust type[%d]", int(aTargetType));
		return DENOM;
	}

	return DENOM;
}