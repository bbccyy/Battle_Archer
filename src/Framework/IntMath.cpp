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

#include "IntMath.h"
#include <cmath>
#include <cstdlib>
#include "Log/Log.h"

 //int64 Sqrt(int64 x)
 //{
 //    return sqrt(x);
 //}

int64 Min(int64 a, int64 b)
{
	if (a < b) return a;
	return b;
}

int64 Max(int64 a, int64 b)
{
	if (a > b) return a;
	return b;
}

int64 Abs(int64 x)
{
	if (x > 0) return x;
	return -x;
}

int64 SaveMod(int64 x, int64 y)
{
    if (x > 0)
    {
        if (y > 0)
        {
            return x % y;
        }
        else
        {
            return -(x % (-y));
        }
    }
    else
    {
        if (y > 0)
        {
            return -((-x) % y);
        }
        else
        {
            return ((-x) % (-y));
        }
    }
}

int64 Clamp(int64 a, int64 b, int64 c)
{
	if (a < b) return b;
	else if (a > c) return c;
	return a;
}

//牛顿方法求解的整数实现
int64 Sqrt(int64 x)  //不要丢负数进去
{    	
    if(x < 0)
    {
        LOG_FATAL("invalid param for sqrt:%ld", x);
        return x;
    }
    bool scaleUp = x < 0xffffffful;//FIXME cpp2lua 0xffffffff -> -1
    if(scaleUp)
    {
        x *= 1000000;
    }
	int64 val = x/1000000;
	//if (val < 200) return scaleUp ? val : val * 100;
	int64 last = 0;
	while (llabs(val - last) > 200)
	{
		last = val;
		val = (last + x / last) >> 1;
	}

	return scaleUp ? val / 1000 : val;
}


//计算cosine值，并以int64(cosVal*aCosBase)的形式返回
//aAngle=角度实际值*aBase， aBase=放大因子，用来告诉函数角度放大了多少倍
//aCosBase=与返回值相关的放大因子，告诉使用者要将返回值除以多少倍以得到最终值
//详细请参考 Cordic Algorithm :）
int64 CosineInt90(int64 aAngle, int64 aBase, int64 aCosBase)  //real = angle_para / aBase
{
    int64 comBase = aCosBase;
    const static int tangent[] ={1, 2, 4, 8, 16, 32, 64, 128, 512};  //real = (comBase / tangent[i]) /comBase
    const static int  angleBase = 10;
    const static int  angle[] = { 450, 266, 140, 71, 36, 18, 9, 4, 2, 1 };  //real = angle[i] / angleBase

    int i, signal;

    int64 xCos, ySin, xTemp, yTemp, z, zNext;
    xCos = 0; ySin = 0; z = aAngle*comBase/aBase; zNext = 0;
    xTemp = 6073 * comBase / 10000;  //0.6073 * comBase
    yTemp = 0;
    signal = 1;

    for (i=0; i<9; i++) 

    {
        xCos=xTemp - signal * yTemp / tangent[i];
        ySin=yTemp + signal * xTemp / tangent[i];
        zNext = z - signal * angle[i] * comBase / angleBase;
        xTemp = xCos;
        yTemp = ySin;
        z = zNext;

        if(zNext>0)
        {
            signal = +1;
        }
        else
        {
            signal = -1; 
        }
    }

    return xCos;
}


int64 CosineInt(int64 aAngle, int64 aBase, int64 aCosBase) 
{
  //int64 realAngle = aAngle % (aBase * 360);
  int64 realAngle = SaveMod(aAngle, (aBase * 360));
  if( realAngle < 0)
  {
    realAngle = - realAngle;
  }
  if (realAngle > 180 * aBase) 
  {
    realAngle = 360 * aBase - realAngle;
  }

  if (realAngle > 90 * aBase) 
  {
    return -CosineInt90( 180 * aBase - realAngle, aBase, aCosBase);
  }
  return CosineInt90(realAngle, aBase, aCosBase);
}


//真实的sin值 * aSinValueBase == aSinValue； 真实的弧度返回值 == 返回值 / aAngleBase
//注意不要将aSinValueBase设置过大（不建议超过10^5)
int64 ArcsinIntRad(int64 aSinValue, int64 aSinValueBase, int64 aAngleBase)
{
     const static int64 localBase = 100000;  //内部的常量基
     const static int64 pi = 314159;  //π
     const static int64 a0 = 157072;  //泰勒0阶
     const static int64 a1 = -21211;  //1阶
     const static int64 a2 = 7426;    //2阶

     if (aSinValue > 0 && aSinValue <= aSinValueBase)
     {
        int64 VB2 = aSinValueBase * aSinValueBase;
        int64 SV2 = aSinValue * aSinValue;
        int64 VBSV = aSinValue * aSinValueBase;
        int64 sqrtUp = Sqrt(aSinValueBase-aSinValue);
        int64 sqrtDown = Sqrt(aSinValueBase);
        return ((VB2 * pi / 2) - (a0 * VB2 + a1 * VBSV + a2 * SV2) / sqrtDown * sqrtUp) / (localBase * VB2 / aAngleBase);
     }
     else if(aSinValue <= 0 && -aSinValue <= aSinValueBase)
     {
        aSinValue = - aSinValue;
        int64 VB2 = aSinValueBase * aSinValueBase;
        int64 SV2 = aSinValue * aSinValue;
        int64 VBSV = aSinValue * aSinValueBase;
        int64 sqrtUp = Sqrt(aSinValueBase-aSinValue);
        int64 sqrtDown = Sqrt(aSinValueBase);
        return ((a0 * VB2 + a1 * VBSV + a2 * SV2) / sqrtDown * sqrtUp - (VB2 * pi / 2)) / (localBase * VB2 / aAngleBase);
     }

     return 0;
}


int64 ArccosIntRad(int64 aCosValue, int64 aCosValueBase, int64 aAngleBase)
{
    const static int64 localBase = 100000;
    const static int64 a0 = 157072;

    int64 acos = -ArcsinIntRad(aCosValue, aCosValueBase, aCosValueBase) + a0 * aCosValueBase / localBase ;

    return acos * aAngleBase / aCosValueBase;
}


int64 ArcsinInt(int64 aSinValue, int64 aSinValueBase, int64 aAngleBase)
{
    const static int64 localBase = 100000;  //内部的常量基
    const static int64 pi = 314159;  //π

    int64 asinRad = ArcsinIntRad(aSinValue, aSinValueBase, aAngleBase);
    return asinRad * 180 * localBase / pi;
}


int64 ArccosInt(int64 aCosValue, int64 aCosValueBase, int64 aAngleBase)
{
    const static int64 localBase = 100000;
    const static int64 pi = 314159;

    int64 acosRad = ArccosIntRad(aCosValue, aCosValueBase, aAngleBase);
    return acosRad * 180 * localBase / pi;
}

//input: B, N, D -> output: B * N / D
//let B = q * D + r
//result = B * N / D = (q * D + r) * N / D = (q * N) + (r * N / D)
//where r is a relatively small number with reguards of B 
int64 IncByRate(int64 aBigNum, int64 aNumerator, int64 aDenomiator)
{
    if (aNumerator == 0) return 0;
    if (aNumerator == aDenomiator) return aBigNum;
    if (aBigNum < 10000000000 && aBigNum > -10000000000)
    {
        return aBigNum * aNumerator / aDenomiator;
    }
	int64 quotient = aBigNum / aDenomiator;
	int64 remainder = SaveMod(aBigNum, aDenomiator);
	return quotient * aNumerator + remainder * aNumerator / aDenomiator;
}

int64 BigARateB(int64 aBigA, int64 aBigB)
{
    if (aBigB > 1000000)
    {
        return aBigA / DENOM * 100 / (aBigB / DENOM);
    }
    return aBigA  * 100 / aBigB;
}