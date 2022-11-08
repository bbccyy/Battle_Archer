/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author tanhuaping
* @date $Date$
* @version $Revision$
* @brief
*
**/

#pragma once
#include <stdlib.h>
#include <string>
#include "Framework/IntMath.h"
#include "Log/Log.h"
using namespace std;


class Vector2
{
public:
    int64 x, z;

    Vector2(int64 aX = 0, int64 aZ = 0) { x = aX; z = aZ; }
    ~Vector2() {}

    void Set(int64 aX, int64 aZ) { x = aX; z = aZ; }
    void Set(const Vector2& aOther) { x = aOther.x; z = aOther.z; }

    int64& operator[](int64 i) 
    { 
        if (i == 0)
            return x;
        else if (i == 1)
            return z;
        else
            throw "Invalid Vector2 Index";
    }
    const int64& operator[](int64 i) const 
    { 
        if (i == 0)
            return x;
        else if (i == 1)
            return z;
        else
            throw "Invalid Vector2 Index";
    }


    bool operator == (const Vector2& aOther) const 
    { 
        return x == aOther.x && z == aOther.z; 
    }
    bool operator != (const Vector2& aOther) const 
    { 
        return x != aOther.x || z != aOther.z; 
    }

    Vector2& operator += (const Vector2& aOther) 
    { 
        x += aOther.x; 
        z += aOther.z; 
        return *this; 
    }
    Vector2& operator -= (const Vector2& aOther) 
    { 
        x -= aOther.x;
        z -= aOther.z; 
        return *this; 
    }
    Vector2& operator *= (int64 aScale) 
    { 
        x *= aScale; 
        z *= aScale; 
        return *this; 
    }
    Vector2& operator /= (int64 aScale) 
    { 
        if (aScale == 0) 
        {
            throw "Numerator Is 0"; 
        }
        x /= aScale;
        z /= aScale; 
		return *this;
    }

    Vector2& Scale(const Vector2& aOther) 
    { 
        x *= aOther.x; 
        z *= aOther.z; 
        return *this; 
    }
    
    int64 Magnitude() const
    {
        return Sqrt(Dot(*this, *this));
    }

    int64 Magnitude2() const
    {
        return Dot(*this, *this);
    }

    void ScaleToLen(int64 aLen)
    {
        int64 magn = Sqrt(Dot(*this, *this));
		if (magn == 0)
		{
			LOG_DEBUG("vector is zero. cant ScaleToLen. len:%d", aLen);
			return;
		}
        x = x * aLen / magn; 
        z = z * aLen / magn; 
    }

    /*string ToString() const
    {
        char buff[64];
        snprintf(buff, 64, "x:%lld z:%lld", x, z);
        return buff;
    }*/

    static Vector2 Scale(const Vector2& aV1, const Vector2& aV2)
    {
        return Vector2(aV1.x * aV2.x, aV1.z * aV2.z);
    }

    static int64 Dot(const Vector2& aV1, const Vector2& aV2)
    {
        return aV1.x * aV2.x + aV1.z * aV2.z;
    }

    static int64 Cross(const Vector2& aV1, const Vector2& aV2)
    {
        return aV1.x * aV2.z - aV1.z * aV2.x;
    }

	static Vector2 Perpendicular(const Vector2& aV1)
	{
		return Vector2(aV1.z, -aV1.x);
	}

	static Vector2 TripleProduct(const Vector2& aVa, const Vector2& aVb, const Vector2& aVc)
	{
		// Triple product expansion is used to calculate perpendicular normal vectors 
		// which kinda 'prefer' pointing towards the Origin in Minkowski space
		Vector2 r;

		int64 ac = Dot(aVa, aVc);
		int64 bc = Dot(aVb, aVc);

		// then perform b * a.dot(c) - a * b.dot(c)
		r.x = aVb.x * ac - aVa.x * bc;
		r.z = aVb.z * ac - aVa.z * bc;
		return r;
	}

	static Vector2 AveragePoint(const Vector2 aVertices[], size_t count)
	{
		//used to roughly compute average center of given polygon
		//it's ok as initial direction of simplex search in GJK
		Vector2 avg = Vector2(0, 0);
		for (size_t i = 0; i < count; i++)
		{
			avg.x += aVertices[i].x;
			avg.z += aVertices[i].z;
		}
		avg.x /= count;
		avg.z /= count;
		return avg;
	}

	static Vector2 MinkowskiSub(const Vector2& aV1, const Vector2& aV2)
	{
		return Vector2(aV1.x - aV2.x, aV1.z - aV2.z);
	}

	Vector2& Negate()
	{
		x = -x;
		z = -z;
		return *this;
	}

};




class Vector3
{
public:
    int64 x, z, y;
    Vector3(int64 aX = 0, int64 aY = 0, int64 aZ = 0) { x = aX; y = aY; z = aZ; }
    //explicit Vector3(const int64* aArray) { x = aArray[0]; y = aArray[1]; z = aArray[2]; }

    ~Vector3() {}


    void Set(int64 aX, int64 aY, int64 aZ) { x = aX; y = aY; z = aZ; }
    void Set(const Vector3& aOther) { x = aOther.x; y = aOther.y; z = aOther.z; }

    bool operator == (const Vector3& aOther) const 
    { 
        return x == aOther.x && y == aOther.y && z == aOther.z; 
    }
    bool operator != (const Vector3& aOther) const 
    { 
        return x != aOther.x || y != aOther.y || z != aOther.z; 
    }

    Vector3& operator += (const Vector3& aOther) 
    { 
        x += aOther.x; 
        y += aOther.y; 
        z += aOther.z; 
        return *this; 
    }
    Vector3& operator -= (const Vector3& aOther) 
    { 
        x -= aOther.x; 
        y -= aOther.y; 
        z -= aOther.z; 
        return *this; 
    }
    Vector3& operator *= (int64 aScale) 
    { 
        x *= aScale; 
        y *= aScale; 
        z *= aScale; 
        return *this; 
    }
    Vector3& operator /= (int64 aScale) 
    { 
        if (aScale == 0) 
        {
            throw "Numerator Is 0"; 
        }
        x /= aScale; 
        y /= aScale; 
        z /= aScale; 
        return *this;
    }

    Vector3& Scale(const Vector3& aOther) 
    { 
        x *= aOther.x; 
        y *= aOther.y; 
        z *= aOther.z; 
        return *this; 
    }
    
    int64 Magnitude() const
    {
        return Sqrt(Dot(*this, *this));
    }

    int64 Magnitude2() const
    {
        return Dot(*this, *this);
    }

    void ScaleToLen(int64 aLen)
    {
        int64 magn = Sqrt(Dot(*this, *this));
		if (magn == 0)
		{
			LOG_DEBUG("vector is zero. cant ScaleToLen. len:%d", aLen);			
			return;
		}
        x = x * aLen / magn; 
        y = y * aLen / magn; 
        z = z * aLen / magn; 
    }

    /*string ToString() const
    {
        char buff[128];
        snprintf(buff, 128, "x:%lld z:%lld y:%lld", x, z, y);
        return buff;
    }*/


	static Vector3 RedirectTo(const Vector3& aV, int aPosIndex, int aTotalNum)
	{
		Vector3 delt;
		int64 angle = aPosIndex * (360 * DENOM / aTotalNum);
		int64 cos = CosineInt(angle, DENOM, DENOM);
		int64 sin = CosineInt(90 * DENOM - angle, DENOM, DENOM);
		delt.x = (aV.x * cos - aV.z * sin) / DENOM;
		delt.y = aV.y;
		delt.z = (aV.x * sin + aV.z * cos) / DENOM;
		return delt;
	}

    static Vector3 Scale(const Vector3& aV1, const Vector3& aV2)
    {
        return Vector3(aV1.x * aV2.x, aV1.y * aV2.y, aV1.z * aV2.z);
    }

    static Vector3 Cross(const Vector3& aV1, const Vector3& aV2)
    {
        return Vector3(
            aV1.y * aV2.z - aV1.z * aV2.y,
            aV1.z * aV2.x - aV1.x * aV2.z,
            aV1.x * aV2.y - aV1.y * aV2.x);
    }

    static int64 Dot(const Vector3& aV1, const Vector3& aV2)
    {
        return aV1.x * aV2.x + aV1.y * aV2.y + aV1.z * aV2.z;
    }

    static int64 Dist(const Vector3& aV1, const Vector3& aV2)
    {
        int64 dist2 = (aV1.x - aV2.x)*(aV1.x - aV2.x) + (aV1.y - aV2.y)*(aV1.y - aV2.y) + (aV1.z - aV2.z)*(aV1.z - aV2.z);
        return Sqrt(dist2);
    }
    static int64 Dist2(const Vector3& aV1, const Vector3& aV2)
    {
        int64 dist2 = (aV1.x - aV2.x)*(aV1.x - aV2.x) + (aV1.y - aV2.y)*(aV1.y - aV2.y) + (aV1.z - aV2.z)*(aV1.z - aV2.z);
        return dist2;
    }


    static const Vector3	ZERO;
    static const Vector3	ONE;
};

inline Vector3 operator/(const Vector3& aV, const int64 aScale)
{
    Vector3 temp(aV); 
    temp /= aScale; 
    return temp;
}

inline Vector3 operator+(const Vector3& aV1, const Vector3& aV2)
{
    return Vector3(aV1.x + aV2.x, aV1.y + aV2.y, aV1.z + aV2.z);
}

inline Vector3 operator-(const Vector3& aV1, const Vector3& aV2)
{
    return Vector3(aV1.x - aV2.x, aV1.y - aV2.y, aV1.z - aV2.z);
}

inline Vector3 operator*(const Vector3& aV, const int64 aScale)
{
    return Vector3(aV.x * aScale, aV.y * aScale, aV.z * aScale);
}

inline Vector3 operator*(const int64 aScale, const Vector3& aV)
{
    return Vector3(aV.x * aScale, aV.y * aScale, aV.z * aScale);
}

inline Vector2 operator+(const Vector2& aV1, const Vector2& aV2)
{
	return Vector2(aV1.x + aV2.x, aV1.z + aV2.z);
}

inline Vector2 operator-(const Vector2& aV1, const Vector2& aV2)
{
	return Vector2(aV1.x - aV2.x, aV1.z - aV2.z);
}

inline Vector2 operator*(const Vector2& aV, const int64 aScale)
{
	return Vector2(aV.x * aScale, aV.z * aScale);
}

inline Vector2 operator*(const int64 aScale, const Vector2& aV)
{
	return Vector2(aV.x * aScale, aV.z * aScale);
}