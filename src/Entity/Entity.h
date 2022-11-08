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
* @brief 有View表现的实体
*
**/

#pragma once
#include "Framework/Transform.h"
#include "Framework/Physics/PhysicsSystem.h"
#include "Log/Log.h"
#include "Define.h"
#include "Skill/RefTarget.h"

class BattleInstance;
class BattleViewOutput;
class MovePath;
class MoveTrace;
class MoveParabloa;
class PathFindingMgr;
struct PathTD;

class Entity :  public IPoolable
{
public:
	static const constexpr char* ANIM_NAME_IDLE = "idle_01";
	static const constexpr char* ANIM_NAME_WEAK = "weak_01";
	static const constexpr char* ANIM_NAME_WEAK2 = "weak_02";
	static const constexpr char* ANIM_NAME_RUN = "run_01";
	static const constexpr char* ANIM_NAME_WALK = "walk_01";
	static const constexpr char* ANIM_NAME_STUN_PREFIX = "stun";
	static const constexpr char* ANIM_NAME_HIT_PREFIX = "hit";
	static const constexpr char* ANIM_NAME_HIT = "hit_01";
	static const constexpr char* ANIM_NAME_HIT_FAKE = "hit_02";
	static const constexpr char* ANIM_NAME_DOWN = "down_01";
	static const constexpr char* ANIM_NAME_DOWN_2 = "down_02";
	static const constexpr char* ANIM_NAME_DOWN_PREFIX = "down";
	static const constexpr char* ANIM_NAME_KNOCK = "knock_01";
	static const constexpr char* ANIM_NAME_KNOCK_2 = "knock_02";
	static const constexpr char* ANIM_NAME_KNOCK_PREFIX = "knock";
	static const constexpr char* ANIM_NAME_FLOAT = "float_01";
	static const constexpr char* ANIM_NAME_FLOAT_2 = "float_02";
	static const constexpr char* ANIM_NAME_DEAD = "death_01";
	static const constexpr char* ANIM_NAME_DEAD_2 = "death_02";
	static const constexpr char* ANIM_NAME_DEAD_3 = "death_03";
	static const constexpr char* ANIM_NAME_DEAD_4 = "death_04";
	static const constexpr char* ANIM_NAME_EMPTY = "";

	static const constexpr char* ANIM_PLAY_DEATH_1 = "skill";
	static const constexpr char* ANIM_PLAY_DEATH_2 = "attack";

	static const constexpr char* ANIM_SOCKET_BODY = "slot_logic_body";

	static const constexpr int DEATH_DROP_SKILL = 501; //TODO:may pass through battleConf
	static const constexpr int COMMON_REACHOUT_MODIFIER = 50000;
public:
    void InitEntity(BattleViewOutput&, PhysicsSystem&, PathFindingMgr* aPathMgr = nullptr);
    void ClearView();
    uint32 GetEntityId() const;
    BattleViewOutput* GetView() const;
    PhysicsSystem* GetPhysics() const;
    void SetPosition(int64 aX, int64 aY, int64 aZ, bool aCmd);
    void SetPosition(const Vector3& aPos, bool aCmd);
	void InitLocation(const Vector3&, const Vector3&);
    void SetRotation(const Vector3&);
    void SetPosRot(const Vector3&, const Vector3&, bool);
	void SetRot(const Vector3&, bool);
    const Vector3& GetPosition() const;
    const Vector3& GetForward() const;
    const Vector3 GetRight() const;
    int GetSpeed() const;
    int GetSize() const;
    bool MoveTowards(const Vector3& aPos, int aFiringRange, int aDeltaTime, int aTargetId, bool aNoRotWithinRange = false, int aBehaviourMove = 0);
	bool Move(const RefTarget& aRefTarget, SharedPtr<Entity> aSelf, int aFiringRange, int aDeltaTime, ERefFaceTo aFaceTo = ERefFaceTo::None, int64 aSpeed = 0, int64 aFaceX = 0, int64 aFaceY = 0, bool aDontPlayAnim = false);
	bool Move2Ref(const RefTarget& aRefTarget, SharedPtr<Entity> aSelf, int aFiringRange, int aDeltaTime, ERefFaceTo aFaceTo = ERefFaceTo::None, bool aIsArmy1 = true);
	void DisableMove();
	bool IsMoving() const;
	RefTarget& GetMoveRefTarget();
	void ScaleOffset(int, int);
    void Scale(int, int);
    virtual void UpdateAgent(){};
	void ResetEntity();
	void TryModifyMoveTrace(int aPosIndex);
	void LocalToWorld(Vector3& aPos) const;
	void WorldToLocal(Vector3& aPos) const;
    void Reset();
	void TryUpdateMapLocation(bool aRetrieve = false);

	bool GreaterEqualThan(int, Entity*);
	bool LessEqualThan(int, Entity*);
	virtual void OnPathIndexChange(int aIndex)
	{
		mPathIndex = aIndex - 1;
	};

	int mEntityRegister0 = 0;

	PathTD* mPathTD = nullptr;		//ptr to predefined path 
	int mPathIndex = 0;
protected:
    Entity() = default;
	RefTarget mMoveRefTarget;
	SharedPtr<MovePath> mMovePath = nullptr;
	SharedPtr<MoveTrace> mMoveTrace = nullptr;
	SharedPtr<MoveParabloa> mMoveParabloa = nullptr;
    BattleViewOutput* mView = nullptr;
    PhysicsSystem* mPhysics = nullptr;
    uint32 mEntityId = 0;
    Vector3 mPosition;
    Vector3 mRotation;
    int mSpeed = 0;
	int64 mBaseSize = 0;
	int64 mSize = 0;
	int64 mBaseSizeScale = 0;
	int64 mSizeScale = 0;
    int mControlled = 0;  //TODO: Delete it 
	bool mIsMoving = false;//是否在主动移动  
	const char* mCurrentAnimName = nullptr;
	int64 mCurrentAnimStartTime = 0;
	int64 mCurrentAnimLength = 0;

	RefTarget mBehaviourRefTarget;
	RefTarget mOverLapRefTarget;

	PathFindingMgr* mPathMgr = nullptr;
};