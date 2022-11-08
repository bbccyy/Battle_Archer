

#include "BuffModFormula.h"
#include "Entity/Unit.h"
#include "Buff/Buff.h"
#include "Entity/Army.h"
#include "BattleInstance.h"
#include <stack>


ST ReadState(vector<int>& aList, int aIdx, int aSize)
{
	if (aIdx >= aSize)
		return ST::END_STATE;
	return static_cast<ST>(aList[aIdx]);
}

bool BackTrace(std::stack<int64>& aStk, bool hasRP)
{
	int64 cache = 0;
	int safeLoop = 1000;
	while (aStk.size() > 2 || hasRP)
	{
		safeLoop--;
		if (safeLoop < 0)
		{
			LOG_WARN("BackTrace Out of SafeLoop");
			return false;
		}
		cache = aStk.top();  //get current operand 
		aStk.pop();
		//the next should be an operator 
		switch (static_cast<OPERATOR>(aStk.top()))
		{
		case OPERATOR::ADD:
			if (hasRP)  //with right parenthesis, need deal all until meet a left parenthesis
			{
				aStk.pop();  //discard operator
				cache = aStk.top() + cache;
				aStk.pop();
			}
			aStk.push(cache);
			if (!hasRP) return true;
			break;
		case OPERATOR::SUB:
			if (hasRP) 
			{
				aStk.pop();  //discard operator
				cache = aStk.top() - cache;
				aStk.pop();
			}
			aStk.push(cache);
			if (!hasRP) return true;
			break;
		case OPERATOR::MUL:
			aStk.pop();  
			cache = aStk.top() * cache;
			aStk.pop();
			aStk.push(cache);
			break;
		case OPERATOR::DEV:
			aStk.pop();
			cache = aStk.top() / cache;
			aStk.pop();
			aStk.push(cache);
			break;
		case OPERATOR::LP:
			if (!hasRP)
			{
				aStk.push(cache);
				return true;
			}
			hasRP = false;
			aStk.pop();
			aStk.push(cache);
			break;
		case OPERATOR::RP:
			//should not jump into this branch 
			hasRP = true;
			aStk.pop();
			aStk.push(cache);
			break;
		default:
			LOG_WARN("unexpected operator %d", aStk.top());
			return false;
		}
	}
	return true;
}

//note: a word should not include any digit numbers
int64 BuffModFormula::CalculateFormula()
{
	int buffId = GetBuff()->GetId();
	auto& formula = Formula::GetInstance()->GetFormula(buffId);
	int size = formula.size();
	if (size < 1 || size % 2 != 0)
	{
		LOG_WARN("invalid formula for buffId: %d", buffId);
		return 0;
	}

	ST state = ST::INIT_STATE;
	int idx = 0;
	std::stack<int64> stk;
	int safeLoop = 1000;

	for (; idx < size;)
	{
		safeLoop--;
		if (safeLoop < 0)
		{
			LOG_WARN("Out of SafeLoop, buff Id = %d", buffId);
			break;
		}
		switch (state)
		{
		case ST::INIT_STATE:
			state = ReadState(formula, idx, size);
			break;
		case ST::OPERAND_DIG_STATE:
		{
			stk.push(formula[++idx]);  //skip meta data to get real digital value, then push it into stack
			BackTrace(stk, false);  //try shrink stack 
			state = ReadState(formula, ++idx, size);  //forward idx by 1, try refresh current state
		}
			break;
		case ST::OPERAND_WORD_STATE:
		{
			SYMBOL word = static_cast<SYMBOL>(formula[++idx]);
			switch (word)
			{
			case SYMBOL::CUR_HP:
				stk.push(static_cast<int64>(GetOwner()->GetHp()));
				break;
			case SYMBOL::MAX_HP:
				stk.push(static_cast<int64>(GetOwner()->GetMaxHp()));  //op on extrimly large number is fatal 
				break;
			case SYMBOL::REST_ENEMY:
				stk.push(static_cast<int64>(GetOwner()->GetArmy().GetActiveUnitArr().size()));
				break;
			case SYMBOL::REST_FRIEND:
				{
					auto& battleInstance = GetOwner()->GetBattleInstance();
					auto armyId = GetOwner()->GetArmy().GetId();
					stk.push(static_cast<int64>(battleInstance.GetEnemyArmy(armyId).GetActiveUnitArr().size()));
				}
				break;
			case SYMBOL::PHY_ATK:
				stk.push(static_cast<int64>(GetOwner()->GetAttr(EAttribute::PhysicalAtkBase)));
				break;
			case SYMBOL::CUR_RAGE:
				{
					auto curRage = GetOwner()->GetRage();
					if (curRage > 1000) curRage = 1000;
					stk.push(static_cast<int64>(curRage));
				}
				break;
			case SYMBOL::PHY_DEF:
				stk.push(static_cast<int64>(GetOwner()->GetAttr(EAttribute::PhysicalDefBase)));
				break;
			default:
				LOG_WARN("unexpected word");
				stk.push(1);
				break;
			}
			BackTrace(stk, false);
			state = ReadState(formula, ++idx, size);
		}
			break;
		case ST::OPERATOR_STATE:
		{
			OPERATOR op = static_cast<OPERATOR>(formula[++idx]);
			switch (op)
			{
			case OPERATOR::ADD:
			case OPERATOR::SUB:
			case OPERATOR::MUL:
			case OPERATOR::DEV:
			case OPERATOR::LP:
				stk.push(static_cast<int>(op));
				break;
			case OPERATOR::RP:
				BackTrace(stk, true);  //shrink this pair of parenthesis 
				break;
			default:
				LOG_WARN("unexpected operator %d", static_cast<int>(op));
				return 0;
			}
			state = ReadState(formula, ++idx, size);
		}
			break;
		case ST::END_STATE:
			break;
		case ST::SPACE_STATE:
		default:
			LOG_WARN("unexpected state received, buffId:%d", buffId);
			return 0;
		}
	}

	if (stk.size() == 1)
	{
		return stk.top();
	}
	else
	{
		LOG_WARN("unable parse formula buffId:%d", buffId);
	}
	return 0;
}

void BuffModFormula::StackAdded(int)
{
	int64 nextVal = CalculateFormula();
	mParams.mEntries[0].mValue = nextVal - mParams.mDelta;
	mParams.mDelta = nextVal;
	GetOwner()->ModifyAttr(mParams.mEntries, false, GetBuff()->GetId());
}

void BuffModFormula::StackRemoved(int)
{
	//nothing
}

void BuffModFormula::OnEnable()
{
	StackAdded(0);
}

void BuffModFormula::OnDisable(bool aShouldTrigger)
{
	EBuffDisableType type = GetBuff()->GetDisableType();
	if (!aShouldTrigger && type == EBuffDisableType::EBuffDisableByReset) {
		return;
	}
	mParams.mEntries[0].mValue = -mParams.mDelta;
	GetOwner()->ModifyAttr(mParams.mEntries, false); 
}