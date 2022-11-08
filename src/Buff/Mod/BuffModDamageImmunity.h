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
* @brief ÃâÒßÉËº¦
*
**/

#pragma once
#include "Buff/BuffMod.h"

enum class BuffDamageImmunityType
{	
	Physical = 0,
	Magic = 1,
	All = 2,
	Percent = 3
};


class BuffModDamageImmunity : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
		BuffDamageImmunityType mImmunityType;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;	
};