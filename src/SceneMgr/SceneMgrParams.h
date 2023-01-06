#pragma once
#include "Path/PathDefine.h"
#include "module/SceneConfArcher.pb.h"

using pb::ArcherScene;
using pb::EArcherGridType;
using pb::ArcherGridBlock;
using pb::SceneConfArcher;

struct GameTile
{
public:
	GameTile(const ArcherGridBlock& conf)
	{
		Index = conf.gridindex();
		tileConfId = conf.configid();
		Type = conf.gridtype();
	}
public:
	int Index = 0;	
	int tileConfId = 0;
	EArcherGridType Type = EArcherGridType::Default;
};

class SceneManagerParams 
{
public:
	SceneManagerParams()
	{
		SceneId = 0;
		mCurArcherSceneConf = nullptr;
	}
	~SceneManagerParams()
	{
		mCurArcherSceneConf = nullptr;
		mGameTiles.clear();
	}

	void Init(const ArcherScene* aConf);

	Vector2 GetRootPosition();
	Vector2 GetWidthAndLengthInTileNum();
	int64 GetTileSize();

	const vector<GameTile>& GetGameTiles();

public:
	int SceneId = 0;

private:
	vector<GameTile> mGameTiles;
	const ArcherScene* mCurArcherSceneConf;
};

