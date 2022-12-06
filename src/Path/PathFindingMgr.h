#pragma once
#include "PathDefine.h"

class Path;
class GridMap;

class PathFindingMgr
{
public:
	PathFindingMgr();
	~PathFindingMgr();

	//you change battle field, you change current map setting  
	void InitMap(int64 aWidth, int64 aLength, const Vector2& aNodeSize, const Vector2& aOriginPos);

	//mark nodes on boundary described by the given vector 
	void ApplyBoundaryNodes(vector<Vector2>& aVec);

	//makr nodes on area given by vector
	void ApplyBlockArea(vector<Vector2>& aVec);

	//input arr contains a list of valid GridMap Tile's index 
	void ApplyBlockAreaManually(vector<int>& aIndexArr);

	//called by Maneuver module, trigger a new path finding process 
	void StartPath(int aEntityId, Vector2 aStartPos, Vector2 aTargetPos, int64 aCastRange);

	//return path finding results: a path vector && state of result
	PathCompleteState GetPath(int aEntityId, vector<Vector2>& aPath);

	//called by any outer module that need to refresh the given Unit's current location 
	void UpdateLocation(int aEntityId, Vector2& aPos, int64 aSize);

	//register unit's preset location when complete a path finding process 
	void RegisterPreSetLocation(Vector2& aPos, int64 aSize, int aEntityId, bool aIsArmy1);

	//unregister unit's preset location when standing still 
	void UnregisterPreSetLocation(int aEntityId, bool aIsArmy1 = true);

	//called by Unit before starting path finding, it applies preset location from all alliance 
	void TryApplyPreSetLocation(bool aIsArmy1);

	//denotes the end of path 
	int PreSetLocation(Vector2& aPos, int64 aSize);

	//clean up pre set location 
	void CleanUpPreSet();

	//set predefined path to specific unit 
	void SetPredefinedPath(int aEntityId, vector<Vector2>& aVec);

	//sync current progression to Predefined Path
	int SyncPathProgress(int aEntityId, Vector2& aVec);

	void SetMaxSearchNum(int aNum)
	{
		mMaxSearchNum = aNum;
	}

	void SetSkipNum(int aNum)
	{
		mSkipNum = aNum;
	}
public:
	bool mJustNavigate = false;

private:

	Path * GetOrInitPath(int aEntityId);

	int GetVersionId()
	{
		mVersionId++;
		return mVersionId;
	}

private:

	int mVersionId = 0;				//will increase with every search

	int mMaxSearchNum = 200;		//used in path finding 

	int mSkipNum = 2;				//skip the first # of nodes in path 
	
	GridMap * mGridMap = nullptr;   //grid map where path finding applies
	
	vector<Path*> mPathVec;			//one Path instance for one entity

	vector<Vector2> mPreSet;        //denotes the point on the end side of path

	vector<Vector3> mPreSetByArmy1; //stores end points of Army1's active paths
	vector<Vector3> mPreSetByArmy2; //that of Army2

	bool mApplied = false;			//denotes weather TryApplyPreSetLocation has been called this round 
	
};