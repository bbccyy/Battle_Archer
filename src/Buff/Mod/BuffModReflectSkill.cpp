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

#include "BuffModReflectSkill.h"
#include "Skill/Skill.h"
#include "Buff/Buff.h"
#include "Entity/Unit.h"

void BuffModReflectSkill::StackAdded(int)
{
    //nothing
}

void BuffModReflectSkill::StackRemoved(int)
{
    //nothing
}

void BuffModReflectSkill::OnEnable()
{
    GetOwner()->IncStateAdjust(StateAdjust::ReflectSkill);
}

void BuffModReflectSkill::OnDisable(bool aShouldTrigger)
{
	mCount = 0;
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
    GetOwner()->DecStateAdjust(StateAdjust::ReflectSkill);
}

void BuffModReflectSkill::ResetValues()
{
    BuffMod::ResetValues();
    mCount = mParams.mCount;
}

bool BuffModReflectSkill::OnActive(Unit* aUtilizer, const Skill* aSkill)
{
    if (!IsValid())
        return false;
    if (mCount <= 0)
        return false;
	if (aSkill->mSkillMainType != mParams.mSkillType
		|| aSkill->IsMasterRageSkill()
		|| aSkill->IsUnparallelledRageSkill()
		|| (aSkill->mSkillChannelType != mParams.mChannelType 
			&& mParams.mChannelType != EDamageChannel::EDamageChannelAny))
	{
		return false;
	}
    --mCount;

	SharedPtr<Skill> skill = SharedPool<Skill>::Get();
	skill->CopyInit(GetOwner(), aSkill);
	skill->SetReflectRefTargetArr(aSkill->GetConstOwner());  
	GetOwner()->ExecuteSkill(skill, 0, nullptr, aSkill->GetConstOwner(), GetOwner());
	return true;
	//aSkill->mAncestorSkill = GetBuff()->mAncestorSkill;
}