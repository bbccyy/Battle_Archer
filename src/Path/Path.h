
#pragma once
#include "PathDefine.h"
#include "BinaryHeap.h"

class GridNode;
class GridMap;

class Path
{
public:
	Path();
	~Path();

	void SetSearchNum(int aNum)
	{
		mMaxSearchNum = aNum;
	}

	void Init(int aEntityId, GridMap* aGridMap, int aMaxSearchNum, int aSkipNum)
	{
		mEntityId = aEntityId;
		mGridMap = aGridMap;
		mMaxSearchNum = aMaxSearchNum;
		mSkipNum = aSkipNum;
	}

	void Reset();

	void PreparePath(Vector2 aStart, Vector2 aTarget, int64 aCastRange, int aVersionNum);

	void CalculatePath();

	void Complete();

	void CalculatePredefine(Vector2& aTargetPos);

	vector<Vector2>& GetPath()
	{
		return mVectorPath;
	}

	PathCompleteState GetState()
	{
		return mState;
	}

	void SetPredefinedPath(vector<Vector2>& aVec);

	int SyncProgress(Vector2& aVec);

	void SetPredefinedPathIndex(int);

public:
	int mEntityId = 0;			//owner's ID 
	int mCurrentIndex = -1;		//owner's current position mapping to gridMap's vector index, used only for updateLocation 
	int64 mSize = 0;			//owner's size 

	GridNode* mCurrentNode = nullptr;
	GridNode* mStartNode = nullptr;
	GridNode* mTargetNode = nullptr;
	GridNode* mBestNode = nullptr;
	int64 mCastRange = 0;

	vector<Vector2> mVectorPath;

	PathCompleteState mState = PathCompleteState::PathCompleteState_NotCalculated;

	vector<Vector2> mPredefinedPath;

	int mPositiveNextIdx = 0;   //denotes the next wanted point in path using positive diretion(from start to end)

	bool mUsePredefinedPath = false;

private:
	int GetDir(int aX1, int aZ1, int aX2, int aZ2);

	// smooth path phase 1
	void PostPathProcess();

	bool IsWalkableA2B(Vector2& aA, Vector2& aB, int64 aStepDist);

private:
	int mVersion = 0;
	int mMaxSearchNum = 200;
	int mSkipNum = 2;

	GridMap* mGridMap = nullptr;
	BinaryHeap* mHeap = nullptr;

	int* neighbourOffsets;
	int64* neighbourCosts;
};