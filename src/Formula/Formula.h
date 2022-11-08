

#pragma once
#include <vector>
#include <unordered_map>

using namespace std;

enum class ST {
	INIT_STATE = 0,
	OPERAND_DIG_STATE,
	OPERAND_WORD_STATE,
	OPERATOR_STATE,
	SPACE_STATE,
	END_STATE
};

enum class OPERATOR {
	ADD = 0,
	SUB,
	MUL,
	DEV,
	LP,
	RP
};

enum class SYMBOL {
	CUR_HP = 0,
	MAX_HP,
	REST_FRIEND,
	REST_ENEMY,
	PHY_ATK,
	CUR_RAGE,
	PHY_DEF
};

class Formula {

public:
	static Formula* GetInstance()
	{
		static Formula instance;
		return &instance;
	}

	Formula() 
		:mTable(unordered_map<int, vector<int>>(20))
	{
		//nothing
	}

	void LoadFormula(int, const string&);
	
	vector<int>& GetFormula(int);

	bool HasFormula(int);

	void SetHasLoadAll(bool);

private:

	static const constexpr char* CUR_HP = "curhp";
	static const constexpr char* MAX_HP = "maxhp";
	static const constexpr char* REST_FRIEND = "restfriend";
	static const constexpr char* REST_ENEMY = "restenemy";
	static const constexpr char* PHY_ATK = "phyatk";
	static const constexpr char* CUR_RAGE = "currage";
	static const constexpr char* PHY_DEF = "phydef";

	unordered_map<int, vector<int>> mTable;
	bool  mHasLoadALl;
};