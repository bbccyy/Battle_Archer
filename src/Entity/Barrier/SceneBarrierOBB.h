


#pragma once
#include "SceneBarrier.h"




class SceneBarrierOBB : public SceneBarrier, public EnableSharedFromThis<SceneBarrierOBB>
{
public:
	SceneBarrierOBB();
	~SceneBarrierOBB();

	void Init(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, SharedPtr<Unit> aUnit, const SkillSummonObstacleData& aConf);
	bool CollisionDetection(Unit* aUnit);
	void UpdateAgent();

};

