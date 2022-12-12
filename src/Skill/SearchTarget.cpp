/**********************************************************************************************************************
 *
 * CopyaRight (c) 2010 babeltime.com, Inc. All Rights Reserved
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


#include <limits.h>
#include "SearchTarget.h"
#include "Skill/Skill.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"
#include "BattleInstance.h"
#include "Log/Log.h"
#include "Framework/Util.h"
#include "Framework/Physics/Region.h"
#include "ConfigMgr/ConfigMgr.h"


int partitionUnit(vector<Unit*>& aArr, int aLeft, int aRight)
{ 
    Unit* refUnit = aArr[aLeft];
    int64 ref = refUnit->mRegister0;
	int64 ref1 = refUnit->mRegister1;
    while( aLeft < aRight )
    {
        while(aLeft < aRight && (aArr[aRight]->mRegister1 > ref1 || aArr[aRight]->mRegister0 >= ref))
        {
            aRight--;
        }
        if( aLeft < aRight) 
        {
            aArr[aLeft] = aArr[aRight]; 
            aLeft++;
        }
        while(aLeft < aRight && (aArr[aLeft]->mRegister1 < ref1 || aArr[aLeft]->mRegister0 < ref))
        {
            aLeft++;
        }
        if(aLeft < aRight) 
        {
            aArr[aRight] = aArr[aLeft]; 
            aRight--;
        }
    }
    aArr[aLeft] = refUnit;
    return aLeft;
}

void topNUnit(vector<Unit*>& aArr, int aTopN, int aLeft, int aRight)
{
    if(aLeft < aRight)
    {
        int pos = partitionUnit(aArr, aLeft, aRight);
        if( aTopN + aLeft == pos + 1 ) //topN正好在pos上 
        {
            return;
        }
        if( aTopN + aLeft < pos + 1) //当topN在左半部分时  
        {
            topNUnit(aArr, aTopN, aLeft, pos-1); 
        }
        else 
        {
            topNUnit(aArr, aTopN - (pos+1 - aLeft), pos+1, aRight);
        }
    }  
}

void GetScenePosTD(Unit* aUnit, int aIndex, Vector3& aPosOut, Vector3& aRotOut)
{
	aPosOut.Set(aUnit->GetPosition());
	aRotOut.Set(aUnit->GetForward());
	if (aIndex == 2)
		return;
	Vector3 dir;
	if (aIndex < 2)
		dir.Set(-aRotOut.x, 0, aRotOut.z);
	else
		dir.Set(aRotOut.x, 0, -aRotOut.z);
	int64 len = Abs(aIndex - 3) * 300000;
	dir.ScaleToLen(len);
	aPosOut.Set(aPosOut.x + dir.x, 0, aPosOut.z + dir.z);
	return;
}

//aOrigin -> [Front_priority | Middle | Back]
//aOutput -> []
//todo: delete it 
bool TryGetPoolFromPosType(vector<int>& aOrigin, vector<EPosType>& aOutput)
{
	int max = -1;
	for (auto v : aOrigin)
	{
		if (v > max)
			max = v;
	}

	if (max < 0)
		return false;

	for (int idx = 0; idx < aOrigin.size(); ++idx)
	{
		if (aOrigin[idx] == max)
		{
			aOutput.emplace_back(static_cast<EPosType>(idx + 1));
			aOrigin[idx] = -1;
		}
	}

	return true;
}

void FilterByCastRange(vector<Unit*>& aAllUnits, vector<Unit*>& aInRange, const SharedPtr<Unit>& aUtilizer, int aCastRange)
{
	int64 mRealCastRange, dist2;	
	int allSize = aAllUnits.size();
	for (int idx = 0; idx < allSize; )
	{
		Vector3 delt = aUtilizer->GetPosition() - aAllUnits[idx]->GetPosition();
		delt.y = 0;
		dist2 = delt.Magnitude2();
		RestoreObjToPool(delt);
		mRealCastRange = aCastRange + aAllUnits[idx]->GetSize() + aUtilizer->GetSize() + MIN_LEN; 
		if (dist2 <= (mRealCastRange*mRealCastRange))
		{
			aInRange.emplace_back(aAllUnits[idx]);
			--allSize;
			if (idx < allSize)
			{
				aAllUnits[idx] = aAllUnits[allSize];
			}
			aAllUnits.resize(allSize);
		}
		else
		{
			++idx;
		}
	}	
}

void GetUnitArrByHeroStatus(ENeedSummon aNeedSummon, bool aNeedDead, vector<Unit*>& aUnitArr)
{
	Unit* unit = nullptr;
	size_t len = aUnitArr.size();
	for (size_t i = 0; i < len; )
	{
		unit = aUnitArr[i];
		if (!unit->IsHidden()
			&& (aNeedSummon == ESummonAndHero || (unit->IsSummoned() == (aNeedSummon == EOnlySummon))) 
			&& (aNeedDead == unit->IsDead()))
		{ //only summon or only hero or both 
			i++;
		}
		else
		{
			--len;
			aUnitArr[i] = aUnitArr[len];
		}
	}
	aUnitArr.resize(len);
}

void RandInRange(BattleInstance& aBattle, vector<Unit*>& aUnitArr, int aLeft, int aRight, int aRandNum)
{
	int rangeSize = aRight - aLeft + 1;
	int index = 0;
	if (rangeSize < 1 || aRandNum < 1 || rangeSize <= aRandNum) return;

	for (int i = aLeft; i < aLeft + aRandNum; i++)
	{
		index = aBattle.Rand(rangeSize) + i;
		auto tmp = aUnitArr[i];
		aUnitArr[i] = aUnitArr[index];
		aUnitArr[index] = tmp;
        rangeSize--;
	}
}

void FilterRand( const SharedPtr<Unit>& aUtilizer, int aRandNum, vector<Unit*>& aUnitArr)
{
    int num = static_cast<int>(aUnitArr.size());
    int offset = 0;
    int index = 0;
    Unit* firstUnit;

    if( aRandNum <= 0 )
    {
        LOG_FATAL("aRandNum == 0");
    }
    if( num <= aRandNum )
    {
        return;
    }

	int liveIdx = num - 1;
	for (int i = 0; i < liveIdx;)
	{
		if (aUnitArr[i]->IsDying())
		{
			auto tmp = aUnitArr[i];
			aUnitArr[i] = aUnitArr[liveIdx];
			aUnitArr[liveIdx] = tmp;
			--liveIdx;
		}
		else {
			++i;
		}
	}

	int liveNum = liveIdx + 1;  //num of live unit(not dying)
	BattleInstance& battleInstance = aUtilizer->GetBattleInstance();

	if (aRandNum <= liveNum)
	{  //discasd all dying units if any
		RandInRange(battleInstance, aUnitArr, 0, liveNum - 1, aRandNum);
		aUnitArr.resize(aRandNum);
	}
	else {
		//need include all live units
		//random in dying pool
		RandInRange(battleInstance, aUnitArr, liveNum, num - 1, aRandNum - liveNum); 
		aUnitArr.resize(aRandNum);
	}

}


//Two phase filt, one for Dying units, the other for Non-Dying units(alive or dead)
//Non-Dying units, if any, would be considered with highest privilege
//Dying units are used to feed the gap between realNum and wanted Num
//In fact, if needDead == true, there will be no Dying units at all :)
void FilterByDist( const SharedPtr<Unit>& aUtilizer, int aNum, int aFlag, vector<Unit*>& aUnitArr)
{    
	if (aUnitArr.size() <= aNum)
	{
		return;
	}
	Vector2 delt;
    for(size_t i = 0; i < aUnitArr.size(); i++)
    {
        delt.x = aUtilizer->GetPosition().x - aUnitArr[i]->GetPosition().x;
        delt.z = aUtilizer->GetPosition().z - aUnitArr[i]->GetPosition().z;
        aUnitArr[i]->mRegister0 = delt.Magnitude2() * aFlag;
		if (aUnitArr[i]->IsDying())
		{
			aUnitArr[i]->mRegister1 = 1;
		}
		else {
			aUnitArr[i]->mRegister1 = -1;
		}
    }
	RestoreObjToPool(delt);
    topNUnit(aUnitArr, aNum, 0, static_cast<int>(aUnitArr.size()-1));
    aUnitArr.resize(aNum);
}

void FilterByAttribute( int aAttributeName, int aNum, int aFlag, vector<Unit*>& aUnitArr)
{
    size_t num = aUnitArr.size();
	if (num <= aNum)
	{
		return;
	}
    switch(aAttributeName)
    {
        case  ESearchTargetFilterAttributeNameHp:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = aUnitArr[i]->GetHp() * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
        case ESearchTargetFilterAttributeNameLostHp:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = ( aUnitArr[i]->GetMaxHp() - aUnitArr[i]->GetHp() ) * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
        case ESearchTargetFilterAttributeNameRage:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = aUnitArr[i]->GetRage() * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
		case ESearchTargetFilterAttributeNameAtk:
			for (size_t i = 0; i < num; i++)
			{
				aUnitArr[i]->mRegister0 = aUnitArr[i]->GetPhysicalAtk(); 
				int64 magcAtk = aUnitArr[i]->GetMagicAtk();
				if (aUnitArr[i]->mRegister0 < magcAtk)
				{
					aUnitArr[i]->mRegister0 = magcAtk;
				}
				aUnitArr[i]->mRegister0 *= aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
			}
			break;
        case ESearchTargetFilterAttributeNamePhysicalAtk:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = aUnitArr[i]->GetPhysicalAtk() * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
        case ESearchTargetFilterAttributeNameMagicAtk:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = aUnitArr[i]->GetMagicAtk() * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
        case ESearchTargetFilterAttributeNamePhysicalDef:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = aUnitArr[i]->GetPhysicalDef() * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
        case ESearchTargetFilterAttributeNameMagicDef:
            for(size_t i = 0; i < num; i++)
            {
                aUnitArr[i]->mRegister0 = aUnitArr[i]->GetMagicDef() * aFlag;
				if (aUnitArr[i]->IsDying())
				{
					aUnitArr[i]->mRegister1 = 1;
				}
				else {
					aUnitArr[i]->mRegister1 = -1;
				}
            }
            break;
    }
    
    topNUnit(aUnitArr, aNum, 0, static_cast<int>(aUnitArr.size()-1));
    aUnitArr.resize(aNum);
}


void FilterByBuff( const SharedPtr<Unit>& aUtilizer, int aBuffId, int aBuffId2, vector<Unit*>& aUnitArr)
{    
    size_t num = aUnitArr.size();
	bool found = false;
	for (size_t i = 0; i < num; ++i)
	{
		if (aUnitArr[i]->HasBuff(aBuffId))
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		for (size_t i = 0; i < num; )
		{
			if (aUnitArr[i]->HasBuff(aBuffId))
			{
				i++;
			}
			else
			{
				num--;
				aUnitArr[i] = aUnitArr[num];
			}
		}
		aUnitArr.resize(num);
	}
	else if (aBuffId2 > 0)
	{
		for (size_t i = 0; i < num; )
		{
			if (aUnitArr[i]->HasBuff(aBuffId2))
			{
				i++;
			}
			else
			{
				num--;
				aUnitArr[i] = aUnitArr[num];
			}
		}
		aUnitArr.resize(num);
	}
	else
	{
		aUnitArr.resize(0);
	}
}

void FilterToGetCounterpart(vector<Unit*>& aUnitArr, const Vector3* aCenter, int64 aSelfSize, int64 aRangeParam, int64 aStandDist)
{
	if (aStandDist <= 0)
		aStandDist = aRangeParam;
	size_t size = aUnitArr.size();
	for (size_t i = 0; i < size; )
	{
		int64 dx = aUnitArr[i]->GetPosition().x - aCenter->x;
		int64 tx = aRangeParam + aSelfSize + aUnitArr[i]->GetSize();
		if (dx < -tx || dx > tx)
		{
			aUnitArr[i] = aUnitArr[size - 1];
			--size;
		}
		else
		{
			++i;
		}
	}
	aUnitArr.resize(size);
	if (size < 1)
		return;
	int64 minDist = -1;
	int tarIdx = 0;
	for (size_t i = 0; i < size; ++i)
	{
		const Vector3& pos = aUnitArr[i]->GetPosition();
		int64 sum = Abs(pos.x - aCenter->x);
		int64 penalty = -Abs(pos.z - aCenter->z) / 2;
		sum += penalty;
		if (sum < 0) sum = 0;
		int64 tarDist = aStandDist + aSelfSize + aUnitArr[i]->GetSize();
		int64 dist = Abs(sum - tarDist);
		if (minDist < 0 || minDist > dist)
		{
			minDist = dist;
			tarIdx = i;
		}
	}
	aUnitArr[0] = aUnitArr[tarIdx];
	aUnitArr.resize(1);
	return;
}

void FilterByRegion(vector<Unit*>& aUnitArr, Region* aRegion)
{
    bool hasCollision;
    size_t num = aUnitArr.size();
    for(size_t i = 0; i < num; )
    {
        BoundingVolume* bv = aUnitArr[i]->GetBV();
        hasCollision = bv && CollisionDetectionRegionWithBV(aRegion, bv);
        if(hasCollision)
        {
            i++;
        }
        else
        {
            num--;
            aUnitArr[i] = aUnitArr[num];
        }
    }
	aUnitArr.resize(num);
}

void FilterByMostIncludeCycle(vector<Unit*>& aUnitArr, const SharedPtr<Unit>& aSelf, int64 aRadius)
{
	if (aUnitArr.empty())
		return;
	auto& selfPos = aSelf->GetPosition();
	int tarIdx = 0;
	int maxCt = 0;
	size_t num = aUnitArr.size();
	int64 maxRange = aRadius * aRadius;
	for (size_t i = 0; i < num; i++)
	{
		int ct = 0;
		auto* u = aUnitArr[i];
		auto& tarPos = u->GetPosition();
		for (size_t j = 0; j < num; j++)
		{
			if (i != j)
			{
				auto* v = aUnitArr[j];
				auto& curPos = v->GetPosition();
				if (maxRange >= (curPos - tarPos).Magnitude2())
				{
					ct++;
				}
			}
		}
		if (ct > maxCt)
		{
			maxCt = ct;
			tarIdx = i;
		}
	}
	aUnitArr[0] = aUnitArr[tarIdx];
	aUnitArr.resize(1);
}

void FilterByMostInclude(vector<Unit*>& aUnitArr, const SharedPtr<Unit>& aSelf, int64 aWidth)
{
	if (aUnitArr.empty())
		return;
	RegionRectangle rectangle;
	auto& selfPos = aSelf->GetPosition();
	int tarIdx = 0;
	int maxCt = 0;
	int maxSize = 0;
	size_t num = aUnitArr.size();
	for (size_t i = 0; i < num; i++)
	{
		auto* u = aUnitArr[i];
		auto& tarPos = u->GetPosition();
		if (tarPos == selfPos)
			continue;
		auto forward = tarPos - selfPos;
		rectangle.center.x = selfPos.x + forward.x / 2;
		rectangle.center.z = selfPos.z + forward.z / 2;
		rectangle.halfSize.z = forward.Magnitude() / 2;
		rectangle.halfSize.x = aWidth / 2;
		rectangle.forward.x = forward.x;
		rectangle.forward.z = forward.z;
		bool hasCollision = false;
		int ct = 0;
		for (size_t j = 0; j < num; j++)
		{
			if (aUnitArr[j] == u)
			{
				ct++;
			}
			else
			{
				BoundingVolume* bv = aUnitArr[j]->GetBV();
				hasCollision = bv && CollisionDetectionRegionWithBV(&rectangle, bv);
				if (hasCollision)
				{
					ct++;
				}
			}
		}
		if (ct > maxCt || (ct == maxCt && rectangle.halfSize.z > maxSize))
		{
			maxCt = ct;
			maxSize = rectangle.halfSize.z;
			tarIdx = i;
		}
	}
	aUnitArr[0] = aUnitArr[tarIdx];
	aUnitArr.resize(1);
	return;
}


void FilterByTargetPriority(BattleInstance& aBattle, vector<Unit*>& aUnitArr, int aNum)
{
	size_t num = aUnitArr.size();
	if (num <= aNum)
		return;
	//filter by hero's priority 
	//pick randomly among valid ones if surpasses uplimit 
	int origNum = aNum;
	vector<vector<Unit*>> sortList(12);
	int index = 0;
	for (size_t i = 0; i < num; i++)
	{
		int tp = aUnitArr[i]->mConfig->GetTargetPriority(); 
		sortList[tp % 12].emplace_back(aUnitArr[i]); 
	}
	for (size_t i = sortList.size() - 1; i >= 0; --i)
	{
		if (sortList[i].size() == 0) continue;  //skip empty
		if (sortList[i].size() <= aNum)
		{ //in this case, include all 
			for (auto unitPtr : sortList[i])
			{
				aUnitArr[index] = unitPtr;
				++index;
			}
			aNum -= sortList[i].size();
			if (aNum == 0)
			{
				aUnitArr.resize(origNum); 
				return;
			}
		}
		else
		{ //in this case, include needed then return
			RandInRange(aBattle, sortList[i], 0, sortList[i].size()-1, aNum);
			for (size_t j = 0; j < aNum; ++j)
			{
				aUnitArr[index] = sortList[i][j];
				++index;
			}
			aUnitArr.resize(origNum);
			return;
		}
	}
	aUnitArr.resize(origNum);
	return;
}

void SearchRefTargetUnit(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, 
        ESearchRefTargetSpace aSpace, 
        ESearchTargetFilter aFilter,
		bool aExcludeSelf,
        int aFilterParam,
		int aFilterParam2,
        int aRefTargetNum,
		vector<Unit*>& aInputArr,
        vector<RefTarget>& aTargetArr)
{
	const SkillData* skillConf = aSkill->GetSkillConf();

	Unit* exclueSelfPtr = nullptr;
	if (aExcludeSelf)
	{
		exclueSelfPtr = aUtilizer.Get();
	}
    size_t num = aInputArr.size();
    //考虑unit特殊修正状态 
    for(size_t i = 0; i < num;)
    {
        if(aInputArr[i]->CanBeRefTargetOfUtilizer(aUtilizer.Get(), aSkill.Get())
			&& aInputArr[i] != exclueSelfPtr)
        {            
			// capable
            i++; 
        }
        else
        {     
			// incapable
            num--;
			aInputArr[i] = aInputArr[num];
        }
    }
    if (num == 0)
        return;

    //考虑空间关系 
    if( ESearchRefTargetSpaceSkillRange == aSpace )
    {
        int64 castRange = CONF_POS_CONVERT(aSkill->GetSkillConf()->basedata().castrange());
		int64 dist2;
        Vector2 delt;
        for( size_t i = 0; i < num; )
        {           
			dist2 = castRange + aInputArr[i]->GetSize();
			dist2 = dist2*dist2;
            delt.x = aUtilizer->GetPosition().x - aInputArr[i]->GetPosition().x;
            delt.z = aUtilizer->GetPosition().z - aInputArr[i]->GetPosition().z;
            if( delt.Magnitude2() < dist2 )
            {
                i++; 
            }
            else
            {
                num--;
				aInputArr[i] = aInputArr[num];
            }
        }
    }
    if (num == 0)
        return;
	aInputArr.resize(num);
   
    //考虑过滤器 
    switch(aFilter)
    {
        case ESearchTargetFilterNone:
            break;
        case ESearchTargetFilterNearest:
            FilterByDist(aUtilizer, aRefTargetNum, 1, aInputArr);
            break;
        case ESearchTargetFilterFarthest:
            FilterByDist(aUtilizer, aRefTargetNum, -1, aInputArr);
            break;
        case ESearchTargetFilterAttributeMin:
            FilterByAttribute( aFilterParam, aRefTargetNum, 1, aInputArr);
            break;
        case ESearchTargetFilterAttributeMax:
            FilterByAttribute( aFilterParam, aRefTargetNum, -1, aInputArr);
            break;
        case ESearchTargetFilterBuff:
            FilterByBuff( aUtilizer, aFilterParam, aFilterParam2, aInputArr);
			break;
		case ESearchTargetFilterMostIncludeCircle:
			FilterByMostIncludeCycle(aInputArr, aUtilizer, aFilterParam);
			break;
		case ESearchTargetFilterMostInclude:
			FilterByMostInclude(aInputArr, aUtilizer, aFilterParam);
            break;
    }

	//apply random filter 
	if (aInputArr.size() > aRefTargetNum)
	{
		RandInRange(aUtilizer->GetBattleInstance(), aInputArr, 0, aInputArr.size() - 1, aRefTargetNum);
		aInputArr.resize(aRefTargetNum);
	}

	int originSize = aTargetArr.size();
    aTargetArr.resize(originSize + aInputArr.size());
    for(size_t i = 0; i < aInputArr.size(); i++)
    {
        aTargetArr[i + originSize].SetUnit(aInputArr[i]->SharedFromThis() );
    }

}


void SearchRefTargetParam(const SharedPtr<Unit>& aUtilizer, 
	const SharedPtr<Skill>& aSkill, 
	vector<RefTarget>& aTargetArr,
	RefTargetParam& aParam)
{
	const SkillData* skillConf = aSkill->GetSkillConf();
	aTargetArr.clear();
	if (skillConf->subskilldata().isfollow())  //keep the same targets as parent skill
	{
		if (!aSkill->IsChildSkill())
		{
			LOG_WARN("Skill %d is master skill, but conf.subskilldata.isfollow == true", aSkill->GetId());
		}
		else
		{
			auto& arr = aSkill->GetParentSkill()->GetRefTargetArr();
			if (arr.size() > 0)
			{
				aTargetArr.reserve(arr.size());
				for (size_t i = 0; i < arr.size(); i++)
				{
					aTargetArr.emplace_back(arr[i]);
				}
				return;
			}
		}
	}

	ESearchRefTargetSpace space = aParam.mSpace;  
	ESearchTargetRelation relation = aParam.mRelation; 
	ESearchTargetFilter filter = aParam.mFilter;
	int filterParam = aParam.mFilterParam;
	int restRefTargetNum = skillConf->basedata().reftargetnum();
	ENeedSummon needSummon = aParam.mNeedSummon;
	bool needDead = aParam.mNeedDead;
	bool excludeSelf = aParam.mExcludeSelf;
	aSkill->mNeedDead = needDead;
	bool usePrioritySearch = true;

	//Gen priority pools based on Pos Type and skill conf 
	bool skipDying = false; 
	int origRefTargetNum = restRefTargetNum; 
	BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
	vector<Unit*> allunits;  //pre-calculated units using relation filter only  
	vector<Unit*> dying;
	vector<Unit*> allbutdying;
	RefTarget rt;					//place holder
	vector<SharedPtr<Unit> > vs;    //place holder

	//apply relation filter here 
	switch (relation)
	{
	case ESearchTargetRelationEnemy:
	{
		const auto& arr1 = battleInstance.TargetArmy(*aUtilizer.Get()).GetUnitArr();
		allunits.reserve(arr1.size());
		allbutdying.reserve(arr1.size());
		for (auto& v : arr1)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	break;
	case ESearchTargetRelationFriend:
	{
		usePrioritySearch = false;
		skipDying = true;
		const auto& arr1 = aUtilizer->GetArmy().GetUnitArr();
		allunits.reserve(arr1.size());
		allbutdying.reserve(arr1.size());
		for (auto& v : arr1)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	break;
	case ESearchTargetRelationAll:
	{
		const auto& arr1 = battleInstance.GetArmy1().GetUnitArr();
		const auto& arr2 = battleInstance.GetArmy2().GetUnitArr();
		allunits.reserve(arr1.size() + arr2.size());
		allbutdying.reserve(arr1.size() + arr2.size());
		for (auto& v : arr1)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
		for (auto& v : arr2)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	}

	if (usePrioritySearch)
	{
		//根据unit状态（召唤，武将，是否死亡等） 
		GetUnitArrByHeroStatus(needSummon, needDead, allunits);

		//search ref target based on the priority of Position Type, ie front, middle and back
		SearchTargetUsingPriority(aUtilizer, aSkill, rt, filter, space,
			excludeSelf, filterParam, 0, restRefTargetNum, allunits, aTargetArr, vs, true);
	}
	else
	{
		//根据unit状态（召唤，武将，是否死亡等） 
		GetUnitArrByHeroStatus(needSummon, needDead, allbutdying);

		SearchRefTargetUnit(aUtilizer, aSkill, space, filter,
			excludeSelf, filterParam, 0, restRefTargetNum, allbutdying, aTargetArr);
		restRefTargetNum = origRefTargetNum - aTargetArr.size();
		if (!skipDying && dying.size() > 0 && restRefTargetNum > 0)
		{
			SearchRefTargetUnit(aUtilizer, aSkill, space, filter,
				excludeSelf, filterParam, 0, restRefTargetNum, dying, aTargetArr);
		}
	}

	RestoreVectorToPool<Unit*>(allunits);
	RestoreVectorToPool<Unit*>(dying);
	RestoreVectorToPool<Unit*>(allbutdying);
	RestoreVectorToPool<SharedPtr<Unit>>(vs);
	RestoreObjToPool(rt);
}


void SearchTargetUsingPriority(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, const RefTarget& aRefTarget,
	ESearchTargetFilter aFilter,
	ESearchRefTargetSpace aSpace,
	bool aExcludeSelf,
	int aFilterParam,
	int aFilterParam2,
	int aTargetNum,
	vector<Unit*>& aInputArr,
	vector<RefTarget>& aTargetArr,
	vector<SharedPtr<Unit> >& aTargetPtrArr,
	bool aIsRef)
{
	const SkillData* skillConf = aSkill->GetSkillConf();

	//Gen priority pools based on Pos Type and skill conf 
	int origTargetNum = aTargetNum;
	int restTargetNum = aTargetNum;
	BattleInstance& battleInstance = aUtilizer->GetBattleInstance();

	auto& typeList = aSkill->GetRerOrEffPosType(aIsRef);
	
	vector<EPosType> output;  //used to store the latest Pos Type that want to compute 
	vector<Unit*> allButDyings;  //pre-calculated units using relation filter only  
	vector<Unit*> dying;
	//apply relation filter here 
	allButDyings.reserve(aInputArr.size());
	for (auto& v : aInputArr)
	{
		if (v->IsDying())
			dying.push_back(v);
		else
			allButDyings.push_back(v);
	}

	vector<Unit*> unitArr;
	//search ref target based on the priority of Position Type,ie front, middle and back
	for (int idx = 0; restTargetNum > 0 && idx < typeList.size(); )
	{
		output.clear();
		while (typeList[idx] != EPosType::None)
		{
			output.emplace_back(typeList[idx]);
			++idx;
		}
		++idx;
		//gen pool of units, call SearchRefTargetUnit, then clean output
		unitArr.clear();
		for (auto unit : allButDyings)
		{
			for (auto type : output)
			{
				if (unit->mPosType == type)
				{
					unitArr.push_back(unit);
					break;
				}
			}
		}

		if (unitArr.size() > 0)
		{
			if (aIsRef)
			{
				SearchRefTargetUnit(aUtilizer, aSkill, aSpace, aFilter,
					aExcludeSelf, aFilterParam, aFilterParam2, restTargetNum, unitArr, aTargetArr);
				restTargetNum = origTargetNum - aTargetArr.size();
			}
			else
			{
				SearchEffTargetUnit(aUtilizer, aSkill, aRefTarget, aFilter,
					aExcludeSelf, aFilterParam, restTargetNum, unitArr, aTargetPtrArr);
				restTargetNum = origTargetNum - aTargetPtrArr.size();
			}
		}
		
		//output.clear();
	}

	if (restTargetNum > 0 && dying.size() > 0)
	{
		if (aIsRef)
			SearchRefTargetUnit(aUtilizer, aSkill, aSpace, aFilter,
				aExcludeSelf, aFilterParam, aFilterParam2, restTargetNum, dying, aTargetArr);
		else
			SearchEffTargetUnit(aUtilizer, aSkill, aRefTarget, aFilter,
				aExcludeSelf, aFilterParam, restTargetNum, dying, aTargetPtrArr);
	}

	//RestoreVectorToPool<EPosType>(output);
	RestoreVectorToPool<Unit*>(allButDyings);
	RestoreVectorToPool<Unit*>(dying);
	RestoreVectorToPool<Unit*>(unitArr);
}

void SearchRefTarget(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, vector<RefTarget>& aTargetArr)
{
    const SkillData* skillConf = aSkill->GetSkillConf();
	RestoreVectorElementToPool<RefTarget>(aTargetArr);
	aTargetArr.clear();
	if (skillConf->subskilldata().isfollow())  //keep the same targets as parent skill
	{
		if (!aSkill->IsChildSkill())
		{
			LOG_WARN("when SearchRefTarget Unable to follow target when current skill[%d] is not childskill", aSkill->GetId());
		}
		else
		{
			auto& arr = aSkill->GetParentSkill()->GetRefTargetArr();
			if (arr.size() > 0)
			{
				aTargetArr.reserve(arr.size());
				for (size_t i = 0; i < arr.size(); i++)
				{
					aTargetArr.emplace_back(arr[i]);
				}
				return;
			}
		}
	}
	BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
    ESearchRefTargetSpace space = ESearchRefTargetSpaceAll;  //spatial relation
    ESearchTargetRelation relation;							 //army relation 
    ESearchTargetFilter filter = ESearchTargetFilterNone;
    int filterParam = 0;									 //store filter attribute name
	int filterParam2 = 0;
    int restRefTargetNum = skillConf->basedata().reftargetnum();
	ENeedSummon needSummon = static_cast<ENeedSummon>(skillConf->basedata().reftargetsummontype());
    bool needDead = false;
	bool excludeSelf = false;
	bool usePrioritySearch = true;
	auto reftargettype = skillConf->basedata().reftargettype();
	ESearchRefTargetMethod type = static_cast<ESearchRefTargetMethod>(reftargettype);
    switch(type)
    {
        case ESearchRefTargetMethodRandEnemy: //随机敌方单位 
            relation = ESearchTargetRelationEnemy; 
            break;
        case ESearchRefTargetMethodRandFriend: //随机己方单位 
            relation = ESearchTargetRelationFriend;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
		case ESearchRefTargetMethodAnyFriendButSummon:  //随机己方英雄(召唤物除外) 
			relation = ESearchTargetRelationFriend;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
			needSummon = ENeedSummon::EOnlyHero;
			break;
        case ESearchRefTargetMethodAllEnemy: //敌方全体 
            relation = ESearchTargetRelationEnemy;
			restRefTargetNum = INT_MAX;
			usePrioritySearch = false;
            break;
        case ESearchRefTargetMethodAllFriend: //己方全体 
            relation = ESearchTargetRelationFriend;
			restRefTargetNum = INT_MAX;
			usePrioritySearch = false;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodSelf: //自己 
            {
                RefTarget target;
                target.SetUnit(aUtilizer);
                aTargetArr.emplace_back(target);
				RestoreObjToPool(target);
                return;
            }
            break;
        case ESearchRefTargetMethodNearestEnemy: //离自己最近的敌方 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterNearest;
            break;
        case ESearchRefTargetMethodNearestFriend: //离自己最近的友方 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterNearest;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFarthestEnemy: //离自己最远的敌方 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterFarthest;
            break;
        case ESearchRefTargetMethodFarthestFriend: //离自己最远的友方 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterFarthest;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodRangeRandEnemy: //技能范围内任意敌方 
            space = ESearchRefTargetSpaceSkillRange;
            relation = ESearchTargetRelationEnemy;            
            break;
        case ESearchRefTargetMethodRangeRandFriend: //技能范围内任意友方 
            space = ESearchRefTargetSpaceSkillRange;
            relation = ESearchTargetRelationFriend;          
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodRangeAllEnemy: //技能范围内所有敌方 
            space = ESearchRefTargetSpaceSkillRange;
            relation = ESearchTargetRelationEnemy;  
			restRefTargetNum = INT_MAX;
			usePrioritySearch = false;
            break;
        case ESearchRefTargetMethodRangeAllFriend: //技能范围内所有友方 
            space = ESearchRefTargetSpaceSkillRange;
            relation = ESearchTargetRelationFriend;  
			restRefTargetNum = INT_MAX;
			usePrioritySearch = false;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodEnemyMinHp: //敌方血量最少 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchRefTargetMethodEnemyMaxHp: //敌方血量最多 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchRefTargetMethodEnemyMaxLostHp: //敌方失血最多 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchRefTargetMethodEnemyMinLostHp: //敌方失血最少 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchRefTargetMethodEnemyMinRage: //敌方怒气最少 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchRefTargetMethodEnemyMaxRage: //敌方怒气最多 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchRefTargetMethodFriendMinHp: //己方血量最少 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameHp;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMaxHp: //己方血量最多 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameHp;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMaxLostHp: //己方失血最多 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMinLostHp: //己方失血最少 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMinRage: //己方怒气最少 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameRage;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMaxRage: //己方怒气最多 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameRage;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodRandFriendDead: //己方死亡目标 
            relation = ESearchTargetRelationFriend;
            needDead = true;
            break;
		case ESearchRefTargetMethodRandFriendHeroDead: //己方死亡英雄  
			relation = ESearchTargetRelationFriend;
			needSummon = EOnlyHero;
			needDead = true;
			break;
		case ESearchRefTargetMethodRandFriendSummonDead: //己方死亡召唤物 
			relation = ESearchTargetRelationFriend;
			needSummon = EOnlySummon;
			needDead = true;
			break;
        case ESearchRefTargetMethodRandEnemyDead: //敌方死亡目标 
            relation = ESearchTargetRelationEnemy;
            needDead = true;
            break;
		case ESearchRefTargetMethodRandEnemyHeroDead: //敌方死亡英雄 
			relation = ESearchTargetRelationEnemy;
			needSummon = EOnlyHero;
			needDead = true;
			break;
		case ESearchRefTargetMethodRandEnemySummonDead: //敌方死亡召唤物 
			relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
			needDead = true;
			break;
        case ESearchRefTargetMethodRandDead: //任意死亡目标 
            relation = ESearchTargetRelationAll;
            needDead = true;
			usePrioritySearch = false;
            break;
		case ESearchRefTargetMethodRandHeroDead: //任意死亡英雄 
			relation = ESearchTargetRelationAll;
			needSummon = EOnlyHero;
			needDead = true;
			usePrioritySearch = false;
			break;
		case ESearchRefTargetMethodRandSummonDead: //任意死亡召唤物 
			relation = ESearchTargetRelationAll;
			needSummon = EOnlySummon;
			needDead = true;
			usePrioritySearch = false;
			break;
        case ESearchRefTargetMethodRandEnemySummon: //随机敌方召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            break;
        case ESearchRefTargetMethodAllEnemySummon: //所有敌方召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
			restRefTargetNum = INT_MAX;
			usePrioritySearch = false;
            break;
		case ESearchRefTargetMethodAllFriendSummon: //所有己方召唤单位 
			relation = ESearchTargetRelationFriend;
			needSummon = EOnlySummon;
			restRefTargetNum = INT_MAX;
			usePrioritySearch = false;
			break;
        case ESearchRefTargetMethodNearestEnemySummon: //离自己最近敌方召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterNearest;
            break;
        case ESearchRefTargetMethodFarthestEnemySummon: //离自己最远敌方召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterFarthest;
            break;
        case ESearchRefTargetMethodRangeRandEnemySummon: //技能范围内任意敌方召唤单位 
            space = ESearchRefTargetSpaceSkillRange;
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            break;
        case ESearchRefTargetMethodRangeAllEnemySummon: //技能范围内全部敌方召唤单位 
            space = ESearchRefTargetSpaceSkillRange;
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
			restRefTargetNum = INT_MAX;
            break;
        case ESearchRefTargetMethodEnemySummonMinHp: //敌方血量最少召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchRefTargetMethodEnemySummonMaxHp: //敌方血量最多召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchRefTargetMethodEnemySummonMinLostHp: //敌方失血最少召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchRefTargetMethodEnemySummonMaxLostHp: //敌方失血最多召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchRefTargetMethodEnemySummonMaxRage: //敌方怒气最多召唤单位 
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchRefTargetMethodEnemySummonMinRage: //敌方怒气最少召唤单位     
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
		case ESearchRefTargetMethodEnemyMaxAtk:		//敌方攻击最高 
			relation = ESearchTargetRelationEnemy;
			filter = ESearchTargetFilterAttributeMax;
			filterParam = ESearchTargetFilterAttributeNameAtk;
			break;
		case ESearchRefTargetMethodFriendMaxAtk:		//己方攻击最高 
			relation = ESearchTargetRelationFriend;
			filter = ESearchTargetFilterAttributeMax;
			filterParam = ESearchTargetFilterAttributeNameAtk;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
			break;
        case ESearchRefTargetMethodFriendMaxPhysicalAtk: //己方物攻最高 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMaxMagicAtk: //己方法攻最高 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMaxPhysicalDef: //己方物防最高 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMaxMagicDef: //己方法防最高 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMinPhysicalAtk: //己方物攻最低 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMinMagicAtk: //己方法攻最低 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMinPhysicalDef: //己方物防最低 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodFriendMinMagicDef: //己方法防最低 
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
        case ESearchRefTargetMethodEnemyMaxPhysicalAtk: //敌方物攻最高 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
            break;
        case ESearchRefTargetMethodEnemyMaxMagicAtk: //敌方法攻最高 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
            break;
        case ESearchRefTargetMethodEnemyMaxPhysicalDef: //敌方物防最高 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
            break;
        case ESearchRefTargetMethodEnemyMaxMagicDef: //敌方法防最高 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
            break;
        case ESearchRefTargetMethodEnemyMinPhysicalAtk: //敌方物攻最低 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
            break;
        case ESearchRefTargetMethodEnemyMinMagicAtk: //敌方法攻最低 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
            break;
        case ESearchRefTargetMethodEnemyMinPhysicalDef: //敌方物防最低 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
            break;
        case ESearchRefTargetMethodEnemyMinMagicDef: //敌方法防最低 
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
            break;
        case ESearchRefTargetMethodForwardFixPos: //自己身前一定距离位置 
            {
                RefTarget target;
                Vector3 pos = aUtilizer->GetForward();
                pos.ScaleToLen( CONF_POS_CONVERT( skillConf->basedata().frontdistance()));
                pos += aUtilizer->GetPosition();
                target.SetPos(pos);
                aTargetArr.emplace_back(target);
				RestoreObjToPool(target);
                return;
            }
            break;
        case ESearchRefTargetMethodFixPos: //场景坐标点 
			{
				auto& army = aUtilizer->GetArmy();
				Vector3 pos = Vector3(0, 0, 0);
				Vector3 rot = Vector3(0, 0, 0);
				army.GetCenterPoint(pos, rot);
				RefTarget target;
				int ct = 2;
				for (auto pos2D : skillConf->basedata().scenepos())
				{
					if (ct == 0)
					{
						break;
					}
					else if (ct == 2)
					{
						pos.x = static_cast<int64>(CONF_POS_CONVERT(pos2D));
					}
					else if (ct == 1)
					{
						pos.z = static_cast<int64>(CONF_POS_CONVERT(pos2D));
					}
					ct--;
				}
				target.SetPos(pos); //will set Type to Pos as well
				target.SetRot(rot);
				aTargetArr.emplace_back(target);
				RestoreObjToPool(target);
				return;
			}
			break;
		case ESearchRefTargetMethodFriendScenePos:  //己方场景坐标点 
			{
				for (int posIdx : skillConf->basedata().sceneposindex())
				{
					RefTarget target;
					const DirectedPosition& scenePos = aUtilizer->GetArmy().GetSummonPointByIndex(posIdx);
					if (&scenePos == &BattleInstance::mDefaultDirectedPosition)
					{
						Vector3 pos;
						Vector3 rot;
						GetScenePosTD(aUtilizer.Get(), posIdx, pos, rot);
						target.SetPos(pos);
						target.SetRot(rot);
					}
					else
					{
						target.SetPos(scenePos.mPos);
						target.SetRot(scenePos.mRot);
					}
					aTargetArr.emplace_back(target);
					RestoreObjToPool(target);
				}
				return;
			}
			break;
		case ESearchRefTargetMethodEnemyScenePos:  //敌方场景坐标点 
		{
			const Army& enemyArmy = battleInstance.TargetArmy(*aUtilizer.Get());
			for (int posIdx : skillConf->basedata().sceneposindex())
			{
				RefTarget target;
				const DirectedPosition& scenePos = enemyArmy.GetSummonPointByIndex(posIdx); 
				if (&scenePos == &BattleInstance::mDefaultDirectedPosition)
				{
					Vector3 pos;
					Vector3 rot;
					GetScenePosTD(aUtilizer.Get(), posIdx, pos, rot);
					target.SetPos(pos);
					target.SetRot(rot);
				}
				else
				{
					target.SetPos(scenePos.mPos);
					target.SetRot(scenePos.mRot);
				}
				aTargetArr.emplace_back(target);
				RestoreObjToPool(target);
			}
			return;
		}
		break;
        case ESearchRefTargetMethodLastNormalSkillTarget: //上次普攻的参考目标 
			if (aUtilizer->GetLastNormalSkillTarget())
			{
				auto unit = aUtilizer->GetLastNormalSkillTarget();
				if (unit->IsDead() == needDead && unit->CanBeRefTargetOfUtilizer(aUtilizer.Get(), aSkill.Get()))
				{
					RefTarget target;
					target.SetUnit(unit);
					aTargetArr.emplace_back(target);
					RestoreObjToPool(target);
					return;
				}
			}
			relation = ESearchTargetRelationEnemy;
			filter = ESearchTargetFilterNearest;
            break;
		case ESearchRefTargetMethodChoosedAtTriggerTime:
			if (aSkill->mTriggerRegister2 > 0)
			{
				auto unit = aUtilizer->GetBattleInstance().GetUnitByEntityId(int(aSkill->mTriggerRegister2));
				if (unit && unit->IsDead() == needDead && unit->CanBeRefTargetOfUtilizer(aUtilizer.Get(), aSkill.Get()))
				{
					RefTarget target;
					target.SetUnit(unit);
					aTargetArr.emplace_back(target);
					RestoreObjToPool(target);
					return;
				}
			}
			return;
        case ESearchRefTargetMethodEnemyBuff: //带特定buff的敌方目标 
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterBuff;
            filterParam = skillConf->basedata().spebuffid();
			filterParam2 = skillConf->basedata().spebuffidback();
            break;
        case ESearchRefTargetMethodFriendBuff: //带特定buff的己方目标 
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterBuff;
            filterParam = skillConf->basedata().spebuffid();
			filterParam2 = skillConf->basedata().spebuffidback();
			excludeSelf = !skillConf->basedata().reftargetincludeself();
            break;
		case ESearchRefTargetMethodMostEffTarget:	 //可产生最多生效目标的参考目标(矩形) 
			relation = ESearchTargetRelationEnemy;
			space = ESearchRefTargetSpaceSkillRange;
			filter = ESearchTargetFilterMostInclude;
			filterParam = CONF_POS_CONVERT(skillConf->effectdata().effectparam2());
			if (filterParam == 0) filterParam = CONF_POS_CONVERT(200);
			break;
		case ESearchRefTargetMethodMostEffTargetCircle:	 //可产生最多生效目标的参考目标(圆形) 
			relation = ESearchTargetRelationEnemy;
			space = ESearchRefTargetSpaceSkillRange;
			filter = ESearchTargetFilterMostIncludeCircle;
			filterParam = CONF_POS_CONVERT(skillConf->effectdata().effectparam1());
			if (filterParam == 0) filterParam = CONF_POS_CONVERT(200);
			break;
		case ESearchRefTargetMethodEnemyProfessionalConbime: //敌方某些职业组合 
			{
				auto& professions = skillConf->basedata().targetprofessions();
				const auto& enemy = battleInstance.TargetArmy(*aUtilizer.Get());
				for (int pid : professions)
				{
					const auto heros = enemy.GetUnitByProfession(pid, false);
					for (auto unit : heros)
					{
						RefTarget target;
						target.SetUnit(unit);
						aTargetArr.emplace_back(target);
						RestoreObjToPool(target);
					}
				}
				return;
			}
			break;
		case ESearchRefTargetMethodFriendProfessionalConbime: //己方某些职业组合 
			{
				auto& professions = skillConf->basedata().targetprofessions();
				const auto& army = aUtilizer->GetArmy();
				for (int pid : professions)
				{
					const auto heros = army.GetUnitByProfession(pid, false);
					for (auto unit : heros)
					{
						RefTarget target;
						target.SetUnit(unit);
						aTargetArr.emplace_back(target);
						RestoreObjToPool(target);
					}
				}
				return;
			}
			break;
		case ESearchRefTargetMethodMaxAtkNotOnly:		//敌方攻击最高且非唯一 
			relation = ESearchTargetRelationEnemy;
			filter = ESearchTargetFilterAttributeMax;
			filterParam = ESearchTargetFilterAttributeNameAtk;
			{
				const auto& arr1 = battleInstance.TargetArmy(*aUtilizer.Get()).GetActiveUnitArr();
				int ct = 0;
				for (auto& u : arr1)
				{
					if (!u->IsDummy() && !u->IsDying())
					{
						ct++;
					}
				}
				if (ct <= 1)
				{
					return;
				}
			}
			break;
        default:
            LOG_FATAL("invalid searchEffTargetMethod:%d, skill:%d", skillConf->effectdata().effecttarget(), skillConf->id());
    }
	aSkill->mNeedDead = needDead;

	//Gen priority pools based on Pos Type and skill conf 
	bool skipDying = false;
	int origRefTargetNum = restRefTargetNum;
	vector<Unit*> allunits;			//pre-calculated units using relation filter only  
	vector<Unit*> rangeUnits;
	vector<Unit*> dying;
	vector<Unit*> allbutdying;
	RefTarget rt;					//place holder
	vector<SharedPtr<Unit> > vs;    //place holder
	//apply relation filter here 
	switch (relation) 
	{ 
	case ESearchTargetRelationEnemy: 
	{
		const auto& arr1 = battleInstance.TargetArmy(*aUtilizer.Get()).GetUnitArr(); 
		allunits.reserve(arr1.size());
		allbutdying.reserve(arr1.size());
		for (auto& v : arr1)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
			{
				allbutdying.push_back(v.Get());
			}
		}
	}
	break;
	case ESearchTargetRelationFriend:
	{
		const auto& arr1 = aUtilizer->GetArmy().GetUnitArr();
		allunits.reserve(arr1.size());
		allbutdying.reserve(arr1.size());
		for (auto& v : arr1)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	break;
	case ESearchTargetRelationAll:
	{
		const auto& arr1 = battleInstance.GetArmy1().GetUnitArr();
		const auto& arr2 = battleInstance.GetArmy2().GetUnitArr();
		allunits.reserve(arr1.size() + arr2.size());
		allbutdying.reserve(arr1.size() + arr2.size());
		for (auto& v : arr1)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
		for (auto& v : arr2)
		{
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	}

	usePrioritySearch = false;
	skipDying = true;
	//TODO: 简化考虑优先级 

	if (!allunits.empty())
	{
		if (usePrioritySearch)
		{
			//根据unit状态（召唤，武将，是否死亡等） 
			GetUnitArrByHeroStatus(needSummon, needDead, allunits);

			if (restRefTargetNum < 2)
			{
				rangeUnits.reserve(allunits.size());
				FilterByCastRange(allunits, rangeUnits, aUtilizer, aSkill->GetCastRange());
			}

			if (rangeUnits.size() > 0)
			{
				//search ref target based on the priority of Position Type, ie front, middle and back
				SearchTargetUsingPriority(aUtilizer, aSkill, rt, filter, space,
					excludeSelf, filterParam, filterParam2, restRefTargetNum, rangeUnits, aTargetArr, vs, true);
			}
			if (aTargetArr.size() == 0)
			{ //allunits -> all units but those in cast range
				SearchTargetUsingPriority(aUtilizer, aSkill, rt, filter, space,
					excludeSelf, filterParam, filterParam2, restRefTargetNum, allunits, aTargetArr, vs, true);
			}
		}
		else
		{
			//根据unit状态（召唤，武将，是否死亡等） 
			GetUnitArrByHeroStatus(needSummon, needDead, allbutdying);

			SearchRefTargetUnit(aUtilizer, aSkill, space, filter,
				excludeSelf, filterParam, filterParam2, restRefTargetNum, allbutdying, aTargetArr);
			restRefTargetNum = origRefTargetNum - aTargetArr.size();
			if (!skipDying && dying.size() > 0 && restRefTargetNum > 0)
			{
				SearchRefTargetUnit(aUtilizer, aSkill, space, filter,
					excludeSelf, filterParam, filterParam2, restRefTargetNum, dying, aTargetArr);
			}
		}
	}
	
	RestoreVectorToPool<Unit*>(allunits);
	RestoreVectorToPool<Unit*>(rangeUnits);
	RestoreVectorToPool<Unit*>(dying);
	RestoreVectorToPool<Unit*>(allbutdying);
	RestoreVectorToPool<SharedPtr<Unit>>(vs);
	RestoreObjToPool(rt);
}



void SearchEffTargetUnit(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, const RefTarget& aRefTarget,
        ESearchTargetFilter aFilter,
		bool aExcludeSelf,
        int aFilterParam,
        int aEffTargetNum,
		vector<Unit*>& aInputArr,
        vector<SharedPtr<Unit>>& aTargetArr)
{
	
    const SkillData* skillConf = aSkill->GetSkillConf();
    const SkillEffectData& skillEffectConf = skillConf->effectdata();
	int skillLevel = aSkill->GetLevel();  //技能等级 

	Unit* effectedRefTarget = nullptr;

    if( skillEffectConf.effecttype() == ESearchEffTargetRegionSingle )
    {
        //理论应该已经选择了参考目标是生效目标，不应该走到这里。做个检查吧
        //LOG_WARN("skill:%d effecttype is single, but not set isrealtarget", skillConf->id());
        return;   
    }

	Unit* excludeSelfPtr = nullptr;
	if (aExcludeSelf)
	{
		excludeSelfPtr = aUtilizer.Get();
	}
    size_t num = aInputArr.size();
    //考虑unit本身的特殊修正状态 
    for(size_t i = 0; i < num;)
    {
        if(aInputArr[i]->CanBeEffTargetOfUtilizer(aUtilizer.Get(), aSkill.Get())
			&& aInputArr[i] != effectedRefTarget
			&& aInputArr[i] != excludeSelfPtr)
        {
            i++;
        }
        else
        {        
            num--;
			aInputArr[i] = aInputArr[num];
        }
    }
	aInputArr.resize(num);

    //根据生效范围过滤 
	BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
    aTargetArr.reserve(aTargetArr.size() + aInputArr.size());
    const Vector3* center;
    if(skillEffectConf.origintype() > 0)
    {
        center = &aRefTarget.GetTargetPos();
    }
    else
    {
        center = &aUtilizer->GetPosition();
    }
    switch(skillEffectConf.effecttype())
    {
		case ESearchEffTargetRegionCounterpart:
		{
			FilterToGetCounterpart(aInputArr, center, aUtilizer->GetSize(), aFilterParam, CONF_POS_CONVERT(skillEffectConf.effectparam1()));
			break;
		}
        case ESearchEffTargetRegionCircle:
        {
            RegionCircle circle;
            circle.center.x = center->x;
            circle.center.z = center->z;
            circle.radius = CONF_POS_CONVERT( skillEffectConf.effectparam1() + (skillLevel - 1) * skillEffectConf.levelrangegrowth());
			circle.selfSize = aUtilizer->GetSize();
            FilterByRegion(aInputArr, &circle);
            //battleInstance.CheckDestructable(&circle, aUtilizer.Get(), aSkill.Get());
            break;
        }            
        case ESearchEffTargetRegionSector:
        {
            RegionSector sector;
            sector.center.x = center->x;
            sector.center.z = center->z;
            sector.forward.x = aRefTarget.GetTargetPos().x - aUtilizer->GetPosition().x;
            sector.forward.z = aRefTarget.GetTargetPos().z - aUtilizer->GetPosition().z;
			if (sector.forward.x == 0 && sector.forward.z == 0)
			{
				sector.forward.x = aUtilizer->GetForward().x;
				sector.forward.z = aUtilizer->GetForward().z;
			}
            sector.radius = CONF_POS_CONVERT( skillEffectConf.effectparam1() + (skillLevel - 1) * skillEffectConf.levelrangegrowth());
            sector.angle = skillEffectConf.effectparam2();
			sector.selfSize = aUtilizer->GetSize();
            FilterByRegion(aInputArr, &sector);
            //battleInstance.CheckDestructable(&sector, aUtilizer.Get(), aSkill.Get());
            break;
        }
        case ESearchEffTargetRegionAnnulus:
        {
            RegionAnnulus annulus;
            annulus.center.x = center->x;
            annulus.center.z = center->z;
            annulus.radius1 = CONF_POS_CONVERT( skillEffectConf.effectparam1() );
            annulus.radius2 = CONF_POS_CONVERT( skillEffectConf.effectparam2() + (skillLevel - 1) * skillEffectConf.levelrangegrowth());
			annulus.selfSize = aUtilizer->GetSize();
            FilterByRegion(aInputArr, &annulus);
            //battleInstance.CheckDestructable(&annulus, aUtilizer.Get(), aSkill.Get());
            break;
        }
        case ESearchEffTargetRegionRectangle:
        {
            RegionRectangle rectangle;
            rectangle.center.x = center->x;
            rectangle.center.z = center->z;
            rectangle.halfSize.z = CONF_POS_CONVERT( skillEffectConf.effectparam1() + (skillLevel - 1) * skillEffectConf.levelrangegrowth()) / 2;
            rectangle.halfSize.x = CONF_POS_CONVERT( skillEffectConf.effectparam2() + (skillLevel - 1) * skillEffectConf.levelrangegrowth()) / 2;
            rectangle.forward.x = aRefTarget.GetTargetPos().x - aUtilizer->GetPosition().x;
            rectangle.forward.z = aRefTarget.GetTargetPos().z - aUtilizer->GetPosition().z;
			if (rectangle.forward.x == 0 && rectangle.forward.z == 0)
			{
				rectangle.forward.x = aUtilizer->GetForward().x;
				rectangle.forward.z = aUtilizer->GetForward().z;
			}
            Vector2 forward = rectangle.forward;
            forward.ScaleToLen(rectangle.halfSize.z);
            rectangle.center += forward;
			rectangle.selfSize = aUtilizer->GetSize();
            FilterByRegion(aInputArr, &rectangle);
            //battleInstance.CheckDestructable(&rectangle, aUtilizer.Get(), aSkill.Get());
            break;
        }
    }
   
    //考虑过滤器
    switch(aFilter)
    {
        case ESearchTargetFilterNone:
            break;
        case ESearchTargetFilterNearest:
            FilterByDist(aUtilizer, aEffTargetNum, 1, aInputArr);
            break;
        case ESearchTargetFilterFarthest:
            FilterByDist(aUtilizer, aEffTargetNum, -1, aInputArr);
            break;
        case ESearchTargetFilterAttributeMin:
            FilterByAttribute( aFilterParam, aEffTargetNum, 1, aInputArr);
            break;
        case ESearchTargetFilterAttributeMax:
            FilterByAttribute( aFilterParam, aEffTargetNum, -1, aInputArr);
            break;
        case ESearchTargetFilterBuff:
            FilterByBuff( aUtilizer, aFilterParam, 0, aInputArr);
            break;
        default:
            LOG_FATAL("invalid filter:%d. skill:%d", aFilter, skillConf->id());
    }

	//random filter 
	if (aInputArr.size() > aEffTargetNum)
	{
		RandInRange(aUtilizer->GetBattleInstance(), aInputArr, 0, aInputArr.size() - 1, aEffTargetNum);
		aInputArr.resize(aEffTargetNum);
	}

	int originSize = aTargetArr.size();
	aTargetArr.reserve(originSize + aInputArr.size());
	for (size_t i = 0; i < aInputArr.size(); i++)
	{
		aTargetArr.emplace_back(aInputArr[i]->SharedFromThis());
	}

}

void SearchEffTarget(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, const RefTarget& aRefTarget, vector<SharedPtr<Unit> >& aTargetArr)
{
    const SkillData* skillConf = aSkill->GetSkillConf(); 
	aTargetArr.clear();
	if (skillConf->subskilldata().isfollowrealtarget())
	{
		if (!aSkill->IsChildSkill())
		{
			LOG_WARN("when SearchEffTarget Unable to follow real target when current skill[%d] is not childskill", aSkill->GetId());
		}
		else
		{
			const auto& arr = aSkill->GetParentSkill()->GetEffTargetArr();
			if (arr.size() > 0)
			{
				aTargetArr.reserve(arr.size());
				for (auto& v : arr)
				{
					aTargetArr.emplace_back(v);
				}
				return;
			}
		}
	}

    ESearchTargetRelation relation;
    ESearchTargetFilter filter = ESearchTargetFilterNone;
    int filterParam = 0;
    int restEffTargetNum = skillConf->effectdata().targetnum();
    ENeedSummon needSummon = ESummonAndHero;
    bool needDead = false;
	bool excludeSelf = false;
	bool usePrioritySearch = true;

	auto effecttarget = skillConf->effectdata().effecttarget();
	ESearchEffTargetMethod type = static_cast<ESearchEffTargetMethod>(effecttarget);
    switch(type)
    {
        case ESearchEffTargetMethodRandEnemy: //随机敌方单位
            relation = ESearchTargetRelationEnemy; 
            break;
        case ESearchEffTargetMethodRandFriend: //随机己方单位
            relation = ESearchTargetRelationFriend;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
		case ESearchEffTargetMethodAnyFriendButSummon: //随机己方单位(召唤物除外) 
			relation = ESearchTargetRelationFriend;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
			needSummon = ENeedSummon::EOnlyHero;
			break;
        case ESearchEffTargetMethodAllEnemy: //敌方全体
            relation = ESearchTargetRelationEnemy;
			restEffTargetNum = INT_MAX;
			usePrioritySearch = false;
            break;
        case ESearchEffTargetMethodAllFriend: //己方全体
            relation = ESearchTargetRelationFriend;
			restEffTargetNum = INT_MAX;
			usePrioritySearch = false;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodNone: //无目标_通常应用于全屏技能
            LOG_FATAL("not support ESearchEffTargetMethodNone");
            break;
        case ESearchEffTargetMethodSelf: //自己
            {
                aTargetArr.emplace_back(aUtilizer);
                return;
            }
        case ESearchEffTargetMethodNearestEnemy: //离自己最近的敌方
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterNearest;
            break;
        case ESearchEffTargetMethodNearestFriend: //离自己最近的友方
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterNearest;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodFarthestEnemy: //离自己最远的敌方
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterFarthest;
            break;
        case ESearchEffTargetMethodFarthestFriend: //离自己最远的友方
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterFarthest;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodEnemyMinHp: //敌方血量最少
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchEffTargetMethodEnemyMaxHp: //敌方血量最多
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchEffTargetMethodEnemyMaxLostHp: //敌方失血最多
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchEffTargetMethodEnemyMinLostHp: //敌方失血最少
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchEffTargetMethodEnemyMinRage: //敌方怒气最少
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchEffTargetMethodEnemyMaxRage: //敌方怒气最多
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchEffTargetMethodFriendMinHp: //己方血量最少
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameHp;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodFriendMaxHp: //己方血量最多
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameHp;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodFriendMaxLostHp: //己方失血最多
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodFriendMinLostHp: //己方失血最少
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodFriendMinRage: //己方怒气最少
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameRage;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodFriendMaxRage: //己方怒气最多
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameRage;
			excludeSelf = !skillConf->effectdata().effecttargetincludeself();
            break;
        case ESearchEffTargetMethodRandFriendDead: //己方死亡目标
            relation = ESearchTargetRelationFriend;
            needDead = true;
            break;
		case ESearchEffTargetMethodRandFriendHeroDead: //己方死亡英雄  
			relation = ESearchTargetRelationFriend;
			needSummon = EOnlyHero;
			needDead = true;
			break;
		case ESearchEffTargetMethodRandFriendSummonDead: //己方死亡召唤物 
			relation = ESearchTargetRelationFriend;
			needSummon = EOnlySummon;
			needDead = true;
			break;
        case ESearchEffTargetMethodRandEnemyDead: //敌方死亡目标
            relation = ESearchTargetRelationEnemy;
            needDead = true;
            break;
		case ESearchEffTargetMethodRandEnemyHeroDead: //敌方死亡英雄 
			relation = ESearchTargetRelationEnemy;
			needSummon = EOnlyHero;
			needDead = true;
			break;
		case ESearchEffTargetMethodRandEnemySummonDead: //敌方死亡召唤物 
			relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
			needDead = true;
			break;
        case ESearchEffTargetMethodRandDead: //任意死亡目标
            relation = ESearchTargetRelationAll;
            needDead = true;
			usePrioritySearch = false;
            break;
		case ESearchEffTargetMethodRandHeroDead: //任意死亡英雄 
			relation = ESearchTargetRelationAll;
			needSummon = EOnlyHero;
			needDead = true;
			usePrioritySearch = false;
			break;
		case ESearchEffTargetMethodRandSummonDead: //任意死亡召唤物 
			relation = ESearchTargetRelationAll;
			needSummon = EOnlySummon;
			needDead = true;
			usePrioritySearch = false;
			break;
        case ESearchEffTargetMethodRandEnemySummon: //随机敌方召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            break;
        case ESearchEffTargetMethodAllEnemySummon: //所有敌方召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
			restEffTargetNum = INT_MAX;
			usePrioritySearch = false;
            break;
		case ESearchEffTargetMethodAllFriendSummon: //所有己方召唤单位 
			relation = ESearchTargetRelationFriend;
			needSummon = EOnlySummon;
			restEffTargetNum = INT_MAX;
			usePrioritySearch = false;
			break;
        case ESearchEffTargetMethodNearestEnemySummon: //离自己最近敌方召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterNearest;
            break;
        case ESearchEffTargetMethodFarthestEnemySummon: //离自己最远敌方召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterFarthest;
            break;
        case ESearchEffTargetMethodEnemySummonMinHp: //敌方血量最少召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchEffTargetMethodEnemySummonMaxHp: //敌方血量最多召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameHp;
            break;
        case ESearchEffTargetMethodEnemySummonMinLostHp: //敌方失血最少召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchEffTargetMethodEnemySummonMaxLostHp: //敌方失血最多召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameLostHp;
            break;
        case ESearchEffTargetMethodEnemySummonMaxRage: //敌方怒气最多召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchEffTargetMethodEnemySummonMinRage: //敌方怒气最少召唤单位
            relation = ESearchTargetRelationEnemy;
			needSummon = EOnlySummon;
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameRage;
            break;
        case ESearchEffTargetMethodFriendMaxPhysicalAtk: //己方物攻最高
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
            break;
        case ESearchEffTargetMethodFriendMaxMagicAtk: //己方法攻最高
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
            break;
        case ESearchEffTargetMethodFriendMaxPhysicalDef: //己方物防最高
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
            break;
        case ESearchEffTargetMethodFriendMaxMagicDef: //己方法防最高
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
            break;
        case ESearchEffTargetMethodFriendMinPhysicalAtk: //己方物攻最低
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
            break;
        case ESearchEffTargetMethodFriendMinMagicAtk: //己方法攻最低
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
            break;
        case ESearchEffTargetMethodFriendMinPhysicalDef: //己方物防最低
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
            break;
        case ESearchEffTargetMethodFriendMinMagicDef: //己方法防最低
            relation = ESearchTargetRelationFriend;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
            break;
        case ESearchEffTargetMethodEnemyMaxPhysicalAtk: //敌方物攻最高
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
            break;
        case ESearchEffTargetMethodEnemyMaxMagicAtk: //敌方法攻最高
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
            break;
        case ESearchEffTargetMethodEnemyMaxPhysicalDef: //敌方物防最高
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
            break;
        case ESearchEffTargetMethodEnemyMaxMagicDef: //敌方法防最高
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMax;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
            break;
        case ESearchEffTargetMethodEnemyMinPhysicalAtk: //敌方物攻最低
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalAtk;
            break;
        case ESearchEffTargetMethodEnemyMinMagicAtk: //敌方法攻最低
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicAtk;
            break;
        case ESearchEffTargetMethodEnemyMinPhysicalDef: //敌方物防最低
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNamePhysicalDef;
            break;
        case ESearchEffTargetMethodEnemyMinMagicDef: //敌方法防最低
            relation = ESearchTargetRelationEnemy;            
            filter = ESearchTargetFilterAttributeMin;
            filterParam = ESearchTargetFilterAttributeNameMagicDef;
            break;
        case ESearchEffTargetMethodEnemyBuff: //带特定buff的敌方目标
            relation = ESearchTargetRelationEnemy;
            filter = ESearchTargetFilterBuff;
            filterParam = skillConf->effectdata().spebuffid();
            break;
        case ESearchEffTargetMethodFriendBuff: //带特定buff的己方目标
            relation = ESearchTargetRelationFriend;
            filter = ESearchTargetFilterBuff;
            filterParam = skillConf->effectdata().spebuffid();
            break;
		case ESearchEffTargetMethodCounterpart: //对位敌方目标 
			relation = ESearchTargetRelationEnemy;
			filterParam = CONF_POS_CONVERT(skillConf->basedata().castrange());
			restEffTargetNum = 1;
			break;
        default:
            LOG_FATAL("invalid searchEffTargetMethod:%d, skill:%d", skillConf->effectdata().effecttarget(), skillConf->id());
    }
	
	int origEffTargetNum = restEffTargetNum;
	// consider the situation that effTar == refTar 
	if (skillConf->basedata().isrealtarget()) 
	{
		if (aRefTarget.GetType() == ERefTargetType::Invalid)
		{
			LOG_FATAL("refTarget is not unit. no effTarget will be return. skill:%d", skillConf->id());
		}
		if (aRefTarget.GetType() == ERefTargetType::Pos)
		{
			//Turn a Position into a dummy Unit, keep this unit as light as possible
			const auto& dummy = aUtilizer->GetArmy().GetDummy();
			Vector3 dir = aRefTarget.GetTargetRot();
			if (dir.x == 0 && dir.z == 0)
			{
				dir = aUtilizer->GetForward();
			}
			dummy->SetPosRot(aRefTarget.GetTargetPos(), dir, false);
			aTargetArr.emplace_back(dummy);
			RestoreObjToPool(dir);
			return;
		}
		Unit* effectedRefTarget = aRefTarget.GetUnit().Get();
		if (needDead == effectedRefTarget->IsDead() && effectedRefTarget->CanBeEffTargetOfUtilizer(aUtilizer.Get(), aSkill.Get()))
		{
			aTargetArr.emplace_back(aRefTarget.GetUnit());
		}
		if (aTargetArr.size() == 0 && restEffTargetNum == 1)
		{
			return;  //参考目标也是生效目标，且生效目标数=1，那么处于其他原因，当参考目标不能成为生效目标时，就认为找不到生效目标了 
		}
	}
	if (aTargetArr.size() >= restEffTargetNum)
	{
		return;
	}
	
	bool skipDying = false;
	restEffTargetNum -= aTargetArr.size();
	BattleInstance& battleInstance = aUtilizer->GetBattleInstance();
	vector<Unit*> allunits;  //pre-calculated units using relation filter only  
	vector<Unit*> dying;
	vector<Unit*> allbutdying;
	Unit* excludeRefTarget = nullptr;

	vector<RefTarget> rt;										//place holder
	ESearchRefTargetSpace space = ESearchRefTargetSpaceAll;		//place holder

	if ((!skillConf->basedata().isrealtarget() && aRefTarget.GetType() == ERefTargetType::Unit)
		|| (skillConf->basedata().isrealtarget() && aTargetArr.size() > 0))
	{ 
		excludeRefTarget = aRefTarget.GetUnit().Get();
	}
	//apply relation filter here 
	switch (relation)
	{
	case ESearchTargetRelationEnemy:
	{
		const auto& arr1 = battleInstance.TargetArmy(*aUtilizer.Get()).GetUnitArr();
		allunits.reserve(arr1.size());
		allbutdying.reserve(arr1.size());
		bool hasFlyUnit = false;
		for (auto& v : arr1)
		{
			if (excludeRefTarget == v.Get() || v->IsDummy()) continue;
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
			{
				allbutdying.push_back(v.Get());
				//if (v->mTDFlyable) hasFlyUnit = true;
			}
		}
		if (hasFlyUnit)
		{
			//FilterByTDType(allbutdying, aUtilizer->mTDCanAtkFlyUnit);
		}
	}
	break;
	case ESearchTargetRelationFriend:
	{
		usePrioritySearch = false;
		skipDying = true;
		const auto& arr1 = aUtilizer->GetArmy().GetUnitArr();
		allunits.reserve(arr1.size());
		allbutdying.reserve(arr1.size());
		for (auto& v : arr1)
		{
			if (excludeRefTarget == v.Get() || v->IsDummy()) continue;
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	break;
	case ESearchTargetRelationAll:
	{
		const auto& arr1 = battleInstance.GetArmy1().GetUnitArr();
		const auto& arr2 = battleInstance.GetArmy2().GetUnitArr();
		allunits.reserve(arr1.size() + arr2.size());
		allbutdying.reserve(arr1.size() + arr2.size());
		for (auto& v : arr1)
		{
			if (excludeRefTarget == v.Get() || v->IsDummy()) continue;
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
		for (auto& v : arr2)
		{
			if (excludeRefTarget == v.Get() || v->IsDummy()) continue;
			allunits.push_back(v.Get());
			if (v->IsDying())
				dying.push_back(v.Get());
			else
				allbutdying.push_back(v.Get());
		}
	}
	}

	if (usePrioritySearch)
	{
		//根据unit状态（召唤，武将，是否死亡等） 
		GetUnitArrByHeroStatus(needSummon, needDead, allunits);

		//search ref target based on the priority of Position Type, ie front, middle and back
		SearchTargetUsingPriority(aUtilizer, aSkill, aRefTarget, filter, space,
			excludeSelf, filterParam, 0, restEffTargetNum, allunits, rt, aTargetArr, false);
	}
	else
	{
		//根据unit状态（召唤，武将，是否死亡等） 
		GetUnitArrByHeroStatus(needSummon, needDead, allbutdying);

		SearchEffTargetUnit(aUtilizer, aSkill, aRefTarget, filter,
			excludeSelf, filterParam, restEffTargetNum, allbutdying, aTargetArr);
		restEffTargetNum = origEffTargetNum - aTargetArr.size();
		if (!skipDying && dying.size() > 0 && restEffTargetNum > 0)
		{
			SearchEffTargetUnit(aUtilizer, aSkill, aRefTarget, filter,
				excludeSelf, filterParam, restEffTargetNum, dying, aTargetArr);
		}
	}

	RestoreVectorToPool(allunits);
	RestoreVectorToPool(dying);
	RestoreVectorToPool(allbutdying);
	RestoreVectorToPool(rt);
}

