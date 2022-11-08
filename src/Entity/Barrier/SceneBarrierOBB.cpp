
#include "SceneBarrierOBB.h"
#include "View/BattleViewOutput.h"
#include "Framework/Physics/PhysicsSystem.h"
#include "Skill/Skill.h"
#include "BattleInstance.h"
#include "ConfigMgr/Util.h"


void SceneBarrierOBB::Init(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, SharedPtr<Unit> aUtilizer, const SkillSummonObstacleData& aConf)
{
	InitBase(aBattle, aView, aPhysics, aUtilizer, aConf);
	mShapeType = EBVType::EBVTypeOBB;

	mAgent = mPhysics->AddAgent(SharedFromThis(), EBVTypeOBB, PHYSICS_GROUP_BARRIER); 

	int frontSize = aConf.shapeparam2();  //size.x
	int leftSize = aConf.shapeparam1();   //size.z
	auto size = Vector2(CONF_POS_CONVERT(frontSize), CONF_POS_CONVERT(leftSize));

	auto* bv = dynamic_cast<OBB*>(mAgent->GetBV());
	bv->Update(nullptr, &size, nullptr);   //Set it's basic shape param
}

bool SceneBarrierOBB::CollisionDetection(Unit* aUnit)
{
	bool hasCollision = mPhysics->IntersectionSphereWithAny2D(aUnit->GetPosition(), aUnit->GetSize(), mAgent, EBVType::EBVTypeOBB);
	return hasCollision;
}

void SceneBarrierOBB::UpdateAgent()
{
	if (!mAgent)
		return;
	auto* bv = dynamic_cast<OBB*>(mAgent->GetBV());
	auto forward = Vector2(mRotation.x, mRotation.z);
	bv->Update(&mPosition, nullptr, &forward);
}

SceneBarrierOBB::SceneBarrierOBB()
{
}


SceneBarrierOBB::~SceneBarrierOBB()
{
}
