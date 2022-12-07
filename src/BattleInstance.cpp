
#include "BattleInstance.h"
#include "View/BattleViewOutput.h"
#include "Entity/Army.h"
#include "Skill/SkillCarrier.h"
#include "Skill/Skill.h"
#include "ConfigMgr/ConfigMgr.h"
#include "Log/Log.h"
#include "Framework/SharedPool.h"
#include "Framework/Util.h"
#include "ThirdParty/mt19937ar.h"
#include "net/BattleBase.pb.h"
#include "net/Battle.pb.h"
#include "net/BattleViewCmd.pb.h"
//#include "Path/PathFindingMgr.h"
#include "Framework/KuhnMunkres.h"

using std::string;

int FindSpotGroupId(const string& aName)
{
	int len = aName.length();
	int gid = 0;
	for (int idx = 0; idx < len; idx++)
	{
		if (aName[idx] == '@')
		{
			idx++;
			gid = atoi(aName.substr(idx, len - idx).c_str());
			break;
		}
	}
	return gid;
}

/*
local CalDist2 = function(A, B)
	local dist2 = math.floor(math.abs(A.x * 10 - B.x * 10) + 0.01)^2 + math.floor(math.abs(A.z * 10 - B.z * 10) + 0.01)^2
    dist2 = math.floor(dist2) 
    return -dist2
end
*/
int CalDist2(Vector3 A, Vector3 B)
{
	int dist2 = ((A.x - B.x) / DENOM) * ((A.x - B.x) / DENOM) + ((A.z - B.z) / DENOM) * ((A.z - B.z) / DENOM);
	return -dist2;
}


DirectedPosition DirectedPosition::Create(const Vector3& aPos, const Vector3& aRot)
{
	DirectedPosition ret;
	ret.mName = "Default";
	ret.mPos.Set(aPos);
	ret.mRot.Set(aRot);
	ret.mGroupId = 0;
	return ret;
}

DirectedPosition DirectedPosition::Create(const PbVector3_Int& aPos, const PbVector3_Int& aRot, const string& aName, int aIdx)
{
	DirectedPosition ret;
	ret.mName = aName;
	ret.mPos = Vector3(
		CONF_POS_CONVERT(aPos.x()),
		CONF_POS_CONVERT(aPos.y()),
		CONF_POS_CONVERT(aPos.z())
	);
	ret.mRot = Vector3(
		CONF_POS_CONVERT(aRot.x()),
		CONF_POS_CONVERT(aRot.y()),
		CONF_POS_CONVERT(aRot.z())
	);
	ret.mGroupId = FindSpotGroupId(aName);
	return ret;
}


void RageSkillExecuteState::Reset()
{
    mUtilizer = nullptr;
    mUnpausedTargetArr.clear();
}


int BattleInstance::HpToRageNum = 0;
int BattleInstance::HpToRageDenom = 1;
int BattleInstance::KillToRage = 2;
int BattleInstance::GravityAccel = CONF_ACC_CONVERT_SEC(980);

int BattleInstance::BlockRate = 5000;

int BattleInstance::AvoidOverlapCoef1 = 20000;
int BattleInstance::AvoidOverlapCoef2 = 50000;
int BattleInstance::AvoidOverlapCoef3 = 100000;
int BattleInstance::AvoidOverlapCoef4 = 400;
int BattleInstance::AvoidOverlapCoef5 = 400;

int64 BattleInstance::DamageUpLimit = LIMIT;

DirectedPosition BattleInstance::mDefaultDirectedPosition = DirectedPosition();

Vector2 BattleInstance::gVectorZero = Vector2(0, 0);

vector<int64> BattleInstance::ATTR_LIMITS = vector<int64>(static_cast<int>(EAttribute::_Count));
vector<int64> BattleInstance::ATTR_LIMITS_UP = vector<int64>(static_cast<int>(EAttribute::_Count));

vector<int64> BattleInstance::BossHpRange = vector<int64>(0);
vector<int> BattleInstance::BossHpRangeGrowth = vector<int>(0);



BattleInstance::BattleInstance()
    : mBattleResult(EBattleResult::None)
    , mFsm(SharedPtr<Fsm>(new Fsm(FSM_NAME)))
    , mView(SharedPtr<BattleViewOutput>(new BattleViewOutput()))
    , mPhysics(SharedPtr<PhysicsSystem>(new PhysicsSystem(3)))  //ADD Barrier to Agent Group, so capacity 2 -> 3
	, mBattleEventDispatcher(SharedPtr<EventDispatcher<int, const BattleEvent&>>(new EventDispatcher<int, const BattleEvent&>()))
    , mFixedFrameDelta(FIXED_FRAME_DELTA_MS) 
    , mTimeLimit(0) 
	, mTimeExtra(0) 
	, mRecordMode(true)
    , mTimerMgr(SharedPtr<TimerMgr>(new TimerMgr(16)))
    , mBornPointArr1(vector<DirectedPosition>(0))  //init in InitNextField
    , mBornPointArr2(vector<DirectedPosition>(0))
    , mStandPointArr(vector<DirectedPosition>(0))
    , mCenterPointArr(vector<DirectedPosition>(0))
    , mSummonPointArr1(vector<DirectedPosition>(0))
    , mSummonPointArr2(vector<DirectedPosition>(0))
	, BossAttributeAdd(vector<int64>(0))
    , mArmy1(SharedPtr<Army>(new Army(1, *this, *mView, *mPhysics, mBornPointArr1, mSummonPointArr1, mCenterPointArr)))
    , mArmy2(SharedPtr<Army>(new Army(2, *this, *mView, *mPhysics, mBornPointArr2, mSummonPointArr2, mCenterPointArr)))
    , mSkillCarrierArr(vector<SharedPtr<SkillCarrier> >(0))
    , mSkillExecCountMap(unordered_map<int, SkillCount>(0))
    , mRand(SharedPtr<MersenneTwister>(new MersenneTwister()))
	//, mPathMgr(new PathFindingMgr())
	, mSceneMgr(new SceneManager())
	, mNodeSize(50000)   //TODO: in conf
{
	LOG_DEBUG("BattleInstance created");
}

BattleInstance::~BattleInstance()
{
	//delete mPathMgr;
	delete mSceneMgr;
	//if (mWheelWarFieldSt) delete mWheelWarFieldSt;
	mBattleEventDispatcher->Clear();
	mRecordInputArr.clear();
    for (auto& rageExecute : mRageSkillExecuteStateArr)
	{
		SharedPool<RageSkillExecuteState>::PutRaw(rageExecute);
	}
    LOG_DEBUG("~BattleInstance");
}

void BattleInstance::RecordUserInput(int aEid, EBattleInput aEvent, int aData)
{
	if (!mRecordMode) return;
	if (mRecordInputArr.size() > MAX_USER_INPUT_NUM) return;
	mRecordInputArr.emplace_back(TFieldInput());
	mRecordInputArr.back().eid = static_cast<uint32>(aEid);
	mRecordInputArr.back().event = (static_cast<uint32>(aEvent));
	mRecordInputArr.back().fieldnum = (static_cast<uint32>(mSceneMgr->CurSceneId));
	mRecordInputArr.back().frametime = (static_cast<uint32>(mFrameTime));
	mRecordInputArr.back().data1 = (static_cast<uint32>(aData));
	mRecordInputArr.back().index = (static_cast<uint32>(mUserInputIndex));
	mUserInputIndex = mUserInputIndex + 1;
}

void BattleInstance::LoadGlobalConfig()
{
    //values from BattleConfig 
    auto* battleConf = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
    auto& hpToRage = battleConf->GetHpToRage();
	auto& sepCoef = battleConf->GetBattleSeparateCoef();
	auto killToRage = battleConf->GetKillToRage();

	auto& attrLimit = battleConf->GetAttrLimit();
	fill(ATTR_LIMITS.begin(), ATTR_LIMITS.end(), 0);
	for (int idx = 0; idx < attrLimit.size(); idx++)
	{
		auto& oneAttr = attrLimit[idx];
		if (oneAttr[0] < ATTR_LIMITS.size())
		{
			ATTR_LIMITS[oneAttr[0]] = oneAttr[1];
		}
	}

    BattleInstance::HpToRageNum = hpToRage[0];
    BattleInstance::HpToRageDenom = hpToRage[1];
	BattleInstance::KillToRage = killToRage;
    BattleInstance::GravityAccel = CONF_ACC_CONVERT_SEC(battleConf->GetDefaultDownAcceleration());
	BattleInstance::AvoidOverlapCoef1 = 0;
	BattleInstance::AvoidOverlapCoef2 = 60000;
	BattleInstance::AvoidOverlapCoef3 = 80000;
	BattleInstance::AvoidOverlapCoef4 = sepCoef[3];
	BattleInstance::AvoidOverlapCoef5 = sepCoef[4];

	BattleInstance::BlockRate = battleConf->GetBlockDamageCoef();

	BattleInstance::DamageUpLimit = battleConf->GetBattleDamageNumMax();

	auto& attrLimitUp = battleConf->GetBattleAttrNumMax();
	fill(ATTR_LIMITS_UP.begin(), ATTR_LIMITS_UP.end(), 0);
	for (int idx = 0; idx < attrLimitUp.size(); idx++)
	{
		auto& oneAttr = attrLimitUp[idx];
		if (oneAttr[0] < ATTR_LIMITS_UP.size())
		{
			ATTR_LIMITS_UP[oneAttr[0]] = oneAttr[1];
		}
	}
}

int BattleInstance::GenerateEventKey(int aMajorKey, int aSubKey)
{
	return aMajorKey * 100 + aSubKey;
}

int BattleInstance::GetUserInputSize()
{
	if (mArgs && mArgs->has_recordinputs())
	{
		mRecordMode = false;
		return mArgs->recordinputs().input_size();
	}
	return 0;
}

const TBattleFieldInput& BattleInstance::GetUserInput(int aIndex)
{
	for (int i = 0; i < mArgs->recordinputs().input_size(); i++)
	{
		const auto& tmp = mArgs->recordinputs().input(i);
		if (tmp.index() == aIndex)
		{
			return tmp;
		}
	}
	//LOG_FATAL("invalid user input index: %d, cur size: %d", aIndex, mArgs->userinput_size());
	const auto& tmp = mArgs->recordinputs().input(0);
	return tmp;
}

int BattleInstance::InitWithRetPbStr(const char* aBattleRes, int aBattleResLen)
{
	TBattleResult* pbMsg = new TBattleResult;
	if (pbMsg->ParsePartialFromArray(aBattleRes, aBattleResLen) == false)
	{
		delete pbMsg;
		LOG_FATAL("parse battle ret failed");
		return -1;
	}
	TBattleArgs* pbMsg2 = new TBattleArgs;
	pbMsg2->MergeFrom(pbMsg->battleargs());
	delete pbMsg;
	//return InitWithPbObj(pbMsg2);
	return InitWithPbObjArcher(pbMsg2);
}

int BattleInstance::InitWithPbStr(const char* aBattleArgs, int aBattleArgsLen)
{
	TBattleArgs* pbMsg = new TBattleArgs;
	if (pbMsg->ParsePartialFromArray(aBattleArgs, aBattleArgsLen) == false)
	{
		delete pbMsg;
		LOG_FATAL("parse battle args failed");
		return -1;
	}

	//return InitWithPbObj(pbMsg);
	return InitWithPbObjArcher(pbMsg);
}

void BattleInstance::SetRandSeed(int aSeed)
{
	mRand->init_genrand(aSeed);
}

int BattleInstance::InitWithPbObjArcher(TBattleArgs* aPbMsg)
{
	mArgs = SharedPtr<TBattleArgs>(aPbMsg);
	mIsPVE = true;
	mBattleId = mArgs->battleid();
	mBattleStarter = mArgs->battlestarter();
	mAuto = false;
	mAIPath = true;
	mVFrameTimeRemain = 0;
	mFrameTime = 0;
	mGameTime = 0;
	mArmy1DyingEnd = 0;
	mArmy2DyingEnd = 0;
	mNeedDoStatistics = false;

	mSceneMgr->InitSceneManager(aPbMsg);

	mView->Init(*this);

	LOG_INFO("randomseed %u", mArgs->randomseed());
	mRand->init_genrand(mArgs->randomseed());

	mArmy1Index = -1;
	mArmy2Index = -1;
	mRageSkillMaskArmy = nullptr;

	InitFsm();
	InitNextFieldArcher();

	return 0;
}

int BattleInstance::InitWithPbObj(TBattleArgs* aPbMsg)
{
	mArgs = SharedPtr<TBattleArgs>(aPbMsg);

	const auto& battleType = mArgs->battletype();
	mIsPVE = battleType == EBattleTypeRPGPVE || battleType == EBattleTypeSLGPVE;
	mIsSLG = battleType == EBattleTypeSLGPVE || battleType == EBattleTypeSLGPVP;

	mBattleId = mArgs->battleid();
	/*auto tmp = mArgs->behavioridarr();
	for (auto v : tmp)
	{
		LOG_DEBUG("v = %d", v);
	}*/
	LoadBossGrowthAttr();  //增长型BOSS战 
	mBattleStarter = mArgs->battlestarter();
	//mBattleStarter = pb::EBattleStarter::EBattleCrossCollaborate;  // TODO: DONT FORGET TO DELETE IT! 
	if (mBattleStarter == pb::EBattleStarter::EBattleBoss)
	{
		//mIsNoBlackScreen = true;
	}

	mAuto = mArgs->extraoption().needauto();
	mAIPath = true;
	//if (mIsTD) mAIPath = false;
    mVFrameTimeRemain = 0;
    mFrameTime = 0;
	mGameTime = 0;
	mArmy1DyingEnd = 0;
	mArmy2DyingEnd = 0;
    mView->Init(*this); 
	LOG_INFO("randomseed %u", mArgs->randomseed());
    mRand->init_genrand(mArgs->randomseed());

	mNeedDoStatistics = mArgs->extraoption().needdostatistics();
	//mNeedDoStatistics = true;

    //values from SceneEditor  <---
    const string* lastConfName = nullptr;
    const SceneConf3d* sceneConf;
    mFieldConfArr.reserve(aPbMsg->sceneconf_size());
    mTimeLimitArr.reserve(aPbMsg->sceneconf_size());
    for (auto& conf : aPbMsg->sceneconf())
    {
        if (!lastConfName || *lastConfName != conf.confname())
        {
            lastConfName = &conf.confname();
            sceneConf = ConfigMgr::GetConfByIndex<SceneConf3d>(FIELD_CONF_COL_NAME, *lastConfName)[0];
        }
		if (sceneConf && conf.confindex() >= static_cast<uint32>(sceneConf->fieldconfarr_size()))
		{
			LOG_FATAL("sceneConf3D->fieldconfarr_size{%d} <= battleArgs.secneConf.confindex{%d}", sceneConf->fieldconfarr_size(), conf.confindex());
			return -1;
		}
        mFieldConfArr.push_back(sceneConf->fieldconfarr(conf.confindex()));
        mTimeLimitArr.push_back(conf.timelimit() * MS_OF_SEC);
    }
    //mSceneMgr->TotalFieldNum = static_cast<int>(mFieldConfArr.size());
    //mSceneMgr->CurSceneId = 0;

    if (mSceneMgr->TotalFieldNum <= 0) {
		LOG_FATAL("mSceneMgr->TotalFieldNum{%d} <= 0", mSceneMgr->TotalFieldNum);
        return -1;
    }

    mArmy1Index = -1;
    mArmy2Index = -1;
	mRageSkillMaskArmy = nullptr;

    InitFsm();
    InitNextField();
	
	ResetTimelimit(mTimeLimitArr[mSceneMgr->CurSceneId]);
	//mSceneMgr->CurSceneId = mSceneMgr->CurSceneId + 1;

    return 0;
}

void BattleInstance::InitFsm()
{
    mStateEnterField = mFsm->AddState(STATE_ENTERFIELD);
    mStateEnterField->SetOnEnter(MakeFunction<>(*this, &BattleInstance::ActionEnterNextField));
    mStateNormal = mFsm->AddState(STATE_NORMAL);
    mStateNormal->SetOnTick(MakeFunction<>(*this, &BattleInstance::ActionTickNormal));
	mStateCutscene = mFsm->AddState(STATE_CUTSCENE);
	mStateCutscene->SetOnEnter(MakeFunction<>(*this, &BattleInstance::ActionEnterCutscene));
	mStateCutscene->SetOnTick(MakeFunction<>(*this, &BattleInstance::ActionTickCutscene));
    mStateRageInput = mFsm->AddState(STATE_RAGEINPUT);
    mStateRageInput->SetOnTick(MakeFunction<>(*this, &BattleInstance::ActionTickRageSkillExecute));
    mStateRageInput->SetOnExit(MakeFunction<>(*this, &BattleInstance::ActionExitRageInput));
	mStateEndShow = mFsm->AddState(STATE_ENDSHOW);
	mStateEndShow->SetOnEnter(MakeFunction<>(*this, &BattleInstance::ActionEnterEndShow));
    auto stateError = mFsm->AddState(STATE_ERROR);
    stateError->SetOnEnter(MakeFunction<>(*this, &BattleInstance::ActionEnterError));

	//等fsm被第一次tick的时候进行跳转
    mFsm->AddTransition(mFsm->GetStartState(), *mStateEnterField, TransitionMode::Auto);
    mFsm->AddTransition(*mStateEnterField, *mStateNormal, TransitionMode::Auto);
    mTransBattleEnd = mFsm->AddTransition(*mStateNormal, *mStateEndShow, TransitionMode::Auto);
    mTransBattleEnd->SetCondition(MakeFunction<>(*this, &BattleInstance::CondiBattleEnd));
    auto transCutscene = mFsm->AddTransition(*mStateNormal, *mStateCutscene, TransitionMode::Auto);
    transCutscene->SetCondition(MakeFunction<>(*this, &BattleInstance::CondiCurrentFieldEnd));
    mTransCutsceneEnd = mFsm->AddTransition(*mStateCutscene, *mStateEnterField, TransitionMode::Manual);
    mTransRageInputBegin = mFsm->AddTransition(*mStateNormal, *mStateRageInput, TransitionMode::Manual);
    mTransRageInputEnd = mFsm->AddTransition(*mStateRageInput, *mStateNormal, TransitionMode::Manual);
    mTransBattleError = mFsm->AddTransition(mFsm->GetAnyState(), *stateError, TransitionMode::Manual);
}

//satisfied iff all Armies from mArmy1 side have been Eliminated
bool BattleInstance::CondiBattleEnd(bool)
{
    if (mArmy1->IsEliminated() && mArmy1Index >= mArgs->army1arr_size() - 1)  //mTimeExtra == 0 &&
    {
        //fail
        //LOG_INFO("Battle fail, army1 eliminated.");
        mBattleResult = EBattleResult::Lose;
        return true;
    }
    return false;
}


//satisfied iff current Army2 is Eliminated AND there are Fields or Other Army2s haven't been reached
//inside this Condi, it will DoTransition to BattleEnd State when it's OK to do so and return False
bool BattleInstance::CondiCurrentFieldEnd(bool)
{
	if (mArmy2->ConditionIsEliminated(mBattleStarter) && mTimeExtra == 0)
    { //if somebody has set extra time, it's behaviour condi and should wait to timeup 
        if (!mSceneMgr->HasNextScene() || mArmy2Index + 1 >= mArgs->army2arr_size())
        { //if no more field or no more enemy, victory
            mBattleResult = EBattleResult::Victory;
            mFsm->DoTransition(mTransBattleEnd);
			return false;
        }
		else if ((mArmy1->ConditionIsEliminated(mBattleStarter) || mArmy1->IsOnlySummonedLeft()) && mArmy1Index >= mArgs->army1arr_size() - 1)
		{ //final lose 
			mBattleResult = EBattleResult::Lose;
			mFsm->DoTransition(mTransBattleEnd);
			return false;
		}
        else
        { //else, to cutscene
            return true;
        }
    }

    return false;
}

void BattleInstance::ActionEnterError()
{
    mBattleResult = EBattleResult::Error;
    //TODO
}

// will clean up part of SkillExecCountMap, InitNextField and do mArmy->OnEnterCutscene
// auto trans to EnterField state at the end
void BattleInstance::ActionEnterCutscene()
{
	if (mRageSkillMaskArmy)
	{
		RageSkillMaskEnd();
	}
    for (auto& count : mSkillExecCountMap)
    {
        count.second.mScreenTotal = 0;
    }
    mArmy1->OnEnterCutscene(); // remove some of Summoned Units from mUnitArr, run unit->OnEnterCutscene for others
    mArmy2->OnEnterCutscene();
	for (int i = 0; i < mSkillCarrierArr.size(); ++i)
	{
		mSkillCarrierArr[i]->Cancel();
	}
	mSkillCarrierArr.clear();
    //InitNextField();
	InitNextFieldArcher();
    //mView->Execute(ViewCommand::Cutscene);
	ResetTimelimit(mTimeLimitArr[mSceneMgr->CurSceneId]);
	//mSceneMgr->CurSceneId = mSceneMgr->CurSceneId + 1;
}

void BattleInstance::InitNextFieldArcher()
{
	mSceneMgr->InitNextField();

	mBornPointArr1.clear();
	mBornPointArr2.clear();
	mStandPointArr.clear();
	mCenterPointArr.clear();
	mSummonPointArr1.clear();
	mSummonPointArr2.clear();

	mBornPointArr1.push_back(DirectedPosition::Create(mSceneMgr->mCurBornPoint, SceneManager::defaultPositiveDir));

	for (int i = 0; i < mSceneMgr->mCurStandPointArr.size(); ++i)
	{
		auto pos = mSceneMgr->mCurStandPointArr[i];
		mBornPointArr1.push_back(DirectedPosition::Create(pos, SceneManager::defaultNegtiveDir));
		mStandPointArr.push_back(DirectedPosition::Create(pos, SceneManager::defaultNegtiveDir));
		mCenterPointArr.push_back(DirectedPosition::Create(pos, SceneManager::defaultNegtiveDir));
		mSummonPointArr1.push_back(DirectedPosition::Create(pos, SceneManager::defaultPositiveDir));
		mSummonPointArr2.push_back(DirectedPosition::Create(pos, SceneManager::defaultNegtiveDir));
	}

	//refresh eliminated army 
	int eliminated = -1;			//第一场是-1，后续场一律为Army2的Id 
	if (mSceneMgr->CurSceneId > 0) 
		eliminated = mArmy2->GetId(); 

	if (mArmy1->IsEliminated())
	{
		++mArmy1Index;	//该数值初始时为 -1 
		InitArmyWith(mArmy1, mArgs->army1arr(mArmy1Index));
	}
	if (mArmy2->IsEliminated())
	{
		++mArmy2Index;
		InitArmyWith(mArmy2, mArgs->army2arr(mArmy2Index));
	}
	//field init done
	mView->Execute(ViewCommand::FieldInit, *mArmy1.Get(), *mArmy2.Get(), eliminated);
}


// load Battle_Area: adjusted point list as outline
// load Spawn Point for both Army, set Stand Point
// if be elimnated, InitArmyWith( mArgs )
// run view->Execute
void BattleInstance::InitNextField()
{
    //get next field conf
    mFieldConf = &mFieldConfArr[mSceneMgr->CurSceneId];
    auto& rootPos = mFieldConf->rootposition();
    //refresh field boundary array
    mFieldAreaPointArr.clear();
	mFieldBlockLineArr.clear();
	mColStrips.clear();
	mRowStrips.clear();
	vector<Vector2> boundaryArr;
	int64 xMax = 0;
	int64 zMax = 0;
	mBossTotalDamageUndertake = 0;
	mBossGrowthLevel = 0;
	int blockLineIdx = 0;
    for (auto& area : mFieldConf->customareaarr())
    {
        if (area.elementtype() == ESceneElementType::BATTLE_AREA)
        {
            for (const auto& point : area.pointarr())
            {
                mFieldAreaPointArr.emplace_back(Vector3(
                    CONF_POS_CONVERT(point.x() - rootPos.x()),
                    CONF_POS_CONVERT(point.y() - rootPos.y()),
                    CONF_POS_CONVERT(point.z() - rootPos.z())
                ));
				Vector2 tmp = Vector2(
					CONF_POS_CONVERT(point.x() - rootPos.x()),
					CONF_POS_CONVERT(point.z() - rootPos.z()));
				boundaryArr.emplace_back(tmp);
				xMax = Abs(tmp.x) > xMax ? Abs(tmp.x) : xMax;
				zMax = Abs(tmp.z) > zMax ? Abs(tmp.z) : zMax;
            }
        }
		if (area.elementtype() == ESceneElementType::BATTLE_BLOCK_LINE)
		{
			if (area.pointarr_size() == 2)
			{
				vector<Vector3> tmpList;
				for (const auto& point : area.pointarr())
				{
					tmpList.emplace_back(Vector3(
						CONF_POS_CONVERT(point.x() - rootPos.x()),
						0,
						CONF_POS_CONVERT(point.z() - rootPos.z())
					));
				}
				if (blockLineIdx != area.index())
				{
					LOG_WARN("invalid block line idx, given %d, want %d", area.index(), blockLineIdx);
				}
				else
				{
					blockLineIdx++;
				}
				mFieldBlockLineArr.emplace_back(tmpList);
			}
		}
    }
	auto& fastFilterConf = mFieldConf->filter();
	mStripD = CONF_POS_CONVERT(fastFilterConf.stripwidth());	//all map should use strip filter 

	int curIdx = 0;
	for (auto& stripInfo : fastFilterConf.colstrips())
	{
		if (stripInfo.index() != curIdx)
		{
			LOG_WARN("Invalid stripInfo index, given %d, expect %d", stripInfo.index(), curIdx);
		}
		else
		{
			mColStrips.emplace_back(vector<int>(0));
			auto& tmp = mColStrips.back();
			tmp.reserve(stripInfo.blocklinearr_size());
			for (int blockId : stripInfo.blocklinearr())
			{
				tmp.emplace_back(blockId);
			}
		}
		curIdx++;
	}
	curIdx = 0;
	for (auto& stripInfo : fastFilterConf.rowstrips())
	{
		if (stripInfo.index() != curIdx)
		{
			LOG_WARN("Invalid stripInfo index, given %d, expect %d", stripInfo.index(), curIdx);
		}
		else
		{
			mRowStrips.emplace_back(vector<int>(0));
			auto& tmp = mRowStrips.back();
			tmp.reserve(stripInfo.blocklinearr_size());
			for (int blockId : stripInfo.blocklinearr())
			{
				tmp.emplace_back(blockId);
			}
		}
		curIdx++;
	}
	if (mStripD > 0)
	{
		int halfWidth = xMax - mStripD / 2;
		mHalfCol = halfWidth % mStripD == 0 ? halfWidth / mStripD : halfWidth / mStripD + 1;
		int halfLength = zMax - mStripD / 2;
		mHalfRow = halfLength % mStripD == 0 ? halfLength / mStripD : halfLength / mStripD + 1;
	}

	vector<vector<Vector2>> blockArea;
	for (auto& area : mFieldConf->rectareaarr())
	{
		if (area.elementtype() == ESceneElementType::OBSTACLE)
		{
			int centerX = area.centerposition().x();
			int centerZ = area.centerposition().z();
			int halfX = centerX - area.rectinfo().minpoint().x();
			int halfZ = centerZ - area.rectinfo().minpoint().y();
			Vector2 posMin = Vector2(
				CONF_POS_CONVERT(centerX - halfX),
				CONF_POS_CONVERT(centerZ - halfZ));
			Vector2 posMax = Vector2(
				CONF_POS_CONVERT(centerX + halfX),
				CONF_POS_CONVERT(centerZ + halfZ));
			vector<Vector2> tmpList; 
			tmpList.emplace_back(posMin);
			tmpList.emplace_back(posMax);
			blockArea.emplace_back(tmpList);
		}
	}
    if (mFieldAreaPointArr.size() < 3)
    {
        LOG_FATAL("field area point array size < 3 (not a polygon)");
    } 
	if (mAIPath)
	{  //init path mgr if needed
		if (mStripD > mNodeSize)
		{
			mNodeSize = mStripD / 2; 
		}
		//mPathMgr->InitMap(2 * xMax, 2 * zMax, Vector2(mNodeSize, mNodeSize), Vector2(0, 0));
		//mPathMgr->ApplyBoundaryNodes(boundaryArr);
		for (auto& subBlock : blockArea)
		{
			//mPathMgr->ApplyBlockArea(subBlock);
		}
		//mPathMgr->mJustNavigate = true;  //NPC 寻路不考虑 PresetLocation (地表涂鸦) 
	}
    //refresh born points
    mBornPointArr1.clear();
    mBornPointArr2.clear();
	mStandPointArr.clear();
	mCenterPointArr.clear();
	mSummonPointArr1.clear();
	mSummonPointArr2.clear();
    auto& points = mFieldConf->pointelementarr();
    for (auto& point : points)
    {
        if (point.elementtype() == SPAWN_SPOT)
        {
            const string& name = point.name();
            if (name[0] == 'S')//starts with SpawnSpot
            {
                mBornPointArr1.push_back(DirectedPosition::Create(point.position(), point.direction(), name, point.pathtrackindex()));
            }
            else if (name[0] == 'E')//starts with EnemySpawnSpot
            {
                mBornPointArr2.push_back(DirectedPosition::Create(point.position(), point.direction(), name, point.pathtrackindex()));
            }
        }
        else if (point.elementtype() == HOLD_SPOT)
        {
            mStandPointArr.push_back(DirectedPosition::Create(point.position(), point.direction(), point.name()));
        }
		else if (point.elementtype() == CENTER_SPOT)
		{
			mCenterPointArr.push_back(DirectedPosition::Create(point.position(), point.direction(), point.name()));
		}
		else if (point.elementtype() == SUM_SPOT)
		{
			/*const string& name = point.name();
			int gid = FindSpotGroupId(name);
			auto& spArr = GetSumSpotArrByName(name);
			int s = spArr.size();
			if (gid >= s)
			{
				for (int i = s; i <= gid; i++)
				{
					vector<DirectedPosition> tmp;
					spArr.emplace_back(tmp);
				}
			}
			auto& tmp = spArr[gid];
			tmp.push_back(DirectedPosition::Create(point.position(), point.direction(), name));*/
		}
    }

	//try record field status for wheelwar
	RecordFieldStatus();

    //refresh eliminated army
    int eliminated = -1;
    if (mArmy1->IsEliminated() )
    {
		eliminated = mArmy1->GetId();
		if (!mArmy1->IsEliminated())
			eliminated = -1;  //-1
        ++mArmy1Index;
        InitArmyWith(mArmy1, mArgs->army1arr(mArmy1Index));
    }
    if (mArmy2->IsEliminated())
    {
		if (eliminated < 0)
		{ //army1 is alived at least
			if (!mArmy2->IsEliminated())
			{ //in gourp match, if army2 is also alived, set army1 lose
				eliminated = mArmy1->GetId();
			}
			else
			{ //army2 is eliminated	
				eliminated = mArmy2->GetId();
			}
		}
		else
		{ //both army eliminated == uninitialized armies	
			eliminated = -1; 
		}
        ++mArmy2Index;
        InitArmyWith(mArmy2, mArgs->army2arr(mArmy2Index));
    }
    //field init done
    mView->Execute(ViewCommand::FieldInit, *mArmy1.Get(), *mArmy2.Get(), eliminated);
	//refresh destructable objects
	mDestructableArr.clear();
    int dtc = -1;
	for (const auto& destructConf : mFieldConf->destructablearr())
	{
        ++dtc;
        if (destructConf.tid() == 0)
        {
            continue;
        }
		auto dest = SharedPool<DestructableObject>::Get();
		mDestructableArr.push_back(dest);
		dest->Init(*this, *mView, *mPhysics, &destructConf, dtc);
	}
	
}


// hooked on EnterField State as OnEnter method
// maintain mVariables like: mSceneMgr->CurSceneIdNum, TimeLimit
// run Army->OnEnterField
// DoTrans from EnterField State to Normal State
void BattleInstance::ActionEnterNextField()
{
    mArmy1->OnEnterField();  // set Born Pos to each Unit, run Unit->OnEnterField method respectively 
    mArmy2->OnEnterField();
    for (auto& destructable : mDestructableArr)
    {
        destructable->Activate();
    }
    //mFsm->DoTransition(mTransFieldInitDone);
}

// hooked on EndShow State as OnEnter method
// View Execute using param mBattleResult
void BattleInstance::ActionEnterEndShow()
{
	mView->Execute(ViewCommand::Cutscene, 1);  //info frontend that battle is actually ended 
	mArmy1->OnEnterBattleEnd();
	mArmy2->OnEnterBattleEnd();
    mView->Execute(ViewCommand::EndShow, static_cast<int>(mBattleResult));
	LOG_DEBUG("Battle ended {reason=%s}", EBattleResultNames[static_cast<int>(mBattleResult)]);
}

bool BattleInstance::ActionTickCutscene(int)
{
	mFsm->DoTransition(mTransCutsceneEnd);
	return false;
}

// hooked on Normal State as OnTick method
// accumulate mFrameTime, let TimerMgr do OnTick, handle/tick all SkillCarrier, and run Army->OnTick 
// finally check if is timeup
bool BattleInstance::ActionTickNormal(int aFrameDelta)
{
	mFrameTime += mFixedFrameDelta;
	mGameTime += mFixedFrameDelta;

	UpdatePlayerPositionAndRotation(); 

	mArmy1->TryExecuteArmySkill(mGameTime, mSceneMgr->CurSceneId);
	mArmy2->TryExecuteArmySkill(mGameTime, mSceneMgr->CurSceneId);
    mTimerMgr->OnTick(mFrameTime);
	mArmy1->OnTick(aFrameDelta);
	mArmy2->OnTick(aFrameDelta);

    for (int s = 0; s < mSkillCarrierArr.size(); ++s)
    {
        auto& carrier = mSkillCarrierArr[s];
        if (carrier->IsEnded() || !carrier->OnTick(mFixedFrameDelta))
        {
            if (carrier.Get() != mSkillCarrierArr.back().Get())
            {
                mSkillCarrierArr[s] = mSkillCarrierArr.back();
            }
            mSkillCarrierArr.pop_back();
			--s;  //FIX a bug not exec last skill
        }
    }

    //timeup
    if (mGameTime >= mTimeLimit + mTimeExtra)
    {
		mBattleResult = EBattleResult::Timeup;
		mFsm->DoTransition(mTransBattleEnd);
    }
    return false;
}

// hooked on RageInput State as OnTick method, may also set to Normal state as well
// accumulate mFrameTime, adjust aFrameDelta with SkillMaskCountdown
// tick every SkillActiveUtilizer, tick every SkillActiveCarrier within Mask time
// quit from Mask time is Countdown < 0
bool BattleInstance::ActionTickRageSkillExecute(int aFrameDelta)
{
	mFrameTime += mFixedFrameDelta;
	bool inMaskTime = false;
	vector<Unit*> activeUnits(mRageSkillActiveUtilizerArr);
    for (auto& unit : activeUnits)
    {
        unit->OnTick(aFrameDelta);
		inMaskTime = inMaskTime || unit->IsInRageSkillMaskTime();
    }
    for (int s = 0; s < mRageSkillCarrierArr.size(); ++s)
    {
        auto& carrier = mRageSkillCarrierArr[s];
		if (&carrier->GetOwner()->GetArmy() == mRageSkillMaskArmy)
		{
			if (carrier->IsEnded() || !carrier->OnTick(aFrameDelta))
			{
				mRageSkillCarrierArr[s] = mRageSkillCarrierArr.back();
				mRageSkillCarrierArr.pop_back();
				--s;
			}
		} 
    }
    if (!inMaskTime)
        RageSkillMaskEnd();
    return false;
}


// switch all WaitForInput State to Begin State in mRageSkillExecuteStateArr
// Unpause those Units as well
void BattleInstance::ActionExitRageInput()
{
    //恢复正在等待输入的大招释放者 
    for (auto& rageExecute : mRageSkillExecuteStateArr)
    {
        if (rageExecute->mStatus == ERageSkillExecuteStatus::WaitForInput)
        {
            rageExecute->mStatus = ERageSkillExecuteStatus::Begin;
            UnpauseUnit(rageExecute->mUtilizer, true);
        }
    }
}

void BattleInstance::RecordFieldStatus()
{
	return;
}

void BattleInstance::InitArmyWith(const SharedPtr<Army>& aArmy, const TArmyInfo& aArmyConf)
{
	if (mSceneMgr->CurSceneId > 0)
		aArmy->RecordUnitInfo();   //可保留 
    aArmy->Clear();
    aArmy->AddUnitByConf(aArmyConf);
	aArmy->LoadArmySkills(aArmyConf);
}

void BattleInstance::ResetTimelimit(int aTimeMs)
{
    mTimeLimit = aTimeMs;
	mTimeExtra = 0;
    mFrameTime = 0;
	mGameTime = 0;

	mArmy1DyingEnd = 0;
	mArmy2DyingEnd = 0;
    LOG_DEBUG("Reset Timelimit to %d, Frame time reset to %d", mTimeLimit, mFrameTime);
    mView->Execute(ViewCommand::ResetTimeLimit, mTimeLimit, mFrameTime);
}

TBattleResult* BattleInstance::ReportResultPb(bool aNeedCMD)
{
	if (hasReported)
	{
		LOG_FATAL("Try call ReportResultPb multi times");
		if (mResult != nullptr)
			return mResult;
		else
			return new TBattleResult;
	}

	TBattleResult* result = new TBattleResult;
	mResult = result;
	hasReported = true;
	result->set_battletime(mGameTime);
	result->set_screenindex(mSceneMgr->CurSceneId);
	TBattleArgs* args = new TBattleArgs;//will be managed by TBattleResult after "result.set_allocated_battleargs(args);"
	args->CopyFrom(*mArgs);

	if (mRecordInputArr.size() > 0)
	{
		TBattleUserInput* userInput = new TBattleUserInput;
		for (int i = 0; i < mRecordInputArr.size(); i++)
		{
			const auto& input = mRecordInputArr[i];
			TBattleFieldInput* pbInput = userInput->add_input();
			pbInput->set_eid(input.eid);
			pbInput->set_event(input.event);
			pbInput->set_fieldnum(input.fieldnum);
			pbInput->set_frametime(input.frametime);
			pbInput->set_data1(input.data1);
			pbInput->set_index(input.index);
		}
		args->set_allocated_recordinputs(userInput);
		args->set_hasuserinput(true);
	}

	result->set_allocated_battleargs(args);
	int starLevel = mArmy1->CountDead();
	if (mBattleResult != EBattleResult::Victory)
		starLevel = 0;
	else if (starLevel > 2)
		starLevel = 1;
	else if (starLevel > 1)
		starLevel = 2;
	else
		starLevel = 3;
	if (starLevel > 0 && mArgs->extraoption().isstorybattle())
	{
		starLevel = 3;
	}
	result->set_starlevel(starLevel);

	RecordFieldStatus(); //车轮战每轮结束都要执行一下这个状态记录方法 

	if (aNeedCMD)
	{
		auto tmp = mView->GetAllCmdsAsString();
		result->set_battlereportstr(tmp.c_str(), tmp.size());
	}
	mArmy1->RecordUnitInfo();
	const auto& army1 = mArmy1->GetUnitInfo();
	for (int i = 0; i < army1.size(); ++i)
	{
		FillArmyInfo(result->add_army1arr(), army1[i]);
	}
	if (mArmy1->mTDRecordDeletedArmy1Units.size() > 0)
	{
		FillArmyInfo(result->add_army1arr(), mArmy1->mTDRecordDeletedArmy1Units);
		for (int i = 0; i < mArmy1->mTDRecordDeletedArmy1Units.size(); ++i)
		{
			mArmy1->mTDRecordDeletedArmy1Units[i]->Reset();
		}
		mArmy1->mTDRecordDeletedArmy1Units.clear();
	}
	mArmy2->RecordUnitInfo();
	const auto& army2 = mArmy2->GetUnitInfo();
	for (int i = 0; i < army2.size(); ++i)
	{
		FillArmyInfo(result->add_army2arr(), army2[i]);
	}
	for (int i = 0; i < army1.size(); ++i)
	{
		for (int j = 0; j < army1[i].size(); ++j)
		{
			//LOG_WARN("reset unit %d", army1[i][j]->GetEntityId());
			army1[i][j]->Reset();
		}
	}
	for (int i = 0; i < army2.size(); ++i)
	{
		for (int j = 0; j < army2[i].size(); ++j)
		{
			//LOG_WARN("reset unit %d", army2[i][j]->GetEntityId());
			army2[i][j]->Reset();
		}
	}

	return result;
}

// fill pb::TBattleResult based on mArmy1->CountDead() and mView->ViewStr()
// return pb.SerializeAsString
// 注意：本方法只可由后端服务器逻辑调用
string BattleInstance::ReportResult()
{
	auto* result = ReportResultPb(true);
	string retStr = result->SerializePartialAsString();
	mResult = nullptr;
	delete result;
	return retStr;
}


void BattleInstance::FillArmyInfo(TArmyInfoAfterBattle* aArmyInfo, const vector<SharedPtr<Unit>>& aUnitList) const
{
    TUnitInfoAfterBattle* unitInfo;
    const TUnitInfo* inputInfo;
    uint32 hid;
    for (auto& unit : aUnitList)
    {
        if (!unit->IsSummoned() && !unit->IsDummy())
        {
            inputInfo = unit->GetUnitInfo();
            if (inputInfo)
                hid = inputInfo->hid();
            else
                hid = 0;
            unitInfo = aArmyInfo->add_unitarr();
            unitInfo->set_hid(hid);
            unitInfo->set_pos(unit->GetBornPoint());
            unitInfo->set_damagein(unit->GetDamageInTotal());
            unitInfo->set_damageout(unit->GetDamageOutTotal());
			unitInfo->set_healout(unit->GetHealOutTotal());
            unitInfo->set_curhp(unit->GetHp());
            unitInfo->set_maxhp(unit->GetMaxHp());
            unitInfo->set_currage(unit->GetRage());
			unitInfo->set_injuredsoldier(unit->GetInjuredNum());
			unitInfo->set_deadsoldier(unit->GetDeadSoldierNum());
			unitInfo->set_killenemysoldier(unit->GetKillNum());
			unitInfo->set_htid(unit->GetTplId());
			//LOG_WARN("unitInfo eid = %d, hid = %d, htid = %d, hp = %lld, pbHp = %lld", unit->GetEntityId(), hid, unit->GetTplId(), unit->GetHp(), unitInfo->curhp());
			auto unitStatistics = new TUnitStatistics;
			FillUnitInfo(unitStatistics, unit.Get());
			unitInfo->set_allocated_unitstatistic(unitStatistics);

			if (NeedDoStatistics())
			{
				auto* battleConf = ConfigMgr::GetConfById<ConfigBattleConfig>(1);
				auto& match = battleConf->GetMatchingShapeshfit();
				auto size = match.size();
				for (int idx = 1; idx < size; idx += 2)
				{
					if (unit->GetTplId() == match[idx])
					{
						unitInfo->set_htid(match[idx - 1]);
					}
				}
			}
        }
    }
}

void BattleInstance::FillUnitInfo(TUnitStatistics* aUnitInfo, Unit* aUnit) const
{
	if (!NeedDoStatistics() || !aUnit) return;
	aUnitInfo->set_totalphycialdamage(aUnit->mTotalPhycialDamage);
	aUnitInfo->set_totalmagicaldamage(aUnit->mTotalMagicalDamage);
	aUnitInfo->set_totalheal(aUnit->mTotalHeal);
	aUnitInfo->set_phycialdamageundertake(aUnit->mPhycialDamageUndertake);
	aUnitInfo->set_magicaldamageundertake(aUnit->mMagicalDamageUndertake);
	aUnitInfo->set_skillexecutecount(aUnit->mSkillExecuteCount);
	aUnitInfo->set_dodgecount(aUnit->mDodgeCount);
	aUnitInfo->set_physicalbase(aUnit->mPhysicalBase);
	aUnitInfo->set_exemptioncount(aUnit->mExemptionCount);
	aUnitInfo->set_magicalbase(aUnit->mMagicalBase);
	aUnitInfo->set_parrycount(aUnit->mParryCount);
	aUnitInfo->set_resistcount(aUnit->mResistCount);
	aUnitInfo->set_criticaldamagecount(aUnit->mCriticalDamageCount);
	aUnitInfo->set_criticaldamagebase(aUnit->mTotalDamageBase);
	aUnitInfo->set_criticalhealcount(aUnit->mCriticalHealCount);
	aUnitInfo->set_criticalhealbase(aUnit->mTotalHealBase);
	aUnitInfo->set_becriticaldamagecount(aUnit->mBeCriticalDamageCount);
	aUnitInfo->set_bedamagebase(aUnit->mTotalBeDamageBase);
	aUnitInfo->set_totalsuckblood(aUnit->mTotalSuckBlood);
	aUnitInfo->set_realheal(aUnit->mRealHeal);
	aUnitInfo->set_totalabsorbblood(aUnit->mTotalAbsorbBlood);
	int timeToLiveRate = 10000;
	if (aUnit->mTTL > 0) timeToLiveRate = aUnit->mTTL * 10000 / mGameTime;
	aUnitInfo->set_timetolive(timeToLiveRate);
	FillSkillInfo(aUnitInfo, aUnit);
}

void BattleInstance::FillSkillInfo(TUnitStatistics* aUnitInfo, Unit* aUnit) const
{
	TSkillStatistics* skillInfo;
	for (auto& skill : aUnit->GetSkillArr())
	{
		FillSkillSingle(aUnitInfo, skill.Get());
		auto& childSkill = skill->GetChildSkill();
		for (auto& chskill : childSkill) {
			FillSkillSingle(aUnitInfo, chskill.Get());
		}
	}
	for (auto& skillSt : aUnit->GetBuffSkillInfo())
	{
		TSkillStatistics* skillInfo;
		skillInfo = aUnitInfo->add_skillstatisticsarr();
		skillInfo->set_skillid(skillSt->mSkillId);
		skillInfo->set_count(skillSt->mBeginCount);
		skillInfo->set_totaleffecttarget(skillSt->mEffectCount);
	}
}

void BattleInstance::FillSkillSingle(TUnitStatistics* aUnitInfo, Skill* aSkill) const
{
	TSkillStatistics* skillInfo;
	skillInfo = aUnitInfo->add_skillstatisticsarr();
	skillInfo->set_skillid(aSkill->GetId());
	skillInfo->set_count(aSkill->mBeginCount);
	skillInfo->set_totaleffecttarget(aSkill->mEffectTargetCount);
	skillInfo->set_totalphycialdamage(aSkill->mTotalPhysicalDamge);
	skillInfo->set_totalmagicaldamage(aSkill->mTotalMagicalDamge);
	skillInfo->set_totalheal(aSkill->mTotalHeal);
	skillInfo->set_totalsuckblood(aSkill->mTotalSuckBlood);
	skillInfo->set_collisionnum(aSkill->mCollisionCount);
}

// skip Units that are StateAdjust::InvisibleDummy
// init RageSkillExecuteState, set to Show or WaitForOtherArmy State accordingly
// run WhenSomeoneStartRageSkill (&aUtilizer)
void BattleInstance::TryShowRageSkill(Unit& aUtilizer)
{
    if (aUtilizer.CheckStateAdjust(StateAdjust::InvisibleDummy))
        return;
	auto* state = SharedPool<RageSkillExecuteState>::GetRaw();
	state->mUtilizer = &aUtilizer;
	state->mStatus = ERageSkillExecuteStatus::Show;
	state->mUnpausedTargetArr.clear();
	state->mUnpausedTargetArr.reserve(4);
    aUtilizer.SetRageSkillState(state);
	
	WhenSomeoneStartRageSkill(state);
	mRageSkillExecuteStateArr.emplace(state);
}

// skip Units that are StateAdjust::InvisibleDummy
// get RageSkillExecuteState from aUtilizer
// if cur FSM State == RageInput, then set Rage State to WaitForInput
// if cur FSM State is not RageInput, just set Rage State to Begin
void BattleInstance::TryBeginRageSkill(Unit& aUtilizer)
{
    if (aUtilizer.CheckStateAdjust(StateAdjust::InvisibleDummy))
        return;
    RageSkillExecuteState* state = aUtilizer.GetRageSkillState();
	if (state == nullptr)
	{
		LOG_WARN("Try begin rage skill but state is nil, Unit tid = %d", aUtilizer.GetTplId()); 
		return;
	}
	if (false && mFsm->IsInState(mStateRageInput->GetId()))
	{ //StateRageInput is sealed by far, so normally main thread won't jump into this branch
        if (mRageSkillMaskArmy)
        { 
			PauseUnit(state->mUtilizer);
        }
		state->mStatus = ERageSkillExecuteStatus::WaitForInput; 
	}
	else
	{
		state->mStatus = ERageSkillExecuteStatus::Begin;
	}
}

bool BattleInstance::IsFieldEnd() const
{
	if (mFsm->IsInState(mStateCutscene->GetId()) || mFsm->IsInState(mStateEndShow->GetId()))
	{
		return true;
	}
	return false;
}

bool BattleInstance::IsInRageSkill(int aArmyId) const
{
	if (mRageSkillMaskArmy)
	{
		if (mRageSkillMaskArmy->GetId() == aArmyId)
		{
			return true;
		}
		// return true 
	}
	return false;
}

// skip Units that are StateAdjust::InvisibleDummy
// clean up cur RageSkillState, 
// if exists ally's RageState before Emit, find the first one and mView Pause itself as well as its mUnpausedTargetArr
void BattleInstance::EndRageSkill(Unit& aUtilizer)
{
    if (aUtilizer.CheckStateAdjust(StateAdjust::InvisibleDummy))
        return;
    RageSkillExecuteState* state = aUtilizer.GetRageSkillState();
	if (!state)
	{
		return;
	}
    aUtilizer.SetRageSkillState(nullptr);
    state->mStatus = ERageSkillExecuteStatus::End;  //TODO: delete it?
	mRageSkillExecuteStateArr.erase(state);
	
    if (mRageSkillMaskArmy)
    { 
		PauseUnit(&aUtilizer);
		for (auto& target : state->mUnpausedTargetArr)
		{			
			PauseUnit(target.Get());
		}
    }
	SharedPool<RageSkillExecuteState>::PutRaw(state);
}

// trans from Normal to RageInput State
// return if succeed
int BattleInstance::RageSkillInput()
{
    mFsm->DoTransition(mTransRageInputBegin);
    return mFsm->IsInState(mStateRageInput->GetId()) ? 1 : 0;
}

// trans from RageInput to Normal State
void BattleInstance::RageSkillInputEnd()
{
    mFsm->DoTransition(mTransRageInputEnd);
}

// the Utilizer is going to display his or her rage skill, therefore:
// will not pause aUtilizer himself
// will pause all enemy units
// will pause all team member who is not executing Rage Skill or just under RageSkillExecuteState::End State
void BattleInstance::PauseUnitWhenSomeoneStartRageSkill(SharedPtr<Army> aArmy, Unit* aUtilizer)
{
	if (aArmy == &(aUtilizer->GetArmy()))
	{ //deal with team member
		for (Unit* unit : aArmy->GetActiveUnitArr())  //TODO: use active arr
		{
			if (aUtilizer != unit)
			{
				RageSkillExecuteState* state = unit->GetRageSkillState();
				if (state == nullptr) //不在怒气技能状态的人要被暂停   
				{					
					PauseUnit(unit);
				}
				else
				{
					switch (state->mStatus)
					{
					case ERageSkillExecuteStatus::WaitForOtherArmy:	 
						break;
					case ERageSkillExecuteStatus::WaitForInput:
						LOG_WARN("should not have WaitForInput unit:%d", unit->GetEntityId());
						break;
					case ERageSkillExecuteStatus::Show:
					case ERageSkillExecuteStatus::Begin: 
						if (unit->IsInRageSkillMaskTime() == false)
						{
							UnpauseUnit(unit, true); //如果队友不在活跃状态，需要标记它进入活跃状态  
						} 
						break;
					case ERageSkillExecuteStatus::End:
						PauseUnit(unit);
						break;
					}
				}
			}
		}
	}
	else
	{ //deal with rivals
		for (auto& unit : aArmy->GetActiveUnitArr())
		{
			PauseUnit(unit);
		}	
	}
}

// will block mArmy2's petition under PVE mode
// otherwise, set mRageSkillUntilizerArmy and MaskCountdown, Pause both army, Exec ViewCmd::Mask_Enable
// set OnTick method of Normal State to ActionTickRageSkillExecute
void BattleInstance::WhenSomeoneStartRageSkill(RageSkillExecuteState* aState)
{
	Unit* utilizer = aState->mUtilizer;
    if (mRageSkillMaskArmy)
    {
		if ( mRageSkillMaskArmy == &(utilizer->GetArmy()))
		{ //unpause other rage skill utilizers in that one of their team member is executing rage skill right now
			UnpauseUnit(utilizer, true);
		}
		else
		{
			// there exists a rival Unit TryShowRageSkill prior to this one, adjust State to WaitForOtherArmy
			aState->mStatus = ERageSkillExecuteStatus::WaitForOtherArmy;
		} 
        return;
    }
    //if ( !mIsNoBlackScreen && !mIsTD && ( !mIsPVE || (mIsPVE && (&(utilizer->GetArmy()) == mArmy1.Get()))) )
	if (false) //archer 玩法没有黑屏 
    {
        mRageSkillMaskArmy = &utilizer->GetArmy();
	    PauseUnitWhenSomeoneStartRageSkill(mArmy1, utilizer);
	    PauseUnitWhenSomeoneStartRageSkill(mArmy2, utilizer);
		UnpauseUnit(utilizer, true);
        mView->Execute(ViewCommand::FullscreenBlackMask, ViewCommand::FULLSCREEN_BLACK_MASK_ENABLE, mRageSkillMaskArmy->GetId());
        
        mStateNormal->SetOnTick(MakeFunction<>(*this, &BattleInstance::ActionTickRageSkillExecute));
    }
}

bool BattleInstance::IsDyingValid(int aArmyId)
{
	if (aArmyId == 1)
	{
		return mArmy2DyingEnd <= mFrameTime;
	}
	else
	{
		return mArmy1DyingEnd <= mFrameTime;
	}
}

void BattleInstance::CleanDyingTime(int aEndTime, int aArmyId)
{
	if (aArmyId == 1)
	{
		if (mArmy1DyingEnd > aEndTime) 
			return;  //ignore this case
		//otherwise, check team member's dyingend 
		mArmy1DyingEnd = mFrameTime;
		for (auto& unit : mArmy1->GetActiveUnitArr())
		{
			int dyingend = unit->TryGetDyingEnd();
			if (mArmy1DyingEnd < dyingend)
				mArmy1DyingEnd = dyingend;
		}
	}
	else
	{
		if (mArmy2DyingEnd > aEndTime)
			return; 
		mArmy2DyingEnd = mFrameTime;
		for (auto& unit : mArmy2->GetActiveUnitArr())
		{
			int dyingend = unit->TryGetDyingEnd();
			if (mArmy2DyingEnd < dyingend)
				mArmy2DyingEnd = dyingend;
		}
	}
}

int BattleInstance::RegisterDyingTime(int aDuration, int aArmyId)
{
	int endTime = mFrameTime + aDuration;
	if (aArmyId == 1)
	{
		mArmy1DyingEnd = mArmy1DyingEnd >= endTime ? mArmy1DyingEnd : endTime;
	}
	else
	{
		mArmy2DyingEnd = mArmy2DyingEnd >= endTime ? mArmy2DyingEnd : endTime;
	}
	return endTime;
}

//send pause cmd iff no records in mRageSkillPauseUnitArr before
void BattleInstance::PauseUnit(Unit* aUnit)
{
	if (aUnit && aUnit->IsDead())
		return;
	std::pair<unordered_set<Unit*>::iterator,bool> ret = mRageSkillPauseUnitArr.emplace(aUnit);
	if (ret.second)
	{
		mView->Execute(ViewCommand::PauseEntity, aUnit->GetEntityId());
	}	
}

// put Unpaused Unit back into mRageSkillActiveUtilizerArr
// View Exec UnpauseEntity
void BattleInstance::UnpauseUnit(Unit* aUnit, bool aSetActive)
{
	if (aUnit && aUnit->IsDead())
		return;
	if (aSetActive)
	{		
		uniqEmplaceBackToVector(mRageSkillActiveUtilizerArr, aUnit);
	}	
	if (mRageSkillPauseUnitArr.erase(aUnit) > 0)
	{
		mView->Execute(ViewCommand::UnpauseEntity, aUnit->GetEntityId());
	}	
}

void BattleInstance::UnpauseDummyUnit(Unit* aUnit)
{
	uniqEmplaceBackToVector(mRageSkillActiveUtilizerArr, aUnit);	
}

// clean up mRageSkillXXX, let mView->Execute( Mask_Disable )
// for all Unit in Battle, do mView->Exec( Unpause )
// setback OnTick method: ActionTickNormal to Normal State
void BattleInstance::RageSkillMaskEnd()
{
    int id = mRageSkillMaskArmy->GetId();
    mRageSkillActiveUtilizerArr.clear();
    mRageSkillMaskArmy = nullptr;
    mRageSkillCarrierArr.clear();
    mView->Execute(ViewCommand::FullscreenBlackMask, ViewCommand::FULLSCREEN_BLACK_MASK_DISABLE, id);

	//看看有没有对方的人在等待进入大招 
	for (auto& rageExecute : mRageSkillExecuteStateArr)
	{
		if (rageExecute->mStatus == ERageSkillExecuteStatus::WaitForOtherArmy)
		{
			rageExecute->mStatus = ERageSkillExecuteStatus::Begin;
			WhenSomeoneStartRageSkill(rageExecute);
		}
	}
	if (mRageSkillMaskArmy == nullptr) 
	{
		for (auto* unit : mArmy1->GetActiveUnitArr())
		{			
			UnpauseUnit(unit, false);
		}
		for (auto* unit : mArmy2->GetActiveUnitArr())
		{
			UnpauseUnit(unit, false);			
		}
		mStateNormal->SetOnTick(MakeFunction<>(*this, &BattleInstance::ActionTickNormal));
		TryResetDying();
		if (!mRageSkillPauseUnitArr.empty())
		{
			mRageSkillPauseUnitArr.clear();
		}
	}    
}
bool BattleInstance::TickEnterField(double aDeltaTimeS)
{
	if (mFsm->IsInState(mFsm->GetStartState().GetId()) || mFsm->IsInState(mStateEnterField->GetId()) )//|| mFsm->IsInState(mStateCutscene->GetId))
	{
		OnTick();
		return true;
	}
	return false;
}
void BattleInstance::OnVTick(double aDeltaTimeS)
{
    mVFrameTimeRemain += static_cast<int>(aDeltaTimeS * FRAME_TIME_SCALE+0.5); 
    while (mVFrameTimeRemain >= mFixedFrameDelta)
    {
		auto beforeFieldIndex = mSceneMgr->CurSceneId;
        OnTick();
		if (mSceneMgr->CurSceneId > beforeFieldIndex)
			return;
        mVFrameTimeRemain -= mFixedFrameDelta;
    }
}

//固定帧率的Tick入口 
void BattleInstance::OnTick()
{
    //LOG_DEBUG("FrameTime:%d", mFrameTime);
    mFsm->OnTick(mFixedFrameDelta);
	OnTickBossGrowth();
}

void BattleInstance::RunBattleToEnd()
{
	while (GetResultType() == EBattleResult::None)
	{
		OnTick();
	}
}


void BattleInstance::DispatchEvent(int aKey, int aArmyId, int aEntityId, int64 aReg0, int64 aReg1, int64 aReg2)
{
	BattleEvent evt;
	evt.SetEventId(aKey);
	evt.mArmyId = aArmyId;
	evt.mEntityId = aEntityId;
	evt.mRegister0 = aReg0;
	evt.mRegister1 = aReg1;
	evt.mRegister2 = aReg2;
	DoDispatchEvent(evt);	
	RestoreObjToPool(evt);
}

void BattleInstance::DoDispatchEvent(const BattleEvent& aEvent)
{
	mBattleEventDispatcher->Dispatch(aEvent);
}

void BattleInstance::AddListener(int aKey, const IFunctionContainer<void, const BattleEvent&>* aFunc)
{
	mBattleEventDispatcher->AddListener(aKey, aFunc);
}

void BattleInstance::RemoveListener(int aKey, const IFunctionContainer<void, const BattleEvent&>* aFunc)
{
	mBattleEventDispatcher->RemoveListener(aKey, aFunc);
}

void BattleInstance::SetAuto(bool aAuto)
{
	EBattleInput input = aAuto ? EBattleInput::EnableAuto : EBattleInput::DisableAuto;
	RecordUserInput(0, input);
	mAuto = aAuto;	
}

int BattleInstance::Rand(int aN) const
{
    if (aN == 0)
    {
		//LOG_DEBUG("Try generate random number within a range of 0");
        return 0;
    }
    return uint32(mRand->genrand_int32()) % aN;
}

void BattleInstance::TryResetDying()
{
	DieCause dieCause(EUnitDieCause::Invalid);

	auto& active1 = mArmy1->GetActiveUnitArr();
	vector<Unit*> tmp(0);
	for (auto unit : active1)
	{
		tmp.emplace_back(unit);
	}

	for (auto& unit : tmp)
	{
		if (unit->IsEmptyHp() && !unit->IsDead())
		{
			unit->Die(dieCause);
		}
	}

	auto& active2 = mArmy2->GetActiveUnitArr();
	tmp.clear();
	for (auto unit : active2)
	{
		tmp.emplace_back(unit);
	}

	for (auto& unit : tmp)
	{
		if (unit->IsEmptyHp() && !unit->IsDead())
		{
			unit->Die(dieCause);
		}
	}
}

const Army& BattleInstance::TargetArmy(Unit& aUnit) const
{
    if (aUnit.CheckStateAdjust(StateAdjust::Chaos))
    {
        return Rand(100) >= 50 ? *mArmy1 : *mArmy2;
    }
    if ((&aUnit.GetArmy() == mArmy1.Get()) != aUnit.CheckStateAdjust(StateAdjust::Charmed))
        return *mArmy2;
    else
        return *mArmy1;
}

const Army& BattleInstance::GetArmy1() const
{
    return *mArmy1;
}

const Army& BattleInstance::GetArmy2() const
{
    return *mArmy2;
}

const Army& BattleInstance::GetEnemyArmy(int aArmyId) const
{
	if (aArmyId == mArmy1->GetId())
		return *mArmy2;
	else
		return *mArmy1;
}

//注意，该方法返回值必须使用 Army& 或 auto& 类型承载，不然会导致Army被提前析构 
Army& BattleInstance::GetArmy(int aArmyId)
{
	if (aArmyId == mArmy1->GetId())
		return *mArmy1;
	else
		return *mArmy2;
}

PathFindingMgr* BattleInstance::GetPathMgr()
{
	if (mAIPath)
		return mSceneMgr->mPathMgr;
	return nullptr;
}

bool BattleInstance::RestrainToBattleArea(const Vector3& aStart, const Vector3& aEnd, int aRadius, Vector3* aResult)
{
	//TODO: should replace by RestrainWithBlockLines 
	if (mStripD > 0 && !mFieldBlockLineArr.empty())
		return false;
    return mPhysics->SegmentPolygon(aStart, aEnd, mFieldAreaPointArr, aRadius, aResult); 
}

bool BattleInstance::RestrainWithBlockLines(const Vector3& aStart, const Vector3& aEnd, int aRadius, Vector3* aResult)
{
	vector<int> affectedLines;
	FilterBlockLine(aStart, aEnd, affectedLines);
	for (auto idx : affectedLines)
	{
		if (mPhysics->SegmentPolygon(aStart, aEnd, mFieldBlockLineArr[idx], aRadius, aResult)) return true;
	}
	return false;
}


int BattleInstance::BehaviourSelectUnitByHp(int aArmyId, int aCheckMost)
{    
    auto& unitArr = aArmyId == 1 ? mArmy1->GetUnitArr() : mArmy2->GetUnitArr();
    int check = -1;
    int value = 0;
    Unit* unit;
    for (int i = 0; i < unitArr.size(); ++i)
    {
        value = unitArr[i]->GetHp();
		if (unitArr[i]->IsHidden() || unitArr[i]->IsDead())
		{
			//do nothing
		}
        else if (((aCheckMost == 1) == (value > check)) || check == -1)
        {
            check = value;
            unit = unitArr[i].Get();
        }
    }
	if (unit == nullptr)
	{
		return 0;
	}
	return unit->GetEntityId();
}

int BattleInstance::BehaviourSelectUnitByLostHp(int aArmyId, int aCheckMost)
{    
    auto& unitArr = aArmyId == 1 ? mArmy1->GetUnitArr() : mArmy2->GetUnitArr();
    int check = -1;
    int value = 0;
    Unit* unit;
    for (int i = 0; i < unitArr.size(); ++i)
    {
        value = unitArr[i]->GetLostHp();
		if (unitArr[i]->IsHidden() || unitArr[i]->IsDead())
		{
			//do nothing
		}
        else if (((aCheckMost == 1) == (value > check)) || check == -1)
        {
            check = value;
            unit = unitArr[i].Get();
        }
    }
	if (unit == nullptr)
	{
		return 0;
	}
	return unit->GetEntityId();
}

int BattleInstance::BehaviourSelectUnitByRage(int aArmyId, int aCheckMost)
{
    auto& unitArr = aArmyId == 1 ? mArmy1->GetUnitArr() : mArmy2->GetUnitArr();
    int check = -1;
    int value = 0;
    Unit* unit;
    for (int i = 0; i < unitArr.size(); ++i)
    {
        value = unitArr[i]->GetRage();
		if (unitArr[i]->IsHidden() || unitArr[i]->IsDead())
		{
			//do nothing
		}
        else if (((aCheckMost == 1) == (value > check)) || check == -1)
        {
            check = value;
            unit = unitArr[i].Get();
        }
    }
	if (unit == nullptr)
	{
		return 0;
	}
	return unit->GetEntityId();
}

int BattleInstance::BehaviourSelectUnitById(int aArmyId, int aTplId)
{   
    auto& army = aArmyId == 1 ? mArmy1 : mArmy2;
    for (auto& unit : army->GetUnitArr())
    {
        if (!unit->IsDead() && unit->GetTplId() == aTplId) 
        {
			return unit->GetEntityId(); 
        }
    }
	for (auto& unit : army->GetUnitArr())
	{
		if (unit->GetTplId() == aTplId)
		{
			return unit->GetEntityId();
		}
	}
	return 0;
}

SharedPtr<Unit> BattleInstance::GetOneRandomUnit(int aMyArmy, int aWhichArmy, int aExcludeId)
{
	int armyId = Rand(2) + 1;
	if (aWhichArmy == 0) armyId = aMyArmy;
	else if (aWhichArmy == 1) armyId = aMyArmy % 2 + 1;

	if (armyId == 1)
	{
		auto eid = mArmy1->GetRandActiveUnit(aExcludeId);
		return mArmy1->GetUnitById(eid);
	}
	else
	{
		auto eid = mArmy2->GetRandActiveUnit(aExcludeId);
		return mArmy2->GetUnitById(eid);
	}
	return nullptr;
}

SharedPtr<Unit> BattleInstance::GetUnitByTplId(int aTplId) const
{
	auto& list = mArmy1->GetUnitArr();
	for (int idx = 0; idx < list.size(); idx++)
	{
		if (list[idx]->GetTplId() == aTplId && !list[idx]->IsHidden() && !list[idx]->IsDead())
		{
			//return mArmy1->GetUnitArr().at(idx);
			return list[idx];
		}
	}
	auto& list2 = mArmy2->GetUnitArr();
	for (int idx = 0; idx < list2.size(); idx++)
	{
		if (list2[idx]->GetTplId() == aTplId && !list2[idx]->IsHidden() && !list2[idx]->IsDead())
		{
			//return mArmy2->GetUnitArr().at(idx);
			return list2[idx];
		}
	}
	return nullptr;
}

SharedPtr<Unit> BattleInstance::GetUnitByEntityId(int aEntityId, bool aIncludeDead) const
{
	auto& list = mArmy1->GetUnitArr();
	for (int idx = 0; idx < list.size(); idx++)
	{
		if (list[idx]->GetEntityId() == aEntityId && !list[idx]->IsHidden() && (aIncludeDead || !list[idx]->IsDead()))
		{
			return list[idx];
		}
	}
	auto& list2 = mArmy2->GetUnitArr();
	for (int idx = 0; idx < list2.size(); idx++)
	{
		if (list2[idx]->GetEntityId() == aEntityId && !list2[idx]->IsHidden() && (aIncludeDead || !list2[idx]->IsDead()))
		{
			return list2[idx];
		}
	}
	return nullptr;
}

void BattleInstance::GetAllActiveUnits(vector<Unit*>& aAllUnits)
{
	auto& list1 = mArmy1->GetActiveUnitArr();
	auto& list2 = mArmy2->GetActiveUnitArr();
	aAllUnits.reserve(list1.size() + list2.size());

	for (int idx = 0; idx < list1.size(); idx++)
	{
		aAllUnits.emplace_back(list1[idx]);
	}
	for (int idx = 0; idx < list2.size(); idx++)
	{
		aAllUnits.emplace_back(list2[idx]);
	}
}

void BattleInstance::BehaviourSelectUnitByAllId(int aArmyId, int aTplId, vector<int>& aEntityIdArr)
{
	auto& army = aArmyId == 1 ? mArmy1 : mArmy2;
	for (auto& unit : army->GetUnitArr())
	{
		if (unit->GetTplId() == aTplId)
		{
			aEntityIdArr.push_back(unit->GetEntityId());
		}
	}
}

void BattleInstance::BehaviourSelectAllUnit(int aArmyId, vector<int>& aEntityIdArr)
{
    auto& army = aArmyId == 1 ? mArmy1 : mArmy2;
    for (auto& unit : army->GetUnitArr())
    {
		if (!unit->IsHidden() && !unit->IsDead() && !(unit->IsDummy() && unit->IsSummoned()))
		{
			aEntityIdArr.push_back(unit->GetEntityId());
		}
    }
}


void BattleInstance::BehaviourSelectAllUnitContantHide(int aArmyId, vector<int>& aEntityIdArr)
{
	auto& army = aArmyId == 1 ? mArmy1 : mArmy2;
	for (auto& unit : army->GetUnitArr())
	{
		if (!(unit->IsDummy() && unit->IsSummoned()))
		{
			aEntityIdArr.push_back(unit->GetEntityId());
		}
	}
}

void BattleInstance::BehaviourSelectUnitBySpawnPointName(int aArmyId, const char* aSpawnPointName, vector<int>& aEntityIdArr)
{   
    auto& army = aArmyId == 1 ? mArmy1 : mArmy2;
    auto& bornPointArr = army->GetBornPointArr();
    for (auto& unit : army->GetUnitArr())
    {
        if (bornPointArr[unit->GetBornPoint()].mName.compare(aSpawnPointName) == 0 && !unit->IsHidden() && !unit->IsDead())
        {
			aEntityIdArr.push_back(unit->GetEntityId());
            return;
        }
    }
}

void BattleInstance::BehaviourGotoResult(int aIsVictory)
{
    mBattleResult = aIsVictory == 1 ? EBattleResult::Victory : EBattleResult::Lose;
    mFsm->DoTransition(mTransBattleEnd);
}

void BattleInstance::BehaviourGotoNextField()
{
	if (mFsm->IsInState(mStateCutscene->GetId()))
		return;
	CleanUpAllSkillCarrier();
	mArmy2->ClearActiveUnitArr(); 
	mTimeExtra = 0;
	CondiCurrentFieldEnd(true);  
}

int BattleInstance::BehaviourAddUnit(int aArmyId, int aTplId, int aLevel, int aPosX, int aPosY, int aPosZ, int aDirX, int aDirY, int aDirZ, int aShow, int aIsBoss)
{
    auto& army = aArmyId == 1 ? mArmy1 : mArmy2;
    auto& unitArr = army->GetUnitArr();
    vector<int> points = vector<int>(army->GetBornPointArr().size(), 0);
    for (auto& unit : unitArr)
    {
		if (unit->GetBornPoint() >= 0)
		{
			points[unit->GetBornPoint()] = unit->GetEntityId();
		}
        
    }
    int empty = -1;
    for (int i = 0; i < points.size(); ++i)
    {
        if (points[i] == 0)
        {
			if (aArmyId == 1)
			{
				if (i >= MAX_USER_BORNPOINT)
				{
					empty = i;
					break;
				}
			}
			else
			{
				empty = i;
				break;
			}
        }
    }
    if (empty == -1)
    {
        LOG_FATAL("no empty born point to add unit {armyId=%d,tplId=%d}", aArmyId, aTplId);
    }
    auto unit = army->AddUnit(aTplId, aLevel, 0, empty, aShow, aIsBoss);//TODO show on UI?
    //unit->SetPosRot(Vector3(aPosX, aPosY, aPosZ), Vector3(aDirX, aDirY, aDirZ), true);
	unit->SetBehaviourMark(true);
	unit->InitLocation(Vector3(aPosX, aPosY, aPosZ), Vector3(aDirX, aDirY, aDirZ));	
	unit->TryUpdateMapLocation();
	unit->DontSetToBornPosWhenCutscene();
	int entityId = int(unit->GetEntityId());
	return entityId;
}

int BattleInstance::BehaviourHideUnit(int aEntityId, int aHiding)
{
    for (auto& unit : mArmy1->GetUnitArr())
    {
        if (unit->GetEntityId() == aEntityId)
        {
            unit->BehaviourHide(aHiding);
            return 0;
        }
    }
    for (auto& unit : mArmy2->GetUnitArr())
    {
        if (unit->GetEntityId() == aEntityId)
        {
            unit->BehaviourHide(aHiding);
            return 0;
        }
    }
	LOG_DEBUG("not found entity:%d", aEntityId);
    return -1;
}

int BattleInstance::BehaviourDeleteUnit(int aEntityId)
{
	if (mArmy1)
		mArmy1->RemoveFromUnitArr(aEntityId);
	if (mArmy2)
		mArmy2->RemoveFromUnitArr(aEntityId);
	return 0;
}

int BattleInstance::BehaviourStopUnit(int aEntityId, int aStopped)
{
    for (auto& unit : mArmy1->GetUnitArr())
    {
        if (unit->GetEntityId() == aEntityId)
        {
            unit->BehaviourStop(aStopped);
			mArmy1->OnBehaviourPause(aStopped != 0);
            return 0;
        }
    }
    for (auto& unit : mArmy2->GetUnitArr())
    {
        if (unit->GetEntityId() == aEntityId)
        {
            unit->BehaviourStop(aStopped);
			mArmy2->OnBehaviourPause(aStopped != 0);
            return 0;
        }
    }
	LOG_DEBUG("not found entity:%d", aEntityId);
    return -1;
}
int BattleInstance::BehaviourUnitAnim(int aEntityId, const char* aAnim)
{
	for (auto& unit : mArmy1->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			return unit->BehaviourAnim(aAnim) ? 1 : 0;
		}
	}
	for (auto& unit : mArmy2->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			return unit->BehaviourAnim(aAnim) ? 1 : 0;			
		}
	}
	LOG_DEBUG("not found entity:%d", aEntityId);
	return -1;
}
int BattleInstance::BehaviourAddBuff(int aEntityId, int aBuffId, int aBuffLv, int aDelete, int aDeletaByBT)
{
	for (auto& unit : mArmy1->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			if (aDelete > 0)
			{
				unit->BehaviourRemoveBuff(aBuffId, aBuffLv);
			}
			else
			{
				unit->BehaviourAddBuff(aBuffId, aBuffLv, aDeletaByBT);
			}
			return 0;
		}
	}
	for (auto& unit : mArmy2->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			if (aDelete > 0)
			{
				unit->BehaviourRemoveBuff(aBuffId, aBuffLv);
			}
			else
			{
				unit->BehaviourAddBuff(aBuffId, aBuffLv, aDeletaByBT);
			}
			return 0;
		}
	}
	LOG_DEBUG("not found entity:%d", aEntityId);
	return -1;
}

int BattleInstance::BehaviourObstacleVisible(const char* aObstacleName, int aIsVisible)
{
    //TODO
	return 0;
}

//set remaining time before normal timeout
int BattleInstance::BehaviourSetTime(int aTime)
{
	if (aTime < 0 || aTime > BATTLE_TIME_UPPER_LIMIT)
	{
		LOG_WARN("BehaviourSetTime found invalid time:%d", aTime);
		return 0;
	}
	mTimeLimit = mFrameTime + aTime;
	mGameTime = mFrameTime;
	mView->Execute(ViewCommand::ResetTimeLimit, mTimeLimit, mGameTime);
	return 0;
}

int BattleInstance::BehaviourSetExtraTime(int aTime)
{
	if (aTime < 0 || aTime > BATTLE_TIME_UPPER_LIMIT)
	{
		LOG_WARN("BehaviourSetExtraTime found invalid time:%d", aTime);
		return 0;
	}
	mTimeExtra = aTime;
	return 0;
}

int BattleInstance::BehaviourExecuteSkill(int aEntityId, int aSkillId, int aDelay)
{
	for (auto& unit : mArmy1->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->BehaviourExecuteSkill(aSkillId, aDelay);
			return 0;
		}
	}
	for (auto& unit : mArmy2->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->BehaviourExecuteSkill(aSkillId, aDelay);
			return 0;
		}
	}
	LOG_DEBUG("not found entity:%d", aEntityId);
	return -1;
}

int BattleInstance::BehaviourSyncLocation(int aEntityId, int aPosX, int aPosY, int aPosZ)
{
	Vector3 pos;
	pos.x += CONF_POS_CONVERT(aPosX);
	pos.y += CONF_POS_CONVERT(aPosY);
	pos.z += CONF_POS_CONVERT(aPosZ);

	for (auto& unit : mArmy1->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->SetPosition(pos, false);
			return 0;
		}
	}
	for (auto& unit : mArmy2->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->SetPosition(pos, false);
			return 0;
		}
	}
	LOG_DEBUG("not found entity:%d", aEntityId);
	return -1;
}

int BattleInstance::BehaviourSyncDirection(int aEntityId, int aDirX, int aDirY, int aDirZ)
{
	Vector3 rot;
	rot.x = aDirX * 1000;
	rot.y = aDirY * 1000;
	rot.z = aDirZ * 1000;

	for (auto& unit : mArmy1->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->SetRotation(rot);
			return 0;
		}
	}
	for (auto& unit : mArmy2->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->SetRotation(rot);
			return 0;
		}
	}
	LOG_DEBUG("not found entity:%d", aEntityId);
	return -1;
}

int BattleInstance::BehaviourMoveToStandPoint(int aEntityId, const char* aStandPointName, int aSpeed, int aTargetId, int aRange, int aOffsetX, int aOffsetY, int aOffsetZ)
{
	Vector3 pos;
	bool find = false;
	if (aTargetId > 0)
	{
		auto unit = GetUnitByTplId(aTargetId);
		if (unit)
		{
			find = true;
			pos = Vector3(unit->GetPosition().x, unit->GetPosition().y, unit->GetPosition().z);
		}
	}
	else 
	{
		for (auto& point : mStandPointArr)
		{
			if (point.mName.compare(aStandPointName) == 0)
			{
				find = true;
				pos = Vector3(point.mPos.x, point.mPos.y, point.mPos.z);
				break;
			}
		}
		if (!find)
		{
			for (auto& point : mBornPointArr1)
			{
				if (point.mName.compare(aStandPointName) == 0)
				{
					find = true;
					pos = Vector3(point.mPos.x, point.mPos.y, point.mPos.z);
					break;
				}
			}
		}
		if (!find)
		{
			for (auto& point : mBornPointArr2)
			{
				if (point.mName.compare(aStandPointName) == 0)
				{
					find = true;
					pos = Vector3(point.mPos.x, point.mPos.y, point.mPos.z);
					break;
				}
			}
		}
	}
	if (!find)
	{
		LOG_DEBUG("not found standpoint %s and target TplId %d", aStandPointName, aTargetId);
		return -1;
	}
	
	pos.x += CONF_POS_CONVERT(aOffsetX);
	pos.y += CONF_POS_CONVERT(aOffsetY);
	pos.z += CONF_POS_CONVERT(aOffsetZ);

	for (auto& unit : mArmy1->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->BehaviourMoveToStandPoint(pos, aSpeed, aRange);
			return 0;
		}
	}
	for (auto& unit : mArmy2->GetUnitArr())
	{
		if (unit->GetEntityId() == aEntityId)
		{
			unit->BehaviourMoveToStandPoint(pos, aSpeed, aRange);
			return 0;
		}
	}
	LOG_DEBUG("not found entity:%d", aEntityId);
	return -1;
}

void BattleInstance::CleanUpAllSkillCarrier()
{
	for (auto& carrier : mSkillCarrierArr)
	{
		carrier->Cancel();
	}
	mSkillCarrierArr.clear();
}

SharedPtr<SkillCarrier> BattleInstance::AddSkillCarrier()
{
    auto ret = SharedPool<SkillCarrier>::Get();    
    mSkillCarrierArr.push_back(ret);
    if (mRageSkillMaskArmy)
    {
        mRageSkillCarrierArr.push_back(ret);
    }    
    return ret;
}

int BattleInstance::GetFrameTime() const
{
    return mFrameTime;
}

int BattleInstance::GetGameTime() const
{
	return mGameTime;
}

int BattleInstance::GetCurField() const
{
	return mSceneMgr->CurSceneId;
}

bool BattleInstance::NeedDoStatistics() const
{
	//return true;
	return mNeedDoStatistics;
}

bool BattleInstance::UseAIPath() const
{
	return mAIPath;
}

TimerMgr* BattleInstance::GetTimerMgr() const
{
    return mTimerMgr.Get();
}

bool BattleInstance::IsPVE() const
{
	return mIsPVE;
}

bool BattleInstance::IsSLG() const
{
	return mIsSLG;
}

bool BattleInstance::IsAuto() const
{
    return mAuto;
}

void BattleInstance::AddSkillCount(int aSkillId, int aArmyId)
{
    SkillCount& skillCount = GetSkillCount(aSkillId);
	if (aArmyId == 1)
	{
		skillCount.mScreenTotal += 1;
		skillCount.mTotal += 1;
	}
	else
	{
		skillCount.mScreenTotal2 += 1;
		skillCount.mTotal2 += 1;
	}
}

void BattleInstance::SubSkillCount(int aSkillId, int aArmyId)
{
	SkillCount& skillCount = GetSkillCount(aSkillId);
	if (aArmyId == 1)
	{
		skillCount.mScreenTotal -= 1;
		skillCount.mTotal -= 1;
	}
	else
	{
		skillCount.mScreenTotal2 -= 1;
		skillCount.mTotal2 -= 1;
	}
}

void BattleInstance::SetSkillCount(int aSkillId, int aCt)
{
	auto tmp = mSkillExecCountMap.count(aSkillId);
	mSkillExecCountMap[aSkillId].mScreenTotal = aCt;
	mSkillExecCountMap[aSkillId].mTotal = 0;
	mSkillExecCountMap[aSkillId].mScreenTotal2 = 0;
	mSkillExecCountMap[aSkillId].mTotal2 = 0;
}

SkillCount& BattleInstance::GetSkillCount(int aSkillId)
{
    if ( mSkillExecCountMap.count(aSkillId) == 0 )
    {
        mSkillExecCountMap[aSkillId].mScreenTotal = 0;
        mSkillExecCountMap[aSkillId].mTotal = 0;
		mSkillExecCountMap[aSkillId].mScreenTotal2 = 0;
		mSkillExecCountMap[aSkillId].mTotal2 = 0;
    }
    return mSkillExecCountMap[aSkillId];
}

//周期调用 
void BattleInstance::UpdatePlayerPositionAndRotation()
{
	auto player = GetUnitByEntityId(1);
	if (!player || player->IsDead())
		return;
	const auto& lastPos = player->GetPosition();
	if (mPlayerPosition == lastPos)
	{
		player->mPlayerStallCounter++;
	}
	else
	{
		player->mPlayerStallCounter = 0;
	}

	player->SetPosRot(mPlayerPosition, mPlayerRotation, false);
}

// will follow the order of input cmd directly
int BattleInstance::ExecuteRageSkill(int aEntityId)
{
	if (mFrameTime < 200 || mFsm->IsInState(mStateCutscene->GetId()) || mFsm->IsInState(mStateEnterField->GetId()))
	{
		return 0;
	}
    for (auto& unit : mArmy1->GetUnitArr())
    {
        if (unit->GetEntityId() == aEntityId)
        {
			if (unit->ManuallyExecuteRageSkill() > 0)
			{
				RecordUserInput(aEntityId, EBattleInput::ExecuteSkill);
				return 1;
			}
			else
				return 0;

        }
    }
    for (auto& unit : mArmy2->GetUnitArr())
    {
        if (unit->GetEntityId() == aEntityId)
        {
			if(unit->ManuallyExecuteRageSkill() > 0)
			{
				RecordUserInput(aEntityId, EBattleInput::ExecuteSkill);
				return 1;
			}
			else
				return 0;
        }
    }
	
    return 0;
}

vector<TBattleViewCmd*>& BattleInstance::FetchViewCmd()
{
    return mView->FetchViewCmd();
}

EBattleResult BattleInstance::GetResultType() const
{
    return mBattleResult;
}

SharedPtr<BattleViewOutput> BattleInstance::GetView() const
{
	return mView;
}
SharedPtr<PhysicsSystem> BattleInstance::GetPhysics() const
{
	return mPhysics;
}

int BattleInstance::GetBossGrowthLevel(int aArmyId)
{
	if (!mIsBossGrowth || aArmyId != 2)
	{
		LOG_WARN("Mis-using of GetBossGrowthLevel, isBossGrowth %b, is Army2 %b", mIsBossGrowth, aArmyId == 2);
		return 0;
	}
	return mBossGrowthLevel;
}

void BattleInstance::OnTickBossGrowth()
{
	if (!mIsBossGrowth) return;
	if (mFsm->IsInState(mStateNormal->GetId()))
	{
		int64 origDmg = mBossTotalDamageUndertake;
		mBossTotalDamageUndertake = 0;
		for (auto& unit : mArmy2->GetUnitArr())
		{
			mBossTotalDamageUndertake += unit->GetDamageInWithOverflow();
		}
		if (origDmg >= mBossTotalDamageUndertake)
			return;
		int aLv = -1;
		int bLv = -1;
		for (int idx = 0; idx < BossHpRange.size(); idx++)
		{
			if (BossHpRange[idx] > origDmg && aLv < 0)
			{
				aLv = idx;
			}
			if (BossHpRange[idx] > mBossTotalDamageUndertake && bLv < 0)
			{
				bLv = idx;
				break;
			}
		}
		int deltaLv = bLv - aLv;
		if (deltaLv > 0)
		{
			mBossGrowthLevel = bLv;
			int deltaGrowth = 0;
			for (int idx = aLv; idx < bLv; idx++)
			{
				deltaGrowth += BossHpRangeGrowth[idx];
			}
			for (auto& unit : mArmy2->GetActiveUnitArr())
			{
				if (!unit->IsSummoned() && !unit->IsDead())
				{
					for (int i = 0; i < BossAttributeAdd.size(); i += 2)
					{
						unit->DirectAddAttr(static_cast<EAttribute>(BossAttributeAdd[i]), BossAttributeAdd[i + 1] * deltaGrowth);
					}
				}
			}
		}

	}
}

void BattleInstance::LoadBossGrowthAttr()
{
	//TODO: use conf or so
	auto starter = mArgs->battlestarter();
	mIsBossGrowth = false;
	switch (starter)
	{
	case pb::EBattleStarter::EBattleMajorWorldBoss:
	case pb::EBattleStarter::EBattleMajorCrossWorldBoss:
		mIsBossGrowth = true;
		break;
	default:
		break;
	}

	if (mIsBossGrowth && mArgs->army2arr_size() > 0)
	{
		for (auto& unit : mArgs->army2arr(0).unitarr())
		{
			int tplid = unit.htid();
			auto* conf = ConfigMgr::GetConfById<ConfigHero>(tplid);
			auto& growth = conf->GetBossAttrGrowth();
			if (growth.size() > 0)
			{
				for (auto& sub : growth)
				{
					BossAttributeAdd.emplace_back(sub[0]);
					BossAttributeAdd.emplace_back(sub[1]);
				}
				break;
			}
		}
	}
}

void BattleInstance::TriggerDamageCopy(int64 aDamage, int aSourceUtilizerId, int buffId)
{

}

vector<DirectedPosition>& BattleInstance::GetArmy1BornPointArr()
{
	return mBornPointArr1;
}

//Filter out block_lines that lay outside the rectangle area depicted by given starting and ending points 
void BattleInstance::FilterBlockLine(const Vector3& aStart, const Vector3& aEnd, vector<int>& aBlockLineArr)
{
	if (mStripD <= 0)
	{
		for (int i = 0; i < mFieldBlockLineArr.size(); i++)
		{
			aBlockLineArr.emplace_back(i);
		}
		return;
	}
	int64 minX = 0, minZ = 0, maxX = 0, maxZ = 0;
	int64 halfStripD = mStripD >> 1;
	int colIdxMin = 0, colIdxMax = 0, rowIdxMin = 0, rowIdxMax = 0;
	if (aStart.x > aEnd.x)
	{
		maxX = aStart.x;
		minX = aEnd.x;
	}
	else
	{
		minX = aStart.x;
		maxX = aEnd.x;
	}
	if (aStart.z > aEnd.z)
	{
		maxZ = aStart.z;
		minZ = aEnd.z;
	}
	else
	{
		minZ = aStart.z;
		maxZ = aEnd.z;
	}

	if (minX < 0)
		minX = minX - halfStripD;
	else
		minX = minX + halfStripD;

	if (maxX < 0)
		maxX = maxX - halfStripD;
	else
		maxX = maxX + halfStripD;

	if (minZ < 0)
		minZ = minZ - halfStripD;
	else
		minZ = minZ + halfStripD;

	if (maxZ < 0)
		maxZ = maxZ - halfStripD;
	else
		maxZ = maxZ + halfStripD;

	colIdxMin = mHalfCol + minX / mStripD;
	colIdxMax = mHalfCol + maxX / mStripD;

	rowIdxMin = mHalfRow + minZ / mStripD;
	rowIdxMax = mHalfRow + maxZ / mStripD;

	if (colIdxMin < 0) colIdxMin = 0;
	if (colIdxMax < 0) colIdxMax = 0;

	if (rowIdxMin < 0) rowIdxMin = 0;
	if (rowIdxMax < 0) rowIdxMax = 0;

	vector<int> tmp;
	size_t s = mFieldBlockLineArr.size();
	tmp.resize(s);
	fill(tmp.begin(), tmp.end(), 0);
	for (int i = colIdxMin; i <= colIdxMax && i < mColStrips.size(); i++)
	{
		for (auto j : mColStrips[i])
		{
			if (j >= 0 && j < s)
			{
				tmp[j] = 1;
			}
			else
			{
				LOG_WARN("invalid col strips info, idx %d, has line idx %d, total line size %d", i, j, s);
			}
		}
	}
	for (int i = rowIdxMin; i <= rowIdxMax && i < mRowStrips.size(); i++)
	{
		for (auto j : mRowStrips[i])
		{
			if (j >= 0 && j < s)
			{
				if (tmp[j] > 0) tmp[j] += 1;
			}
			else
			{
				LOG_WARN("invalid col strips info, idx %d, has line idx %d, total line size %d", i, j, s);
			}
		}
	}

	for (auto i : tmp)
	{
		if (i > 1)
		{
			aBlockLineArr.emplace_back(i);
		}
	}
}

void BattleInstance::TryGetSkillsFromArgs(vector<int>& aSkills, int aTplId, int aArmyId)
{
	if (aArmyId == 1)
	{
		for (auto& army : mArgs->army1arr())
		{
			for (auto& unit : army.unitarr())
			{
				if (unit.htid() == aTplId)
				{
					for (auto skillId : unit.skillarr())
					{
						aSkills.emplace_back(skillId.id());
					}
					return;
				}
			}
		}
	}
	else
	{
		for (auto& army : mArgs->army2arr())
		{
			for (auto& unit : army.unitarr())
			{
				if (unit.htid() == aTplId)
				{
					for (auto skillId : unit.skillarr())
					{
						aSkills.emplace_back(skillId.id());
					}
					return;
				}
			}
		}
	}
}

void BattleEvent::Reset()
{
	mKey = 0;
}

int BattleEvent::GetEventId() const
{
	return mKey;
}

void BattleEvent::SetEventId(int aKey)
{
	mKey = aKey;
}
