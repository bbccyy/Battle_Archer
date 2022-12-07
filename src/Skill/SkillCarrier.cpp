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
#include "BattleInstance.h"
#include "SkillCarrier.h"
#include "SkillExecutor.h"
#include "Skill/SkillProjectile/SkillProjectile.h"
#include "Framework/SharedPool.h"
#include "SkillExecutor.h"
#include "Skill.h"
#include "Skill/HitHandler/HitHandler.h"
#include "SearchTarget.h"
#include "Log/Log.h"
#include "Entity/Unit.h"
#include "View/BattleViewOutput.h"
#include "Framework/Util.h"

int SkillCarrier::Init(SharedPtr<Unit> aOwner, SharedPtr<SkillExecutor> aSkillExecutor, const Vector3& aStartPos, RefTarget& aRefTarget )
{
    mOwner = aOwner;
    mSkillExecutor = aSkillExecutor;
    mRefTarget.Set(aRefTarget);

    mSkillConf = mSkillExecutor->GetSkillConf();
	mStatus = ESkillCarrierStatus::Running;

    mProjectile = nullptr;
    if( mSkillConf->curvadata().iscurve() )  // has projectile or not
    {
        mProjectile = NewSkillProjectile(SharedFromThis(), aStartPos, aRefTarget);
		mNeedTickProjectile = true;        
    }
    else
    {
		mNeedTickProjectile = false;
		OnReachRefTarget(mRefTarget);
    }
    
    return 0;
}

void SkillCarrier::Reset()
{
	if (mProjectile) mProjectile.Release();
	if (mOwner) mOwner.Release();
	if (!mSkillExecutor)
	{
		LOG_WARN("fail to find skill executor when reset carrier");
		return;
	}
	SharedPtr<Skill> skill = mSkillExecutor->GetSkill();
	for (auto iter = mHitHandlerList.begin(); iter != mHitHandlerList.end(); iter++)
	{
		skill->ReturnHitHandler(*iter);
	}
	mHitHandlerList.clear();
	if (mSkillExecutor)
		mSkillExecutor.Release();
	mRefTarget.Reset();
	mSkillConf = nullptr;
	mNeedTickProjectile = false;
	mStatus = ESkillCarrierStatus::End;
}

bool SkillCarrier::IsEnded() const
{
    return mStatus == ESkillCarrierStatus::End;
}

bool SkillCarrier::OnTick(int aDeltaTime)
{
	if (mNeedTickProjectile)
	{
		if (mProjectile->OnTick(aDeltaTime) == false)
		{
			mProjectile->ClearView();
			mNeedTickProjectile = false;
		}
	}
	if ( !mHitHandlerList.empty() )
	{
		auto iter = mHitHandlerList.begin();
		while (iter != mHitHandlerList.end())
		{
			if ( (*iter)->OnTick(aDeltaTime))
			{
				iter++;
			}
			else
			{
				mSkillExecutor->GetSkill()->ReturnHitHandler(*iter);
				iter = mHitHandlerList.erase(iter);
			}
		}
	}
	
	//不需要tick弹道，也没有需要tick的Handler时，就说明活都干完了
	if (!mNeedTickProjectile && mHitHandlerList.empty())
	{
		mStatus = ESkillCarrierStatus::End;
		return false;
	}
   
	return true;
}

void SkillCarrier::Cancel()
{
	if (mStatus == ESkillCarrierStatus::End)
	{
		return;
	}
    mStatus = ESkillCarrierStatus::End;
	for (auto iter = mHitHandlerList.begin(); iter != mHitHandlerList.end(); iter++)
	{
		(*iter)->Cancel();
	}    
	if (mNeedTickProjectile)
	{
		mProjectile->ClearView();
		mNeedTickProjectile = false;
	}
}


void SkillCarrier::OnReachRefTarget(const RefTarget& aRefTarget)
{
	SharedPtr<Skill> skill = mSkillExecutor->GetSkill(); 
	if ( mOwner->HasDeleted()
		|| (aRefTarget.GetType() == ERefTargetType::Unit && aRefTarget.GetUnit()->HasDeleted() ) )
	{
		LOG_DEBUG("owner or reftarget has deleted. owner:%d skill:%d", mOwner->GetEntityId(), skill->GetId());
		return;
	}
    //选择生效目标 
    vector<SharedPtr<Unit> > effectTargetArr;    

    SearchEffTarget(mOwner, skill, aRefTarget, effectTargetArr);
    LOG_DEBUG("Skill carrier {skillId=%d} hitting eff targets {count=%d}", skill->GetId(), effectTargetArr.size()); 
	auto& efftars = skill->GetEffTargetArr();
    for (auto& t : effectTargetArr)
    {
		if (!t->IsDummy()) {
			LOG_DEBUG("eff target=%d", t->GetEntityId()); 
			uniqEmplaceBackToVector(efftars, t);
		}
    }

    Vector3 dir = mProjectile ? mProjectile->GetForward() : aRefTarget.GetTargetPos() - mOwner->GetPosition();
    mOwner->GetView()->Execute(ViewCommand::SkillOnReachRefTarget
        , mOwner->GetEntityId()
        , skill->GetId()
        , aRefTarget
        , dir
        , effectTargetArr, mProjectile ? mProjectile->GetEntityId() : 0);
	RestoreObjToPool(dir);
	
	if (effectTargetArr.size() == 0)
	{
		RestoreVectorToPool(effectTargetArr);
		return;
	}

	if (mOwner->GetBattleInstance().NeedDoStatistics())
	{
		if (mSkillConf->effectdata().recordeffecttarget()) //if cur skill conf need sum efftarget
		{
			//skill->GetAncestorSkill()->mEffectTargetCount += effectTargetArr.size();
			skill->mEffectTargetCount += effectTargetArr.size();
		}
	}
	SharedPtr<HitHandler> hitHandler = skill->FetchHitHandler();
    hitHandler->BeforeHitBatch( mOwner, SharedFromThis(), effectTargetArr);
    for(size_t i = 0; i < effectTargetArr.size() && !IsEnded(); i++)
    {
        SharedPtr<Unit> target = effectTargetArr[i];
        if( hitHandler->CanHit(mOwner, target, SharedFromThis()) )
        {            
			//if (skill->IsMasterRageSkill() && target != mOwner)  //add condi "target != mOwner" 
			if (mSkillConf->basedata().isrecoverfrompause()) //in case of RageSkill, check if need to unpause target unit
			{
				mOwner->AddRageSkillUnpausedTarget(target); //unpause be hitted man 
			}
            hitHandler->OnHit( mOwner, target, SharedFromThis()); 
        }    
    }
	if (!IsEnded()) //skill may terminate when trigger on hit event 
	{ 
		hitHandler->AfterHitBatch(mOwner, SharedFromThis(), effectTargetArr);
		if (hitHandler->IsDurative())
		{
			mHitHandlerList.emplace_back(hitHandler);
		}
	}
	else 
	{
		//cancel hithandler before recycle it
		hitHandler->Cancel();
	}
	RestoreVectorToPool(effectTargetArr);
}

const SharedPtr<Unit> SkillCarrier::GetOwner() const
{
    return mOwner;
}
const SkillData* SkillCarrier::GetSkillConf() const
{
    return mSkillConf;
}
const SharedPtr<Skill> SkillCarrier::GetSkill() const
{
    return mSkillExecutor->GetSkill();
}
const RefTarget& SkillCarrier::GetRefTarget() const
{
    return mRefTarget;
}

SharedPtr<SkillExecutor> SkillCarrier::GetSkillExecutor()
{
	return mSkillExecutor;
}