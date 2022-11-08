


#include "BuffModResetBuffTime.h"
#include "Entity/Unit.h"

void BuffModResetBuffTime::StackAdded(int)
{
	//nothing
}

void BuffModResetBuffTime::StackRemoved(int)
{
	//nothing
}

void BuffModResetBuffTime::OnEnable()
{
	for (auto id : *mParams.mBuffIdArr)
	{
		if (!IsValid())
			return;
		auto buff = GetOwner()->GetBuff(id);
		if (buff)
		{
			buff->BuffReset();
		}
	}
}

void BuffModResetBuffTime::OnDisable(bool aShouldTrigger)
{
	//nothing
	mParams.mBuffIdArr = nullptr;
}

