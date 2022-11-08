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



class BuffModHitDownImmunity : public BuffMod
{
public:
	struct Params : public BuffMod::CommonParams
	{
	public:
	} mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;	
};