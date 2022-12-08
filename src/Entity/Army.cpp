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
* @brief
*
**/

#include "Army.h"
#include "BattleInstance.h"
#include "Framework/SharedPool.h"
#include "Log/Log.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ConfigMgr/Pb/net/Battle.pb.h"
#include "View/BattleViewOutput.h"
#include "Path/PathFindingMgr.h"
#include "Skill/Skill.h"
#include "net/BattleBase.pb.h"
#include "net/Battle.pb.h"

int Partition(vector<Unit*>& v, int low, int high, int army)
{
	Unit* tmp = v[low];
	while (low < high) {
		while (low < high && v[high]->LessEqualThan(army, tmp)) { 
			high--;
		}
		v[low] = v[high];
		while (low<high && v[low]->GreaterEqualThan(army, tmp)) {
			low++;
		}
		v[high] = v[low];
	}
	v[low] = tmp;
	return low;
}

void QuickSort(vector<Unit*>& v, int low, int high, int army)
{
	if (low < high) {
		int mid = Partition(v, low, high, army);
		QuickSort(v, low, mid - 1, army);
		QuickSort(v, mid + 1, high, army);
	}
}

Army::Army(int aId, BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, const vector<DirectedPosition>& aBornPoints, const vector<DirectedPosition>& aSummonPoints, const vector<DirectedPosition>& aCenterPoints)
    : mId(aId)
    , mBattle(aBattle)
    , mView(aView)
    , mPhysics(aPhysics)
    , mBornPoints(aBornPoints)
    , mCenterPoints(aCenterPoints)
    , mSummonPoints(aSummonPoints) 
{
	LOG_DEBUG("Army %d created", aId);
    mUnitArr.reserve(UNIT_ARR_SIZE);
    mActiveUnitArr.reserve(UNIT_ARR_SIZE);
	mActiveUnitCopyArr.reserve(UNIT_ARR_SIZE);
	mRemovedBeforeCutscene.reserve(UNIT_ARR_SIZE);
	auto* battleConf = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
	mRageThreshold = battleConf->GetUnparalleledSkillThreshold();
	mMaxRageUnparallel = battleConf->GetMaxUnparalleledSkillRage();
	mRageUnparallel = 0;  //TODO
	mSortCount = 10;
	mArmySkillProb = 0;
	mBehaviourStopCount = 0;
	mBehaviourPauseTime = 0;
	mBehaviourPauseStart = 0;
	mSubRage = 0;
}

Army::~Army()
{
    for(auto& unit : mUnitArr)
    {
        unit->Reset();
    }
    mUnitArr.clear();
	mActiveUnitArr.clear();
	mRecordUnitArr.clear();
	mActiveUnitCopyArr.clear();
	mTDRecordDeletedArmy1Units.clear();
	if (mRemovedBeforeCutscene.size() > 0)
	{
		for (auto& u : mRemovedBeforeCutscene)
		{
			u->Reset();
		}
	}
	mRemovedBeforeCutscene.clear();

    if(mDummyUnit)
    {
        mDummyUnit->Reset();
		mDummyUnit = nullptr;
    }
	if (mArmyShooter)
	{
		mArmyShooter->Reset();
		mArmyShooter = nullptr;
	}
        
}

// tick every Unit in this Army
void Army::OnTick(int const aDeltaTime)
{
	if (mSortCount > 0 && mBattle.UseAIPath())
	{
		QuickSort(mActiveUnitArr, 0, mActiveUnitArr.size() - 1, mId);
		mSortCount--;
	}
	mActiveUnitCopyArr.resize(mActiveUnitArr.size());
	for (mIterateIndex = 0; mIterateIndex < mActiveUnitArr.size(); ++mIterateIndex)
	{ //run OnTick on a copy of mActiveUnitArr 
		mActiveUnitCopyArr[mIterateIndex] = mActiveUnitArr[mIterateIndex];
	}
	//这个有个约定： 从mActiveUnitArr中删除unit必须是将最后一个移到当前位置，添加unit必须从尾部
	for (mIterateIndex = 0; mIterateIndex < mActiveUnitCopyArr.size(); ++mIterateIndex)
	{
		mActiveUnitCopyArr[mIterateIndex]->OnTick(aDeltaTime);
	}
	mActiveUnitCopyArr.clear();
	if (mBattle.UseAIPath())
		mBattle.GetPathMgr()->CleanUpPreSet();
	if (mArmyShooter)
		mArmyShooter->OnTick(aDeltaTime);
}

//summon a unit based on input config, then push into this Army
SharedPtr<Unit> Army::SummonUnit(int const aTplId, int const aLevel, int const aSkillLevel, 
	int const aBornPoint, int const aTimedLife, int aAdvLv, bool const aKeepOnCutscene, Unit* aAttrProvider,
	int const aAttrInheritPercent, WeakPtr<Skill> aAncestorSkill, Unit* aSummoner, bool aUseFixedRate)
{
    SharedPtr<Unit> ret = SharedPool<Unit>::Get();
    mUnitArr.push_back(ret);
    mActiveUnitArr.push_back(ret.Get());
	if (mBattle.IsInRageSkill(mId))
	{
		mBattle.UnpauseDummyUnit(ret.Get());
	}

	if (aSummoner == nullptr)
		aSummoner = aAttrProvider;
	//const ConfigHero* heroConfig = ConfigMgr::GetConfById<ConfigHero>(aTplId);
	//const vector<int64>& skillArr = heroConfig->GetSkillID();

	if (aAttrInheritPercent > 0)
	{
		ret->LoadAttr(aAttrProvider, aAttrInheritPercent, aTplId, aUseFixedRate);
	}
	else
	{
		//ret->LoadAttr(aTplId);
		ret->LoadAttr(aTplId, aLevel);
	}

	vector<int> skillList;
	if (aAttrProvider->GetTplId() == aTplId)
	{
		GetBattleInstance().TryGetSkillsFromArgs(skillList, aTplId, mId);
	}

	ret->SetSummoner(aSummoner);
    ret->Init(aTplId, aLevel, aSkillLevel, aAdvLv, aBornPoint, *this, mView, mPhysics, skillList);
    if (aTimedLife > 0)
    {
        ret->SetTimedLife(aTimedLife, aKeepOnCutscene);
    }
	ret->SetAncestorSkill(aAncestorSkill);
	ret->AddViewEntity(aBornPoint, 0, 0, aSummoner->GetEntityId());
	ret->Born();

    LOG_DEBUG("Unit %d summoned to Army %d. {tplId=%d bornPoint=%d timedLife=%d}",
        ret->GetEntityId(),
        mId,
        aTplId,
        aBornPoint,
        aTimedLife);
    return ret;
}

//roughly the same with SummonUnit, but not live time limits
SharedPtr<Unit> Army::AddUnit(int const aTplId, int const aLevel, int aAdvLv, int const aBornPoint, int const aShowOnUI, int const aIsBoss)
{
    SharedPtr<Unit> ret = SharedPool<Unit>::Get();
    mUnitArr.push_back(ret);
    mActiveUnitArr.push_back(ret.Get());
    ret->LoadAttr(aTplId);
	//TODO 技能等级默认为1
    ret->Init(aTplId, aLevel, 1, aAdvLv, aBornPoint, *this, mView, mPhysics, vector<int>());
    ret->AddViewEntity(aBornPoint, aShowOnUI, aIsBoss);
	auto& p = GetBornPointByIndex(ret->GetBornPoint());
	ret->SetPosRot(p.mPos, p.mRot, false);
	ret->TryUpdateMapLocation();
	ret->Born();
	LOG_DEBUG("Unit %d added to Army %d. {tplId=%d bornPoint=%d}",
        ret->GetEntityId(),
        mId,
        aTplId,
        aBornPoint);
    return ret;
}

SharedPtr<Unit> Army::AddPet(const TUnitInfo& aUnitInfo)
{
	//TODO 
	return nullptr;
}

SharedPtr<Unit> Army::AddHero(const TUnitInfo& aUnitInfo)
{
	SharedPtr<Unit> ret = SharedPool<Unit>::Get();
	mUnitArr.push_back(ret);
	ret->LoadAttr(aUnitInfo);
	ret->mUnitType = UnitType::Player;
	ret->Init(aUnitInfo, *this, mView, mPhysics, 0);	//最后一个入参是出身点位，主角默认是0（第一个）
	auto& p = GetBornPointByIndex(ret->GetBornPoint());
	ret->SetPosRot(p.mPos, p.mRot, false);
	//ret->TryUpdateMapLocation();

	if (ret->GetHp() > 0)
		mActiveUnitArr.push_back(ret.Get());
	else
		ret->SetDie();  //directly set Fsm to Dead state 
	//ret->Born();
	LOG_DEBUG("Unit %d added to Army %d. {tplId=%d bornPoint=%d}",
		ret->GetEntityId(),
		mId,
		aUnitInfo.htid(),
		0);
	return ret;
}

//overloading method with a simple pb::TUnitInfo parameter
SharedPtr<Unit> Army::AddUnit(const TUnitInfo& aUnitInfo)
{
	return AddUnit(aUnitInfo, aUnitInfo.pos());
}

SharedPtr<Unit> Army::AddUnit(const TUnitInfo& aUnitInfo, int aPos)
{
	SharedPtr<Unit> ret = SharedPool<Unit>::Get();
	mUnitArr.push_back(ret);
	ret->LoadAttr(aUnitInfo);
	ret->mUnitType = UnitType::Monster;
	ret->Init(aUnitInfo, *this, mView, mPhysics, aPos);
	auto& p = GetBornPointByIndex(ret->GetBornPoint());
	ret->SetPosRot(p.mPos, p.mRot, false);
	ret->TryUpdateMapLocation();

	if (ret->GetHp() > 0)
		mActiveUnitArr.push_back(ret.Get());
	else
		ret->SetDie();  //directly set Fsm to Dead state 
	//ret->Born();
	LOG_DEBUG("Unit %d added to Army %d. {tplId=%d bornPoint=%d}",
		ret->GetEntityId(),
		mId,
		aUnitInfo.htid(),
		aPos);
	return ret;
}


void Army::TryExecuteArmySkill(int aGameTime, int aFieldIndex)
{
	if (mArmySkillArr.empty())
		return;
	if (!AbleToExecuteArmySkillNow())
		return;
	if (mArmySkillProb >= mArmySkillArr.size())
		return;

	while (mArmySkillProb < mArmySkillArr.size() && 
		mArmySkillArr[mArmySkillProb]->mArmySkillTiming + mBehaviourPauseTime <= aGameTime)
	{
		if (mArmySkillArr[mArmySkillProb]->mArmySkillStrategy == 0 || aFieldIndex == 1)
		{
			mArmySkillArr[mArmySkillProb]->RefreshRefTarget();
			GetOrInitArmyShooter()->ExecuteSkill(mArmySkillArr[mArmySkillProb], 0, nullptr, nullptr);
		}
		mArmySkillProb = mArmySkillProb + 1;
	}
}

void Army::LoadArmySkills(const TArmyInfo& aArmyConf)
{
	mArmySkillArr.clear();
	mArmySkillProb = 0;
	if (aArmyConf.armyskillarr_size() == 0)
		return;

	for (const TSkillAttribute& skillInfo : aArmyConf.armyskillarr())
	{
		int skillId = skillInfo.id();
		int skillLv = skillInfo.level();
		SharedPtr<Skill> armySkill = SharedPool<Skill>::Get();
		armySkill->Init(GetOrInitArmyShooter(), skillId, skillLv, nullptr);
		if (armySkill->mIsArmySkill)
		{
			mArmySkillArr.emplace_back(armySkill);
		}
	}
	//sort: min to max
	for (int p = 0; p < mArmySkillArr.size() - 1; ++p)
	{
		int minq = p;
		for (int q = p + 1; q < mArmySkillArr.size(); ++q)
		{
			if (mArmySkillArr[q]->mArmySkillTiming < mArmySkillArr[minq]->mArmySkillTiming
				|| (mArmySkillArr[q]->mArmySkillTiming == mArmySkillArr[minq]->mArmySkillTiming && 
					mArmySkillArr[q]->GetId() < mArmySkillArr[minq]->GetId()))
				minq = q;
		}
		if (p != minq)
		{  //swap
			auto tmp = mArmySkillArr[p];
			mArmySkillArr[p] = mArmySkillArr[minq];
			mArmySkillArr[minq] = tmp;
		}
	}
}

//add multi Units by method AddUnit
void Army::AddUnitByConf(const TArmyInfo& aArmyConf)
{
	bool first = true;
    for (const TUnitInfo& conf : aArmyConf.unitarr())
    {
		if (mId == 2)
			AddUnit(conf);	//Army2 正常添加 
		else
		{
			if (first)
			{
				AddHero(conf);	//Army1 的第一个默认是英雄 
				first = false;
			}
			else
			{
				AddPet(conf);	//后面的默认是随从 
			}
		}
			
    }
}

bool Army::HasUnitWithHid(int aHid)
{
	for (int u = 0; u < mUnitArr.size(); ++u)
	{
		if (mUnitArr[u] && mUnitArr[u]->GetHeroId() == aHid)
		{
			return true;
		}
	}
	return false;
}

bool Army::HasUnitWithHtid(int aTplId)
{
	for (int u = 0; u < mUnitArr.size(); ++u)
	{
		if (mUnitArr[u] && mUnitArr[u]->GetOrigTplId() == aTplId)
		{
			return true;
		}
	}
	return false;
}

int Army::RemoveIfAlive(int aEntityId)
{
	bool find = false;
	for (int u = 0; u < mActiveUnitArr.size(); ++u)
	{
		if (mActiveUnitArr[u] && mActiveUnitArr[u]->GetEntityId() == aEntityId)
		{
			mTDRecordDeletedArmy1Units.emplace_back(mActiveUnitArr[u]);
			mActiveUnitArr[u] = mActiveUnitArr.back();
			mActiveUnitArr.pop_back();
			find = true;
			break;
		}
	}
	if (!find) return -1;
	RemoveFromUnitArr(aEntityId);
	return 0;
}


void Army::RemoveFromActive(Unit* aUnit)
{
    for (int u = 0; u < mActiveUnitArr.size(); ++u)
    {
        if (mActiveUnitArr[u] == aUnit)
        {
            mActiveUnitArr[u] = mActiveUnitArr.back();
            mActiveUnitArr.pop_back();
			return;
        }
    }
	//LOG_INFO("not found unit:%d in army:%d", aUnit->GetEntityId(), mId);
}

void Army::RemoveFromUnitArr(int aEntityId)
{
	DieCause dieCause(EUnitDieCause::Behaviour);
	for (int u = 0; u < mUnitArr.size(); ++u)
	{
		if (mUnitArr[u] && mUnitArr[u]->GetEntityId()== aEntityId)
		{
			if (!mUnitArr[u]->IsDead())
			{
				mUnitArr[u]->AnyToDead(dieCause); //behavior Die
			}
			mUnitArr[u]->ClearView();
			mUnitArr[u]->OnDelete();
			mUnitArr[u] = mUnitArr.back();
			mUnitArr.pop_back();
			return;
		}
	}
}

int Army::CountNonSummonNonDummyUnit() const
{
	int ret = 0;
	for (auto* unit : mActiveUnitArr)
	{
		if (!unit->IsDummy() && !unit->IsDummy())
		{
			++ret;
		}
	}
	return ret;
}

int Army::CountNonDummyUnit() const
{
	int ret = 0;
	for (auto* unit : mActiveUnitArr)
	{
		if (!unit->IsDummy())
		{
			++ret;
		}
	}
	return ret;
}

int Army::CountSummonedUnit(const Unit* aSummoner, int const aTplId) const
{
    int ret = 0;
    for (auto* unit : mActiveUnitArr)
    {
        if (unit->GetTplId() == aTplId && unit->IsSummonedBy(aSummoner))
        {
            ++ret;
        }
    }
    return ret;
}

void Army::GetSummonedUnit(const Unit* aSummoner, int aTplId, vector<Unit*>& aSummonedUnits)
{
	for (auto* unit : mActiveUnitArr)
	{
		if (unit->GetTplId() == aTplId && unit->IsSummonedBy(aSummoner) && !unit->IsDead())
		{
			aSummonedUnits.emplace_back(unit);
		}
	}
}

//add or deduct a Unit
void Army::UnitDeadStatusChanged(Unit* aUnit)
{
    if (aUnit->IsDead())
    {
        RemoveFromActive(aUnit);
    }
    else
    {
        mActiveUnitArr.push_back(aUnit);
    }
}

// apply or recover Hidden status
void Army::UnitHiddenStatusChanged(Unit* aUnit)
{
    if (aUnit->IsHidden())
    {
        RemoveFromActive(aUnit);
    }
    else if (!aUnit->IsDead())
    {
		for (auto u : mActiveUnitArr)
		{
			if (u == aUnit) return;  //avoid unhide without pre-hide 
		}
        mActiveUnitArr.push_back(aUnit);
    }
}

bool Army::ConditionIsEliminated(int aStarter) const
{
	if (aStarter == pb::EBattleStarter::EBattleMajorExpedition)
	{
		return IsOnlyDummyLeft();
	}
	if (aStarter == pb::EBattleStarter::EBattleMajorInstanceNormal ||
		aStarter == pb::EBattleStarter::EBattleMajorActivityTD ||
		aStarter == pb::EBattleStarter::EBattleMajorTD ||
		aStarter == pb::EBattleStarter::EBattleNone)
	{
		return IsEliminated();
	}
	return IsEliminated(true);
}

bool Army::IsOnlyDummyLeft() const
{
	int size = mActiveUnitArr.size();
	for (int i = 0; i < size; i++)
	{
		if (!mActiveUnitArr[i]->IsDummy())
		{
			return false;
		}
	}
	return true;
}

bool Army::IsOnlySummonedLeft() const
{
	int size = mActiveUnitArr.size();
	for (int i = 0; i < size; i++)
	{
		if (!mActiveUnitArr[i]->IsSummoned() && !mActiveUnitArr[i]->IsDummy())
		{
			return false;
		}
	}
	return true;  //TODO: return size > 0
}



// an Army is Eliminated(true) iff mActiveUnitArr is empty or only dummy left
bool Army::IsEliminated(bool aConsiderDummy) const
{
	if (aConsiderDummy)
	{
		for (auto& unit : mActiveUnitArr)
		{
			if (!unit->IsDummy())
				return false;
		}
	}
	else
	{
		if (mActiveUnitArr.size() > 0)
			return false;
	}
	return true;
}


// set Born Pos to each Unit, run Unit->OnEnterField method respectively
void Army::OnEnterField()
{
	mSortCount = 10;
    mActiveUnitArr.clear();
	vector<SharedPtr<Unit>> unitArrCopy(mUnitArr);
    for (auto& unit : unitArrCopy)
    {		
		auto& p = GetBornPointByIndex(unit->GetBornPoint());
		if (unit->SetToBornPos())
			unit->SetPosRot(p.mPos, p.mRot, false);
		if (!unit->IsDead() && !unit->IsHidden())
		{
			mActiveUnitArr.push_back(unit.Get());
		}
    }

	vector<Unit*> activeArrCopy(mActiveUnitArr);
	for (auto unitPtr : activeArrCopy)
	{
		if (!unitPtr->IsDead())
		{
			if (!unitPtr->hasBorn())
				unitPtr->Born();
			unitPtr->OnEnterField();
			unitPtr->TryUpdateMapLocation();
		}
	}
}

// remove some of Summoned Units from mUnitArr, run unit->OnEnterCutscene for others 
void Army::OnEnterCutscene()
{
	mBehaviourStopCount = 0;
	mBehaviourPauseTime = 0;
	mBehaviourPauseStart = 0;
	mSubRage = 0;
	DieCause dieCause(EUnitDieCause::ClearSummonWhenCutScene);
    for (int u = 0; u < mUnitArr.size(); ++u)
    {
        auto& unit = mUnitArr[u];
        if (unit->IsSummoned() && (unit->IsClearOnCutscene() || unit->IsDead()))
        {
			if (!unit->IsDead())
			{
				unit->Die(dieCause);   //this will make sure NO ghost timer in TimeMgr
			}
			unit->OnDelete();
			RemoveFromActive(unit.Get());
			mRemovedBeforeCutscene.emplace_back(mUnitArr[u]);
            if (unit != mUnitArr.back())
            {
                mUnitArr[u] = mUnitArr.back();
                --u;
            }
            mUnitArr.pop_back();
        }
		else
		{
			unit->OnEnterCutscene();
		}
    }
}

void Army::OnEnterBattleEnd()
{
	vector<Unit*> tmp(mActiveUnitArr);
	for (auto& unit : tmp)
	{
		unit->CurrentSkillInterrupted();
		unit->UnRegisterAllEvents();
		if (unit->IsMoving()) 
			unit->DisableMove();
	}
}


// will also do unit->ClearView
void Army::Clear()
{
    for (auto& unit : mUnitArr)
    {
        //unit->ClearView();  //let frontEnd deal with corpses 
		unit->OnDelete();
    }
    mUnitArr.clear();
    mActiveUnitArr.clear();
}

SharedPtr<Unit> Army::GetUnitByHid(int aHid)
{
	for (int i = 0; i < mUnitArr.size(); ++i)
	{
		if (mUnitArr[i]->GetHeroId() == aHid)
			return mUnitArr[i];
	}
	return nullptr;
}

SharedPtr<Unit> Army::GetUnitById(int aId)
{
	for (int i = 0; i < mUnitArr.size(); ++i)
	{
		if (mUnitArr[i]->GetEntityId() == aId)
			return mUnitArr[i];
	}
	return nullptr;
}

SharedPtr<Unit> Army::GetUnitByBornPointId(int aBid, bool aNeedAlived)
{
	for (int i = 0; i < mUnitArr.size(); ++i)
	{
		if (mUnitArr[i]->GetBornPoint() == aBid && mUnitArr[i]->IsDead() != aNeedAlived)
		{
			return mUnitArr[i];
		}
	}
	return nullptr;
}

int Army::GetRandActiveUnit(int aExclude)
{
	int size = mActiveUnitArr.size();
	if (size == 0 || (aExclude > 0 && size == 1))
		return 0;
	vector<int> tmp;
	for (auto* unit : mActiveUnitArr)
	{
		if (unit->GetEntityId() != aExclude && 
			!unit->IsDummy() && 
			!unit->IsRefDummy() && 
			unit->GetHp() > 0)
		{
			tmp.emplace_back(unit->GetEntityId());
		}
	}
	if (tmp.empty())
		return 0;
	return tmp[mBattle.Rand(tmp.size())];
}

void Army::RecordUnitInfo()
{
	vector<SharedPtr<Unit>> tmp; 
	tmp.reserve(mUnitArr.size());
	for (int i = 0; i < mUnitArr.size(); ++i)
	{
		tmp.emplace_back(mUnitArr[i]);
	}
	for (int i = 0; i < mRemovedBeforeCutscene.size(); ++i)
	{
		tmp.emplace_back(mRemovedBeforeCutscene[i]);
	}
	mRecordUnitArr.emplace_back(tmp);
	mRemovedBeforeCutscene.clear();
}

vector<vector<SharedPtr<Unit>>> Army::GetUnitInfo()
{
	return mRecordUnitArr;
}

BattleInstance& Army::GetBattleInstance() const
{
    return mBattle;
}

bool Army::HasArmyShooter() const
{
	if (mArmyShooter)
	{
		return true;
	}
	return false;
}

SharedPtr<Unit> Army::GetOrInitArmyShooter()
{
	if (mArmyShooter)
	{
		return mArmyShooter;
	}
	mArmyShooter = SharedPool<Unit>::Get();
	mArmyShooter->InitDummy(*this, mView, mPhysics); 
	mArmyShooter->LoadAttr(mActiveUnitArr, DENOM, 0);
	if (mId == 1)
	{
		mArmyShooter->SetPosRot(Vector3(500000, 0, 0), Vector3(-100, 0, 0), false);
	}
	else
	{
		mArmyShooter->SetPosRot(Vector3(-500000, 0, 0), Vector3(100, 0, 0), false);
	}
	return mArmyShooter;
}

const SharedPtr<Unit> Army::GetArmyShooter() const 
{
	return mArmyShooter;
}

SharedPtr<Unit> Army::GetDummy()
{
	if (mDummyUnit)
	{
		return mDummyUnit;
	}
	mDummyUnit = SharedPool<Unit>::Get();
	mDummyUnit->InitDummy(*this, mView, mPhysics);
	return mDummyUnit;
}

const vector<SharedPtr<Unit> >& Army::GetUnitArr() const
{
    return mUnitArr;
}

const vector<Unit*>& Army::GetActiveUnitArr() const
{
	return mActiveUnitArr;
}

const vector<DirectedPosition>& Army::GetBornPointArr() const
{
    return mBornPoints;
}

int Army::GetId() const
{
    return mId;
}

void Army::ClearActiveUnitArr()
{
	DieCause casedByBehaviour = DieCause(EUnitDieCause::ClearAllWhenDircetWin);
	for (auto& unit : mActiveUnitArr)
	{
		unit->Die(casedByBehaviour);
	}
	mActiveUnitArr.clear();
}

// will not include any Summoned Unit
int Army::CountDead() const
{
    int count = 0;
    for (auto& unit : mUnitArr) {
        if (!unit->IsSummoned() && !unit->IsBehaviourUnit() && unit->IsEmptyHp())
        {
            ++count;
        }
    }
    return count;
}
int Army::CountAlivedAny() const
{
	int count = 0;
	for (auto& unit : mActiveUnitArr) {
		if (!unit->IsDummy() && !unit->IsEmptyHp())
		{
			++count;
		}
	}
	return count;
}
int Army::CountAlivedHero() const
{
	int count = 0;
	for (auto& unit : mActiveUnitArr) {
		if (!unit->IsSummoned() && !unit->IsBehaviourUnit() && !unit->IsDummy() && !unit->IsEmptyHp())
		{
			++count;
		}
	}
	return count;
}

void Army::AddRage(int64 const aAmount)
{
	mRageUnparallel = mRageUnparallel + aAmount;
	if (mRageUnparallel >= mMaxRageUnparallel)
		mRageUnparallel = mMaxRageUnparallel;
	mBattle.GetView()->Execute(ViewCommand::AddUnparallelRage, mId, aAmount, mRageUnparallel, mMaxRageUnparallel);
}

void Army::SubRage(int64 const aAmount)
{
	mRageUnparallel = mRageUnparallel - aAmount;
	if (mRageUnparallel < 0)
		mRageUnparallel = 0;
	mBattle.GetView()->Execute(ViewCommand::SubUnparallelRage, mId, aAmount, mRageUnparallel, mMaxRageUnparallel);
}

bool Army::CanExecuteUnparallel()
{
	return mRageUnparallel >= mRageThreshold;
}

void Army::SkillUseRage()
{
	SubRage(mRageUnparallel);
}

void Army::GetCenterPointByIndex(int aIndex, Vector3& aPos, Vector3& aRot)
{
	if (mCenterPoints.empty())
	{
		aRot.x = 100;
		return;
	}

	if (aIndex >= mBornPoints.size())
	{
		LOG_FATAL("cant found bornPoint Idx:%d, only has size:%d", aIndex, mBornPoints.size());
		aIndex = 0;
	}

	int gid = mBornPoints[aIndex].mGroupId;
	if (gid >= mCenterPoints.size())
	{
		LOG_WARN("cant find centerPoint by gid %d", gid);
		gid = 0;
	}
	auto& cp = mCenterPoints[gid];
	aPos.Set(cp.mPos);
	aRot.Set(cp.mRot);

	return;
}

const DirectedPosition& Army::GetBornPointByIndex(int aIndex)
{
	if (aIndex >= mBornPoints.size())
	{
		LOG_FATAL("cant found bornPoint Idx:%d, only has size:%d", aIndex, mBornPoints.size());
		return mBornPoints[0];//log_fatal will throw exception 
	}
	return mBornPoints[aIndex];
}

vector<SharedPtr<Unit>> Army::GetUnitByProfession(int aProfession, bool aNeedDead) const
{
	vector<SharedPtr<Unit>> ret;
	for (int i = 0; i < mUnitArr.size(); i++)
	{
		if (!mUnitArr[i]->IsDummy() && !mUnitArr[i]->IsSummoned() && 
			mUnitArr[i]->GetProfession() == aProfession && aNeedDead == mUnitArr[i]->IsDead())
		{
			ret.emplace_back(mUnitArr[i]);
		}
	}
	return ret;
}

int Army::GetSummonPointNum() const
{
	return mSummonPoints.size();
}

const DirectedPosition& Army::GetSummonPointByIndex(int aIndex) const
{
	if (aIndex >= mSummonPoints.size())
	{
		return BattleInstance::mDefaultDirectedPosition;
	}
	return mSummonPoints[aIndex];
}

const DirectedPosition& Army::GetSummonPointByRand() const
{
	int size = mSummonPoints.size();
	if (size <= 0)
	{
		LOG_WARN("SummonPoints is empty");
		return BattleInstance::mDefaultDirectedPosition;
	}
	int idx = mBattle.Rand(size);
	return mSummonPoints[idx];
}

void Army::OnBehaviourPause(bool aPause)
{
	auto* battleConf = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
	int pauseNum = battleConf->GetHeroNumBeastPause();
	if (aPause)
	{
		++mBehaviourStopCount;
		if (mBehaviourPauseStart == 0 && mBehaviourStopCount >= pauseNum)
		{
			mBehaviourPauseStart = mBattle.GetGameTime();
		}
	}
	else
	{
		--mBehaviourStopCount;
		if (mBehaviourPauseStart > 0 && mBehaviourStopCount < pauseNum)
		{
			mBehaviourPauseTime += (mBattle.GetGameTime() - mBehaviourPauseStart);
			mBehaviourPauseStart = 0;
		}
	}
}


inline bool Army::AbleToExecuteArmySkillNow()
{
	return mBehaviourPauseStart == 0;
}


int Army::CountCountryHeroNumber(ECountry aCountry) const
{
	int count = 0;
	for (auto& unit : mActiveUnitArr) {
		if (!unit->IsSummoned() && !unit->IsDummy() && !unit->IsEmptyHp() &&
			(aCountry == ECountry::None || unit->mCountry == aCountry))
		{
			++count;
		}
	}
	return count;
}