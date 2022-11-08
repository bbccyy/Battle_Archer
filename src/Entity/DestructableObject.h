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
* @brief Õ½¶·µ¥Î»
*
**/

#pragma once
#include "Entity.h"
#include "module/SceneConf3d.pb.h"
#include "ConfigMgr/ConfigMgr.h"

class Agent;
class Unit;
class Skill;
using pb::Destructable;

class DestructableObject : public Entity, public EnableSharedFromThis<DestructableObject>
{
public:
    static int DamageBySkillValue;
    static int DamageByRageSkillValue;
    static int DamageBySkillMoveValue;
    DestructableObject() = default;
    void Init(BattleInstance& aBattle, BattleViewOutput& aView, PhysicsSystem& aPhysics, const Destructable* aConf, int aSeqId);
    void Activate();
    void DamageByMove(const Unit* aUtilizer);
    void DamageBySkill(const Unit* aUtilizer, const Skill* aSkill);
    void Reset();
    bool IsValid() const;
private:
    const Destructable* mInitConf;
    const ConfigDestructiveObjects* mConf;
    int mSeqId;
    BattleInstance* mBattle;
    Agent* mAgent;
    bool mIsValid;
    int mHp;
    void CheckDestruct();
};