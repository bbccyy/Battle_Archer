#pragma once
#include "MoveExecutor.h"
#include "Entity/Unit.h"

typedef struct ParamTrace : public ParamMove
{
public:
	int64 mSpeed = 0;  //base speed(scalar)
	int64 mAccInSec0 = 0; //first order of acceleration
	int64 mAccDInSec = 0; //second order
	int64 mCastRange = 0;
	const RefTarget* mRefTarget;
	bool mNoVerticalMove = false;
	int64 mFaceToTargetX = 0;
	int64 mFaceToTargetZ = 0;
	bool mDontPlayAnim = false;
}TraceParam;


class MoveTrace : public MoveExecutor
{
public:
	void Init(TraceParam&);
	EMoveStatus OnTick(int aDeltaTime);
	void Reset();
	void Enable();
	void Disable();
	EMoveType Type();
	void RefreshStatus();
	void SetSpeedParams(int64 aSpeed, int64 aAcc0, int64 aAccD);
	void SetRefTarget(const RefTarget* aRefTarget);
	void SetRingPosition(int aIndex, int aTotalNum);
private:
	int mTime;
	int mTargetEntityId;
	Vector3 mCurPos;
	Vector3 mCurRot;
	int64 mSpeed0, mSpeed;
	int64 mAccInSec0; 
	int64 mAccDInSec; 
	int64 mCastRange;
	const RefTarget* mRefTarget;
	bool mNoVerticalMove;
	bool mTouchEndH;
	int64 mFaceToTargetX;
	int64 mFaceToTargetZ;
	int mDontPlayAnim = false;
	int mRingIndex;
	int mTotalRingNum;

};

