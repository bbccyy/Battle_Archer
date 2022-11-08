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
* @brief
*
**/

#include "PhysicsSystem.h"
#include "Framework/SharedPool.h"
#include "Log/Log.h"
#include "CollisionDetection.h"
#include "Region.h"
#include "Framework/Util.h"

using namespace std;


bool cmpAgent( const Agent* a1, const Agent* a2 )
{
    return a1->mRegister0 < a2->mRegister0;
}


Agent::Agent()
{
    mBV = nullptr;
}

Agent::~Agent()
{
    Reset();
}

void Agent::Reset()
{
    if( mBV != nullptr )
    {
        switch (mBV->type)
        {
            case EBVTypeCylinder:
                SharedPool<Cylinder>::PutRaw( dynamic_cast<Cylinder*>(mBV));
                break;
            case EBVTypeOBB:
                SharedPool<OBB>::PutRaw( dynamic_cast<OBB*>(mBV));
                break;
            default:
                delete mBV;
                LOG_WARN("invalid bounding volume type:%d", mBV->type);
        }
        mBV = nullptr;
    }
}

void Agent::Init(const WeakPtr<Entity>& aEntity, EBVType const aBVType, int const aGroupId)
{
    if(mBV)
    {
        LOG_FATAL("already init");
    }
    switch (aBVType)
    {
        case EBVTypeCylinder:
            mBV = SharedPool<Cylinder>::GetRaw();
            break;
        case EBVTypeOBB:
            mBV= SharedPool<OBB>::GetRaw();
            break;
        default:
            LOG_FATAL("invalid bounding volume type:%d", aBVType);
    }
	mEntity = aEntity;
    mGroupId = aGroupId;
}

PhysicsSystem::PhysicsSystem(int const aGroupCapacity, int const aAgentCapacity)
    : mAgentGroupArr(vector<vector<Agent*>>(0))
{
    mAgentGroupArr.reserve(aGroupCapacity);
    for (int n = 0; n < aGroupCapacity; ++n) {
        mAgentGroupArr.emplace_back();
        mAgentGroupArr.back().reserve(aAgentCapacity);
    }
}

PhysicsSystem::~PhysicsSystem()
{

}

Agent* PhysicsSystem::AddAgent(const WeakPtr<Entity>& aEntity, EBVType const aBVType, int const aGroupId)
{
    Agent* agent = SharedPool<Agent>::GetRaw();
    agent->Init(aEntity, aBVType, aGroupId);
    mAgentGroupArr[aGroupId].emplace_back(agent);
    return agent;
}

 
void PhysicsSystem::RemoveAgent(const Agent* aAgent)
{
	if (!aAgent)
	{
		return;
	}
    auto& group = mAgentGroupArr[aAgent->GetGroupId()];
    for(size_t i = 0; i < group.size(); i++)
    {
        if(group[i] == aAgent )
        {
            group[i]->Reset();
            SharedPool<Agent>::PutRaw(group[i]);

            group[i] = group.back();
            group.pop_back();
            return;
        }
    }
    LOG_DEBUG("not found agent");
}

const vector<Agent*> PhysicsSystem::GetAgentGroup(int const aId) const
{
    return mAgentGroupArr[aId];
}

//2D平面的碰撞检测
bool PhysicsSystem::IntersectionSphereWithAny2D(const Vector3& aCenter, const int aSize, const Agent* aSubjectAgent, EBVType const aBVType)
{
	BoundingVolume* bv = aSubjectAgent->GetBV(); 
	bool hasCollision = false;
	const auto& center = Vector2(aCenter.x, aCenter.z);
	CollisionResults results;
	switch (bv->type)
	{
	case EBVTypeCylinder:
		{
			const auto& cylinder = dynamic_cast<Cylinder*>(bv);
			const auto& tarCenter = Vector2(cylinder->center.x, cylinder->center.z);
			hasCollision = IntersectPointSphere2D(center, aSize + cylinder->radius, tarCenter);
		}
		break;
	case EBVTypeOBB:
		{
			hasCollision = IntersectOBBSphere2D(center, aSize, dynamic_cast<OBB*>(bv), results);
		}
		break;
	default:
		LOG_WARN("invalid bounding volume type:%d", bv->type);
	}
	return hasCollision;
}

void PhysicsSystem::SwepLineCircle2D(int const aGroupId, const Vector3& aStart, const Vector3& aEnd, int aLength, vector<SharedPtr<Entity> >& aCollisionEntityArr)
{
	auto& group = mAgentGroupArr[aGroupId];
	vector<Agent*> collisionAgentArr;
	Vector2 startPos(aStart.x, aStart.z);
	Vector2 front(aEnd.x, aEnd.z);
	front -= startPos; 
	Vector2 size(int64(aLength/2), front.Magnitude()/2);
	Vector3 center = (aEnd - aStart)/2 + aStart; 
	OBB* tmp = new OBB;
	tmp->Update(&center, &size, &front);
	CollisionResults results;
	//IntersectOBBSphere2D
	for (size_t i = 0; i < group.size(); i++)
	{
		Agent* agent = group[i];
		BoundingVolume* bv = agent->GetBV();
		bool hasCollision = false;
		switch (bv->type)
		{
		case EBVTypeCylinder:
			{
			Cylinder* cylinder = dynamic_cast<Cylinder*>(bv);
			Vector2 tmpCenter(cylinder->center.x, cylinder->center.z);
			hasCollision = IntersectOBBSphere2D(tmpCenter, cylinder->radius, tmp, results);
			RestoreObjToPool(tmpCenter);
			}
			break;
		case EBVTypeOBB:
			{
			OBB* obb = dynamic_cast<OBB*>(bv);
			hasCollision = IntersectOBBOBB2D(tmp, obb, results);
			}
			break;
		default:
			LOG_WARN("invalid bounding volume type:%d", bv->type);
		}
		if (hasCollision)
		{
			agent->mRegister0 = results.CollisionPos;
			collisionAgentArr.push_back(agent);
		}
	}

	delete tmp;
	if (collisionAgentArr.empty())
	{
		RestoreObjToPool(startPos);
		RestoreObjToPool(front);
		RestoreObjToPool(size);
		RestoreObjToPool(center);
		return;
	}
	selectionSort(collisionAgentArr, cmpAgent);
	aCollisionEntityArr.reserve(collisionAgentArr.size());
	for (size_t i = 0; i < collisionAgentArr.size(); i++)
	{
		aCollisionEntityArr.emplace_back(collisionAgentArr[i]->GetEntity());
	}
	RestoreObjToPool(startPos);
	RestoreObjToPool(front);
	RestoreObjToPool(size);
	RestoreObjToPool(center);
}

void PhysicsSystem::SwepCircle2D(int const aGroupId, const Vector3& aStart, const Vector3& aEnd, int const aRadius, vector<SharedPtr<Entity> >& aCollisionEntityArr)
{
    auto& group = mAgentGroupArr[aGroupId];
    vector<Agent*> collisionAgentArr;
    Vector2 startPos(aStart.x, aStart.z);
    Vector2 endPos(aEnd.x, aEnd.z);
    CollisionResults results;
    for(size_t i = 0; i < group.size(); i++)
    {
        Agent* agent = group[i];
        BoundingVolume* bv = agent->GetBV();
        bool hasCollision = false;
        switch (bv->type)
        {
            case EBVTypeCylinder:
                hasCollision = IntersectMovingSphereSphere2D(startPos, endPos, aRadius, dynamic_cast<Cylinder*>(bv), results);
                break;
            case EBVTypeOBB:
                hasCollision = IntersectMovingSphereOBB2D(startPos, endPos, aRadius, dynamic_cast<OBB*>(bv), results);
                break;
            default:
                LOG_WARN("invalid bounding volume type:%d", bv->type);
        }
        if(hasCollision)
        {
            agent->mRegister0 = results.CollisionPos;
            collisionAgentArr.push_back(agent);
        }
    }
    if( collisionAgentArr.empty() )
    {
        return;
    }
	selectionSort(collisionAgentArr, cmpAgent);
	aCollisionEntityArr.reserve(collisionAgentArr.size());
    for( size_t i = 0; i < collisionAgentArr.size(); i++)
    {
		aCollisionEntityArr.emplace_back( collisionAgentArr[i]->GetEntity() );
    }

}

// find out all agents as Entity managed by mAgentArr which located within the range described by input param aSubjectAgent and aSubjectCenter
void PhysicsSystem::IntersectionTest2D(int const aGroupId, const Agent* aSubjectAgent, const Vector3* aSubjectCenter, vector<SharedPtr<Entity> >& aResult)
{
    auto& group = mAgentGroupArr[aGroupId];
	BoundingVolume* bv = aSubjectAgent->GetBV();
	//目前只支持被测试对象是圆柱的情况  
	if (bv->type != EBVTypeCylinder)
	{
		LOG_FATAL("only surpport subject bv: cylinder");
		return;
	}
	Cylinder* cylinder = dynamic_cast<Cylinder*>(bv);

	Vector2 subjectCenter;
    if (aSubjectCenter)
    {
        subjectCenter.x = aSubjectCenter->x;
        subjectCenter.z = aSubjectCenter->z;
    }
    else
    {
        subjectCenter.x = cylinder->center.x;
        subjectCenter.z = cylinder->center.z;
    }
	
	int64 subJectRadius = cylinder->radius;

	for (auto* agent : group)
	{
        if (agent != aSubjectAgent)
        {
            bv = agent->GetBV();

            bool hasIntersection = false;
            switch (bv->type)
            {
            case EBVTypeCylinder:
            {
                cylinder = dynamic_cast<Cylinder*>(bv);
                Vector2 center(cylinder->center.x, cylinder->center.z);
                hasIntersection = IntersectPointSphere2D(subjectCenter, subJectRadius + cylinder->radius, center);
                RestoreObjToPool(center);
            }
            break;
            case EBVTypeOBB:
            {
                OBB* obb = dynamic_cast<OBB*>(bv);
                CollisionResults results;
                hasIntersection = IntersectOBBSphere2D(subjectCenter, subJectRadius, obb, results);
            }
            break;
            default:
                LOG_WARN("invalid bounding volume type:%d", bv->type);
            }
            if (hasIntersection)
            {
                aResult.emplace_back(agent->GetEntity());
            }
        }
	}
    RestoreObjToPool(subjectCenter);
}


bool PhysicsSystem::SegmentPolygon2(const Vector3& aA1, const Vector3& aA2, const Vector3& aB1, const Vector3& aB2, int const aRadius, Vector3* aResult)
{
	Vector3 tmp;
	if (IntersectionSegSeg2D(aA1, aA2, aB1, aB2, tmp))
	{
		if (aRadius > MIN_LEN)
		{
			Vector3 reduction = aA1 - aA2;
			reduction.ScaleToLen(aRadius);
			aResult->Set(tmp.x + reduction.x, aA2.y, tmp.z + reduction.z);
		}
		else
		{
			aResult->Set(tmp.x, aA2.y, tmp.z);
		}
		return true;
	}
	return false;
}


bool PhysicsSystem::IntersectionSegSeg2D(const Vector3 & aA1, const Vector3 & aA2, const Vector3 & aB1, const Vector3 & aB2, Vector3 & aPoint)
{
	bool hasCollision = false;
	const auto& a1 = Vector2(aA1.x, aA1.z);
	const auto& a2 = Vector2(aA2.x, aA2.z);
	const auto& b1 = Vector2(aB1.x, aB1.z);
	const auto& b2 = Vector2(aB2.x, aB2.z);
	CollisionResults results;
	hasCollision = IntersectSegmentSegment2D(a1, a2, b1, b2, results);
	if (!hasCollision)
	{
		return hasCollision;
	}
	aPoint.x = results.CollisionPoint.x;
	aPoint.y = 0;
	aPoint.z = results.CollisionPoint.z;
	return hasCollision;
}

bool PhysicsSystem::SegmentPolygon(const Vector3& aStart, const Vector3& aEnd, vector<Vector3>& aPolygon, int const aRadius, Vector3* aResult)
{
    bool ret = true;
    for (int i = 0, j = static_cast<int>(aPolygon.size() - 1); i < aPolygon.size(); ++i)
    {
        if ((aPolygon[i].z > aEnd.z) != (aPolygon[j].z > aEnd.z)
            && (aEnd.x < aPolygon[i].x + (aPolygon[j].x - aPolygon[i].x) * (aEnd.z - aPolygon[i].z) / (aPolygon[j].z - aPolygon[i].z)))
        {
            ret = !ret;
        }
        j = i;
    }
    if (!ret)
    {
        aResult->Set(aEnd);
        return ret;
    }
    else
    {
        //https://stackoverflow.com/a/14795484
        int64 x, z;
        const Vector3& a = aStart;
        const Vector3& b = aEnd;
        int64 ab_x, ab_z, cd_x, cd_z, ca_x, ca_z, s, t, denom;
        int i = 0, j = static_cast<int>(aPolygon.size() - 1), size = static_cast<int>(aPolygon.size());
        for (; i < size; ++i)
        {
            Vector3& c = aPolygon[j];
            Vector3& d = aPolygon[i];
            /*LOG_DEBUG("a(%f,%f,%f) b(%f,%f,%f)"
                , (float)a.x / DENOM, (float)a.y / DENOM, (float)a.z / DENOM
                , (float)b.x / DENOM, (float)b.y / DENOM, (float)b.z / DENOM
            );
            LOG_DEBUG("c(%f,%f,%f) d(%f,%f,%f)"
                , (float)c.x / DENOM, (float)c.y / DENOM, (float)c.z / DENOM
                , (float)d.x / DENOM, (float)d.y / DENOM, (float)d.z / DENOM
            );*/
            ab_x = b.x - a.x;
            ab_z = b.z - a.z;
            cd_x = d.x - c.x;
            cd_z = d.z - c.z;
            ca_x = a.x - c.x;
            ca_z = a.z - c.z;

            denom = ab_x * cd_z - cd_x * ab_z;
            if (denom == 0)
            {
                //LOG_DEBUG("collinear");
            }
            else
            {
                bool denomPositive = denom > 0;
                s = ab_x * ca_z - ab_z * ca_x;
                if ((s <= 0) == denomPositive)
                {
                    //LOG_DEBUG("a outside of bc");
                }
                else
                {
                    t = cd_x * ca_z - cd_z * ca_x;
                    if ((t <= 0) == denomPositive)
                    {
                        //LOG_DEBUG("c outside of ab");
                    }
                    else
                    {
                        if (((s >= denom) == denomPositive) || ((t >= denom) == denomPositive))
                        {
                            //LOG_DEBUG("other non collision");
                        }
                        else
                        {
                            /*
                            LOG_DEBUG("radius=%d, ab=(%f,%f) abp=(%f,%f) abp1=(%f,%f) t=%lld denom=%lld p=%f,%f"
                                , aRadius
                                , (float)ab_x / DENOM, (float)ab_z / DENOM
                                , (float)((t * ab_x) / denom) / DENOM, (float)((t * ab_z) / denom) / DENOM
                                , (float)(((t / DENOM_SQR) * ab_x) / (denom / DENOM_SQR)) / DENOM, (float)(((t / DENOM_SQR) * ab_z) / (denom / DENOM_SQR)) / DENOM
                                , t, denom, (float)t/denom, (float)(t / DENOM_SQR) / (denom / DENOM_SQR));
                                */

                            if ((t > DENOM_SQR || t < -DENOM_SQR) && (denom > DENOM_SQR || denom < -DENOM_SQR))
                            {
                                t = t / DENOM;
                                denom = denom / DENOM;
                            }
                            x = a.x + (t * ab_x) / denom;
                            z = a.z + (t * ab_z) / denom;
                            //LOG_DEBUG("target (%f,%f,%f)", (float)x / DENOM, (float)aEnd.y / DENOM, (float)z / DENOM);

                            if (aRadius > MIN_LEN)
                            {
                                Vector3 reduction = aStart - aEnd;
                                reduction.ScaleToLen(aRadius);
                                //LOG_DEBUG("radius reduction (%f,%f,%f)", (float)reduction.x / DENOM, (float)reduction.y / DENOM, (float)reduction.z / DENOM);
                                aResult->Set(x + reduction.x, aEnd.y, z + reduction.z);
                            }
                            else
                            {
                                aResult->Set(x, aEnd.y, z);
                            }
                            return ret;
                        }
                    }
                }
            }
			if (size == 2) break;
			j = i;
        }
        //assert(false);
        aResult->Set(aStart.x, aStart.y, aStart.z);
        return ret;
    }
}

bool CollisionDetectionRegionWithBV(Region* aRegion, BoundingVolume* aBv)
{
    CollisionResults results;
    switch (aRegion->type)
    {
    case ERegionCircle:
    {
        RegionCircle* circle = dynamic_cast<RegionCircle*>(aRegion);
        switch (aBv->type)
        {
        case EBVTypeCylinder:
        {
            Cylinder* cylinder = dynamic_cast<Cylinder*>(aBv);
            Vector2 center(cylinder->center.x, cylinder->center.z);
            return IntersectPointSphere2D(center, cylinder->radius + circle->radius + circle->selfSize, circle->center);
        }
        case EBVTypeOBB:
        {
            return IntersectOBBSphere2D(circle->center, circle->radius + circle->selfSize, dynamic_cast<OBB*>(aBv), results);
        }
        }
        break;
    }
    case ERegionSector:
    {
        RegionSector* sector = dynamic_cast<RegionSector*>(aRegion);
        switch (aBv->type)
        {
        case EBVTypeCylinder:
        {
            Cylinder* cylinder = dynamic_cast<Cylinder*>(aBv);
            Vector2 center(cylinder->center.x, cylinder->center.z);
            return IntersectSectorSphere2D(sector->center, sector->forward, sector->angle * 5, 10,
                sector->radius, center, cylinder->radius, results);
        }
        case EBVTypeOBB:
        {
            LOG_FATAL("not support intersect test between obb and sctor");
            return false;
        }
        }
        break;
    }
    case ERegionAnnulus:
    {
        RegionAnnulus* annulus = dynamic_cast<RegionAnnulus*>(aRegion);
        switch (aBv->type)
        {
        case EBVTypeCylinder:
        {
            Cylinder* cylinder = dynamic_cast<Cylinder*>(aBv);
            Vector2 center(cylinder->center.x, cylinder->center.z);
            return IntersectRingSphere2D(center, cylinder->radius, annulus->center, annulus->radius1, annulus->radius2);
        }
        case EBVTypeOBB:
        {
            LOG_FATAL("not support intersect test between obb and annulus");
            return false;
        }
        }
        break;
    }
    case ERegionRectangle:
    {
        RegionRectangle* rectangle = dynamic_cast<RegionRectangle*>(aRegion);
        OBB obb;
        obb.center.x = rectangle->center.x;
        obb.center.y = 0;
        obb.center.z = rectangle->center.z;
        obb.halfSize = rectangle->halfSize;
        obb.front = rectangle->forward;
        obb.right.x = obb.front.z;
        obb.right.z = -obb.front.x;
        switch (aBv->type)
        {
        case EBVTypeCylinder:
        {
            Cylinder* cylinder = dynamic_cast<Cylinder*>(aBv);
            Vector2 center(cylinder->center.x, cylinder->center.z);
            return IntersectOBBSphere2D(center, cylinder->radius, &obb, results);
        }
        case EBVTypeOBB:
        {
            return IntersectOBBOBB2D(&obb, dynamic_cast<OBB*>(aBv));
        }
        }
        break;
    }
    }
    return false;
}