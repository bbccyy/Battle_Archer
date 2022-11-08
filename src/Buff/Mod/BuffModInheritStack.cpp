

#include "BuffModInheritStack.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModInheritStack::StackAdded(int)
{
	//nothing
}

void BuffModInheritStack::StackRemoved(int)
{
	//nothing
}

void BuffModInheritStack::OnEnable()
{
	auto owner = GetOwner();
	if (!owner->HasBuff(mParams.mBuffId))
		return;

	//auto& targetBuff = owner->GetBuff(mParams.mBuffId);
	int tarStack = owner->GetBuff(mParams.mBuffId)->GetStack();
	auto myBuff = GetBuff();
	myBuff->WhenAddSameBuff(tarStack - myBuff->GetStack());
}

void BuffModInheritStack::OnDisable(bool aShouldTrigger)
{
	//nothing
}