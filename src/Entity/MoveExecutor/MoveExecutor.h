#pragma once
#include "Entity/Entity.h"
#include "module/SkillData.pb.h"
#include "View/BattleViewOutput.h"
#include "Skill/RefTarget.h"
#include "Framework/IntMath.h"

#define SEG_NUM 3
#define BEZIER_DENOM 1000
#define BEZIER_DENOM_2 1000000
#define BEZIER_DENOM_3 1000000000

#define MAX_UP_LIMIT 10000000  //100m
#define MAX_DOWN_LIMIT -10000000  //-100m

using namespace pb;

enum class EMoveStatus
{
	EMoveInit,
	EMoveStart,

	EMoveParabloaUp,
	EMoveParabloaPeak,
	EMoveParabloaDown,  //according conf: down to somewhere it stops
	EMoveParabloaFall,  //according pyhsics: fall to ground

	EMovePreDone,
	EMoveDone,

};

enum class EMoveType
{
	EMoveTrace,
	EMoveParabloa,
	EMoveCurve,
	EMoveStraight,
	EMoveNone,
	EMoveModify,
	EMovePath
};

class Unit;

//pass by value, so keep it simple
typedef struct MoveParams {
public:
	SharedPtr<Entity> mSelf;  //moving entity, could be a Unit, a Projectile, a Barrier, etc.
	//SharedPtr<Unit> mUtilizer;  //SkillMove as CtrledUnit, Projectile as TargetUnit
	Vector3 mTarPos;  //optional
	//RefTarget mRefTarget;
}ParamMove;

class MoveExecutor :  public IPoolable
{
public:
	MoveExecutor() = default;
	~MoveExecutor() = default;
	void InitBase(BattleViewOutput* aView, SharedPtr<Entity> aSelf, Vector3 aTarPos);
	virtual void Enable() = 0;
	virtual void Disable();
	virtual EMoveStatus OnTick(int aDeltaTime) = 0;
	virtual void Reset();
	virtual void RefreshStatus();
	virtual void SetTargetPos(Vector3);;
	virtual void SetSpeedParams(int64 aSpeed, int64 aAcc0, int64 aAccD);
	virtual EMoveType Type();

	void GetPosition(Vector3&);
	void SetPosition(const Vector3& aPos);
	void SetPosAndRot(const Vector3& aPos, const Vector3& aRot);
	EMoveStatus GetMoveStatus() const;
protected:
	WeakPtr<Entity> mSelf;
	Vector3 mTargetPos;
	BattleViewOutput* mView;

	bool mHitAreaBound;  //Horizontal move restriction: do not touch boundery
	bool mEnabled;
	EMoveStatus mStatus;

};

SharedPtr<MoveExecutor> CreateMoveExecutor(EMoveType aType);