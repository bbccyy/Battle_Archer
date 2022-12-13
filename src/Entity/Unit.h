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
* @brief 战斗单位
*
**/

#pragma once


#include "Entity/MoveExecutor/MoveParabloa.h"
namespace pb {		
	class TArmyUnitInfo; 
}
using pb::TArmyUnitInfo;



#include <vector>
#include <queue>
#include "Framework/SharedPtr.h"
#include "Framework/StateMachine.h"
#include "Framework/Timer.h"
#include "Buff/BuffMgr.h"
#include "UnitDefine.h"
#include "Entity.h"
#include "Skill/SkillDefine.h"
#include "Entity/MoveExecutor/MoveParabloa.h"

using std::vector;
using std::queue;

struct RageSkillExecuteState;
struct HitResult;
struct ActiveBase;
class Skill;
class Buff;
class Army;
class Entity;
struct DirectedPosition;

class BattleInstance;
class BattleViewOutput;
class PhysicsSystem;
class Cylinder;
class SkillExecutor;
class Agent;
class BuffModStealHp;
class BuffModShapeshift;
class BuffModDamageShare;
class BuffModDamageCopy;
class BuffModHealCopy;
//class SceneBarrier;
//class MeleeRingMgr;
struct BuffModPropertyEntry;
enum class BuffType;
enum class BuffSubType;
enum class EActiveBaseType;
enum class ShapeshiftBuffInheritanceRule;

class ConfigHero;
namespace pb
{
    class TUnitInfo;
    class AvatarData;
}
using pb::TUnitInfo;
using pb::AvatarData;

enum class MoveStrategy
{
	Trace = 0,
	AIPath = 1,
	PredefinedPath = 2,
};

//被控制状态类型 
enum class ControlledType
{
    None = 0,
    MoveBySkill = 1,
    Dizziness,
    Freeze,
    RandomMove,
	SkillRecovery
};

enum class UnitType
{
	Undefined = 0,
	Player = 1,
	Pet = 2,
	Monster = 3,
};

//受击类型
enum class BeHitType
{
	None = 0,
	Hit = 1,
	Down = 2,
	Knock = 3
};

enum class ActionSpeedCondition
{
	OnNormalBegin = 0,		//need apply factor if has
	OnNonnormalBegin = 1,   //need retrive factor to normal
	OnRecoverBegin = 2,     //need apply factor if has
	OnRecoverEnd = 3,		//need retrive factor to normal
	OnInterrupt = 4,		//need retrive factor if has
	OnRevertSpeed = 5       //need send anyway
};

enum class ScreenTextType
{
	DamageImmunityPhysical = 14,
	DamageImmunityMagical = 15,
	AbsorbDamage = 16,
	DamageImmunityAll = 17,
	HitDownImmunity = 18,
	SpeedUp = 19,  //map to both Attack and Move speed in BuffMod
	SpeedDown = 20,
	DefenseDownPhysical = 21,   //map to buffMode type:ChangeProperty  -> PhysicalDefBase, PhysicalDefPercent, PhysicalDefExtra
	DefenseUpPhysical = 22,
	DefenseDownMagical = 23,   //MagicDefBase, MagicDefPercent, MagicDefExtra
	DefenseUpMagical = 24,
	NoSkill = 25, 
	Charmed = 26,
	Dodge = 5,
	Exemption = 6,
	Block = 7,
	Resilience = 8,
	Taunt = 27,
	PhysicalDamageIncreaseUp = 29,
	PhysicalDamageIncreaseDown = 30,
	PhysicalDamageAvoidUp = 31,
	PhysicalDamageAvoidDown = 32,
	MagicalDamageIncreaseUp = 33,
	MagicalDamageIncreaseDown = 34,
	MagicalDamageAvoidUp = 35,
	MagicalDamageAvoidDown = 36,
	ShieldApply = 37,
	ShieldAbsorb = 38,
	Interrupt = 39,
	PerfectInterrupt = 40

};

//特殊修正类型（非被控制的特殊状态） 
enum class StateAdjust
{
    //对应buff的状态 
    Charmed = 0,
    Chaos,
    Freeze,
    Dizziness,
    NoMove,
    NoSkill,
    NoNormalSkill,
    RepeatSkill,
    Taunted,
    ReflectDamage,
    ReflectSkill,
    NonRefTarget,
    NonEffTarget,
	NonHostileRefTarget,
	NonHostileEffTarget,
    HealCopy,
    DamageCopy,
    DamageShare,
    AbsorbDamage,
    Toughness,
	DamageImmunityAll,
	DamageImmunityPhysical,
	DamageImmunityMagic,
	DamageImmunityPercent,
	HitDownImmunity,
	MoveControlImmunity,
	NoRageRecover,

    //逻辑状态 
    BehaviourHidden,//被行为隐藏 
    BehaviourStopped,//被行为设置为待机 
    InvisibleDummy,//该单位是隐形NPC 

	VulnerableToBarrier,  //able to be blocked by barrier
	Disable,  //reduce damage to exactlly 1 

	NoSmallSkill,
	NoRageSkill,

	ShrinkControlDuration,  //缩减受控时长 
	UnlimitedShield,  //无上限吸收护盾 
	ReflectBuff,	//反弹Buff 
	FatalDmgShift,  //致命伤偏移 

	RageImmunity,  //免疫降怒 

	TDBeanImmunity,  //TD:免疫豆子标记 

	IgnoreShield,	//无视护盾存在 
	NoSuckBlood,	//禁止吸血  
	NoRevive,		//禁止复活 
	SetMaxLoseHP,	//激活可损血上限 
	AdjustReflectedDmg, //反弹伤害调节 

	RageImmunityBuffOnly,	//免疫降怒(buff) 
	RageImmunitySkillOnly,  //免疫降怒(skill) 

	AdjustBuffHitRate,  //调节减益Buff命中率 

	LimitByMaxHpRate,   //承受伤害的上限被自身最大生命值的百分比限制 

	NonRefTargetWithWhiteList,  //不可被选中为参考目标(白名单中的除外) 
	NonEffTargetWithWhiteList,  //不可被选中为生效目标(白名单中的除外) 

    _Count
};

enum class BeanState
{
	NoneToMelee,     //无到有(近战) 
	NoneToDistance,	 //无到有(远程) 
	AnyToNone,		 //任意有到无 
};

enum class ShieldType
{
	Physical,		 //物理
	Magical,		 //法术
	Universal,		 //任意
	UniversalCount   //次数 
};

enum class RageSkillStatus
{
	RageNotReady = 0,
	RageReadyToCast,
	RageReadyButBeControlled,
	RageFinishCasting,
	RageStartCasting,
};


struct ShapeShift : public IPoolable
{
public:
	void Reset();
public:
	int mTplId = 0;
	int mLevel = 0;
	int mLastTplId = 0;
	int mLastLevel = 0;
	vector<int64> mLastAttrArr;
	int mInheritLevel = 0;
	bool mInheritAttributes = false;
	bool mInheritSkill = false;
	ShapeshiftBuffInheritanceRule mInheritBuff;
	int mNormalAtkNumBeforeChangeAvatar = 0;
	int mSkillNumBeforeChangeAvatar = 0;
	int mSkillLv = 0;
	int mChainSkillIndex = 0;
	bool isBattleSoulMode = false;
	int mBuffId = 0;

	bool mIsValid = false;
};


//被控制的信息 
struct ControlToken : public EnableSharedFromThis<ControlToken>, IPoolable
{
public:
	~ControlToken();
    void Reset();
    void CalculatePriority();
    ControlledType mType;//控制类型 
    bool mIsValid;//该状态是否生效 
    const char* mName;//（动作）名称 
    int mPriority;//（动作）表现优先级，用于排序 
    int mStartTime;//开始生效的时间点，用于排序 
	int mTimeOut;  //this state will be abandoned at <mTimeOut> Unit time
	bool mReplayable;
    const IFunctionContainer<bool, int>* OnTick;//该状态的持续处理方法 

    static SharedPtr<ControlToken> Create(ControlledType, const IFunctionContainer<bool, int>*, const char*);
};

struct DieCause
{
	EUnitDieCause cause;
	int data;  //store skill or buff id
	int rageBonus;  //store bonus rage by far
	const char* animName;
	vector<int> moveConf;
	Vector3 mDir;
	
	DieCause(EUnitDieCause aCause = EUnitDieCause::Invalid);
	void Reset();
	bool IsNormalDie() const { return moveConf.size() == 0; };
};

struct ConditionChangeData
{
	int mKey;
	int mMainType;
	int mRelation;
	int mTarget;
	int64 mParam1;
	vector<int> mParamArr;
};

struct ChangeDataByBuffSub
{
	BuffSubType mType;
	EAttribute mAttr;
	int64 mValue;
};

struct BuffSkillInfo : public IPoolable
{
public:
	void Reset() {
		mSkillId = 0;
		mBeginCount = 0;
		mEffectCount = 0;
	};
	int mSkillId;
	int mBeginCount;
	int mEffectCount;
};

//一个战斗单位，代表战场上的一个个体，能够移动，释放技能，接受伤害/治疗，接受buff 
class Unit : public Entity, public EnableSharedFromThis<Unit>
{
public:
    Unit() = default;
    void Init(const TUnitInfo&, Army&, BattleViewOutput&, PhysicsSystem&, int aBornPoint);//使用序列化信息初始化 
    void Init(int aTplId, int aLevel, int aSkillLevel, int aAdvLv, int aBornPoint, Army&, BattleViewOutput&, PhysicsSystem&, const vector<int>& aSkillList);//使用原始id信息初始化（用于召唤） 
	void InitDummy(Army&, BattleViewOutput&, PhysicsSystem&);
	void AddViewEntity(int, int, int, int aParent = 0);//通知View添加Entity 
    void Reset();
	void UnRegisterAllEvents();
    void LoadSkill(const TUnitInfo&);//根据传入的配置加载技能列表 
    void LoadSkill(int);//根据英雄配置加载技能列表 
    void LoadSkill(const vector<int>&, int);//根据BattleArgs记录数据加载技能列表 
    void LoadAttr(const TUnitInfo&);//根据传入的配置加载属性列表 
    void LoadAttr(int const aTplId);//根据配置计算属性列表 
    void LoadAttr(int const aTplId, int const aLevel);//同上，附带等级属性调整  
    void LoadAttr(const Unit* aUnit, int aPercent, int const aTplId, bool aUseFixedRate);//根据百分比继承属性
    void LoadAttr(const vector<Unit*> aUnitList, int aPercent, int const aTplId);//根据平均属性继承 
    void OnTick(int aDeltaTime);
    void OnEnterField();//开始下一屏 
    void OnEnterCutscene();//进入过场 

	void SendScreenTextCmd(ScreenTextType aType, int64 aExtraData = 0);
	void SendMaxHpChangeCmd(int aSkillId = 0, int aUtilizerId = 0);

	SharedPtr<Skill> AddSkill(int aSkillId, int aLevel);
	void RemoveSkill(int const aSkillId);

    Vector3 GetSocketPos(const char* aAnimName, const char* aSocketName) const;
    TimerMgr* GetTimerMgr() const;
    Army& GetArmy() const;
    const TUnitInfo* GetUnitInfo() const;
    BattleInstance& GetBattleInstance() const;
    string& GetAvatarName() const;
    Agent* GetAgent() const;
    BoundingVolume* GetBV() const;
    Cylinder& GetBVDerived() const;
    const char* GetCurrentAnimName() const;
    const char* GetDeathAnimName(string) const;
	bool HasCurrentAnimName() const;
	int64 GetCurrentAnimStartTime() const;
	int64 GetCurrentAnimTotalTime() const;
    //int GetNormalAtkNum() const;
    int GetUnitTime() const;
    int64 GetHp() const;
    int64 GetLostHp() const;
    int64 GetMaxHp() const;
    int64 GetRage() const;
    int64 GetMaxRage() const;
	int64 GetShieldByType(ShieldType) const;
	void AddShieldByType(ShieldType, int64);
	void SubShieldByType(ShieldType, int64, int, int);
    int GetLevel() const;
    int64 GetDamageInTotal() const;//受到伤害总量 
	int64 GetDamageInWithOverflow() const;  //带溢出的总承伤 
    int64 GetDamageOutTotal() const;//输出伤害总量 
    int64 GetHealOutTotal() const;//输出有效治疗总量  
	int GetArmyId() const;
	int GetAdvLevel() const;
	int GetStar() const;
	int GetProfession() const;
	SharedPtr<ControlToken> GetControlToken(const char*);
	SharedPtr<ControlToken> ScheduleControlToken(const char* aAnimName, int aDuriation);
	const char* GetAnimNameByConf(const char*);
	int GetTimeLengthByAnimName(const char*);
	bool HasInRangeSkillTarget();
	RefTarget& GetInRangeSkillTarget();

    bool IsBorn() const;//unit is born if fsm is initialized
    bool IsDead() const;
    bool IsDying() const;
    bool IsEmptyHp() const;
    bool IsHidden() const;
    bool IsSummoned() const;
	bool IsDummy() const;
	bool IsRefDummy() const;
	bool IsBehaviourUnit() const;
    bool IsClearOnCutscene() const;
    bool IsEnemy(const SharedPtr<Unit>&) const;
	bool IsEnemy(const int) const;
	bool IsHero(const int) const;
	//bool IsSlg() const;
	bool NeedFieldInit() const;
	bool IsTowerLike() const;

	int GetAncestor() const;

    void ModifyActionSpeed(int);
	void ConditionSendActionSpeedCMD(ActionSpeedCondition);
    bool CheckStateAdjust(StateAdjust) const;
    void IncStateAdjust(StateAdjust);
    void DecStateAdjust(StateAdjust);

    void TryReceiveBuff(SharedPtr<Unit>, SharedPtr<Unit>, int aBuffId, int aLevel, WeakPtr<Skill> aAncestorSkill = WeakPtr<Skill>(), int aBTDel = 0, bool aAbleToInterrupt = true);
	void ExecuteSkill(const SharedPtr<Skill>, int, SharedPtr<SkillExecutor>, SharedPtr<Unit>, SharedPtr<Unit> aReflecter = nullptr);//尝试立刻执行一个技能 
	void TryTriggerSkillOnHp();
    int ManuallyExecuteRageSkill();//手动触发怒气技能 
	//int ManuallyUnregisterNextSemiAutoSkill();
	int TryExecuteRageSkillAuto();
	//int TryExecuteBattleSoulSkillAuto();
    int TryExecuteRageSkill(); 
    //int TryExecuteBattleSoulSkill();
	void TryExecuteRageSkillBreakNormalAuto();
	//void TryExecuteBattleSoulSkillBreakNormalAuto();
	//int ManuallyExecuteUnparalleledSkill();//手动触发无双技能 
	//int ManuallyExecuteBattleSoulSkill();//手动触发武魂真身技能 
    void SetRageSkillState(RageSkillExecuteState*);
    RageSkillExecuteState* GetRageSkillState();
    bool IsInRageSkillMaskTime() const;
    void OnSkillKeyframe(const SkillExecutor& aSkillExecutor);
	void OnSkillEnd(const SkillExecutor& aSkillExecutor);
    void CurrentSkillInterrupted(bool aNoEvent = false);//打断当前技能 
    void NormalSkillInterrupted();//打断普攻 
    void OtherSkillInterrupted();//打断除普攻外的其他技能 
	void SmallSkillInterrupted();//打断小技能 
	void RageSkillInterrupted();//打断怒气技能 
    void OnDodge(const SharedPtr<Unit>&, int aSkillId);//（物理）闪避 
    void OnExemption(const SharedPtr<Unit>&);//（法术）豁免 
    void OnParry(ETriggerAfterParrySub, int aSkillId, int aUtilizerId);//（物理）格挡 
    void OnDamage(ETriggerAfterDmgSub, int aSkillId, int aUtilizerId, int64 aDmg);// 受伤 
    void OnResist();//（法术）抵抗 
	void OnCritical(Unit *);  //暴击 
	void OnBeCritical();  //被暴击 
	void OnDizzy();		//眩晕  
	void OnBuffSubtypeActive(BuffSubType);	//当buff子类型激活后   
	void OnShieldEnabled(); //护盾激活  
	void OnDispelBuff(Unit *);  //驱散buff 
	void OnHealOverflow(int aBuffId, int64 aOverFlow);  //过量治疗时 
    void OnHit(const SharedPtr<Unit>&, int aSkillId, BeHitType, const bool aSkipDmg = false);//被技能命中 
    void OnSkillMoveDone(int aSkillId);  //技能移动结束 
    void OnApplyUnlimitedShield(int aUtilizer);  //无上限护盾吸收伤害过后 
    void OnReflectSkill(int aSkillId);  //反弹技能后  
    void OnRageSkill();					//大招后   
    void OnRageSkillWithRef();			//大招后(带参考目标)  
    void OnBeSummoned();				//被召唤后    
    void OnBeRevived();					//被复活后 
    void OnAnimSkill();					//非普攻非大招带动画技能执行后 
    void DealingDamageByBuff(int64);//通过buff对别人造成伤害（用于数据统计） 
	
    int64 Damage(HitResult& aResult, Unit* aUtilizer, const Skill* aSkill, const Buff* aBuff, bool aIgnoreRage = false);//伤害 
    int64 Heal(HitResult& aResult, Unit* aUtilizer, const Skill* aSkill, const Buff* aBuff);//治疗 
    void HealByStealHp(int64 aHpDelta, const Skill* aSkill, const Buff* aBuff);//（通过吸血）治疗自己 
    void Revive(int aHp, int aLifeTime, bool aClearOnCutscene, bool aResetSkillCD);
    void SetSummoner(Unit* aSummoner);
	void SetAncestorSkill(WeakPtr<Skill> aSkill);
    bool IsSummonedBy(const Unit* aUnit) const;
    bool IsEnemyRageShow() const;
    void SetTimedLife(int, bool);//设置存活时间（只有召唤物有存活时间） 
    void Die(const DieCause& aCause);
	void SetDie();

    //void EnableMoveBySkill(SharedPtr<IFunctionContainer<void, SharedPtr<Unit>> >, const Unit* aUtilizer, bool aValidRefTarget, bool aValidEffTarget);//被技能移动 
	void EnableMoveBySkill(const IFunctionContainer<void, SharedPtr<Unit> >* aWhenCancel, ControlToken* aState, const Unit* aUtilizer, bool const aValidRefTarget, bool const aValidEffTarget);
	//void DisableMoveBySkill(bool, SharedPtr<Unit> aUtilizer, bool aValidRefTarget, bool aValidEffTarget);//结束被技能移动 
	void DisableMoveBySkill(bool aClearControl, SharedPtr<Unit> aUtilizer, ControlToken* aState, bool const aValidRefTarget, bool const aValidEffTarget);
	SharedPtr<Unit> GetLastNormalSkillTarget() const;
	void SetLastNormalSkillTarget(SharedPtr<Unit> aRefTarget);
	void SetLastRefTarget(SharedPtr<Unit> aRefTarget, int64);

    bool HasBuff(int) const;
	WeakPtr<Buff> GetBuff(int aBuffId);
	int64 GetBuffRecordData(int aBuffId);
    bool RemoveByBuffType(const vector<BuffType>&, int, int, bool aShouldTrigger = false, int aCleanLv = 0);
    bool RemoveByBuffSubType(const vector<BuffSubType>&, int, int, bool aShouldTrigger = false, int aCleanLv = 0);
    bool RemoveBuff(int, int);
	bool RemoveBuffAndTrigger(int, int);
    bool RemoveBuff(const vector<int>&, int, int, bool aShouldTrigger = false);
	int CountBuffLayerByMainType(BuffType) const;
	int CountBuffLayerBySubType(BuffSubType) const;
	int CountBuffLayerByBuffIdOR(const vector<int>&) const;
	int CountBuffLayerByBuffIdAND(const vector<int>&) const;
    int TauntedTargetBuffId() const;
    void TauntedTarget(int);
    void ClearTauntedTarget();
	void SetSpecifyBeTargetSkills(const vector<int>&);
	void ResetSpecifyBeTargetSkills(const vector<int>&);
    void BeControlled(ControlToken&);//附加一层被控制状态 
    void ClearBeControlled(ControlToken&);//清除一层被控制状态 

    void SkillImmunityByType(const vector<ESkillSubType>&);
    void SkillImmunity(int);
    void SkillImmunity(const vector<int>&);
    void RevokeSkillImmunityByType(const vector<ESkillSubType>&);
    void RevokeSkillImmunity(int);
    void RevokeSkillImmunity(const vector<int>&);
    void BuffImmunityByType(const vector<BuffType>&);
    void BuffImmunityBySubType(const vector<BuffSubType>&);
    void BuffImmunity(int);
    void BuffImmunity(const vector<int>&);
    void RevokeBuffImmunityByType(const vector<BuffType>&);
    void RevokeBuffImmunityBySubType(const vector<BuffSubType>&);
    void RevokeBuffImmunity(int);
    void RevokeBuffImmunity(const vector<int>&);
	void InvokeBuffModifyDamage(ChangeDataByBuffSub& aData);
	void RevokeBuffModifyDamage(ChangeDataByBuffSub& aData);
	void PropertyChangeImmunity(EAttribute);
	void RevokePropertyChangeImmunity(EAttribute);
    void ModifyAttr(const vector<BuffModPropertyEntry>&, bool aNeedSendText = true, int aBuffId = 0);//属性修改 
    void RevertAttr(const vector<BuffModPropertyEntry>&);//取消属性修改 
    int64 ModifyMaxHp(int64 aMaxHpChange, int64 aHpChange, int64 aHpDiff, bool aNeedSendCmd = true);
	//bool HasTextShift(int aSkillId);
	//int GetTextShift(int aEntityId);
	//void SetTextShift(int aEntityId);
	//void CleanTextShift();

	bool CanBeRefTargetOfUtilizer(Unit* aUtilizer, Skill* aSkill);
	bool CanBeEffTargetOfUtilizer(Unit* aUtilizer, Skill* aSkill);
	bool IsLastAliveHeroInArmy();
	bool IsArmy2PVE();
    bool IsImmueToBuff(int aBuffId, BuffType, BuffSubType) const;
    bool IsImmueToSkill(int aSkillId, ESkillSubType) const;
	bool IsImmuePropertyDec(EAttribute) const;
	bool hasBuffModifyDamage() const;
    void AddRage(int64, ERageChangeCause);
    void SubRage(int64, ERageChangeCause);
	//void AddRageUnparallel(int64);
	//void SubRageUnparallel(int64);
    void SkillUseRage(int64 aSubRageTime = 0);
	//void SkillUseRageUnparallel();
	void Born();
	bool hasBorn();
	void OnDelete();
	bool HasDeleted();
	void RemoveAllListener();
	MoveStrategy HowToMove(const RefTarget&);
    int64 GetAttr(EAttribute aAttr) const;
    bool IsInvalidAttr(EAttribute aAttr) const;
	int64 GetAttrByCondition(EAttribute aAttr, SharedPtr<Unit>& aTarget, SharedPtr<Skill> aSkill = nullptr);
	void DirectAddAttr(EAttribute aAttr, int64 aValue);
	int GetHeroId() const;
	int GetTplId() const;
	int GetCurTplId() const;
	int GetKnockTimeLength() const;
    int64 GetPhysicalAtk() const;
    int64 GetMagicAtk() const;
    int64 GetPhysicalDef() const;
    int64 GetMagicDef() const;
	int64 GetFinalDamage() const;
	int64 GetFinalAvoid() const;
	int GetSpeedFactor() const;
	int GetCurTroopNum() const;
	int GetDeadSoldierNum() const;
	int GetInjuredNum() const;
	int GetKillNum() const;
	void IncKillNum(int);
    int GetBornPoint() const;
	//int GetSpotGroupId() const;
	const Vector3& GetIdleBodyPosition();  //ADD
	const int64 GetIdleBodyHeight();
    void UpdateAgent() override;
    void WriteViewInfo(ostream&, TArmyUnitInfo* pArmyUnitInfo = nullptr) const;
	void AddRageSkillUnpausedTarget(const SharedPtr<Unit>&);
    void BehaviourExecuteSkill(int aSkillId, int aDelay);
    void BehaviourMoveToStandPoint(Vector3, int aSpeed = 0, int aRange = 0);
    void BehaviourHide(int aHiding);
    void BehaviourStop(int aStopped);
	bool BehaviourAnim(const char* aAnim);
	void BehaviourAddBuff(int aBuffId, int aBuffLv, int aBTDel = 0);
	void BehaviourRemoveBuff(int aBuffId, int aBuffLv);
	//void AddBarrier(SharedPtr<SceneBarrier> aBarrier);
	//void TickBarrier(int const aDeltaTime);
	void RegisterSkillOnHpEntry(BuffModSkillOnHpEntry*);
	void UnregisterSkillOnHpEntry(BuffModSkillOnHpEntry*);
	void DontSetToBornPosWhenCutscene();
	bool SetToBornPos();
	void SetBehaviourMark(bool);
	int64 CountMaxHpRPG() const;
	//int64 CountMaxHpSLG() const;
	//int64 CountSoldierHpSLG() const;
    void SetAnim(const char* aAnim);
	void SetAnimLenth(int);
	const vector<SharedPtr<Skill> >& GetSkillArr() const;
	int BuildConditionChangeKey(int aMainType, int aRel, int aTar, int64 aParam, const vector<int>& aParamArr);
	void RegisterConditionChange(int aMainType, int aRel, int aTar, int64 aParam, const vector<int>& aParamArr);
	void UnregisterConditionChange(int aMainType, int aRel, int aTar, int64 aParam, const vector<int>& aParamArr);
	void ClearConditionChangeArr();
	void ClearChgDataByBuffSubArr();
	//void RegisterSemiAutoSkills(const vector<SharedPtr<Skill>>&);

	bool HasRefTarget(int aEntityId);
	bool IsInMove2RefST() const;
	int64 TryGetCastRange();
	int TryGetCurrentRefTarget();
	//void TryCleanSemiAuto();
	void AnyToDead(DieCause);
	bool AbleToInterrupt(int aAtkerEnergyLv, bool aIsPhysical);
	void RecordHealOut(int64 aValue);
	bool HasBuffBySubType(BuffSubType);
	bool HasBuffBySubTypes(vector<BuffSubType>&);
	void TryInterruptBossSkill();
	int TryGetDyingEnd();
	uint32 TryGetLargestEnergyLevel();
	uint32 TryGetShrinkControlSum();
	void SetBuffSkillInfo(int, int, int);
	const vector<SharedPtr<BuffSkillInfo>>& GetBuffSkillInfo();
	bool HasShield();
	bool IsArmyShooter();
	
	const DirectedPosition GetBornPointPosition();

	int GetOrigTplId();

	//void TryCleanUpWarRiderRelatedSkills();

	//void TryExtendBattleSoulModeBuffLive(int64);

public:
	int mArmyId = 0;
    int64 mRegister0 = 0; 
    int64 mRegister1 = 0; 

	int64 mTotalPhycialDamage = 0;
	int64 mTotalMagicalDamage = 0;
	int64 mTotalHeal = 0;
	int64 mPhycialDamageUndertake = 0;
	int64 mMagicalDamageUndertake = 0;
	int64 mSkillExecuteCount = 0;

	int64 mProAttTalent = 100;
	int64 mProDefTalent = 100;
	int mDodgeCount = 0;
	int mPhysicalBase = 0;
	int mExemptionCount = 0;
	int mMagicalBase = 0;
	int mParryCount = 0;
	int mResistCount = 0;
	int mCriticalDamageCount = 0;
	int mTotalDamageBase = 0;
	int mCriticalHealCount = 0;
	int mTotalHealBase = 0;
	int mBeCriticalDamageCount = 0;
	int mTotalBeDamageBase = 0;
	int mTTL = 0;
	int64 mTotalSuckBlood = 0;
	int64 mRealHeal = 0;
	int64 mTotalAbsorbBlood = 0;
	WeakPtr<Skill> mAncestorSkill = nullptr;

	const ConfigHero* mConfig = nullptr;  // hold value of Hero.xlsm in Design folder
	const AvatarData* mAvatarConf = nullptr;
	const TUnitInfo* mInfo = nullptr;

	Unit* mSummoner = nullptr;

	bool mIsMale = true;
	bool mFirstHitDone = false;

	EPosType mPosType;

	int mSkillIdSpecial = 0;  //a SkillId that is Free From NoSkill State 

	int mBossDefActive = false;
	int mDefPointNum = 0;
	int mDefType = 0;

	int mLastAppliedSpeedFactor = SPEED_FACTOR_BASE;

	bool mProvideKillRage = true;
	//vector<int> mTextShiftSkill;

	int mTimeWhenDead = 0;			//will not consider field number 

	int64 mExtraCastRange = 0;		//the extra range added by buff 

	ECountry mCountry = ECountry::None;

	UnitType mUnitType = UnitType::Undefined;

	int mPlayerStallCounter = 0;
	int mLastPlayerStallCounter = 0;

private:
    const constexpr static char* FSM_NAME = "Unit";
    const constexpr static char* STATE_BORN = "Born";
    const constexpr static char* STATE_IDLE = "Idle";
    const constexpr static char* STATE_CHOOSESKILL = "ChooseSkill";
    const constexpr static char* STATE_MOVETONEAREST_REFTARGET = "MoveToNearestRefTarget";
    const constexpr static char* STATE_EXECUTESKILL = "ExecuteSkill";
    const constexpr static char* STATE_SKILLRECOVERY = "SkillRecovery";
    const constexpr static char* STATE_BEHIT = "BeHit";
    const constexpr static char* STATE_BECONTROLLED = "BeControlled";
    const constexpr static char* STATE_BATTLEEND = "BattleEnd";
    const constexpr static char* STATE_DEAD = "Dead";
    const constexpr static char* STATE_DYING = "Dying";
    const constexpr static char* STATE_REVIVE = "Revive";
    const constexpr static char* STATE_BEHAVIOUR = "Behaviour";
    const constexpr static char* SUMMONED_DUMMY_NAME = "Avatar_dummy_01_low";
    SharedPtr<Fsm> mFsm;
    string mFsmName;
    State* mStateBeControlled;
    State* mStateBehaviour;
    State* mStateIdle;
    State* mStateDead;
	State* mStateDying;
	State* mStateBeHit;
	State* mStateSkillRecovery;
	State* mStateExecuteSkill;
	State* mStateMoveToRef;
	State* mStateChooseSkill;
	State* mRevive;
    Transition* mTransResetToIdle;//OK
    Transition* mTransBehaviour;//OK
	Transition* mTransBehaviourToIdle;//OK
    Transition* mTransCutscene;//OK
    //Transition* mTransBeHit;
    //Transition* mTransBeHitEnd;
    Transition* mTransBeControlled;//OK
    Transition* mTransBeControlledEnd;//OK
    Transition* mTransDead;//OK
    Transition* mTransRealDead;//OK
    Transition* mTransAnyToDead;//OK
    Transition* mTransRevive;//OK
	Transition* mTransMoveToRefTarget; 
	//Transition* mTransCantMoveToRefTarget;
	//Transition* mTransReturnBehaviourStop;
	//Transition* mTransReturnDying;
	//Transition* mTranseAutoSkillRecovery;
	Transition* mTransAutoMoveToRefTarget;//OK
    Transition* mTransNoSkillToExecute;//OK
    Transition* mTransSkillEnded;//OK
    Transition* mTransToExecuteSkill;//OK
	//Transition* mTransReachRefAndRecovered;
	//Transition* mTransReachRefNotRecovered;
	//Transition* mTransRecoverLostRefTarget;
	Transition* mTransChooseToExecute;//OK

	int mDeadStateId = 0;

    int mTplId = 0;
	int mHid = 0;
	bool mIsPVP = false;

	//static int slgCoef1, slgCoef2, slgCoef3, slgCoef4, slgCoef5, slgCoef6;  //hold slg coef values from battleConfig

	int mTroopId = 0;  //SLG related data
	int mTroopNum = 0;
	int mCurTroopNum = 0;   // curTroopNum + mInjuredNum + DeadNum == TroopNum
	int mInjuredNum = 0;
	int mDeadNum = 0;
	int64 mSoldierStdHp = 0;   //standard soldier hp for this battle
	int mDeathRate = 0;
	int mKillNum = 0;

    int mLevel = 0;
    int64 mHp = 0;   //current Hp
    int64 mMaxHp = 0;  //uplimits
	int64 mRage = 0;  //current Rage
	int64 mRageSkillThreshold = 0; //Rage threshold used to judge one can or can not Do RageSkill right now
	int64 mMaxRage = 0;
	int64 mPhyicalShield = 0;
	int64 mMagicalShield = 0;
	int64 mUniversalShield = 0;
	DieCause mDieCause;
    Army* mArmy = nullptr;
    Agent* mAgent = nullptr;
    bool mOverlap = false;
    Cylinder* mBV = nullptr;
    int mUnitTime = 0;//localized Unit time in ms
    int mActionSpeedFactor = 0;
    int mRealSpeedFactor = 0;
    int mHitTimeLength = 0;
	int mDownTimeLength = 0;
	int mDownTimeLength2 = 0;
	int mKnockTimeLength = 0;
	int mKnockTimeLength2 = 0;
    SharedPtr<TimerMgr> mTimerMgr = nullptr;
    SharedPtr<BuffMgr> mBuffMgr = nullptr;
    int mBornPoint = 0;
    SharedPtr<string> mAvatarName = nullptr;
	bool mIsDummy = false;
	bool mIsBorn = false;
	bool mIsDeleted = false;
	bool mDontInitToBornPos = false;
    SharedPtr<Timer<Unit> > mTimedLife = nullptr;
    SharedPtr<Timer<Unit> > mBeHitTimer = nullptr;  //TODO: DELETE IT
    int64 mFallSpeed = 0;
    bool mFloatWithoutBeingMoved = false;  //denotes that one is floating Not because of Being controlled or so 
    int64 mRecoveryTime = 0;
	SharedPtr<Unit> mLastNormalTarget = nullptr;
	SharedPtr<Unit> mLastRefTarget = nullptr;
	int64 mLastCastRange = 0;
	SharedPtr<Unit> mSkillSourceUtilizer = nullptr;
    Unit* mKiller = nullptr;

    bool mClearOnCutscene = false;
    vector<int64> mAttrArr;
	vector<pair<int, int>> mImmueBuffArr;
    vector<int> mImmueBuffTypeArr;
    vector<int> mImmueBuffSubTypeArr;
	vector<pair<int, int>> mImmueSkillArr;
    vector<int> mImmueSkillTypeArr;
	vector<int> mImmuePropertyArr;
    vector<int> mStateAdjustPropertyArr;
    vector<ControlToken*> mBeControlledStack;
    vector<SharedPtr<ShapeShift>> mShapeShiftStack;
	vector<BuffModSkillOnHpEntry*> mTriggerOnHpSkillArr;
	vector<ChangeDataByBuffSub*> mTableChgDataByBuffSub;
	//vector<pair<int, int>> mTextShiftCounter;

	int64 mDamageInTotal = 0;
	int64 mDamageInWithOverflow = 0;
	int64 mDamageOutTotal = 0;
	int64 mHealOutTotal = 0;

	vector<SharedPtr<Skill>> mChainSkillArr;  //a list of normal skills that will execute in loop 
	vector<int> mChainSkillOrder;
	int mChainSkillIndex = 0;
	int mAdvLevel = 0;
	int mStar = 0;

	//vector<SharedPtr<Skill>> mBattleSoulTriggerArr; //武魂真身触发技 
	//SharedPtr<Skill> mBattleSoulSkill;	 //武魂真身变身技能 
	//vector<int> mBattleSoulExcludeSkills; //武魂真身需要排除的技能(普攻+大招) 

    vector<SharedPtr<Skill> > mSkillArr; //所有技能的数组 
	//vector<SharedPtr<Skill>> mSemiAutoArr;  //store current semi auto skills 
    SharedPtr<Skill> mRageSkill = nullptr;  //hold RageSkill of this Unit
	vector<SharedPtr<Skill>> mRageSkillArr; //hold all rage skill of this unit
	//SharedPtr<Skill> mUnparalleledSkill = nullptr;
    vector<SharedPtr<Skill> > mTriggerSkillArr;
	vector<SharedPtr<Skill>> mRandomNormalSkillArr; 
    SharedPtr<Skill> mCurSkill = nullptr; //当前执行的技能 
    SharedPtr<Skill> mChoosedSkill = nullptr; //手动选择的技能

    SharedPtr<SkillExecutor> mCurSkillExecutor = nullptr; //当前正在执行的带动作的技能，一般应该是主动选择的技能 
    vector<SharedPtr<SkillExecutor> > mSkillExecutorArr;
	//vector<SharedPtr<SceneBarrier>> mSceneBarrierArr;  //for instant SommonBarrier skills, their summons will be placed here
	//int mNoTargetCounter = 0; //用于记录连续多少次没有选择到目标
	//int mNormalAtkNum = 0;
	int mNormalAtkNumBeforeChangeAvatar = 0;
	//int mCurrentSkillNum = 0;
	//int mNextSemiAutoTime = 0;   //the time at which next semi auto skill will be executed 
    bool mRageSkillManualReady = false; //flag variable for Manually Execute Rageskill, denotes the validation of cur state to execute its rage skill
    bool mRageSkillAutoReady = false;
	//bool mUnparalleledSkillReady = false;
	//bool mBattleSoulSkillAutoReady = false;
	
    RageSkillExecuteState* mRageSkillExecuteState = nullptr;

    const IFunctionContainer<void, SharedPtr<Unit> >* mOnMoveBySkillCancel = nullptr;
    vector<SharedPtr<ControlToken>> mControlTokens; 
	vector<SharedPtr<ControlToken>> mControlStateByHitArr;
	vector<ConditionChangeData*> mConditionChangeArr;
    int mTauntedTargetBuffId = 0;
    //BuffModShapeshift* mShapeshiftMod = nullptr;
	unordered_map<int, int > mSpecifyBeTargetSkillMap;

    SharedPtr<Skill> mBehaviourSkill = nullptr;
    Vector3 mBehaviourMoveTarget;

	Vector3 mLastPosition;

	bool mAbleToChooseSkill = false;

	void BreakPlayerStall();
	bool ActionTickIdle(int);
    bool ActionChooseSkill(int);
    bool ActionMoveToRefTarget(int);
	void ActionExitMoveToRefTarget();
    void ActionExecuteSkill();
    void ActionExitExecuteSkill();	
	void ActionEnterSkillRecovery();
    void ActionExitSkillRecovery();
    bool ActionTickSkillRecovery(int);
	void AvoidOverlap2(int const);
	void DoAvoidOverlap(const Vector3* aFinalPos = nullptr, int64 aMoveDist = 0, int aDeltaTime = 0, const Vector3* aMyTarget = nullptr);
	bool IsSameDir(Vector3& aDir1, Vector3& aDir2);
    void CancelOverlapMove();
    void ActionEnterDead();
	void ActionEnterDying();
    void ActionEnterBorn();
    void ActionEnterRevive();
    bool ActionTickBeControlled(int);
    bool ActionTickDead(int);
    bool ActionTickDying(int);
	void doBehaviourStop();

	void DetermineDeathAnim(Unit*);
	
    //bool CallbackBeHitEnded(Timer<Unit>&);
	bool CleanUpBeCtrlState(Timer<Unit>&);
    bool TimedUnitExpire(Timer<Unit>&);

    bool CallbackBehaviourExecuteSkill(Timer<Unit>&);
	bool CallbackBehaviourStop(Timer<Unit>&);
    bool ActionBehaviourMoveToStandPoint(int aDeltaTime);
    bool ActionBehaviourStopped(int aDeltaTime);

	bool CondiDying(bool);
	bool CondiTargetInRange(bool);
	bool CondiTargetOutOfRange(bool);

	void InitFsmCommon();
	void LinkFsmCommon();
    void InitFsm();
    void InitPlayerFsm();
    void InitFields(Army&, BattleViewOutput&, PhysicsSystem&);
    void InitPhysics();
    void InitAvatar();
    void LoadConfig(int);
	void LoadChainSkillOrder(int aIndex = 0);
	const vector<vector<int64>>& getChainListConf(int aIndex);

	SharedPtr<Skill> GetRageSkill();

    void SkillInterrupted(const SharedPtr<SkillExecutor>&, bool aIsPassive = false, bool aNoEvent = false);

    void DealingDamage(int64, int64, int64, Unit*, bool);
    int64 DamageBy(int64, bool aIgnoreRage = false);
	//inline void SlgDamage(int);
    int64 HealBy(int64);
	//inline void SlgHeal();
    bool CheckRageSkill();
    //int CheckSemiAutoSkill(bool aManual = false);
	//void CheckUnparalleledSkill();
	//void CheckBattleSoulSkill();
    
    void CheckSkillExecutor();
	void IncreaseSkillIndex();
	Vector3  mSocketBody;   // derived directly from animConf.SocketPosition.Idel
	Vector3  mHitPosition;  // trans mSocketBody to World space
	int64 mBehaviourSpeed = 0;
	int64 mBehaviourRange = 0;
	string mBehaviourAnim = "";
	bool mBehaviourMark = false;  //true -> unit is added by behaviour
	int mNumOfAvoidOverlapMovement = 0;
	Vector3 mLastDir;

	//bool mIsManualSemiAuto = false;
	RageSkillStatus mRageSkillStatus;
	//RageSkillStatus mUnparallelSkillStatus;
	//RageSkillStatus mBattleSoulSkillStatus;
	vector<SharedPtr<BuffSkillInfo>> mBuffSkillStatistics;
};