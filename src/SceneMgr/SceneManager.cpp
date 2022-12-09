
#include "SceneManager.h"
#include "ConfigMgr/ConfigMgr.h"


const Vector3 SceneManager::defaultPositiveDir = Vector3(0, 0, 1);
const Vector3 SceneManager::defaultNegtiveDir = Vector3(0, 0, -1);

SceneManager::SceneManager()
{
	mPathMgr = new PathFindingMgr();
	mGameTileMgr = new GameTileMap();
}

SceneManager::~SceneManager()
{
	delete mPathMgr;
	delete mGameTileMgr;
	mFieldConfArr.clear();
	mCurStandPointArr.clear();
}

void SceneManager::InitSceneManager(TBattleArgs* aPbMsg)
{
	mFieldConfArr.reserve(aPbMsg->sceneconf_size());
	CurSceneId = -1;
	const string* lastConfName = nullptr;
	const SceneConfArcher* sceneConf = nullptr;
	for (auto& conf : aPbMsg->sceneconf())
	{
		lastConfName = &conf.confname();
		sceneConf = ConfigMgr::GetConfByIndex<SceneConfArcher>(FIELD_CONF_COL_NAME, *lastConfName)[0];
		mFieldConfArr.push_back(sceneConf->fieldconf());
	}
	TotalFieldNum = static_cast<int>(mFieldConfArr.size());
}

bool SceneManager::HasNextScene()
{
	return CurSceneId < TotalFieldNum;
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

	auto* fieldConf = &mFieldConfArr[CurSceneId];
	//ʹ���м��������������߼������㿪����Ƶ���޸�����,���ȶ����ȥ�� 
	SceneManagerParams* param = new SceneManagerParams();
	param->Init(fieldConf);

	Vector2 widthAndHeight = param->GetWidthAndLengthInTileNum();
	int width = widthAndHeight.x;
	int height = widthAndHeight.z;
	int64 tileSize = param->GetTileSize();

	mGameTileMgr->ReInit(width, height, tileSize, DIVISION_NUM);
	mGameTileMgr->RegisterTiles(param->GetGameTiles());

	delete param; //�Ѿ����ã��ǵü���ɾ�� 

	mGameTileMgr->ResolveBlockLines();

	mPathMgr->InitMap(width * tileSize, height * tileSize, Vector2(tileSize/DIVISION_NUM, tileSize/DIVISION_NUM), Vector2(0, 0));
	vector<int> gridMapIdxArr;
	gridMapIdxArr.resize(DIVISION_NUM * DIVISION_NUM);
	for (auto node : mGameTileMgr->mTileNodeMap)
	{
		if (node->Type == pb::EArcherGridType::Obstacle_All ||
			node->Type == pb::EArcherGridType::Obstacle_Ground_Only)
		{
			mGameTileMgr->MappingFromTileToGrid(node->Index, gridMapIdxArr);
			mPathMgr->ApplyBlockAreaManually(gridMapIdxArr);
		}
	}
	mPathMgr->mJustNavigate = true; 

	//CommonStandPoints 
	Vector3 curPos;
	for (auto idx : fieldConf->standtileindexarr())
	{
		mGameTileMgr->IndexToPosition(idx, curPos);
		curPos.y = idx;		//��index����y�������У���Լstruct��Դ������Ժ�����������չ(�����Բ���)
		mCurStandPointArr.emplace_back(curPos);
	}

	//PlayerBornPoint
	mGameTileMgr->IndexToPosition(fieldConf->playerbrontileindex(), mCurBornPoint);
	mCurBornPoint.y = fieldConf->playerbrontileindex();
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

	//ǰ��������ķ����ھ��Բ��ᴥ���ٴε��õ���ǰ�����߼�����Ȼʹ��mTmp��mTmp2���᲻��ȫ 
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
