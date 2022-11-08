/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author liyingbo
* @date $Date$
* @version $Revision$
* @brief
*
**/

#include "BuffModSkillOnEnd.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"
#include "Skill/SkillExecutor.h"
#include "Buff/Buff.h"

void BuffModSkillOnEnd::StackAdded(int)
{
    //nothing
}

void BuffModSkillOnEnd::StackRemoved(int)
{
    //nothing
}

void BuffModSkillOnEnd::OnEnable()
{
    //nothing
}

void BuffModSkillOnEnd::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset)
	{
		mParams.mSkill = nullptr;
		mParams.mSkillBack = nullptr;
		mParams.mSkillId = 0;
		mParams.mSkillIdBack = 0;
		mParams.mSourceType = 0;
		mParams.mIgnoreNoSkill = false;
		mParams.mDisableType = EBuffDisableType::EBuffDisableByTimeOut;
		return;
	}
	if (type == mParams.mDisableType || mParams.mDisableType == EBuffDisableType::EBuffDisableByAny)
	{
		mParams.mSkill->RefreshRefTarget();
		mParams.mSkill->mAncestorSkill = GetBuff()->mAncestorSkill;
		const auto& sourceUtilizer = mParams.mSourceType == 1 ? GetSourceUtilizer() : WeakPtr<Unit>();
		if (mParams.mIgnoreNoSkill)
			GetOwner()->mSkillIdSpecial = mParams.mSkill->GetId();
		if (mParams.mSkill->CanExecute() == CheckResult::Pass)
		{
			for (int r = 0; r < GetBuff()->GetStack(); ++r)
			{
				if (mParams.mSkill->RefreshRefTarget())
					GetOwner()->ExecuteSkill(mParams.mSkill, 0, nullptr, sourceUtilizer);
			}
		}
		else if (mParams.mSkillIdBack > 0 
			&& mParams.mSkillBack->CanExecute() == CheckResult::Pass)
		{
			for (int r = 0; r < GetBuff()->GetStack(); ++r)
			{
				if (mParams.mSkillBack->RefreshRefTarget())
					GetOwner()->ExecuteSkill(mParams.mSkillBack, 0, nullptr, sourceUtilizer);
			}
		}
		if (mParams.mIgnoreNoSkill)
			GetOwner()->mSkillIdSpecial = 0;
	}
	if (GetSourceUtilizer() && mParams.mSkill)
	{
		GetSourceUtilizer()->SetBuffSkillInfo(mParams.mSkill->GetId(), mParams.mSkill->mBeginCount, mParams.mSkill->mEffectTargetCount);
	}
}