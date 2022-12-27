/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author liyingbo
* @date $Date$
* @version $Revision$
* @brief 一个Buff，包含多个BuffMod
*
**/

#pragma once
#include <vector>
#include "Framework/SharedPool.h"
#include "Framework/Timer.h"
#include "Define.h"

using std::vector;

class Unit;
class BuffMod;
class BuffMgr;
class Skill;
namespace pb
{
    class BuffData;
    class SpecialHitModel;
}
using pb::BuffData;
using pb::SpecialHitModel;

enum class BuffSubType;

//TODO: coordinate values with config
enum class BuffType
{
    Positive = 0,
    Negative = 1,
    Neutral = 2,
	Tag = 3,

    _Count
};


//TODO: coordinate values with config
enum class BuffSubType
{
    //增益 
    Heal = 100,//治疗 改变血量 BuffModHp
    MoveSpeedUp = 101,//加移动速度 改变属性 BuffModProperty
    ReflectDamage = 102,//反弹伤害 反弹伤害 BuffModReflectDamage
    ReflectSkill = 103,//反射技能 反射技能 BuffModReflectSkill
    BuffImmunity = 104,//免疫buff 清除、免疫 BuffModBuffImmunity
    Strengthen = 105,//属性增强 改变属性 BuffModProperty
    AttackSpeedUp = 106,//加攻速 改变攻速 BuffModAttackSpeed
    RecoverRage = 107,//恢复怒气 改变怒气 BuffModRage
    AbsorbDamage = 108,//吸收伤害 吸收伤害 BuffModAbsorbDamage
	NonHostileTargettable = 109,//不能被敌方选中 不能成为敌方的选择目标 BuffModNonHostileTargettable
    NonTargettable = 110,//不能被选中 不能成为选择目标 BuffModNonTargettable	
    DamageShare = 111,//伤害分担 伤害分组(平均分摊) BuffModDamageShare
    HealCopy = 112,//治疗复制 治疗复制 BuffModHealCopy
    StealHp = 113,//吸血 吸血 BuffModStealHp
    SkillImmunity = 114,//免疫技能 免疫技能 BuffModSkillImmunity
    Toughness = 115,//底力 底力 BuffModToughness
    DispelNegativeBuff = 116,//清减益buff 清除buff BuffModDispel
	DamageImmunity = 117, //免疫伤害 
	HitDownImmunity = 118, //免疫受击或击倒 
	StrengthenByEquip = 119,  //装备属性增强 
	SkillOnHp = 120,  //Skill will be triggerred once upon Unit's Hp drop below certain threshold  
	ConvertDamageToHeal = 121,  //转化所有伤害为治疗 
	MoveControlImmunity = 122,  //免疫位移效果 
	ConditionChangeDmgCoef = 123,  //条件修改伤害数值 
	HealEnhance = 124,  //治疗加深 
	PropertyDecImmunity = 125,  //免疫战斗属性降低 
	DecDmgByBuffSub = 126,     //更具攻击者自身带有的buff的子类型，觉得活得多少伤害减免 
	ShrinkControlDuration = 127,  //缩短受控时长 
	UnlimitedShield = 128,    //无上限周期性护盾 
	ReflectBuff = 129,   //反弹buff 
	FatalDmgShift = 130,   //致命伤偏移 
	RageImmunity = 131,    //免疫降怒 
	IgnoreShield = 132,    //无视护盾存在 
	RevertStateOnEnd = 133,    //回溯状态 
	ChangeCastRange = 134,     //提升技能释放距离 
	SetMaxLoseHp = 135,     //激活可损血上限 
	AdjustReflectedDmg = 136, //调节反弹类伤害 
	UIEffect = 137,			//激活UI特效 
	AdjustBuffHitRate = 138, //调节Buff命中率(减益Buff) 
	LimitByMaxHpRate = 139,	 //承受伤害的上限被自身最大生命值的百分比限制 
	BattleArcherModify = 140,//修改弓箭主技能属性 
	
    //减益 
    Weaken = 200,//属性削弱 改变属性 BuffModProperty
    MoveSpeedDown = 201,//减移动速度 改变属性 BuffModProperty
    AttackSpeedDown = 202,//减攻速 改变攻速 BuffModAttackSpeed
    NoMove = 203,//不能移动 不能移动 BuffModNoMove
    NoNormalSkill = 204,//不能普攻 不能普攻 BuffModNoNormalSkill
    NoSkill = 205,//不能放技能 不能放技能 BuffModNoSkill
    Damage = 206,//伤害 改变血量 BuffModHp
    ReduceRage = 207,//减怒 改变怒气 BuffModRage
    Dizziness = 209,//眩晕 眩晕 BuffModDizziness
    Freeze = 210,//冰冻 冰冻 BuffModFreeze
    Charmed = 211,//魅惑 魅惑 BuffModCharmed
    Chaos = 212,//混乱 混乱 BuffModChaos
    RandomMove = 213,//随机乱走 在一定区域乱走 BuffModRandomMove
    DamageCopy = 214,//伤害复制 伤害复制 BuffModDamageCopy
    Taunt = 215,//强制攻击 强制攻击带有某buff的目标 BuffModTaunt
    DispelPositiveBuff = 216,//清增益buff 清除buff BuffModDispel
    TransformToSheep = 217,//变羊 变形 BuffModTransformation
	NoRageRecover = 218, //禁怒 忽略所有恢复怒气的请求 BuffModNoRageRecover 
	Buring = 219,		//灼烧 
	Toxic = 220,		//中毒 
	Bleeding = 221,		//撕裂 
	Numb = 222,			//麻痹 
	RendArmor = 223,	//破甲 
	Blinding  = 224,	//致盲 
	Disable = 225,      //残废 
	Ice = 226,			//寒冰 
	Wind = 227,			//风 
	Lightning = 228,    //雷电 
	Sleep = 229,		//睡眠 
	HarmOnMove = 230,   //移动触发损失 
	Fear = 231,			//恐惧 
	Dispel = 232,		//驱逐 
	NoSuckBlood = 233,	//禁止吸血 
	NoRevive = 234,		//禁止复活 
	InfernoFire = 235,	//业火 
	NoHeal = 236,		//禁疗 
	Confuse = 237,		//困惑 


    //中性 
    Transformation = 300,//变形 变形 BuffModTransformation
    Nothing = 301,//什么也不做 什么也不做 <NONE>
    Scale = 302,//缩放体型 缩放体型 BuffModTransformScale
    Die = 303,//到时死亡 buff结束时死亡 BuffModDie
    DispelBuff = 304,//清除buff 清除buff BuffModDispel
    RepeatSkill = 305,//放某技能 持续释放某技能 BuffModRepeatSkill
    SkillOnEnd = 307,//buff消失时放技能 buff消失时释放技能 BuffModSkillOnEnd
	SpecifyBeTargetSkill = 308, //拥有该buff的单位表示，只能成为指定技能的目标 
	ResetBuffTime = 310,//重置Buff时间 
	AddSkill = 311, //添加技能  
	Formula = 312, //公式化修改属性  
	RangeEffect = 313, //范围效果  
	RecordData = 314,  //记录数据  
	HideSomeAppearance = 315, //隐藏部分显示 
	InheritBuffStack = 316,   //继承已有BuffId的层数 
	ScaleText = 317,   //调整伤害数字大小 
	AddDefPoint = 318,  //添加防御点个数和颜色 
	RemoveDefPoint = 319,  //去除防御点 
	RangeEffectCondition = 320, //条件范围效果 
	ChangeDir = 321,	//改变朝向 
	MonitorDefST = 322,	//TD:监控职业状态  
	TDNoBean = 323,		//TD:情况自身豆子并拒绝新豆子  
	TDRepeatSendBean = 324,		//TD:扫描己方根据地，尝试给豆子 
	TDRepeatCheckBean = 325,	//TD:周期判断自己位置，处理身上标记的豆子 
	BuffOnStack = 326,  //层数释放和回收buff 
	ChangeSummonedAI = 327,  //将召唤单位转化为被动模式 

	//标记类
	MarkCaoren = 501,		//曹仁标记 

    //对应BuffMod 
    ChangeProperty = 1000,//BuffModProperty
    ChangeHp,//BuffModHp
    ChangeRage,//BuffModRage
	ChangePropertyByEquip, //BuffModPropertyByEquip

    //兼容  
    _MoveBySkill,

    _Count
};

enum class BuffOverrideType
{//先后顺序重要, BuffMgr.TryAddBuff()中判定已存在Buff的处理时用 
    None = 0,//不重置 (也不叠加) 
    Reset = 2,//重置但不叠加 
    StackReset = 1,//重置且叠加 
	StackNoReset = 3,//叠加但不重置 
};

//属性源   
enum class BuffAttrSource
{
	SourceUtilizer = 0,
	Owner = 1
};

//属性ID
enum class BuffAttrId
{
	Hp = 0,
	PhysicalAttack = 1,
	PhysicalDefend = 2,
	MagicAttack = 3,
	MagicDefend = 4
};
int64 GetUnitAttr(Unit* aUnit, BuffAttrId aAttrId);


enum class BuffBeClearByBuffType 
{
	Any = 0,
	None = 1,
	SpecifyBuffId = 2
};

enum class BuffHitConditionType
{
	None = -1,
	ByType = 0,
	BySubType = 1,
	AllBuffExists = 2,
	AnyBuffExists = 3,
	NeedOtherGender = 4
};

enum class EBuffDisableType
{
	EBuffDisableByTimeOut,
	EBuffDisableByManual,
	EBuffDisableByAny,
	EBuffDisableByReset,
	None
};

struct BuffHitCondition : public IPoolable
{
public:
    virtual bool Valid(const BuffMgr&, const BuffData*);
	virtual void UpdateStackCount(const BuffMgr&) = 0;
    int StackCount() const;
	bool Dicing(const BuffMgr&, const BuffData*);
protected:
    int mStackCount = 0;
};

struct BuffHitNone : public BuffHitCondition
{
public:
	bool Valid(const BuffMgr&, const BuffData*);
	void UpdateStackCount(const BuffMgr&);
	void Reset() {};
};

struct BuffHitByType : public BuffHitCondition
{
public:
    BuffType mType;
	void UpdateStackCount(const BuffMgr&);
	void Reset() {
		mType = BuffType::Positive;
	};
};

struct BuffHitBySubType : public BuffHitCondition
{
public:
    BuffSubType mSubType;
	void UpdateStackCount(const BuffMgr&);
	void Reset() {
		mSubType = BuffSubType::Heal;
	};
};

struct BuffHitAllBuffExists : public BuffHitCondition
{
public:
    vector<int> mBuffs;
	void UpdateStackCount(const BuffMgr&);
	void Reset();
};

struct BuffHitAnyBuffExists : public BuffHitCondition
{
public:
    vector<int> mBuffs;
	void UpdateStackCount(const BuffMgr&);
	void Reset();
};

struct BuffHitByGender : public BuffHitCondition
{
public:
	Unit * mUtilizer = nullptr;
	bool Valid(const BuffMgr&, const BuffData*);
	void UpdateStackCount(const BuffMgr&);
	void Reset();
};

class Buff : public EnableSharedFromThis<Buff>, public IPoolable
{
    enum class EBuffStatus
    {
        Invalid, //未被使用
        Using, 
        Removed        
    };
public:
    Buff():mStatus(EBuffStatus::Invalid){}
    bool Init(const SharedPtr<Unit>&, const SharedPtr<Unit>&, const WeakPtr<Unit>&, BuffMgr&, int aBuffId, int aLevel, const BuffData*, const SharedPtr<BuffHitCondition>&);
    void Reset();
    int GetId() const;
	bool IsValid() const;
    bool IsClearableByBuff(int aByBuffId) const;
    BuffType GetType() const;
    BuffSubType GetSubType() const;
	EBuffDisableType GetDisableType() const;
	int GetLevel() const;
    int GetStack() const;
    int64 ScaledValue(int64 aValue) const;
    const WeakPtr<Unit>& GetOwner() const;
	WeakPtr<Unit>& GetSourceUtilizer();
    void SpecialConditionEffectMultiplier();
    void SpecialConditionTimeMultiplier();
    void BuffReset(int);
    void BuffReset();
    void Offset(int);
    void CleanListener();
    int IncreaseStack();
    int RemoveStack(int);
    void OnRemove(bool);
    bool CheckHitCondition(const BuffMgr&);
    const SharedPtr<BuffMod>* GetMod(BuffSubType aType) const;
    BuffMgr* GetMgr() const;
    const char* GetAnimName() const;
	void WhenBuffNumberChanged();
    int WhenAddSameBuff();
	int WhenAddSameBuff(int aTimes);
	WeakPtr<Skill> mAncestorSkill;
	int GetLabelId() const;
	bool HasLabelId() const;
	int64 GetRecordData() const;
	void SetRecordData(int64);
	void AddRecordData(int64);
	bool NeedRemoveWhenBeControlled() const;
	bool NeedRemoveWhenShapeShifted() const;
	bool IsControlType() const;
	void AddModsByConf(const SharedPtr<Unit>&, const SharedPtr<Buff>&, int aLevelFactor, const BuffData* aBuffConf);
	int64 TryShrinkTimeLength();
	int64 GetRemainingTime();
public:
	BuffOverrideType mOverrideType = BuffOverrideType::None;
	int mBeCleanLevel = 0;
	int64 mExecuteTime = 0;
private:
    int mId = 0;
    int mLevel = 0;
	bool mRemoveWhenBeControlled = false;
	bool mRemoveWhenShapeShifted = false;
    EBuffStatus mStatus = EBuffStatus::Invalid;
	EBuffDisableType mDisableType = EBuffDisableType::EBuffDisableByTimeOut;
    int64 mTimeLength = 0;
	WeakPtr<Unit> mSourceUtilizer = nullptr;
    WeakPtr<Unit> mOwner = nullptr;
    BuffMgr* mMgr = nullptr;
    BuffBeClearByBuffType mBeClearByBuffType = BuffBeClearByBuffType::Any;
	vector<int> mCleanableBuffIdArr;
    BuffType mType = BuffType::Positive;
    BuffSubType mSubType = BuffSubType::Heal;
    int mStack = 0;
    int mEffectMultiplier = 0;
    int64 mTimeMultiplier = 0;
	int mLabelId = 0;
	int64 mRecordData = 0;
    vector<SharedPtr<BuffMod> > mMods;
    SharedPtr<Timer<Buff> > mLifeTimer = nullptr;
    SharedPtr<Timer<Buff> > mSetAnimTimer = nullptr;
    const BuffData* mConfig = nullptr;
    const SpecialHitModel* mSpConf = nullptr;
    const char* mAnimName = nullptr;
	bool mEffectNeedRealtimeRefresh = false;
    SharedPtr<BuffHitCondition> mHitCondition = nullptr;

    bool OnTimeout(Timer<Buff>&);
    void RefreshUnitAnim();
    bool OnSetUnitAnimTimer(Timer<Buff>&);
    void AddMod(const SharedPtr<BuffMod>& aMod);
    void StackAdded(int);
    void StackRemoved(int);

    //template<class M, class P = typename M::Params>
    //P& AddMod(SharedPtr<Buff>&, BuffSubType, int);
    template<class M>
    M* CreateMod(const SharedPtr<Buff>&);
};