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
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Framework/SharedPtr.h"
#include "Framework/FunctionContainer.h"
#include "Log/Log.h"
#include "Define.h"

class BattleInstance;
struct DirectedPosition;
class Army;
class Unit;
class RefTarget;
class Vector3;
class Vector2;
enum class ControlledType;

using std::ofstream;


#include "net/BattleViewCmd.pb.h"


using pb::TBattleViewCmd;
using pb::TBattleViewCmdList;
using pb::TBattleViewCmd_ECmdEntry;


//zlib boost
//#include <boost/iostreams/filtering_streambuf.hpp>
//#include <boost/iostreams/copy.hpp>
//#include <boost/iostreams/filter/zlib.hpp>




struct ViewCommand
{
public:
    struct Entry
    {
    public:
        Entry(TBattleViewCmd_ECmdEntry aCmdEntry);
        
		const unsigned short GetValue() const;
		
		TBattleViewCmd_ECmdEntry GetInfoTyple() const;
		
		operator int();
        bool operator ==(const Entry& aOther)
        {
            return mValue == aOther.mValue;
        }
        bool operator !=(const Entry& aOther)
        {
            return mValue != aOther.mValue;
        }
    private:
		static unsigned short mCount;
		unsigned short mValue = 255;
		TBattleViewCmd_ECmdEntry mInfoType;
    };
public:
    //scene
    static const Entry Init;//View初始化() 
    static const Entry Cutscene;//进入过场状态()
    static const Entry ResetTimeLimit;//重置倒计时(aTimeLimit, aFrameTime)
    static const Entry FieldInit;/*设置一屏战斗信息(
                                 aEliminatedArmyId,<-1=none, other value=army id>
                                 UnitState[] aUnits1，
                                 UnitState[] aUnits2，
                                 //Vector3[] aBornPoints1,
                                 //Vector3[] aBornPoints2
                                 )
                                 UnitState{aEntityId, aTplId, aArmyId, aBornPoint, aCurHp, aCurRage, aMaxHp, aMaxRage, aMoveSpeed}
                                 Vector3{x,y,z}*/
    static const Entry EndShow;//战斗结束展示状态(aResult)
    static const Entry FullscreenBlackMask;//黑屏效果(aShouldHighlight, aArmyId)
    static const int FULLSCREEN_BLACK_MASK_ENABLE = 1;
    static const int FULLSCREEN_BLACK_MASK_DISABLE = 0;
    //entity
    static const Entry AddAvatar;//创建英雄物体(aEntityId, aTplId, aArmyId, aCurHp, aMaxHp, aCurRage, aRageSkillThreshold, aBornPointIndex, aMoveSpeed, aBaseSizeScale, aShowOnUI)
    static const Entry AddProjectile;//创建弹道物体(aEntityId, aSkillId, aProjectileType, aOwnerId, aTargetId)
    static const Entry AddDestructable;//创建可破坏物体(aEntityId, aSeqId, aPosX, aPosY, aPosZ)
	static const Entry AddSceneBarrier;//创建场景屏障(aEntityId)  //TODO
    static const Entry ChangeAvatar;//更换英雄物体显示(aEntityId, aTplId, aCurHp, aCurRage, aMaxHp, aMaxRage)
    static const Entry DelEntity;//清除物体(aEntityId)
    static const Entry PauseEntity;//暂停(aEntityId)
    static const Entry UnpauseEntity;//解除暂停(aEntityId)
    static const Entry DestructEntity;//触发物体破坏效果(aEntityId)
    static const Entry AttachToSocket;//将target entity挂到utilizer entity的socket上，并播放指定动作(aUtilizerId,aSocketName,aTargetId,aOffsetX,aOffsetY,aOffsetZ)
    static const Entry Scale;//缩放物体(aEntityId, aScale)
    static const Entry Die;//死亡(aEntityId)
    static const Entry Revive;//复活(aEntityId)
    static const Entry Damage;//伤害(aEntityId, aHpDelta, aCurHp, aUtilizer, aSkillId, aBuffId, aIsCrit, aIsBlock, aDirX, aDirY, aDirZ)
    static const Entry Heal;//治疗(aEntityId, aHpDelta, aCurHp, aUtilizer, aSkillId, aBuffId, aIsCrit)
    static const Entry ImmueBuff;//免疫buff效果(aEntityId, aBuffId)
    static const Entry ImmueSkill;//免疫skill效果(aEntityId, aSkillId)
    static const Entry AddRage;//增加怒气(aEntityId, aRageDelta, aCurRage)
	static const Entry AddUnparallelRage;//增加无双怒气(aArmyId, aRageDelta, aCurRage, aMaxRage)
    static const Entry SubRage;//减少怒气(aEntityId, aRageDelta, aCurRage)
	static const Entry SubUnparallelRage;//减少无双怒气(aArmyId, aRageDelta, aCurRage, aMaxRage)
    static const Entry RageSkillStatus;//怒气技可释放(aEntityId, aReadySkillId)
    static const Entry UnparalleledSkillStatus;//无双技可释放(aEntityId, aIsReady)
    static const Entry BattleSoulSkillStatus;//武魂真身可释放(aEntityId, aIsReady)
    static const Entry SkillHit;//技能命中(aEntityId, aSkillId, aBeHit, aDirX, aDirY, aDirZ)
    static const Entry Dodge;//闪避(aEntityId)
    static const Entry Exemption;//豁免(aEntityId)
    static const Entry Parry;//格挡(aEntityId)
    static const Entry Resist;//抵抗(aEntityId)
    static const Entry ControlledStateChange;//控制状态改变(aEntityId, aControlledType, aAnimName)
	static const Entry ActionSpeed; //行动速度变化 (aEntityId, aCurSpeed)
	static const Entry MaxHpChange;//(aEntityId, aCurHp, aCurMaxHp)
    //buff
    static const Entry BuffAdd;//(aEntityId, aBuffId)
    static const Entry BuffModEnable;//(aEntityId, aBuffId, aBuffModId)
    static const Entry BuffDel;//(aEntityId, aBuffId)
    static const Entry BuffNumberChange;//(aEntityId, aBuffId, aCurNumber)
    //skill
    static const Entry SkillBegin;//(aEntityId, aSkillId, uint32[] aRefTargetIdArr)
    static const Entry SkillShow;//(aEntityId, aSkillId, uint32[] aRefTargetIdArr)
    static const Entry SkillEmit;//(aEntityId, aSkillId, aRefTargetPosX, aRefTargetPosY, aRefTargetPosZ)
    static const Entry SkillInterrupted;//(aEntityId, aSkillId)
    static const Entry SkillEnd;//(aEntityId, aSkillId)
    static const Entry SkillUnparallel;//(aEntityId, aSkillId)
    static const Entry SkillOnReachRefTarget;//(aEntityId, aSkillId, uint32 aRefTargetId/Vector3 aRefTargetPos, Vector3 aDir, uint32[] aEffTargetIdArr)
    //move
	static const Entry Move;//同步位置旋转(aEntityId, aCurPosX, aCurPosY, aCurPosX, aCurRotX, aCurRotY, aCurRotZ, aCurSpeed, aControlled, aTarget)
	static const Entry Maneuver;//Move with params(aEntityId, aMoveType, uint32[] aParams)
	static const Entry Locate; //Set Entity's location(aEntityId, aCurPosX, aCurPosY, aCurPosX, aCurRotX, aCurRotY, aCurRotZ)
	static const Entry InitLocation;//After add avatar, init it's location(param is same with Locate)
	//behaviour
    static const Entry BehaviourStandPointReached;//(aEntityId)
	//screen text
	static const Entry ScreenText; //(aEntityId, aEffectType, aExtraData)
	//defend point
	static const Entry DefendPoint;  //(aEntityId, aPointNum, aPointColor) 
	static const Entry DelDefendPoint;  //(aEntityId, aPointNum, aIsActive)  
};

enum class EViewCommandRecordType
{
    None = 0,
    JSON,
    MSGPACK,
};

class BattleViewOutput
{
public:
    static EViewCommandRecordType RecordType;
    BattleViewOutput();
    ~BattleViewOutput();
    void Init(const BattleInstance&);

    template<typename... A>
    void Execute(const ViewCommand::Entry& aCommand, const A&... aArgs)
    {
        if (RecordType == EViewCommandRecordType::None)
            return;
		WriteToFile(aCommand, aArgs...);
    }

    uint32 NextId();
    
	vector<TBattleViewCmd*>& FetchViewCmd() {
		mCmdsLastFetch.clear();
		mCmdsLastFetch.reserve(mBattleViewCmdList.cmds_size() - mLastFetchCmdPos);

		while (mLastFetchCmdPos < mBattleViewCmdList.cmds_size())
		{
			mCmdsLastFetch.push_back( mBattleViewCmdList.mutable_cmds(mLastFetchCmdPos) );
			mLastFetchCmdPos++;
		}
		return mCmdsLastFetch;
	}
	inline string GetAllCmdsAsString() {		
		std::stringstream os;
		mBattleViewCmdList.SerializeToOstream(&os);				
		return os.str();
	}


private:
    static constexpr const char* VIEW_FILE_NAME = "_view_output";
    static constexpr const char* END_LINE = "\n";
    static constexpr const char* TAB = "\t";
    static constexpr const char* SEP = ",";
    static constexpr const char* QUATE = "\"";
    static constexpr const char* ASSIGN = ":";
    static constexpr const char* ARRAY_START = "[";
    static constexpr const char* ARRAY_END = "]";
    static constexpr const char* ARRAY_END_SEP = "],";
    static constexpr const char* BLOCK_START = "{";
    static constexpr const char* BLOCK_END = "}";
    static constexpr const char* FIELD_TIME = "T";
    static constexpr const char* FIELD_ARGS = "A";
    static constexpr const char* FIELD_ARGS_STR = "S";
    int mTime = -1;
    uint32 mSeqId = 0;
	size_t mLastFetchCmdPos = 0;
    const BattleInstance* mBattle;
    
	TBattleViewCmdList mBattleViewCmdList;
	int mIndexLastFetch;
	vector<TBattleViewCmd*> mCmdsLastFetch;


    void TryWriteTime(TBattleViewCmd& aBattleViewCmd);
    
	void WriteToFile(const ViewCommand::Entry& , const uint32& aEntityId, const ControlledType&, const char* aAnimName);
    void WriteToFile(const ViewCommand::Entry& , const Army& aArmy1, const Army& aArmy2, const int&);
    void WriteToFile(const ViewCommand::Entry& , const uint32& aEntityId, const int& aSkillId, const vector<RefTarget>&);
    void WriteToFile(const ViewCommand::Entry& , const uint32& aEntityId, const int& aMoveType, const int& aPathState, const Vector3& aSelfPos, const Vector3& aTarPos, const int& aTargetId, const int64& aSpeed, const int64& aCastRange, const vector<Vector2>& aPath);
	void WriteToFile(const ViewCommand::Entry& , const uint32& aEntityId, const int& aSkillId, const vector<int>&);
    void WriteToFile(const ViewCommand::Entry& , const uint32& aEntityId, const int& aSkillId, const RefTarget& aRefTarget, const Vector3& aDir, const vector<SharedPtr<Unit> >& aEffTargetIdArr, const uint32& aProjectileEntityId);
    void WriteToFile(const ViewCommand::Entry& aCommand, const uint32& aUtilizerId, const char* aSocketName, const uint32& aTargetId, const char* aAnimName, const int& offsetX, const int& offestY);


	template<typename F, typename... A>
	void WriteCommandToPb(const ViewCommand::Entry& aCommand, TBattleViewCmd &aBattleViewCmd, F aFirst, A... aArgs) {
		aBattleViewCmd.add_args(aFirst);
		WriteCommandToPb(aCommand, aBattleViewCmd, aArgs...);
	}
	inline void WriteCommandToPb(const ViewCommand::Entry& aCommand, TBattleViewCmd &aBattleViewCmd) {
	}


    template<typename... A>
    void WriteToFile(const ViewCommand::Entry& aCommand, A... aArgs)//第一层派发 第二层限制 int32
    {
		TBattleViewCmd* pBattleViewCmd = mBattleViewCmdList.add_cmds();
		TryWriteTime(*pBattleViewCmd);
		pBattleViewCmd->set_cmdentry(aCommand.GetInfoTyple());
		WriteCommandToPb(aCommand, *pBattleViewCmd, aArgs...);
	}
};