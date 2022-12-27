#pragma once
#include "Path/PathFindingMgr.h"
#include "SceneMgr/GameTileMap.h"
#include "ConfigMgr/Pb/net/Battle.pb.h"

using pb::TBattleArgs;
using pb::ArcherScene;
using pb::EArcherGridType;

class MersenneTwister;

const int64 MaxBounceLen = CONF_POS_CONVERT(5000);  //50米 

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void InitSceneManager(TBattleArgs* aPbMsg, MersenneTwister* aRand);

	void InitNextField();

	bool HasNextScene();

	bool IsOnMissionCmpleteTile(const Vector3& aCurPosition);

	EArcherGridType GetTileTypeFromPos(const Vector3& aPos);

	bool DetectCollision(const Vector3& aInputA, const Vector3& aInputB, Vector2& aHitSegA, Vector2& aHitSegB, Vector2& aPoint);

	bool IntersectBoundaryWithRadius(const Vector3& aStart, const Vector3& aEnd, int const aRadius, Vector3* aResult);

	void GetRandomPositionNearBy(const Vector3& aCurPos, const unsigned int aDistMin, const unsigned int aDistMax, Vector3& aOutputPosition);

	void CalculateMoveBouncePath(vector<Vector2>& aOutput, const Vector3& aStart, const Vector3& aEnd, int aBounceNum);

public:
	int CurSceneId = 0;
	int TotalFieldNum = 0;

	vector<Vector3> mCurStandPointArr;
	Vector3 mCurBornPoint;

	PathFindingMgr* mPathMgr = nullptr;
	GameTileMap* mGameTileMgr = nullptr;

	const static Vector3 defaultPositiveDir;
	const static Vector3 defaultNegtiveDir;

private:
	Vector3 CalculateReflectDir(const Vector2& InputDir, const Vector2& SegA, const Vector2& SegB);

private:
	const constexpr static char* FIELD_CONF_COL_NAME = "Confname";
	const constexpr static int DIVISION_NUM = 3; //控制一块策划地砖能在单个轴向被分成几份 

	vector<ArcherScene> mFieldConfArr;

	Vector2 mTmp, mTmp2, mTmp3;

	MersenneTwister* mRand = nullptr;
};
