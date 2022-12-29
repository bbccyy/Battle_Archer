
#include "SkillProjectileBounce.h"
#include "Skill/SkillCarrier.h"
#include "Skill/SkillExecutor.h"
#include "Skill/SkillDefine.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Log/Log.h"
#include "View/BattleViewOutput.h"
#include "ConfigMgr/ConfigMgr.h"

void SkillProjectileBounce::Init(WeakPtr<SkillCarrier> aCarrier, const Vector3& aStartPos, const RefTarget& aRefTarget)
{
	InitBase(aCarrier, aStartPos, aRefTarget);

	auto skill = mCarrier->GetSkill();
	if (skill->mArcherParam.IsValid)
	{
		int ret = skill->mArcherParam.GetValue(EArcherParamsType::Bounce_Num);
		if (ret > 0)
		{
			mBounceNum = ret;
		}
		ret = skill->mArcherParam.GetValue(EArcherParamsType::Max_Through_Num);
		if (ret > 0)
		{
			mMaxCollisionNum = ret;
			//mGapTime = 500;  //TODO: 走配置 
		}
	}

	InitMoveParam();
}


void SkillProjectileBounce::InitMoveParam()
{
	mStatus = EProjectileBounceStatus::EProjectileBounceStatusNormal;

	mRefTarget.GetTargetSocketBodyPos(mTargetPos);  //set target pos before Build Executor 
	mRotation = mTargetPos - mPosition;				//init direction 

	mMoveBounce = BuildBounceExecutor(SharedFromThis());
	mCurExecutor = mMoveBounce;
}


void SkillProjectileBounce::Reset()
{
	ResetBase();
	if (mMoveBounce)
		mMoveBounce = nullptr;

	mMoveStatus = EMoveStatus::EMoveDone;
	mStatus = EProjectileBounceStatus::EProjectileBounceStatusNormal;
}

bool SkillProjectileBounce::OnTick(int aDeltaTime)
{

	if (mStatus == EProjectileBounceStatus::EProjectileBounceStatusDone)
	{
		return false;
	}

	Vector3 prePos = mPosition;

	mMoveStatus = mCurExecutor->OnTick(aDeltaTime);

	if (mMoveStatus == EMoveStatus::EMovePartDone)
	{
		clearTouchedEntityIdArr();
	}

	if (mMaxCollisionNum > 0)
	{
		if (mCurCollisionNum < mMaxCollisionNum)
		{
			CollisionDetection(prePos, mPosition); 
		}
		if (mCurCollisionNum >= mMaxCollisionNum)
		{//disappear here
			mCurExecutor->Disable();
			mStatus = EProjectileBounceStatus::EProjectileBounceStatusDone;
			return false;
		}
	}

	if (mMoveStatus == EMoveStatus::EMoveDone)
	{
		mStatus = EProjectileBounceStatus::EProjectileBounceStatusDone;
		mCarrier->OnReachRefTarget(mRefTarget); //到达目标点时再触发一次 
	}

	return mStatus != EProjectileBounceStatus::EProjectileBounceStatusDone;

}