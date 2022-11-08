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

#ifndef _Transform
#define _Transform
//#include <math.h>
#include "Math.h"

//#define INT64_MAX        9223372036854775807LL
//#define INT64_MIN        (-9223372036854775807LL - 1)

// int64 Sqrt(int64 x)
// {
//      return sqrt(x);
// }

class Vector2
{
public:
    int64 x, z;

    Vector2() : x(0),z(0) {}
    Vector2(int64 aX, int64 aZ) { x = aX; z = aZ; }
    ~Vector2() {}

    void Set(int64 aX, int64 aZ) { x = aX; z = aZ; }
    void Set(const Vector2& aV) { x = aV.x; z= aV.z; }

    int64& operator[](int64 i) 
    { 
        if (i == 0)
        {
            return x; 
        }
        else if (i == 1) 
        {
            return z; 
        }
        else {
            throw "Invalid Vector3 Index";
        }
    }
    const int64& operator[](int64 i) const 
    { 
        if (i == 0)
        {
            return x; 
        }
        else if (i == 1) 
        {
            return z; 
        }
        else {
            throw "Invalid Vector3 Index";
        }
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
    }

    Vector2& Scale(const Vector2& aOther) 
    { 
        x *= aOther.x; 
        z *= aOther.z; 
        return *this; 
    }
    
    int64 Magnitude()
    {
        return Sqrt(Dot(*this, *this));
    }

    int64 Magnitude2()
    {
        return Dot(*this, *this);
    }

    void ScaleToLen(int64 aLen)
    {
        int64 magn = Sqrt(Dot(*this, *this));
        x = x * aLen / magn; 
        z = z * aLen / magn; 
    }

    static Vector2 Scale(const Vector2& aV1, const Vector2& aV2)
    {
        return Vector2(aV1.x * aV2.x, aV1.z * aV2.z);
    }

    static int64 Dot(const Vector2& aV1, const Vector2& aV2)
    {
        return aV1.x * aV2.x + aV1.z * aV2.z;
    }
private:
    Vector2(const Vector2 &);  
    void operator=(const Vector2 &);  
};




class Vector3
{
public:
    int64 x, z, y;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(int64 aX, int64 aY, int64 aZ) { x = aX; y = aY; z = aZ; }
    //explicit Vector3(const int64* aArray) { x = aArray[0]; y = aArray[1]; z = aArray[2]; }

    ~Vector3() {}


    void Set(int64 aX, int64 aY, int64 aZ) { x = aX; y = aY; z = aZ; }
    void Set(const Vector3& aV) { x = aV.x; y = aV.y; z= aV.z; }
    //void Set(const int64* aArray) { x = aArray[0]; y = aArray[1]; z = aArray[2]; }

    int64& operator[](int64 i) 
    { 
        if (x < 0 || x > 2) 
        {
            throw "Invalid Vector3 Index";
        }
        return (&x)[i]; 
    }
    const int64& operator[](int64 i) const 
    { 
        if (x < 0 || x > 2) 
        {
            throw "Invalid Vector3 Index"; 
        }			
        return (&x)[i]; 
    }

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
    }

    Vector3& Scale(const Vector3& aOther) 
    { 
        x *= aOther.x; 
        y *= aOther.y; 
        z *= aOther.z; 
        return *this; 
    }
    
    int64 Magnitude()
    {
        return Sqrt(Dot(*this, *this));
    }

    int64 Magnitude2()
    {
        return Dot(*this, *this);
    }

    void ScaleToLen(int64 aLen)
    {
        int64 magn = Sqrt(Dot(*this, *this));
        x = x * aLen / magn; 
        y = y * aLen / magn; 
        z = z * aLen / magn; 
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


    static const Vector3	ZERO;
    static const Vector3	ONE;
private:
    Vector3(const Vector3 &);  
    void operator=(const Vector3 &);  
};

inline Vector3 operator/(const Vector3& aV, const int64 aScale)
{
    Vector3 temp(aV); 
    temp /= aScale; 
    return temp;
}

inline Vector3 operator+(const Vector3& aV1, const Vector3& aV2)
{
    return Vector3(aV1.x * aV2.x, aV1.y * aV2.y, aV1.z * aV2.z);
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

#endif