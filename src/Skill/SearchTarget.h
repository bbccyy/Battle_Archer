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

#include "Define.h"
#include "Framework/SharedPool.h"
#include "Skill/SkillDefine.h"
#include "Skill/RefTarget.h"
#include <vector>
using namespace std;

class Unit;
class Skill;

struct RefTargetParam 
{
	ESearchRefTargetSpace mSpace = ESearchRefTargetSpace::ESearchRefTargetSpaceAll;
	ESearchTargetRelation mRelation = ESearchTargetRelation::ESearchTargetRelationAll;
	ESearchTargetFilter mFilter = ESearchTargetFilter::ESearchTargetFilterNone;
	ENeedSummon mNeedSummon = ENeedSummon::EOnlySummon;
	bool mNeedDead = false;
	bool mExcludeSelf = false;
	int mFilterParam = 0;
};

void SearchRefTargetUnit(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, 
        ESearchRefTargetSpace aSpace, 
        ESearchTargetFilter aFilter,
		bool aExcludeSelf,
        int aFilterParam,
		int aFilterParam2,
        int aRefTargetNum,
		vector<Unit*>& aInputArr,
        vector<RefTarget>& aTargetArr);

void SearchEffTargetUnit(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, const RefTarget& aRefTarget,
	ESearchTargetFilter aFilter,
	bool aExcludeSelf,
	int aFilterParam,
	int aEffTargetNum,
	vector<Unit*>& aInputArr,
	vector<SharedPtr<Unit> >& aTargetArr);

void SearchTargetUsingPriority(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, const RefTarget& aRefTarget,
	ESearchTargetFilter aFilter,
	ESearchRefTargetSpace aSpace,
	bool aExcludeSelf,
	int aFilterParam,
	int aFilterParam2,
	int aRefTargetNum,
	vector<Unit*>& aInputArr,
	vector<RefTarget>& aTargetArr,
	vector<SharedPtr<Unit> >& aTargetPtrArr,
	bool aIsRef = true);

void SearchRefTarget(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, vector<RefTarget>& aTargetArr);

void SearchEffTarget(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, const RefTarget& aRefTarget, vector<SharedPtr<Unit> >& aTargetArr);

void SearchRefTargetParam(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Skill>& aSkill, vector<RefTarget>& aTargetArr, RefTargetParam& aParam);