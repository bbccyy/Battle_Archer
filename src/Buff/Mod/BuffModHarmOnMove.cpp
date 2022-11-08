

#include "BuffModHarmOnMove.h"
#include "Entity/Unit.h"
#include "Skill/Skill.h"
#include "Buff/Buff.h"

void BuffModHarmOnMove::StackAdded(int)
{
	//nothing
}

void BuffModHarmOnMove::StackRemoved(int)
{
	//nothing
}

void BuffModHarmOnMove::OnEnable()
{
	auto& unit = GetOwner();
	const auto& curPos = unit->GetPosition();
	mPrePosX = curPos.x;
	mPrePosZ = curPos.z;
	mTimer = SharedPool<Timer<BuffModHarmOnMove> >::Get();
	mTimer->Execute(unit->GetTimerMgr(), this, &BuffModHarmOnMove::ExecuteSkill, unit->GetUnitTime() + 500);
}

void BuffModHarmOnMove::OnDisable(bool aShouldTrigger)
{
	if (mTimer)
	{
		mTimer->Cancel();
		mTimer = nullptr;
	}
	mPrePosX = 0;
	mPrePosZ = 0;
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		mParams.mSkill = nullptr;
		return;
	}
	if (GetSourceUtilizer() && mParams.mSkill)
	{
		GetSourceUtilizer()->SetBuffSkillInfo(mParams.mSkill->GetId(), mParams.mSkill->mBeginCount, mParams.mSkill->mEffectTargetCount);
	}
}

bool BuffModHarmOnMove::ExecuteSkill(Timer<BuffModHarmOnMove>& aTimer)
{
	mParams.mSkill->isTriggeredByBuff = true;
	mParams.mSkill->mAncestorSkill = GetBuff()->mAncestorSkill;
	GetOwner()->mSkillIdSpecial = mParams.mSkill->GetId();

	const auto& curPos = GetOwner()->GetPosition();
	if (curPos.x == mPrePosX && curPos.z == mPrePosZ)
	{
		aTimer.Reset(GetOwner()->GetUnitTime() + 500);
		return true;
	}

	int64 dx = curPos.x - mPrePosX;
	int64 dz = curPos.z - mPrePosZ;
	int64 dist = Sqrt(dx * dx + dz * dz);

	mParams.mSkill->mExtraDmgCoef = dist * DENOM / CONF_POS_CONVERT(100); 

	const auto& sourceUtilizer = GetSourceUtilizer();
	if (mParams.mSkill->RefreshRefTarget())
		GetOwner()->ExecuteSkill(mParams.mSkill, 0, nullptr, sourceUtilizer);

	if (!IsValid() && !mParams.mSkill)
		return false;
	GetOwner()->mSkillIdSpecial = 0;
	mParams.mSkill->isTriggeredByBuff = false;
	mParams.mSkill->mExtraDmgCoef = DENOM;

	mPrePosX = curPos.x;
	mPrePosZ = curPos.z;

	if (IsValid())
		aTimer.Reset(GetOwner()->GetUnitTime() + 500);  //wait 500ms to exec next 

	return true;
}