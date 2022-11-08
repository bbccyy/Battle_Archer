

#include "BuffModBuffOnStack.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModBuffOnStack::StackAdded(int)
{
	OnStackNumberChange();
}

void BuffModBuffOnStack::StackRemoved(int)
{
	OnStackNumberChange();
}

void BuffModBuffOnStack::OnStackNumberChange()
{
	if (mInProcessing)
	{
		LOG_WARN("OnStackNumberChange but In Processing! buffId %d", GetBuff()->GetId());
		return;
	}
	mInProcessing = true;
	const auto* buff = GetBuff();
	int curStk = buff->GetStack();
	int lv = buff->GetLevel();
	auto owner = GetOwner();
	if (curStk > mLastStack)
	{
		for (auto& action : mParams.mActionArr)
		{
			if (action.mStack <= curStk && action.mStack > mLastStack)
			{
				for (auto id : action.mBuffArr)
				{
					owner->TryReceiveBuff(owner, owner, id, lv);
				}
			}
		}
	}
	else if (curStk < mLastStack)
	{
		for (auto& action : mParams.mActionArr)
		{
			if (action.mStack > curStk && action.mStack <= mLastStack)
			{
				for (auto id : action.mBuffArr)
				{
					owner->RemoveBuffAndTrigger(id, 0);
				}
			}
		}
	}
	mLastStack = curStk;
	mInProcessing = false;
}

void BuffModBuffOnStack::CleanAllBuff()
{
	if (mInProcessing)
	{
		LOG_WARN("CleanAllBuff but In Processing! buffId %d", GetBuff()->GetId());
		return;
	}
	mInProcessing = true;
	if (mLastStack <= 0)
		return;
	auto& owner = GetOwner();
	for (auto& action : mParams.mActionArr)
	{
		if (action.mStack <= mLastStack)
		{
			for (auto id : action.mBuffArr)
			{
				owner->RemoveBuffAndTrigger(id, 0);
			}
		}
	}
	mInProcessing = false;
}

void BuffModBuffOnStack::OnEnable()
{
	mLastStack = 0;
	mInProcessing = false;
	OnStackNumberChange();
}

void BuffModBuffOnStack::OnDisable(bool aShouldTrigger)
{	
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		mLastStack = 0;
		mInProcessing = false;
		mParams.mActionArr.clear();
		return;
	}
	CleanAllBuff();
	mLastStack = 0;
	mInProcessing = false;
}