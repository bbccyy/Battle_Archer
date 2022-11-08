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

#pragma once

typedef unsigned char       uint8;
typedef unsigned int        uint32;

typedef char       int8;
typedef int        int32;
typedef long long  int64;


//位移从配置单位(厘米)转换成运算单位(微米) -> (10微米) 
#define CONF_POS_CONVERT(x) (int64((x)*1000))

//时间从配置单位(毫秒)转换成运算单位(毫秒) 
#define CONF_TIME_CONVERT(x) (int(x))

//速度从配置单位(厘米/秒)转换成运算单位(微米/毫秒)  -> (10微米/毫秒) 
#define CONF_VEL_CONVERT(x) (int(x))

//加速度从配置单位(厘米/秒^2)转换成运算单位(微米/秒^2)  -> (10微米/秒^2) 
#define CONF_ACC_CONVERT_SEC(x) (int64(x)*1000)

//加速度导数从配置单位(厘米/秒^3)转换成运算单位(微米/秒^3)  -> (10微米/秒^2) 
#define CONF_ACCD_CONVERT_SEC(x) (int64(x)*1000)


//角色编辑器中时间从配置单位(毫秒)转换成运算单位(毫秒) 
#define EDITOR_CONF_TIME_CONVERT(x) (int(x))

//角色编辑器中位移从配置单位(厘米)转换成运算单位(微米)  -> (10微米) 
#define EDITOR_CONF_POS_CONVERT(x) (int64((x)*1000))

const constexpr int64 LIMIT = 4599999999999999;

const constexpr int MS_OF_SEC = 1000;
const constexpr int64 MS_OF_SEC2 = 1000000;
const constexpr int64 MS_OF_SEC3 = 1000000000;

const constexpr int DENOM = 10000;  
const constexpr int64 DENOM_SQR = 100000000;

const constexpr int MIN_LEN = 6; //因为采用整数运算，如果ScaleToLen时的长度小于这个值会导致Vector变成zero

const constexpr int SQUAD_STD_NUMBER = 9;  //标准队伍人数 

const constexpr int FIXED_FRAME_DELTA_MS = 100;
const constexpr int FRAME_TIME_SCALE = 1000;
const constexpr int BATTLE_TIME_UPPER_LIMIT = 9000000;
const constexpr int TIMER_CLEANUP_RATIO_DENOM = 3;

const constexpr int PHYSICS_GROUP_UNIT = 0;
const constexpr int PHYSICS_GROUP_DESTRUCTABLE = 1;
const constexpr int PHYSICS_GROUP_BARRIER = 2;

const constexpr int GJK_MAX_TRY = 5;
const constexpr int MELEE_RING_MAX_SLOT = 16;
const constexpr int MELEE_RING_MAX_SIZE = 10;
const constexpr int MELEE_ATTACK_RANGE = 200000;
const constexpr int MELEE_RING_MIN_NEARBY_RANGE = 500000;

const constexpr int AIPATH_RANGE = 150000;

const constexpr int SPEED_FACTOR_UPLIMIT = 30000;
const constexpr int SPEED_FACTOR_DOWNLIMIT = -8000;
const constexpr int SPEED_FACTOR_BASE = 0;

const constexpr int MAX_USER_BORNPOINT = 0;

const constexpr int MAX_USER_INPUT_NUM = 6001;

const constexpr int TD_COLD_DOWN = 5000;
const constexpr int TD_VALID_WAVE_DELTA = 2;
const constexpr int TD_SPECIAL_ENEMY = -99999;