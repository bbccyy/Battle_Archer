/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief  本来想让物理系统尽量独立一些，但是为了方便开发，还是让Agent中存了Entity的指针
*
**/


#pragma once
#include <vector>
#include "BoundingVolume.h"
#include "Framework/SharedPool.h"

using namespace std;

class Entity;

class Agent : public IPoolable
{
public:
    Agent();
    ~Agent();

    void Init(const WeakPtr<Entity>& aEntity, EBVType const aBVType, int const aGroupId);
    void Reset();

    inline SharedPtr<Entity> GetEntity()
    {
        return mEntity;
    }
    inline BoundingVolume* GetBV() const
    {
        return mBV;
    }
    int GetGroupId() const
    {
        return mGroupId;
    }

public:
    int64 mRegister0;
protected:
    BoundingVolume* mBV = nullptr; //bounding volume
    WeakPtr<Entity> mEntity;
    int mGroupId;
};


class PhysicsSystem
{
public:
    PhysicsSystem(int const aGroupCapacity, int const aAgentCapacity = 64);
    ~PhysicsSystem();

    Agent* AddAgent(const WeakPtr<Entity>& aEntity, EBVType const aBVType, int const aGroupId);
    void RemoveAgent(const Agent* aAgent);
    const vector<Agent*> GetAgentGroup(int const) const;

    //1)
    void SwepCircle2D(int const aGroupId, const Vector3& aStart, const Vector3& aEnd, int aRadius, vector<SharedPtr<Entity> >& aCollisionEntityArr);
	//2)
    void SwepLineCircle2D(int const aGroupId, const Vector3& aStart, const Vector3& aEnd, int aLength, vector<SharedPtr<Entity> >& aCollisionEntityArr);
	//3) Unit against boundary 
    bool SegmentPolygon(const Vector3&, const Vector3&, vector<Vector3>& aPolygon, int const, Vector3*);

    //TODO Delete 
    void IntersectionTest2D(int const aGroupId, const Agent* aSubjectAgent, const Vector3*, vector<SharedPtr<Entity> >& aResult);
	bool IntersectionSegSeg2D(const Vector3& aA1, const Vector3& aA2, const Vector3& aB1, const Vector3& aB2, Vector3& aPoint);
	bool SegmentPolygon2(const Vector3&, const Vector3&, const Vector3& aB1, const Vector3& aB2, int const, Vector3*);

protected:
    vector<vector<Agent*>> mAgentGroupArr;
};



