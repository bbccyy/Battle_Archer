


#include "HitHandlerBarrier.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Log/Log.h"
#include "Entity/UnitDefine.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "BattleInstance.h"
#include "ConfigMgr/ConfigMgr.h"


void HitHandlerBarrier::Reset()
{
	HitHandler::Reset();
	RelaseDmgOrHealHandler();
	mSceneBarrierArr.clear();
	if (mUtilizer)
		mUtilizer.Release();
	if (mTarget)
		mTarget.Release();
	if (mSkillCarrier)
		mSkillCarrier.Release();
};


void HitHandlerBarrier::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
	if (mDmgOrHealHandler)
	{
		mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
	}
}


void HitHandlerBarrier::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
	const SkillData* skillConf = aSkillCarrier->GetSkillConf();
	const SkillSummonObstacleData& conf = skillConf->summonobstacledata();
	mIsDurative = skillConf->basedata().islasting();
	mUtilizer = aUtilizer;
	mTarget = aTarget;
	mSkillCarrier = aSkillCarrier;

	auto barrier = NewSceneBarrier(aUtilizer, conf);
	
	auto pos = Vector3(aTarget->GetPosition());  //use target's position in default
	auto front = Vector3(aTarget->GetForward());
	front.y = 0;
	pos.y = 0;
	auto left = Vector3(front.z, 0, -front.x);  //1,3 -> 3,-1
	auto forward = Vector3(aUtilizer->GetForward());  //use utilizer's direction as default

	int distance = aUtilizer->GetSize();
	if (conf.has_distance())
	{
		distance += CONF_POS_CONVERT(conf.distance());
	}
	EEmbattleRelativeDirection relDir = static_cast<EEmbattleRelativeDirection>(conf.positiontype());
	switch (relDir)
	{
	case ESummonSkillBirthPlaceEffTargetForward:
		front.ScaleToLen(distance);
		pos += front;
		break;
	case ESummonSkillBirthPlaceEffTargetBackward:
		front.ScaleToLen(distance);
		pos -= front;
		break;
	case ESummonSkillBirthPlaceEffTargetLeft:
		left.ScaleToLen(distance);
		pos += left;
		break;
	case ESummonSkillBirthPlaceEffTargetRight:
		left.ScaleToLen(distance);
		pos -= left;
		break;
	}

	//barrier->SetPosRot(pos, forward, true);  //set barrier's location
	barrier->InitLocation(pos, forward);

	if (mIsDurative == true)
	{
		mSceneBarrierArr.emplace_back(barrier); //record this barrier
	}
	else
	{
		//not lasting skill, then let battle instance manage it
		aUtilizer->AddBarrier(barrier);
	}

	LOG_DEBUG("unit %d summon barrier at pos [%d,%d,%d]", aUtilizer->GetEntityId(), pos.x, pos.y, pos.z);

	if (mDmgOrHealHandler)
	{
		mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
	}
	else
	{
		TriggerOnHitEvent(aUtilizer, aTarget, aSkillCarrier, 0);
	}

}


bool HitHandlerBarrier::OnTick(int aDeltaTime)
{
	auto j = mSceneBarrierArr.size();
	for (int i = 0; i < j; )
	{
		mSceneBarrierArr[i]->OnTick(aDeltaTime);
		if (mSceneBarrierArr[i]->IsValid() == false)
		{
			j--;
			auto tmp = mSceneBarrierArr[i];
			if (i < j)
			{
				mSceneBarrierArr[i] = mSceneBarrierArr[j];
			}
			tmp->ClearView();
			//SharedPool<SceneBarrier>::PutRaw(tmp.Get());
		}
		else
		{
			i++;
		}
	}
	mSceneBarrierArr.resize(j);

	if (mSceneBarrierArr.size() == 0)
	{
		TriggerOnEnd();
		Cancel();
		return false;
	}
	return true;
}


void HitHandlerBarrier::Cancel()
{
	for (auto barrier : mSceneBarrierArr)
	{
		barrier->ClearView();
		//SharedPool<SceneBarrier>::PutRaw(barrier.Get());
	}
	if (mSceneBarrierArr.size() > 0)
	{
		mSceneBarrierArr.clear();
	}

}


void HitHandlerBarrier::TriggerOnEnd()
{
	//TODO
}