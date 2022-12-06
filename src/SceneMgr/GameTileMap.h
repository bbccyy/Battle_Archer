#pragma 
#include "SceneMgr/SceneMgrParams.h"
#include "Framework/SharedPool.h"

class TileNode : public IPoolable
{
public:
	TileNode() = default;
	~TileNode() = default;

	void Init(int aIndex, int aBoxX, int aBoxZ, EArcherGridType aType, const Vector2& aPosLD, const Vector2& aPosRU)
	{
		X = aBoxX;
		Z = aBoxZ;
		Index = aIndex;
		Type = aType;
		PositionLeftDown.Set(aPosLD);
		PositionRightUp.Set(aPosRU);
	}

	void Reset()
	{
		X = 0;
		Z = 0;
		Index = 0;
		Type = EArcherGridType::Default;
		PositionLeftDown.Set(0, 0);
		PositionRightUp.Set(0, 0);
	}

public:
	int X = 0;			//column index 
	int Z = 0;			//row index 
	int Index = 0;
	EArcherGridType Type = EArcherGridType::Default;		//?? 1->Default; (-1)->Block; 2->Trap
	Vector2 PositionLeftDown;
	Vector2 PositionRightUp;
};

//要求场景关于中心点左右和上下对其，长宽都有奇数块GameTile，
//场景中心点位于0点，有一块GameTile正好位于其上，该GameTile的中心与场景中心对齐 
class GameTileMap
{
public:
	GameTileMap() = default;
	~GameTileMap()
	{
		Reset();
	};

	//aDivisionNum必须是奇数，代码会做检测 
	void ReInit(int aWidthTileNum, int aLengthTileNum, int64 TileSize, int aDivisionNum);
	void Reset();

	pb::EArcherGridType GetTileTypeFromPosition(int64 aX, int64 aZ);

	inline int BoxPositionToIndex(int aCol, int aRow);
	inline void IndexToBoxPosition(int aIndex, Vector2& aOutput);
	void IndexToPosition(int aIndex, Vector3& aOutput);
	int PositionToIndex(int64 aX, int64 aZ);
	int PositionToBoxPosition(int64 aX, int64 aZ, Vector2& Output);

	void MappingFromTileToGrid(int aTileIndex, vector<int>& aOutput); //输出pathMgr对应的gridIndex序列 

	void RegisterTiles(const vector<GameTile>& aListOfTiles);
	
	void ResolveBlockLines();

	bool DetectCollision(const Vector2& aInputA, const Vector2& aInputB, Vector2& aHitSegA, Vector2& aHitSegB, Vector2& aPoint);

public:
	vector<SharedPtr<TileNode>> mTileNodeMap;

private:
	void GetLDandRUpositionFromBoxPosition(int aCol, int aRow, Vector2& aLD, Vector2& aRU);
	int HasBlockLine(int aIdxCur, int aIdxOther, Vector2& A, Vector2& B);

private:
	int mDivisionNum = 1;
	int mGridInTile = 0;
	int mDeltaNum = 0;
	int mColNum = 0;
	int mHalfCol = 0;
	int mRowNum = 0;
	int mHalfRow = 0;
	int64 mTileSize = 0;
	int64 mTileHalfSize = 0;

	Vector2 mTmp;
	Vector2 mTmp2;
	Vector2 mCenterOffset;

	//第一维索引行号，第二维记录同属于一行的BlockLine 
	vector<vector<pair<Vector2, Vector2>>> mBlockLinesHorizontal;	//收纳水平线 下标从低到高 -> row从上到下 
	vector<vector<pair<Vector2, Vector2>>> mBlockLinesVertical;		//收纳垂直线 下标从低到高 -> col从左到右 

};