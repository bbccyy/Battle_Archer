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
#include "Transform.h"
#include <iostream>
#include <list>
using namespace std;
/*
我们这里实现的是一个2.5D的物理系统：2D+高度。默认y轴为高度
*/


enum EBVType
{
    EBVTypeCylinder,
    EBVTypeOBB,
};


class AABB2D
{
public:
    Vector2 min;
    Vector2 max;
};



class BoundingVolume
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
    void Reset(){};
};

class Sector
{
public:
	Vector2 center; //扇形所在园的园心
	Vector2 dir; //扇形圆弧面的朝向
	int64 theta;  //半角
	int64 thetaBase; // real theta = theta/thetaBase
	int64 radius;  //半径
	int sampleFreq;  //角度采样间隔度数(1,2,3,5,...)

	list<Vector2*> arc;  //从A到B点（含）的点集

	void CalculatePoint()
	{
		CleanUp();
		Vector2 right(dir.x, dir.z);
		Vector2 front(-dir.z, dir.x);
		Vector2 origFront(0, 100);
		Vector2 origRight(100, 0);
		int64 len = right.Magnitude();
		int64 origLen = 100;
		int64 tmpX = Vector2::Dot(origFront, right)/len;
		int64 tmpZ = Vector2::Dot(origFront, front)/len;
		origFront.x = tmpX;
		origFront.z = tmpZ;
		tmpX = Vector2::Dot(origRight, right)/len;
		tmpZ = Vector2::Dot(origRight, front)/len;
		origRight.x = tmpX;
		origRight.z = tmpZ;

		list<Vector2*> others;
		for(int64 ta=theta; ta >= 0; ta -= sampleFreq * thetaBase){
			if (ta == 0) {
				Vector2 *upCorner = new Vector2(radius, 0);
				arc.push_back(upCorner);
				continue;
			}
			int64 cosbase = 1000000;
			int64 cosval = CosineInt(ta, thetaBase, cosbase);
			tmpX = 0;
			tmpZ = 100;
			if (cosval * 100 / cosbase != 0) //认为小于0.01就等于0了
			{
				int64 cvp = cosval * cosval;
				tmpX = Sqrt( 10000 * cvp / (cosbase * cosbase - cvp) );
				//cout << "cosval = " << cosval << ";   tmpX = " << tmpX << endl;
				if (cosval < 0){
					tmpX = -tmpX;
				}
			}
			Vector2 *upCorner = new Vector2(tmpX, tmpZ);
			upCorner->ScaleToLen(radius);  //这是转换坐标后的一个扇形非圆心端点
			Vector2 *downCorner = new Vector2(upCorner->x, -upCorner->z);  //和另一个端点沿x轴镜像对称
			//list<Vector2*> *chain = *(arc.rbegin());
			//chain->push_back(upCorner);
			arc.push_back(upCorner);
			others.push_back(downCorner);
		}
		list<Vector2*>::reverse_iterator rit;
		list<Vector2*>::iterator it;
		for (rit = others.rbegin(); rit != others.rend(); ++rit){
			arc.push_back(*rit);
		}
		others.clear();

		for (it = arc.begin(); it != arc.end(); ++it){
			Vector2 startToEnd((*it)->x, (*it)->z);
			tmpX = Vector2::Dot(startToEnd, origRight)/origLen;
            tmpZ = Vector2::Dot(startToEnd, origFront)/origLen;
            startToEnd.x = tmpX + center.x;
            startToEnd.z = tmpZ + center.z;
            (*it)->x = startToEnd.x;
			(*it)->z = startToEnd.z;
			//cout<<startToEnd.x << " " << startToEnd.z << endl;
		}
	}

	void CleanUp()
	{
		for (list<Vector2*>::iterator iter = arc.begin(); iter != arc.end(); iter++) {
			Vector2 *cur = *iter;
			delete cur;
		}
		arc.clear();
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

	Vector2 A,B,C,D;


    OBB(): BoundingVolume(EBVTypeOBB){}
    void Reset(){};

    void Update(const Vector3* aPos, const Vector2* aSize, const Vector2* aFront)
    {
        if( aPos )
        {
            center = *aPos;
        }
    }

	void CalculatePoint()
	{
		Vector2 ct(center.x, center.z);
		Vector2 rd = right;
		rd.ScaleToLen(halfSize.x);
		Vector2 fd = front;
		fd.ScaleToLen(halfSize.z);
		A = ct;
		A += rd;
		A += fd;
		B = ct;
		B += rd;
		B -= fd;
		C = ct;
		C -= rd;
		C -= fd;
		D = ct;
		D -= rd;
		D += fd;
	}
};



