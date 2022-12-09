#pragma once
#include "Path/PathFindingMgr.h"
#include "SceneMgr/GameTileMap.h"
#include "ConfigMgr/Pb/net/Battle.pb.h"

using pb::TBattleArgs;
using pb::ArcherScene;
using pb::EArcherGridType;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void InitSceneManager(TBattleArgs* aPbMsg);

	void InitNextField();

	bool HasNextScene();

	bool IsOnMissionCmpleteTile(const Vector3& aCurPosition);

	EArcherGridType GetTileTypeFromPos(const Vector3& aPos);

	bool DetectCollision(const Vector3& aInputA, const Vector3& aInputB, Vector2& aHitSegA, Vector2& aHitSegB, Vector2& aPoint);

	bool IntersectBoundaryWithRadius(const Vector3& aStart, const Vector3& aEnd, int const aRadius, Vector3* aResult);

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
	const constexpr static char* FIELD_CONF_COL_NAME = "Confname";
	const constexpr static int DIVISION_NUM = 3; //控制一块策划地砖能在单个轴向被分成几份 

	vector<ArcherScene> mFieldConfArr;

	Vector2 mTmp, mTmp2, mTmp3;
};
