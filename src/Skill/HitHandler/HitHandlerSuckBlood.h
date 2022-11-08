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

#pragma once

#include "HitHandler.h"


class HitHandlerSuckBlood: public  HitHandler
{
public:
	bool CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) override;
    virtual void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
    virtual void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier);

    void Reset();
    
};




