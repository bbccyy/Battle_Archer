

#pragma once
#include "MoveExecutor.h"


typedef struct ParamCurve : public ParamMove
{
public:
	int64 mSpeed = 0;  //base speed(scalar)
	int64 mAngle = 0;  //angle between curve plane and standard vertical plane
	int64 mOffset1 = 0, mOffset2 = 0;  //offset of two control points in B-line
	int64 mAccInSec0[SEG_NUM]; //first order of acceleration of each segments
	int64 mAccDInSec[SEG_NUM]; //second order
}CurveParam;


class MoveCurve : public MoveExecutor
{
public:
	void Init(CurveParam&);
	EMoveStatus OnTick(int aDeltaTime);
	void Reset();
	void Enable();
	void Disable();
	EMoveType Type();
	void RefreshStatus();
	void SetTargetPos(Vector3);
	void SetSpeedParams(int64 aSpeed, const int64 aAccInSec0[SEG_NUM], const int64 aAccDInSec[SEG_NUM]);
private:
	int64 mSpeed;
	RefTarget mRefTarget;
	const SkillCurveData* mMoveConf;
	int mTime;

	Vector3 mStartPos;
	Vector3 mCurPos;
	Vector3 mCurRot;

	Vector3 mForward;
	Vector2 mRight;

	int64 mPosOnLine;
	int64 mLineLen;
	int64 mCurTargetLen; // 曲线分成了3段，当前段的目标长度
	int64 mSinDeflection;//曲线面倾斜角度的sin，以DENOM为分母
	int64 mCosDeflection;


	int64 mSpeed0;
	int64 mAccInSec0[SEG_NUM];
	int64 mAccDInSec[SEG_NUM];
	int64 mAngle;
	int64 mOffset1;
	int64 mOffset2;

	int64 mControlPoint1;
	int64 mControlPoint2;
	int64 mBezierCoef3;
	int64 mBezierCoef2;
	int64 mBezierCoef1;

	//EProjectileCurveStatus mStatus;
	int mSegIndex;


};

