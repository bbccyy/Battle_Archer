/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author liyingbo
* @date $Date$
* @version $Revision$
* @brief 按场上对立双方划分的战斗单位集合
*
**/

#pragma once
#include <vector>
#include "Framework/SharedPtr.h"
#include "Unit.h"

using std::vector;
namespace pb {
    class TUnitInfo;
    class TArmyInfo;
}
using pb::TUnitInfo;
using pb::TArmyInfo;
class PhysicsSystem;
struct DirectedPosition;
class Skill;
enum class EBattleResult;

class Army
{
public:
    Army() = delete;
    ~Army();
    Army(int aId, BattleInstance&, BattleViewOutput&, PhysicsSystem&, const vector<DirectedPosition>&, const vector<DirectedPosition>&, const vector<DirectedPosition>&);

    void OnTick(int);
    BattleInstance& GetBattleInstance() const;
    const vector<SharedPtr<Unit> >& GetUnitArr() const;
    const vector<DirectedPosition>& GetBornPointArr() const;
	const vector<Unit*>& GetActiveUnitArr() const;
	bool HasArmyShooter() const;
	SharedPtr<Unit> GetDummy();
	const SharedPtr<Unit> GetArmyShooter() const;
	SharedPtr<Unit> GetOrInitArmyShooter();
    int GetId() const;
    int CountDead() const;
    int CountAlivedHero() const;
    int CountAlivedAny() const;
	void AddRage(int64 const aAmount);
	void SubRage(int64 const aAmount);
	bool CanExecuteUnparallel();
	void SkillUseRage();

    SharedPtr<Unit> SummonUnit(int aTplId, int aLevel, int aSkillLevel, int aBornPoint, int aTimedLife, int aAdvLv, bool aClearOnCutscene, Unit* aAttrProvider, int aAttrInheritPercent, WeakPtr<Skill> aAncestorSkill, Unit* aSummoner = nullptr, bool aUseFixedRate = false);
    SharedPtr<Unit> AddUnit(int aTplId, int aLevel, int aAdvLv, int aBornPoint, int aShowOnUI, int aIsBoss);
    SharedPtr<Unit> AddUnit(const TUnitInfo&);
    SharedPtr<Unit> AddUnit(const TUnitInfo&, int aPos);
    SharedPtr<Unit> AddHero(const TUnitInfo&);
    SharedPtr<Unit> AddPet(const TUnitInfo&);

    void AddUnitByConf(const TArmyInfo&);
	void LoadArmySkills(const TArmyInfo&);
	void TryExecuteArmySkill(int, int);
    int CountCountryHeroNumber(ECountry aCountry) const;
    int CountSummonedUnit(const Unit* aSummoner, int aTplId) const;
	int CountNonDummyUnit() const;
	int CountNonSummonNonDummyUnit() const;
	void GetSummonedUnit(const Unit* aSummoner, int aTplId, vector<Unit*>& aSummonedUnits);
    void UnitDeadStatusChanged(Unit*);
    void UnitHiddenStatusChanged(Unit*);
	bool ConditionIsEliminated(int) const;
    bool IsEliminated(bool aConsiderDummy = false) const;

    bool IsOnlySummonedLeft() const;
    bool IsOnlyDummyLeft() const;
    void OnEnterField();
    void OnEnterCutscene();
	void OnEnterBattleEnd();
    void Clear();
	void RecordUnitInfo();
	vector<vector<SharedPtr<Unit>>> GetUnitInfo();
	void ClearActiveUnitArr();
	void RemoveFromUnitArr(int);

	int RemoveIfAlive(int);
	bool HasUnitWithHtid(int);
	bool HasUnitWithHid(int);
	const DirectedPosition& GetSummonPointByIndex(int aIndex) const;
	const DirectedPosition& GetSummonPointByRand() const;
	void OnBehaviourPause(bool);
	int GetRandActiveUnit(int aExclude);
	SharedPtr<Unit> GetUnitById(int aId);
	SharedPtr<Unit> GetUnitByHid(int aHid);
	SharedPtr<Unit> GetUnitByBornPointId(int aBid, bool aNeedAlived);
	 vector<SharedPtr<Unit>> GetUnitByProfession(int aProfession, bool aNeedDead) const;
	const DirectedPosition& GetBornPointByIndex(int aIndex);
	void GetCenterPointByIndex(int aIndex, Vector3& aPos, Vector3& aRot);
	int GetSummonPointNum() const;

	vector<SharedPtr<Unit> > mTDRecordDeletedArmy1Units;

	int mSubRage = 0;

private:
    const constexpr static int UNIT_ARR_SIZE = 8;
    int mId;  // 1 = Army1, 2 = Army2
	int mIterateIndex;
	int mCounterTD = 10;
	int64 mMaxRageUnparallel;
	int64 mRageUnparallel; 
	int64 mRageThreshold; 
    BattleInstance& mBattle;
    BattleViewOutput& mView;
    PhysicsSystem& mPhysics;
    const vector<DirectedPosition>& mBornPoints;
    const vector<DirectedPosition>& mCenterPoints;
    const vector<DirectedPosition>& mSummonPoints;
    vector<SharedPtr<Unit> > mUnitArr;
	vector<vector<SharedPtr<Unit>>> mRecordUnitArr;
    vector<Unit*> mActiveUnitArr;
    vector<Unit*> mActiveUnitCopyArr;
	SharedPtr<Unit> mDummyUnit;
	SharedPtr<Unit> mArmyShooter;
	vector<SharedPtr<Skill>> mArmySkillArr;
	vector<SharedPtr<Unit> > mRemovedBeforeCutscene;

	int mArmySkillProb = 0;

    void RemoveFromActive(Unit*);

	inline bool AbleToExecuteArmySkillNow();

	int mSortCount = 0;
	int mBehaviourStopCount = 0;
	int mBehaviourPauseTime = 0;
	int mBehaviourPauseStart = 0;
};