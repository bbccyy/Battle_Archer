#pragma once
#include "MoveExecutor.h"
#include "Entity/Unit.h"
#include "Path/PathDefine.h"

class PathFindingMgr;

typedef struct ParamPath : public ParamMove
{
public:
	int64 mSpeed = 0;  //base speed(scalar)
	int64 mCastRange = 0;
	const RefTarget* mRefTarget = nullptr;
	PathFindingMgr* mPathMgr = nullptr;
	bool mIsArmy1 = false;
}PathParam;


class MovePath : public MoveExecutor
{
public:
	void Init(PathParam&);
	EMoveStatus OnTick(int aDeltaTime);
	void Reset();
	void Enable();
	void Disable();
	EMoveType Type();
	void RefreshStatus();
private:
	int mTime;
	int mTargetEntityId;
	Vector3 mCurPos;
	Vector3 mCurRot;
	int64 mSpeed0, mSpeed;
	int64 mCastRange;
	const RefTarget* mRefTarget;
	bool mTouchEndH;
	int mPathIndex;
	bool mIsArmy1 = false;

	PathFindingMgr* mPathMgr;
	vector<Vector2> mPath;
	PathCompleteState mPathState;

	const int64 mThreshouldDist = 300000;   //6 meter, within this dist, we change frequence of refreshing Path
	const int64 mThreshouldDist2 = 90000000000;   //mThreshouldDist2 = mThreshouldDist^2
	const int mInF = 500;					//500ms for each search
	const int mOutF = 2000;					//2000ms for each search
	int mFT = 2000;							//current threshould 
	int mF = 0;								//current ms within a search loop 

};

