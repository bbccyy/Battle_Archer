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
* @brief Buff管理器
*
**/

#pragma once
#include <unordered_map>
#include <unordered_set>
#include "Framework/SharedPtr.h"
#include "Framework/MapOnVector.h"
#include "BuffMod.h"
using std::vector;

class Buff;
//class BuffMod;
class Unit;
class BattleViewOutput;
struct BuffHitCondition;
namespace pb
{
    class BuffData;
}
using pb::BuffData;
using std::unordered_map;
using std::unordered_set;

enum class BuffType;
enum class BuffSubType;

class BuffMgr
{
public:
    BuffMgr(WeakPtr<Unit>, BattleViewOutput&);
    void Reset();
    const MapOnVector<int, SharedPtr<Buff> >& GetBuffMap() const;
    bool TryAddBuff(const SharedPtr<Unit>&, const SharedPtr<Unit>&, int aBuffId, int aLevel, WeakPtr<Skill> aAncestorSkill = WeakPtr<Skill>(), int aBTDel = 0, bool aAbleToInterrupt = true);
    vector<BuffMod*> SearchMod(BuffSubType);
    void EndOnDamage(BuffMod*);
    void CheckEndOnDamage();
    bool RemoveByBuffType(const vector<BuffType>& aTypeArr, int aPartialCount, int aByBuffId, bool aShouldTrigger = false, int aCleanLv = 0);
    bool RemoveByBuffSubType(const vector<BuffSubType>& aSubTypeArr, int aPartialCount, int aByBuffId, bool aShouldTrigger = false, int aCleanLv = 0);
    bool RemoveBuff(int, int, bool);
    bool RemoveBuff(const vector<int>& aIdArr, int aPartialCount, int aByBuffId, bool aShouldTrigger = false);
    bool RemoveBuffById(int);
	void FilterBuffByBeControlledMark();
	void FilterBuffByShapeShiftMark();
    void Clear(bool aShouldTrigger = false);
    void CleanListener();
	void OnTick();
	WeakPtr<Unit> GetOwner() const;
	int CountBuffLayerByMainType(BuffType) const;
	int CountBuffLayerBySubType(BuffSubType) const;
	int CountBuffLayerByBuffIdOR(const vector<int>&) const;
	int CountBuffLayerByBuffIdAND(const vector<int>&) const;
	bool CheckBuffExistenceBySubType(BuffSubType) const;
	bool CheckBuffExistenceBySubTypeOR(vector<BuffSubType>&) const;
	bool HasBuff(int aBuffId) const;
	WeakPtr<Buff> GetBuff(int aBuffId);
private:

	bool HasInRemove(int);
	bool hasInRemoveSub(int, vector<int>&);

	MapOnVector<int, SharedPtr<Buff> > mBuffMap;
    vector<BuffMod*> mEndOnDamageMods;	
	
	vector<int> mBuffInRemove1;
	vector<int> mBuffInRemove2;
	vector<int> mBuffInRemove3;
	vector<int> mBuffInRemove4;
	int mBuffInRemove5 = 0;

    //避免在buff运行中把自己干掉，没有人持有它，所以先找个地方存者，然后统一清理 
    unordered_set<SharedPtr<Buff> > mBuffSetRemoved;
    //vector<BuffMod*> mSearchResult; SearchMod需要支持可重入
    WeakPtr<Unit> mOwner = nullptr;
    BattleViewOutput* mView = nullptr;
	bool mBuffNumberChanged = false;
	bool mInClean = false;

    SharedPtr<BuffHitCondition> CreateBuffHitCondition(const BuffData*, Unit* aUtilizer = nullptr);
};