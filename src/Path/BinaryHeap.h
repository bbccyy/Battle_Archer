#pragma once
#include "PathDefine.h"

class GridNode;

struct Tuple
{
public:
	unsigned int F;
	GridNode* Node;
};

class BinaryHeap
{
public:
	//BinaryHeap();
	BinaryHeap(int aCapacity);
	~BinaryHeap();

	/** Number of items in the tree */
	int mNumberOfItems;

	/** The tree will grow by at least this factor every time it is expanded */
	int mGrowthFactor;

	/** Number of children of each node in the tree. */
	const int D = 4;

	/** Sort nodes by G score if there is a tie when comparing the F score. */
	const bool SortGScores = true;

	/** Rounds up v so that it has remainder 1 when divided by D. */
	int RoundUpToNextMultipleMod1(int v);

	void Clear();

	GridNode* GetNode(int i);

	void SetF(int i, unsigned int F);

	void Expand();

	void Add(GridNode* aNode);

	/** Returns the node with the lowest F score from the heap */
	GridNode* Remove();

	inline bool IsEmpty()
	{
		return mNumberOfItems <= 0;
	}
private:
	vector<Tuple> mHeapVec;
};