

#pragma once
#include "Buff/BuffMod.h"
#include "Skill/RefTarget.h"

struct ControlToken;

class BuffModFear : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		int mType = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
	void ResetValues() override;   //一定要先reset数据再使用，因为这是个IPoolable的货，会产生cpp lua不一致问题 
private:
	SharedPtr<ControlToken> mControlState = nullptr;
	Vector3 mMoveTarget = Vector3(0, 0, 0);
	RefTarget mRefTarget;
	bool mInitTarget = false;
	bool mMoveDone = false;
	bool Move(int);
};