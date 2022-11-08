
#pragma once
#include "Buff/BuffMod.h"

class BuffModRangeEffectCondition : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int64 mRadius;
		ERangeEffectConditionType mCondition;
		vector<BuffModPropertyEntry> mProperty;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
private:
	vector<SharedPtr<Unit>> mWatchList;
	SharedPtr<Timer<BuffModRangeEffectCondition> > mTimer;
	void ApplyStacked();
	void ApplyStackedWithNum(int);
	void RevertValue();
	bool OnUpdate(Timer<BuffModRangeEffectCondition>& aTimer);
	void GetUnitArrByRelation(vector<SharedPtr<Unit>>& aWatchList);
	int HasHeroInRange();
};