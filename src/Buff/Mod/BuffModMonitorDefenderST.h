

#pragma once
#include "Buff/BuffMod.h"
#include "Framework/FunctionContainer.h"

struct BattleEvent;

class BuffModMonitorDefenderST : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
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
	bool mIsPlat = false;
	int mEventKey = 0;
	const IFunctionContainer<void, const BattleEvent&>* mFunc = nullptr;
};