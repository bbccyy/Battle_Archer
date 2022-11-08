
#pragma once
#include "Define.h"
#include "Framework/SharedPool.h"

class GridNode : public IPoolable
{
public:
	GridNode();
	~GridNode();

	//GridNode(int aIndex, int aBoxX, int aBoxZ, unsigned int aFlag);

	void Init(int aIndex, int aBoxX, int aBoxZ, unsigned int aFlag)
	{
		Index = aIndex;
		X = aBoxX;
		Z = aBoxZ;
		mNeighbourFlag = aFlag;
	}

	void Reset()
	{
		version = 0;
		mParent = nullptr;
		G = 0;
		H = 0;
		Cost = 0;
		mNativeCost = 0;
		mNeighbourFlag = 0xFF; 
		mOccupant = 0;
		X = 0;
		Z = 0;
		Index = 0;	
		closed = false;  
	}
	
	inline int64 GetG()
	{
		return G;
	}

	inline void SetG(int64 aG)
	{
		G = aG;
	}

	inline int64 GetF()
	{
		return G + H;
	}

	inline void SetH(int64 aH)
	{
		H = aH;
	}

	inline int64 GetH()
	{
		return H;
	}

	inline int64 GetCost()
	{
		return Cost;
	}

	inline void SetCost(int64 aCost)
	{
		Cost = aCost;
	}

	inline void AddNativeCost(int64 aCost)
	{
		mNativeCost += aCost;
	}

	inline void SubNativeCost(int64 aCost)
	{
		mNativeCost -= aCost;
	}

	inline int64 GetNativeCost()
	{
		return mNativeCost;
	}

	inline void SetParent(GridNode* aGridNode)
	{
		mParent = aGridNode;
	}

	inline GridNode* GetParent()
	{
		return mParent;
	}

	inline void SetFlag(unsigned int aFlag)
	{
		mNeighbourFlag = aFlag;
	}

	/** True if the node has a connection in the specified direction.
	* The dir parameter corresponds to directions in the grid as:
	*         Z
	*         |
	*         |
	*
	*      6  2  5
	*       \ | /
	* --  3 - X - 1  ----- X
	*       / | \
	*      7  0  4
	*
	*         |
	*         |
	*/
	bool IsVisableNeighbour(int aDir);   //really need use this technology? 

public:
	int mOccupant = 0;		//denotes the player's ID, if any, that occupied of affected this node //TODO: DELETE IT 

	int X = 0;				//box 2-D position 
	int Z = 0;
	int Index = 0;			//index of Vector
	int version = 0;		//assigned by PathFindingMgr, increased by 1 for each pathfinding process 
	bool closed = false;    //together with version, could determine if this node is in closed list 
private:
	int64 G = 0;
	int64 H = 0;
	int64 Cost = 0;
	int64 mNativeCost = 0;

	GridNode* mParent = nullptr;
	unsigned int mNeighbourFlag = 0xFF;   //Really need do this? 
};