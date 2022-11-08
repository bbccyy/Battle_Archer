

#pragma once
#include "Buff/BuffMod.h"

class BuffModRangeEffect : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int64 mRadius = 0;
		ESearchTargetRelation TargetType = ESearchTargetRelation::ESearchTargetRelationAll;
		int TimeBeforeEffect = 0;
		int BuffId = 0;
		bool excludeSelf = false;
		bool needDead = false;
		ENeedSummon needSummon = ENeedSummon::EOnlySummon;
		bool removeWhenOutOfRange = false;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
private:
	Unit * mExclueSelfPtr;
	vector<SharedPtr<Unit>> mWatchList;
	vector<pair<int, int>> mRecorder;
	vector<int> mVisitList;
	SharedPtr<Timer<BuffModRangeEffect> > mTimer;
	void GetUnitArrByRelation(vector<SharedPtr<Unit>>& aWatchList);
	bool OnUpdate(Timer<BuffModRangeEffect>& aTimer);
	void SetRecord(int aEntityId, int aTime);
	int GetRecord(int aEntityId);
	bool addVisited(int aEntityId);
	void removeVisited(int aEntityId);
	void CleanRecord(vector<SharedPtr<Unit>>& aWatchList);
};