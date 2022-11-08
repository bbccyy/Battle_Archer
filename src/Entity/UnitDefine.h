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

enum class EAttribute
{
    Invalid,
    Leadership,            //1   统帅  数值
    Force,                 //2   武力  数值
    Intelligence,          //3   智力  数值
    Politics,              //4   政治  数值
    Charm,                 //5   魅力  数值
    AtkSpeed,              //6   攻速  比率
    HpBase,                //7   生命基础值   数值
    PhysicalAtkBase,       //8   物理攻击基础值 数值
    PhysicalDefBase,       //9   物理防御基础值 数值
    MagicAtkBase,          //10  法术攻击基础值 数值
    MagicDefBase,          //11  法术防御基础值 数值
    HpPercent,             //12  生命百分比   比率
    PhysicalAtkPercent,    //13  物理攻击百分比 比率
    PhysicalDefPercent,    //14  物理防御百分比 比率
    MagicAtkPercent,       //15  法术攻击百分比 比率
    MagicDefPercent,       //16  法术防御百分比 比率
    HpExtra,               //17  生命最终值
    PhysicalAtkExtra,      //18  物理攻击最终值
    PhysicalDefExtra,      //19  物理防御最终值
    MagicAtkExtra,         //20  法术攻击最终值
    MagicDefExtra,         //21  法术防御最终值
    DamageRank,            //22  伤害等级    数值
    AvoidInjuryRank,       //23  免伤等级    数值
    PhysicalPercentAdd,    //24  物理伤害加成  比率
    PhysicalPercentSub,    //25  物理伤害减免  比率
    MagicPercentAdd,       //26  法术伤害加成  比率
    MagicPercentSub,       //27  法术伤害减免  比率
    NormalSkillPercentAdd, //28  普攻伤害加成  比率
    NormalSkillPercentSub, //29  普攻伤害减免  比率
    OtherSkillPercentAdd,  //30  技能伤害加成  比率
    OtherSkillPercentSub,  //31  技能伤害减免  比率
    FinalDamage,           //32  最终伤害值   数值
    FinalAvoidInjury,      //33  最终免伤值   数值
    PhysicalAtkTalent,     //34  物理攻击天赋  数值
    PhysicalDefTalent,     //35  物理防御天赋  数值
    MagicAtkTalent,        //36  法术攻击天赋  数值
    MagicDefTalent,        //37  法术防御天赋  数值
    CriticalProb,          //38  暴击率 比率
    AntiCriticalProb,      //39  抗暴率 比率
    PhysicalHitProb,       //40  物理命中    比率
    MagicHitProb,          //41  法术命中    比率
    DodgeProb,             //42  闪避  比率
    ExemptionProb,         //43  豁免(法术闪避）    比率
    AntiBlockProb,         //44  破档  比率
    AntiResilienceProb,    //45  法术穿透(法术破挡）  比率
    BlockProb,             //46  格挡  比率
    ResilienceProb,        //47  抵抗（法术格挡）    比率
    CriticalPercentAdd,    //48  暴击伤害倍率  比率
    CriticalPercentSub,    //49  暴击伤害抗性  比率
    StrikeBackProb,        //50  反击  比率
    PVEPercentAdd,         //51  PVE增伤   比率
    PVEPercentSub,         //52  PVE免伤   比率
    PVPPercentAdd,         //53  PVP增伤   比率
    PVPPercentSub,         //54  PVP免伤   比率
    HealAdd,               //55  治疗量 数值
    BeHealAdd,             //56  被治疗量    数值
    HealPercentAdd,        //57  治疗率 比率
    BeHealPercentAdd,      //58  被治疗率    比率
    DizzinessPercentAdd,   //59  眩晕命中百分比 比率
    SilencePercentAdd,     //60  沉默命中百分比 比率
    TorpidityPercentAdd,   //61  麻痹命中百分比 比率
    ReduceRagePercentAdd,  //62  降怒命中百分比 比率
    ForbidRagePercentAdd,  //63  禁怒命中百分比 比率
    FreezePercentAdd,      //64  冰冻命中百分比 比率
    PetrifyPercentAdd,     //65  石化命中百分比 比率
    FearPercentAdd,        //66  恐惧命中百分比 比率
    CharmPercentAdd,       //67  魅惑命中百分比 比率
    ChaosPercentAdd,       //68  混乱命中百分比 比率
    TauntPercentAdd,       //69  挑衅（嘲讽）命中百分比 比率 
    CripplePercentAdd,     //70  残废命中百分比 比率 
    DizzinessPercentSub,   //71  眩晕抗性百分比 比率 
    SilencePercentSub,     //72  沉默抗性百分比 比率 
    TorpidityPercentSub,   //73  麻痹抗性百分比 比率 
    ReduceRagePercentSub,  //74  降怒抗性百分比 比率 
    ForbidRagePercentSub,  //75  禁怒抗性百分比 比率 
    FreezePercentSub,      //76  冰冻抗性百分比 比率 
    PetrifyPercentSub,     //77  石化抗性百分比 比率 
    FearPercentSub,        //78  恐惧抗性百分比 比率 
    CharmPercentSub,       //79  魅惑抗性百分比 比率 
    ChaosPercentSub,       //80  混乱抗性百分比 比率 
    TauntPercentSub,       //81  挑衅（嘲讽）抗性百分比 比率 
    CripplePercentSub,     //82  残废抗性百分比 比率 
    Arm,                   //83  所带兵种    数值 
    HealCriticalProb,      //84  治疗暴击率   比率 
    CutsceneAddRage,       //85  过屏增加的怒气 数值 
    CutsceneAddHp,         //86  过屏增加的生命 数值 
    HealCriticalPercentAdd, //87  治疗爆伤 比率 
    MoveSpeed,              //88  移动速度 
	InitRage,               //89 初始怒气 
	DamageAddPercentToMale,   //90 对男性增伤 
	DamageSubPercentToMale,   //91 对男性免伤 
	DamageAddPercentToFemale, //92 对女性增伤 
	DamageSubPercentToFemale, //93 对女性免伤 

	UniversalHitProb,		 //通用命中  94  比率 
	UniversalDodgeProb,      //通用闪避  95  比率 
	UniversalAntiBlockProb,  //通用破挡  96  比率 
	UniversalBlockProb,      //通用格挡  97  比率 
	UniversalArmourPiercing, //通用穿甲  98  比率 
	UniversalArmour,		 //通用护甲  99  比率 

	RageGrowthRate,			//怒气回复倍率  100  比率 
	RageDecRate,			//怒气下降倍率  101  比率 

	SystemDamage,			//系统伤害  102  比率 
	SystemAvoidInjury,		//系统免伤  103  比率 

	TreasureAdd,			//宝物增伤  104  比率 
	TreasureSub,			//宝物减伤  105  比率 

	BreakWei,				//破魏 106 比率 
	BreakShu,				//破蜀 107 比率 
	BreakWu,				//破吴 108 比率 
	BreakQun,				//破群 109 比率 

	ResistWei,				//抗魏 110 比率	
	ResistShu,				//抗蜀 111 比率 
	ResistWu,				//抗吴 112 比率 
	ResistQun,				//抗群 113 比率 

	PlatinumAdd,			//白金增伤 114 比率 
	PlatinumSub,			//白金免伤 115 比率 

    _Count
};




enum class ERageChangeCause
{
	Invalid,
	SkillGive,			//加怒技能，消耗自己的怒气
	SkillBeGiven,		//加怒技能，被加怒气
	SkillSuck,			//吸怒技能，吸收怒气
	SkillBeSucked,		//吸怒技能，被吸怒气
	Kill,				//杀敌获得怒气
	OnDamage,			//受伤时，获得怒气
	Buff,				//buff增加、减少怒气
	ExecuteSkill,		//执行技能获得怒气
	RageSkillCost,		//怒气技能消耗
	RageSkillCostSmoothly   //怒气技能消耗(平滑扣减) 

};


enum class EUnitDieCause
{
	Invalid,
	Skill,
	Buff,
	Behaviour,
	Timeout,
	ClearSummonWhenCutScene,
	ClearAllWhenDircetWin
};

enum class EPosType
{
	None = 0,
	Front = 1,
	Middle,
	Back
};

enum class EConditionChangeMainType
{
	CurHp = 0,
	MaxHp = 1,
	CurRage = 2,

	MemberNumber = 3,				 //己方人数
	SelfToTargetDistFar = 4,
	EffTargetNumber = 5,
	TargetCurHp = 6,				//目标剩余血量(多) 
	TargetCurRage = 7,
	SelfToTargetDistNear = 8,
	TargetHasShield = 9,
	TargetIsSummoned = 10,
	TargetRageToSelf = 11,
	TargetHasGivenSubTypes = 12,	//目标拥有给定的buff子类型 
	MemberNumberSelfLess = 13,		//己方人数越少 
	MemberNumberEnemyMore = 14,		//敌方人数越多 
	TargetCurHpLess = 15,			//目标剩余血量(少) 

	_Count
};

enum class EConditionRelation
{
	Greater = 0,
	Less = 1,

	_Count
};

enum class ECountry
{
	None = 0,
	Wei = 1,
	Shu = 2,
	Wu = 3,
	Qun = 4,
	Master = 5,
	Story = 6,

	_Count
};