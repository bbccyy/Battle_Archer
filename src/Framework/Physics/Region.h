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

#include "CollisionDetection.h"


enum ERegion
{
    ERegionCircle,
    ERegionSector,
    ERegionAnnulus,
    ERegionRectangle,
};

class Region
{
public:
    ERegion type;

    Region(ERegion aType):type(aType),selfSize(0){}
    virtual ~Region(){}
	int64 selfSize;
};


class RegionCircle : public Region
{
public:
    RegionCircle(): Region(ERegionCircle){}
    virtual ~RegionCircle(){}
    void Reset(){}

    Vector2 center;
    int64 radius; 
};



class RegionSector : public Region
{
public:
    RegionSector(): Region(ERegionSector){}
    virtual ~RegionSector(){}
    void Reset(){}

    Vector2 center;
    int64 radius;  
    int64 angle;
    Vector2 forward;
};

class RegionAnnulus : public Region
{
public:
    RegionAnnulus(): Region(ERegionAnnulus){}
    virtual ~RegionAnnulus(){}
    void Reset(){}

    Vector2 center;
    int64 radius1; 
    int64 radius2; 
};


class RegionRectangle : public Region
{
public:
    RegionRectangle(): Region(ERegionRectangle){}
    virtual ~RegionRectangle(){}
    void Reset(){}

    Vector2 center;
    Vector2 halfSize;
    Vector2 forward;  //认为+z轴为正前方
};



bool CollisionDetectionRegionWithBV(Region* aRegion, BoundingVolume* aBv);