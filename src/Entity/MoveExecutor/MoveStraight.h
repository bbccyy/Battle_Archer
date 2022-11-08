

#pragma once
#include "MoveExecutor.h"
#include "Entity/Unit.h"

typedef struct ParamStraight : public ParamMove
{
public:
	int64 mSpeed = 0;  //base speed(scalar)
	int64 mAccInSec0 = 0; //first order of acceleration
	int64 mAccDInSec = 0; //second order
	bool mNoVerticalMove = false;
}StraightParam;

class MoveStraight : public MoveExecutor
{
public:
	void Init(StraightParam&);
	EMoveStatus OnTick(int aDeltaTime);
	void Reset();
	void Enable();
	void Disable();
	EMoveType Type();
	void RefreshStatus();
	void SetTargetPos(Vector3);
	void SetSpeedParams(int64 aSpeed, int64 aAcc0, int64 aAccD);
private:
	int64 mSpeed;
	int mTime;
	bool mNoVerticalMove;

	int mStayTimeOnReachTarget;

	Vector3 mStartPos;
	Vector3 mCurPos;
	Vector3 mCurRot;

	int64 mSpeed0;
	int64 mAccInSec0;
	int64 mAccDInSec;
};

