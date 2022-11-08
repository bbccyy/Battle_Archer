


#include <thread> 
#include <stdio.h> 
#include "tool.h"
#include "ConfigMgr/ConfigMgr.h"
#include "Entity/UnitDefine.h"


#if defined _MSC_VER
#include <windows.h>
#else
#include <sys/stat.h>
#endif


int Mkdir(const char* aPath)
{
	if (opendir(aPath) == NULL)
	{
#if defined _MSC_VER
		return CreateDirectory(aPath, NULL) ? 0 : -1;
#else
		mkdir(aPath, 0777);
#endif
	}
	return 0;
}

string Dirname(const char* aPath)
{
	string str(aPath);
	int index = str.rfind("\\");
	if (index < 0)
		index = str.rfind("/");
	if(index >= 0)
		return str.substr(0, index);
	
	return str;
}

void WriteToFile(string aStr, const char* aName)
{
	ofstream out(aName, ofstream::binary | ofstream::out);
	if (out.good() == false)
	{
		LOG_FATAL("open args file faield %s %d", aStr, out.rdstate());
		return;
	}
	out << aStr;
	out.flush();
	out.close();
	return;
}

string LoadBattleArgs(const char* file)
{	
	ifstream in(file, ifstream::binary | ifstream::in);	
	if (in.good() == false)
	{
		LOG_FATAL("open args file faield %s %d", file, in.rdstate());
		return "";
	}
	stringstream strStream;
	strStream << in.rdbuf();
	string battleArgsStr = strStream.str();
	in.close();
	return battleArgsStr;
}
void LoadUserInput(const char* file, vector<UserInput>& inputArr)
{
	ifstream in(file, fstream::in);
	if (in.good() == false)
	{
		return;
	}
	string line;
	char buf[1024];
	while (!in.eof())
	{
		UserInput userInput;
		getline(in, line);
		if (line == "")
		{
			break;
		}
		sscanf(line.c_str(), "%d %s %d %d", &userInput.time, buf, &userInput.commen1, &userInput.field);
		if (strcmp(buf, "executeRageSkill") == 0)
		{
			userInput.cmd = EUserInputCmdExecuteRageSkill;
		}
		else if (strcmp(buf, "executeUnparalleledSkill") == 0)
		{
			userInput.cmd = EUserInputCmdExecuteUnparalleledSkill;
		}
		else if (strcmp(buf, "unregisterSemiAutoSkill") == 0)
		{
			userInput.cmd = EUserInputCmdUnregisterSemiAutoSkill;
		}
		else if (strcmp(buf, "addUnitTD") == 0)
		{
			userInput.cmd = EUserInputCmdAddUnitTD;
			userInput.commen2 = userInput.field;
			userInput.field = 1;
		}
		else if (strcmp(buf, "tryDeleteUnitTD") == 0)
		{
			userInput.cmd = EUserInputCmdDeleteDeadUnitTD;
			userInput.field = 1;
		}
		else if (strcmp(buf, "initNextWave") == 0)
		{
			userInput.cmd = EUserInputCmdInitNextWaveTD;
			userInput.field = 1;
		}
		else
		{
			LOG_WARN("invalid cmd:%s", buf);
		}
		inputArr.push_back(userInput);
	}
}

void LoadBehaviourInput(const char* file, vector<UserInput>& inputArr)
{
	ifstream in(file, fstream::in);
	if (in.good() == false)
	{
		return;
	}
	string line;
	char buf[1024];
	while (!in.eof())
	{
		bool done = true;
		UserInput userInput;
		getline(in, line);
		if (line == "")
		{
			break;
		}
		sscanf(line.c_str(), "%d %d %s %d %d %d %d %d %d %d %d %d", &userInput.time, &userInput.field, buf, &userInput.commen1,
			&userInput.commen2, &userInput.commen3, &userInput.commen4, &userInput.py, &userInput.pz, &userInput.dx,
			&userInput.dy, &userInput.dz);
		if (strcmp(buf, "addUnit") == 0)
		{
			userInput.cmd = EBehaviourInputCmdAddUnit;
		}
		else if (strcmp(buf, "gotoResult") == 0)
		{
			userInput.cmd = EBehaviourInputCmdGotoResult;
		}
		else if (strcmp(buf, "gotoNextField") == 0)
		{
			userInput.cmd = EBehaviourInputCmdGotoNextField;
		}
		else if (strcmp(buf, "moveToStandPoint") == 0)
		{
			sscanf(line.c_str(), "%d %d %s %d %s %d %d %d %d %d %d", &userInput.time, &userInput.field, buf, &userInput.commen1,
				&userInput.name, &userInput.commen2, &userInput.commen3, &userInput.commen4, &userInput.dx, &userInput.dy, &userInput.dz);
			userInput.cmd = EBehaviourInputCmdMoveToStandPoint;
		}
		else if (strcmp(buf, "executeSkill") == 0)
		{
			userInput.cmd = EBehaviourInputCmdExecuteSkill;
		}
		else if (strcmp(buf, "obstacleVisible") == 0)
		{
			userInput.cmd = EBehaviourInputCmdObstacleVisible;
		}
		else if (strcmp(buf, "hideUnit") == 0)
		{
			userInput.cmd = EBehaviourInputCmdHideUnit;
		}
		else if (strcmp(buf, "deleteUnit") == 0)
		{
			userInput.cmd = EBehaviourInputCmdDeleteUnit;
		}
		else if (strcmp(buf, "unitAnim") == 0)
		{
			sscanf(line.c_str(), "%d %d %s %d %s %d", &userInput.time, &userInput.field, buf, &userInput.commen1,
				&userInput.name);
			userInput.cmd = EBehaviourInputCmdUnitAnim;
		}
		else if (strcmp(buf, "stopUnit") == 0)
		{
			userInput.cmd = EBehaviourInputCmdStopUnit;
		}
		else if (strcmp(buf, "addBuff") == 0)
		{
			userInput.cmd = EBehaviourInputCmdAddBuff;
		}
		else if (strcmp(buf, "setTime") == 0)
		{
			userInput.cmd = EBehaviourInputCmdSetTime;
		}
		else if (strcmp(buf, "setExtraTime") == 0)
		{
			userInput.cmd = EBehaviourInputCmdSetExtraTime;
		}
		else if (strcmp(buf, "syncLocation") == 0)
		{
			sscanf(line.c_str(), "%d %d %s %d %d %d %d", &userInput.time, &userInput.field, buf, &userInput.commen1,
				&userInput.commen2, &userInput.commen3, &userInput.commen4);
			userInput.cmd = EBehaviourInputCmdSyncLocation;
		}
		else if (strcmp(buf, "syncDirection") == 0)
		{
			sscanf(line.c_str(), "%d %d %s %d %d %d %d", &userInput.time, &userInput.field, buf, &userInput.commen1,
				&userInput.commen2, &userInput.commen3, &userInput.commen4);
			userInput.cmd = EBehaviourInputCmdSyncDirection;
		}
		else
		{
			//LOG_WARN("invalid cmd:%s", buf);
			done = false;
		}
		if (done)
			inputArr.push_back(userInput);
	}
}

void _perm(int* aArr, int aN, int aM, vector<vector<int> >& aRet, vector<int> aStack)
{
	if (aM <= 0)
	{
		if (aStack.size() > 0)
		{
			aRet.push_back(aStack);
		}
		return;
	}
	if (aN <= 0)
	{
		return;
	}
	aStack.push_back(*aArr);
	_perm(aArr + 1, aN - 1, aM - 1, aRet, aStack);

	aStack.pop_back();
	_perm(aArr + 1, aN - 1, aM, aRet, aStack);
}

void perm(int* aArr, int aN, int aM, vector<vector<int> >& aRet)
{
	vector<int> s;
	_perm(aArr, aN, aM, aRet, s);
}

void genUnitInfo(int aHtid, TUnitInfo* aUnitInfo)
{
	int lv = 10;
	aUnitInfo->set_hid(aHtid);
	aUnitInfo->set_htid(aHtid);
	aUnitInfo->set_level(lv);
	aUnitInfo->set_basesizescale(10000);

	auto* heroConf = ConfigMgr::GetConfById<ConfigHero>(aHtid);
	
	auto skillIdArr = heroConf->GetSkillID();
	for (int i = 0; i < skillIdArr.size(); i++)
	{
		TSkillAttribute* skillInfo = aUnitInfo->add_skillarr();
		skillInfo->set_id(skillIdArr[i]);
		skillInfo->set_level(10);
	
		const vector<vector<int64> >& addtionalSkill = heroConf->GetAddtionalSkill();

		for (int j = 0; j < addtionalSkill.size(); j++)
		{
			const vector<int64>& arr = addtionalSkill[j];
			if (skillIdArr[i] == arr[0])
			{
				for (int k = 1; k < arr.size(); k++)
				{
					TSkillAttribute* skillInfo = aUnitInfo->add_skillarr();
					skillInfo->set_id(arr[k]);
					skillInfo->set_level(10);
				}
				break;
			}			
		}
	}
	auto* heroAttrConf = ConfigMgr::GetConfById<ConfigHeroAttribute>(aHtid);
	int lvFactor = lv - 1;
#define ADD_ATTR(id, value) \
	TAttribute* attr_##id = aUnitInfo->add_attrarr();\
	attr_##id->set_id((uint32)EAttribute::id);\
	attr_##id->set_value(value);\

	ADD_ATTR(Leadership, heroAttrConf->GetBaseCommand());
	ADD_ATTR(Force, heroAttrConf->GetBaseStrength());
	ADD_ATTR(Intelligence, heroAttrConf->GetBaseIntelligence());
	ADD_ATTR(Politics, heroAttrConf->GetBasePolity());
	ADD_ATTR(Charm, heroAttrConf->GetBaseFashion());
	ADD_ATTR(CriticalProb, heroAttrConf->GetBaseCritical());
	ADD_ATTR(PhysicalHitProb, heroAttrConf->GetBasePhysicalHit());
	ADD_ATTR(MagicHitProb, heroAttrConf->GetBaseMagicHit());
	ADD_ATTR(DodgeProb, heroAttrConf->GetBaseDodge());
	ADD_ATTR(ExemptionProb, heroAttrConf->GetExemption());
	ADD_ATTR(BlockProb, heroAttrConf->GetBaseBlock());
	ADD_ATTR(ResilienceProb, heroAttrConf->GetBaseToughness());
	ADD_ATTR(CriticalPercentAdd, heroAttrConf->GetBaseCriticalMultiple());
	ADD_ATTR(PhysicalAtkTalent, heroAttrConf->GetPhysicalAttackTalent());
	ADD_ATTR(PhysicalDefTalent, heroAttrConf->GetPhysicalDefendTalent());
	ADD_ATTR(MagicAtkTalent, heroAttrConf->GetMagicAttackTalent());
	ADD_ATTR(MagicDefTalent, heroAttrConf->GetMagicDefendTalent());

	ADD_ATTR(HpBase, heroAttrConf->GetBaseHp() + lvFactor * heroAttrConf->GetGrowHp() + 10000);
	ADD_ATTR(PhysicalAtkBase, heroAttrConf->GetBasePhysicalAttack() + lvFactor * heroAttrConf->GetGrowPhysicalAttack());
	ADD_ATTR(MagicAtkBase, heroAttrConf->GetBaseMagicAttack() + lvFactor * heroAttrConf->GetGrowMagicAttack());
	ADD_ATTR(PhysicalDefBase, heroAttrConf->GetBasePhysicalDefend() + lvFactor * heroAttrConf->GetGrowPhysicalDefend());
	ADD_ATTR(MagicDefBase, heroAttrConf->GetBaseMagicDefend() + lvFactor * heroAttrConf->GetGrowMagicDefend());
}

void genArmyInfo(vector<int>& aHtidArr, TArmyInfo* aArmyInfo)
{
	for (int i = 0; i < aHtidArr.size(); i++)
	{
		TUnitInfo* unitInfo = aArmyInfo->add_unitarr();
		unitInfo->set_pos(i);
		genUnitInfo(aHtidArr[i], unitInfo);
	}
}

TBattleArgs* genBattleArgs(vector<int>& aArmy1HtidArr, vector<int>& aArmy2HtidArr, uint32 aSeed)
{
	TBattleArgs* battleArgs = new TBattleArgs;
	
	genArmyInfo(aArmy1HtidArr, battleArgs->add_army1arr()) ;
	genArmyInfo(aArmy2HtidArr, battleArgs->add_army2arr());

	battleArgs->set_battletype(EBattleType::EBattleTypeRPGPVP);
	battleArgs->set_randomseed(aSeed);

	TSceneInfo* sceneInfo = battleArgs->add_sceneconf();
	sceneInfo->set_confname("Battle_Jiedao");
	sceneInfo->set_confindex(0);
	sceneInfo->set_timelimit(90);

	return battleArgs;
}

void genTestArgs()
{
	int arrValidHtid[] = {
			10003, //夏侯惇
			10005, //典韦 
			10008, //曹操 
			10010, //徐晃 
			//10011, //张郃 
			10014, //曹仁 
			10015, //夏侯渊
			10016, //张春华
			10023, //刘备 
			10025, //黄忠 
			10027, //祝融 
			10028, //孟获 
			10038, //孙尚香
			10039, //大乔 
			//10040, //吕蒙 
			10041, //孙权 
			10045, //周泰 
			10046, //孙坚 
			10048, //黄盖 
			10055, //董卓 
			10057, //华佗 
			//10058, //貂蝉 
			//10060, //袁绍 
			10061, //张角 
			10062, //文丑 
			10063, //颜良 
	};
	int validHtidNum = sizeof(arrValidHtid) / sizeof(int);
	vector< vector<int> > allCom;
	perm(arrValidHtid, validHtidNum, 5, allCom);

	string outDir = "args";
	Mkdir(outDir.c_str());
	int index = 0;
	int needNum = 1000;
	int allNum = allCom.size() * (allCom.size() - 1) / 2;
	int factor = allNum / needNum;
	for (int i = 0; i < allCom.size(); i++)
	{
		for (int j = i+1; j < allCom.size(); j++)
		{			
			if (index++ % factor)
			{
				continue;
			}
				
			stringstream fileName;
			fileName << outDir << "/args__" << allCom[i][0];
			for (int k = 1; k < allCom[i].size(); k++)
			{
				fileName << "_" << allCom[i][k];
			}
			fileName << "__" << allCom[j][0];
			for (int k = 1; k < allCom[j].size(); k++)
			{
				fileName << "_" << allCom[j][k];
			}

			auto battleArgs = genBattleArgs( allCom[i], allCom[j], i*10000 + j );
			string str;
			battleArgs->SerializeToString(&str);
			ofstream out(fileName.str(), std::ifstream::binary);
			out << str;
			out.close();
			LOG_DEBUG("%s", fileName.str().c_str());
	
		}
	}
	
}
