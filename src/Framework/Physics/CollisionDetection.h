/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author bbccyy
* @date $Date$
* @version $Revision$
* @brief
*
**/

#pragma once

#include "Framework/Transform.h"
#include "BoundingVolume.h"
#include "Log/Log.h"
#include <algorithm> 

#define NUMDIM  3
#define RIGHT   0
#define LEFT    1
#define MIDDLE  2

typedef struct CollisionResults {

	Vector2  CollisionPoint;

	int64    CollisionPos;

	CollisionResults() :CollisionPos(0), CollisionPoint(0,0)
	{
	}

}CollisionResults;

bool IntersectRayAABB2D(const Vector2& aStart, const Vector2& aEnd, const AABB2D* aAABB, CollisionResults &aCollision);

bool ContainPointAABB2D(const Vector2& aPoint, const AABB2D* aAABB);

bool IntersectSegmentSegment2D(const Vector2& aPoint11, const Vector2& aPoint12, const Vector2& aPoint21, const Vector2& aPoint22, CollisionResults &aCollision);

bool IntersectSegmentAABB2D(const Vector2& aStart, const Vector2& aEnd, const AABB2D* aAABB, CollisionResults &aCollision);

bool IntersectSegmentSphere2D(const Vector2& aStart, const Vector2& aEnd, Vector2 aCenter, int64 aRadius, CollisionResults &aCollision);

bool IntersectMovingSphereAABB2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius, const AABB2D* aAABB, CollisionResults &aCollision);

bool IntersectMovingSphereSphere2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius, const Cylinder* aCylinder, CollisionResults &aCollision);

bool IntersectMovingSphereOBB2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius, OBB* aOBB, CollisionResults &aCollision);

int64 DetectSideLinePoint(const Vector2& aStart, const Vector2& aEnd, const Vector2& aPoint);

bool IntersectSectorSphere2D(const Vector2& aSCenter, const Vector2& aDir, const int64 aHalfTheta, int64 aThetaBase,
    const int64 aSRadius, const Vector2& aCenter, int64 aRadius, CollisionResults &aCollision);

bool IntersectOBBSphere2D(const Vector2& aCenter, int64 aRadius, OBB* aOBB, CollisionResults &aCollision);

bool IntersectOBBOBBoneside(OBB* aOBB1, OBB* aOBB2);

bool IntersectOBBOBB2D(OBB* aOBB1, OBB* aOBB2);

bool IntersectOBBOBBwithCollisionPointOneside(OBB* aOBB1, OBB* aOBB2, CollisionResults &aCollision, bool isSecond);

bool IntersectOBBOBB2D(OBB* aOBB1, OBB* aOBB2, CollisionResults &aCollision);

bool IntersectRingSphere2D(const Vector2& aCenter, int64 aRadius, const Vector2& aRingCenter, int64 aRadiusMin, int64 aRadiusMax);

bool IntersectRingSphere2D(const Vector2& aCenter, int64 aRadius, const Vector2& aRingCenter, int64 aRadiusMin, int64 aRadiusMax, CollisionResults &aCollision);

bool IntersectPointSphere2D(const Vector2& aCenter, int64 aRadius, const Vector2& aPoint);

bool gjk(const Vector2 aVertices1[], size_t aCount1, const Vector2 aVertices2[], size_t aCount2);