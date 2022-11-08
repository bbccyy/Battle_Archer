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

#include "BuffMgr.h"
#include "Buff.h"
#include "Framework/SharedPool.h"
#include "Log/Log.h"
#include "Entity/Unit.h"
#include "ConfigMgr/ConfigMgr.h"
#include "View/BattleViewOutput.h"
#include "Buff/BuffMod.h"
#include "Skill/SkillDefine.h"
#include "BattleInstance.h"
#include "Framework/Util.h"


bool CompareBuffLv(const SharedPtr<Buff>& aA, const SharedPtr<Buff>& aB)
{
	return aA->mBeCleanLevel > aB->mBeCleanLevel;
}


BuffMgr::BuffMgr(WeakPtr<Unit> aOwner, BattleViewOutput& aView)
    : mOwner(aOwner)
    , mView(&aView)
	, mBuffNumberChanged(false)
	, mInClean(false)
{
    
}

void BuffMgr::Reset()
{
    mBuffSetRemoved.clear();
    mBuffMap.clear();
    mOwner = nullptr;
	mEndOnDamageMods.clear();

	mView = nullptr;
	mBuffNumberChanged = false;
	mInClean = false;

	mBuffInRemove1.clear();
	mBuffInRemove2.clear();
	mBuffInRemove3.clear();
	mBuffInRemove4.clear();
	mBuffInRemove5 = 0;
}

bool BuffMgr::hasInRemoveSub(int aBuffId, vector<int>& aVec)
{
	for (int i = 0; i < aVec.size(); i++)
	{
		if (aBuffId == aVec[i])
		{
			return true;
		}
	}
	return false;
}

bool BuffMgr::HasInRemove(int aBuffId)
{
	if (!mBuffInRemove1.empty() && hasInRemoveSub(aBuffId, mBuffInRemove1)) return true;
	if (!mBuffInRemove2.empty() && hasInRemoveSub(aBuffId, mBuffInRemove2)) return true;
	if (!mBuffInRemove3.empty() && hasInRemoveSub(aBuffId, mBuffInRemove3)) return true;
	if (!mBuffInRemove4.empty() && hasInRemoveSub(aBuffId, mBuffInRemove4)) return true;
	if (mBuffInRemove5 == aBuffId) return true;
	
	return false;
}

bool BuffMgr::TryAddBuff(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Unit>& aSourceUtilizer, int aBuffId, int aLevel, WeakPtr<Skill> aAncestorSkill, int aBTDel, bool aAbleToInterrupt)
{
	if (mInClean) return false;
	if (HasInRemove(aBuffId)) return false;

    SharedPtr<Buff> buff = nullptr;
    const BuffData* config = ConfigMgr::GetConfById<BuffData>(aBuffId);
	if (!config)
	{
		LOG_WARN("unable to load conf for buff %d", aBuffId);
		return false;
	}
	
    if (static_cast<BuffHitConditionType>(config->specialhitmodel().hittype()) == BuffHitConditionType::None)
    {  
		int64 origHitRate = config->basedatamodel().hitrate();
		if (mOwner->GetBattleInstance().Rand(DENOM) > origHitRate)
			return false;  //miss
    }
	auto iter = mBuffMap.find(aBuffId);
    if (iter != mBuffMap.end())
    {
		buff = iter->second;
		if (!buff->IsValid())
		{
			return false;
		}
        if (mOwner->IsImmueToBuff(aBuffId, buff->GetType(), buff->GetSubType()))
        {
            mOwner->GetView()->Execute(ViewCommand::ImmueBuff, mOwner->GetEntityId(), aBuffId);
            return false;
        }
        //special hit/miss check
		if (!buff->CheckHitCondition(*this))
		{
			return false;
		} 
        int stack = buff->GetStack();
        int stackNew = buff->WhenAddSameBuff();
		buff->mAncestorSkill = aAncestorSkill;
        if (stackNew != stack && buff->IsValid())
        {
            mView->Execute(ViewCommand::BuffNumberChange, mOwner->GetEntityId(), aBuffId, stackNew); 
            //mOwner->TryTriggerSkill(ETriggerMajor::BuffNumber); 
			int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::BuffNumber), static_cast<int>(ETriggerCommonSub::None));
			mOwner->GetBattleInstance().DispatchEvent(key, mOwner->GetArmyId(), mOwner->GetEntityId(), aBuffId, stackNew);
            mBuffNumberChanged = true;
        } 
		if (buff->IsValid())
		{
			if (buff->mOverrideType == BuffOverrideType::Reset || buff->mOverrideType == BuffOverrideType::StackReset)
			{
				mOwner->OnBuffSubtypeActive(buff->GetSubType());
			}
		}
		// mOwner->TryRefreshAnimByBuff(config);
		return true;
    }
    else
    {
        if (mOwner->IsImmueToBuff(aBuffId
            , static_cast<BuffType>(config->basedatamodel().maintype())
            , static_cast<BuffSubType>(config->basedatamodel().subtype())
            ))
            return false;
    }
    //special hit/miss check
    SharedPtr<BuffHitCondition> condition = CreateBuffHitCondition(config, aUtilizer.Get());
    if (condition->Valid(*this, config))
    {
        buff = SharedPool<Buff>::Get();
        bool suc = buff->Init(aUtilizer, aSourceUtilizer, mOwner, *this, aBuffId, aLevel, config, condition);
		if (!suc)
		{ //shrink time to zero, so direct skip this control buff 
			buff->Reset();  //call reset to prevent lua failure, lua needs the reset action 
			buff.Release();  //will tranlate to buff = nil in lua
			return false;
		}
		if (!aAbleToInterrupt && buff->IsControlType()) 
		{ //block this buff since not able to interrupt 
			buff->Reset();  //call reset to prevent lua failure, lua needs the reset action 
			buff.Release();  //will tranlate to buff = nil in lua
			return false;
		}
		if (mBuffMap.insert(aBuffId, buff) == false)
		{ //buff->AddModsByConf may trigger another round of Try_Add_Same_Buff 
			buff->Reset();
			buff.Release();
			return false;
		}
		mView->Execute(ViewCommand::BuffAdd, mOwner->GetEntityId(), aBuffId, aSourceUtilizer->GetEntityId(), aBTDel);
		buff->AddModsByConf(aUtilizer, buff, aLevel - 1, config);
		buff->mAncestorSkill = aAncestorSkill;  
		mBuffNumberChanged = true;  
		int key = BattleInstance::GenerateEventKey(static_cast<int>(ETriggerMajor::BuffNumber), static_cast<int>(ETriggerCommonSub::None));
		mOwner->GetBattleInstance().DispatchEvent(key, mOwner->GetArmyId(), mOwner->GetEntityId(), aBuffId, buff->GetStack());
		if (buff->IsValid())
			mOwner->OnBuffSubtypeActive(buff->GetSubType());
        return true;
    }
    return false;
}

SharedPtr<BuffHitCondition> BuffMgr::CreateBuffHitCondition(const BuffData* aConfig, Unit* aUtilizer)
{
    SharedPtr<BuffHitCondition> condition;
    switch ( static_cast<BuffHitConditionType>(aConfig->specialhitmodel().hittype()))
    {
	case BuffHitConditionType::ByType:
    {
		SharedPtr<BuffHitByType> byType = SharedPool<BuffHitByType>::Get();
        byType->mType = static_cast<BuffType>(aConfig->specialhitmodel().bufftype());
        condition = byType;
    }
    break;
	case BuffHitConditionType::BySubType:
    {        
		SharedPtr<BuffHitBySubType> bySubType = SharedPool<BuffHitBySubType>::Get();
        bySubType->mSubType = static_cast<BuffSubType>(aConfig->specialhitmodel().bufftype());
		condition = bySubType;
    }
    break;
	case BuffHitConditionType::AllBuffExists:
    {
		SharedPtr<BuffHitAllBuffExists> allExists = SharedPool<BuffHitAllBuffExists>::Get();        
        for (int id : aConfig->specialhitmodel().bufflist())
        {
            allExists->mBuffs.push_back(id);
        }
        condition = allExists;
    }
    break;
	case BuffHitConditionType::AnyBuffExists:
    {        
		SharedPtr<BuffHitAnyBuffExists> anyExists = SharedPool<BuffHitAnyBuffExists>::Get();
        for (int id : aConfig->specialhitmodel().bufflist())
        {
            anyExists->mBuffs.push_back(id);
        }
        condition = anyExists;
    }
    break;
	case BuffHitConditionType::NeedOtherGender:
	{
		SharedPtr<BuffHitByGender> byGender = SharedPool<BuffHitByGender>::Get();
		byGender->mUtilizer = aUtilizer;
		condition = byGender;
	}
	break;
    default:        
		SharedPtr<BuffHitNone> none = SharedPool<BuffHitNone>::Get();
        condition = none;
        break;
    }
    return condition;
}

vector<BuffMod*> BuffMgr::SearchMod(BuffSubType aType)
{
	vector<BuffMod*> ret;
    for (auto& buffPair : mBuffMap)
    {
        auto* mod = buffPair.second->GetMod(aType);
        if(mod)
			ret.push_back(mod->Get());
    }
    return ret;
}

int BuffMgr::CountBuffLayerByMainType(BuffType aType) const
{
	int count = 0;
	for (auto& buffPair : mBuffMap)
	{
		if (buffPair.second->GetType() == aType)
			count += buffPair.second->GetStack();
	}
	return count;
}

int BuffMgr::CountBuffLayerBySubType(BuffSubType aType) const
{
	int count = 0;
	for (auto& buffPair : mBuffMap)
	{
		if (buffPair.second->GetSubType() == aType)
			count += buffPair.second->GetStack();
	}
	return count;
}

bool BuffMgr::CheckBuffExistenceBySubType(BuffSubType aSubType) const
{
	for (auto& buffPair : mBuffMap)
	{
		if (buffPair.second->GetSubType() == aSubType) 
			return true;
	}
	return false;
}

bool BuffMgr::CheckBuffExistenceBySubTypeOR(vector<BuffSubType>& aList) const
{
	for (auto& buffPair : mBuffMap)
	{
		auto curType = buffPair.second->GetSubType();
		for (auto type : aList)
		{
			if (curType == type) return true;
		}
	}
	return false;
}

int BuffMgr::CountBuffLayerByBuffIdOR(const vector<int>& aIds) const
{
	int count = 0;
	for (auto buffId : aIds)
	{
		auto iter = mBuffMap.find(buffId);
		if (iter != mBuffMap.end())
		{
			auto stack = iter->second->GetStack();
			count = count > stack ? count : stack;
		}
	}
	return count;
}

int BuffMgr::CountBuffLayerByBuffIdAND(const vector<int>& aIds) const
{
	int count = 0;
	for (auto buffId : aIds)
	{
		auto iter = mBuffMap.find(buffId);
		if (iter != mBuffMap.end())
			count += iter->second->GetStack();
		else
			return 0;
	}
	return count;
}

bool BuffMgr::HasBuff(int aBuffId) const
{
	return mBuffMap.find(aBuffId) != mBuffMap.end();
}

WeakPtr<Buff> BuffMgr::GetBuff(int aBuffId)
{
	if (mBuffMap.find(aBuffId) == mBuffMap.end()) return nullptr;
	return static_cast<WeakPtr<Buff>>(mBuffMap.find(aBuffId)->second);
}

void BuffMgr::EndOnDamage(BuffMod* aMod)
{
	uniqEmplaceBackToVector(mEndOnDamageMods, aMod);    
}

void BuffMgr::CheckEndOnDamage()
{
    for (auto* m : mEndOnDamageMods)
    {
        m->Disable(false);
    }
    mEndOnDamageMods.clear();
}

void BuffMgr::FilterBuffByBeControlledMark()
{
	vector<int> toRemove;
	//auto buffMap = mBuffMap.copy();
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
	for (auto& buff : buffMap)
	{
		if (mBuffMap.size() == 0) //buffMgr has been cleaned during loop, return directly 
			return;
		if (buff.second->NeedRemoveWhenBeControlled())
		{
			toRemove.emplace_back(buff.first);
			mBuffSetRemoved.emplace(buff.second);
			buff.second->OnRemove(true);
		}
	}
	for (auto& id : toRemove)
	{
		mBuffMap.erase(id);
	}
	if (!toRemove.empty())
	{
		mBuffNumberChanged = true;
	}
    RestoreVectorToPool(toRemove);
}

void BuffMgr::FilterBuffByShapeShiftMark()
{
	vector<int> toRemove;
	//auto buffMap = mBuffMap.copy();
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
	for (auto& buff : buffMap)
	{
		if (mBuffMap.size() == 0) //buffMgr has been cleaned during loop, return directly 
			return;
		if (buff.second->NeedRemoveWhenShapeShifted())
		{
			toRemove.emplace_back(buff.first);
			mBuffSetRemoved.emplace(buff.second);
			buff.second->OnRemove(true);
		}
	}
	for (auto& id : toRemove)
	{
		mBuffMap.erase(id);
	}
	if (!toRemove.empty())
	{
		mBuffNumberChanged = true;
	}
	RestoreVectorToPool(toRemove);
}

bool BuffMgr::RemoveByBuffType(const vector<BuffType>& aTypeArr, int aPartialCount, int aByBuffId, bool aShouldTrigger, int aCleanLv)
{
    int removed;
	bool suc = false;
    vector<int> toRemove;
	//auto buffMap = mBuffMap.copy();
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
	buffMap.sort(CompareBuffLv); // from high cleanLv to low cleanLv 

    for (auto& buff : buffMap)
    {
		if (mBuffMap.size() == 0) { //buffMgr has been cleaned during loop, return directly 
			if (!mBuffInRemove1.empty()) mBuffInRemove1.clear();
			return true;
		}
		if(	aCleanLv >= buff.second->mBeCleanLevel   // has enough priviledge to clean up this buff 
			&& InVector(aTypeArr, buff.second->GetType() )
			&& (aByBuffId == 0 ||  buff.second->IsClearableByBuff(aByBuffId) ) )
        {
			mBuffInRemove1.emplace_back(buff.first);
			suc = true;
            if (aPartialCount > 0)
            {
                removed = buff.second->RemoveStack(aPartialCount);
                aPartialCount -= removed;
                if (aPartialCount <= 0)
                {
                    break;
                }
            }
			else if (aPartialCount < 0)
			{
				buff.second->OnRemove(aShouldTrigger);
				toRemove.emplace_back(buff.first);
				mBuffSetRemoved.emplace(buff.second);
				aPartialCount++;
				if (aPartialCount >= 0)
				{
					break;
				}
			}
            else
            {
                buff.second->OnRemove(aShouldTrigger);
                toRemove.emplace_back(buff.first);
                mBuffSetRemoved.emplace(buff.second);
            }
        }
    }
    for (auto& id : toRemove)
    {        
        mBuffMap.erase(id);
    }
	if (!toRemove.empty())
	{
		mBuffNumberChanged = true;
	}
	if (!mBuffInRemove1.empty()) mBuffInRemove1.clear();
	return suc;
}

bool BuffMgr::RemoveByBuffSubType(const vector<BuffSubType>& aSubTypeArr, int aPartialCount, int aByBuffId, bool aShouldTrigger, int aCleanLv)
{
    int removed;
	bool suc = false;
    vector<int> toRemove;
	//auto buffMap = mBuffMap.copy();
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
	buffMap.sort(CompareBuffLv);

    for (auto& buff : buffMap)
    {
		if (mBuffMap.size() == 0) { //buffMgr has been cleaned during loop, return directly 
			if (!mBuffInRemove2.empty()) mBuffInRemove2.clear();
			return true;
		}
		if ( aCleanLv >= buff.second->mBeCleanLevel 
			&& InVector(aSubTypeArr, buff.second->GetSubType() )
			&& (aByBuffId == 0 || buff.second->IsClearableByBuff(aByBuffId)) )
        {
			mBuffInRemove2.emplace_back(buff.first);
			suc = true;
            if (aPartialCount)
            {
                removed = buff.second->RemoveStack(aPartialCount);
                aPartialCount -= removed;
                if (aPartialCount <= 0)
                {
                    break;
                }
            }
			else if (aPartialCount < 0)
			{
				buff.second->OnRemove(aShouldTrigger);
				toRemove.emplace_back(buff.first);
				mBuffSetRemoved.emplace(buff.second);
				aPartialCount++;
				if (aPartialCount >= 0)
				{
					break;
				}
			}
            else
            {
				toRemove.emplace_back(buff.first);
				mBuffSetRemoved.emplace(buff.second);
                buff.second->OnRemove(aShouldTrigger);
            }
        }
    }
    for (auto& id : toRemove)
    {
        mBuffMap.erase(id);
    }
	if (!toRemove.empty())
	{
		mBuffNumberChanged = true;
	}
	if (!mBuffInRemove2.empty()) mBuffInRemove2.clear();
	return suc;
}

bool BuffMgr::RemoveBuff(int aBuffId, int aPartialCount, bool aTriggerEvent)
{
	//auto buffMap = mBuffMap.copy();
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
	auto iter = buffMap.find(aBuffId);
    if (iter == buffMap.end())
        return false;

	mBuffInRemove3.emplace_back(aBuffId);
    if (aPartialCount)
    {
		iter->second->RemoveStack(aPartialCount);
    }
    else
    {
        auto& buff = iter->second;
		mBuffSetRemoved.emplace(buff);
		mBuffMap.erase(aBuffId);
        buff->OnRemove(aTriggerEvent);
    }
	
	mBuffNumberChanged = true;	
	if (!mBuffInRemove3.empty()) mBuffInRemove3.clear();
	return true;
}

bool BuffMgr::RemoveBuff(const vector<int>& aBuffArr, int aPartialCount, int aByBuffId, bool aShouldTrigger)
{
    int removed;
	bool suc = false;
    vector<int> toRemove;
	//auto buffMap = mBuffMap.copy();  //loop on copy return 
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
    for (auto& id : aBuffArr)
    {   
		if (mBuffMap.size() == 0) {
			if (!mBuffInRemove4.empty()) mBuffInRemove4.clear();
			return true;
		}
		auto iter = buffMap.find(id);
        if (iter != buffMap.end())
        {
			auto& buff = iter->second;
            if (aByBuffId == 0 || buff->IsClearableByBuff(aByBuffId) ) 
            {  
				mBuffInRemove4.emplace_back(id);
				suc = true;
                if (aPartialCount)
                {
                    removed = buff->RemoveStack(aPartialCount);
                    aPartialCount -= removed;
                    if (aPartialCount <= 0)
                    {
                        break;
                    }
                }
                else
                {
					toRemove.emplace_back(id);
					mBuffSetRemoved.emplace(buff);
                    buff->OnRemove(aShouldTrigger);
                }
            }
        }			
    }
    for (auto& id : toRemove)
    {
        mBuffMap.erase(id);
    }
	if (!toRemove.empty())
	{
		mBuffNumberChanged = true;
	}
	if (!mBuffInRemove4.empty()) mBuffInRemove4.clear();
	return suc;
}

bool BuffMgr::RemoveBuffById(int const aId)
{
    auto iter = mBuffMap.find(aId);
    if(iter == mBuffMap.end())
    {
        return false;
    }
	mBuffInRemove5 = aId;
    mBuffSetRemoved.emplace(iter->second);
    mBuffMap.erase(aId);
	mBuffNumberChanged = true;
	mBuffInRemove5 = 0;
	return true;
}

void BuffMgr::CleanListener()
{
	for (auto& buff : mBuffMap)
	{
		buff.second->CleanListener();
	}
}

void BuffMgr::Clear(bool aShouldTrigger)
{
	if (mInClean)
		return;
	mInClean = true;
	//auto buffMap = mBuffMap.copy();
	MapOnVector<int, SharedPtr<Buff> > buffMap;
	mBuffMap.copy(buffMap);
    for (auto& buff : buffMap)
    {
		if (mBuffMap.size() == 0)
			return;
        buff.second->OnRemove(aShouldTrigger);
        mBuffSetRemoved.emplace(buff.second);
    }
	//to prevent insertion during onRemove(true) when first loop 
	MapOnVector<int, SharedPtr<Buff> > buffMap2;
	mBuffMap.copy(buffMap2);
	for (auto& buff : buffMap2)
	{
		if (buffMap.find(buff.first) == buffMap.end())
		{
			buff.second->OnRemove(false);
			mBuffSetRemoved.emplace(buff.second);
		}
	}
    mEndOnDamageMods.clear();    
    mBuffMap.clear();
	mBuffNumberChanged = true;
	mInClean = false;
}



WeakPtr<Unit> BuffMgr::GetOwner() const
{
	return mOwner;
}

const MapOnVector<int, SharedPtr<Buff> >& BuffMgr::GetBuffMap() const
{
    return mBuffMap;
}


void BuffMgr::OnTick()
{
	if (mBuffNumberChanged)
	{
		//auto buffMap = mBuffMap.copy();
		MapOnVector<int, SharedPtr<Buff> > buffMap;
		mBuffMap.copy(buffMap);
		for (auto& buff : buffMap)
		{
			buff.second->WhenBuffNumberChanged();
		}
		mBuffNumberChanged = false;
	}
    mBuffSetRemoved.clear();
}