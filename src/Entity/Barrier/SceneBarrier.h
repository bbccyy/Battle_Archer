#pragma once
#include "Entity/Entity.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "Skill/SkillDefine.h"
#include "module/SkillData.pb.h" //TODO: replace with skillConf

using pb::SkillSummonObstacleData;

//TODO: extend to multi shapes as required
class SceneBarrier : public Entity
{
public:
	SceneBarrier() = default;
	~SceneBarrier() = default;
	virtual void InitBase(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, SharedPtr<Unit> aUnit, const SkillSummonObstacleData& aConf);
	virtual void Init(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, SharedPtr<Unit> aUnit, const SkillSummonObstacleData& aConf);
	virtual bool OnTick(int);  //TODO: will move or not?
	void Reset();
	void DealUnits(const Army& aArmy);
	bool IsValid() const;
	EBVType GetShapeType() const;

	virtual bool CollisionDetection(Unit* aUnit);  //this scene barrier will use this method to probe any possible Units
	virtual void UpdateAgent();

protected:
	
	SharedPtr<Unit> mOwner;
	int mLifeTime;
	int mTime;
	int mBuffId;
	bool mIsValid;
	ESearchTargetRelation mCollisionCheckType;
	EBVType mShapeType;
	int mArmyId;

	const SkillSummonObstacleData* mConf; 

	BattleInstance * mBattle;
	Agent* mAgent;

};

SharedPtr<SceneBarrier> NewSceneBarrier(SharedPtr<Unit> aUtilizer, const SkillSummonObstacleData& aConf);



