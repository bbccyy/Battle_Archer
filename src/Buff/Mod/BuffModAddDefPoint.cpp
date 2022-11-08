
#include "BuffModAddDefPoint.h"
#include "Entity/Unit.h"
#include "View/BattleViewOutput.h"

void BuffModAddDefPoint::StackAdded(int)
{
	//nothing
}

void BuffModAddDefPoint::StackRemoved(int)
{
	//nothing
}

void BuffModAddDefPoint::OnEnable()
{
	auto owner = GetOwner();
	owner->mBossDefActive = true;
	owner->mDefPointNum = mParams.mPointNum;
	owner->mDefType = mParams.mType;  //channel
	owner->GetView()->Execute(ViewCommand::DefendPoint, owner->GetEntityId(), mParams.mPointNum, mParams.mColor);
}

void BuffModAddDefPoint::OnDisable(bool aShouldTrigger)
{
	//do nothing
}