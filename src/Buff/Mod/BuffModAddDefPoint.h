
#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

class BuffModAddDefPoint : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		int32 mPointNum;
		int32 mType;
		int32 mColor;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};