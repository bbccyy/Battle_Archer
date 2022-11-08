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
* @brief ¿ÉÆÆ»µÎïÌå
*
**/

#include "DestructableObject.h"
#include "View/BattleViewOutput.h"
#include "Framework/Physics/PhysicsSystem.h"
#include "Skill/Skill.h"
#include "BattleInstance.h"
#include "ConfigMgr/Util.h"

int DestructableObject::DamageBySkillValue;
int DestructableObject::DamageByRageSkillValue;
int DestructableObject::DamageBySkillMoveValue;

void DestructableObject::Init(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, const Destructable* aConf, int const aSeqId)
{
    InitEntity(aView, aPhysics);
    mBattle = &aBattle;
    mInitConf = aConf;
    mSeqId = aSeqId;
}

void DestructableObject::Activate()
{
    mIsValid = true;
    //TODO use rectangular agent
    mAgent = mPhysics->AddAgent(SharedFromThis(), EBVTypeCylinder, PHYSICS_GROUP_DESTRUCTABLE);
    const auto& min = mInitConf->rectinfo().minpoint();
    const auto& max = mInitConf->rectinfo().maxpoint();
    const auto& confPos = mInitConf->artobjectposition();
    auto pos = Vector3(CONF_POS_CONVERT(confPos.x()), CONF_POS_CONVERT(confPos.y()), CONF_POS_CONVERT(confPos.z()));
    auto size = Vector2(CONF_POS_CONVERT(max.x() - min.x()), CONF_POS_CONVERT(max.y() - min.y()));
    auto* bv = dynamic_cast<Cylinder*>(mAgent->GetBV());
    auto radius = size.x / 2;
    bv->Update(&pos, &radius);
    mConf = ConfigMgr::GetConfById<ConfigDestructiveObjects>(mInitConf->tid());
    mHp = mConf->GetDestructiveLimit();
    mView->Execute(ViewCommand::AddDestructable, mEntityId, mSeqId, pos.x, pos.y, pos.z);
    mInitConf = nullptr;
}

void DestructableObject::DamageByMove(const Unit* aUtilizer)
{
    if (!mIsValid)
        return;
    mHp -= DamageBySkillMoveValue;
    CheckDestruct();
}

void DestructableObject::DamageBySkill(const Unit* aUtilizer, const Skill* aSkill)
{
    if (!mIsValid)
        return;
    if (aSkill->IsRageSkill()) {
        mHp -= DamageByRageSkillValue;
    }
    else {
        mHp -= DamageBySkillValue;
    }
    CheckDestruct();
}

void DestructableObject::Reset()
{
    if (mAgent)
    {
        mPhysics->RemoveAgent(mAgent);
    }
}

bool DestructableObject::IsValid() const
{
    return mIsValid;
}

void DestructableObject::CheckDestruct()
{
    if (mHp <= 0)
    {
        mView->Execute(ViewCommand::DestructEntity, mEntityId);
        mPhysics->RemoveAgent(mAgent);
        mAgent = nullptr;
        mIsValid = false;
        int rn = mBattle->Rand(DENOM);
        int accum = 0;
        int i = 0;
        for (auto& v : mConf->GetEventWeight())
        {
            accum += v;
            if (rn <= v)
                break;
            ++i;
        }
        for (int k = 0; k < i; ++k) {
            //TODO
        }
    }
}