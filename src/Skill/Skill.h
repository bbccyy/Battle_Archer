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
#include <vector>
#include <unordered_set>
#include "Framework/SharedPool.h"
#include "Framework/Transform.h"
#include "module/SkillData.pb.h"
#include "module/AvatarData.pb.h"
#include "SkillDefine.h"
#include "RefTarget.h"
#include "Framework/FunctionContainer.h"

using namespace pb;
using namespace std;

class Unit;
class SkillExecutor;
class HitHandler;
struct BattleEvent;
enum class EPosType;

struct SkillCount
{
public:
    int mTotal;  //range scope: all Screen/Field until the end of battle
    int mScreenTotal;  //range scope: within a Screen/Field
	int mTotal2;    //For army2 use
	int mScreenTotal2;
};

const AnimData* FindAnimConf(const string& aAvatarName, const string& aAnimName);

//技能的持续性数据，单次执行的相关操作由SkillExecutor负责
class Skill : public EnableSharedFromThis<Skill>, public IPoolable
{
public:
    ~Skill();
    int Init( SharedPtr<Unit> aUnit, int aSkillId, int aSkillLevel, WeakPtr<Skill> aParentSkill = WeakPtr<Skill>());
	void CopyInit(SharedPtr<Unit> aUnit, const Skill*);
    void Reset();
	void Replace(int);
	bool CheckReplacement();

	void TryTriggerSkill(const BattleEvent&);
	bool RegisterListener();
	bool UnRegisterListener();

    bool mNeedDead = false;
	bool mAutoRageSkill = false;
	bool mSubRageSmoothly = false;
	int mSubRageTime = 0;
	bool mEnemyShowRage = false;
	bool mIsBlockPriority = false;
	bool mIsIgnoreShield = false;
	bool mIsIgnoreInterruptEffect = false;
	bool mRageSkillInterruptable = false;

	bool isTriggeredByBuff = false;  //a flag records real skill executor(either buff or unit)

	bool isPositiveType();

    bool RefreshRefTarget();
    bool TryExecute(int aDelay, WeakPtr<SkillExecutor> aParentExecutor, const SharedPtr<Unit>& aSourceUtilizer, const SharedPtr<SkillExecutor> aCurExecutor, SharedPtr<Unit> aReflecter = nullptr);
    
	CheckResult CanExecute() const;
	CheckResult CanExecuteCommon() const;
	bool CanExecuteSpecial() const;
	bool PassTriggerChance() const;
	CheckResult CanExecuteNow() const; //选择好技能后，在执行之前还需要做的瞬间检查  
    int GetId() const;
    int GetTimeLength() const;
    int GetStandTime() const;
	int GetPriority() const;
	bool HasDefPoint() const;
	int GetDefPointBuffId() const;
	int GetDefPointDuration() const;
    const char* GetAnimName() const;
    bool IsNormalSkill() const;
    bool IsNonNormalNonRageAnimSkill() const;
	bool IsPartOfRageSkill() const;
	bool IsRageSkill() const;
	bool IsMasterRageSkill() const;
	bool IsUnparallelledRageSkill() const;
	bool IsPhysicalSkill() const;
	bool IsChildSkill() const;
    bool HasAnim() const;
	bool HasSemiAutoSkillArr() const;
    const vector<SharedPtr<Skill> >& GetChildSkill() const;
    const vector<SharedPtr<Skill> >& GetProbabilisticSkill() const;
    const vector<SharedPtr<Skill> >& GetSemiAutoSkill() const;
    int GetLastExecuteNormalAtkNum() const;
	void ResetLastExecuteNormalAtkNum();
    int GetCastRange() const;
    void OffsetCD(int);
    void ResetCD();
    const SkillData* GetSkillConf() const;
    const AnimData* GetAnimConf() const;
    int GetLevel() const;
	int GetLevelMinus() const;
    const SharedPtr<HitHandler> FetchHitHandler();
	void ReturnHitHandler(SharedPtr<HitHandler> aHitHandler);
    bool IsTargetDeadBody() const;
    bool HasRefTarget() const;
	void CleanRefTargetArr();
	bool HasEffTarget() const;
	bool HasProjectile() const;
    bool IsRefTargetInRange() const;
    bool IsRefTargetInRangeDynamic();
    vector<RefTarget>& GetRefTargetArr();
    void SetReflectRefTargetArr(const SharedPtr<Unit> aUnit);
    const RefTarget& GetNearestRefTarget() const;
	const RefTarget* GetNearestRefTargetPtr() const;
	vector<SharedPtr<Unit> >& GetEffTargetArr();
    bool CheckTriggerWithCountryHero() const;
    bool CheckArmySubRage(int aArmyId) const;
    bool CheckTriggerWithCountryHeroRuntime() const;
    bool CheckTriggerWithSkill(int aSkillId) const;
    bool CheckEventSubWithSkill(int aSkillId) const;
    bool CheckEventBuffSub(int aBuffSubType) const;
	bool CheckEventDeathSub(int) const;
	int GetPerfectInterruptDuration() const;
    void tryExecuteSkill(bool aNeedInterrupt);
	void DealLockon();
	int64 GetDist2(const Vector3&, const Vector3&);
	int GetNearestFromRefTargetArr();
	WeakPtr<Skill> GetParentSkill();
	void SetAncestorSkill(WeakPtr<Skill> aSkill);
	WeakPtr<Skill> GetAncestorSkill();
	SharedPtr<Unit> GetOwner();
	const SharedPtr<Unit> GetConstOwner() const;

	int mEnergyLv = 1;
	int mEnergyLvMove = 1;
	bool mGroundMeshSkill = false;

	int mBeginCount = 0;  //技能释放次数 
	int mEffectTargetCount = 0;  //生效目标总数 
	int mTotalPhysicalDamge = 0;
	int mTotalMagicalDamge = 0;
	int mTotalHeal = 0;
	int mTotalSuckBlood = 0;
	int mCollisionCount = 0;  //贯穿个数 

	int mSkillMainType = 0;
	int mSkillChannelType = 0;
	WeakPtr<Skill> mAncestorSkill = nullptr;

	bool mIsSemiAutoSkill = false;
	int mSemiAutoTTL = 0;
	int mSemiAutoGap = 0;

	int64 mTriggerRegister1 = 0;
	int64 mTriggerRegister2 = 0;

	const vector<EPosType>& GetRefPosType() const;
	const vector<EPosType>& GetEffPosType() const;
	const vector<EPosType>& GetRerOrEffPosType(bool aIsRef) const;

	bool mIsArmySkill = false;
	int mArmySkillTiming = 0;
	int mArmySkillStrategy = 0;

	int64 mExtraDmgCoef = DENOM;

	vector<int> mProbabilisticParams;

	bool mWarRiderRelated = false;
	bool mBattleSoulRelated = false;
    
protected:
    int DoInit();
    void InitChildSkill();
    
private:
    SharedPtr<Unit> mOwner;
    WeakPtr<Skill> mParentSkill;

	WeakPtr<Unit> mLockonTarget;

	vector<EPosType> mRefPos;
	vector<EPosType> mEffPos;

    int mSkillId = 0;
    int mLevel = 0;
	int mPriority = 0;
	bool mLockon = false;
	bool mIsPartOfRageSkill = false;

	int mEventKey = 0;

	int mEventRelation = 0; //who cast: ie self, enemy, both and so
	int mCastType = 0; //general type, including [non-trigger type such as normal, rage, non-normal...] AND [all trigger type]  0~any
	int mEventMajor = 0;
	int mEventSub = 0;  //sub type(used to distinguish skills under the same major type)  0~99

	ESkillSubType mSkillSubType = ESkillSubTypeDamage;

    const SkillData* mSkillConf = nullptr;
    const AnimData* mAnimConf = nullptr;
    int mTimeLength = 0;
    int mStandTime = 0;  //interval time after anim Done but before skill Done
    int64 mCastRange = 0;
	vector<SharedPtr<HitHandler> > mHitHandlerArr;

    vector<SharedPtr<Skill> > mChildSkillArr;
	vector<SharedPtr<Skill> > mProbabilisticSkillArr;

	vector<SharedPtr<Skill> > mSemiAutoSkillArr;

    int mLastExecuteTime = 0;
    int mLastExecuteNormalAtkNum = 0; //上次执行时，owner的普攻次数
    int mCDTime = 0;

    ETriggerMajor mTriggerType;  //TODO: Delete it? 

    vector<RefTarget> mRefTargetArr;
	vector<SharedPtr<Unit> > mEffTargetArr;  //ADD
    int mNearestRefTargetIndex = 0;
	int64 mRealCastRange = 0;
    bool mRefTargetInRange = false;

	bool mFocuseOnRand = true;  //在技能真正释放前，保持每次tick选择的random目标一致 
	bool mIsPositiveType = false;
	bool mIsIngoreNoSkill = false;

	const IFunctionContainer<void, const BattleEvent&>* mFunc = nullptr;

};