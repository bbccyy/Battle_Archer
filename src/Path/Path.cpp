
#include "Path.h"
#include "GridMap.h"
#include "GridNode.h"


Path::Path()
	: mVersion(0)
	, mEntityId(0)
	, mCurrentIndex(-1)
	, mMaxSearchNum(200)
	, mGridMap(nullptr)
	, mUsePredefinedPath(false)
{
	mHeap = new BinaryHeap(256);
}

Path::~Path()
{

}

void Path::Reset()
{
	mVersion = 0;
	mEntityId = 0;
	mCurrentIndex = -1;
	mMaxSearchNum = 200;
	mCurrentNode = nullptr;
	mStartNode = nullptr;
	mTargetNode = nullptr;
	mBestNode = nullptr;
	mGridMap = nullptr;
	neighbourOffsets = nullptr;
	neighbourCosts = nullptr;
	mUsePredefinedPath = false;
	mState = PathCompleteState::PathCompleteState_NotCalculated;

	if (mHeap)
		delete mHeap;
	mVectorPath.clear();
}

void Path::PreparePath(Vector2 aStart, Vector2 aTarget, int64 aCastRange, int aVersionNum)
{
	if (mUsePredefinedPath)
	{
		CalculatePredefine(aTarget);
		return;
	}
	if (mGridMap == nullptr)
	{
		LOG_WARN("use Path but not init");
		return;
	}
	mVersion = aVersionNum;
	mCastRange = aCastRange;
	mHeap->Clear();

	Vector2 startPos, tarPos;
	mGridMap->Position2PositionForce(aStart.x, aStart.z, startPos);
	mGridMap->Position2PositionForce(aTarget.x, aTarget.z, tarPos);

	mStartNode = mGridMap->GetOrInitNode(startPos.x, startPos.z);
	if (!mStartNode)
	{
		LOG_INFO("not found start pos, [%d, %d]", aStart.x, aStart.z);
		mStartNode = mGridMap->GetOrInitNodeForce(startPos.x, startPos.z);
	}

	mTargetNode = mGridMap->GetOrInitNode(tarPos.x, tarPos.z);
	if (!mTargetNode)
	{
		LOG_INFO("not found target pos, [%d, %d]", aTarget.x, aTarget.z);
		mTargetNode = mGridMap->GetOrInitNodeForce(tarPos.x, tarPos.z);
	}

	mCurrentNode = mStartNode;
	mBestNode = mStartNode;
	int64 initH = mGridMap->ManhattanDist(mCurrentNode->X, mCurrentNode->Z, mTargetNode->X, mTargetNode->Z);
	mCurrentNode->version = mVersion;
	mCurrentNode->SetG(0);
	mCurrentNode->SetH(initH);
	mCurrentNode->SetParent(nullptr);
	mCurrentNode->closed = false;
	mHeap->Add(mCurrentNode);

	neighbourOffsets = mGridMap->GetNeighbourOffset();
	neighbourCosts = mGridMap->GetNeighbourCost();

	mState = PathCompleteState::PathCompleteState_NotCalculated;

}

void Path::CalculatePath()
{
	if (mUsePredefinedPath)
		return;
	int counter = 0;
	while (mState == PathCompleteState::PathCompleteState_NotCalculated)
	{
		if (counter > mMaxSearchNum)
		{
			mState = PathCompleteState::PathCompleteState_Partial;
			return;
		}

		if (mHeap->IsEmpty())
		{
			mState = PathCompleteState::PathCompleteState_Partial;
			return;
		}

		mCurrentNode = mHeap->Remove();
		if (mCurrentNode->closed)
		{
			continue;
		}

		counter++;
		mCurrentNode->closed = true;  //close this node 

		if (mCurrentNode->GetH() < mBestNode->GetH())
		{
			mBestNode = mCurrentNode;
			if (mBestNode->GetH() <= mCastRange)
			{
				mState = PathCompleteState::PathCompleteState_Complete;
				return;
			}
		}

		int index = mCurrentNode->Index;
		for (int i = 0; i < 8; ++i)
		{
			GridNode* other = mGridMap->GetOrInitNode(index + neighbourOffsets[i]);
			if (!other)
			{  //out of boundary 
				continue;
			}
			int64 curCost = neighbourCosts[i];
			int64 costFromCurrent = other->GetNativeCost() + mCurrentNode->GetG() + curCost;
			if (other->version == mVersion)
			{  //this node has been visited before
				if (other->closed)
				{  //skip closed node
					continue;
				}
				if (other->GetG() > costFromCurrent)
				{
					other->SetG(costFromCurrent);
					other->SetParent(mCurrentNode);
					mHeap->Add(other);
				}
			}
			else
			{  //discover a new node
				other->version = mVersion;
				other->closed = false;
				other->SetG(costFromCurrent);
				other->SetH(mGridMap->ManhattanDist(other->X, other->Z, mTargetNode->X, mTargetNode->Z));
				other->SetParent(mCurrentNode);
				mHeap->Add(other);
			}
		}
	}
}

void Path::Complete()
{
	if (mUsePredefinedPath)
		return;
	//gen the path vector according to mBestNode 
	mVectorPath.clear();
	mVectorPath.reserve(50);  //experience value 
	mCurrentNode = mBestNode;
	if (!mCurrentNode)
	{
		LOG_WARN("invalid search, no BestNode");
		return;
	}

	vector<Vector2> list;
	list.reserve(50);
	while (mCurrentNode)
	{
		Vector2 tmp(mCurrentNode->X, mCurrentNode->Z);
		list.emplace_back(tmp);
		mCurrentNode = mCurrentNode->GetParent();
	}

	if (list.size() > mSkipNum)
	{
		for (int i = 0; i < mSkipNum; ++i)
		{
			list.pop_back();
		}
	}

	int idx = list.size() - 1;
	int lastX = list[idx].x;
	int lastZ = list[idx].z;
	int val = -1;
	Vector2 curPos;

	//while (mCurrentNode)
	for ( ; idx >= 0; --idx)
	{
		curPos = list[idx];
		bool popLast = false;
		int dir = GetDir(lastX, lastZ, curPos.x, curPos.z);
		lastX = curPos.x;
		lastZ = curPos.z;
		if (dir != -1)
		{
			if (val == -1)
			{
				val = dir;
				popLast = false;
			}
			else
			{
				if (val != dir)
				{
					//do not pop last;
					popLast = false;
					val = dir;
				}
				else
				{
					popLast = true;
				}
			}
		}

		if (popLast && mVectorPath.size() > 0)
		{
			mVectorPath.pop_back();
		}

		Vector2 tmp;
		mGridMap->Position2RealPosition(curPos.x, curPos.z, tmp);
		mVectorPath.emplace_back(tmp);
	}
	list.clear();

	PostPathProcess();
}

void Path::PostPathProcess()
{
	if (mUsePredefinedPath)
		return;
	if (mVectorPath.size() < 3) return;
	Vector2 startPos;
	Vector2 curPos;
	int idx = 0;  //point to start position
	int vSize = mVectorPath.size();
	vector<int> shotPath;
	shotPath.reserve(vSize);
	shotPath.emplace_back(idx);
	int64 nodeSize = mGridMap->GetNodeSize();
	while (idx < vSize - 1)
	{
		startPos = mVectorPath[idx];
		int p = idx + 2;  //point to the tmp end position 
		while (p < vSize)
		{
			curPos = mVectorPath[p];
			if (!IsWalkableA2B(startPos, curPos, nodeSize))
			{
				p--;
				shotPath.emplace_back(p);
				break;
			}
			p++;
		}
		idx = p;
	}
	shotPath.emplace_back(vSize - 1);
	if (shotPath.size() == vSize)
		return;

	vector<Vector2> tmp;
	tmp.reserve(shotPath.size());
	for (int idx : shotPath)
	{
		tmp.emplace_back(mVectorPath[idx]);
	}
	mVectorPath.clear();
	if (mState == PathCompleteState::PathCompleteState_Complete &&
		tmp.size() < 3)
	{ //just use trace 
		if (tmp.size() > 0)
			mVectorPath.push_back(tmp[tmp.size()-1]);
		tmp.clear();
	}
	else
	{
		mVectorPath = tmp;
	}
}

bool Path::IsWalkableA2B(Vector2& aA, Vector2& aB, int64 aStepDist)
{
	Vector2 dir = aB - aA;
	Vector2 tar;
	int64 mag = dir.Magnitude();
	int64 step = aStepDist;
	while (step < mag)
	{
		dir.ScaleToLen(step);
		tar = aA + dir;
		if (!mGridMap->Walkable(tar.x, tar.z))
		{
			return false;
		}
		step += aStepDist;
	}
	return true;
}

int Path::GetDir(int aX1, int aZ1, int aX2, int aZ2)
{
	//old pos <X1,Z1>, new pos<X2, Z2>
	if (aX1 < aX2)
	{
		if (aZ1 < aZ2)
		{
			return 5;
		}
		else if (aZ1 == aZ2)
		{
			return 1;
		}
		else
		{
			return 4;
		}
	}
	else if (aX1 == aX2)
	{
		if (aZ1 < aZ2)
		{
			return 2;
		}
		else if (aZ1 == aZ2)
		{
			return -1;  //same position
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (aZ1 < aZ2)
		{
			return 6;
		}
		else if (aZ1 == aZ2)
		{
			return 3;
		}
		else
		{
			return 7;
		}
	}
	return -1;
}

void Path::CalculatePredefine(Vector2& aTargetPos)
{
	if (!mUsePredefinedPath)
		return;
	int s = mPredefinedPath.size();
	if (s == 0)
		return;

	mVectorPath.clear();
	bool isForward = true;
	if (aTargetPos == mPredefinedPath[0])
	{
		isForward = false;
	}

	if (!isForward)
	{
		for (int i = mPositiveNextIdx - 1; i >= 0; --i)
		{
			mVectorPath.emplace_back(mPredefinedPath[i]);
		}
	}
	else
	{
		for (int i = mPositiveNextIdx; i < s; ++i)
		{
			mVectorPath.emplace_back(mPredefinedPath[i]);
		}
	}

	mState = PathCompleteState::PathCompleteState_Complete;
}

void Path::SetPredefinedPathIndex(int aIndex)
{
	mPositiveNextIdx = aIndex;
}

int Path::SyncProgress(Vector2& aVec)
{
	if (!mUsePredefinedPath)
		return 0;
	int s = mPredefinedPath.size();
	for (int i = 0; i < s; i++)
	{
		if (aVec == mPredefinedPath[i])
		{
			mPositiveNextIdx = i + 1;
			if (mPositiveNextIdx == s)  
				return -1;  //Indicate it's the last point 
			return mPositiveNextIdx;
		}
	}
	LOG_FATAL("unable to sync point [%d, %d] with current path", aVec.x, aVec.z);
	return 0;
}

void Path::SetPredefinedPath(vector<Vector2>& aVec)
{
	if (aVec.empty())
		return;
	mUsePredefinedPath = true;
	mPositiveNextIdx = 0;
	mPredefinedPath.clear();
	for (auto& v : aVec)
	{
		mPredefinedPath.emplace_back(v);
	}
}