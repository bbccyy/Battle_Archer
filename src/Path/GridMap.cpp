

#include "GridMap.h"
#include "GridNode.h"
#include <math.h>

GridMap::GridMap()
{

}

GridMap::~GridMap()
{
	
}

//GridMap::GridMap(int64 aWidth, int64 aLength, const Vector2& aNodeSize, const Vector2& aOriginPos)
//	:mGridOrigin(aOriginPos)
//	,mGridNodeSize(aNodeSize)
//	,mWidth(aWidth)
//	,mLength(aLength)
//{
//	ReInit(aWidth, aLength, aNodeSize, aOriginPos);
//}

void GridMap::ReInit(int64 aWidth, int64 aLength, const Vector2& aNodeSize, const Vector2& aOriginPos)
{
	mGridOrigin = aOriginPos;
	mGridNodeSize = aNodeSize;
	mHalfNodeSize = aNodeSize;
	mWidth = aWidth;
	mLength = aLength;

	mHalfNodeSize.x = mHalfNodeSize.x / 2;
	mHalfNodeSize.z = mHalfNodeSize.z / 2;

	int halfWidth = aWidth / 2 - mHalfNodeSize.x;
	mHalfCol = halfWidth % aNodeSize.x == 0 ? halfWidth / aNodeSize.x : halfWidth / aNodeSize.x + 1;
	mColNum = 2 * mHalfCol + 1;

	int halfLength = aLength / 2 - mHalfNodeSize.z;
	mHalfRow = halfLength % aNodeSize.z == 0 ? halfLength / aNodeSize.z : halfLength / aNodeSize.z + 1;
	mRowNum = 2 * mHalfRow + 1;

	Reset();
	mVecSize = mColNum * mRowNum;
	mGridNodeVecFromPool.resize(mVecSize);

	mCommonNativeCost = aNodeSize.x * 7;
	mBlockNativeCost = mCommonNativeCost * 100;
	InitBoundaryNodes();
	InitNeighbourSetting();

	mHasInited = true;
}

void GridMap::Reset()
{
	for (int i = 0; i < mGridNodeVecFromPool.size(); i++)
	{
		if (mGridNodeVecFromPool[i])
		{
			//mGridNodeVecFromPool[i]->Reset();
			mGridNodeVecFromPool[i].Release();
		}
	}
	mGridNodeVecFromPool.clear();
	mGroundMaskTable.clear();
	mGroundMaskAdjust.clear();
	mHasInited = false;
}

int GridMap::BoxPosition2Index(int64 aX, int64 aZ)
{
	return mColNum * aZ + aX;
}

int GridMap::Position2Index(int64 aX, int64 aZ)
{
	if (aX < 0)
		aX = aX - mHalfNodeSize.x;
	else
		aX = aX + mHalfNodeSize.x;
	if (aZ < 0)
		aZ = aZ - mHalfNodeSize.z;
	else
		aZ = aZ + mHalfNodeSize.z;

	int colIdx = mHalfCol + aX / mGridNodeSize.x;
	int rowIdx = mHalfRow + aZ / mGridNodeSize.z;

	if (colIdx < 0) colIdx = 0;
	else if (colIdx >= mColNum) colIdx = mColNum - 1;

	if (rowIdx < 0) rowIdx = 0;
	else if (rowIdx >= mRowNum) rowIdx = mRowNum - 1;

	return mColNum * rowIdx + colIdx;
}

int GridMap::Position2Position(int64 aX, int64 aZ, Vector2& aPos)
{
	/*int colIdx = mHalfCol + aX / mGridNodeSize.x;
	int rowIdx = mHalfRow + aZ / mGridNodeSize.z;*/
	if (aX < 0)
		aX = aX - mHalfNodeSize.x;
	else
		aX = aX + mHalfNodeSize.x;
	if (aZ < 0)
		aZ = aZ - mHalfNodeSize.z;
	else
		aZ = aZ + mHalfNodeSize.z;

	int colIdx = mHalfCol + aX / mGridNodeSize.x;
	int rowIdx = mHalfRow + aZ / mGridNodeSize.z;

	if (colIdx < 0) colIdx = 0;
	else if (colIdx >= mColNum) colIdx = mColNum - 1;

	if (rowIdx < 0) rowIdx = 0;
	else if (rowIdx >= mRowNum) rowIdx = mRowNum - 1;

	aPos.x = colIdx;
	aPos.z = rowIdx;

	return mColNum * rowIdx + colIdx;
}

int GridMap::Position2PositionForce(int64 aX, int64 aZ, Vector2& aPos)
{
	Position2Position(aX, aZ, aPos);
	if (aPos.x < 0) aPos.x = 0;
	if (aPos.x >= mColNum) aPos.x = int64(mColNum) - 1;
	if (aPos.z < 0) aPos.z = 0;
	if (aPos.z >= mRowNum) aPos.z = int64(mRowNum) - 1;
	return mColNum * aPos.z + aPos.x;
}

void GridMap::Position2RealPosition(int aX, int aZ, Vector2& aPos)
{
	aPos.x = (aX - mHalfCol) * mGridNodeSize.x;
	aPos.z = (aZ - mHalfRow) * mGridNodeSize.z;
}

int64 GridMap::ManhattanDist(int aX1, int aZ1, int aX2, int aZ2)
{
	int a = abs(aX1 - aX2);
	int b = abs(aZ1 - aZ2);
	if (a >= b)
	{
		int c = a - b;
		return c * orthCost + (a - c) * diagCost;
	}
	else
	{
		int c = b - a;
		return c * orthCost + (b - c) * diagCost;
	}
	return 0;
}

GridNode* GridMap::AddNode(int aIndex, int aBoxX, int aBoxZ, unsigned int aFlag)
{
	if (mGridNodeVecFromPool[aIndex])
	{
		mGridNodeVecFromPool[aIndex]->SetFlag(aFlag);
		return mGridNodeVecFromPool[aIndex].Get();
	}
	auto tmp = SharedPool<GridNode>::Get();
	tmp->Init(aIndex, aBoxX, aBoxZ, aFlag);
	mGridNodeVecFromPool[aIndex] = tmp;
	return tmp.Get();

	//GridNode* tmp = new GridNode(aIndex, aBoxX, aBoxZ, aFlag);
	//mGridNodeVec[aIndex] = tmp;
	//return tmp;
}

GridNode* GridMap::GetOrInitNode(int aBoxX, int aBoxZ)
{
	int index = BoxPosition2Index(aBoxX, aBoxZ);
	if (index < 0 || index >= mVecSize)
		return nullptr;
	if (mGridNodeVecFromPool[index])
	{
		return mGridNodeVecFromPool[index].Get();
	}
	return AddNode(index, aBoxX, aBoxZ);
}

GridNode* GridMap::GetOrInitNode(int aIndex)
{
	if (aIndex < 0 || aIndex >= mVecSize)
		return nullptr;
	if (mGridNodeVecFromPool[aIndex])
	{
		return mGridNodeVecFromPool[aIndex].Get();
	}
	int boxZ = aIndex / mColNum;
	int boxX = aIndex - boxZ * mColNum;
	return AddNode(aIndex, boxX, boxZ);  
}

GridNode* GridMap::GetOrInitNodeForce(int aBoxX, int aBoxZ)
{
	Vector2 tmp;
	Position2PositionForce(aBoxX, aBoxZ, tmp);
	return GetOrInitNode(tmp.x, tmp.z);
}

void GridMap::InitBoundaryNodes()
{
	int lastLineIdx = mColNum * (mRowNum - 1);

	AddNode(0, 0, 0, upLeft);
	AddNode(mColNum - 1, mColNum - 1, 0, upRight);
	AddNode(lastLineIdx, mColNum - 1, mRowNum - 1, downLeft);
	AddNode(mVecSize - 1, 0, mRowNum - 1, downRight);

	for (int i = 1; i < mColNum - 1; ++i)
	{
		AddNode(i, i, 0, up);
		AddNode(lastLineIdx + i, i, mRowNum - 1, down);
	}
	for (int j = 2; j < mRowNum; ++j)
	{
		AddNode(j * mColNum - 1, mColNum - 1, j - 1, right);
		AddNode((j - 1) * mColNum, 0, j - 1, left);
	}
}

void GridMap::ApplyBlockArea(vector<Vector2>& aVec)
{
	if (aVec.size() != 2) return;
	Vector2 aPosMin, aPosMax;
	Position2PositionForce(aVec[0].x, aVec[0].z, aPosMin);
	Position2PositionForce(aVec[1].x, aVec[1].z, aPosMax);
	for (int i = aPosMin.x; i <= aPosMax.x; i++)
	{
		for (int j = aPosMin.z; j <= aPosMax.z; j++)
		{
			auto node = GetOrInitNode(i, j);
			if (node)
			{
				node->AddNativeCost(mBlockNativeCost);
			}
		}
	}
}

void GridMap::ApplyBoundaryNodes(vector<Vector2>& aVec)
{
	if (aVec.size() < 3) return;
	Vector2 aPos1, aPos2;
	Position2PositionForce(aVec[0].x, aVec[0].z, aPos1);
	for (int idx = 1; idx < aVec.size(); ++idx)
	{
		auto node = GetOrInitNode(aPos1.x, aPos1.z);
		if (node) node->AddNativeCost(mBlockNativeCost);

		Position2PositionForce(aVec[idx].x, aVec[idx].z, aPos2);
		int xStep = 0;
		if (aPos2.x > aPos1.x) xStep = 1;
		else if (aPos2.x < aPos1.x) xStep = -1;
		int zStep = 0;
		if (aPos2.z > aPos1.z) zStep = 1;
		else if (aPos2.z < aPos1.z) zStep = -1;

		int a = abs(aPos2.x - aPos1.x);  //number of boxes in x-axis
		int b = abs(aPos2.z - aPos1.z);  //number of boxes in z-axis

		if (a >= b)
		{ //x-axis is longer than z, so make step based on x-axis
			int c = 0;     // c : distance till jump
			if (b > 0)     // b : num of jump
			{
				c = a / (b + 1);     
				if (c == 0) c = 1;   //when a == b
			}
			int j = 1, k = 0;		 //j:dist counter,  k:used num of jump
			for (int i = 0; i < a; ++i)
			{
				aPos1.x += xStep;
				auto node = GetOrInitNode(aPos1.x, aPos1.z);
				if (node) node->AddNativeCost(mBlockNativeCost);

				if (k < b)  //still can jump 
				{
					if (j >= c)  //able to jump 
					{
						j = 1;   //reset counter 
						k++;	 //increae used jump
						aPos1.z += zStep;  //apply jump 
						auto node = GetOrInitNode(aPos1.x, aPos1.z);
						if (node) node->AddNativeCost(mBlockNativeCost);
					}
					else
					{
						++j;	//increse used distance 
					}
				}
			}
			for (int i = k; i < b; ++i)
			{
				aPos1.z += zStep;
				auto node = GetOrInitNode(aPos1.x, aPos1.z);
				if (node) node->AddNativeCost(mBlockNativeCost);
			}
		}
		else
		{//z-axis is longer than x, so make step based on z-axis
			int c = 0;
			if (a > 0)
			{
				c = b / (a + 1);	 //distance till jump
				if (c == 0) c = 1;   //well, it's impossible 
			}
			int j = 1, k = 0;		 //j:dist counter,  k:used num of jump
			for (int i = 0; i < b; ++i)
			{
				aPos1.z += zStep;
				auto node = GetOrInitNode(aPos1.x, aPos1.z);
				if (node) node->AddNativeCost(mBlockNativeCost);

				if (k < a)  //still can jump 
				{
					if (j >= c)  //able to jump 
					{
						j = 1;   //reset counter 
						k++;	 //increae used jump
						aPos1.x += xStep;  //apply jump 
						auto node = GetOrInitNode(aPos1.x, aPos1.z);
						if (node) node->AddNativeCost(mBlockNativeCost);
					}
					else
					{
						++j;	//increse used distance 
					}
				}
			}
			for (int i = k; i < a; ++i)
			{
				aPos1.x += xStep;
				auto node = GetOrInitNode(aPos1.x, aPos1.z);
				if (node) node->AddNativeCost(mBlockNativeCost);
			}
		}

		aPos1 = aPos2;
	}
}

void GridMap::InitNeighbourSetting()
{
	NeighbourOffset[0] = mColNum;
	NeighbourOffset[1] = 1;
	NeighbourOffset[2] = -mColNum;
	NeighbourOffset[3] = -1;
	NeighbourOffset[4] = mColNum + 1;
	NeighbourOffset[5] = -mColNum + 1;
	NeighbourOffset[6] = -mColNum - 1;
	NeighbourOffset[7] = mColNum - 1;

	orthCost = mGridNodeSize.x;
	diagCost = orthCost * 1414 / 1000;
	NeighbourCosts[0] = orthCost;
	NeighbourCosts[1] = orthCost;
	NeighbourCosts[2] = orthCost;
	NeighbourCosts[3] = orthCost;
	NeighbourCosts[4] = diagCost;
	NeighbourCosts[5] = diagCost;
	NeighbourCosts[6] = diagCost;
	NeighbourCosts[7] = diagCost;
}

void GridMap::RegisterGroundMask(int64 aSize)
{
	aSize = aSize - mMaskSub;
	aSize = aSize > 0 ? aSize : mMaskSub;
	if (mGroundMaskTable.count(aSize) != 0)
		return;

	int manhattanDist = static_cast<int>((aSize - mGridNodeSize.x / 2) / mGridNodeSize.x);
	if (manhattanDist < 1) manhattanDist = 1;

	vector<int> tmp;
	vector<int> adjust;
	int side = 0;
	int base = 0;
	int deltaCost = mCommonNativeCost / manhattanDist;
	for (int i = -manhattanDist; i <= manhattanDist; ++i)
	{
		if (i <= 0)
			side = i + manhattanDist;
		else
			side = manhattanDist - i;

		base = i * mColNum;
		for (int j = -side; j <= side; ++j)
		{
			tmp.push_back(base + j);
			int dist = abs(i) + abs(j);
			adjust.push_back(-deltaCost * dist);  //the farer the less
		}
	}
	//mGroundMaskTable.insert(make_pair(aSize, tmp));
	mGroundMaskTable[aSize] = tmp;
	mGroundMaskAdjust[aSize] = adjust;
}

void GridMap::MarkGround(int aIndex, int64 aSize)
{
	aSize = aSize - mMaskSub;
	aSize = aSize > 0 ? aSize : mMaskSub;
	if (mGroundMaskTable.count(aSize) == 0)
	{
		LOG_WARN("Mark ground but not yet RegisterGroundMask, size = %d", aSize);
		RegisterGroundMask(aSize);
	}
	vector<int>& list = mGroundMaskTable[aSize];
	vector<int>& adj = mGroundMaskAdjust[aSize];
	for (int idx = 0; idx < list.size(); ++idx)
	{
		int deltaIdx = list[idx];
		auto node = GetOrInitNode(aIndex + deltaIdx);
		if (node)
		{
			int adjustData = adj[idx];
			node->AddNativeCost(mCommonNativeCost + adjustData);
		}
	}
}

void GridMap::RetrieveGround(int aIndex, int64 aSize)
{
	aSize = aSize - mMaskSub;
	aSize = aSize > 0 ? aSize : mMaskSub;
	if (mGroundMaskTable.count(aSize) == 0)
		return;

	vector<int>& list = mGroundMaskTable[aSize];
	vector<int>& adj = mGroundMaskAdjust[aSize];
	for (int idx = 0; idx < list.size(); ++idx)
	{
		int deltaIdx = list[idx];
		auto node = GetOrInitNode(aIndex + deltaIdx);
		if (node)
		{
			int adjustData = adj[idx];
			node->SubNativeCost(mCommonNativeCost + adjustData);
		}
	}
}

bool GridMap::Walkable(int64 aX, int64 aZ)
{
	int idx = Position2Index(aX, aZ);
	if (idx < 0 || idx >= mVecSize) return false;
	if (!mGridNodeVecFromPool[idx]) return true;
	if (mGridNodeVecFromPool[idx]->GetNativeCost() > 0) return false;
	return true;
}