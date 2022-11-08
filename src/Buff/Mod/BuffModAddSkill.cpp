

#include "BuffModAddSkill.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"

void BuffModAddSkill::StackAdded(int)
{
	//nothing
}

void BuffModAddSkill::StackRemoved(int)
{
	//nothing
}

void BuffModAddSkill::OnEnable()
{
	int skillLv = mParams.mSkillLevel;
	if (skillLv < 0)
	{
		auto parentSkill = GetBuff()->mAncestorSkill;
		if (parentSkill && !parentSkill.Expired())
		{
			skillLv = parentSkill->GetLevel();
		}
		else
		{
			LOG_WARN("want use parent skill lv, but failed to obtain from Buff[%d]", GetBuff()->GetId());
			skillLv = 1;
		}
	}
	for (auto id : *mParams.mSkillIdArr)
	{
		GetOwner()->AddSkill(id, skillLv);
	}
}

void BuffModAddSkill::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mSkillIdArr = nullptr;
		return;
	}
	for (auto id : *mParams.mSkillIdArr)
	{
		GetOwner()->RemoveSkill(id);
	}
}