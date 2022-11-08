#pragma once
#include "HitHandler.h"
#include "module/SkillData.pb.h"
#include "Entity/Barrier/SceneBarrier.h"

using namespace pb;

class HitHandlerBarrier : public  HitHandler
{
public:

	virtual void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
	virtual void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier);

	void Reset();

	bool OnTick(int aDeltaTime) override;
	void Cancel() override;
	inline void TriggerOnEnd();

private:

	SharedPtr<Unit> mUtilizer;
	SharedPtr<Unit> mTarget;
	WeakPtr<SkillCarrier> mSkillCarrier;
	vector<SharedPtr<SceneBarrier>> mSceneBarrierArr;
};

