

#pragma once
#include "Buff/BuffMod.h"



class BuffModNoSuckBlood : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int64 mPercent;
	} mParams;
private:
	int64 mCurPercent = 0;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;	
	int64 GetPercent();
};