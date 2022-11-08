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


#include "SkillProjectileWired.h"
#include "Skill/SkillCarrier.h"
#include "Skill/SkillExecutor.h"
#include "Skill/SkillDefine.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Log/Log.h"




void SkillProjectileWired::Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
    InitBase(aCarrier, aStartPos, aRefTarget);
    mDuration = CONF_TIME_CONVERT(mSkillConf->curvadata().curvelasttime());
}

void SkillProjectileWired::Reset()
{
    ResetBase();

	mDuration = 0;
}

bool SkillProjectileWired::OnTick(int aDeltaTime)
{
    if(mTime == 0)
    {
        mCarrier->OnReachRefTarget( mRefTarget );
    }
    mTime += aDeltaTime;
   
    return mTime < mDuration;
}





