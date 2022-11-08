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

#include "Define.h"


const constexpr int64 INT64_MAX_VALUE = 9223372036854775807LL;
const constexpr int64 INT64_MIN_VALUE = -9223372036854775807LL - 1;
const constexpr int	  INT32_MIN_VALUE = -2147483647 - 1;
const constexpr int	  INT32_MAX_VALUE = 2147483647;


int64 Abs(int64 x);

int64 Sqrt(int64 x);

int64 SaveMod(int64 x, int64 y);

int64 Min(int64 a, int64 b);

int64 Max(int64 a, int64 b);

int64 Clamp(int64 a, int64 b, int64 c);

int64 CosineInt(int64 aAngle, int64 aBase, int64 aCosBase);

//int64 Arcsin(int64 aSinValue, int64 aSinValueBase, int64 aAngleBase);

int64 ArcsinInt(int64 aSinValue, int64 aSinValueBase, int64 aAngleBase);

int64 ArccosInt(int64 aCosValue, int64 aCosValueBase, int64 aAngleBase);

int64 IncByRate(int64 aBigNum, int64 aRate, int64 aDenomiator);

int64 BigARateB(int64 aBigA, int64 aBigB);