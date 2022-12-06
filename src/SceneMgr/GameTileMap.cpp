
#include "GameTileMap.h"
#include "Framework/Physics/CollisionDetection.h"

//aDivisionNum���������������������� 
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

	//TODO:Ӧ�ü����߼� 
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

	//4���˵� 
	Vector2 LU, LD, RU, RD;
	LU.Set(-mHalfCol * mTileSize - mTileHalfSize, mHalfRow * mTileSize + mTileHalfSize);
	LD.Set(-mHalfCol * mTileSize - mTileHalfSize, -mHalfRow * mTileSize - mTileHalfSize);
	RU.Set(mHalfCol * mTileSize + mTileHalfSize, mHalfRow * mTileSize + mTileHalfSize);
	RD.Set(mHalfCol * mTileSize + mTileHalfSize, -mHalfRow * mTileSize - mTileHalfSize);

	Vector2 A, B;	//��������ɨ��ʱ��ÿһ�д�������ɨ -> A��������㣬B���ұ��յ� 
					//��������ɨ��ʱ��ÿһ�д�������ɨ -> A��������㣬B�������յ� 
	bool search_starter = true;		//T=search_starter; F=search_end 
	int last_ret = 0, ret = 0;

	//First, Do Horizontal Search!
	mBlockLinesHorizontal.emplace_back(vector<pair<Vector2, Vector2>>());	//��һ�д�ű߽��� 
	mBlockLinesHorizontal[0].emplace_back(pair<Vector2, Vector2>(LU, RU));	//ע���߶γ��� 
	for (int i = 1; i < mRowNum; ++i)
	{
		search_starter = true;
		mBlockLinesHorizontal.emplace_back(vector<pair<Vector2, Vector2>>());
		for (int j = 0; j < mColNum; ++j)
		{
			int curIdx = i * mColNum + j;
			int upIdx = (i - 1) * mColNum + j;
			ret = HasBlockLine(curIdx, upIdx, mTmp, mTmp2); //0->no; 1->yes; 2->yes_but_reverse 
			if (ret > 0)	//����Tile֮�����BlockLine 
			{
				if (search_starter) //֮ǰ��û�м�¼���A����¼һ�� 
				{
					A.Set(mTmp);
					B.Set(mTmp2);
					search_starter = false;	//���±�ʶ������������Ŀ���������յ� 
				}
				else
				{
					if (last_ret == ret) //Ԥ��б��ڷŵ��ϰ�������������� 
						B.Set(mTmp2);
					else
					{
						//�������Ч���ҵ����յ��ͬʱ�ҵ�����һ����� 
						//��ʱlast_ret������Ϊ0����Ϊsearch_starter��ǰ����true���� 
						//���� search_starter == false 
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
	mBlockLinesHorizontal.emplace_back(vector<pair<Vector2, Vector2>>());	//���һ��(mRowNum+1��)����µ׽��� 
	mBlockLinesHorizontal[0].emplace_back(pair<Vector2, Vector2>(RD, LD));	//ע���߶γ��� 

	//Handler Vertical Block lines here��
	mBlockLinesVertical.emplace_back(vector<pair<Vector2, Vector2>>());		//��һ�д����߽��� 
	mBlockLinesVertical[0].emplace_back(pair<Vector2, Vector2>(LD, LU));	//ע���߶γ��� 
	for (int i = 1; i < mColNum; ++i)
	{
		search_starter = true;
		mBlockLinesVertical.emplace_back(vector<pair<Vector2, Vector2>>());
		for (int j = 0; j < mRowNum; ++j)
		{
			int curIdx = j * mColNum + i;
			int leftIdx = curIdx - 1;
			ret = HasBlockLine(curIdx, leftIdx, mTmp, mTmp2); //0->no; 1->yes; 2->yes_but_reverse 
			if (ret > 0)	//����Tile֮�����BlockLine 
			{
				if (search_starter) //֮ǰ��û�м�¼���A����¼һ�� 
				{
					A.Set(mTmp);
					B.Set(mTmp2);
					search_starter = false;	//���±�ʶ������������Ŀ���������յ� 
				}
				else
				{
					if (last_ret == ret) //Ԥ��б��ڷŵ��ϰ�������������� 
						B.Set(mTmp2);
					else
					{
						//�������Ч���ҵ����յ��ͬʱ�ҵ�����һ����� 
						//��ʱlast_ret������Ϊ0����Ϊsearch_starter��ǰ����true���� 
						//���� search_starter == false 
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
	mBlockLinesVertical.emplace_back(vector<pair<Vector2, Vector2>>());		//���һ��(mColNum+1��)����ұ߽��� 
	mBlockLinesVertical[0].emplace_back(pair<Vector2, Vector2>(RU, RD));	//ע���߶γ��� 

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

	aOutput.Set(colIdx, rowIdx);  //X����col(���)��Z����row(����) 

	return mColNum * rowIdx + colIdx;
}

int GameTileMap::PositionToIndex(int64 aX, int64 aZ)
{
	return PositionToBoxPosition(aX, aZ, mTmp);
}

//ȷ������� aOutput.size == mGridInTile 
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

//�Ҳ���Tile�򷵻�Ĭ��ֵ0��������ͨ�ؿ飩
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
		idx = tile.Index; //ע�⣬������β�ʹ�����Ա༭����Index����˱���ȷ��˫����Index�������һ�µ� 
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