
#include "SceneManager.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ThirdParty/mt19937ar.h"


const Vector3 SceneManager::defaultPositiveDir = Vector3(DENOM, 0, 0);  //从左向右看 
const Vector3 SceneManager::defaultNegtiveDir = Vector3(-DENOM, 0, 0);

SceneManager::SceneManager()
{
	mPathMgr = new PathFindingMgr();
	mGameTileMgr = new GameTileMap();
	mRand = nullptr;
}

SceneManager::~SceneManager()
{
	delete mPathMgr;
	delete mGameTileMgr;
	mFieldConfArr.clear();
	mCurStandPointArr.clear();

	mRand = nullptr;
}

void SceneManager::InitSceneManager(TBattleArgs* aPbMsg, MersenneTwister* aRand)
{
	mRand = aRand;
	mFieldConfArr.reserve(aPbMsg->sceneconf_size());
	CurSceneId = -1;
	const string* lastConfName = nullptr;
	const SceneConfArcher* sceneConf = nullptr;
	for (auto& conf : aPbMsg->sceneconf())
	{
		lastConfName = &conf.confname();
		sceneConf = ConfigMgr::GetConfByIndex<SceneConfArcher>(FIELD_CONF_COL_NAME, *lastConfName)[0];
		mFieldConfArr.push_back(&sceneConf->fieldconf());
	}
	TotalFieldNum = static_cast<int>(mFieldConfArr.size());
}

bool SceneManager::HasNextScene()
{
	return CurSceneId < TotalFieldNum - 1;
}

void SceneManager::InitNextField()
{
	CurSceneId++;
	if (CurSceneId >= TotalFieldNum)
	{
		LOG_FATAL("No scene conf left, can not init next field! curSceneId = [%d], total = [%d]", 
			CurSceneId, TotalFieldNum);
		return;
	}

	mCurStandPointArr.clear();
	mCurBornPoint.Set(0, 0, 0);
	mTmp.Set(0, 0);
	mTmp2.Set(0, 0);
	mTmp3.Set(0, 0);

	auto* fieldConf = mFieldConfArr[CurSceneId];
	//使用中间对象隔离配置与逻辑，方便开发期频繁修改配置,待稳定后可去除 
	SceneManagerParams* param = new SceneManagerParams();
	param->Init(fieldConf);

	Vector2 widthAndHeight = param->GetWidthAndLengthInTileNum();
	int width = widthAndHeight.x;
	int height = widthAndHeight.z;
	int64 tileSize = param->GetTileSize();

	mGameTileMgr->ReInit(width, height, tileSize, DIVISION_NUM);
	mGameTileMgr->RegisterTiles(param->GetGameTiles());

	delete param; //已经无用，记得及早删除 

	mGameTileMgr->ResolveBlockLines();

	mPathMgr->InitMap(width * tileSize, height * tileSize, Vector2(tileSize/DIVISION_NUM, tileSize/DIVISION_NUM), Vector2(0, 0));
	vector<int> gridMapIdxArr;
	gridMapIdxArr.resize(DIVISION_NUM * DIVISION_NUM);
	for (auto node : mGameTileMgr->mTileNodeMap)
	{
		if (node && (node->Type == pb::EArcherGridType::Obstacle_All ||
			node->Type == pb::EArcherGridType::Obstacle_Ground_Only))  //Trap 敌方可以在其上行走  
		{
			mGameTileMgr->MappingFromTileToGrid(node->Index, gridMapIdxArr);
			mPathMgr->ApplyBlockAreaManually(gridMapIdxArr);
		}
	}
	mPathMgr->mJustNavigate = false; 

	//CommonStandPoints 
	Vector3 curPos;
	for (auto idx : fieldConf->standtileindexarr())
	{
		mGameTileMgr->IndexToPosition(idx, curPos);
		//curPos.y = idx;		//将index放在y轴数据中，节约struct资源，如果以后有需求在拓展(可能性不大)
		mCurStandPointArr.emplace_back(curPos);
	}

	//PlayerBornPoint
	mGameTileMgr->IndexToPosition(fieldConf->playerbrontileindex(), mCurBornPoint);
	//mCurBornPoint.y = fieldConf->playerbrontileindex();
}

EArcherGridType SceneManager::GetTileTypeFromPos(const Vector3& aPos)
{
	int idx = mGameTileMgr->PositionToIndex(aPos.x, aPos.z);
	if (idx >= mGameTileMgr->mTileNodeMap.size())
	{
		LOG_FATAL("Invalid index[%d] get from PositionToIndex", idx);
		return EArcherGridType::Default;
	}

	if (mGameTileMgr->mTileNodeMap[idx])
	{
		return mGameTileMgr->mTileNodeMap[idx]->Type;
	}

	return EArcherGridType::Default;
}

bool SceneManager::IsOnMissionCmpleteTile(const Vector3& aCurPosition)
{
	return GetTileTypeFromPos(aCurPosition) == EArcherGridType::Mission_Complete;
}

bool SceneManager::DetectCollision(const Vector3& aInputA, const Vector3& aInputB, Vector2& aHitSegA, Vector2& aHitSegB, Vector2& aPoint)
{
	mTmp.Set(aInputA.x, aInputA.z);
	mTmp2.Set(aInputB.x, aInputB.z);

	//前提是下面的方法内绝对不会触发再次调用到当前方法逻辑，不然使用mTmp和mTmp2将会不安全 
	bool ret = mGameTileMgr->DetectCollision(mTmp, mTmp2, aHitSegA, aHitSegB, aPoint);

	return ret;
}

bool SceneManager::IntersectBoundaryWithRadius(const Vector3& aStart, const Vector3& aEnd, int const aRadius, Vector3* aResult)
{
	mTmp.Set(aStart.x, aStart.z);
	mTmp2.Set(aEnd.x, aEnd.z);

	bool ret = mGameTileMgr->IntersectBoundaryWithRadius(mTmp, mTmp2, aRadius, mTmp3);
	if (!ret)
		return ret;

	aResult->x = mTmp3.x;
	aResult->z = mTmp3.z;
	return ret;
}

void SceneManager::GetRandomPositionNearBy(const Vector3& aCurPos, const unsigned int aDistMin, const unsigned int aDistMax, Vector3& aOutputPosition)
{
	vector<int> candidates;
	mGameTileMgr->GetAllAvailablePositionNearBy(aCurPos, aDistMin, aDistMax, candidates);

	int r = uint32(mRand->genrand_int32()) % mGameTileMgr->mDivisionNum; //0~2
	r -= mGameTileMgr->mDivisionNum / 2; //-1~1
	int c = uint32(mRand->genrand_int32()) % mGameTileMgr->mDivisionNum; //0~2
	c -= mGameTileMgr->mDivisionNum / 2; //-1~1
	//this is local random offsets 
	mTmp.Set(r * mGameTileMgr->mTileSizeOverDivisionNum, c * mGameTileMgr->mTileSizeOverDivisionNum);

	if (candidates.empty())
	{
		LOG_WARN("unable to find any nearby tile, invalid input Dist?");
		aOutputPosition.x = aCurPos.x + mTmp.x;
		aOutputPosition.z = aCurPos.z + mTmp.z;
		return;
	}

	//this is random offset among all available GameTiles 
	int i = uint32(mRand->genrand_int32()) % candidates.size();
	int idx = candidates[i];
	mGameTileMgr->IndexToPosition(idx, aOutputPosition);

	//apply local offsets thereby 
	aOutputPosition.x = aOutputPosition.x + mTmp.x;
	aOutputPosition.z = aOutputPosition.z + mTmp.z;
}

//要求InputDir的模长必须是DENOM 
//以下运算是在假设设单位长度为DENOM下进行的 
Vector3 SceneManager::CalculateReflectDir(const Vector2& InputDir, const Vector2& SegA, const Vector2& SegB)
{
	Vector2 neg_InputDir;
	neg_InputDir.Set(-InputDir.x, -InputDir.z); 
	Vector2 SegDir = SegB - SegA;
	SegDir.ScaleToLen(DENOM);
	int64 SegLen = DENOM;
	Vector2 SegNormal;
	SegNormal.Set(SegDir.z, -SegDir.x); 

	int64 d = Vector2::Dot(neg_InputDir, SegNormal) / DENOM; // 1^2 = 1;  DENOM^2 != DENOM -> 所有这里必须除以一个DENOM修正 

	Vector3 ReflectDir;	// Normal.ScaleToLen(d) * 2 + InputDir = ReflectDir 
	ReflectDir.Set(
		SegNormal.x * d * 2 / DENOM + InputDir.x,
		0,
		SegNormal.z * d * 2 / DENOM + InputDir.z
	);
	return ReflectDir;
}

void SceneManager::CalculateMoveBouncePath(vector<Vector2>& aOutput, const Vector3& aStart, const Vector3& aEnd, int aBounceNum)
{
	Vector2 HitSegA, HitSegB, Point, CurDir;

	Vector3 dir = aEnd - aStart;
	CurDir.Set(dir.x, dir.z);
	CurDir.ScaleToLen(DENOM);

	dir.y = 0;
	dir.ScaleToLen(MaxBounceLen);
	Vector3 inputSegA = aStart;
	inputSegA.y = 0;
	Vector3 inputSegB = inputSegA + dir;  //更新起点和终点 

	bool ret = false;

	for (int i = 0; i <= aBounceNum; ++i)  //aBounceNum可以为0，此时会在第一个遇到的墙体处消失 
	{
		ret = DetectCollision(inputSegA, inputSegB, HitSegA, HitSegB, Point); //必须确保HitSegA -> HitSegB的顺序一致性 
		if (!ret)  //如果撞不到边界，就直接输出终点并返回 
		{
			Vector2 routePoint;
			routePoint.Set(inputSegB.x, inputSegB.z);
			aOutput.emplace_back(routePoint);
			return;
		}

		aOutput.emplace_back(Point);
		if (i == aBounceNum) //没有后续反射了，直接退出 
			return;

		//has next
		auto nextDir = CalculateReflectDir(CurDir, HitSegA, HitSegB);
		nextDir.ScaleToLen(DENOM);
		CurDir.Set(nextDir.x, nextDir.z);		//update cur dir

		nextDir.ScaleToLen(MaxBounceLen);
		inputSegA.Set(Point.x, 0, Point.z);		//update inputSeg 
		inputSegB = inputSegA + nextDir;
	}

	//TODO: use Vector pools 
	return;
}