
#include "GridNode.h"
#include "BinaryHeap.h"

#include <stdlib.h>

//BinaryHeap::BinaryHeap()
//{
//
//}

BinaryHeap::BinaryHeap(int aCapacity)
	: mGrowthFactor(2)
	, mNumberOfItems(0)
{
	vector<Tuple> mHeapVec(aCapacity);
}

BinaryHeap::~BinaryHeap()
{
	mHeapVec.clear();
}

int BinaryHeap::RoundUpToNextMultipleMod1(int v)
{
	return v + (4 - ((v - 1) % D)) % D;
}

void BinaryHeap::Clear()
{
	mNumberOfItems = 0;
	mHeapVec.clear();
}

GridNode* BinaryHeap::GetNode(int i)
{
	return mHeapVec[i].Node;
}

void BinaryHeap::SetF(int i, unsigned int F)
{
	mHeapVec[i].F = F;
}

void BinaryHeap::Expand()
{
	int newSize = std::max((int)(mHeapVec.size() + 4), (int)(mHeapVec.size() * mGrowthFactor));
	newSize = RoundUpToNextMultipleMod1(newSize);

	if (newSize > 1 << 18)
	{
		throw "inary Heap Size really large (2^18).";
		return;
	}

	mHeapVec.resize(newSize);
}

void BinaryHeap::Add(GridNode* aNode)
{
	if (aNode == NULL)
	{
		return;
	}

	if (mNumberOfItems == mHeapVec.size()) {
		Expand();
	}

	int bubbleIndex = mNumberOfItems;
	unsigned int nodeF = aNode->GetF();
	unsigned int nodeG = aNode->GetG();
	while (bubbleIndex != 0) {
		// Parent node of the bubble node
		int parentIndex = (bubbleIndex - 1) / D;

		if (nodeF < mHeapVec[parentIndex].F || (SortGScores && nodeF == mHeapVec[parentIndex].F && nodeG > mHeapVec[parentIndex].Node->GetG())) {
			// Swap the bubble node and parent node
			// (we don't really need to store the bubble node until we know the final index though
			// so we do that after the loop instead)
			mHeapVec[bubbleIndex] = mHeapVec[parentIndex];
			bubbleIndex = parentIndex;
		}
		else {
			break;
		}
	}

	Tuple t;
	t.F = nodeF;
	t.Node = aNode;
	mHeapVec[bubbleIndex] = t;
	mNumberOfItems++;
}

GridNode* BinaryHeap::Remove()
{
	if (mNumberOfItems == 0)
	{
		return NULL;
	}

	mNumberOfItems--;
	GridNode* returnNode = mHeapVec[0].Node;

	Tuple swapItem = mHeapVec[mNumberOfItems];
	unsigned int swapItemG = swapItem.Node->GetG();
	int parent, swapIndex = 0;
	while (true)
	{
		parent = swapIndex;
		unsigned int swapF = swapItem.F;
		int pd = parent * D + 1;

		if (pd <= mNumberOfItems)
		{
			unsigned int f0 = mHeapVec[pd + 0].F;
			unsigned int f1 = mHeapVec[pd + 1].F;
			unsigned int f2 = mHeapVec[pd + 2].F;
			unsigned int f3 = mHeapVec[pd + 3].F;

			if (pd + 0 < mNumberOfItems && (f0 < swapF ||
				(SortGScores && f0 == swapF && mHeapVec[pd + 0].Node->GetG() < swapItemG))) {
				swapF = f0;
				swapIndex = pd + 0;
			}

			if (pd + 1 < mNumberOfItems && (f1 < swapF ||
				(SortGScores && f1 == swapF && mHeapVec[pd + 1].Node->GetG() < (swapIndex == parent ? swapItemG : mHeapVec[swapIndex].Node->GetG())))) {
				swapF = f1;
				swapIndex = pd + 1;
			}

			if (pd + 2 < mNumberOfItems && (f2 < swapF ||
				(SortGScores && f2 == swapF && mHeapVec[pd + 2].Node->GetG() < (swapIndex == parent ? swapItemG : mHeapVec[swapIndex].Node->GetG())))) {
				swapF = f2;
				swapIndex = pd + 2;
			}

			if (pd + 3 < mNumberOfItems && (f3 < swapF ||
				(SortGScores && f3 == swapF && mHeapVec[pd + 3].Node->GetG() < (swapIndex == parent ? swapItemG : mHeapVec[swapIndex].Node->GetG())))) {
				swapIndex = pd + 3;
			}
		}

		if (parent != swapIndex)
		{
			mHeapVec[parent] = mHeapVec[swapIndex];
		}
		else
		{
			break;
		}
	}

	mHeapVec[swapIndex] = swapItem;
	return returnNode;
}

