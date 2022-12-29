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

#include "HitHandler.h"
#include "HitHandlerDamage.h"
#include "HitHandlerHeal.h"
#include "HitHandlerSummon.h"
#include "HitHandlerMove.h"
#include "HitHandlerSuckBlood.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "BattleInstance.h"



SharedPtr<HitHandler> NewHitHandler(ESkillSubType aSkillSubType)
{
    switch(aSkillSubType)
    {
        case ESkillSubTypeDamage:
            return SharedPool<HitHandlerDamage>::Get();
		case ESkillSubTypeDamageBeheaded:
			return SharedPool<HitHandlerDamage>::Get();
        case ESkillSubTypeHeal:
            return SharedPool<HitHandlerHeal>::Get();
        case ESkillSubTypeSummon:
            return SharedPool<HitHandlerSummon>::Get();
        case ESkillSubTypeMove:
            return SharedPool<HitHandlerMove>::Get();
        case ESkillSubTypeSuckBlood:
            return SharedPool<HitHandlerSuckBlood>::Get();
        default:
            LOG_FATAL("invalid skillSubType:%d", aSkillSubType);
    }
    return nullptr;
}

void HitHandler::Reset()
{
	mIsDurative = false;
	mIsAccessional = false;
	if (mDmgOrHealHandler)
		mDmgOrHealHandler.Release();
}

bool HitHandler::CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
	return DefaultHitDecision(aUtilizer, aTarget, aSkillCarrier);
}


bool HitHandler::DefaultHitDecision(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
    const SkillData* skillConf = aSkillCarrier->GetSkillConf();
    const SkillBaseData& baseConf = skillConf->basedata();
    const SkillHitData& hitConf = skillConf->hitdata();
	auto skill = aSkillCarrier->GetSkill();

    bool isPhysical = baseConf.skilltunnel() == EDamageChannelPhysical;

	if (!aTarget->IsDummy() && aTarget->IsImmueToSkill(skillConf->id(), ESkillSubType(skillConf->basedata().subtype()) ))
	{
		LOG_DEBUG("unit:%d immueskill:%d from %d", aTarget->GetEntityId(), skillConf->id(), aUtilizer->GetEntityId());
		return false;
	}
	
	/*
	if (aUtilizer != aTarget && aTarget->IsImmunityBySkillStatus())
	{
		LOG_DEBUG("unit:%d immueskill:%d from %d, because of executing non-listenbreak skill", aTarget->GetEntityId(), skillConf->id(), aUtilizer->GetEntityId());
		return false;
	}
	*/
    //命中判断 
    if( hitConf.hitforsure() == false )
    {
        int hitProb = aUtilizer->GetAttrByCondition(isPhysical?EAttribute::PhysicalHitProb:EAttribute::MagicHitProb, aTarget, skill)
                - aTarget->GetAttrByCondition(isPhysical?EAttribute::DodgeProb:EAttribute::ExemptionProb, aUtilizer, skill)
				+ aUtilizer->GetAttrByCondition(EAttribute::UniversalHitProb, aTarget, skill) - aTarget->GetAttrByCondition(EAttribute::UniversalDodgeProb, aUtilizer, skill);
        if( hitProb <= 0 || hitProb < battleInstance.Rand(DENOM) )
        {
            LOG_DEBUG("Skill {id=%d utilizer:%d} dodged by target:%d", skillConf->id(), aUtilizer->GetEntityId(), aTarget->GetEntityId());
			if (baseConf.skilltunnel() == EDamageChannelPhysical)
			{
				aTarget->OnDodge(aUtilizer, skillConf->id());
				if (battleInstance.NeedDoStatistics())
				{
					aTarget->mPhysicalBase++;
					aTarget->mDodgeCount++;
				}
			}
			else
			{
				aTarget->OnExemption(aUtilizer);
				if (battleInstance.NeedDoStatistics())
				{
					aTarget->mMagicalBase++;
					aTarget->mExemptionCount++;
				}
			}
            return false;
        }
		else
		{
			if (battleInstance.NeedDoStatistics())
			{
				if (baseConf.skilltunnel() == EDamageChannelPhysical)
					aTarget->mPhysicalBase++;
				else
					aTarget->mMagicalBase++;
			}
		}
    }

    return true;
}

void HitHandler::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    if(mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
}


void HitHandler::Init(SharedPtr<Unit> aUtilizer, SharedPtr<Skill> aSkill)
{
    const SkillData* skillConf = aSkill->GetSkillConf();
    const SkillBaseData& baseConf = skillConf->basedata();
	mIsAccessional = false;
    if(ESkillSubTypeDamage == baseConf.subtype()
    || ESkillSubTypeHeal == baseConf.subtype() )
    {
        return;
    }
    if( skillConf->has_damagedata() && !skillConf->damagedata().skipdamage())
    {
        mDmgOrHealHandler = SharedPool<HitHandlerDamage>::Get();
		mDmgOrHealHandler->SetIsAccessional(true);
    }
    else if( skillConf->has_healdata() )
    {
        mDmgOrHealHandler = SharedPool<HitHandlerHeal>::Get();
		mDmgOrHealHandler->SetIsAccessional(true);
    }
    else
    {
        //LOG_WARN("need set damage or heal");
    }
}

void HitHandler::RelaseDmgOrHealHandler()
{
	if (mDmgOrHealHandler)
		mDmgOrHealHandler.Release();
}


void HitHandler::TriggerOnHitEvent(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier, int64 aDamage)
{
	if (aTarget->IsRefDummy() || aTarget->IsDead())
	{
		return;
	}
	const SkillData* skillConf = aSkillCarrier->GetSkillConf();
	const SkillEffectData& effectConf = skillConf->effectdata();

	int skillLevel = aSkillCarrier->GetSkill()->GetLevel();
	SharedPtr<Unit> sourceUtilizer = aSkillCarrier->GetSkillExecutor()->GetSourceUnit();

	//检查是否能打断 
	bool isPhysical = skillConf->basedata().skilltunnel() == EDamageChannelPhysical;
	int energyLv = aSkillCarrier->GetSkill()->mEnergyLv;
	bool ableToInterrupt = aTarget->AbleToInterrupt(energyLv, isPhysical);

	//加buff 
	auto ancestorSkill = aSkillCarrier->GetSkill()->GetAncestorSkill();

	bool found = false;
	for (int i = effectConf.levelsubbuff_size() - 1; i >= 0; i--)
	{ //先看看是否有技能关联的buff需要释放 
		auto& levelSubBuffInfo = effectConf.levelsubbuff(i);
		if (levelSubBuffInfo.level() <= skillLevel)
		{
			for (size_t j = 0; j < levelSubBuffInfo.id_size(); j++)
			{
				aTarget->TryReceiveBuff(aUtilizer, sourceUtilizer, levelSubBuffInfo.id(static_cast<int>(j)), skillLevel, ancestorSkill, 0, ableToInterrupt);
				found = true;
			}
			break;
		}
	}
	if (!found)
	{ //没有的话在看看默认配置里的buff 
		for (int i = 0; i < effectConf.addbuffid_size(); i++)
		{
			aTarget->TryReceiveBuff(aUtilizer, sourceUtilizer, effectConf.addbuffid(i), skillLevel, ancestorSkill, 0, ableToInterrupt);
		}
	}

    if (ancestorSkill->mArcherParam.IsValid)
    {
        //弓箭传奇主角技能的额外buff 
        auto& list = ancestorSkill->mArcherParam.GetBuffIds();
        for (auto id : list)
        {
            aTarget->TryReceiveBuff(aUtilizer, sourceUtilizer, id, skillLevel, ancestorSkill, 0, ableToInterrupt);
        }
    }

	//skip hit logic if not able to interrupt 
	if (!ableToInterrupt)
		return;

	if (skillConf->basedata().interruptbossskill())
	{
		aTarget->TryInterruptBossSkill();
	}

	const SkillHitData& hitConf = skillConf->hitdata();
	//是否进去受击状态 
	//bool enterBeHitState = false;
	BeHitType enterBeHitState = BeHitType::None;
	switch (hitConf.hiteffectplaytype())
	{
	case EHitEffectPlayTypePositive:
		//enterBeHitState = true;
		enterBeHitState = BeHitType::Hit;
		break;
	case EHitEffectPlayTypeByLostdHp:
        int64 tarDmg = IncByRate(aTarget->GetMaxHp(), int64(hitConf.hiteffectplayparam()), DENOM);
		//if (int64(aDamage * DENOM) > int64(aTarget->GetMaxHp()) * int64(hitConf.hiteffectplayparam()))
		if (aDamage > tarDmg)
		{
			enterBeHitState = BeHitType::Hit;
		}
		break;
	}
	if (enterBeHitState != BeHitType::None && hitConf.playdownanim())
	{
		enterBeHitState = BeHitType::Down;
	}
	else if (enterBeHitState != BeHitType::None && skillConf->movedata().allowreplaceanim())
	{
		//skillConf->movedata().has_allowreplaceanim() &&
		enterBeHitState = BeHitType::Knock;
	}

	bool needSkipDmg = skillConf->damagedata().skipdamage();
	if (aDamage == 0)
	{  //for heal handler, dmg = 0 
		needSkipDmg = true;
	}
	aTarget->OnHit(aUtilizer, skillConf->id(), enterBeHitState, needSkipDmg);
}




void EmbattleRectangleInRelativeDiretion(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aRefPos, Vector3& aForward, 
                EEmbattleRelativeDirection aRelDir, int64 aRelDist, int aColNum, int64 aRowGap, int64 aColGap, int64 aVerticalPos)
{
    int unitNum = static_cast<int>(aUnitArr.size());
    int rowNum = unitNum / aColNum;
    if (unitNum % aColNum > 0)
    {
        rowNum++;
    }

    Vector3 right( aForward.z, 0, -aForward.x );

    int row = 0;
    int col = 0;
    int halfColNum = aColNum / 2;
    int halfCol = 0;
    Vector3 delt;
    Vector3 pos;

    //计算中心点的位置 
    Vector3 centerPos(aRefPos);
    switch( aRelDir )
    {
        case EEmbattleRelativeDirectionBackward:   
            delt = aForward;
            delt.ScaleToLen( -aRelDist - aRowGap * (rowNum - 1) / 2 );                
            break;
        case EEmbattleRelativeDirectionForward:
            delt = aForward;
            delt.ScaleToLen( aRelDist + aRowGap * (rowNum - 1) / 2 ); 
            break;
        case EEmbattleRelativeDirectionLeft:
            delt = right;
            delt.ScaleToLen( -aRelDist - aColGap * (aColNum - 1) / 2);            
            break;
        case EEmbattleRelativeDirectionRight:
            delt = right;
            delt.ScaleToLen( aRelDist + aColGap * (aColNum - 1) / 2 );            
            break;
        case EEmbattleRelativeDirectionSurround:
            
            break;
    }
    centerPos += delt;

    int j = 0;
    for(int i = 0; i < unitNum; i++)
    {
        row = i / aColNum;
        col = i % aColNum;
        /*每一行中，需要从中间开始放人： 
                1, 0, 2
                4, 3, 5
          变换公式： floor( aColNum/2 ) + floor( (col+1)/2 ) - ( col % 2 ) * ( col + 1)
        */
        halfCol = (col + 1)/2;
        col  = halfColNum + halfCol -  ( col % 2 )*(col + 1);

        pos = centerPos;
        delt = right;
        delt.ScaleToLen( (2*col - aColNum + 1) * aColGap / 2 );
        pos += delt;

        delt = aForward;
        delt.ScaleToLen( (-2*row + rowNum - 1) * aRowGap / 2 );
        pos += delt;

		Vector3 tmpPos = Vector3(pos.x, aVerticalPos, pos.z);
		aUnitArr[i]->InitLocation(tmpPos, aForward);
    }
}


void EmbattleRectangleSurround(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aCenterCellPos, Vector3& aForward,
                    bool aForwardTarget, int aColNum, int64 aRowGap, int64 aColGap, int64 aVerticalPos)
{
    int unitNum = static_cast<int>(aUnitArr.size());
    int rowNum = unitNum / aColNum;
    if (unitNum % aColNum > 0)
    {
        rowNum++;
    }
    Vector3 right( aForward.z, 0, -aForward.x );

    int row = 0;
    int col = 0;
    int halfColNum = aColNum / 2;
    int halfCol = 0;
    Vector3 delt;
    Vector3 pos;

    //被包围的对象，默认放在中间cell 
    int centerRow = rowNum / 2;
    int centerCol  = aColNum / 2;
    int centerCellIndex = centerRow*aColNum;

    int j = 0;
    for(int i = 0; i < unitNum; i++)
    {
        j = i >= centerCellIndex ? (i+1) : i; //如果是包围目标，需要把中间的cell留出来 
        row = j / aColNum;
        col = j % aColNum;
        /*每一行中，需要从中间开始放人： 
                1, 0, 2
                4, 3, 5
          变换公式： floor( aColNum/2 ) + floor( (col+1)/2 ) - ( col % 2 ) * ( col + 1)
        */
        halfCol = (col + 1)/2;
        col  = halfColNum + halfCol -  ( col % 2 )*(col + 1);

        pos = aCenterCellPos;
        delt = right;
        delt.ScaleToLen( (col - centerCol) * aColGap );
        pos += delt;

        delt = aForward;
        delt.ScaleToLen( (centerRow - row) * aRowGap );
        pos += delt;

        Vector3 forward = aForward;
        if( aForwardTarget )
        {
            forward = aCenterCellPos - pos;
        }
		Vector3 tmpPos = Vector3(pos.x, aVerticalPos, pos.z);
		aUnitArr[i]->InitLocation(tmpPos, forward);
    }
}

void EmbattleVector(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aRefPos, Vector3& aForward, 
	bool aForwardTarget, const vector<int64>& aVectorArr, int64 aVerticalPos)
{
	Vector3 forward(aForward);
	Vector3 right(forward.z, 0, -forward.x);
	Vector3 centerPos(aRefPos);

	Vector3 tarPos;
	Vector3 deltaZ;
	for (int idx = 0; idx < aUnitArr.size(); idx++)
	{
		int64 dX = aVectorArr[idx * 2];
		int64 dZ = aVectorArr[idx * 2 + 1];

		tarPos.Set(forward);
		tarPos.ScaleToLen(dX);

		deltaZ.Set(right);
		deltaZ.ScaleToLen(dZ);

		tarPos += centerPos;
		tarPos += deltaZ;

		tarPos.y = aVerticalPos;

		forward.Set(aForward);
		if (aForwardTarget)
		{
			forward = centerPos - tarPos;
		}

		aUnitArr[idx]->InitLocation(tarPos, forward);
	}
}

void EmbattleCircle(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aRefPos, Vector3& aForward, 
                   EEmbattleRelativeDirection aRelDir, int64 aRelDist, bool aForwardTarget, 
				   int64 aFirstRadius, int64 aUnitRadius, int64 aVerticalPos)
{
    int unitNum = static_cast<int>(aUnitArr.size());
    const int angleBase = 100;
	if (aFirstRadius < aRelDist)
		aFirstRadius = aRelDist;

    //先以原点为中心放，等放完知道整体的大小，然后再平移到目标地点 

    int numInOneCircle;
    int64 angleDelt, angle, cos, sin;
    int64 radius = aFirstRadius - aUnitRadius - aUnitRadius;
    Vector3 forward(aForward);
    Vector3 delt;
    int index = 0;
    //一个循环放一圈 
    while(index < unitNum)
    {
        radius += aUnitRadius + aUnitRadius;
        //sin = aUnitRadius * DENOM / radius;
        //numInOneCircle = static_cast<int>(180*angleBase / ArcsinInt( sin, DENOM, angleBase));
		numInOneCircle = unitNum;
        angleDelt = 360 * angleBase / numInOneCircle;

        forward.ScaleToLen(radius); 
        for(int i = 1; i <= numInOneCircle && index < unitNum; i++)
        {
            int j  =  i / 2;
            angle = j * angleDelt * (1 - i%2*2);//按照从前面中间开始，往两边依次排布 
            cos = CosineInt(angle, angleBase, DENOM);
            sin  = CosineInt(90 * angleBase - angle, angleBase, DENOM);
            delt.x = (forward.x * cos - forward.z * sin) / DENOM;
            delt.y = forward.y;
            delt.z = (forward.x * sin + forward.z * cos) / DENOM;
            aUnitArr[index]->SetPosRot(delt, delt, false);
            index++;
        } 
    }
    
    //计算中心点的位置 
    Vector3 right( aForward.z, 0, -aForward.x );
    Vector3 centerPos(aRefPos);
    switch( aRelDir )
    {
        case EEmbattleRelativeDirectionBackward:   
            delt = aForward;
            delt.ScaleToLen( -radius - aRelDist );                
            break;
        case EEmbattleRelativeDirectionForward:
            delt = aForward;
            delt.ScaleToLen( radius + aRelDist );          
            break;
        case EEmbattleRelativeDirectionLeft:
            delt = right;
            delt.ScaleToLen( -radius - aRelDist);            
            break;
        case EEmbattleRelativeDirectionRight:
            delt = right;
            delt.ScaleToLen( radius + aRelDist );        
            break;
        case EEmbattleRelativeDirectionSurround: 
            delt.x = 0;
            delt.y = 0;           
            delt.z = 0;
            break;
    }
    centerPos += delt;

    for(size_t i = 0; i < unitNum; i++)
    {
        delt = aUnitArr[i]->GetPosition();
        delt += centerPos;
        
        forward = aForward;
        if(aForwardTarget)
        {
            forward = centerPos - delt;
        }
		Vector3 tmpPos = Vector3(delt.x, aVerticalPos, delt.z);
		aUnitArr[i]->InitLocation(tmpPos, forward);
    }
}