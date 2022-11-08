
#include "Formula.h"
#include "Define.h"
#include "Log/Log.h"
#include "ConfigMgr/ConfigMgr.h"
#include "module/BuffData.pb.h"

bool CompareCharSlice(const string& a, int a_begin, int a_end, const string& b)
{
	if (a.substr(a_begin, a_end - a_begin) == b)
		return true;
	return false;
}

int myStrToInt(const string& aStr)
{
	if (aStr == "0") return 0;
	if (aStr == "1") return 1;
	if (aStr == "2") return 2;
	if (aStr == "3") return 3;
	if (aStr == "4") return 4;
	if (aStr == "5") return 5;
	if (aStr == "6") return 6;
	if (aStr == "7") return 7;
	if (aStr == "8") return 8;
	if (aStr == "9") return 9;
	return -1;
}

ST CheckCurrentState(const string& aStr, int aIndex)
{
	string str = aStr.substr(aIndex, 1);
	if (' ' == aStr[aIndex] || '\t' == aStr[aIndex])
	{
		return ST::SPACE_STATE;
	}
	else if (myStrToInt(str) >= 0)
	{
		return ST::OPERAND_DIG_STATE;
	}
	else if ('+' == aStr[aIndex] || '-' == aStr[aIndex] ||
		'*' == aStr[aIndex] || '/' == aStr[aIndex] ||
		'(' == aStr[aIndex] || ')' == aStr[aIndex])
	{
		return ST::OPERATOR_STATE;
	}
	else if (aIndex >= aStr.length())
	{
		return ST::END_STATE;
	}

	return ST::OPERAND_WORD_STATE;
}

void Formula::LoadFormula(int aKey, const string& aFormula)
{
	if (aFormula.empty())
		return;
	
	auto& vessel = mTable[aKey];

	ST state = ST::INIT_STATE;
	int64 cache = 0;
	int leftP = -1;

	for (int idx = 0; idx < aFormula.length(); )
	{
		switch (state)
		{
		case ST::INIT_STATE:
			state = CheckCurrentState(aFormula, idx);
			break;
		case ST::OPERAND_DIG_STATE:
			cache = cache * 10 + myStrToInt(aFormula.substr(idx, 1));
			++idx;
			state = CheckCurrentState(aFormula, idx);  //refresh current state
			if (state != ST::OPERAND_DIG_STATE)
			{
				vessel.emplace_back(static_cast<int>(ST::OPERAND_DIG_STATE));
				vessel.emplace_back(cache);
				cache = 0;
			}
			break;
		case ST::OPERAND_WORD_STATE:
			if (leftP < 0)
			{
				leftP = idx;
			}
			++idx;
			state = CheckCurrentState(aFormula, idx);
			if (state != ST::OPERAND_WORD_STATE)
			{ //use dictionary tree?
				vessel.emplace_back(static_cast<int>(ST::OPERAND_WORD_STATE));
				if (CompareCharSlice(aFormula, leftP, idx, string(CUR_HP)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::CUR_HP));
				}
				else if (CompareCharSlice(aFormula, leftP, idx, string(MAX_HP)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::MAX_HP));
				}
				else if (CompareCharSlice(aFormula, leftP, idx, string(REST_FRIEND)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::REST_FRIEND));
				}
				else if (CompareCharSlice(aFormula, leftP, idx, string(REST_ENEMY)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::REST_ENEMY));
				}
				else if (CompareCharSlice(aFormula, leftP, idx, string(PHY_ATK)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::PHY_ATK));
				}
				else if (CompareCharSlice(aFormula, leftP, idx, string(CUR_RAGE)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::CUR_RAGE));
				}
				else if (CompareCharSlice(aFormula, leftP, idx, string(PHY_DEF)))
				{
					vessel.emplace_back(static_cast<int>(SYMBOL::PHY_DEF));
				}
				else //TODO...
				{
					LOG_FATAL("unexpected word in buff id = %d", aKey);
					return;
				}
				leftP = -1;  //reset 
			}
			break;
		case ST::OPERATOR_STATE:
			switch (aFormula[idx])
			{
			case '+':
				vessel.emplace_back(static_cast<int>(ST::OPERATOR_STATE));
				vessel.emplace_back(static_cast<int>(OPERATOR::ADD));
				break;
			case '-':
				vessel.emplace_back(static_cast<int>(ST::OPERATOR_STATE));
				vessel.emplace_back(static_cast<int>(OPERATOR::SUB));
				break;
			case '*':
				vessel.emplace_back(static_cast<int>(ST::OPERATOR_STATE));
				vessel.emplace_back(static_cast<int>(OPERATOR::MUL));
				break;
			case '/':
				vessel.emplace_back(static_cast<int>(ST::OPERATOR_STATE));
				vessel.emplace_back(static_cast<int>(OPERATOR::DEV));
				break;
			case '(':
				vessel.emplace_back(static_cast<int>(ST::OPERATOR_STATE));
				vessel.emplace_back(static_cast<int>(OPERATOR::LP));
				break;
			case ')':
				vessel.emplace_back(static_cast<int>(ST::OPERATOR_STATE));
				vessel.emplace_back(static_cast<int>(OPERATOR::RP));
				break;
			default:
				LOG_FATAL("unexpected operator %s", aFormula.c_str());
				return;
			}
			++idx;
			state = CheckCurrentState(aFormula, idx);
			break;
		case ST::SPACE_STATE:
			++idx;
			state = CheckCurrentState(aFormula, idx);
			break;
		case ST::END_STATE:
			break;
		default:
			break;
		}
	}
}

vector<int>& Formula::GetFormula(int aKey)
{
	/*if (mTable.find(aKey) != mTable.end())
	{
		return mTable[aKey];
	}
	return vector<int>();*/
	auto iter = mTable.find(aKey);
	if (iter != mTable.end())
	{
		return iter->second;
	}
	if (mHasLoadALl)
	{
		LOG_FATAL("not found formula for %d", aKey);		
	}
	
	auto conf = ConfigMgr::GetConfById<pb::BuffData>(aKey);
	if (conf->has_buffmodpropertyformulaconfig() && conf->buffmodpropertyformulaconfig().active())
	{
		//这里不用加锁了。在server端。所有的formula都会被提前加载完 
		LoadFormula(aKey, conf->buffmodpropertyformulaconfig().formula());
	}
	return mTable[aKey];
}

bool Formula::HasFormula(int aKey)
{
	return mTable.find(aKey) != mTable.end();
}

void Formula::SetHasLoadAll(bool aHasLoadAll)
{
	mHasLoadALl = aHasLoadAll;
}

