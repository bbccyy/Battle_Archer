/**********************************************************************************************************************
 *
 * Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
 * $Id$
 *
 **********************************************************************************************************************/
 
/**
 * @file $HeadURL$
 * @author $Author$
 * @date $Date$
 * @version $Revision$
 * @brief
 *
 **/


#include "SkillProjectileExpansionLink.h"
#include "Skill/SkillCarrier.h"
#include "Skill/SkillExecutor.h"
#include "Skill/SkillDefine.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Log/Log.h"




void SkillProjectileExpansionLink::Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
    InitBase(aCarrier, aStartPos, aRefTarget);
    
	InitMoveParam();
    mStayTimeOnReachTarget = CONF_TIME_CONVERT(mSkillConf->curvadata().curvelasttime());
	
}



