
#pragma once
#include "Buff/BuffMod.h"



class BuffModPropertyDecImmunity : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
		EAttribute mAttr;
	} mParams;
public:
	void StackAdded(int) override;
	void StackRemoved(int) override;
	void OnEnable() override;
	void OnDisable(bool) override;
};