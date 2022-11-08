

#include "MeleeRingMgr.h"
#include "Entity.h"
#include "Unit.h"
#include "BattleInstance.h"

//When unit A's skill B's reftarget(C) has changed and
//B is a melee master skill and its reftarget(C) is out of range
//and C is right the owner of this MeleeRingMgr, 
//then this method will be called by A 
void MeleeRingMgr::RegisterAttacker(Unit* aUnit)
{
	for (int idx = 0; idx < mApproachingAttackers.size(); ++idx)
	{
		if (mApproachingAttackers[idx] == aUnit) return;
	}
	mApproachingAttackers.emplace_back(aUnit);
}


//Called after battleInstance's TickNormal method, 
//before really modify targets' moveTrace maneuvers 
//for every tick 
void MeleeRingMgr::UnregisterInvalidAttackers()
{
	int num = mApproachingAttackers.size();
	int myEntityId = mSelf->GetEntityId();
	for (int idx = 0; idx < num; )
	{
		auto* unit = mApproachingAttackers[idx];
		if (!unit->HasRefTarget(myEntityId))
		{
			--num;
			mApproachingAttackers[idx] = mApproachingAttackers[num];
		}
		else
		{
			++idx;
		}
	}
	mApproachingAttackers.resize(num);
}


void MeleeRingMgr::OnTick(const vector<Unit*>& aAllActiveUnits)
{
	UnregisterInvalidAttackers();
	int frameTime = mSelf->GetBattleInstance().GetFrameTime();
	if (frameTime != 0 && frameTime % 500 == 0)
		RefreshNearBy(aAllActiveUnits);   //TODO: if no one is moving, skip RefreshNearBy 
	if (frameTime != 0 && frameTime % 300 == 0)
		RedistributeRegisteredPosition();
}


//scan nearby, include all units in range of MinNearByDist 
void MeleeRingMgr::RefreshNearBy(const vector<Unit*>& aAllActiveUnits)
{
	int myRefTargetId = mSelf->TryGetCurrentRefTarget();
	if (myRefTargetId > 0) //do not scan nearby when moving 
		return;
	mNearByUnits.clear();
	Vector3 myPos = mSelf->GetPosition();
	for (auto unit : aAllActiveUnits)
	{
		auto v = unit->GetPosition() - myPos;
		if (v.Magnitude2() <= mMinNearByDist2)
		{
			mNearByUnits.emplace_back(unit);
		}
	}
}


//re-distribute position to approaching attacker
void MeleeRingMgr::RedistributeRegisteredPosition()
{
	mMutualTarget = nullptr; 
	mRingTable.clear();
	mRingTable.resize(MELEE_RING_MAX_SLOT);
	int myRefTargetId = mSelf->TryGetCurrentRefTarget();  //0 -> invalid
	if (myRefTargetId > 0)
	{ // owner is moving to its reftarget right now 
		mNearByUnits.clear();  //ignore nearby if owner is in moving to reftarget state 
		for (auto unit : mApproachingAttackers)
		{
			if (unit->GetEntityId() == myRefTargetId)
			{
				mMutualTarget = unit;
				unit->mEntityRegister0 = 0;
				unit->TryModifyMoveTrace(0);  //info my mutual target with 0 position(my front side) 
				mRingTable[0] = unit;
			}
		}
	}

	if (mNearByUnits.size() >= MELEE_RING_MAX_SIZE) 
	{  //do nothing when nearby is full of units 
		for (auto unit : mApproachingAttackers)
		{
			unit->mEntityRegister0 = -1;
			unit->TryModifyMoveTrace(-1);
		}
		return;
	}
	
	Vector3 myDir = mSelf->GetForward();
	for (auto unit : mApproachingAttackers)
	{
		if (unit == mMutualTarget)
			continue;

		auto unitPos = unit->GetPosition();
		int pIdx = CalcFirstHitPosition(unitPos);
		if (pIdx < 0)
		{
			unit->mEntityRegister0 = -1;
			unit->TryModifyMoveTrace(-1); 
			continue;
		}

		pIdx = TryBookSlot(pIdx, unit);
		unit->TryModifyMoveTrace(pIdx);

		/*int64 range = unit->TryGetCastRange() + unit->GetSize() + mSelf->GetSize();
		myDir.ScaleToLen(range);
		Vector3 tarDir = Vector3::RedirectTo(myDir, unit->mEntityRegister0, MELEE_RING_MAX_SLOT);*/
	}

	return;
}


//     0  <-- first position index starts from 0, it's locate right at the front side of owner 
//     |
// 3--- --- 1  <-- the second position index when dividing the circle into 4 parts
//     |
//     2
// Purpose: Find out the best position on ring for given target unit without any consideration 
//          of other units' influence 
// Input: target local position 
// Output: position index on my melee ring (returns -1 if find something invalid during calculation) 
int MeleeRingMgr::CalcFirstHitPosition(const Vector3& aTargetPos)
{
	Vector3 myDir = mSelf->GetForward();
	Vector3 myRight = mSelf->GetRight();
	Vector3 tarDir = aTargetPos - mSelf->GetPosition();
	myRight.y = 0;
	myDir.y = 0;
	tarDir.y = 0;
	int side = 0;  //0->same as myDir, 1->right side, 2->opposite of myDir, 3->left side
	int dot = Vector3::Dot(tarDir, myRight);
	if (dot > 0)
	{ //right
		side = 1;
	}
	else if (dot < 0)
	{ //left
		side = 3;
	}
	else
	{
		dot = Vector3::Dot(tarDir, myDir);
		if (dot > 0)
		{ //same dir, return first slot index 
			//side = 0;
			return 0;
		}
		else if (dot < 0)
		{ //opposite dir, return middle slot index 
			//side = 2;
			return MELEE_RING_MAX_SLOT / 2;
		}
		else
		{ //unexcepted case: contains ZERO vector, return invalid signal 
			LOG_WARN("CalcFirstHitPosition, contains ZERO forward, Eid[%d] myDir[%d, %d], tarDir[%d, %d]",
				mSelf->GetEntityId(), myDir.x, myDir.z, tarDir.x, tarDir.z);
			return -1;
		}
	}

	int64 baseMag = 100000;
	tarDir.ScaleToLen(baseMag);
	myDir.ScaleToLen(baseMag);

	int64 myDotTar = Vector3::Dot(tarDir, myDir);
	int64 cosValue = myDotTar / baseMag;  //myDotTar * baseMag / (baseMag * baseMag)  where first baseMag denote as base of cosValue
	if (cosValue > baseMag) cosValue = baseMag;
	
	int64 theta = ArccosInt(cosValue, baseMag, baseMag);  // 0 ~ 180 * baseMag
	int64 slotAngle = 360 * baseMag / MELEE_RING_MAX_SLOT;
	
	if (side == 1)
	{ //right
		int64 index100 = theta * 100 / slotAngle;
		int index = index100 / 100;
		if (index100 % 100 > 50)
		{
			++index;
		}
		return index;
	}
	else if (side == 3)
	{ //left 
		int64 index100 = theta * 100 / slotAngle;
		int index = MELEE_RING_MAX_SLOT - index100 / 100;
		if (index100 % 100 > 50)
		{
			--index;
		}
		if (index == MELEE_RING_MAX_SLOT)
		{
			index = 0;
		}
		return index;
	}

	return -1;
}


int MeleeRingMgr::TryBookSlot(int aFirstIndex, Unit* aTarget)
{
	int idx = aFirstIndex;
	if (aTarget == nullptr) return -1;
	if (idx < 0 || idx >= mRingTable.size())
	{
		aTarget->mEntityRegister0 = -1;
		return -1;
	}
	int count = 1;
	int multi = 1;
	while (count <= MELEE_RING_MAX_SLOT)
	{
		if (mRingTable[idx] == nullptr && CheckNearBy(aTarget))
		{
			mRingTable[idx] = aTarget;
			aTarget->mEntityRegister0 = idx;
			return idx;
		}
		//not satisfied, prepare next index to search empty slot 
		idx = aFirstIndex + multi * (2*(count%2) - 1);
		if (count % 2 == 0) ++multi;
		++count;
		if (idx < 0) idx = MELEE_RING_MAX_SLOT + idx;
		else if (idx >= MELEE_RING_MAX_SLOT) idx = idx - MELEE_RING_MAX_SLOT;
	}
	aTarget->mEntityRegister0 = -1;
	return -1;
}


//input: target unit
//output: true iff no overlap with owner's nearby units and vice verse 
bool MeleeRingMgr::CheckNearBy(Unit* aTarget)
{
	if (aTarget == nullptr)
		return false;

	for (auto unit : mNearByUnits)
	{
		if (unit == aTarget)
			continue;

		Vector3 tmp = unit->GetPosition() - aTarget->GetPosition();
		if (tmp.Magnitude2() < mMinDist2)
		{
			return false;
		}
	}
	return true;
}


void MeleeRingMgr::Reset()
{
	mMutualTarget = nullptr;
	mAngleBase = DENOM;
	mApproachingAttackers.clear();
	mNearByUnits.clear();
	mRingTable.clear();
}