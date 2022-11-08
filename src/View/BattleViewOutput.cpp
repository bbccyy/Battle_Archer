/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
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
#include "BattleViewOutput.h"
#include "BattleInstance.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"

unsigned short ViewCommand::Entry::mCount = 0;
EViewCommandRecordType BattleViewOutput::RecordType = EViewCommandRecordType::JSON;

//scene
const ViewCommand::Entry ViewCommand::Cutscene = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Cutscene);
const ViewCommand::Entry ViewCommand::ResetTimeLimit = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ResetTimeLimit);
const ViewCommand::Entry ViewCommand::FieldInit = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_FieldInit);
const ViewCommand::Entry ViewCommand::EndShow = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_EndShow);
const ViewCommand::Entry ViewCommand::FullscreenBlackMask = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_FullscreenBlackMask);

//entity
const ViewCommand::Entry ViewCommand::AddAvatar = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AddAvatar);
const ViewCommand::Entry ViewCommand::AddProjectile = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AddProjectile);
const ViewCommand::Entry ViewCommand::AddDestructable = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AddDestructable);
const ViewCommand::Entry ViewCommand::AddSceneBarrier = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AddSceneBarrier);
const ViewCommand::Entry ViewCommand::ChangeAvatar = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ChangeAvatar);
const ViewCommand::Entry ViewCommand::DelEntity = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_DelEntity);
const ViewCommand::Entry ViewCommand::PauseEntity = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_PauseEntity);
const ViewCommand::Entry ViewCommand::UnpauseEntity = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_UnpauseEntity);
const ViewCommand::Entry ViewCommand::DestructEntity = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_DestructEntity);
const ViewCommand::Entry ViewCommand::AttachToSocket = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AttachToSocket);
const ViewCommand::Entry ViewCommand::Scale = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Scale);
const ViewCommand::Entry ViewCommand::Die = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Die);
const ViewCommand::Entry ViewCommand::Revive = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Revive);
const ViewCommand::Entry ViewCommand::Damage = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Damage);
const ViewCommand::Entry ViewCommand::Heal = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Heal);
const ViewCommand::Entry ViewCommand::ImmueBuff = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ImmueBuff);
const ViewCommand::Entry ViewCommand::ImmueSkill = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ImmueSkill);
const ViewCommand::Entry ViewCommand::AddRage = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AddRage);
const ViewCommand::Entry ViewCommand::AddUnparallelRage = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_AddUnparallelRage);
const ViewCommand::Entry ViewCommand::SubUnparallelRage = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SubUnparallelRage);
const ViewCommand::Entry ViewCommand::SubRage = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SubRage);
const ViewCommand::Entry ViewCommand::RageSkillStatus = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_RageSkillReady);
const ViewCommand::Entry ViewCommand::UnparalleledSkillStatus = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_UnparalleledSkillReady);
const ViewCommand::Entry ViewCommand::BattleSoulSkillStatus = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_BattleSoulSkillReady);
const ViewCommand::Entry ViewCommand::SkillHit = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillHit);
const ViewCommand::Entry ViewCommand::Dodge = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Dodge);
const ViewCommand::Entry ViewCommand::Exemption = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Exemption);
const ViewCommand::Entry ViewCommand::Parry = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Parry);
const ViewCommand::Entry ViewCommand::Resist = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Resist);
const ViewCommand::Entry ViewCommand::ControlledStateChange = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ControlledStateChange);
const ViewCommand::Entry ViewCommand::ActionSpeed = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ActionSpeed);
const ViewCommand::Entry ViewCommand::MaxHpChange = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_MaxHpChange);

//buff
const ViewCommand::Entry ViewCommand::BuffAdd = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_BuffAdd);
const ViewCommand::Entry ViewCommand::BuffModEnable = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_BuffModEnable);
const ViewCommand::Entry ViewCommand::BuffDel = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_BuffDel);
const ViewCommand::Entry ViewCommand::BuffNumberChange = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_BuffNumberChange);

//skill
const ViewCommand::Entry ViewCommand::SkillBegin = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillBegin);
const ViewCommand::Entry ViewCommand::SkillShow = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillShow);
const ViewCommand::Entry ViewCommand::SkillEmit = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillEmit);
const ViewCommand::Entry ViewCommand::SkillInterrupted = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillInterrupted);
const ViewCommand::Entry ViewCommand::SkillEnd = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillEnd);
const ViewCommand::Entry ViewCommand::SkillUnparallel = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillUnparallel);
const ViewCommand::Entry ViewCommand::SkillOnReachRefTarget = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_SkillOnReachRefTarget);

//move
const ViewCommand::Entry ViewCommand::Move = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Move);
const ViewCommand::Entry ViewCommand::Maneuver = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Maneuver);
const ViewCommand::Entry ViewCommand::Locate = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_Locate);
const ViewCommand::Entry ViewCommand::InitLocation = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_InitLocation);

//behaviour
const ViewCommand::Entry ViewCommand::BehaviourStandPointReached = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_BehaviourStandPointReached);

//screen text
const ViewCommand::Entry ViewCommand::ScreenText = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_ScreenText);

//defend point
const ViewCommand::Entry ViewCommand::DefendPoint = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_DefendPoint);
const ViewCommand::Entry ViewCommand::DelDefendPoint = ViewCommand::Entry(TBattleViewCmd_ECmdEntry::TBattleViewCmd_ECmdEntry_DelDefendPoint);


ViewCommand::Entry::Entry(TBattleViewCmd_ECmdEntry aInfoType)
    : mValue(mCount)
	, mInfoType(aInfoType)
{
    ++mCount;
}


const unsigned short ViewCommand::Entry::GetValue() const
{

    return mValue;
}


TBattleViewCmd_ECmdEntry ViewCommand::Entry::GetInfoTyple() const
{

	return mInfoType;
}

ViewCommand::Entry::operator int()
{
    return mValue;
}


BattleViewOutput::BattleViewOutput() : mIndexLastFetch(0)
{
}

BattleViewOutput::~BattleViewOutput()
{
}

void BattleViewOutput::Init(const BattleInstance& aBattle)
{
    mTime = -1;
    mSeqId = 0;
    mBattle = &aBattle;

}

uint32 BattleViewOutput::NextId()
{
    mSeqId = mSeqId + 1;
    return mSeqId;
}


void BattleViewOutput::TryWriteTime(TBattleViewCmd& aBattleViewCmd)
{

    int v = mBattle->GetFrameTime();
    if (v != mTime)
    {
		mTime = v;
		aBattleViewCmd.set_cmdtime(mBattle->GetFrameTime());
    }
}


void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aEntityId, const ControlledType& aType, const char* aAnimName)
{

	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	TryWriteTime(*pBattleViewCmd);
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	WriteCommandToPb(aCommand, *pBattleViewCmd, aEntityId, static_cast<int>(aType));
	pBattleViewCmd->set_anim(aAnimName);
}

void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const Army& aArmy1, const Army& aArmy2, const int& aEliminatedArmyId)
{

	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	constexpr const char* army1 = "army1";
    constexpr const char* army2 = "army2";
    TryWriteTime(*pBattleViewCmd);
    
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	pBattleViewCmd->add_args(aEliminatedArmyId);

	stringstream* writer = new stringstream;

	vector<SharedPtr<Unit>> vArmyUnit = aArmy1.GetUnitArr();
	for (vector<SharedPtr<Unit>>::iterator it = vArmyUnit.begin(); it != vArmyUnit.end(); it++) {
		if (!(it->Get()->IsHidden()))
		{
			TArmyUnitInfo* pArmyUnitInfo = pBattleViewCmd->add_army1();
			it->Get()->WriteViewInfo(*writer, pArmyUnitInfo);
		}
	}
	if (aArmy1.HasArmyShooter())
	{
		TArmyUnitInfo* pArmyUnitInfo = pBattleViewCmd->add_army1();
		aArmy1.GetArmyShooter()->WriteViewInfo(*writer, pArmyUnitInfo);
	}


	vArmyUnit = aArmy2.GetUnitArr();
	for (vector<SharedPtr<Unit>>::iterator it = vArmyUnit.begin(); it != vArmyUnit.end(); it++) {
		if (!(it->Get()->IsHidden()))
		{
			TArmyUnitInfo* pArmyUnitInfo = pBattleViewCmd->add_army2();
			it->Get()->WriteViewInfo(*writer, pArmyUnitInfo);
		}
	}
	if (aArmy2.HasArmyShooter())
	{
		TArmyUnitInfo* pArmyUnitInfo = pBattleViewCmd->add_army2();
		aArmy2.GetArmyShooter()->WriteViewInfo(*writer, pArmyUnitInfo);
	}

	delete writer;
}


void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aEntityId, const int& aSkillId, const vector<RefTarget>& aRefTargetArr)
{  //SkillBegin, SkillShow
    constexpr const char* ref = "ref";

    
	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	TryWriteTime(*pBattleViewCmd);
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	pBattleViewCmd->add_args(aEntityId);
	pBattleViewCmd->add_args(aSkillId);
	for (int e = 0; e < aRefTargetArr.size(); ++e) {
		if (aRefTargetArr[e].GetType() == ERefTargetType::Unit) {
			const auto& unit = aRefTargetArr[e].GetUnit();
			pBattleViewCmd->add_refs(unit->GetEntityId());
		}
	}
}

void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aEntityId, const int& aMoveType, const int& aPathState, const Vector3& aSelfPos, const Vector3& aTarPos, const int& aTargetId, const int64& aSpeed, const int64& aCastRange, const vector<Vector2>& aPath)
{  //Maneuver: MovePath
	//constexpr const char* ref = "ref";

	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	TryWriteTime(*pBattleViewCmd);
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	pBattleViewCmd->add_args(aEntityId);
	pBattleViewCmd->add_args(aMoveType);
	pBattleViewCmd->add_args(aPathState);
	pBattleViewCmd->add_args(aSelfPos.x);
	pBattleViewCmd->add_args(aSelfPos.y);
	pBattleViewCmd->add_args(aSelfPos.z);
	pBattleViewCmd->add_args(aTarPos.x);
	pBattleViewCmd->add_args(aTarPos.y);
	pBattleViewCmd->add_args(aTarPos.z);
	pBattleViewCmd->add_args(aTargetId);
	pBattleViewCmd->add_args(aSpeed);
	pBattleViewCmd->add_args(aCastRange);

	for (int e = 0; e < aPath.size(); ++e) {
		pBattleViewCmd->add_refs(aPath[e].x);
		pBattleViewCmd->add_refs(aPath[e].z);
	}

}

void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aEntityId, const int& aSkillId, const vector<int>& aEffTargetArr)
{
	constexpr const char* eff = "eff";

	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	
	TryWriteTime(*pBattleViewCmd);
	
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	pBattleViewCmd->add_args(aEntityId);
	pBattleViewCmd->add_args(aSkillId);
	for (int e = 0; e < aEffTargetArr.size(); ++e)
	{
		if (aEffTargetArr[e] > 0)
		{
			pBattleViewCmd->add_effs(aEffTargetArr[e]);
		}
	}
}

void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aUtilizerId, const char* aSocketName, const uint32& aTargetId, const char* aAnimName, const int& offsetX, const int& offsetY)
{

	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	TryWriteTime(*pBattleViewCmd);
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	pBattleViewCmd->add_args(aUtilizerId);
	pBattleViewCmd->add_args(aTargetId);
	pBattleViewCmd->add_args(offsetX);
	pBattleViewCmd->add_args(offsetY);
	pBattleViewCmd->set_socketname(aSocketName);
	pBattleViewCmd->set_anim(aAnimName);
}

void BattleViewOutput::WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aEntityId, const int& aSkillId, const RefTarget& aRefTarget, const Vector3& aDir, const vector<SharedPtr<Unit>>& aEffTargetIdArr, const uint32& aProjectileEntityId)
{  //SkillOnReachRefTarget
    
	constexpr const char* refId = "refId";
    constexpr const char* refPos = "refPos";
    constexpr const char* eff = "eff";

	TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
	TryWriteTime(*pBattleViewCmd);
	pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
	pBattleViewCmd->add_args(aEntityId);
	pBattleViewCmd->add_args(aSkillId);
	pBattleViewCmd->add_args(aProjectileEntityId);
	pBattleViewCmd->add_args(aDir.x);
	pBattleViewCmd->add_args(aDir.y);
	pBattleViewCmd->add_args(aDir.z);
	if (aRefTarget.GetType() == ERefTargetType::Unit)
	{
		pBattleViewCmd->set_refid(aRefTarget.GetUnit()->GetEntityId());
		
	}
	else
	{
		const Vector3& pos = aRefTarget.GetTargetPos();
		//TRefPos aRefPos = pBattleViewCmd->refpos();
		TRefPos *aRefPos = new TRefPos();
		aRefPos->set_x(pos.x);
		aRefPos->set_y(pos.y);
		aRefPos->set_z(pos.z);
		pBattleViewCmd->set_allocated_refpos(aRefPos);
	}

	for (int e = 0; e < aEffTargetIdArr.size(); ++e)
	{

		pBattleViewCmd->add_effs(aEffTargetIdArr[e]->GetEntityId());
	}
}
