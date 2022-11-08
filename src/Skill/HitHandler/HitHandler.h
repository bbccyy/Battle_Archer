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

#include "Define.h"
#include "Framework/SharedPool.h"
#include "Framework/Transform.h"
#include "Skill/SkillDefine.h"
#include "module/SkillData.pb.h"



#include <vector>
using namespace std;
using namespace pb;

class Unit;
class Skill;
class SkillCarrier;
enum class BeHitType;


class HitHandler : public IPoolable
{
public:
    HitHandler()
        : mDmgOrHealHandler(nullptr)
        , mIsDurative(false)
		, mIsAccessional(false)
    {
    }
	void Reset();
    virtual bool CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier);
    virtual void BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr);
    virtual void OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier) = 0;
    virtual bool OnTick(int aDeltaTime){return false;}
    
    virtual void AfterHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr){};
    
    virtual void Init(SharedPtr<Unit> aUtilizer, SharedPtr<Skill> aSkill);
    void RelaseDmgOrHealHandler();

	void TriggerOnHitEvent(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier, int64 aDamage);
	bool DefaultHitDecision(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier);
    inline bool IsDurative()
    {
        return mIsDurative;
    }
	inline void SetIsAccessional(bool aIsAccessional)
	{
		mIsAccessional = aIsAccessional;
	}
    virtual void Cancel() {}

protected:
    SharedPtr<HitHandler> mDmgOrHealHandler;
    bool mIsDurative;
	bool mIsAccessional; //denote if the mDmgOrHealHandler is the only subtype of current skill 
};


struct HitResult
{
public:
    int64 mValue;
    bool mIsHit;
    bool mIsCrit;
    bool mIsBlock;
	bool mIsPhysical;
	bool mIsPercent;
	bool mIsMelee;
	int mDamageSpecialType;
    Vector3 mSkillDir;

    HitResult(): mValue(0),
                mIsHit(false),
                mIsCrit(false),
                mIsBlock(false),
				mIsPhysical(false),
				mIsPercent(false),
				mIsMelee(false),
				mDamageSpecialType(0)
    {}
};




SharedPtr<HitHandler> NewHitHandler(ESkillSubType aSkillSubType);


void EmbattleRectangleInRelativeDiretion(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aRefPos, Vector3& aForward, 
                   EEmbattleRelativeDirection aRelDir, int64 aRelDist, int aColNum, int64 aRowGap, int64 aColGap, int64 aVerticalPos = 0);

void EmbattleRectangleSurround(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aCenterCellPos, Vector3& aForward,
                    bool aForwardTarget, int aColNum, int64 aRowGap, int64 aColGap, int64 aVerticalPos = 0);


void EmbattleCircle(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aRefPos, Vector3& aForward, 
                   EEmbattleRelativeDirection aRelDir, int64 aRelDist, bool aForwardTarget, int64 aFirstRadius, int64 aUnitRadius, int64 aVerticalPos = 0);

void EmbattleVector(vector<SharedPtr<Unit> >& aUnitArr, Vector3& aRefPos, Vector3& aForward, bool aForwardTarget, const vector<int64>& aVectorArr, int64 aVerticalPos = 0);

static int64 ApplySpecialAdjustCommon(int64 aValue, int64 aCoef, ESpecialAdjustTarget aTargetType, ESpecialAdjustTarget aDataType = ESpecialAdjustTarget::ESpecialAdjustNone)
{
	if (aTargetType != aDataType)
		return aValue;
	switch (aTargetType)
	{
	case ESpecialAdjustCrit:
		return aValue + aCoef;
	case ESpecialAdjustDmgOrHeal:
        return IncByRate(aValue, aCoef, DENOM);
		//return aValue * aCoef / DENOM;
	default:
		return aValue;
	}
}