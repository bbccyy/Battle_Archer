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


#include "HitHandlerSummon.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "BattleInstance.h"
#include "ConfigMgr/ConfigMgr.h"



void HitHandlerSummon::Reset()
{
	HitHandler::Reset();
    RelaseDmgOrHealHandler();
};


void HitHandlerSummon::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
}


void HitHandlerSummon::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillSummonData& summonConf = skillConf->summondata();

    if(!summonConf.usereftargetasblueprint() && summonConf.id_size() != summonConf.num_size() )
    {
        LOG_FATAL("invalid conf. skill:%d  summonConf.id:%d  summonConf.num:%d", 
                skillConf->id(), summonConf.id_size(), summonConf.num_size() );
    }
    vector<SharedPtr<Unit> > unitArr;
    int64 maxRadius = 0;
    int skillLevel = aSkillCarrier->GetSkill()->GetLevel();
	SharedPtr<Unit> sourceUtilizer = aSkillCarrier->GetSkillExecutor()->GetSourceUnit();
    int inheritPercent = 0;
    if (summonConf.inheritattribute() || summonConf.inheritattributefromreftarget())
    {
        inheritPercent = summonConf.inheritpercentage();
    }
	Unit* attrUnit = aUtilizer.Get();
	if (summonConf.inheritattributefromreftarget() && aSkillCarrier->GetRefTarget().GetType() == ERefTargetType::Unit)
	{
		attrUnit = aSkillCarrier->GetRefTarget().GetUnit().Get();
	}
	if (summonConf.inheritattributefromancestor() && aSkillCarrier->GetSkill()->mAncestorSkill)
	{
		attrUnit = aSkillCarrier->GetSkill()->mAncestorSkill->GetOwner().Get();
	}
	bool ripOld = false;
	bool provideKillRage = true;
	if (summonConf.has_isnokillragebonus())
		provideKillRage = !summonConf.isnokillragebonus();
	int maxNum = summonConf.maxsameidunit();
	if (summonConf.has_deletesameidunit())
	{
		ripOld = summonConf.deletesameidunit();
	}

	WeakPtr<Skill> ancestorSkill = aSkillCarrier->GetSkill()->GetAncestorSkill();
    for(int i = 0; i < summonConf.id_size(); i++)
    {
        int tplId = summonConf.id(i);
		if (summonConf.usereftargetasblueprint() 
			&& aSkillCarrier->GetRefTarget().GetType() == ERefTargetType::Unit)
		{
			tplId = aSkillCarrier->GetRefTarget().GetUnit()->GetTplId();
		}
		vector<Unit*> vec;
		aUtilizer->GetArmy().GetSummonedUnit(aUtilizer.Get(), tplId, vec);
		int existingNum = vec.size();
        int slot = maxNum - existingNum;
		if (ripOld)
		{ //modi slot if rip Old
			DieCause dieCause;
			dieCause.cause = EUnitDieCause::Timeout;
			for (auto unit : vec)
			{
				unit->Die(dieCause);
			}
			slot = maxNum;
		}

		if (slot <= 0)
			continue;

        int num = summonConf.num(i);
        if (num > slot)
            num = slot;
        int level = 1;
		int leveltype = summonConf.leveltype();
        switch(leveltype)
        {
            case ESummonLevelMethodByUtilizerLevel:
                level = aUtilizer->GetLevel() * summonConf.levelparam() / DENOM;
                break;
            case ESummonLevelMethodByTargetLevel:
                level = aTarget->GetLevel() * summonConf.levelparam() / DENOM;
                break;
            case ESummonLevelMethodSetValue:
                level = summonConf.levelparam();
                break;
			case ESummonLevelMethodBossGrowth:
				level = battleInstance.GetBossGrowthLevel(aUtilizer->GetArmyId());
				break;
			default:
				LOG_WARN("unknown leveltype %d when summon unit", leveltype);
        }
        if( level < 1)
        {
            level  = 1;
        }
        int lifeTime = summonConf.lasttimetype() > 0 ? -1 : summonConf.lasttimeparam();
        int summonNum = 0;
		SharedPtr<Unit> summonUnit;
        for( summonNum = 0; summonNum < num; summonNum++)
        {
            summonUnit = aUtilizer->GetArmy().SummonUnit(tplId, level, skillLevel, 0, lifeTime, attrUnit->GetAdvLevel(), summonConf.canoverscreen(), attrUnit, inheritPercent, ancestorSkill, aUtilizer.Get(), summonConf.usefixedrate());
			summonUnit->mProvideKillRage = provideKillRage;
			unitArr.emplace_back(summonUnit);
        }        
        if(summonNum > 0)
        { 
            if( maxRadius < summonUnit->GetSize())
            {
                maxRadius = summonUnit->GetSize();
            }
        }
    }

    const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);

    Vector3 center = aTarget->GetPosition(); 
    Vector3 forward = aTarget->GetForward(); 
    EEmbattleRelativeDirection relDir;
	auto posConf = summonConf.positon();
    switch(posConf)
    {
        case ESummonSkillBirthPlaceEffTargetBackward: 
            relDir = EEmbattleRelativeDirectionBackward;
            break;
        case ESummonSkillBirthPlaceEffTargetForward:
            relDir = EEmbattleRelativeDirectionForward;          
            break;
        case ESummonSkillBirthPlaceEffTargetLeft:
            relDir = EEmbattleRelativeDirectionLeft;         
            break;
        case ESummonSkillBirthPlaceEffTargetRight:
            relDir = EEmbattleRelativeDirectionRight;  
            break;
		case ESummonSkillBirthPlaceEffTargetSurround:
			relDir = EEmbattleRelativeDirectionSurround;
			break;
		default:
			LOG_FATAL("invalid summon position:%d skillId:%d", posConf, skillConf->id());
    }

	int64 vp = CONF_POS_CONVERT(summonConf.verticalposition());

	auto fm = summonConf.formation();
    if(fm == ESummonSkillFormationRectangle)
    {        
        if(posConf == ESummonSkillBirthPlaceEffTargetSurround )
        {
            //如果目标是敌方，就让召唤物朝向目标
            EmbattleRectangleSurround(unitArr, center, forward, aUtilizer->IsEnemy(aTarget), 
                    battleConfig->GetDefaultColNum(), maxRadius*2, maxRadius*2, vp);
        }
        else
        {
            EmbattleRectangleInRelativeDiretion(unitArr, center, forward, relDir, CONF_POS_CONVERT(summonConf.mindistance()), 
                    battleConfig->GetDefaultColNum(), maxRadius*2, maxRadius*2, vp);
        }        
    }
    else if (fm == ESummonSkillFormationCircle) 
    {
        bool forwardTarget = (posConf == ESummonSkillBirthPlaceEffTargetSurround)  &&  aUtilizer->IsEnemy(aTarget);
        EmbattleCircle(unitArr, center, forward, relDir, CONF_POS_CONVERT(summonConf.mindistance()),
                    forwardTarget, CONF_POS_CONVERT(battleConfig->GetDefaultRadius()), maxRadius, vp);
    }
	else  //ESummonSkillFormationVector
	{
		int posVecSize = summonConf.positionvectorarr().size();
		vector<int64> tmp;
		tmp.reserve(posVecSize);
		for (auto d : summonConf.positionvectorarr())
		{
			tmp.emplace_back(CONF_POS_CONVERT(d));
		}
		int rest = posVecSize - 2 * unitArr.size();
		if (rest < 0)
		{
			LOG_WARN("Invalid position vector arr size when summon unit using vector! skill id = %d, deltaSize = %d", skillConf->id(), rest);
			while (rest++ < 0) tmp.emplace_back(0);
		}
		EmbattleVector(unitArr, center, forward, false, tmp);
	}

	//加buff需要保证在设置了出生点和朝向之后，不然会引发预料不到的bug 
	for (auto summonUnit : unitArr)
	{
		for (int i = 0; i < summonConf.addbuffid_size(); i++)
		{
			summonUnit->TryReceiveBuff(aUtilizer, sourceUtilizer, summonConf.addbuffid(i), skillLevel, ancestorSkill);
		}
		summonUnit->OnBeSummoned();
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



