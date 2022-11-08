

#pragma once
#include "Buff/BuffMod.h"
#include "Entity/UnitDefine.h"
#include "Formula/Formula.h"


class BuffModFormula : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		vector<BuffModPropertyEntry> mEntries;
		EAttribute mApplyType;
		int64 mDelta;  //store changed value 
	} mParams;

public:
	int64 CalculateFormula();
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;

};