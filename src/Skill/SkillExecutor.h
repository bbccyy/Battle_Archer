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

#include <vector>

#include "Framework/SharedPtr.h"
#include "Framework/Timer.h"
#include "Framework/Transform.h"
#include "module/SkillData.pb.h"
#include "module/AvatarData.pb.h"
#include "RefTarget.h"

using namespace std;
using namespace pb;
class Unit;
class Skill;
class SkillCarrier;

enum class ESkillStatus
{
    Init,  // 技能数据初始化 
    Show,  // 展示 
    Begin, // 开始前摇 
    Emit,  // 关键帧时发出技能 
    Interrupted, // 打断 
    End  // 技能结束 
};


class SkillExecutor : public EnableSharedFromThis<SkillExecutor>, public IPoolable
{
public:    
    int Init(SharedPtr<Unit> aOwner, SharedPtr<Skill> aSkill, int aDelay, WeakPtr<SkillExecutor> aParent);
    void Reset();

    void Interrupt();
    void WhenSomeSkillInterrupted(const SharedPtr<SkillExecutor>& aSkillExecutor );
	void CleanDefPointEvent();
	void TryAddDefPointEvent();

    const SkillData* GetSkillConf() const;
    const AnimData* GetAnimConf() const;
    const SharedPtr<Skill> GetSkill() const;
    bool IsChild() const;
    const WeakPtr<SkillExecutor> GetParent() const;
    int GetStartTime() const;
    const vector<RefTarget>& GetRefTargetArr() const;
    int GetCurPhase() const;
    bool IsInactive() const;
    bool WillPlayHitAnim() const;
	void SetSourceUnit(SharedPtr<Unit>);
	void SetReflecter(SharedPtr<Unit>);
	SharedPtr<Unit> GetSourceUnit();

	int mBeginTime = 0;

	int mRegisterDyingTime = 0;

protected:
    void EmitCarrier();
    void startChildSkill();
    bool GetSocketPos(const AnimData* aAnimConf, int aAnimStartTime, const string& aSocketName, int aPhaseIndex, Vector3& aPos) const;
	void RefreshSpeedFactor();
private:
	//A给B加了一个buff，buff触发了一个技能，那这个技能的mSourceUnit=A 
	SharedPtr<Unit> mSourceUnit = nullptr;
    SharedPtr<Unit> mOwner = nullptr;
    SharedPtr<Unit> mReflecter = nullptr;
    SharedPtr<Skill> mSkill = nullptr;
    const SkillData* mSkillConf = nullptr;
    const AnimData* mAnimConf = nullptr;
    
	bool mIsChild = false;
	WeakPtr<SkillExecutor> mAncestors = nullptr;
    WeakPtr<SkillExecutor> mParent = nullptr;
	WeakPtr<Skill> mAncestorSkill = nullptr;
    
    ESkillStatus mStatus = ESkillStatus::End;
    int mCurPhase = 0;

    vector<RefTarget> mRefTargetArr;
    vector<WeakPtr<SkillCarrier> > mCarrierArr;

    int mStartTime = 0;
    int mKeyFrameTime = 0;
	int mSpeedFactor = 0;
    SharedPtr<Timer<SkillExecutor> > mTimer = nullptr;

    bool OnShow(Timer<SkillExecutor>&);
    bool OnBegin(Timer<SkillExecutor>&);
    bool OnKeyFrame(Timer<SkillExecutor>&);
    bool OnPhase(Timer<SkillExecutor>&);
    bool OnEnd(Timer<SkillExecutor>&);

	//void TryRegisterTextShiftInfo();
	//void TryUnregisterTextShiftInfo();

	void SendSkillEmitCMD();
};



