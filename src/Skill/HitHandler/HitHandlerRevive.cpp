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


#include "HitHandlerRevive.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"
#include "ConfigMgr/ConfigMgr.h"



void HitHandlerRevive::Reset()
{
	HitHandler::Reset();
    RelaseDmgOrHealHandler();
    mRevivedUnitArr.clear();
};


bool HitHandlerRevive::CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
	if (aTarget->CheckStateAdjust(StateAdjust::NoRevive))
	{
		return false;
	}
	auto& battleInstance = aTarget->GetBattleInstance();
	if (!battleInstance.CanReviveTD(aTarget->GetArmyId()))
	{
		return false;
	}
	return DefaultHitDecision(aUtilizer, aTarget, aSkillCarrier);
}

void HitHandlerRevive::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
    mRevivedUnitArr.clear();
}

void HitHandlerRevive::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillRebornData& reviveConf = skillConf->reborndata();
    SharedPtr<Skill> skill = aSkillCarrier->GetSkill();

    int hp = 0;
    switch( reviveConf.lifetype() )
    {
        case EReviveHpTypeMaxHpPercent:
            hp = IncByRate(aTarget->GetMaxHp(), reviveConf.lifeparam1() + skill->GetLevelMinus() * reviveConf.lifeparam2(), DENOM);
            //hp = aTarget->GetMaxHp() * ( reviveConf.lifeparam1() + skill->GetLevelMinus()*reviveConf.lifeparam2() )  / DENOM  ;
            break;
        case EReviveHpTypeFixValue:
            hp = reviveConf.lifeparam1() + skill->GetLevelMinus()*reviveConf.lifeparam2();
    }

    if(hp <= 0)
    {
        //策划说即使是在百分比的情况下，也不能为0，直接报错 
        LOG_FATAL("skill:%d revive id:%d hp:0", skillConf->id(), aTarget->GetEntityId() );
    }

    int lifeTime = reviveConf.lasttimetype() > 0 ? -1 : reviveConf.lasttimeparam();

    aTarget->Revive(hp, lifeTime, reviveConf.canoverscreen(), reviveConf.resetcooldown());
    mRevivedUnitArr.emplace_back(aTarget);

	if (mDmgOrHealHandler)
	{
		mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
	}
	else
	{
		TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, 0);
	}
}



void HitHandlerRevive::AfterHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{

    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillRebornData& reviveConf = skillConf->reborndata();
    const ConfigBattleConfig* battleConfig = ConfigMgr::GetConfById<ConfigBattleConfig>(1);

    if(  reviveConf.positon() == EReviveSkillPositionDeathPlace)
    {
        //只要死的时候，尸体不会有移动，这里就啥也不用做
        return;
    }
    if(  reviveConf.positon() == EReviveSkillPositionBirthPlace)
    {
        for(size_t i = 0; i < mRevivedUnitArr.size(); i++)
        {
            //mRevivedUnitArr[i]->SetPosition(); TODO  
        }
        return;
    }

    //以施法者为参考排布
    int64 maxRadius = 0;
    int64 bodySize;
    for( size_t i = 0; i < mRevivedUnitArr.size(); i++)
    {
        bodySize = mRevivedUnitArr[i]->GetSize();
        if( maxRadius < bodySize)
        {
            maxRadius = bodySize;
        }
    }
    
    Vector3 center = aUtilizer->GetPosition();
    Vector3 forward = aUtilizer->GetForward(); 
    EEmbattleRelativeDirection relDir = EEmbattleRelativeDirectionSurround;
    switch( reviveConf.positon() )
    {
        case EReviveSkillPositionUtilizerBackward:
            relDir = EEmbattleRelativeDirectionBackward;
            break;
        case EReviveSkillPositionUtilizerForward:
            relDir = EEmbattleRelativeDirectionForward;
            break;
        case EReviveSkillPositionUtilizerSurround:
            relDir = EEmbattleRelativeDirectionSurround;
            break;
    }

    if(  reviveConf.formation() == EReviveSkillFormationRectangle)
    {                
        if( reviveConf.positon() == ESummonSkillBirthPlaceEffTargetSurround )
        {
            //如果目标是地方，就让召唤物朝向目标
            EmbattleRectangleSurround(mRevivedUnitArr, center, forward, false, 
                         battleConfig->GetDefaultColNum(), maxRadius*2, maxRadius*2);
        }
        else
        {
            EmbattleRectangleInRelativeDiretion(mRevivedUnitArr, center, forward, relDir, reviveConf.mindistance(), 
                    battleConfig->GetDefaultColNum(), maxRadius*2, maxRadius*2);
        }        
    }
    else //ESummonSkillFormationCircle
    {
        EmbattleCircle(mRevivedUnitArr, center, forward, relDir, reviveConf.mindistance(), 
                        false, battleConfig->GetDefaultRadius(), maxRadius );
    }

    mRevivedUnitArr.clear();
}

