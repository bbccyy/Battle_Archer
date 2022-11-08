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
#include "module/SkillData.pb.h"
#include "Framework/Transform.h"
#include "Framework/SharedPool.h"
#include "Entity/MoveExecutor/MoveParabloa.h"

using namespace pb;

class HitHandlerMove;
class MoveExecutor;
struct ControlToken;

class MoveController : public IPoolable
{
public:
    void Reset();
	void Cancel(bool aDisableMove);
    void Init(const SkillMoveData* aConf);
	void LoadAndAnalyzeUpData();
	void LoadAndAnalyzeDownData();
	void LoadAndAnalyzeFallData();

	void SetExecutorDown();
	void SetExecutorFall();

    Vector3 GetTargetPos();
	void SetTime();
	bool IsValid();
	EMoveStatus OnTick(int aDeltaTime);

	SharedPtr<MoveParabloa> mMoveParabloa;
	EMoveStatus mMoveStatus;
	EMoveStatus mParabloaStatus;

	int mTime, mTotalTime, mDownTime;
	int mStayTimeOnPeak;
	int mAnimFallDownTimeLength;

	SharedPtr<Unit> mUtilizer;
    SharedPtr<Unit> mControlledUnit;
    SharedPtr<Unit> mMoveTargetUnit;
	SharedPtr<Unit> mSkillTargetUnit;

	HitHandlerMove* mParent;
    int64 mRelativeDist;
    EDirection mDirection;
    Vector3 mTargetPos;
    const SkillMoveData* mMoveConf;
    int64 mSpeedV;      //垂直方向速度

	bool mHasUp;
	bool mHasPeak;
	bool mHasDown;
	bool mHasFall;

	bool mIsMoveSelf;
    bool mHitAreaBound;
	bool mDamageOrBuffDone;

	int64 mSpeedH;		  //水平速度 
	int64 mSpeedHAcc;	  //水平加速度 
    int64 mMoveUpHeight;  //位移高度
    int64 mMoveDownHeight;  //位移下降高度
    int64 mSpeedUp;     //位移上升速度
    int64 mSpeedDown;   //位移下落速度

    int64 mAccUpInSec0; // 上移加速度 
    int64 mAccDUpInSec;

    int64 mAccDownInSec0; // 下落加速度
    int64 mAccDDownInSec;

	int64 mAccFallInSec0;

	vector<SharedPtr<ControlToken>> mControlStates;  // control states that have been added by this moveExecutor
};

class HitHandlerMove : public HitHandler
{
public:
    HitHandlerMove();
    void Reset();

	bool CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) override;
    void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr) override;
    void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) override;
    bool OnTick(int aDeltaTime) override;
    void Cancel() override;
	void DealDamageOrBuff(const SharedPtr<MoveController>&);
	void CleanUpMoveExecutor(const SharedPtr<MoveController>&, bool aDisableMove = false);

	const SkillData* mSkillConf;

	//vector<SharedPtr<ControlState>> mControlStates;
private:
    vector<SharedPtr<MoveController> > mMoveCtrlerArr;
    SharedPtr<Unit> mUtilizer;
    WeakPtr<SkillCarrier> mSkillCarrier;
	const SkillMoveData* mMoveConf;
	bool mSetVulnerable;

    void ExternalCancelRequest(SharedPtr<Unit> aControlledUnit);
	void TryCleanUpMoveCtrlerArr();
};




