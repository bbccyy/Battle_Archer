
#pragma once
#include "PathDefine.h"
#include "Framework/SharedPool.h"

class GridNode;

class GridMap
{
public:
	GridMap();
	//GridMap(int64 aWidth, int64 aLength, const Vector2& aNodeSize, const Vector2& aOriginPos);
	~GridMap();

	void ReInit(int64 aWidth, int64 aLength, const Vector2& aNodeSize, const Vector2& aOriginPos);
	void Reset();

	//mapping from box position to Vector 1-D index
	int BoxPosition2Index(int64 aX, int64 aZ);

	//mapping from real position to Vector 1-D index
	int Position2Index(int64 aX, int64 aZ);

	//mapping from real position to Box 2-D index
	int Position2Position(int64 aX, int64 aZ, Vector2& aPos);

	//mapping from box position to real position
	void Position2RealPosition(int aX, int aZ, Vector2& aPos);

	//will find nearest position if necessary 
	int Position2PositionForce(int64 aX, int64 aZ, Vector2& aPos);

	GridNode* AddNode(int aIndex, int aBoxX, int aBoxZ, unsigned int aFlag = 0xFF);  //1111 1111

	GridNode* GetOrInitNode(int aBoxX, int aBoxZ);
	GridNode* GetOrInitNode(int aIndex);
	GridNode* GetOrInitNodeForce(int aBoxX, int aBoxZ);

	//calculate unit's block region size accordingly 
	void RegisterGroundMask(int64 aSize);

	//apply unit's block region to map so that others will 
	//take this region into consideration while path finding
	void MarkGround(int aIndex, int64 aSize);

	//disable the block region arround given index
	void RetrieveGround(int aIndex, int64 aSize);

	//find if a real position is located at a walkable box 
	bool Walkable(int64 aX, int64 aZ);

	int* GetNeighbourOffset()
	{
		return NeighbourOffset;
	}

	int64* GetNeighbourCost()
	{
		return NeighbourCosts;
	}

	int64 GetNodeSize()
	{
		return mGridNodeSize.x;
	}

	//given box 2-D position, return manhattan distance between them 
	int64 ManhattanDist(int aX1, int aZ1, int aX2, int aZ2);

	//mark nodes on boundary described by the given vector 
	void ApplyBoundaryNodes(vector<Vector2>& aVec);

	//makr nodes on area given by vector
	void ApplyBlockArea(vector<Vector2>& aVec);

	//input arr contains a list of valid GridMap Tile's index 
	void ApplyBlockAreaManually(vector<int>& aIndexArr);

private:
	//adding nodes at boundary position, setting their Neighbour Flags
	void InitBoundaryNodes();

	//init value: NeighbourOffset and NeighbourCosts
	void InitNeighbourSetting();

private:
	const unsigned int upLeft = 0x13;
	const unsigned int up = 0x9b;
	const unsigned int upRight = 0x89;
	const unsigned int right = 0xcd;
	const unsigned int downRight = 0x4c;
	const unsigned int down = 0x6e;
	const unsigned int downLeft = 0x26;
	const unsigned int left = 0x37;

	const unsigned int mMaskSub = 30000;  //used to shrink the size of ground mask

	bool mHasInited = false;

	int NeighbourOffset[8];	   //stores 8 adjacent node's index offsets
	int64 NeighbourCosts[8];   //and their cost
	int64 orthCost = 0;
	int64 diagCost = 0;
	int64 mCommonNativeCost = 0;
	int64 mBlockNativeCost = 0;
	map<int64, vector<int>> mGroundMaskTable;  //register different mask table according to unit's size 
	map<int64, vector<int>> mGroundMaskAdjust; //used to adjust mask cost based on dist to unit center

	Vector2 mGridNodeSize;   //both x and y direction
	Vector2 mHalfNodeSize;   //both x and y direction, in its half size 
	Vector2 mGridOrigin;     //indicates the very center box's position, usually equals <0, 0>
	int64 mWidth;     //measured in micro meter (10mm in fact)
	int64 mLength;

	int mHalfCol;	// 2 * mHalfCol + 1 == mColNum
	int mHalfRow;
	int mColNum;    //number of box in Column view
	int mRowNum;	//number of box in Row view

	//vector<GridNode*> mGridNodeVec;
	//The index of vector stands for the Index of Node, Counting from bottom-to-up and from left-to-right 
	vector<SharedPtr<GridNode>> mGridNodeVecFromPool;	//vector of grid nodes 
	int mVecSize;										//the size of mGridNodeVec

};