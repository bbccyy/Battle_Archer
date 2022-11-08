/**********************************************************************************************************************
 *
 * Copyright (c) 2010 babeltime.com, Inc. All Rights Reserved
 * $Id$
 *
 **********************************************************************************************************************/
 
/**
 * @file $HeadURL$
 * @author $Author$
 * @date $Date$
 * @version $Revision$
 * @brief
 *
 **/

typedef unsigned char       uint8;
typedef unsigned int        uint32;

typedef char       int8;
typedef int        int32;
typedef long long  int64;


//位移从配置单位(厘米)转换成运算单位(微米)
#define CONF_POS_CONVERT(x) (int(x)*10000)

//时间从配置单位(毫秒)转换成运算单位(毫秒)
#define CONF_TIME_CONVERT(x) int(x)

//速度从配置单位(厘米/秒)转换成运算单位(微米/毫秒)
#define CONF_VEL_CONVERT(x) (int(x)*10)

//加速度从配置单位(厘米/秒^2)转换成运算单位(微米/秒^2)
#define CONF_ACC_CONVERT_SEC(x) (int(x)*10000)

//加速度导数从配置单位(厘米/秒^3)转换成运算单位(微米/秒^3)
#define CONF_ACCD_CONVERT_SEC(x) (int(x)*10000)

#define MS_OF_SEC 1000
#define MS_OF_SEC2 1000000
#define MS_OF_SEC3 1000000000


