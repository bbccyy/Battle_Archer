
#include "BuffModCommonTool.h"
#include "Entity/Unit.h"
#include "Entity/Army.h"

void FilterUnit(const vector<SharedPtr<Unit> >* aCandidateArr, vector<SharedPtr<Unit>>& aWatchList,
	ENeedSummon aNeedSummon,
	bool aNeedDead, Unit* aUtilizer)
{
	for (size_t i = 0; i < aCandidateArr->size(); i++)
	{
		auto unit = (*aCandidateArr)[i];
		if (!unit->IsHidden()
			&& !unit->IsDummy()
			&& (aNeedSummon == ESummonAndHero || (unit->IsSummoned() == (aNeedSummon == EOnlySummon)))  //只要召唤，或只要英雄，或两者皆可
			&& (aNeedDead == unit->IsDead())
			&& unit->CanBeRefTargetOfUtilizer(aUtilizer, nullptr))
		{
			aWatchList.push_back(unit);
		}
	}
}