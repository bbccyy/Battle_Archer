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
* @brief    一个BuffMod，对应一种buff效果
*          通过继承并重载OnEnable与OnDisable来实现具体效果
*
**/

#pragma once
#include "Framework/SharedPool.h"
#include "Framework/Timer.h"
#include "Skill/SkillDefine.h"

class Buff;
class Unit;
class Skill;
enum class BuffSubType;
enum class EAttribute;

enum class EBuffModStatus
{
    Init,
    Enable,
    End
};

enum class BuffDispelTarget
{
    ByMainType,
    BySubType,
    ById
};

enum class BuffModHpOrRageType
{
    ByMaxValue,
    ByCurrentValue
};

class BuffMod : public EnableSharedFromThis<BuffMod>, public IPoolable
{
public:
    struct CommonParams
    {
    public:
        int mDelay = 0;
        bool mEndWhenDamaged = false;
    };
public:
    void Init(BuffSubType, Buff&, int);
    void Reset();
    void Reset(int);
	virtual void OnReset();
    void Disable(bool);
    virtual void ResetValues();
    virtual void StackAdded(int) = 0;
    virtual void StackRemoved(int) = 0;
	virtual bool UnRegisterListener() { return true; };
    void Offset(int);
    void SetCommonParams(CommonParams* aParams);
    bool IsOfType(BuffSubType) const;
	Buff* GetBuff() const;
    const WeakPtr<Unit>& GetOwner() const;
	const WeakPtr<Unit>& GetSourceUtilizer() const;
	const WeakPtr<Skill>& GetAncestorSkill() const;
private:
    int mId = 0;
    BuffSubType mModType;
    CommonParams* mCommonParams = nullptr;
    SharedPtr<Timer<BuffMod> > mBuffModTimer = nullptr;
    Buff* mBuff = nullptr;
    EBuffModStatus mStatus;
protected:
    bool Enable(Timer<BuffMod>&);
    virtual void OnEnable() = 0;
    virtual void OnDisable(bool) = 0;
    
    bool IsValid() const;
};

struct BuffModPropertyEntry
{
public:
	EAttribute mProperty;
	EAttribute mSourceProperty;
	int64 mPercent = 0;
	int64 mAdd = 0;
	int64 mValue = 0;
};

struct BuffModSkillOnHpEntry : public IPoolable
{
public:
	SharedPtr<Skill> mSkill = nullptr;
	WeakPtr<Unit> mSourcer = nullptr;
	EBuffTriggerSkillHpType mHpType = EBuffTriggerSkillHpType::ETriggerSkillHpTypeFixValue;
	int64 mLifeValue = 0;
public:
	void Reset() {
		mSkill = nullptr;
		mSourcer = nullptr;
		mHpType = EBuffTriggerSkillHpType::ETriggerSkillHpTypeFixValue;
		mLifeValue = 0;
	};
};