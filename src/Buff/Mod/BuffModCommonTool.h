#pragma once
#include "Framework/SharedPool.h"
#include "Skill/SkillDefine.h"

class Unit;

void FilterUnit(const vector<SharedPtr<Unit> >* aCandidateArr, vector<SharedPtr<Unit>>& aWatchList,
	ENeedSummon aNeedSummon,
	bool aNeedDead, Unit* aUtilizer);