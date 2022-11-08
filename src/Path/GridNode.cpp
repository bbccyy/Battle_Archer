
#include "GridNode.h"

GridNode::GridNode()
	: G(0)
	, H(0)
	, Cost(0)
	, mNativeCost(0)
	, mParent(nullptr)
{
}

//GridNode::GridNode(int aIndex, int aBoxX, int aBoxZ, unsigned int aFlag)
//	: G(0)
//	, H(0)
//	, Cost(0)
//	, mNativeCost(0)
//	, mParent(nullptr)
//	, closed(false)
//	, Index(aIndex)
//	, X(aBoxX)
//	, Z(aBoxZ)
//	, mNeighbourFlag(aFlag)
//{
//}

GridNode::~GridNode()
{
}

bool GridNode::IsVisableNeighbour(int aDir)
{
	return (mNeighbourFlag >> aDir & 1) != 0;
}