
#include "PathFindingMgr.h"
#include "GridMap.h"
#include "Path.h"

PathFindingMgr::PathFindingMgr()
	:mVersionId(0)
	,mMaxSearchNum(100)
	,mSkipNum(3)
{
	mGridMap = new GridMap();
}

PathFindingMgr::~PathFindingMgr()
{
	if (mGridMap)
	{
		mGridMap->Reset();
		delete mGridMap;
	}
	for (auto path : mPathVec)
	{
		path->Reset();
		delete path;
	}
	mPathVec.clear();
	mPreSet.clear();
}

void PathFindingMgr::InitMap(int64 aWidth, int64 aLength, const Vector2& aNodeSize, const Vector2& aOriginPos)
{
	if (!mGridMap)
	{
		LOG_FATAL("not yet init GridMap");
		return;
	}

	for (Path* path : mPathVec)
	{
		path->Reset();
		delete path;
	}
	mPathVec.clear();

	mGridMap->ReInit(aWidth, aLength, aNodeSize, aOriginPos);
}

Path * PathFindingMgr::GetOrInitPath(int aEntityId)
{
	for (auto path : mPathVec)
	{
		if (path->mEntityId == aEntityId)
			return path;
	}
	auto path = new Path();
	path->Init(aEntityId, mGridMap, mMaxSearchNum, mSkipNum);
	mPathVec.emplace_back(path);
	return path;
}

void PathFindingMgr::ApplyBlockAreaManually(vector<int>& aIndexArr)
{
	mGridMap->ApplyBlockAreaManually(aIndexArr);
}

void PathFindingMgr::ApplyBlockArea(vector<Vector2>& aVec)
{
	mGridMap->ApplyBlockArea(aVec);
}

void PathFindingMgr::ApplyBoundaryNodes(vector<Vector2>& aVec)
{
	mGridMap->ApplyBoundaryNodes(aVec);
}

void PathFindingMgr::RegisterPreSetLocation(Vector2& aPos, int64 aSize, int aEntityId, bool aIsArmy1)
{
	if (mJustNavigate) return;
	int idx = PreSetLocation(aPos, aSize);
	if (idx < 0) return;
	vector<Vector3>& list = mPreSetByArmy1;
	if (!aIsArmy1) list = mPreSetByArmy2;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].x == aEntityId)
		{
			list[i].y = static_cast<int64>(idx);
			list[i].z = aSize;
			return;
		}
	}
	list.emplace_back(Vector3(aEntityId, idx, aSize));
}

void PathFindingMgr::UnregisterPreSetLocation(int aEntityId, bool aIsArmy1)
{
	if (mJustNavigate) return;
	vector<Vector3>& list = mPreSetByArmy1;
	if (!aIsArmy1) list = mPreSetByArmy2;
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		if (list[i].x == static_cast<int64>(aEntityId))
		{
			list[i] = list[size - 1];
			list.pop_back();
			return;
		}
	}
}

void PathFindingMgr::TryApplyPreSetLocation(bool aIsArmy1)
{
	if (mJustNavigate) return;
	if (mApplied) return;
	mApplied = true;
	vector<Vector3>& list = mPreSetByArmy1;
	if (!aIsArmy1) list = mPreSetByArmy2;
	for (int i = 0; i < list.size(); i++)
	{
		Vector2 v;
		v.x = list[i].y;
		v.z = list[i].z;
		mPreSet.push_back(v);
		mGridMap->RegisterGroundMask(v.z);
		if (v.x >= 0)
			mGridMap->MarkGround(v.x, v.z);
	}
}

int PathFindingMgr::PreSetLocation(Vector2& aPos, int64 aSize)
{
	Vector2 v;
	int idx = mGridMap->Position2Index(aPos.x, aPos.z);
	v.x = static_cast<int64>(idx);
	v.z = aSize;
	mPreSet.push_back(v);
	mGridMap->RegisterGroundMask(aSize);
	if (v.x < 0) return idx;
	mGridMap->MarkGround(v.x, aSize);
	return idx;
}

void PathFindingMgr::CleanUpPreSet()
{
	if (mJustNavigate) return;
	mApplied = false;
	if (mPreSet.size() == 0) return;
	for (auto v : mPreSet)
	{
		mGridMap->RetrieveGround(v.x, v.z);
	}
	mPreSet.clear();
}

void PathFindingMgr::SetPredefinedPath(int aEntityId, vector<Vector2>& aVec)
{
	Path* path = GetOrInitPath(aEntityId);
	path->SetPredefinedPath(aVec);
}

int PathFindingMgr::SyncPathProgress(int aEntityId, Vector2& aVec)
{
	Path* path = GetOrInitPath(aEntityId);
	if (!path->mUsePredefinedPath)
	{
		//LOG_WARN("try sync none-predefinedPath eid %d", aEntityId);
		return 0;
	}
	return path->SyncProgress(aVec);
}

void PathFindingMgr::UpdateLocation(int aEntityId, Vector2& aPos, int64 aSize)
{
	if (mJustNavigate) return;
	Path* path = GetOrInitPath(aEntityId);
	if (path->mCurrentIndex >= 0)
	{
		//recover previous ground mask
		mGridMap->RetrieveGround(path->mCurrentIndex, path->mSize);
		mGridMap->RegisterGroundMask(aSize);
		path->mCurrentIndex = mGridMap->Position2Index(aPos.x, aPos.z);
		path->mSize = aSize;
		if (path->mCurrentIndex < 0) return;
		mGridMap->MarkGround(path->mCurrentIndex, aSize);
	}
	else
	{
		//init for first time
		mGridMap->RegisterGroundMask(aSize);
		path->mCurrentIndex = mGridMap->Position2Index(aPos.x, aPos.z);
		path->mSize = aSize;
		if (path->mCurrentIndex < 0) return;
		mGridMap->MarkGround(path->mCurrentIndex, aSize);
	}
}

void PathFindingMgr::StartPath(int aEntityId, Vector2 aStartPos, Vector2 aTargetPos, int64 aCastRange)
{
	Path* path = GetOrInitPath(aEntityId);
	if (!mJustNavigate && path->mCurrentIndex >= 0)
	{  //need clean up self Ground mask before 
		mGridMap->RetrieveGround(path->mCurrentIndex, path->mSize);
	}

	path->PreparePath(aStartPos, aTargetPos, aCastRange, GetVersionId());
	path->CalculatePath();
	path->Complete();

	if (!mJustNavigate && path->mCurrentIndex >= 0)
	{  //add back after path done
		mGridMap->MarkGround(path->mCurrentIndex, path->mSize);
	}
}

PathCompleteState PathFindingMgr::GetPath(int aEntityId, vector<Vector2>& aPath)
{
	Path* path = GetOrInitPath(aEntityId);
	auto state = path->GetState();

	if (state == PathCompleteState::PathCompleteState_NotCalculated)
	{
		LOG_WARN("EntityId %d try get path but not calculate before", aEntityId);
		return state;
	}

	auto& vec = path->GetPath();
	aPath.reserve(vec.size());
	for (int i = 0; i < vec.size(); ++i)
	{
		aPath.emplace_back(vec[i]);
	}
	return state;
}