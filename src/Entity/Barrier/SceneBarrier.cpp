

#include "SceneBarrier.h"
#include "SceneBarrierOBB.h"
#include "View/BattleViewOutput.h"
#include "Framework/Physics/PhysicsSystem.h"
#include "Skill/Skill.h"
#include "BattleInstance.h"
#include "ConfigMgr/Util.h"


void SceneBarrier::Init(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, SharedPtr<Unit> aUnit, const SkillSummonObstacleData& aConf)
{
	return;
}

void SceneBarrier::InitBase(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, SharedPtr<Unit> aUtilizer, const SkillSummonObstacleData& aConf)
{
	InitEntity(aView, aPhysics);
	mBattle = &aBattle;
	mOwner = aUtilizer;
	mConf = &aConf;
	mIsValid = true;

	mLifeTime = CONF_TIME_CONVERT(aConf.lasttime());
	mTime = 0;
	mBuffId = 0;
	if (aConf.has_buffid())
	{
		mBuffId = aConf.buffid();
	}
	mCollisionCheckType = static_cast<ESearchTargetRelation>(aConf.targettype());
	mArmyId = aUtilizer->GetArmy().GetId();

	mView->Execute(ViewCommand::AddSceneBarrier, mEntityId);
}

void SceneBarrier::Reset()
{
	if (mAgent)
	{
		mPhysics->RemoveAgent(mAgent);
	}
	if (mOwner)
		mOwner.Release();
}

bool SceneBarrier::CollisionDetection(Unit* aUnit)
{
	return false;
}

//bool SceneBarrier::CollisionDetection(Unit* aUnit)
//{
//	LOG_WARN("not implement CollisionDetection method");
//	return false;
//}

bool SceneBarrier::OnTick(int aDeltaTime)
{
	if (!mIsValid)
	{
		return false;
	}

	mTime += aDeltaTime;

	const auto& army1 = mBattle->GetArmy1();
	const auto& army2 = mBattle->GetArmy2();

	switch (mCollisionCheckType)
	{
	case ESearchTargetRelation::ESearchTargetRelationEnemy:
		if (mArmyId == army1.GetId())
		{
			DealUnits(army2);
		}
		else
		{
			DealUnits(army1);
		}
		break;
	case ESearchTargetRelation::ESearchTargetRelationFriend:
		if (mArmyId == army1.GetId())
		{
			DealUnits(army1);
		}
		else
		{
			DealUnits(army2);
		}
		break;
	case ESearchTargetRelation::ESearchTargetRelationAll:
		DealUnits(army1);
		DealUnits(army2);
		break;
	default:
		LOG_WARN("Unknow collision check type founded: %d", mCollisionCheckType);
		break;
	}

	if (mTime >= mLifeTime)
	{
		mIsValid = false;
		return false;
	}
	return true;
}

void SceneBarrier::DealUnits(const Army& aArmy)
{
	auto& unitArr = aArmy.GetActiveUnitArr(); //only counts on Active Unit
	for (auto& unit : unitArr)
	{
		if (unit->CheckStateAdjust(StateAdjust::VulnerableToBarrier) == true &&
			CollisionDetection(unit) == true)
		{
			unit->CurrentSkillInterrupted();
			unit->TryReceiveBuff(mOwner, mOwner, mBuffId, 1); //TODO: buff level
		}
	}
}


void SceneBarrier::UpdateAgent()
{
	LOG_DEBUG("not implement UpdateAgent");
	return;
}


EBVType SceneBarrier::GetShapeType() const
{
	return mShapeType;
}

bool SceneBarrier::IsValid() const
{
	return mIsValid;
}


SharedPtr<SceneBarrier> NewSceneBarrier(SharedPtr<Unit> aUtilizer, const SkillSummonObstacleData& aConf)
{
	SharedPtr<SceneBarrier> barrier;
	EBVType barrierType = static_cast<EBVType>(aConf.shapetype());
	switch (barrierType)
	{
	case EBVTypeOBB:
		barrier = SharedPool<SceneBarrierOBB>::Get();
		break;
	case EBVTypeCylinder:
		barrier = SharedPool<SceneBarrierOBB>::Get();  //TODO: add cylinder
		break;
	default:
		LOG_FATAL("invalid barrier Type:%d", barrierType);
	}

	auto& battle = aUtilizer->GetBattleInstance();
	barrier->Init(battle, *battle.GetView(),*battle.GetPhysics(), aUtilizer, aConf);

	return barrier;
}