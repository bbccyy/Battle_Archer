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


#define INT64_MAX        9223372036854775807LL
#define INT64_MIN        (-9223372036854775807LL - 1)

int64 Sqrt(int64 x);
int64 CosineInt(int64 aAngle, int64 aBase, int64 aCosBase);
int64 CosineInt90(int64 aAngle, int64 aBase, int64 aCosBase);