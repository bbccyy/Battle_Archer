

#pragma once
#include "Framework/Transform.h"
#include "Framework/Physics/PhysicsSystem.h"
#include "Log/Log.h"
#include "Define.h"
#include "Skill/RefTarget.h"

class Unit;

class MeleeRingMgr : public IPoolable {
public:
	MeleeRingMgr() = default;

	void Init(Unit* aSelf)
	{
		mSelf = aSelf;
		mRingTable.resize(MELEE_RING_MAX_SLOT);
		mMinDist2 = (MELEE_ATTACK_RANGE - 20000) * (MELEE_ATTACK_RANGE - 20000);
		mMinNearByDist2 = MELEE_RING_MIN_NEARBY_RANGE * MELEE_RING_MIN_NEARBY_RANGE;
	}

	void RegisterAttacker(Unit* aUnit);
	void UnregisterInvalidAttackers();
	void OnTick(const vector<Unit*>& aAllActiveUnits);
	void Reset();

private:
	void RefreshNearBy(const vector<Unit*>&);
	void RedistributeRegisteredPosition();
	int TryBookSlot(int aFirstIndex, Unit* aTarget);
	int CalcFirstHitPosition(const Vector3& aTargetPos);
	bool CheckNearBy(Unit* aTarget);

private:
	Unit* mSelf;  //mgr holder
	Unit* mMutualTarget; 
	vector<Unit*> mApproachingAttackers;  //attackers that are still in moving 
	vector<Unit*> mNearByUnits;  //attackers that are reached their position 

	int mAngleBase;
	int64 mMinDist2;
	int64 mMinNearByDist2;
	vector<Unit*> mRingTable;


};