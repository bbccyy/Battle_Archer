
#pragma once
#include "MoveExecutor.h"


typedef struct ParamParabloa : public ParamMove
{
public:
	int64 mSpeedH = 0;  //horizontal speed(scalar)
	int64 mSpeedHAcc = 0; 
	int64 mSpeedV = 0;  //vertical speed(scalar, could be + or -)
	int64 mAccInSec0V = 0, mAccDInSecV = 0; //first and second order of acceleration of vertical movement
	int64 mTerminateV = 0;  //will stop vertical movement once reach out this altitude
	int64 mTotalMoveV = 0;  //distance limits of vertical movement, control terminate condition
	                    //to avoid missing checkpoint problem, it's accumulated sum, not a fixed altitude value

}ParaParam;


class MoveParabloa : public MoveExecutor
{
public:
	void Init(ParaParam&);
	EMoveStatus OnTick(int aDeltaTime);
	void Reset();
	void Enable();
	void Disable();
	EMoveType Type();
	void SetSpeedH(int64);
	void SetVerticalParam(int64 aSpeedV, int64 aAcc0, int64 aAccD);
	void SetTotalMoveV(int64);  //TODO DELETE
	void SetTerminateV(int64);
	void RefreshStatus();
	bool IsHorizontalDone();
	void SetSpeedV(int64);
	bool HasTerminateV();
	void SetHorizontalStatus(bool);
	bool HasHorizontalMove();
private:
	int64 mSpeedH; 
	int64 mSpeedHAcc; 
	int64 mSpeedV; 
	int64 mAccInSec0V, mAccDInSecV; 
	int64 mTotalMoveV; 
	int64 mTerminateV;

	int mTime;
	bool reachH;
};

