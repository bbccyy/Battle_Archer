

#include "BuffModMoveControlImmunity.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModMoveControlImmunity::StackAdded(int)
{
	//nothing
}

void BuffModMoveControlImmunity::StackRemoved(int)
{
	//nothing
}

void BuffModMoveControlImmunity::OnEnable()
{
	GetOwner()->IncStateAdjust(StateAdjust::MoveControlImmunity);
}

uint32 BuffModMoveControlImmunity::GetEnergyLevel()
{
	return mParams.mEnergyLevel;
}

void BuffModMoveControlImmunity::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	GetOwner()->DecStateAdjust(StateAdjust::MoveControlImmunity);
}