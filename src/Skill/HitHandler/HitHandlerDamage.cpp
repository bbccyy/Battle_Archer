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
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "ConfigMgr/ConfigMgr.h"
#include "BattleInstance.h"
#include "Framework/Util.h"


inline int64 CurbRate(int64 aValue)
{
	if (aValue < -DENOM)
	{
		LOG_DEBUG("CurbRate fail, Given Val = %d < -10000", aValue);
		return -DENOM;
	}
	return aValue;
}

inline int64 CurbZero(int64 aValue)
{
	if (aValue < 0)
	{
		LOG_DEBUG("CurbZero fail, Given Val = %d < 0", aValue);
		return 0;
	}
	return aValue;
}

void HitHandlerDamage::Reset()
{
	HitHandler::Reset();
	mAdjuestByTargetNumCoef = 0;
	mDamage = 0;
}

void HitHandlerDamage::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillDamageData& damageConf = skillConf->damagedata();
	const SkillEnergyRecoverData& rageConf = skillConf->energyrecoverdata();

    mAdjuestByTargetNumCoef = DENOM;

    if( damageConf.adjustbytargetcount() )
    {
        int targetNum = static_cast<int>(aEffTargetArr.size());
        if( damageConf.adjustdata_size() % 2 != 0 )
        {
            LOG_FATAL("invalid conf. AdjustData. skill:%d", skillConf->id());
        }
        for( int i = 0; i < damageConf.adjustdata_size(); i+=2 )
        {
            if( targetNum >= damageConf.adjustdata(i) )
            {
                mAdjuestByTargetNumCoef = CurbZero(int64(damageConf.adjustdata(i+1)));
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
		int64 addRage = rageCoef * (rageConf.param1() + rageConf.param2() * aSkillCarrier->GetSkill()->GetLevelMinus()) / DENOM;
		if (addRage > 0)
			aUtilizer->AddRage(addRage, ERageChangeCause::ExecuteSkill);
	}
}

void HitHandlerDamage::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillDamageData& damageConf = skillConf->damagedata();
    SharedPtr<Skill> skill = aSkillCarrier->GetSkill();
	int64 damage = 0;
    mDamage = 0;
    if( damageConf.skipdamage() ) 
    {
		if (!mIsAccessional)
		{
			TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, 0);
		} 
        return;
    }

    bool isPhysical = skillConf->basedata().skilltunnel() == EDamageChannelPhysical;
    int damageType = damageConf.damagetype();
	SharedPtr<Unit> skillSourceUnit = aSkillCarrier->GetSkillExecutor()->GetSourceUnit();

    HitResult hitResult;
	hitResult.mIsPhysical = isPhysical;
    hitResult.mIsHit = true;
	hitResult.mDamageSpecialType = static_cast<int>(skillConf->basedata().damagespecialtype());
    hitResult.mSkillDir = aTarget->GetPosition() - aUtilizer->GetPosition();

	auto mainType = static_cast<ESkillMainType>(skillConf->basedata().maintype());
	if (mainType == ESkillMainType::ESkillMainTypeMeleeSinglePositive
		|| mainType == ESkillMainType::ESkillMainTypeMeleeSingleNegative
		|| mainType == ESkillMainType::ESkillMainTypeMeleeSingleNeutral
		|| mainType == ESkillMainType::ESkillMainTypeMeleeCrowdPositive
		|| mainType == ESkillMainType::ESkillMainTypeMeleeCrowdNegative
		|| mainType == ESkillMainType::ESkillMainTypeMeleeCrowdNeutral)
	{
		hitResult.mIsMelee = true;
	}

	if (aUtilizer->CheckStateAdjust(StateAdjust::Disable))
	{
		damage = 1;
		TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, damage);

		mDamage = damage;
		hitResult.mValue = damage;
		aTarget->Damage(hitResult, skillSourceUnit.Get(), skill.Get(), nullptr);
		RestoreObjToPool(hitResult);
		return;
	}

    int64 skillFinal = int64(damageConf.extraparam1()) + int64(damageConf.extraparam1()) * int64(skill->GetLevelMinus());

	int64 specialAdjust = DENOM;
	ESpecialAdjustTarget targetType = ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal;

	if (damageConf.has_specialadjust() && damageConf.specialadjust().enable())
	{
		auto& adjConf = damageConf.specialadjust();
		if (adjConf.has_adjusttarget())
		{
			targetType = static_cast<ESpecialAdjustTarget>(adjConf.adjusttarget());
		}
		specialAdjust = CalculateSpecialCoef(aTarget, skillConf, targetType);
	}
    
    switch(damageType)
    {
        case EDamageCalculateMethodNormal:
            damage = CalculateDamageNormal(skillSourceUnit, aTarget, skill, hitResult, specialAdjust, targetType) + skillFinal;
            break;
        case EDamageCalculateMethodMaxHpPercent:
			if (!aTarget->CheckStateAdjust(StateAdjust::DamageImmunityPercent))
			{
				//damage = aTarget->GetMaxHp() * int64(damageConf.typeparam1() + skill->GetLevelMinus()*damageConf.typeparam2()) / DENOM;
				damage = IncByRate(aTarget->GetMaxHp(), int64(damageConf.typeparam1() + skill->GetLevelMinus()*damageConf.typeparam2()), DENOM);
				damage = ApplySpecialAdjustCommon(damage, specialAdjust, targetType, ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal);
				damage = damage + skillFinal;
			}
			else
			{
				damage = skillFinal;
			}
			break;
		case EDamageCalculateMethodSelfMaxHpPercent:
			if (!aTarget->CheckStateAdjust(StateAdjust::DamageImmunityPercent))
			{
				//damage = aUtilizer->GetMaxHp() * int64(damageConf.typeparam1()) / DENOM;
				damage = IncByRate(aUtilizer->GetMaxHp(), int64(damageConf.typeparam1()) , DENOM);
				damage = ApplySpecialAdjustCommon(damage, specialAdjust, targetType, ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal);
				damage = damage + skillFinal;
			}
			else
			{
				damage = skillFinal;
			}
			break;
        case EDamageCalculateMethodCurHpPercent:
			if (!aTarget->CheckStateAdjust(StateAdjust::DamageImmunityPercent))
			{
				damage = IncByRate(aTarget->GetHp(), damageConf.typeparam1() + skill->GetLevelMinus() * damageConf.typeparam2(), DENOM);
				//damage = int64(aTarget->GetHp()) * (damageConf.typeparam1() + skill->GetLevelMinus()*damageConf.typeparam2()) / DENOM;
				damage = ApplySpecialAdjustCommon(damage, specialAdjust, targetType, ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal);
				damage = damage + skillFinal;
			}
			else
			{
				damage = skillFinal;
			}
			break;
        case EDamageCalculateMethodFixValue:
            damage = int64(damageConf.typeparam1()) + int64(skill->GetLevelMinus()) * damageConf.typeparam2() + int64(skillFinal);
            break;
        case EDamageCalculateMethodKillWhenLowHp:
            {
                int64 coef = int64(damageConf.typeparam1()) + int64(skill->GetLevelMinus()) * damageConf.typeparam2();
				int64 targetHp = IncByRate(int64(aTarget->GetMaxHp()), coef, DENOM);
				//if(int64(aTarget->GetHp())* DENOM < int64(aTarget->GetMaxHp()) * coef  )
				if (aTarget->GetHp() < targetHp)
                { 
                    damage = aTarget->GetHp(); 
                }
                else
                {
                    damage = skillFinal;
                }
            }            
            break;
        case EDamageCalculateMethodLoseHpPercent:
			if (!aTarget->CheckStateAdjust(StateAdjust::DamageImmunityPercent))
			{
				damage = IncByRate(aTarget->GetMaxHp() - aTarget->GetHp(), int64(damageConf.typeparam1() + skill->GetLevelMinus() * damageConf.typeparam2()), DENOM);
				//damage = int64(aTarget->GetMaxHp() - aTarget->GetHp()) * int64(damageConf.typeparam1() + skill->GetLevelMinus()*damageConf.typeparam2()) / DENOM;
			}
			else
			{
				damage = skillFinal;
			}
            break;
		case EDamageCalculateMethodSelfCurHpPercent:
			damage = IncByRate(aUtilizer->GetHp(), damageConf.typeparam1() + skill->GetLevelMinus() * damageConf.typeparam2(), DENOM);
			//damage = aUtilizer->GetHp() * int64(damageConf.typeparam1() + skill->GetLevelMinus()*damageConf.typeparam2()) / DENOM;
			break;
		case EDamageCalculateMethodRecordData:
			damage = aUtilizer->GetBuffRecordData(damageConf.buffid()) * (damageConf.typeparam1() + skill->GetLevelMinus()*damageConf.typeparam2()) / DENOM;
			break;
        default:
            LOG_FATAL("invalid damage calculate method:%d", damageConf.damagetype());
    }
    if( damageConf.upperlimit() 
        && ( EDamageCalculateMethodMaxHpPercent == damageType 
            || EDamageCalculateMethodCurHpPercent == damageType
            || EDamageCalculateMethodLoseHpPercent == damageType)  )
    {
        int64 baseAtk = isPhysical ? skillSourceUnit->GetPhysicalAtk() : skillSourceUnit->GetMagicAtk();
        int64 atkLimit = baseAtk * damageConf.upperlimitparam() / DENOM;
        if( damage > atkLimit )
        {
            damage = atkLimit;
        }
    }

	if (damageConf.lowerlimit()
		&& (EDamageCalculateMethodMaxHpPercent == damageType
			|| EDamageCalculateMethodCurHpPercent == damageType
			|| EDamageCalculateMethodLoseHpPercent == damageType))
	{
		int64 lowerDamage = 0;
		switch (static_cast<EDamageLimitType>(damageConf.lowerlimittype()))
		{
		case EDamageLimitFixValue:
			lowerDamage = static_cast<int64>(damageConf.lowerlimitparam());
			break;
		case EDamageLimitPhysical:
			lowerDamage = skillSourceUnit->GetPhysicalAtk() * damageConf.lowerlimitparam() / DENOM;
			break;
		case EDamageLimitMagical:
			lowerDamage = skillSourceUnit->GetMagicAtk() * damageConf.lowerlimitparam() / DENOM;
			break;
		default:
			LOG_WARN("unknow damage limit type %d", damageConf.lowerlimittype());
		}
		if (damage < lowerDamage)
		{
			damage = lowerDamage;
		}
	}

	TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, damage);

    mDamage = damage;
    hitResult.mValue = damage;
    int64 dmg = aTarget->Damage(hitResult, skillSourceUnit.Get(), skill.Get(), nullptr);
	RestoreObjToPool(hitResult);
}


int64 HitHandlerDamage::CalculateDamageNormal(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, HitResult& aHitResult, int64 aSpecialAdjust, ESpecialAdjustTarget aTargetType)
{
    BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
	if (battleInstance.NeedDoStatistics()) {
		aUtilizer->mTotalDamageBase++;
		aTarget->mTotalBeDamageBase++;
	}
    const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);

    const SkillData* skillConf = aSkill->GetSkillConf();
    const SkillBaseData& baseConf = skillConf->basedata();
    const SkillDamageData& damageConf = skillConf->damagedata();

    //bool isPhysical = baseConf.skilltunnel() == EDamageChannelPhysical;  GetAttrByCondition
	bool isPhysical = aHitResult.mIsPhysical;
	bool isPvE = battleInstance.IsPVE();

	DamageIntermediateResult intermedResult;
    if(isPhysical)
    {
        CalculateDamageCoefPhysical(aUtilizer, aTarget, aSkill, intermedResult);
    }
    else
    {
        CalculateDamageCoefMagic(aUtilizer, aTarget, aSkill, intermedResult);
    }

	if (!isPvE)
	{ //for pvp
		intermedResult.pveAmend = DENOM;
		intermedResult.pvpAmend = DENOM + aUtilizer->GetAttr(EAttribute::PVPPercentAdd) -
			aTarget->GetAttr(EAttribute::PVPPercentSub);
		if (intermedResult.pvpAmend < 2000) intermedResult.pvpAmend = 2000;
	}
	else
	{ //for pve
		intermedResult.pvpAmend = DENOM;
		intermedResult.pveAmend = DENOM + aUtilizer->GetAttr(EAttribute::PVEPercentAdd) -
			aTarget->GetAttr(EAttribute::PVEPercentSub);
		if (intermedResult.pveAmend < 2000) intermedResult.pveAmend = 2000;
	}

	intermedResult.armourPiercing = aUtilizer->GetAttr(EAttribute::UniversalArmourPiercing)
		- aTarget->GetAttr(EAttribute::UniversalArmour);
	if (intermedResult.armourPiercing < 0)
		intermedResult.armourPiercing = 0;
	intermedResult.armourPiercing = DENOM - intermedResult.armourPiercing;
	if (intermedResult.armourPiercing < 0)
		intermedResult.armourPiercing = 0;
	if (damageConf.extraarmourpiercing() > 0)
	{
		intermedResult.armourPiercing -= damageConf.extraarmourpiercing();
		if (intermedResult.armourPiercing < 0)
			intermedResult.armourPiercing = 0;
	}
	if (aSpecialAdjust < 0) 
	{  //going to modify base defandent value 
		aSpecialAdjust = -aSpecialAdjust;
		if (damageConf.isusestateadjust() 
			&& intermedResult.baseDef > 0
			&& (damageConf.skilltunnel() == EDamageChannelPhysical) == isPhysical )
		{
			intermedResult.baseDef = 0;
		}
	}

    int64 rankPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::DamageRank, aTarget, aSkill)*battleConfig->GetDamagePercentAddCoef()
                        - aTarget->GetAttrByCondition(EAttribute::AvoidInjuryRank, aUtilizer, aSkill)*battleConfig->GetDamagePercentSubCoef());

    int64 attrSkillPercent = 0;
    if( skillConf->basedata().skillcasttype().casttype() == static_cast<int>(ECastType::NormalAtk)
        || skillConf->basedata().skillcasttype().casttype() == static_cast<int>(ECastType::RandomNormalAtk) )
    {
        attrSkillPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::NormalSkillPercentAdd, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::NormalSkillPercentSub, aUtilizer, aSkill));
    }
    else
    {
        attrSkillPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::OtherSkillPercentAdd, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::OtherSkillPercentSub, aUtilizer, aSkill));
    }

    int64 skillCoef = int64(damageConf.typeparam1()) + int64(aSkill->GetLevelMinus())* int64(damageConf.typeparam2());
    skillCoef += int64(battleInstance.Rand( damageConf.typeparam3() * 2 )) - int64(damageConf.typeparam3());
	skillCoef = CurbZero(skillCoef * aSkill->mExtraDmgCoef / DENOM);

	int64 sysCoef = DENOM + aUtilizer->GetAttr(EAttribute::SystemDamage) - aTarget->GetAttr(EAttribute::SystemAvoidInjury);
	if (sysCoef < 2000) sysCoef = 2000;  //系统增减伤(军团战等使用) 
    
	int64 treasureCoef = DENOM + aUtilizer->GetAttr(EAttribute::TreasureAdd) - aTarget->GetAttr(EAttribute::TreasureSub);
	if (treasureCoef < 2000) treasureCoef = 2000;  //宝物增减伤 

	int64 countryCoef = DENOM;
	if (aTarget->mCountry != ECountry::None && aTarget->mCountry != ECountry::Master)
	{
		switch (aTarget->mCountry)
		{
		case ECountry::Wei:
			countryCoef = Min(18000, Max(2000, DENOM + aUtilizer->GetAttr(EAttribute::BreakWei) - aTarget->GetAttr(EAttribute::ResistWei)));
			break;
		case ECountry::Shu:
			countryCoef = Min(18000, Max(2000, DENOM + aUtilizer->GetAttr(EAttribute::BreakShu) - aTarget->GetAttr(EAttribute::ResistShu)));
			break;
		case ECountry::Wu:
			countryCoef = Min(18000, Max(2000, DENOM + aUtilizer->GetAttr(EAttribute::BreakWu) - aTarget->GetAttr(EAttribute::ResistWu)));
			break;
		case ECountry::Qun:
			countryCoef = Min(18000, Max(2000, DENOM + aUtilizer->GetAttr(EAttribute::BreakQun) - aTarget->GetAttr(EAttribute::ResistQun)));
			break;
		}
	}

	int64 platinumCoef = Min(18000, Max(2000, DENOM + aUtilizer->GetAttr(EAttribute::PlatinumAdd) - aTarget->GetAttr(EAttribute::PlatinumSub)));


    LOG_DEBUG("damage coef baseAtk:%d, baseDef:%d channelPercent:%d, attrPercent:%d, talentRate:%d, rankPercent:%d, attrSkillPercent:%d, skillCoef:%d adjuestByTargetNumCoef:%d", 
		intermedResult.baseAtk, intermedResult.baseDef, intermedResult.channelPercent, intermedResult.attrPercent, intermedResult.talentRate, 
		rankPercent, attrSkillPercent, skillCoef, mAdjuestByTargetNumCoef);

    /*
        （A.物理攻击总值-D.物理防御总值 * 穿甲值）
        *（1+A.物理伤害加成-D.物理伤害减免）
        *（1+A.武力*武力攻击系数-D.武力*武力防御系数）

        *（1+A.伤害加成-D.伤害减免）
        * f（技能伤害）
        * 技能系数
		* (1 + A.职业攻击天赋 - D.职业防御天赋) 
		* (1 + A.性别增伤 - D.性别减伤) 
		* (1 + A.PVP增伤 - D.PVP减伤)   <--只有在PVP模式下生效
		* (1 + A.PVE增伤 - D.PVE减伤)   <--只有在PVE模式下生效
		* (1 + A.SYS增伤 - D.SYS减伤)   <--在军团战等模式下生效 
		* (1 + A.宝物增伤 - D.宝物减伤) <--宝物系统提供 
		* (1 + f(A.国家增伤 - D.国家减伤))  
		* (1 + f(A.白金增伤 - D.白金减伤)) 

        {破防}
        *（A.物理攻击天赋-D.物理防御天赋）
    */
    int64 damage = intermedResult.baseAtk - intermedResult.baseDef * intermedResult.armourPiercing / DENOM;
	if (damage < 0) damage = 0;
    //damage += damage * intermedResult.channelPercent / DENOM;
	damage += IncByRate(damage, intermedResult.channelPercent, DENOM);

    //damage += damage * intermedResult.attrPercent / DENOM;
	damage += IncByRate(damage, intermedResult.attrPercent, DENOM);

    //damage += damage * rankPercent / DENOM;
	damage += IncByRate(damage, rankPercent, DENOM);

    //damage += damage * attrSkillPercent / DENOM;
	damage += IncByRate(damage, attrSkillPercent, DENOM);

    //damage = damage * skillCoef / DENOM;
	damage = IncByRate(damage, skillCoef, DENOM);

    //damage = damage * mAdjuestByTargetNumCoef / DENOM;
	damage = IncByRate(damage, mAdjuestByTargetNumCoef, DENOM);

	//damage = damage * intermedResult.proTalent / DENOM;
	damage = IncByRate(damage, intermedResult.proTalent, DENOM);

	//damage = damage * intermedResult.genderAmend / DENOM;
	damage = IncByRate(damage, intermedResult.genderAmend, DENOM);

	//damage = damage * intermedResult.pvpAmend / DENOM;
	damage = IncByRate(damage, intermedResult.pvpAmend, DENOM);

	//damage = damage * intermedResult.pveAmend / DENOM;
	damage = IncByRate(damage, intermedResult.pveAmend, DENOM);

	//damage = damage * sysCoef / DENOM;
	damage = IncByRate(damage, sysCoef, DENOM);

	//damage = damage * treasureCoef / DENOM;
	damage = IncByRate(damage, treasureCoef, DENOM);

	//damage = damage * countryCoef / DENOM;
	damage = IncByRate(damage, countryCoef, DENOM);

	//damage = damage * platinumCoef / DENOM;
	damage = IncByRate(damage, platinumCoef, DENOM);


    //破防
    //int64 floorDamage = intermedResult.baseAtk * battleConfig->GetFloorDamageCoef() / DENOM;
    int64 floorDamage = IncByRate(intermedResult.baseAtk, battleConfig->GetFloorDamageCoef(), DENOM);
    if ( damage  < floorDamage )
    {
        damage = floorDamage;
    }
    if(intermedResult.talentRate <= 0)
    {
        damage = 0;
    }
    //damage = damage * intermedResult.talentRate / DENOM;
    damage = IncByRate(damage, intermedResult.talentRate, DENOM);

    //爆击判断
    int64 criticalProb = 0;
	int64 criticalAddBySkill = 0;
    switch(damageConf.crittype() )
    {
        case ECritTypeNorm:
            criticalProb = aUtilizer->GetAttrByCondition(EAttribute::CriticalProb, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::AntiCriticalProb, aUtilizer, aSkill);
            break;
        case ECritTypePositive:
            criticalProb = DENOM;
            break;
        case ECritTypeAddSkillPortion:
            criticalProb = aUtilizer->GetAttrByCondition(EAttribute::CriticalProb, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::AntiCriticalProb, aUtilizer, aSkill) + damageConf.critparam();
			criticalAddBySkill = damageConf.critparam2();
			break;
        case ECritTypeOnlySkillPortion:
            criticalProb = damageConf.critparam();
			criticalAddBySkill = damageConf.critparam2();
            break;
    }
	criticalProb = ApplySpecialAdjustCommon(criticalProb, aSpecialAdjust, aTargetType, ESpecialAdjustTarget::ESpecialAdjustCrit);  //try adjust crit by coef
    if( criticalProb >= DENOM || criticalProb >= battleInstance.Rand(DENOM) )
    {
        int64 criticalPercent = criticalAddBySkill + aUtilizer->GetAttrByCondition(EAttribute::CriticalPercentAdd, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::CriticalPercentSub, aUtilizer, aSkill);
        if(criticalPercent > 0)
        {
            //damage += damage * criticalPercent / DENOM;
			damage += IncByRate(damage, criticalPercent, DENOM);
        }
        aHitResult.mIsCrit = true;
		if (battleInstance.NeedDoStatistics())
		{
			aUtilizer->mCriticalDamageCount++;
			aTarget->mBeCriticalDamageCount++;
		}
        LOG_DEBUG("skill:%d, utilizer:%d, target:%d critical. percent:%d damage:%d", 
            skillConf->id(), aUtilizer->GetEntityId(), aTarget->GetEntityId(), criticalPercent, damage);
    }
    //格挡判断
    if( damageConf.isignoreblock() == false )
    {
        int blockProb = aTarget->GetAttrByCondition(isPhysical?EAttribute::BlockProb:EAttribute::ResilienceProb, aUtilizer, aSkill)
                        - aUtilizer->GetAttrByCondition(isPhysical?EAttribute::AntiBlockProb:EAttribute::AntiResilienceProb, aTarget, aSkill)
						+ aTarget->GetAttrByCondition(EAttribute::UniversalBlockProb, aUtilizer, aSkill)
						- aUtilizer->GetAttrByCondition(EAttribute::UniversalAntiBlockProb, aTarget, aSkill);
        if( blockProb >= DENOM || blockProb >= battleInstance.Rand(DENOM) )
        {
            //damage =  damage * BattleInstance::BlockRate / DENOM; 
            damage = IncByRate(damage, BattleInstance::BlockRate, DENOM);
            aHitResult.mIsBlock = true;
			if (aHitResult.mDamageSpecialType == static_cast<int>(EDamageSpecialType::None))
			{
				aHitResult.mDamageSpecialType = static_cast<int>(EDamageSpecialType::Block);
			}
            LOG_DEBUG("skill:%d, utilizer:%d, target:%d block. damage:%d", 
                skillConf->id(), aUtilizer->GetEntityId(), aTarget->GetEntityId(), damage);
			if (battleInstance.NeedDoStatistics())
			{
				if (isPhysical)
					aTarget->mParryCount++;
				else
					aTarget->mResistCount++;
			}
        }
    }

	//special adjustment from certain skill
	damage = ApplySpecialAdjustCommon(damage, aSpecialAdjust, aTargetType, ESpecialAdjustTarget::ESpecialAdjustDmgOrHeal);

    //伤害浮动
	int fc = battleConfig->GetDamageFloatCoef();
    int floatCoef = DENOM + battleInstance.Rand(fc * 2) - fc;
	damage = IncByRate(damage, floatCoef, DENOM);
    //damage = damage * floatCoef / DENOM;

    int64 finalDamage = aUtilizer->GetFinalDamage() - aTarget->GetFinalAvoid();
    if(finalDamage > 0)
    {
        damage += finalDamage;
    }

	if (damage > BattleInstance::DamageUpLimit)
	{
		damage = BattleInstance::DamageUpLimit;  //only apply to normal damage workflow 
	}

    LOG_DEBUG("skill:%d, utilizer:%d, target:%d finaldamage. finalDamage:%d, damage:%d", 
            skillConf->id(), aUtilizer->GetEntityId(), aTarget->GetEntityId(), finalDamage, damage);

    return damage;
}



void HitHandlerDamage::CalculateDamageCoefPhysical(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, DamageIntermediateResult& aIntermedResult)
{
    const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);

	aIntermedResult.proTalent = CurbZero(DENOM + (aUtilizer->mProAttTalent - DENOM) - (aTarget->mProDefTalent - DENOM));

	aIntermedResult.genderAmend = DENOM + (aTarget->mIsMale ? aUtilizer->GetAttr(EAttribute::DamageAddPercentToMale) :
		aUtilizer->GetAttr(EAttribute::DamageAddPercentToFemale)) - (aUtilizer->mIsMale ? aTarget->GetAttr(EAttribute::DamageSubPercentToMale) :
		aTarget->GetAttr(EAttribute::DamageSubPercentToFemale));
	if (aIntermedResult.genderAmend < 2000) aIntermedResult.genderAmend = 2000;

	aIntermedResult.baseAtk = aUtilizer->GetPhysicalAtk();  //todo: add aTarget and using GetAttrByCondition
	aIntermedResult.baseDef = aTarget->GetPhysicalDef();
  
	aIntermedResult.channelPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::PhysicalPercentAdd, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::PhysicalPercentSub, aUtilizer, aSkill));
	aIntermedResult.attrPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::Force, aTarget, aSkill)*battleConfig->GetForceAtkCoef()
                    - aTarget->GetAttrByCondition(EAttribute::Force, aUtilizer, aSkill)*battleConfig->GetForceDefCoef());
	aIntermedResult.talentRate = aUtilizer->GetAttrByCondition(EAttribute::PhysicalAtkTalent, aTarget, aSkill)*battleConfig->GetPhysicsAtkCoef()
                    - aTarget->GetAttrByCondition(EAttribute::PhysicalDefTalent, aUtilizer, aSkill)*battleConfig->GetPhysicsDefCoef();
}


void HitHandlerDamage::CalculateDamageCoefMagic(SharedPtr<Unit> aUtilizer,  SharedPtr<Unit> aTarget, SharedPtr<Skill> aSkill, DamageIntermediateResult& aIntermedResult)
{
    const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);

	aIntermedResult.proTalent = CurbZero(DENOM + (aUtilizer->mProAttTalent - DENOM) - (aTarget->mProDefTalent - DENOM));

	aIntermedResult.genderAmend = DENOM + (aTarget->mIsMale ? aUtilizer->GetAttr(EAttribute::DamageAddPercentToMale) :
		aUtilizer->GetAttr(EAttribute::DamageAddPercentToFemale)) - (aUtilizer->mIsMale ? aTarget->GetAttr(EAttribute::DamageSubPercentToMale) :
		aTarget->GetAttr(EAttribute::DamageSubPercentToFemale));
	if (aIntermedResult.genderAmend < 2000) aIntermedResult.genderAmend = 2000;

	aIntermedResult.baseAtk = aUtilizer->GetMagicAtk();
	aIntermedResult.baseDef = aTarget->GetMagicDef();
  
	aIntermedResult.channelPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::MagicPercentAdd, aTarget, aSkill) - aTarget->GetAttrByCondition(EAttribute::MagicPercentSub, aUtilizer, aSkill));
	aIntermedResult.attrPercent = CurbRate(aUtilizer->GetAttrByCondition(EAttribute::Intelligence, aTarget, aSkill)*battleConfig->GetIntelligenceAtkCoef()
                        - aTarget->GetAttrByCondition(EAttribute::Intelligence, aUtilizer, aSkill)*battleConfig->GetIntelligenceDefCoef());
	aIntermedResult.talentRate = aUtilizer->GetAttrByCondition(EAttribute::MagicAtkTalent, aTarget, aSkill) * battleConfig->GetMagicAtkCoef()
                        - aTarget->GetAttrByCondition(EAttribute::MagicDefTalent, aUtilizer, aSkill) * battleConfig->GetMagicDefCoef();
}


int64 HitHandlerDamage::CalculateSpecialCoef(SharedPtr<Unit> aTarget, const SkillData* aSkillConf, const ESpecialAdjustTarget aTargetType)
{
	auto& damageConf = aSkillConf->damagedata();
	if (!damageConf.has_specialadjust())
		return DENOM;
	auto& adjConf = damageConf.specialadjust();

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
		//LOG_WARN("invalid damage special adjust buffParam size:%d", adjConf.buffparam_size());
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
	int rawCoef = adjList.Get(adjConf.adjustdata_size() - 1);
	for (int i = 0; i < adjList.size(); i+=2)
	{
		if (layer <= adjList.Get(i))
			rawCoef = adjList.Get(i + 1);
		else
			break;
	}

	switch (aTargetType)
	{
	case ESpecialAdjustCrit:
		return rawCoef;
	case ESpecialAdjustDmgOrHeal:
		return rawCoef + DENOM;
	default:
		LOG_FATAL("ileagle adjust type[%d]", int(aTargetType));
		return DENOM;
	}

	return DENOM;
}


void HitHandlerDamage::AfterHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{

	const SkillData* skillConf = aSkillCarrier->GetSkillConf();
	const SkillDamageData& effectConf = skillConf->damagedata();
	int effNum = aEffTargetArr.size();
	if (effectConf.healbyeffnum() && effNum > 0)
	{
		int64 healRate = aUtilizer->GetAttr(EAttribute::HealPercentAdd) + aUtilizer->GetAttr(EAttribute::BeHealPercentAdd);
		if (healRate <= 0) return;
		HitResult hitResult;
		hitResult.mIsHit = true;
		hitResult.mIsPhysical = skillConf->basedata().skilltunnel() == EDamageChannelPhysical;
		int64 coef = effectConf.healcoefficient();
		int64 atk = 0;
		if (hitResult.mIsPhysical)
		{
			atk = aUtilizer->GetPhysicalAtk();
		}
		else
		{
			atk = aUtilizer->GetMagicAtk();
		}
		hitResult.mValue = atk * coef / DENOM * effNum ;
		if (hitResult.mValue < 0)
			hitResult.mValue = 0;
		int64 originHeal = hitResult.mValue;
		int64 realHeal = aUtilizer->Heal(hitResult, aUtilizer.Get(), aSkillCarrier->GetSkill().Get(), nullptr);
		if (effectConf.buffid2() > 0 && realHeal < originHeal)
		{ //如果 buffid2 有值，说明需要将溢出治疗量记录到 治疗承受者 身上的给定buff上 
			aUtilizer->OnHealOverflow(effectConf.buffid2(), originHeal - realHeal);
		}
	}

}
