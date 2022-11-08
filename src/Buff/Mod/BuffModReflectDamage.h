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
* @brief 反射伤害
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Buff/Buff.h"

class Skill;
enum class ReflectType
{
    Physical = 1,
    Magical = 2,
    PhysicalAndMagical = 0
};
// 反弹数值计算方式    
enum class ReflectValueType
{
	FixValue = 0,
	ByAttribute = 1	
};


class BuffModReflectDamage : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        ReflectType mReflectType = ReflectType::Physical;
		ReflectValueType mReflectValueType = ReflectValueType::FixValue;
		BuffAttrSource mAttrSource = BuffAttrSource::SourceUtilizer;
		BuffAttrId mAttrId = BuffAttrId::Hp;
        int64 mPercent = 0;
        int64 mAdd = 0;
		int64 mPercentByAttr = 0;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void OnActive(Unit*, const Skill*, int64);
};