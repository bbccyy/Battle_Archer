
#include "GameTileMap.h"
#include "Framework/Physics/CollisionDetection.h"

//aDivisionNum必须是奇数，代码会做检测 
void GameTileMap::ReInit(int aWidthTileNum, int aLengthTileNum, int64 aTileSize, int aDivisionNum)
{
	Reset();

	if (aWidthTileNum % 2 > 0 || aLengthTileNum % 2 > 0 || aDivisionNum % 2 > 0)
	{
		LOG_FATAL("Unable to init GameTileMap, invalid input data");
		return;
	}

	mColNum = aWidthTileNum;
	mHalfCol = (mColNum - 1) / 2;
	mRowNum = aLengthTileNum;
	mHalfRow = (mRowNum - 1) / 2;

	mTileSize = aTileSize;
	mTileHalfSize = mTileSize / 2;
	mDivisionNum = aDivisionNum;
	mGridInTile = mDivisionNum * mDivisionNum;
	mDeltaNum = mDivisionNum * (mColNum - 1);

	mCenterOffset.Set(-mColNum * aTileSize / 2, -mRowNum * aTileSize / 2);

	mTileNodeMap.resize(mColNum * mRowNum);
}

void GameTileMap::Reset()
{
	for (int i = 0; i < mTileNodeMap.size(); ++i)
	{
		if (mTileNodeMap[i])
		{
			mTileNodeMap[i].Release();
		}
	}
	mTileNodeMap.clear();

	mBlockLinesHorizontal.clear();
	mBlockLinesVertical.clear();

	mDivisionNum = 0;
	mGridInTile = 0;
	mDeltaNum = 0;
	mColNum = 0;
	mHalfCol = 0;
	mRowNum = 0;
	mHalfRow = 0;
	mTileSize = 0;
	mTileHalfSize = 0;

	mTmp.Set(0, 0);
	mTmp2.Set(0, 0);
	mCenterOffset.Set(0, 0);
}

bool GameTileMap::DetectCollision(const Vector2& aInputA, const Vector2& aInputB, Vector2& aHitSegA, Vector2& aHitSegB, Vector2& aPoint)
{
	auto InputVector = aInputB - aInputA;
	int64 distSqrMin = InputVector.Magnitude2();
	bool ret = false;

	//TODO:应用加速逻辑 
	CollisionResults results;
	for (auto& rowList : mBlockLinesHorizontal)
	{
		for (auto& segment : rowList)
		{
			bool hasCollision = IntersectSegmentSegment2D(aInputA, aInputB, segment.first, segment.second, results);
			if (hasCollision)
			{
				auto curVector = results.CollisionPoint - segment.first;
				auto curDist = curVector.Magnitude2();
				if (curDist <= distSqrMin)
				{
					ret = true;
					distSqrMin = curDist;
					aHitSegA.Set(segment.first);
					aHitSegB.Set(segment.second);
					aPoint.Set(results.CollisionPoint);
				}
			}
		}
	}

	for (auto& colList : mBlockLinesVertical)
	{
		for (auto& segment : colList)
		{
			bool hasCollision = IntersectSegmentSegment2D(aInputA, aInputB, segment.first, segment.second, results);
			if (hasCollision)
			{
				auto curVector = results.CollisionPoint - segment.first;
				auto curDist = curVector.Magnitude2();
				if (curDist <= distSqrMin)
				{
					ret = true;
					distSqrMin = curDist;
					aHitSegA.Set(segment.first);
					aHitSegB.Set(segment.second);
					aPoint.Set(results.CollisionPoint);
				}
			}
		}
	}

	return ret;
}

void GameTileMap::ResolveBlockLines()
{
	if (mTileNodeMap.empty())
		return;

	//4个端点 
	Vector2 LU, LD, RU, RD;
	LU.Set(-mHalfCol * mTileSize - mTileHalfSize, mHalfRow * mTileSize + mTileHalfSize);
	LD.Set(-mHalfCol * mTileSize - mTileHalfSize, -mHalfRow * mTileSize - mTileHalfSize);
	RU.Set(mHalfCol * mTileSize + mTileHalfSize, mHalfRow * mTileSize + mTileHalfSize);
	RD.Set(mHalfCol * mTileSize + mTileHalfSize, -mHalfRow * mTileSize - mTileHalfSize);

	Vector2 A, B;	//从上往下扫描时，每一行从左往右扫 -> A是坐标起点，B是右边终点 
					//从左往右扫描时，每一列从上往下扫 -> A是上面起点，B是下面终点 
	bool search_starter = true;		//T=search_starter; F=search_end 
	int last_ret = 0, ret = 0;

	//First, Do Horizontal Search!
	mBlockLinesHorizontal.emplace_back(vector<pair<Vector2, Vector2>>());	//第一行存放边界线 
	mBlockLinesHorizontal[0].emplace_back(pair<Vector2, Vector2>(LU, RU));	//注意线段朝向 
	for (int i = 1; i < mRowNum; ++i)
	{
		search_starter = true;
		mBlockLinesHorizontal.emplace_back(vector<pair<Vector2, Vector2>>());
		for (int j = 0; j < mColNum; ++j)
		{
			int curIdx = i * mColNum + j;
			int upIdx = (i - 1) * mColNum + j;
			ret = HasBlockLine(curIdx, upIdx, mTmp, mTmp2); //0->no; 1->yes; 2->yes_but_reverse 
			if (ret > 0)	//两块Tile之间存在BlockLine 
			{
				if (search_starter) //之前还没有记录起点A，记录一下 
				{
					A.Set(mTmp);
					B.Set(mTmp2);
					search_starter = false;	//更新标识符，接下来的目标是搜索终点 
				}
				else
				{
					if (last_ret == ret) //预防斜向摆放的障碍物引发计算错误 
						B.Set(mTmp2);
					else
					{
						//该情况等效于找到了终点的同时找到了下一个起点 
						//此时last_ret不可能为0，因为search_starter当前不在true上面 
						//保持 search_starter == false 
						if (last_ret == 1)
							mBlockLinesHorizontal[i].emplace_back(pair<Vector2, Vector2>(A, B));
						else if (last_ret == 2)
							mBlockLinesHorizontal[i].emplace_back(pair<Vector2, Vector2>(B, A));
						else
							LOG_FATAL("Invalid State A!");
						A.Set(mTmp);
						B.Set(mTmp2);
					}
				}
			}
			else
			{
				if (!search_starter)  //we are searching the End_Point! 
				{
					if (last_ret == 1)
						mBlockLinesHorizontal[i].emplace_back(pair<Vector2, Vector2>(A, B));
					else if (last_ret == 2)
						mBlockLinesHorizontal[i].emplace_back(pair<Vector2, Vector2>(B, A));
					else
						LOG_FATAL("Invalid State B!");
					search_starter = true;
				}
			}
			last_ret = ret;
		}
		if (!search_starter)
		{
			if (last_ret == 1)
				mBlockLinesHorizontal[i].emplace_back(pair<Vector2, Vector2>(A, B));
			else if (last_ret == 2)
				mBlockLinesHorizontal[i].emplace_back(pair<Vector2, Vector2>(B, A));
			else
				LOG_FATAL("Invalid State C!");
		}
	}
	mBlockLinesHorizontal.emplace_back(vector<pair<Vector2, Vector2>>());	//最后一行(mRowNum+1行)存放下底界线 
	mBlockLinesHorizontal[0].emplace_back(pair<Vector2, Vector2>(RD, LD));	//注意线段朝向 

	//Handler Vertical Block lines here！
	mBlockLinesVertical.emplace_back(vector<pair<Vector2, Vector2>>());		//第一列存放左边界线 
	mBlockLinesVertical[0].emplace_back(pair<Vector2, Vector2>(LD, LU));	//注意线段朝向 
	for (int i = 1; i < mColNum; ++i)
	{
		search_starter = true;
		mBlockLinesVertical.emplace_back(vector<pair<Vector2, Vector2>>());
		for (int j = 0; j < mRowNum; ++j)
		{
			int curIdx = j * mColNum + i;
			int leftIdx = curIdx - 1;
			ret = HasBlockLine(curIdx, leftIdx, mTmp, mTmp2); //0->no; 1->yes; 2->yes_but_reverse 
			if (ret > 0)	//两块Tile之间存在BlockLine 
			{
				if (search_starter) //之前还没有记录起点A，记录一下 
				{
					A.Set(mTmp);
					B.Set(mTmp2);
					search_starter = false;	//更新标识符，接下来的目标是搜索终点 
				}
				else
				{
					if (last_ret == ret) //预防斜向摆放的障碍物引发计算错误 
						B.Set(mTmp2);
					else
					{
						//该情况等效于找到了终点的同时找到了下一个起点 
						//此时last_ret不可能为0，因为search_starter当前不在true上面 
						//保持 search_starter == false 
						if (last_ret == 1)
							mBlockLinesVertical[i].emplace_back(pair<Vector2, Vector2>(A, B));
						else if (last_ret == 2)
							mBlockLinesVertical[i].emplace_back(pair<Vector2, Vector2>(B, A));
						else
							LOG_FATAL("Invalid State D!");
						A.Set(mTmp);
						B.Set(mTmp2);
					}
				}
			}
			else
			{
				if (!search_starter)  //we are searching the End_Point! 
				{
					if (last_ret == 1)
						mBlockLinesVertical[i].emplace_back(pair<Vector2, Vector2>(A, B));
					else if (last_ret == 2)
						mBlockLinesVertical[i].emplace_back(pair<Vector2, Vector2>(B, A));
					else
						LOG_FATAL("Invalid State E!");
					search_starter = true;
				}
			}
			last_ret = ret;
		}
		if (!search_starter)
		{
			if (last_ret == 1)
				mBlockLinesVertical[i].emplace_back(pair<Vector2, Vector2>(A, B));
			else if (last_ret == 2)
				mBlockLinesVertical[i].emplace_back(pair<Vector2, Vector2>(B, A));
			else
				LOG_FATAL("Invalid State F!");
		}
	}
	mBlockLinesVertical.emplace_back(vector<pair<Vector2, Vector2>>());		//最后一列(mColNum+1列)存放右边界线 
	mBlockLinesVertical[0].emplace_back(pair<Vector2, Vector2>(RU, RD));	//注意线段朝向 

	return;
}

int GameTileMap::HasBlockLine(int aIdxCur, int aIdxOther, Vector2& A, Vector2& B)
{
	const SharedPtr<TileNode>& aCur = mTileNodeMap[aIdxCur];
	const SharedPtr<TileNode>& aOther = mTileNodeMap[aIdxOther];

	int ret = 0;		//0->no; 1->yes; 2->yes_but_reverse 

	if (!aCur && !aOther)
		return 0;

	if (aCur && aOther)
	{
		if((aCur->Type == pb::EArcherGridType::Obstacle_All && aOther->Type != pb::EArcherGridType::Obstacle_All) ||
			(aCur->Type != pb::EArcherGridType::Obstacle_All && aOther->Type == pb::EArcherGridType::Obstacle_All))
		{
			//find!
			if (aIdxCur == aIdxOther + 1)
			{
				//left -> right
				A.Set(aOther->PositionRightUp);
				B.Set(aCur->PositionLeftDown);
				if (aCur->Type != pb::EArcherGridType::Obstacle_All) ret = 2;
				else ret = 1;
			}
			else
			{
				//down -> up
				A.Set(aOther->PositionLeftDown);
				B.Set(aCur->PositionRightUp);
				if (aCur->Type != pb::EArcherGridType::Obstacle_All) ret = 1;
				else ret = 2;
			}
			return ret;
		}
		else
		{
			//not find!
			return 0;
		}
	}

	if (aCur)
	{
		if (aCur->Type == pb::EArcherGridType::Obstacle_All)
		{
			//find!
			if (aIdxCur == aIdxOther + 1)
			{
				//left -> right
				A.Set(aCur->PositionLeftDown);
				B.Set(aCur->PositionLeftDown);
				A.z += mTileSize;
				ret = 1;
			}
			else
			{
				//down -> up
				A.Set(aCur->PositionRightUp);
				B.Set(aCur->PositionRightUp);
				A.x -= mTileSize;
				ret = 2;
			}
			return ret;
		}
		else
		{
			//not find!
			return 0;
		}
	}
	else
	{
		if (aOther->Type == pb::EArcherGridType::Obstacle_All)
		{
			//find!
			if (aIdxCur == aIdxOther + 1)
			{
				//left -> right
				A.Set(aOther->PositionRightUp);
				B.Set(aOther->PositionRightUp);
				B.z -= mTileSize;
				ret = 2;
			}
			else
			{
				//down -> up
				A.Set(aOther->PositionLeftDown);
				B.Set(aOther->PositionLeftDown);
				B.x += mTileSize; 
				ret = 1;
			}
			return ret;

		}
		else
		{
			//not find!
			return 0;
		}
	}
}

inline int GameTileMap::BoxPositionToIndex(int aCol, int aRow)
{
	return mColNum * aRow + aCol;
}

inline void GameTileMap::IndexToBoxPosition(int aIndex, Vector2& aOutput)
{
	aOutput.z = aIndex / mColNum;
	aOutput.x = aIndex % mColNum;
}

void GameTileMap::IndexToPosition(int aIndex, Vector3& aOutput)
{
	aOutput.z = aIndex / mColNum;	//row index 
	aOutput.x = aIndex % mColNum;	//col index 
	GetLDandRUpositionFromBoxPosition(aOutput.x, aOutput.z, mTmp, mTmp2);
	aOutput.x = mTmp.x + mTileHalfSize;
	aOutput.z = mTmp.z + mTileHalfSize;
	aOutput.y = 0;
}

int GameTileMap::PositionToBoxPosition(int64 aX, int64 aZ, Vector2& aOutput)
{
	if (aX < 0)
		aX = aX - mTileHalfSize;
	else
		aX = aX + mTileHalfSize;

	if (aZ < 0)
		aZ = aZ - mTileHalfSize;
	else
		aZ = aZ + mTileHalfSize;

	int colIdx = mHalfCol + aX / mTileSize;
	int rowIdx = mHalfRow + aZ / mTileSize;

	if (colIdx < 0) colIdx = 0;
	else if (colIdx >= mColNum) colIdx = mColNum - 1;

	if (rowIdx < 0) rowIdx = 0;
	else if (rowIdx >= mRowNum) rowIdx = mRowNum - 1;

	aOutput.Set(colIdx, rowIdx);  //X代表col(宽度)，Z代表row(长度) 

	return mColNum * rowIdx + colIdx;
}

int GameTileMap::PositionToIndex(int64 aX, int64 aZ)
{
	return PositionToBoxPosition(aX, aZ, mTmp);
}

//确保输入的 aOutput.size == mGridInTile 
void GameTileMap::MappingFromTileToGrid(int aTileIndex, vector<int>& aOutput)
{
	if (aOutput.size() != mGridInTile)
	{
		LOG_FATAL("invalid input list size");
		return;
	}

	IndexToBoxPosition(aTileIndex, mTmp);
	int col = mTmp.x;
	int row = mTmp.z;
	int cur = mGridInTile * row * mColNum + col * mDivisionNum;
	int ct = 0;
	for (int i = 0; i < mDivisionNum; ++i)
	{
		for (int j = 0; j < mDivisionNum; ++j)
		{
			aOutput[ct++] = cur + j;
		}
		cur = cur + mDeltaNum + 1;
	}
}

//找不到Tile则返回默认值0（代表普通地块）
pb::EArcherGridType GameTileMap::GetTileTypeFromPosition(int64 aX, int64 aZ)
{
	int idx = PositionToIndex(aX, aZ);
	auto node = mTileNodeMap[idx];
	if (node)
		return node->Type;
	return pb::EArcherGridType::Default;
}

void GameTileMap::GetLDandRUpositionFromBoxPosition(int aCol, int aRow, Vector2& aLD, Vector2& aRU)
{
	aLD.z = (mRowNum - aRow - 1) * mTileSize;
	aLD.x = aCol * mTileSize;

	aLD.x += mCenterOffset.x;
	aLD.z += mCenterOffset.z;

	aRU.z = aLD.z + mTileSize;
	aRU.x = aLD.x + mTileSize;
}

void GameTileMap::RegisterTiles(const vector<GameTile>& aListOfTiles)
{
	int idx = 0;
	Vector2 tileXZ;
	for (auto& tile : aListOfTiles)
	{
		IndexToBoxPosition(tile.Index, tileXZ);
		idx = tile.Index; //注意，这边信任并使用来自编辑器的Index，因此必须确保双方对Index的理解是一致的 
		if (mTileNodeMap[idx])
		{
			LOG_WARN("Duplicated Tile found! Index = [%d]", tile.Index);
			mTileNodeMap[idx].Release();
		}
		mTileNodeMap[idx] = SharedPool<TileNode>::Get();
		GetLDandRUpositionFromBoxPosition(tileXZ.x, tileXZ.z, mTmp, mTmp2);
		mTileNodeMap[idx]->Init(idx, tileXZ.x, tileXZ.z, tile.Type, mTmp, mTmp2);
	}
}