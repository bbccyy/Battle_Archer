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
* @brief
*
**/

#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Framework/SharedPtr.h"
#include "Framework/StateMachine.h"
#include "Skill/Skill.h"
#include "Framework/Timer.h"
#include "module/SceneConf3d.pb.h"
#include "module/BuffData.pb.h"
#include "Framework/Transform.h"
#include "Entity/DestructableObject.h"
#include "Framework/EventDispatcher.h"
#include "SceneMgr/SceneManager.h"
#include <ctime>


using std::vector;
using std::unordered_map;
using std::unordered_set;

class ConfigBattleInfo;

namespace pb
{
    class TBattleArgs;
	class TBattleResult;
    class TSceneInfo;
    class TArmyInfo;
    class TArmyInfoAfterBattle;
	class TUnitStatistics;
    class PbVector3;
    class PbVector3_Int;
    class Destructable;
	class BuffData;
	class TBattleViewCmd;
	class TBattleFieldInput;
	class TUnitInfo;
	class TSkillCount;
	class TSkillCountInfo;
	//class TWheelWarRidingInfo;
}
using pb::SceneConf3d;
using pb::FieldConf3;
using pb::TBattleArgs;
using pb::TBattleResult;
using pb::TSceneInfo;
using pb::TArmyInfo;
using pb::TArmyInfoAfterBattle;
using pb::PbVector3;
using pb::PbVector3_Int;
using pb::Destructable;
using pb::BuffData;
using pb::TBattleViewCmd;
using pb::TBattleFieldInput;
using pb::TUnitInfo;
using pb::TSkillCount;
using pb::TSkillCountInfo;
//using pb::TWheelWarRidingInfo;

class MersenneTwister;
class BattleViewOutput;
class PhysicsSystem;
class Army;
class Unit;
class SkillCarrier;
struct SkillCount;
struct UnitConf;
class BattleInstance;
class Region;
class PathFindingMgr;

enum class EActiveBaseType
{
	None = 0,
	Melee = 1,
	Distance = 2,
};

enum class EBattleInput
{
	None = 0,
	ExecuteSkill = 1,
	ExecuteSuper = 2,
	EnableAuto = 3,
	DisableAuto = 4,
	UnregisterSemi = 5,
	InitNextWaveTD = 6,
	AddUnitTD = 7,
	DeleteUnitTD = 8,
	DeleteAliveUnitTD = 9,
	InitNextWaveWithBonusTD = 10,
	ExecuteBattleSoul = 11,
};

enum class EBattleResult
{
    None = 0,
    Timeup,
    Victory,
    Lose,
    Error
};
static const char* EBattleResultNames[] = { "None", "Timeup", "Victory", "Lose", "Error" };

struct DirectedPosition
{
public:
	DirectedPosition() = default;
	~DirectedPosition()
	{
	};
	static DirectedPosition Create(const PbVector3_Int&, const PbVector3_Int&, const string&, int aIdx = 0);
	static DirectedPosition Create(const Vector3&, const Vector3&);
public:
	Vector3 mPos;
	Vector3 mRot;
	string mName;

	int mGroupId = 0;

};

enum class ERageSkillExecuteStatus
{
	WaitForOtherArmy,
    Show,
	WaitForInput,  //展示结束，目标还没有选好   
    Begin,
    //Emit,  暂时没用
    End
};

struct TFieldInput
{
public:
	int eid = 0;
	int event = 0;
	int fieldnum = 0;
	int frametime = 0;
	int index = 0;
	int data1 = 0;
};

struct BattleEvent : public EnableSharedFromThis<BattleEvent>, IPoolable
{
public:
	void Reset();
	int GetEventId() const;
	void SetEventId(int aKey);
	int mArmyId;  //will store armyId for determing self or enemy
	int mEntityId;  //entityId
	int64 mRegister0;  //skillId / buffId
	int64 mRegister1;  //payload_1
	int64 mRegister2;  //payload_1
private:
	int mKey;
};

struct RageSkillExecuteState : public EnableSharedFromThis<RageSkillExecuteState>, IPoolable
{
public:
    void Reset();
    Unit* mUtilizer;
    vector<SharedPtr<Unit> > mUnpausedTargetArr;//被大招命中后，根据配置脱离暂停状态的单位 
    ERageSkillExecuteStatus mStatus;
};

class BattleInstance
{
public:
    BattleInstance();
    BattleInstance(const BattleInstance&) = delete;
    BattleInstance& operator=(const BattleInstance&) = delete;
    ~BattleInstance();
public:
    static int GravityAccel;//角色浮空时的默认下落加速度 
    static int HpToRageNum;//受伤害转换为怒气时血量损失的单位数量 
    static int HpToRageDenom;//受伤害转换为怒气时怒气增加的单位数量 
	static int KillToRage;//击倒对方获取的怒气绝对值 
	static int AvoidOverlapCoef1;
	static int AvoidOverlapCoef2;
	static int AvoidOverlapCoef3;
	static int AvoidOverlapCoef4;
	static int AvoidOverlapCoef5;

	static int BlockRate;  //格挡百分比 

	static vector<int64> ATTR_LIMITS;

	static vector<int64> BossHpRange;
	static vector<int> BossHpRangeGrowth;
	static Vector2 gVectorZero;
	static DirectedPosition mDefaultDirectedPosition;
	static int64 DamageUpLimit;
	static vector<int64> ATTR_LIMITS_UP;

	int mBattleId = 0;

	vector<int64> BossAttributeAdd;

	int64 mBossTotalDamageUndertake = 0;
	int mBossGrowthLevel = 0;
	bool mIsBossGrowth = false;

	Vector3 mPlayerPosition;
	Vector3 mPlayerRotation;

	bool mRecordMode = true;
	int GetUserInputSize();
	const TBattleFieldInput& GetUserInput(int);
	// exposure the methond for lua using
	void RecordUserInput(int aEid, EBattleInput aEvent, int aData = 0) ;

	static void LoadGlobalConfig();
	static int GenerateEventKey(int aMajorKey, int aSubKey = 0);
	bool TickEnterField(double aDeltaTimeS);
    void OnVTick(double aDeltaTimeS);// (variable framerate)Tick
    void OnTick();// (fixed framerate)Tick
	void RunBattleToEnd();

	void DispatchEvent(int aKey, int aArmyId, int aEntityId, int64 aReg0 = 0, int64 aReg1 = 0, int64 aReg2 = 0);
	void DoDispatchEvent(const BattleEvent&);
	void AddListener(int, const IFunctionContainer<void, const BattleEvent&>*);
	void RemoveListener(int, const IFunctionContainer<void, const BattleEvent&>*);
    
	void SetRandSeed(int);

	int InitWithPbObjArcher(TBattleArgs* aPbMsg);
	int InitWithPbObj(TBattleArgs* aPbMsg);
    int InitWithPbStr(const char* aBattleArgs, int aBattleArgsLen);
	int InitWithRetPbStr(const char* aBattleRes, int aBattleResLen);
    string ReportResult();
	TBattleResult* ReportResultPb(bool aNeedCMD);
	void TryShowRageSkill(Unit&);
    void TryBeginRageSkill(Unit&);  
	bool IsInRageSkill(int) const;
	bool IsFieldEnd() const;
    void EndRageSkill(Unit&);
    int RageSkillInput();
    void RageSkillInputEnd();
	int GetCurField() const;
	bool NeedDoStatistics() const;
	bool UseAIPath() const;
	
	bool IsPVE() const;
	bool IsSLG() const;
    bool IsAuto() const;
    void SetAuto(bool aAuto);
    void ResetTimelimit(int aTimeMs);
    int GetFrameTime() const;
    int GetGameTime() const;
    TimerMgr* GetTimerMgr() const;
    SharedPtr<SkillCarrier> AddSkillCarrier();
	void CleanUpAllSkillCarrier();
    int Rand(int aN) const;
    const Army& TargetArmy(Unit&) const;
    const Army& GetArmy1() const;
    const Army& GetArmy2() const;
    Army& GetArmy(int aArmyId);
	const Army& GetEnemyArmy(int aEntityId) const;
    bool RestrainToBattleArea(const Vector3&, const Vector3&, int, Vector3*);
    bool RestrainWithBlockLines(const Vector3&, const Vector3&, int, Vector3*);
	void TryResetDying();

    int BehaviourSelectUnitByHp(int aArmyId, int aCheckMost);
	int BehaviourSelectUnitByLostHp(int aArmyId, int aCheckMost);
	int BehaviourSelectUnitByRage(int aArmyId, int aCheckMost);
	int BehaviourSelectUnitById(int aArmyId, int aTplId);
	void BehaviourSelectUnitByAllId(int aArmyId, int aTplId, vector<int>& aEntityIdArr);
    void BehaviourSelectAllUnit(int aArmyId, vector<int>& aEntityIdArr);
	void BehaviourSelectAllUnitContantHide(int aArmyId, vector<int>& aEntityIdArr);
    void BehaviourSelectUnitBySpawnPointName(int aArmyId, const char* aSpawnPointName, vector<int>& aEntityIdArr);
	void BehaviourGotoResult(int aIsVictory);
	void BehaviourGotoNextField(void);
	int BehaviourAddUnit(int aArmyId, int aTplId, int aLevel, int aPosX, int aPosY, int aPosZ, int aDirX, int aDirY, int aDirZ, int aShow, int aIsBoss);
    int BehaviourHideUnit(int aEntityId, int aHiding);
    int BehaviourDeleteUnit(int aEntityId);
    int BehaviourStopUnit(int aEntityId, int aStopped);
	int BehaviourUnitAnim(int aEntityId, const char* aAnim);
	int BehaviourAddBuff(int aEntityId, int aBuffId, int aBuffLv, int aDelete, int aDeletaByBT);
	int BehaviourObstacleVisible(const char* aObstacleName, int aIsVisible);
    int BehaviourExecuteSkill(int aEntityId, int aSkillId, int aDelay);
	int BehaviourMoveToStandPoint(int aEntityId, const char* aStandPointName, int aSpeed, int aTargetId, int aRange, int aOffsetX, int aOffsetY, int aOffsetZ);
	int BehaviourSyncLocation(int aEntityId, int aPosX, int aPosY, int aPosZ);
	int BehaviourSyncDirection(int aEntityId, int aDirX, int aDirY, int aDirZ);
	int BehaviourSetTime(int aTime);
	int BehaviourSetExtraTime(int aTime);

    void AddSkillCount(int aSkillId, int aArmyId = 1);
    void SubSkillCount(int aSkillId, int aArmyId = 1);
    SkillCount& GetSkillCount(int aSkillId);
    void SetSkillCount(int aSkillId, int aCt);
    int ExecuteRageSkill(int aEntityId);

	vector<TBattleViewCmd*>& FetchViewCmd();
    EBattleResult GetResultType() const;
	SharedPtr<BattleViewOutput> GetView() const;
	SharedPtr<PhysicsSystem> GetPhysics() const;
	SharedPtr<Unit> GetUnitByTplId(int aTplId) const;
	SharedPtr<Unit> GetUnitByEntityId(int aEntityId, bool aIncludeDead = false) const;
	void GetAllActiveUnits(vector<Unit*>&);
	void UnpauseDummyUnit(Unit*);
	void UnpauseUnit(Unit*, bool);
	void PauseUnit(Unit*);
	int RegisterDyingTime(int aDuration, int aArmyId);
	void CleanDyingTime(int aEndTime, int aArmyId);
	bool IsDyingValid(int aArmyId);
	void TriggerDamageCopy(int64 aDamage, int aSourceUtilizerId, int buffId);
	void TryGetSkillsFromArgs(vector<int>& aSkills, int aTplId, int aArmyId);
	vector<DirectedPosition>& GetArmy1BornPointArr();
	//vector<vector<DirectedPosition>>& GetSumSpotArrByName(const string&);
	int GetBossGrowthLevel(int aArmyId);

	SharedPtr<Unit> GetOneRandomUnit(int aMyArmy, int aWhichArmy, int aExcludeId);

	PathFindingMgr* GetPathMgr();

	void FilterBlockLine(const Vector3& aStart, const Vector3& aEnd, vector<int>& aBlockLineArr);

	void UpdatePlayerPositionAndRotation();

private:
    const constexpr static char* FSM_NAME = "Battle";
    const constexpr static char* STATE_ENTERFIELD = "EnterField";
    const constexpr static char* STATE_NORMAL = "Normal";
    const constexpr static char* STATE_CUTSCENE = "Cutscene";
    const constexpr static char* STATE_RAGEINPUT = "RageInput";
    const constexpr static char* STATE_ENDSHOW = "EndShow";
    const constexpr static char* STATE_ERROR = "Error";
    const constexpr static char* FIELD_CONF_COL_NAME = "Confname";

	int mUserInputIndex = 0;
	vector<TFieldInput> mRecordInputArr;

	TBattleResult* mResult = nullptr;
	//TWheelWarRidingInfo* mWarRider = nullptr;
	bool hasReported = false;

    bool mAuto;
	bool mNeedDoStatistics;
	bool mAIPath = false;

    SharedPtr<Fsm> mFsm;
    SharedPtr<TBattleArgs> mArgs;

	//PathFindingMgr* mPathMgr = nullptr;

	SceneManager* mSceneMgr = nullptr;

	int64 mNodeSize = 50000;
	
	//bool mIsNoBlackScreen = false;

    bool mIsPVE = false;
    bool mIsSLG = false;
	int mBattleStarter = 0;
    int mArmy1Index;
    int mArmy2Index;

	int mArmy1WinCt = 0;
	int mArmy2WinCt = 0;
	int mTotalRound = 0;
    SharedPtr<BattleViewOutput> mView;
    //int mSceneMgr->TotalFieldNum;
    EBattleResult mBattleResult;
    vector<FieldConf3> mFieldConfArr;
    vector<uint32> mTimeLimitArr;
    vector<Vector3> mFieldAreaPointArr;

    vector<vector<Vector3>> mFieldBlockLineArr;		//store a list of BlockLine, take subscript as Index
	vector<vector<int>> mColStrips;		//index matters 
	vector<vector<int>> mRowStrips;
	int64 mStripD = 0;					//the width of strip 
	int mHalfCol = 0;
	int mHalfRow = 0;

    SharedPtr<MersenneTwister> mRand;
    SharedPtr<PhysicsSystem> mPhysics;

	SharedPtr<EventDispatcher<int, const BattleEvent&>> mBattleEventDispatcher;  //TODO: add event depth in skill 
    
    unordered_set<RageSkillExecuteState*> mRageSkillExecuteStateArr;
    vector<Unit*> mRageSkillActiveUtilizerArr;
	unordered_set<Unit*> mRageSkillPauseUnitArr;
    vector<SharedPtr<SkillCarrier> > mRageSkillCarrierArr;
    Army* mRageSkillMaskArmy;  // the Army that someone belongs to which has start Rage Skill

    int mFixedFrameDelta;// (fixed framerate) time delta(ms)
    int mVFrameTimeRemain;// (variable framerate) time remain(ms)
    int mFrameTime;// (fixed framerate) accumulated time(ms)
	int mGameTime;

    int mTimeLimit;
	int mTimeExtra;
    //int mSceneMgr->CurSceneId;
    FieldConf3* mFieldConf;
    SharedPtr<Army> mArmy1;
    SharedPtr<Army> mArmy2;
    vector<DirectedPosition> mBornPointArr1;
    vector<DirectedPosition> mBornPointArr2;
    vector<DirectedPosition> mStandPointArr;
    vector<DirectedPosition> mCenterPointArr;
	vector<DirectedPosition> mSummonPointArr1;
	vector<DirectedPosition> mSummonPointArr2;
    vector<SharedPtr<SkillCarrier> > mSkillCarrierArr;
    unordered_map<int, SkillCount> mSkillExecCountMap;
    vector<SharedPtr<DestructableObject>> mDestructableArr;
    SharedPtr<TimerMgr> mTimerMgr;


    State* mStateNormal;
    State* mStateRageInput;
	State* mStateEnterField;
	State* mStateCutscene;
	State* mStateEndShow;

    Transition* mTransRageInputBegin;
    Transition* mTransRageInputEnd;
    Transition* mTransCutsceneEnd;
    Transition* mTransBattleEnd;
    Transition* mTransBattleError;

	int mArmy1DyingEnd = 0;
	int mArmy2DyingEnd = 0;

    bool CondiBattleEnd(bool);
    bool CondiCurrentFieldEnd(bool);
    void InitFsm();
    void InitArmyWith(const SharedPtr<Army>&, const TArmyInfo&);
    void RecordFieldStatus();
    void ActionEnterError();
    void ActionEnterCutscene();
    void ActionEnterNextField();
    void ActionEnterEndShow();
    bool ActionTickNormal(int aFrameDelta);
    bool ActionTickRageSkillExecute(int);
	bool ActionTickCutscene(int);
    void ActionExitRageInput();
	void OnTickBossGrowth();

	//void OnTickMeleeRingMgr();

    void InitNextField();
    void InitNextFieldArcher();

    void PauseUnitWhenSomeoneStartRageSkill(SharedPtr<Army>, Unit*);
    void WhenSomeoneStartRageSkill(RageSkillExecuteState*);
    
    void RageSkillMaskEnd();
    void FillArmyInfo(TArmyInfoAfterBattle*, const vector<SharedPtr<Unit>>& aUnitList) const;
	void FillUnitInfo(TUnitStatistics*, Unit*) const;
	void FillSkillInfo(TUnitStatistics*, Unit*) const;
	void FillSkillSingle(TUnitStatistics*, Skill*) const;
	void LoadBossGrowthAttr();

};