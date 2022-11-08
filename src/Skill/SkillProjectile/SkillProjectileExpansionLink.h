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

#include "SkillProjectileLine.h"


class SkillProjectileExpansionLink : public SkillProjectileLine
{
public:
    void Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget) override;
};

