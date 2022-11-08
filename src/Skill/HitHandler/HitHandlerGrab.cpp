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

#include "HitHandlerGrab.h"
#include "Skill/Skill.h"
#include "Skill/SkillCarrier.h"
#include "Entity/Unit.h"
#include "View/BattleViewOutput.h"

HitHandlerGrab::HitHandlerGrab()
{
    mIsDurative = true;
    mControlState = ControlToken::Create(ControlledType::MoveBySkill, nullptr, Unit::ANIM_NAME_IDLE);
}

void HitHandlerGrab::Reset()
{
	HitHandler::Reset();
	RelaseDmgOrHealHandler();
	if (mUtilizer)
		mUtilizer.Release();
	if (mTarget)
		mTarget.Release();
	if (mSkillCarrier)
		mSkillCarrier.Release();
	if (mControlState)
		mControlState.Release();
	mSkillConf = nullptr;
	mGrabConf = nullptr;
	mGrabTime = 0;
	mRelativePosition = Vector3(0, 0, 0);
}

void HitHandlerGrab::BeforeHitBatch(SharedPtr<Unit> aUtilizer, SharedPtr<SkillCarrier> aSkillCarrier, vector<SharedPtr<Unit> >& aEffTargetArr)
{
    mSkillConf = aSkillCarrier->GetSkillConf();
    mGrabConf = &mSkillConf->grabdata();
	mIsDurative = true;
	mControlState = ControlToken::Create(ControlledType::MoveBySkill, nullptr, mGrabConf->animonplay().c_str());
	mControlState->mStartTime = 0;
    if (mDmgOrHealHandler)
    {
        mDmgOrHealHandler->BeforeHitBatch(aUtilizer, aSkillCarrier, aEffTargetArr);
    }
    mTarget.Release();
}

bool HitHandlerGrab::CanHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    if (aTarget->IsImmueToSkill(mSkillConf->id(), ESkillSubType(mSkillConf->basedata().subtype())))
    {
        LOG_DEBUG("unit:%d immueskill:%d from %d", aTarget->GetEntityId(), mSkillConf->id(), aUtilizer->GetEntityId());
        return false;
    }
    if (mGrabConf->damagetime() == EMoveSkillDamageTimeBeforeMove)
    {
        return DefaultHitDecision(aUtilizer, aTarget, aSkillCarrier);
    }
    return true;
}

void HitHandlerGrab::OnHit(SharedPtr<Unit> aUtilizer, SharedPtr<Unit> aTarget, SharedPtr<SkillCarrier> aSkillCarrier)
{
    if (mDmgOrHealHandler && mGrabConf->damagetime() == EMoveSkillDamageTimeBeforeMove)
    {
        mDmgOrHealHandler->OnHit(aUtilizer, aTarget, aSkillCarrier);
        if (aTarget->IsDead() || (aSkillCarrier && aSkillCarrier->IsEnded()))
        {
            return;
        }
    }
    LOG_ASSERT(!mTarget);//TODO 目前只能支持一个目标
    mUtilizer = aUtilizer;
    mTarget = aTarget;
    mSkillCarrier = aSkillCarrier;
    aTarget->EnableMoveBySkill(
        MakeFunction<>(*this, &HitHandlerGrab::ExternalCancelRequest),
        mControlState.Get(),
        aUtilizer.Get(),
        mGrabConf->canbereftarget(),
        mGrabConf->canbeeffecttarget()
    );
	if (!mTarget)
	{ //Grab terminated by EnableMoveBySkill(be controlled)
		return;
	}
    mGrabTime = mGrabConf->lasttime();
    //position after grab
    int offsetX = 0;
    int offsetY = 0;
    int64 x = 0;
    int64 y = 0;
    if (mGrabConf->offsetofslot_size() > 0)
    {
        offsetX = mGrabConf->offsetofslot(0);
        offsetY = mGrabConf->offsetofslot(1);
        x = EDITOR_CONF_POS_CONVERT(offsetX);
        y = EDITOR_CONF_POS_CONVERT(offsetY);
    }
    if (x > MIN_LEN)
    {
        mRelativePosition = mUtilizer->GetForward();
        mRelativePosition.ScaleToLen(x);
    }
    else
    {
        mRelativePosition = Vector3();
    }
	const char* animName = aSkillCarrier->GetSkill()->GetAnimName();
	if (strncmp(animName, Entity::ANIM_NAME_EMPTY, 1) == 0)
	{
		animName = Entity::ANIM_NAME_IDLE;
	}
    mRelativePosition += Vector3(0, y, 0) + aUtilizer->GetSocketPos(animName, mGrabConf->selfgrabsocket().c_str());
	if (mRelativePosition.y < 0) mRelativePosition.y = 0;
    mTarget->SetPosRot(mUtilizer->GetPosition() + mRelativePosition, mTarget->GetForward(), false);
    mTarget->GetView()->Execute(
        ViewCommand::AttachToSocket,
        aUtilizer->GetEntityId(),
        mGrabConf->selfgrabsocket().c_str(),
        aTarget->GetEntityId(),
        mGrabConf->animonplay().c_str(),
        offsetX,
        offsetY
    );
    LOG_DEBUG("unit %d grabbed by unit %d", aTarget->GetEntityId(), aUtilizer->GetEntityId());
}

bool HitHandlerGrab::OnTick(int aDeltaTime)
{
	if (!mTarget)
	{
		return false;
	}
    mGrabTime -= aDeltaTime;
    if (mGrabTime <= 0)
    {
        TriggerOnEnd();
        Cancel();
        return false;
    }
    //sync mTarget position
    mTarget->SetPosRot(mUtilizer->GetPosition() + mRelativePosition, mTarget->GetForward(), false);
    return true;
}

void HitHandlerGrab::Cancel()
{
    if(!mTarget)
    {
        return;
    }
    mTarget->DisableMoveBySkill(true, mUtilizer, mControlState.Get(), mGrabConf->canbereftarget(), mGrabConf->canbeeffecttarget());
    mTarget->GetView()->Execute(
        ViewCommand::AttachToSocket,
        mUtilizer->GetEntityId(),
        "",
        mTarget->GetEntityId(),
        "", 0, 0
    );
    //keep the position as it is when dropping
    mTarget->SetPosRot(mUtilizer->GetPosition() + mRelativePosition, mTarget->GetForward(), true);
    LOG_DEBUG("unit %d dropped by unit %d", mTarget->GetEntityId(), mUtilizer->GetEntityId());
}

void HitHandlerGrab::TriggerOnEnd()
{
    if(!mTarget)
    {
        return;
    }
    if (mDmgOrHealHandler)
    {
        if (mGrabConf->damagetime() == EMoveSkillDamageTimeAfterMove && DefaultHitDecision(mUtilizer, mTarget, mSkillCarrier))
        {
            mDmgOrHealHandler->OnHit(mUtilizer, mTarget, mSkillCarrier);
        }
    }
    else
    {
        TriggerOnHitEvent(mUtilizer, mTarget, mSkillCarrier, 0);
    }
}

void HitHandlerGrab::ExternalCancelRequest(SharedPtr<Unit> aControlledUnit)
{
    //mTarget->DisableMoveBySkill(true, mUtilizer, mControlState.Get(), mGrabConf->canbereftarget(), mGrabConf->canbeeffecttarget());
	TriggerOnEnd();
	Cancel();
	mTarget.Release();
}