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
#include <list>
#include "Framework/SharedPool.h"
#include "module/SkillData.pb.h"
#include "Entity/Entity.h"
#include "RefTarget.h"
#include "Skill/SkillExecutor.h"

using namespace pb;

class HitHandler;
class Unit;
class SkillProjectile;

enum class ESkillCarrierStatus
{
    Running,
    End
};

class SkillCarrier : public EnableSharedFromThis<SkillCarrier>,  public IPoolable
{
public:
    int Init(SharedPtr<Unit> aOwner, SharedPtr<SkillExecutor> aSkillExecutor, const Vector3& aStartPos, RefTarget& aRefTarget );
    void Reset();

    bool IsEnded() const;
    bool OnTick(int);
    void Cancel();

    void OnReachRefTarget(const RefTarget& aRefTarget);

    const SharedPtr<Unit> GetOwner() const;
    const SkillData* GetSkillConf() const;
    const SharedPtr<Skill> GetSkill() const;
    const RefTarget& GetRefTarget() const;

	SharedPtr<SkillExecutor> GetSkillExecutor();
private:
    SharedPtr<Unit> mOwner = nullptr;
    SharedPtr<SkillExecutor> mSkillExecutor = nullptr;
	list< SharedPtr<HitHandler> > mHitHandlerList;
    RefTarget mRefTarget;

    const SkillData* mSkillConf = nullptr;

    SharedPtr<SkillProjectile> mProjectile = nullptr;
	bool mNeedTickProjectile = false;

    ESkillCarrierStatus mStatus = ESkillCarrierStatus::End;
	
};


