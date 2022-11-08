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
* @brief 持续释放某技能（该技能为被动技能=没有技能动作，不影响主动释放的技能）
*
**/

#pragma once
#include "Buff/BuffMod.h"

class Skill;

class BuffModRepeatSkill : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int mSkillId = 0;
        int mInterval = 0;
        int mCount = 0;
        SharedPtr<Skill> mSkill = nullptr;
		int mSourceType = 0;
		int mCastCondition = 0;
		int mValueType = 0;
		int64 mValue = 0;
		bool mIgnoreNoSkill = false;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
    void ResetValues() override;
	void OnReset() override;
private:
    int mCount = 0;
	int64 mFixValue = 0;
	int mRecordCount = 0;
    SharedPtr<Timer<BuffModRepeatSkill> > mTimer = nullptr;
    bool ExecuteSkill(Timer<BuffModRepeatSkill>&);
	bool ExecuteSkillUsingRecordData(Timer<BuffModRepeatSkill>&);
};