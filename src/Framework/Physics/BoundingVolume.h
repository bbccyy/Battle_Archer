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

#pragma once
#include "Framework/Transform.h"
#include "Framework/SharedPool.h"

/*
我们这里实现的是一个2.5D的物理系统：2D+高度。默认y轴为高度
*/


enum EBVType
{
	EBVTypeOBB,
	EBVTypeCylinder,
};


class AABB2D
{
public:
    Vector2 min;
    Vector2 max;

    /*string ToString() const
    {
        char buff[128];
        snprintf(buff, 128, "min[%s], max[%s]", min.ToString().c_str(), max.ToString().c_str() );
        return buff;
    }*/
};



class BoundingVolume : public IPoolable
{
public:
    EBVType type;

    BoundingVolume(EBVType aType):type(aType){}
    virtual ~BoundingVolume(){}
};

//永远竖直的圆柱体
class Cylinder : public BoundingVolume
{
public:
    Vector3 center;
    int64 radius;
    int64 height;

    Cylinder(): BoundingVolume(EBVTypeCylinder){}
    void Reset()
	{
		center.Set(0, 0, 0);
		radius = 0;
		height = 0;
	};
    inline void Update(const Vector3* aPos = nullptr, const int64* aRadius = nullptr, const int64* aHeight = nullptr)
    {
        if( aPos )
        {
            center.Set(*aPos);
        }
        if( aRadius )
        {
            radius = *aRadius;
        }
        if( aHeight)
        {
            height = *aHeight;
        }
    }
};

//oriented bounding box。 永远竖直，只会在x-z平面旋转的OBB。 
class OBB : public BoundingVolume
{
public:
    Vector3 center; //底座的中心点
    Vector2 halfSize;
    Vector2 front;  //认为+z轴为正前方
    Vector2 right;  //认为+x轴为右方 
    int64 height;


    OBB(): BoundingVolume(EBVTypeOBB){}
    void Reset(){};

    inline void Update(const Vector3* aPos = nullptr, const Vector2* aSize = nullptr, const Vector2* aForward = nullptr)
    {
        if( aPos )
        {
            center = *aPos;
        }
        if( aSize )
        {
            halfSize = *aSize;
        }
        if( aForward)
        {
            front = *aForward;
            right.x = front.z;
            right.z = -front.x;
        }
    }
};



