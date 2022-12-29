#include "BuffModChgArcherSkill.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "Skill/Skill.h"


void BuffModChgArcherSkill::OnEnable()
{
	auto& owner = GetOwner();
	auto archerSkill = owner->GetArcherSkill();

	if (!archerSkill)
	{
		return;
	}

	if (mParams.mKeyList.size() != mParams.mValueList.size())
	{
		LOG_WARN("Invalid Change Archer Skill Mod!, BuffId = %d", GetBuff()->GetId());
		return;
	}

	for (int i = 0; i < mParams.mKeyList.size(); ++i)
	{
		auto type = static_cast<EArcherParamsType>(mParams.mKeyList[i]);
		archerSkill->mArcherParam.SetValue(type, mParams.mValueList[i]);
	}
}

void BuffModChgArcherSkill::StackAdded(int)
{
}

void BuffModChgArcherSkill::StackRemoved(int)
{
}

void BuffModChgArcherSkill::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mKeyList.clear();
		mParams.mValueList.clear();
		return;
	}
	mParams.mKeyList.clear();
	mParams.mValueList.clear();
}