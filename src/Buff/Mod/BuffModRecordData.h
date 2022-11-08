

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"
#include "Framework/FunctionContainer.h"

struct BattleEvent;

enum class EBuffRecordDataType 
{
	Damage = 0,			//伤害 
	Heal = 1,			//治疗  
	Counter,			//次数  
	DamageToSelfHpRate, //伤害占自身血量百分比  

	_Count
};

class BuffModRecordData : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		ETriggerRelation mBody;
		ETriggerMajor mMajor;
		int mSub = 0;
		EBuffRecordDataType mDataType;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
	void TryTriggerMod(const BattleEvent&);
	bool RegisterListener();
	bool UnRegisterListener() override;
private:
	int mEventKey = 0;
	const IFunctionContainer<void, const BattleEvent&>* mFunc = nullptr;
};