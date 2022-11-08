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

#include "BuffModSpecifyBeTargetSkill.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"

void BuffModSpecifyBeTargetSkill::StackAdded(int)
{
    //nothing
}

void BuffModSpecifyBeTargetSkill::StackRemoved(int)
{
    //nothing
}

void BuffModSpecifyBeTargetSkill::OnEnable()
{    
	GetOwner()->SetSpecifyBeTargetSkills(mParams.mSpecifyBeTargetSkills);
    
}

void BuffModSpecifyBeTargetSkill::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mSpecifyBeTargetSkills.clear();
		return;
	}
	GetOwner()->ResetSpecifyBeTargetSkills(mParams.mSpecifyBeTargetSkills);
}