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


#define AVATAR_CONF_KEY "Avatarname"

const constexpr int CHAIN_SKILL_NUM = 5;

enum class EDirection
{
    Forward,
    Backward,
    Left,
    Right
};

enum ESkillReplaceType
{
	ESkillReplaceLessThan = 1,   //参考目标与自己距离小于给定值时，替换技能   1
	ESkillReplaceGreatThan,		 //~大于给定值时，~  2
	ESkillReplaceHasBuff,		 //参考目标身上有给定buff时，替换技能  3
	ESkillReplaceNotHasBuff,	 //~没有给定buff时，~   4
	ESkillReplaceIsLastTarget    //参考目标时目标阵营最后一个武将时，替换技能   5
};


//技能主类型
enum ESkillMainType
{
    ESkillMainTypeMeleeSinglePositive,      //近战单体增益 
    ESkillMainTypeMeleeSingleNegative,      //近战单体减益 
    ESkillMainTypeMeleeSingleNeutral,       //近战单体中性 

    ESkillMainTypeMeleeCrowdPositive,       //近战多目标增益 
    ESkillMainTypeMeleeCrowdNegative,       //近战多目标减益 
    ESkillMainTypeMeleeCrowdNeutral,        //近战多目标中性 

    ESkillMainTypeRangedSinglePositive,      //远程单体增益 
    ESkillMainTypeRangedSingleNegative,      //远程单体减益 
    ESkillMainTypeRangedSingleNeutral,       //远程单体中性 

    ESkillMainTypeRangedCrowdPositive,       //远程多目标增益 
    ESkillMainTypeRangedCrowdNegative,       //远程多目标减益 
    ESkillMainTypeRangedCrowdNeutral,        //远程多目标中性 

    ESkillMainType_Count
};


//技能子类型 
enum ESkillSubType
{
    ESkillSubTypeDamage,                //伤害 
    ESkillSubTypeHeal,                  //治疗 
    ESkillSubTypeSummon,                //召唤 
    ESkillSubTypeRevive,                //复活 
    ESkillSubTypeMove,                  //位移 
    ESkillSubTypeSuckRage,              //吸怒 
    ESkillSubTypeAddRage,               //回怒 
    ESkillSubTypeSuckBlood,             //吸血 
    ESkillSubTypeGrab,                  //投技 
	ESkillSubTypeBarrier,               //召唤障碍物
	ESkillSubTypeDamageBeheaded,		//伤害（斩杀） 
};


enum class CheckResult
{
	Pass = 0,			//no reason(aka pass) 
	SurpassCountNum,	//out weight count num
	CD,					//still in count down
	NoSkill,			//no skill
	NoNormalSkill,		//no normal skill
	Porbability,		//fail to pass random check 
	NoTarget,			//not found target 
};


//技能释放方式
enum class ECastType    
{
	//非条件触发类型
	None = -1,
	NormalAtk = 0,       //普攻 
	NormalAtkSpecial,    //小技能普攻 
	RandomNormalAtk,     //概率触发 
	Unparalleled,        //无双技 
	Rage,                //大招 
	WithBuff,			 //由buff主动释放（不是触发技能） 

	//条件触发类型 
	EventTrigger,

	_Count

};

enum class ETriggerRelation   //Relation Param
{
	Self = 0,			//自己 
	Friend = 1,			//己方 
	Enemy,				//敌方 
	Any,				//全部 
    FriendHeroOnly,     //己方武将
    EnemyHeroOnly,      //敌方武将

	_Count
};

enum class ETriggerMajor   
{
	None = -1,
	Enter = 0,			 //开场施放 
	Born,                //出生释放 
	Death,               //死亡释放 
	Revive,              //复活释放 
	AfterDmg,            //受伤后释放 发送伤害承受者的Id 
	AfterHeal,           //受治疗后施放 
	AfterDodge,          //闪避后施放 
	AfterImmune,         //免疫后施放 
	AfterParry,          //格挡后施放 
	AfterResist,         //抵抗后施放 
	BuffNumber,          //buff层数触发 
	WithSkill,           //技能触发 
	BeforeDeath,          //濒死触发 
	WhenApplyDamage,	  //当造成伤害后触发 发送伤害制造者的Id 
	AfterCritical,        //暴击后触发 
	AfterDizzy,			  //眩晕后触发 
	WhenMatchRecordValue, //满足记录数值阈值后 
	AfterBeCritical,      //被暴击后触发 
	AfterKill,			  //击杀后触发 
	AfterInterrupt,       //打断后触发 
	AfterShield,		  //上盾后触发 
	AfterDispelEnemyBuff, //驱散敌方Buff后触发 
	AfterHitHandlerMove,  //技能位移结束后触发 
	AfterHitHandlerMoveAnyWay,  //技能位移结束后(正常或被打断)触发 
	TDAfterOutOfZone,			//当前不处于根据地时触发 
	TDAfterNotFoundRefTarget,	//当在根据地内找不到目标一段时间后触发 
	AfterBuffSubtype,			//当buff子类型触发后 
	AfterApplyUnlimitedShield,  //无上限护盾吸收伤害过后 
	AfterSkillReflected,		//技能反弹后触发 
	AfterRageSkill,				//大招后触发 
	SummonWithRefTarget,		//召唤非dummy后触发(附带被召唤者) 
	ReviveWithRefTarget,		//复活后触发(附带被复活者) 
	AfterSkillWithAnim,			//非普攻非概率普攻非大招但是有动作的主技能释放后触发 
	AfterRageSkillWithRefTarget,//大招后触发(附带被召唤者) 
    WhenFirstApplyDamage,	    //当第一次伤害后触发 
	OnCheckCountryHeroNumber,	//己方某国武将数量触发(仅开场触发一次) 
	OnCHeckCountryHeroNumberRuntime,	//己方某国武将数量触发(武将数量发生变化时触发) 

    AfterSubRage,               //减怒后触发 

	_Count

};

enum class ETriggerCommonSub
{
	None = 0 
};

enum class ETriggerDeathSub
{
	None = 0,
	UseKillerAsRefTarget = 1,	//使用击杀者作为参考目标 
	UseAncestorAsRefTarget = 2, //使用始祖释放者作为参考目标 
	OnlySkillOwnerLeft = 3,     //场上一方只有技能拥有者存活 
    NoHeroLeft = 4,             //场上没有己方武将存活 

	_Count
};

enum class ETriggerWithSkillSub
{
	None = 0,
	Normal = 1,			//普攻 
	NonNormal,			//非普攻 
	Any,				//全部 
	SkillList,          //技能队列 

	_Count
};

enum class ETriggerAfterParrySub
{
	None = 0,
	Melee = 1,			//近战 
	Range,			    //远程 
	Any,				//全部 
	Skill,				//某技能 
	SkillWithRef,		//某技能且附带参考目标 

	_Count
};

enum class ETriggerAfterDodgeSub
{
	None = 0,
	Any = 1,			//全部 
	Skill,				//某技能 
	SkillWithRef,		//某技能且附带参考目标 

	_Count
};

enum class ETriggerAfterDmgSub
{
	None = 0,
	Melee = 1,			//近战		1 
	Range,			    //远程		2 
	Any,				//全部		3 
	Skill,				//某技能	4
	Phy,				//物理攻击	5
	Mag,				//法术		6
	RageSkill,			//大招伤害	7

	_Count
};


enum ESearchRefTargetMethod
{
    ESearchRefTargetMethodRandEnemy,             //随机敌方单位 
    ESearchRefTargetMethodRandFriend,            //随机己方单位 
    ESearchRefTargetMethodAllEnemy,              //敌方全体 
    ESearchRefTargetMethodAllFriend,             //己方全体 
    ESearchRefTargetMethodSelf,                  //自己 
    ESearchRefTargetMethodNearestEnemy,          //离自己最近的敌方 
    ESearchRefTargetMethodNearestFriend,         //离自己最近的友方 
    ESearchRefTargetMethodFarthestEnemy,         //离自己最远的敌方 
    ESearchRefTargetMethodFarthestFriend,        //离自己最远的友方 
    ESearchRefTargetMethodRangeRandEnemy,        //技能范围内任意敌方 
    ESearchRefTargetMethodRangeRandFriend,       //技能范围内任意友方 
    ESearchRefTargetMethodRangeAllEnemy,         //技能范围内所有敌方 
    ESearchRefTargetMethodRangeAllFriend,        //技能范围内所有友方 
    ESearchRefTargetMethodEnemyMinHp,            //敌方血量最少 
    ESearchRefTargetMethodEnemyMaxHp,            //敌方血量最多 
    ESearchRefTargetMethodEnemyMaxLostHp,        //敌方失血最多 
    ESearchRefTargetMethodEnemyMinLostHp,        //敌方失血最少 
    ESearchRefTargetMethodEnemyMinRage,          //敌方怒气最少 
    ESearchRefTargetMethodEnemyMaxRage,          //敌方怒气最多 
    ESearchRefTargetMethodFriendMinHp,           //己方血量最少 
    ESearchRefTargetMethodFriendMaxHp,           //己方血量最多 
    ESearchRefTargetMethodFriendMaxLostHp,       //己方失血最多 
    ESearchRefTargetMethodFriendMinLostHp,       //己方失血最少 
    ESearchRefTargetMethodFriendMinRage,         //己方怒气最少 
    ESearchRefTargetMethodFriendMaxRage,         //己方怒气最多 
    ESearchRefTargetMethodRandFriendDead,        //己方死亡目标 
    ESearchRefTargetMethodRandEnemyDead,         //敌方死亡目标 
    ESearchRefTargetMethodRandDead,              //任意死亡目标 
    ESearchRefTargetMethodRandEnemySummon,       //随机敌方召唤单位 
    ESearchRefTargetMethodAllEnemySummon,        //所有敌方召唤单位 
    ESearchRefTargetMethodNearestEnemySummon,    //离自己最近敌方召唤单位 
    ESearchRefTargetMethodFarthestEnemySummon,   //离自己最远敌方召唤单位 
    ESearchRefTargetMethodRangeRandEnemySummon,  //技能范围内任意敌方召唤单位 
    ESearchRefTargetMethodRangeAllEnemySummon,   //技能范围内全部敌方召唤单位 
    ESearchRefTargetMethodEnemySummonMinHp,      //敌方血量最少召唤单位 
    ESearchRefTargetMethodEnemySummonMaxHp,      //敌方血量最多召唤单位 
    ESearchRefTargetMethodEnemySummonMinLostHp,  //敌方失血最少召唤单位 
    ESearchRefTargetMethodEnemySummonMaxLostHp,  //敌方失血最多召唤单位 
    ESearchRefTargetMethodEnemySummonMaxRage,    //敌方怒气最多召唤单位 
    ESearchRefTargetMethodEnemySummonMinRage,    //敌方怒气最少召唤单位 
    ESearchRefTargetMethodFriendMaxPhysicalAtk,  //己方物攻最高 
    ESearchRefTargetMethodFriendMaxMagicAtk,     //己方法攻最高 
    ESearchRefTargetMethodFriendMaxPhysicalDef,  //己方物防最高 
    ESearchRefTargetMethodFriendMaxMagicDef,     //己方法防最高 
    ESearchRefTargetMethodFriendMinPhysicalAtk,  //己方物攻最低 
    ESearchRefTargetMethodFriendMinMagicAtk,     //己方法攻最低 
    ESearchRefTargetMethodFriendMinPhysicalDef,  //己方物防最低 
    ESearchRefTargetMethodFriendMinMagicDef,     //己方法防最低 
    ESearchRefTargetMethodEnemyMaxPhysicalAtk,   //敌方物攻最高 
    ESearchRefTargetMethodEnemyMaxMagicAtk,      //敌方法攻最高 
    ESearchRefTargetMethodEnemyMaxPhysicalDef,   //敌方物防最高 
    ESearchRefTargetMethodEnemyMaxMagicDef,      //敌方法防最高 
    ESearchRefTargetMethodEnemyMinPhysicalAtk,   //敌方物攻最低 
    ESearchRefTargetMethodEnemyMinMagicAtk,      //敌方法攻最低 
    ESearchRefTargetMethodEnemyMinPhysicalDef,   //敌方物防最低 
    ESearchRefTargetMethodEnemyMinMagicDef,      //敌方法防最低 
    ESearchRefTargetMethodForwardFixPos,         //自己身前一定距离位置 
    ESearchRefTargetMethodFixPos,                //场景坐标点 
    ESearchRefTargetMethodLastNormalSkillTarget, //上次普攻的参考目标 
    ESearchRefTargetMethodEnemyBuff,             //带特定buff的敌方目标 
    ESearchRefTargetMethodFriendBuff,            //带特定buff的己方目标 
	ESearchRefTargetMethodRandFriendHeroDead,    //己方死亡英雄 
	ESearchRefTargetMethodRandFriendSummonDead,  //己方死亡召唤物 
	ESearchRefTargetMethodRandEnemyHeroDead,     //敌方死亡英雄 
	ESearchRefTargetMethodRandEnemySummonDead,   //敌方死亡召唤物 
	ESearchRefTargetMethodRandHeroDead,				//任意死亡英雄 
	ESearchRefTargetMethodRandSummonDead,			//任意死亡召唤物 
	ESearchRefTargetMethodAllFriendSummon,			//所有己方召唤 
	ESearchRefTargetMethodFriendScenePos,			//己方场景点 
	ESearchRefTargetMethodEnemyScenePos,			//敌方场景点 
	ESearchRefTargetMethodChoosedAtTriggerTime,		//技能触发时选中的武将 
	ESearchRefTargetMethodAnyFriendButSummon,		//随机己方英雄(召唤物除外) 
	ESearchRefTargetMethodCurrentBaseCenter,		//TD:当前根据地中心  
	ESearchRefTargetMethodNearestFortress,  		//TD:最近的要塞点 
	ESearchRefTargetMethodBeanOwner,		  		//TD:自身持有豆子的拥有者 
	ESearchRefTargetMethodBornCenter,		  		//TD:自身出生点中心  
	ESearchRefTargetMethodMostEffTarget,			//可产生最多生效目标的参考目标(矩形) 
	ESearchRefTargetMethodFriendMaxAtk,				//攻击最高的己方角色  
	ESearchRefTargetMethodEnemyMaxAtk,				//攻击最高的敌方角色  
	ESearchRefTargetMethodMostEffTargetCircle,		//可产生最多生效目标的参考目标(圆形) 
	ESearchRefTargetMethodMaxAtkNotOnly,			//敌方攻击最高且非唯一 
	ESearchRefTargetMethodEnemyProfessionalConbime,	//敌方某些职业组合 
	ESearchRefTargetMethodFriendProfessionalConbime,//己方某些职业组合 
	ESearchRefTargetMethodBornPointByRow,			//和自己同行(出生点) 
	ESearchRefTargetMethodBornPointByCol,			//和自己同列(出生点) 
	ESearchRefTargetMethodBornPointByNeighbour,		//和自己相邻(出生点) 

};

enum ESearchEffTargetMethod
{
    ESearchEffTargetMethodRandEnemy,            //随机敌方单位 
    ESearchEffTargetMethodRandFriend,           //随机己方单位 
    ESearchEffTargetMethodAllEnemy,             //敌方全体 
    ESearchEffTargetMethodAllFriend,            //己方全体 
    ESearchEffTargetMethodNone,                 //无目标_通常应用于全屏技能 
    ESearchEffTargetMethodSelf,                 //自己 
    ESearchEffTargetMethodNearestEnemy,         //离自己最近的敌方 
    ESearchEffTargetMethodNearestFriend,        //离自己最近的友方 
    ESearchEffTargetMethodFarthestEnemy,        //离自己最远的敌方 
    ESearchEffTargetMethodFarthestFriend,       //离自己最远的友方 
    ESearchEffTargetMethodEnemyBuff,            //带特定buff的敌方目标 
    ESearchEffTargetMethodFriendBuff,           //带特定buff的己方目标 
    ESearchEffTargetMethodEnemyMinHp,           //敌方血量最少 
    ESearchEffTargetMethodEnemyMaxHp,           //敌方血量最多 
    ESearchEffTargetMethodEnemyMaxLostHp,       //敌方失血最多 
    ESearchEffTargetMethodEnemyMinLostHp,       //敌方失血最少 
    ESearchEffTargetMethodEnemyMinRage,         //敌方怒气最少 
    ESearchEffTargetMethodEnemyMaxRage,         //敌方怒气最多 
    ESearchEffTargetMethodFriendMinHp,          //己方血量最少 
    ESearchEffTargetMethodFriendMaxHp,          //己方血量最多 
    ESearchEffTargetMethodFriendMaxLostHp,      //己方失血最多 
    ESearchEffTargetMethodFriendMinLostHp,      //己方失血最少 
    ESearchEffTargetMethodFriendMinRage,        //己方怒气最少 
    ESearchEffTargetMethodFriendMaxRage,        //己方怒气最多 
    ESearchEffTargetMethodRandFriendDead,       //己方死亡目标 
    ESearchEffTargetMethodRandEnemyDead,        //敌方死亡目标 
    ESearchEffTargetMethodRandDead,             //任意死亡目标 
    ESearchEffTargetMethodRandEnemySummon,      //随机敌方召唤单位 
    ESearchEffTargetMethodAllEnemySummon,       //所有敌方召唤单位 
    ESearchEffTargetMethodNearestEnemySummon,   //离自己最近敌方召唤单位 
    ESearchEffTargetMethodFarthestEnemySummon,  //离自己最远敌方召唤单位 
    ESearchEffTargetMethodEnemySummonMinHp,     //敌方血量最少召唤单位 
    ESearchEffTargetMethodEnemySummonMaxHp,     //敌方血量最多召唤单位 
    ESearchEffTargetMethodEnemySummonMinLostHp, //敌方失血最少召唤单位 
    ESearchEffTargetMethodEnemySummonMaxLostHp, //敌方失血最多召唤单位 
    ESearchEffTargetMethodEnemySummonMaxRage,   //敌方怒气最多召唤单位 
    ESearchEffTargetMethodEnemySummonMinRage,   //敌方怒气最少召唤单位 
    ESearchEffTargetMethodFriendMaxPhysicalAtk, //己方物攻最高 
    ESearchEffTargetMethodFriendMaxMagicAtk,    //己方法攻最高 
    ESearchEffTargetMethodFriendMaxPhysicalDef, //己方物防最高 
    ESearchEffTargetMethodFriendMaxMagicDef,    //己方法防最高 
    ESearchEffTargetMethodFriendMinPhysicalAtk, //己方物攻最低 
    ESearchEffTargetMethodFriendMinMagicAtk,    //己方法攻最低 
    ESearchEffTargetMethodFriendMinPhysicalDef, //己方物防最低 
    ESearchEffTargetMethodFriendMinMagicDef,    //己方法防最低 
    ESearchEffTargetMethodEnemyMaxPhysicalAtk,  //敌方物攻最高 
    ESearchEffTargetMethodEnemyMaxMagicAtk,     //敌方法攻最高 
    ESearchEffTargetMethodEnemyMaxPhysicalDef,  //敌方物防最高 
    ESearchEffTargetMethodEnemyMaxMagicDef,     //敌方法防最高 
    ESearchEffTargetMethodEnemyMinPhysicalAtk,  //敌方物攻最低 
    ESearchEffTargetMethodEnemyMinMagicAtk,     //敌方法攻最低 
    ESearchEffTargetMethodEnemyMinPhysicalDef,  //敌方物防最低 
    ESearchEffTargetMethodEnemyMinMagicDef,     //敌方法防最低 
	ESearchEffTargetMethodRandFriendHeroDead,    //己方死亡英雄 
	ESearchEffTargetMethodRandFriendSummonDead,  //己方死亡召唤物 
	ESearchEffTargetMethodRandEnemyHeroDead,     //敌方死亡英雄 
	ESearchEffTargetMethodRandEnemySummonDead,   //敌方死亡召唤物 
	ESearchEffTargetMethodRandHeroDead,          //任意死亡英雄 
	ESearchEffTargetMethodRandSummonDead,        //任意死亡召唤物 
	ESearchEffTargetMethodAllFriendSummon,       //所有己方召唤物 
	ESearchEffTargetMethodAnyFriendButSummon,	 //随机己方英雄(召唤物除外) 
	ESearchEffTargetMethodCounterpart			 //对位敌方单位
};

enum ENeedSummon
{
	EOnlySummon,
	EOnlyHero,
	ESummonAndHero
};

enum ESearchRefTargetSpace
{
    ESearchRefTargetSpaceAll,
    ESearchRefTargetSpaceSkillRange
};

enum ESearchTargetRelation
{
    ESearchTargetRelationAll,
    ESearchTargetRelationEnemy,
    ESearchTargetRelationFriend
};

enum ERangeEffectConditionType
{
	EHasAnemyInRange,
	EHasAnyInRange,
	EHasFriendInRange,
	EHasEnemyInRangeNum,
	EToBeContinue
};

enum ESearchTargetFilter
{
    ESearchTargetFilterNone,
    ESearchTargetFilterNearest,
    ESearchTargetFilterFarthest,
    ESearchTargetFilterAttributeMin,
    ESearchTargetFilterAttributeMax,
    ESearchTargetFilterBuff,
    ESearchTargetFilterMostInclude,
    ESearchTargetFilterMostIncludeCircle,
};

enum ESearchEffTargetRegion
{
    ESearchEffTargetRegionSingle,
    ESearchEffTargetRegionCircle,
    ESearchEffTargetRegionSector,
    ESearchEffTargetRegionAnnulus,
    ESearchEffTargetRegionRectangle,
    ESearchEffTargetRegionCounterpart,
};

enum ESearchTargetFilterAttributeName
{
    ESearchTargetFilterAttributeNameHp,
    ESearchTargetFilterAttributeNameLostHp,
    ESearchTargetFilterAttributeNameRage,
    ESearchTargetFilterAttributeNamePhysicalAtk,
    ESearchTargetFilterAttributeNameMagicAtk,
    ESearchTargetFilterAttributeNamePhysicalDef,
    ESearchTargetFilterAttributeNameMagicDef,
    ESearchTargetFilterAttributeNameAtk
};


enum EProjectileType
{
    EProjectileTypeLine,  //常规直线 
    EProjectileTypeWired,         //连线弹道（没有弹道移动过程，瞬间链接上） 
    EProjectileTypeExpansionLink, //拉伸连线 (有伸缩过程)  
    EProjectileTypeCurve         //曲线 
};


enum ECollisionCheckType 
{
    ECollisionCheckTypeEnemy,
    ECollisionCheckTypeFriend,
    ECollisionCheckTypeAll
};


enum EDamageCalculateMethod
{
	EDamageCalculateMethodNormal,
	EDamageCalculateMethodMaxHpPercent,		//按目标血量上限百分比计算 
	EDamageCalculateMethodCurHpPercent,		//按目标当前血量百分比 
	EDamageCalculateMethodFixValue,			//固定数值 
	EDamageCalculateMethodKillWhenLowHp,	//血量低于百分比则斩杀 
	EDamageCalculateMethodLoseHpPercent,	//按目标当前损失血量百分比 
	EDamageCalculateMethodSelfCurHpPercent, //按照自身当前血量百分比 
	EDamageCalculateMethodRecordData,		//按记录数据的百分比 
	EDamageCalculateMethodSelfMaxHpPercent	//按自身血量上限百分比计算 
};


enum EDamageLimitType
{
	EDamageLimitFixValue,
	EDamageLimitPhysical,
	EDamageLimitMagical
};

enum EHealCalculateMethod
{
    EHealCalculateMethodNormal,
    EHealCalculateMethodMaxHpPercent,  //按目标血量上限百分比计算 
    EHealCalculateMethodCurHpPercent,  //按目标当前血量百分比 
    EHealCalculateMethodFixValue,      //固定数值 
    EHealCalculateMethodAddToMax,      //直接加到目标血量上限 
	EHealCalculateMethodRecordData,    //按记录数据的百分比 
	EHealCalculateMethodSelfLoseHpPercent,  //按当前自身损失血量百分比 
	EHealCalculateMethodNoOverflow     //普通方式计算，但是溢出值附给护盾 
};

enum EDamageChannel
{
    EDamageChannelPhysical,
    EDamageChannelMagic,
    EDamageChannelAny
};

enum ECritType
{
    ECritTypeNorm,
    ECritTypePositive,
    ECritTypeAddSkillPortion,
    ECritTypeOnlySkillPortion
};


enum ESummonLevelMethod
{
    ESummonLevelMethodByUtilizerLevel,  //技能发出者等级百分比 
    ESummonLevelMethodByTargetLevel,	//生效目标等级百分比 
    ESummonLevelMethodSetValue,			//设定等级 
	ESummonLevelMethodBossGrowth		//BOSS血条层数 
};


enum EHitEffectPlayType
{
    EHitEffectPlayTypePositive,   //必然播放受击动作 
    EHitEffectPlayTypeByLostdHp        //根据损血百分比 
};


enum EReviveHpType
{
    EReviveHpTypeMaxHpPercent,
    EReviveHpTypeFixValue
};

enum EBuffTriggerSkillHpType
{
	ETriggerSkillHpTypeFixValue,
	ETriggerSkillHpTypeMaxHpPercent
};

enum EReviveSkillPosition 
{
    EReviveSkillPositionDeathPlace,
    EReviveSkillPositionBirthPlace,    
    EReviveSkillPositionUtilizerBackward,
    EReviveSkillPositionUtilizerForward,
    EReviveSkillPositionUtilizerSurround
};


enum  EReviveSkillFormation
{
    EReviveSkillFormationRectangle,
    EReviveSkillFormationCircle
};


enum ESuckRageType
{
    ESuckRageTypeCurRagePercent,
    ESuckRageTypeMaxRagePercent,
    ESuckRageTypeFixValue
};

//回怒技能  自身怒气消耗类型 
enum EAddRageSkillCostType
{
    EAddRageSkillCostTypeNoCost,
    EAddRageSkillCostTypeCurRagePercent,
    EAddRageSkillCostTypeMaxRagePercent,
    EAddRageSkillCostTypeFixValue
};


//回怒技能  自身怒气消耗类型 
enum EAddRageSkillAddType
{
    EAddRageSkillAddTypeCostPercent,
    EAddRageSkillAddTypeCurRagePercent,
    EAddRageSkillAddTypeMaxRagePercent
};



//吸血技能 吸血类型
enum ESuckBloodSkillSuckType
{
    ESuckBloodSkillSuckTypeDamagePercent,
    ESuckBloodSkillSuckTypeTargetCurHpPercent,
    ESuckBloodSkillSuckTypeTargetMaxHpPercent,
    ESuckBloodSkillSuckTypeFixValue
};



//位移技能 伤害时机 
enum EMoveSkillDamageTime
{
    EMoveSkillDamageTimeBeforeMove,
    EMoveSkillDamageTimeAfterMove,
};


enum EMoveSkillMoveType
{
    EMoveSkillMoveTypeBackwardFixValue,
    EMoveSkillMoveTypeForwardFixValue,
    EMoveSkillMoveTypeTargetToSelfForward,
    EMoveSkillMoveTypeSelfToTargetForward,
    EMoveSkillMoveTypeSelfToTargetBackward,
    EMoveSkillMoveTypeSkillDir,     //技能释放方向 
    EMoveSkillMoveTypeNegSkillDir,  //技能释放方向的反方向 
    EMoveSkillMoveTypeRadialDirection,
	EMoveSkillMoveTypeSelfArmyForward,  //己方队伍朝向 
	EMoveSkillMoveTypeSelfForwardOnly,	//释放者自身朝向 
	EMoveSkillMoveTypeTargetLeft,  //参考目标左侧 
	EMoveSkillMoveTypeTargetRight,  //参考目标右侧 
};

enum EEmbattleRelativeDirection
{
    EEmbattleRelativeDirectionBackward,
    EEmbattleRelativeDirectionForward,
    EEmbattleRelativeDirectionLeft,
    EEmbattleRelativeDirectionRight,
    EEmbattleRelativeDirectionSurround
};

enum ESummonSkillBirthPlace 
{
    ESummonSkillBirthPlaceEffTargetBackward,
    ESummonSkillBirthPlaceEffTargetForward,
    ESummonSkillBirthPlaceEffTargetLeft,
    ESummonSkillBirthPlaceEffTargetRight,
    ESummonSkillBirthPlaceEffTargetSurround
};


enum  ESummonSkillFormation
{
    ESummonSkillFormationRectangle,
    ESummonSkillFormationCircle,
    ESummonSkillFormationVector,     
};

enum ESubSkillLevelCalculateMethod
{
    ESubSkillLevelCalculateMethodEqMaster,
    ESubSkillLevelCalculateMethodMasterPercent,
    ESubSkillLevelCalculateMethodFixValue
};

enum EDamageSpecialType
{
	None = 0,  //normal skill 
	Block,
	Poison,
	Raze,
	Burn,
	MinorSkill,
	RageSkill
};

enum EDamageSpecialAdjust
{
	EDamageSpecialAdjustEnable,
	EDamageSpecialAdjustNeedContainBuff
};

enum EDamageSpecialAdustSubType
{
	EDamageSpecialAdjustInvalid,
	EDamageSpecialAdjustWithBuffMainType,
	EDamageSpecialAdjustWithBuffSubType,
	EDamageSpecialAdjustWithBuffIdOR,
	EDamageSpecialAdjustWithBuffIdAND
};

enum ESpecialAdjustTarget
{
	ESpecialAdjustNone,
	ESpecialAdjustDmgOrHeal,
	ESpecialAdjustCrit
};
