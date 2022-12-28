#pragma once
#include "MoveExecutor.h"
#include "Entity/Unit.h"


typedef struct ParamBounce : public ParamMove
{
public:
	int64 mSpeed = 0;						//base speed(scalar)
	int64 mCastRange = 0;
	//const RefTarget* mRefTarget = nullptr;
	vector<Vector2> mPath;
}BounceParam;


class MoveBounce : public MoveExecutor
{
public:
	void Init(BounceParam&);
	EMoveStatus OnTick(int aDeltaTime);
	void Reset();
	void Enable();
	void Disable();
	EMoveType Type();
	void RefreshStatus();
private:
	int mTime;
	//int mTargetEntityId;
	Vector3 mCurPos;
	Vector3 mCurRot;
	int64 mSpeed0, mSpeed;
	int64 mCastRange;
	//const RefTarget* mRefTarget;
	bool mTouchEndH;
	int mPathIndex;
	//bool mIsArmy1 = false;
	
	vector<Vector2> mPath;
};

