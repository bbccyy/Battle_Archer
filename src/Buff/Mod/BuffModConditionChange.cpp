


#include "BuffModConditionChange.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"

void BuffModConditionChange::StackAdded(int)
{
	mAddData = GetBuff()->ScaledValue(mParams.mAdd);
	GetOwner()->RegisterConditionChange(mParams.mMainType, mParams.mRelation, mParams.mTarget, mAddData, mParams.mParamArr);
}

void BuffModConditionChange::StackRemoved(int)
{
	mAddData = GetBuff()->ScaledValue(mParams.mAdd);
	GetOwner()->RegisterConditionChange(mParams.mMainType, mParams.mRelation, mParams.mTarget, mAddData, mParams.mParamArr);
}

void BuffModConditionChange::OnEnable()
{
	mAddData = GetBuff()->ScaledValue(mParams.mAdd);
	GetOwner()->RegisterConditionChange(mParams.mMainType, mParams.mRelation, mParams.mTarget, mAddData, mParams.mParamArr);
}

void BuffModConditionChange::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mAddData = 0;
		return;
	}
	GetOwner()->UnregisterConditionChange(mParams.mMainType, mParams.mRelation, mParams.mTarget, mAddData, mParams.mParamArr);
	mAddData = 0;
}