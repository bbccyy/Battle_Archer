
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

	InitMoveParam();
}


void SkillProjectileBounce::InitMoveParam()
{
	//mStatus = EProjectileLineStatusForward;
	//mStayTimeOnReachTarget = 0;
	mRefTarget.GetTargetSocketBodyPos(mTargetPos);  //set target pos before Build Executor
	mRotation = mTargetPos - mPosition;			//init direction 

	if (mLockTarget)  //lock target -> use MoveTrace  
	{
		mMoveTrace = BuildTraceExecutor(SharedFromThis());
		mCurExecutor = mMoveTrace;
	}
	else  // use -> MoveStraight
	{
		mMovePath = BuildStraightExecutor(SharedFromThis());
		mCurExecutor = mMovePath;
	}
}
