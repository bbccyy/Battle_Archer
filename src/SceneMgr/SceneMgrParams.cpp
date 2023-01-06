
#include "SceneMgr/SceneMgrParams.h"


void SceneManagerParams::Init(const ArcherScene* aConf)
{
	mCurArcherSceneConf = aConf;
	if (!mCurArcherSceneConf)
	{
		LOG_FATAL("Null ArcherSceneConf");
		return;
	}

	SceneId = mCurArcherSceneConf->sceneid();
	mGameTiles.clear();

	for (auto& gridBlk : mCurArcherSceneConf->gridblockarr())
	{
		mGameTiles.emplace_back(GameTile(gridBlk));
	}
}

Vector2 SceneManagerParams::GetRootPosition()
{
	return Vector2(0, 0); //战斗逻辑内永远是0点 
}

Vector2 SceneManagerParams::GetWidthAndLengthInTileNum()
{
	return Vector2(mCurArcherSceneConf->scenetilewidth(), mCurArcherSceneConf->scenetileheight());
}

int64 SceneManagerParams::GetTileSize()
{
	return CONF_POS_CONVERT(mCurArcherSceneConf->tilesize());  //配置单位是厘米，需要转换 
}

const vector<GameTile>& SceneManagerParams::GetGameTiles()
{
	return mGameTiles;
}