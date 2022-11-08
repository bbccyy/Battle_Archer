// 版权2016-2016 Bable Time, Inc. 版权所有。
// 作者：wuqilin
// 日期：2022-08-11 17:36:48
// 描述：自动生成的配置结构定义文件，不要直接修改
// --------


#pragma once
#include <vector>
#include <string>
#include <string.h>  //linux下strcmp需要这个
#include "CsvBaseType.h"
#include "CsvHelper.h"
#include "Define.h"
#include "Log/Log.h"

using namespace std;


class ConfigAttribute : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigAttribute failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigAttribute. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigAttribute failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigAttribute failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 8 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:8 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mName = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mShowType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[2] ],0);
        mPrerogativeAttributeMethod = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[3] ],0);
        mHaloToBaseId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[4] ],0);
        mDisplayformat = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[5] ],0);
        mInitialValue = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[6] ],0);
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[7] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","Name","ShowType","PrerogativeAttributeMethod","HaloToBaseId","Displayformat","InitialValue","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","int","int","int","int","int","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[8];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigAttribute);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetName</name>
                <replaceName>Name</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetName() const
    {
        return mName;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetShowType</name>
                <replaceName>ShowType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetShowType() const
    {
        return mShowType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetPrerogativeAttributeMethod</name>
                <replaceName>PrerogativeAttributeMethod</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPrerogativeAttributeMethod() const
    {
        return mPrerogativeAttributeMethod;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetHaloToBaseId</name>
                <replaceName>HaloToBaseId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHaloToBaseId() const
    {
        return mHaloToBaseId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetDisplayformat</name>
                <replaceName>Displayformat</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDisplayformat() const
    {
        return mDisplayformat;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetInitialValue</name>
                <replaceName>InitialValue</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetInitialValue() const
    {
        return mInitialValue;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigAttribute</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mName;
    int64 mShowType;
    int64 mPrerogativeAttributeMethod;
    int64 mHaloToBaseId;
    int64 mDisplayformat;
    int64 mInitialValue;
    int64 mVersion;

};


class ConfigBattleConfig : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigBattleConfig failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigBattleConfig. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigBattleConfig failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigBattleConfig failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 122 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:122 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mDamagePercentAddCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mDamagePercentSubCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[2] ],0);
        mForceAtkCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[3] ],0);
        mForceDefCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[4] ],0);
        mIntelligenceAtkCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[5] ],0);
        mIntelligenceDefCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[6] ],0);
        mPhysicsAtkCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[7] ],0);
        mPhysicsDefCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[8] ],0);
        mMagicAtkCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[9] ],0);
        mMagicDefCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[10] ],0);
        mIntelligenceCureCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[11] ],0);
        mDamageFloatCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[12] ],0);
        mCureFloatCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[13] ],0);
        mFloorDamageCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[14] ],0);
        mBlockDamageCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[15] ],0);
        mIntelligenceCureCoefLimit = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[16] ],0);
        mDefaultDownAcceleration = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[17] ],0);
        mDefaultColNum = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[18] ],0);
        mDefaultRadius = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[19] ],0);
        mMaxRage = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[20] ],0);
        mRageSkillThreshold = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[21] ],0);
        mHpToRage = convertToVector<int64>(aColArr[mapStructFieldToCsvField[22] ],0);
        mKillToRage = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[23] ],0);
        mDefaultEnterAI = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[24] ],0);
        mPenetrateMaxDistance = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[25] ],0);
        mDefaultSkillScale = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[26] ],0);
        mBloodHideTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[27] ],0);
        mBloodAnimTime = convertFromStr<float>(aColArr[mapStructFieldToCsvField[28] ],0);
        mBloodCellValue = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[29] ],0);
        mSlgTroopHurtShow = convertToVector<int64>(aColArr[mapStructFieldToCsvField[30] ],0);
        mDefaultSlgTroopSquare = convertToVector<int64>(aColArr[mapStructFieldToCsvField[31] ],0);
        mDeathRate = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[32] ],0);
        mWoundedConversionRate = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[33] ],0);
        mZoomRole = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[34] ],0);
        mZoomOther = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[35] ],0);
        mCameraMoveSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[36] ],0);
        mCameraMoveDistance = aColArr[mapStructFieldToCsvField[37] ];
        mCutSceneSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[38] ],0);
        mNotDisplaysegmentCount = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[39] ],0);
        mRageSkillCamera = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[40] ],0);
        mRageSkillCameraSpeedTime = convertToVector<int64>(aColArr[mapStructFieldToCsvField[41] ],0);
        mCameraMoveCriticalDistance = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[42] ],0);
        mDestructiveValue = convertToVector<int64>(aColArr[mapStructFieldToCsvField[43] ],0);
        mCameraStretchingParameter = convertToVector2<float>(aColArr[mapStructFieldToCsvField[44] ],0);
        mCameraStretchingFormulae = aColArr[mapStructFieldToCsvField[45] ];
        mTroopLv = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[46] ],0);
        mSceneObjiectDestroyCoinLimit = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[47] ],0);
        mSlgBattleAttrCoef = convertToVector<int64>(aColArr[mapStructFieldToCsvField[48] ],0);
        mAtkBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[49] ],0);
        mDefBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[50] ],0);
        mHpBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[51] ],0);
        mCriticalBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[52] ],0);
        mCriticalMultipleBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[53] ],0);
        mHitBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[54] ],0);
        mBlockBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[55] ],0);
        mDamageBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[56] ],0);
        mSkillDamageBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[57] ],0);
        mPvpDamageBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[58] ],0);
        mPveDamageBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[59] ],0);
        mDimensionBattleForceCoef = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[60] ],0);
        mTalBattleForceCoefent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[61] ],0);
        mRageSkillPauseTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[62] ],0);
        mMaxUnparalleledSkillRage = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[63] ],0);
        mUnparalleledSkillThreshold = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[64] ],0);
        mSLGMaxDrawNum = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[65] ],0);
        mSLGDrawDecideTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[66] ],0);
        mSLGDrawContinuedTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[67] ],0);
        mBatleFloatingNumInterval = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[68] ],0);
        mMatchingShapeshfit = convertToVector<int64>(aColArr[mapStructFieldToCsvField[69] ],0);
        mFadeOutMeterial = aColArr[mapStructFieldToCsvField[70] ];
        mFadeOutEffect = aColArr[mapStructFieldToCsvField[71] ];
        mFadeOutEffectLight = aColArr[mapStructFieldToCsvField[72] ];
        mCoinDropWeight = convertToVector<int64>(aColArr[mapStructFieldToCsvField[73] ],0);
        mBossCoinDropWeight = convertToVector<int64>(aColArr[mapStructFieldToCsvField[74] ],0);
        mCoinDropActionCoef = convertToVector<int64>(aColArr[mapStructFieldToCsvField[75] ],0);
        mBoxDropActionCoef = convertToVector<int64>(aColArr[mapStructFieldToCsvField[76] ],0);
        mBattleSeparateCoef = convertToVector<int64>(aColArr[mapStructFieldToCsvField[77] ],0);
        mCoinDropNum = convertToVector<int64>(aColArr[mapStructFieldToCsvField[78] ],0);
        mCoinBoxBackSpeed = convertToVector<int64>(aColArr[mapStructFieldToCsvField[79] ],0);
        mTogetherRatio = convertToVector<int64>(aColArr[mapStructFieldToCsvField[80] ],0);
        mWinActionTime = convertToVector<int64>(aColArr[mapStructFieldToCsvField[81] ],0);
        mCoinStrikeEffect = aColArr[mapStructFieldToCsvField[82] ];
        mCoinMusic = convertToVector<string>(aColArr[mapStructFieldToCsvField[83] ],"");
        mSuperSkillDamageOutTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[84] ],0);
        mBossShowEndTime = convertToVector<int64>(aColArr[mapStructFieldToCsvField[85] ],0);
        mBattleSpeedUnlockCfg = convertToVector<int64>(aColArr[mapStructFieldToCsvField[86] ],0);
        mCoinDropHeroNum = convertToVector<int64>(aColArr[mapStructFieldToCsvField[87] ],0);
        mBoxCollectEffect = aColArr[mapStructFieldToCsvField[88] ];
        mBoxMusic = convertToVector<string>(aColArr[mapStructFieldToCsvField[89] ],"");
        mDefaultAIHero = convertToVector<int64>(aColArr[mapStructFieldToCsvField[90] ],0);
        mDefencePointCamera = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[91] ],0);
        mDefencePointCameraCameraSpeedTime = convertToVector<int64>(aColArr[mapStructFieldToCsvField[92] ],0);
        mDropItemScale = convertToVector<int64>(aColArr[mapStructFieldToCsvField[93] ],0);
        mExpeditionStarAdjust = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[94] ],0);
        mExpeditionExtraAdjust = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[95] ],0);
        mBossHpRange = convertToVector<int64>(aColArr[mapStructFieldToCsvField[96] ],0);
        mCameraAdjust = convertToVector<int64>(aColArr[mapStructFieldToCsvField[97] ],0);
        mTDCameraAdjust = convertToVector<int64>(aColArr[mapStructFieldToCsvField[98] ],0);
        mBloodSize = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[99] ],0);
        mCameraCoordinateAdjust = convertToVector<float>(aColArr[mapStructFieldToCsvField[100] ],0);
        mPvpHpAdjust = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[101] ],0);
        mPveNpcSkill = convertToVector<int64>(aColArr[mapStructFieldToCsvField[102] ],0);
        mSuckBloodEffect = aColArr[mapStructFieldToCsvField[103] ];
        mHeroNumBeastPause = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[104] ],0);
        mFighterBaseInfo = convertToVector<int64>(aColArr[mapStructFieldToCsvField[105] ],0);
        mShooterBaseInfo = convertToVector<int64>(aColArr[mapStructFieldToCsvField[106] ],0);
        mShooterToFighterID = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[107] ],0);
        mNextWaveMinMonster = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[108] ],0);
        mWarningTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[109] ],0);
        mShooterAttackRangeRate = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[110] ],0);
        mEnergyAdd = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[111] ],0);
        mEnergyGrow = convertToVector<int64>(aColArr[mapStructFieldToCsvField[112] ],0);
        mAttrLimit = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[113] ],0);
        mTDDefaultId = convertToVector<int64>(aColArr[mapStructFieldToCsvField[114] ],0);
        mTDCommonSkill = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[115] ],0);
        mTDFortress = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[116] ],0);
        mNewBossHpRange = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[117] ],0);
        mWarRidingFormOffset = convertToVector<int64>(aColArr[mapStructFieldToCsvField[118] ],0);
        mBattleAttrNumMax = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[119] ],0);
        mBattleDamageNumMax = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[120] ],0);
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[121] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","DamagePercentAddCoef","DamagePercentSubCoef","ForceAtkCoef","ForceDefCoef","IntelligenceAtkCoef","IntelligenceDefCoef","PhysicsAtkCoef","PhysicsDefCoef","MagicAtkCoef","MagicDefCoef","IntelligenceCureCoef","DamageFloatCoef","CureFloatCoef","FloorDamageCoef","BlockDamageCoef","IntelligenceCureCoefLimit","DefaultDownAcceleration","DefaultColNum","DefaultRadius","MaxRage","RageSkillThreshold","HpToRage","KillToRage","DefaultEnterAI","PenetrateMaxDistance","DefaultSkillScale","BloodHideTime","BloodAnimTime","BloodCellValue","SlgTroopHurtShow","DefaultSlgTroopSquare","DeathRate","WoundedConversionRate","ZoomRole","ZoomOther","CameraMoveSpeed","CameraMoveDistance","CutSceneSpeed","NotDisplaysegmentCount","RageSkillCamera","RageSkillCameraSpeedTime","CameraMoveCriticalDistance","DestructiveValue","CameraStretchingParameter","CameraStretchingFormulae","TroopLv","SceneObjiectDestroyCoinLimit","SlgBattleAttrCoef","AtkBattleForceCoef","DefBattleForceCoef","HpBattleForceCoef","CriticalBattleForceCoef","CriticalMultipleBattleForceCoef","HitBattleForceCoef","BlockBattleForceCoef","DamageBattleForceCoef","SkillDamageBattleForceCoef","PvpDamageBattleForceCoef","PveDamageBattleForceCoef","DimensionBattleForceCoef","TalBattleForceCoefent","RageSkillPauseTime","MaxUnparalleledSkillRage","UnparalleledSkillThreshold","SLGMaxDrawNum","SLGDrawDecideTime","SLGDrawContinuedTime","BatleFloatingNumInterval","MatchingShapeshfit","FadeOutMeterial","FadeOutEffect","FadeOutEffectLight","CoinDropWeight","BossCoinDropWeight","CoinDropActionCoef","BoxDropActionCoef","BattleSeparateCoef","CoinDropNum","CoinBoxBackSpeed","TogetherRatio","WinActionTime","CoinStrikeEffect","CoinMusic","SuperSkillDamageOutTime","BossShowEndTime","BattleSpeedUnlockCfg","CoinDropHeroNum","BoxCollectEffect","BoxMusic","DefaultAIHero","DefencePointCamera","DefencePointCameraCameraSpeedTime","DropItemScale","ExpeditionStarAdjust","ExpeditionExtraAdjust","BossHpRange","CameraAdjust","TDCameraAdjust","BloodSize","CameraCoordinateAdjust","PvpHpAdjust","PveNpcSkill","SuckBloodEffect","HeroNumBeastPause","FighterBaseInfo","ShooterBaseInfo","ShooterToFighterID","NextWaveMinMonster","WarningTime","ShooterAttackRangeRate","EnergyAdd","EnergyGrow","AttrLimit","TDDefaultId","TDCommonSkill","TDFortress","NewBossHpRange","WarRidingFormOffset","BattleAttrNumMax","BattleDamageNumMax","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int[]","int","int","int","int","int","float","int","int[]","int[]","int","int","int","int","int","string","int","int[][]","int[][]","int[]","int","int[]","float[][]","string","int[][]","int","int[]","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int[]","string","assetpath","assetpath","int[]","int[]","int[]","int[]","int[]","int[]","int[]","int[]","int[]","assetpath","string[]","int","int[]","int[]","int[]","assetpath","string[]","int[]","int[][]","int[]","int[]","int[][]","int[][]","int[]","int[]","int[]","int","float[]","int","int[]","assetpath","int","int[]","int[]","int[][]","int","int","int","int[][]","int[]","int[][]","int[]","int[][]","int","int[][]","int[]","int[][]","int","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[122];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigBattleConfig);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDamagePercentAddCoef</name>
                <replaceName>DamagePercentAddCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDamagePercentAddCoef() const
    {
        return mDamagePercentAddCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDamagePercentSubCoef</name>
                <replaceName>DamagePercentSubCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDamagePercentSubCoef() const
    {
        return mDamagePercentSubCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetForceAtkCoef</name>
                <replaceName>ForceAtkCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetForceAtkCoef() const
    {
        return mForceAtkCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetForceDefCoef</name>
                <replaceName>ForceDefCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetForceDefCoef() const
    {
        return mForceDefCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetIntelligenceAtkCoef</name>
                <replaceName>IntelligenceAtkCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIntelligenceAtkCoef() const
    {
        return mIntelligenceAtkCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetIntelligenceDefCoef</name>
                <replaceName>IntelligenceDefCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIntelligenceDefCoef() const
    {
        return mIntelligenceDefCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPhysicsAtkCoef</name>
                <replaceName>PhysicsAtkCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPhysicsAtkCoef() const
    {
        return mPhysicsAtkCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPhysicsDefCoef</name>
                <replaceName>PhysicsDefCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPhysicsDefCoef() const
    {
        return mPhysicsDefCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetMagicAtkCoef</name>
                <replaceName>MagicAtkCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMagicAtkCoef() const
    {
        return mMagicAtkCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetMagicDefCoef</name>
                <replaceName>MagicDefCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMagicDefCoef() const
    {
        return mMagicDefCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetIntelligenceCureCoef</name>
                <replaceName>IntelligenceCureCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIntelligenceCureCoef() const
    {
        return mIntelligenceCureCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDamageFloatCoef</name>
                <replaceName>DamageFloatCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDamageFloatCoef() const
    {
        return mDamageFloatCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCureFloatCoef</name>
                <replaceName>CureFloatCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCureFloatCoef() const
    {
        return mCureFloatCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetFloorDamageCoef</name>
                <replaceName>FloorDamageCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetFloorDamageCoef() const
    {
        return mFloorDamageCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBlockDamageCoef</name>
                <replaceName>BlockDamageCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBlockDamageCoef() const
    {
        return mBlockDamageCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetIntelligenceCureCoefLimit</name>
                <replaceName>IntelligenceCureCoefLimit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIntelligenceCureCoefLimit() const
    {
        return mIntelligenceCureCoefLimit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultDownAcceleration</name>
                <replaceName>DefaultDownAcceleration</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefaultDownAcceleration() const
    {
        return mDefaultDownAcceleration;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultColNum</name>
                <replaceName>DefaultColNum</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefaultColNum() const
    {
        return mDefaultColNum;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultRadius</name>
                <replaceName>DefaultRadius</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefaultRadius() const
    {
        return mDefaultRadius;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetMaxRage</name>
                <replaceName>MaxRage</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMaxRage() const
    {
        return mMaxRage;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetRageSkillThreshold</name>
                <replaceName>RageSkillThreshold</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRageSkillThreshold() const
    {
        return mRageSkillThreshold;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetHpToRage</name>
                <replaceName>HpToRage</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetHpToRage() const
    {
        return mHpToRage;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetKillToRage</name>
                <replaceName>KillToRage</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetKillToRage() const
    {
        return mKillToRage;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultEnterAI</name>
                <replaceName>DefaultEnterAI</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefaultEnterAI() const
    {
        return mDefaultEnterAI;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPenetrateMaxDistance</name>
                <replaceName>PenetrateMaxDistance</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPenetrateMaxDistance() const
    {
        return mPenetrateMaxDistance;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultSkillScale</name>
                <replaceName>DefaultSkillScale</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefaultSkillScale() const
    {
        return mDefaultSkillScale;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBloodHideTime</name>
                <replaceName>BloodHideTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBloodHideTime() const
    {
        return mBloodHideTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBloodAnimTime</name>
                <replaceName>BloodAnimTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline float GetBloodAnimTime() const
    {
        return mBloodAnimTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBloodCellValue</name>
                <replaceName>BloodCellValue</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBloodCellValue() const
    {
        return mBloodCellValue;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSlgTroopHurtShow</name>
                <replaceName>SlgTroopHurtShow</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetSlgTroopHurtShow() const
    {
        return mSlgTroopHurtShow;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultSlgTroopSquare</name>
                <replaceName>DefaultSlgTroopSquare</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetDefaultSlgTroopSquare() const
    {
        return mDefaultSlgTroopSquare;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDeathRate</name>
                <replaceName>DeathRate</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDeathRate() const
    {
        return mDeathRate;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetWoundedConversionRate</name>
                <replaceName>WoundedConversionRate</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetWoundedConversionRate() const
    {
        return mWoundedConversionRate;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetZoomRole</name>
                <replaceName>ZoomRole</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetZoomRole() const
    {
        return mZoomRole;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetZoomOther</name>
                <replaceName>ZoomOther</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetZoomOther() const
    {
        return mZoomOther;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraMoveSpeed</name>
                <replaceName>CameraMoveSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCameraMoveSpeed() const
    {
        return mCameraMoveSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraMoveDistance</name>
                <replaceName>CameraMoveDistance</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetCameraMoveDistance() const
    {
        return mCameraMoveDistance;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCutSceneSpeed</name>
                <replaceName>CutSceneSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCutSceneSpeed() const
    {
        return mCutSceneSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetNotDisplaysegmentCount</name>
                <replaceName>NotDisplaysegmentCount</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetNotDisplaysegmentCount() const
    {
        return mNotDisplaysegmentCount;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetRageSkillCamera</name>
                <replaceName>RageSkillCamera</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetRageSkillCamera() const
    {
        return mRageSkillCamera;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetRageSkillCameraSpeedTime</name>
                <replaceName>RageSkillCameraSpeedTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetRageSkillCameraSpeedTime() const
    {
        return mRageSkillCameraSpeedTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraMoveCriticalDistance</name>
                <replaceName>CameraMoveCriticalDistance</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCameraMoveCriticalDistance() const
    {
        return mCameraMoveCriticalDistance;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDestructiveValue</name>
                <replaceName>DestructiveValue</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetDestructiveValue() const
    {
        return mDestructiveValue;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraStretchingParameter</name>
                <replaceName>CameraStretchingParameter</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<float> >& GetCameraStretchingParameter() const
    {
        return mCameraStretchingParameter;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraStretchingFormulae</name>
                <replaceName>CameraStretchingFormulae</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetCameraStretchingFormulae() const
    {
        return mCameraStretchingFormulae;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTroopLv</name>
                <replaceName>TroopLv</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetTroopLv() const
    {
        return mTroopLv;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSceneObjiectDestroyCoinLimit</name>
                <replaceName>SceneObjiectDestroyCoinLimit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSceneObjiectDestroyCoinLimit() const
    {
        return mSceneObjiectDestroyCoinLimit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSlgBattleAttrCoef</name>
                <replaceName>SlgBattleAttrCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetSlgBattleAttrCoef() const
    {
        return mSlgBattleAttrCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetAtkBattleForceCoef</name>
                <replaceName>AtkBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetAtkBattleForceCoef() const
    {
        return mAtkBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefBattleForceCoef</name>
                <replaceName>DefBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefBattleForceCoef() const
    {
        return mDefBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetHpBattleForceCoef</name>
                <replaceName>HpBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHpBattleForceCoef() const
    {
        return mHpBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCriticalBattleForceCoef</name>
                <replaceName>CriticalBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCriticalBattleForceCoef() const
    {
        return mCriticalBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCriticalMultipleBattleForceCoef</name>
                <replaceName>CriticalMultipleBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCriticalMultipleBattleForceCoef() const
    {
        return mCriticalMultipleBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetHitBattleForceCoef</name>
                <replaceName>HitBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHitBattleForceCoef() const
    {
        return mHitBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBlockBattleForceCoef</name>
                <replaceName>BlockBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBlockBattleForceCoef() const
    {
        return mBlockBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDamageBattleForceCoef</name>
                <replaceName>DamageBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDamageBattleForceCoef() const
    {
        return mDamageBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSkillDamageBattleForceCoef</name>
                <replaceName>SkillDamageBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSkillDamageBattleForceCoef() const
    {
        return mSkillDamageBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPvpDamageBattleForceCoef</name>
                <replaceName>PvpDamageBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPvpDamageBattleForceCoef() const
    {
        return mPvpDamageBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPveDamageBattleForceCoef</name>
                <replaceName>PveDamageBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPveDamageBattleForceCoef() const
    {
        return mPveDamageBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDimensionBattleForceCoef</name>
                <replaceName>DimensionBattleForceCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDimensionBattleForceCoef() const
    {
        return mDimensionBattleForceCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTalBattleForceCoefent</name>
                <replaceName>TalBattleForceCoefent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTalBattleForceCoefent() const
    {
        return mTalBattleForceCoefent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetRageSkillPauseTime</name>
                <replaceName>RageSkillPauseTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRageSkillPauseTime() const
    {
        return mRageSkillPauseTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetMaxUnparalleledSkillRage</name>
                <replaceName>MaxUnparalleledSkillRage</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMaxUnparalleledSkillRage() const
    {
        return mMaxUnparalleledSkillRage;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetUnparalleledSkillThreshold</name>
                <replaceName>UnparalleledSkillThreshold</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetUnparalleledSkillThreshold() const
    {
        return mUnparalleledSkillThreshold;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSLGMaxDrawNum</name>
                <replaceName>SLGMaxDrawNum</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSLGMaxDrawNum() const
    {
        return mSLGMaxDrawNum;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSLGDrawDecideTime</name>
                <replaceName>SLGDrawDecideTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSLGDrawDecideTime() const
    {
        return mSLGDrawDecideTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSLGDrawContinuedTime</name>
                <replaceName>SLGDrawContinuedTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSLGDrawContinuedTime() const
    {
        return mSLGDrawContinuedTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBatleFloatingNumInterval</name>
                <replaceName>BatleFloatingNumInterval</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBatleFloatingNumInterval() const
    {
        return mBatleFloatingNumInterval;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetMatchingShapeshfit</name>
                <replaceName>MatchingShapeshfit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetMatchingShapeshfit() const
    {
        return mMatchingShapeshfit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetFadeOutMeterial</name>
                <replaceName>FadeOutMeterial</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetFadeOutMeterial() const
    {
        return mFadeOutMeterial;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetFadeOutEffect</name>
                <replaceName>FadeOutEffect</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetFadeOutEffect() const
    {
        return mFadeOutEffect;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetFadeOutEffectLight</name>
                <replaceName>FadeOutEffectLight</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetFadeOutEffectLight() const
    {
        return mFadeOutEffectLight;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinDropWeight</name>
                <replaceName>CoinDropWeight</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetCoinDropWeight() const
    {
        return mCoinDropWeight;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBossCoinDropWeight</name>
                <replaceName>BossCoinDropWeight</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetBossCoinDropWeight() const
    {
        return mBossCoinDropWeight;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinDropActionCoef</name>
                <replaceName>CoinDropActionCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetCoinDropActionCoef() const
    {
        return mCoinDropActionCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBoxDropActionCoef</name>
                <replaceName>BoxDropActionCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetBoxDropActionCoef() const
    {
        return mBoxDropActionCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBattleSeparateCoef</name>
                <replaceName>BattleSeparateCoef</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetBattleSeparateCoef() const
    {
        return mBattleSeparateCoef;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinDropNum</name>
                <replaceName>CoinDropNum</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetCoinDropNum() const
    {
        return mCoinDropNum;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinBoxBackSpeed</name>
                <replaceName>CoinBoxBackSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetCoinBoxBackSpeed() const
    {
        return mCoinBoxBackSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTogetherRatio</name>
                <replaceName>TogetherRatio</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetTogetherRatio() const
    {
        return mTogetherRatio;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetWinActionTime</name>
                <replaceName>WinActionTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetWinActionTime() const
    {
        return mWinActionTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinStrikeEffect</name>
                <replaceName>CoinStrikeEffect</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetCoinStrikeEffect() const
    {
        return mCoinStrikeEffect;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinMusic</name>
                <replaceName>CoinMusic</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<string>& GetCoinMusic() const
    {
        return mCoinMusic;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSuperSkillDamageOutTime</name>
                <replaceName>SuperSkillDamageOutTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSuperSkillDamageOutTime() const
    {
        return mSuperSkillDamageOutTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBossShowEndTime</name>
                <replaceName>BossShowEndTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetBossShowEndTime() const
    {
        return mBossShowEndTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBattleSpeedUnlockCfg</name>
                <replaceName>BattleSpeedUnlockCfg</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetBattleSpeedUnlockCfg() const
    {
        return mBattleSpeedUnlockCfg;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCoinDropHeroNum</name>
                <replaceName>CoinDropHeroNum</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetCoinDropHeroNum() const
    {
        return mCoinDropHeroNum;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBoxCollectEffect</name>
                <replaceName>BoxCollectEffect</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetBoxCollectEffect() const
    {
        return mBoxCollectEffect;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBoxMusic</name>
                <replaceName>BoxMusic</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<string>& GetBoxMusic() const
    {
        return mBoxMusic;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefaultAIHero</name>
                <replaceName>DefaultAIHero</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetDefaultAIHero() const
    {
        return mDefaultAIHero;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefencePointCamera</name>
                <replaceName>DefencePointCamera</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetDefencePointCamera() const
    {
        return mDefencePointCamera;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDefencePointCameraCameraSpeedTime</name>
                <replaceName>DefencePointCameraCameraSpeedTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetDefencePointCameraCameraSpeedTime() const
    {
        return mDefencePointCameraCameraSpeedTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetDropItemScale</name>
                <replaceName>DropItemScale</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetDropItemScale() const
    {
        return mDropItemScale;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetExpeditionStarAdjust</name>
                <replaceName>ExpeditionStarAdjust</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetExpeditionStarAdjust() const
    {
        return mExpeditionStarAdjust;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetExpeditionExtraAdjust</name>
                <replaceName>ExpeditionExtraAdjust</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetExpeditionExtraAdjust() const
    {
        return mExpeditionExtraAdjust;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBossHpRange</name>
                <replaceName>BossHpRange</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetBossHpRange() const
    {
        return mBossHpRange;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraAdjust</name>
                <replaceName>CameraAdjust</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetCameraAdjust() const
    {
        return mCameraAdjust;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTDCameraAdjust</name>
                <replaceName>TDCameraAdjust</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetTDCameraAdjust() const
    {
        return mTDCameraAdjust;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBloodSize</name>
                <replaceName>BloodSize</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBloodSize() const
    {
        return mBloodSize;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetCameraCoordinateAdjust</name>
                <replaceName>CameraCoordinateAdjust</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<float>& GetCameraCoordinateAdjust() const
    {
        return mCameraCoordinateAdjust;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPvpHpAdjust</name>
                <replaceName>PvpHpAdjust</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPvpHpAdjust() const
    {
        return mPvpHpAdjust;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetPveNpcSkill</name>
                <replaceName>PveNpcSkill</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetPveNpcSkill() const
    {
        return mPveNpcSkill;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetSuckBloodEffect</name>
                <replaceName>SuckBloodEffect</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetSuckBloodEffect() const
    {
        return mSuckBloodEffect;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetHeroNumBeastPause</name>
                <replaceName>HeroNumBeastPause</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroNumBeastPause() const
    {
        return mHeroNumBeastPause;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetFighterBaseInfo</name>
                <replaceName>FighterBaseInfo</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetFighterBaseInfo() const
    {
        return mFighterBaseInfo;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetShooterBaseInfo</name>
                <replaceName>ShooterBaseInfo</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetShooterBaseInfo() const
    {
        return mShooterBaseInfo;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetShooterToFighterID</name>
                <replaceName>ShooterToFighterID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetShooterToFighterID() const
    {
        return mShooterToFighterID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetNextWaveMinMonster</name>
                <replaceName>NextWaveMinMonster</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetNextWaveMinMonster() const
    {
        return mNextWaveMinMonster;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetWarningTime</name>
                <replaceName>WarningTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetWarningTime() const
    {
        return mWarningTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetShooterAttackRangeRate</name>
                <replaceName>ShooterAttackRangeRate</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetShooterAttackRangeRate() const
    {
        return mShooterAttackRangeRate;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetEnergyAdd</name>
                <replaceName>EnergyAdd</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetEnergyAdd() const
    {
        return mEnergyAdd;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetEnergyGrow</name>
                <replaceName>EnergyGrow</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetEnergyGrow() const
    {
        return mEnergyGrow;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetAttrLimit</name>
                <replaceName>AttrLimit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetAttrLimit() const
    {
        return mAttrLimit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTDDefaultId</name>
                <replaceName>TDDefaultId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetTDDefaultId() const
    {
        return mTDDefaultId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTDCommonSkill</name>
                <replaceName>TDCommonSkill</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetTDCommonSkill() const
    {
        return mTDCommonSkill;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetTDFortress</name>
                <replaceName>TDFortress</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTDFortress() const
    {
        return mTDFortress;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetNewBossHpRange</name>
                <replaceName>NewBossHpRange</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetNewBossHpRange() const
    {
        return mNewBossHpRange;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetWarRidingFormOffset</name>
                <replaceName>WarRidingFormOffset</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetWarRidingFormOffset() const
    {
        return mWarRidingFormOffset;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBattleAttrNumMax</name>
                <replaceName>BattleAttrNumMax</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetBattleAttrNumMax() const
    {
        return mBattleAttrNumMax;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetBattleDamageNumMax</name>
                <replaceName>BattleDamageNumMax</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBattleDamageNumMax() const
    {
        return mBattleDamageNumMax;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigBattleConfig</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mDamagePercentAddCoef;
    int64 mDamagePercentSubCoef;
    int64 mForceAtkCoef;
    int64 mForceDefCoef;
    int64 mIntelligenceAtkCoef;
    int64 mIntelligenceDefCoef;
    int64 mPhysicsAtkCoef;
    int64 mPhysicsDefCoef;
    int64 mMagicAtkCoef;
    int64 mMagicDefCoef;
    int64 mIntelligenceCureCoef;
    int64 mDamageFloatCoef;
    int64 mCureFloatCoef;
    int64 mFloorDamageCoef;
    int64 mBlockDamageCoef;
    int64 mIntelligenceCureCoefLimit;
    int64 mDefaultDownAcceleration;
    int64 mDefaultColNum;
    int64 mDefaultRadius;
    int64 mMaxRage;
    int64 mRageSkillThreshold;
    vector<int64> mHpToRage;
    int64 mKillToRage;
    int64 mDefaultEnterAI;
    int64 mPenetrateMaxDistance;
    int64 mDefaultSkillScale;
    int64 mBloodHideTime;
    float mBloodAnimTime;
    int64 mBloodCellValue;
    vector<int64> mSlgTroopHurtShow;
    vector<int64> mDefaultSlgTroopSquare;
    int64 mDeathRate;
    int64 mWoundedConversionRate;
    int64 mZoomRole;
    int64 mZoomOther;
    int64 mCameraMoveSpeed;
    string mCameraMoveDistance;
    int64 mCutSceneSpeed;
    vector<vector<int64> > mNotDisplaysegmentCount;
    vector<vector<int64> > mRageSkillCamera;
    vector<int64> mRageSkillCameraSpeedTime;
    int64 mCameraMoveCriticalDistance;
    vector<int64> mDestructiveValue;
    vector<vector<float> > mCameraStretchingParameter;
    string mCameraStretchingFormulae;
    vector<vector<int64> > mTroopLv;
    int64 mSceneObjiectDestroyCoinLimit;
    vector<int64> mSlgBattleAttrCoef;
    int64 mAtkBattleForceCoef;
    int64 mDefBattleForceCoef;
    int64 mHpBattleForceCoef;
    int64 mCriticalBattleForceCoef;
    int64 mCriticalMultipleBattleForceCoef;
    int64 mHitBattleForceCoef;
    int64 mBlockBattleForceCoef;
    int64 mDamageBattleForceCoef;
    int64 mSkillDamageBattleForceCoef;
    int64 mPvpDamageBattleForceCoef;
    int64 mPveDamageBattleForceCoef;
    int64 mDimensionBattleForceCoef;
    int64 mTalBattleForceCoefent;
    int64 mRageSkillPauseTime;
    int64 mMaxUnparalleledSkillRage;
    int64 mUnparalleledSkillThreshold;
    int64 mSLGMaxDrawNum;
    int64 mSLGDrawDecideTime;
    int64 mSLGDrawContinuedTime;
    int64 mBatleFloatingNumInterval;
    vector<int64> mMatchingShapeshfit;
    string mFadeOutMeterial;
    string mFadeOutEffect;
    string mFadeOutEffectLight;
    vector<int64> mCoinDropWeight;
    vector<int64> mBossCoinDropWeight;
    vector<int64> mCoinDropActionCoef;
    vector<int64> mBoxDropActionCoef;
    vector<int64> mBattleSeparateCoef;
    vector<int64> mCoinDropNum;
    vector<int64> mCoinBoxBackSpeed;
    vector<int64> mTogetherRatio;
    vector<int64> mWinActionTime;
    string mCoinStrikeEffect;
    vector<string> mCoinMusic;
    int64 mSuperSkillDamageOutTime;
    vector<int64> mBossShowEndTime;
    vector<int64> mBattleSpeedUnlockCfg;
    vector<int64> mCoinDropHeroNum;
    string mBoxCollectEffect;
    vector<string> mBoxMusic;
    vector<int64> mDefaultAIHero;
    vector<vector<int64> > mDefencePointCamera;
    vector<int64> mDefencePointCameraCameraSpeedTime;
    vector<int64> mDropItemScale;
    vector<vector<int64> > mExpeditionStarAdjust;
    vector<vector<int64> > mExpeditionExtraAdjust;
    vector<int64> mBossHpRange;
    vector<int64> mCameraAdjust;
    vector<int64> mTDCameraAdjust;
    int64 mBloodSize;
    vector<float> mCameraCoordinateAdjust;
    int64 mPvpHpAdjust;
    vector<int64> mPveNpcSkill;
    string mSuckBloodEffect;
    int64 mHeroNumBeastPause;
    vector<int64> mFighterBaseInfo;
    vector<int64> mShooterBaseInfo;
    vector<vector<int64> > mShooterToFighterID;
    int64 mNextWaveMinMonster;
    int64 mWarningTime;
    int64 mShooterAttackRangeRate;
    vector<vector<int64> > mEnergyAdd;
    vector<int64> mEnergyGrow;
    vector<vector<int64> > mAttrLimit;
    vector<int64> mTDDefaultId;
    vector<vector<int64> > mTDCommonSkill;
    int64 mTDFortress;
    vector<vector<int64> > mNewBossHpRange;
    vector<int64> mWarRidingFormOffset;
    vector<vector<int64> > mBattleAttrNumMax;
    int64 mBattleDamageNumMax;
    int64 mVersion;

};


class ConfigDestructiveObjects : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigDestructiveObjects failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigDestructiveObjects. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigDestructiveObjects failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigDestructiveObjects failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 5 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:5 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mDestructiveLimit = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mEventWeight = convertToVector<int64>(aColArr[mapStructFieldToCsvField[2] ],0);
        mRandomEvent = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[3] ],0);
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[4] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","DestructiveLimit","EventWeight","RandomEvent","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","int[]","int[][]","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[5];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigDestructiveObjects);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjects</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjects</name>
            <Function>
                <name>GetDestructiveLimit</name>
                <replaceName>DestructiveLimit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDestructiveLimit() const
    {
        return mDestructiveLimit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjects</name>
            <Function>
                <name>GetEventWeight</name>
                <replaceName>EventWeight</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetEventWeight() const
    {
        return mEventWeight;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjects</name>
            <Function>
                <name>GetRandomEvent</name>
                <replaceName>RandomEvent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetRandomEvent() const
    {
        return mRandomEvent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjects</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mDestructiveLimit;
    vector<int64> mEventWeight;
    vector<vector<int64> > mRandomEvent;
    int64 mVersion;

};


class ConfigDestructiveObjectsEvent : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigDestructiveObjectsEvent failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigDestructiveObjectsEvent. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigDestructiveObjectsEvent failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigDestructiveObjectsEvent failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 6 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:6 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mEventType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mEvents = convertToVector<int64>(aColArr[mapStructFieldToCsvField[2] ],0);
        mEffectType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[3] ],0);
        mEffectResourcePath = aColArr[mapStructFieldToCsvField[4] ];
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[5] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","EventType","Events","EffectType","EffectResourcePath","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","int[]","int","assetpath","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[6];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigDestructiveObjectsEvent);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjectsEvent</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjectsEvent</name>
            <Function>
                <name>GetEventType</name>
                <replaceName>EventType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetEventType() const
    {
        return mEventType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjectsEvent</name>
            <Function>
                <name>GetEvents</name>
                <replaceName>Events</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetEvents() const
    {
        return mEvents;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjectsEvent</name>
            <Function>
                <name>GetEffectType</name>
                <replaceName>EffectType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetEffectType() const
    {
        return mEffectType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjectsEvent</name>
            <Function>
                <name>GetEffectResourcePath</name>
                <replaceName>EffectResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetEffectResourcePath() const
    {
        return mEffectResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigDestructiveObjectsEvent</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mEventType;
    vector<int64> mEvents;
    int64 mEffectType;
    string mEffectResourcePath;
    int64 mVersion;

};


class ConfigHero : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigHero failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigHero. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigHero failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigHero failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 109 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:109 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mModelId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mHeroFragmentID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[2] ],0);
        mIsFashion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[3] ],0);
        mFashionModelId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[4] ],0);
        mHeroName = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[5] ],0);
        mHeroPositionId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[6] ],0);
        mHeroDescribeId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[7] ],0);
        mAnimateResourcePath = aColArr[mapStructFieldToCsvField[8] ];
        mAnimateResourceHighPath = aColArr[mapStructFieldToCsvField[9] ];
        mHeadshotResourcePath = aColArr[mapStructFieldToCsvField[10] ];
        mSpineResourcePath = aColArr[mapStructFieldToCsvField[11] ];
        mBagImageResourcePath = aColArr[mapStructFieldToCsvField[12] ];
        mHandbookImageResourcePath = aColArr[mapStructFieldToCsvField[13] ];
        mHeroLihuiResourcePath = aColArr[mapStructFieldToCsvField[14] ];
        mHeroNameResourcePath = aColArr[mapStructFieldToCsvField[15] ];
        mStarup_NameResourcePath = aColArr[mapStructFieldToCsvField[16] ];
        mFrameAnim_SpriteResourcePath = aColArr[mapStructFieldToCsvField[17] ];
        mRageSkilHeadNormalshotResourcePath = aColArr[mapStructFieldToCsvField[18] ];
        mRageSkilHeadshotResourcePath = aColArr[mapStructFieldToCsvField[19] ];
        mSkillID = convertToVector<int64>(aColArr[mapStructFieldToCsvField[20] ],0);
        mSkillUnlockProgress = convertToVector<int64>(aColArr[mapStructFieldToCsvField[21] ],0);
        mAddtionalSkill = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[22] ],0);
        mChainSkillList = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[23] ],0);
        mLevelUpID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[24] ],0);
        mAttributeID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[25] ],0);
        mTroopID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[26] ],0);
        mTroopLv = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[27] ],0);
        mFormation = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[28] ],0);
        mPosWeight = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[29] ],0);
        mPosType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[30] ],0);
        mBodySize = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[31] ],0);
        mIgnoreCollision = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[32] ],0);
        mImmuneOverlap = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[33] ],0);
        mIsLead = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[34] ],0);
        mIsFemaleLead = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[35] ],0);
        mIsHero = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[36] ],0);
        mUnionProfitID = convertToVector<int64>(aColArr[mapStructFieldToCsvField[37] ],0);
        mQuality = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[38] ],0);
        mAptitude = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[39] ],0);
        mGender = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[40] ],0);
        mNation = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[41] ],0);
        mProfessionIcon = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[42] ],0);
        mProfession = convertToVector<int64>(aColArr[mapStructFieldToCsvField[43] ],0);
        mTargetPriority = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[44] ],0);
        mPromoteID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[45] ],0);
        mPromoteTalentId = convertToVector<int64>(aColArr[mapStructFieldToCsvField[46] ],0);
        mPromoteAttributeId = convertToVector<int64>(aColArr[mapStructFieldToCsvField[47] ],0);
        mHeroStar = convertToVector<int64>(aColArr[mapStructFieldToCsvField[48] ],0);
        mStarUpID = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[49] ],0);
        mStarUpAttr = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[50] ],0);
        mStarChangeHtid = convertToVector<int64>(aColArr[mapStructFieldToCsvField[51] ],0);
        mStarChangeSkill = convertToVector<int64>(aColArr[mapStructFieldToCsvField[52] ],0);
        mAppointmentAptitude = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[53] ],0);
        mHeroBattleZoom = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[54] ],0);
        mTeamHeroPaintingVoice = aColArr[mapStructFieldToCsvField[55] ];
        mManOfTheMatchVoice = aColArr[mapStructFieldToCsvField[56] ];
        mDeadBodyDisappearRule = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[57] ],0);
        mViewBossTimeline = convertToVector<string>(aColArr[mapStructFieldToCsvField[58] ],"");
        mHeroSlotBattleEffectZoom = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[59] ],0);
        mModelIdDefault = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[60] ],0);
        mFavoriteId = convertToVector<int64>(aColArr[mapStructFieldToCsvField[61] ],0);
        mFavoriteDes = convertToVector<int64>(aColArr[mapStructFieldToCsvField[62] ],0);
        mLikeType = convertToVector<int64>(aColArr[mapStructFieldToCsvField[63] ],0);
        mHateType = convertToVector<int64>(aColArr[mapStructFieldToCsvField[64] ],0);
        mFavoriteExpId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[65] ],0);
        mFavoriteStoryTask = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[66] ],0);
        mLive2DResourcePath = aColArr[mapStructFieldToCsvField[67] ];
        mWalkRunSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[68] ],0);
        mHeroForumID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[69] ],0);
        mExclusiveEquipmentId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[70] ],0);
        mCameraMaxRange = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[71] ],0);
        mBossAttrGrowth = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[72] ],0);
        mIsArShow = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[73] ],0);
        mIsHideWhenBorn = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[74] ],0);
        mStarGiveItem = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[75] ],0);
        mTDAttack1 = convertToVector<int64>(aColArr[mapStructFieldToCsvField[76] ],0);
        mTDChainSkillList1 = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[77] ],0);
        mTDAttack2 = convertToVector<int64>(aColArr[mapStructFieldToCsvField[78] ],0);
        mTDChainSkillList2 = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[79] ],0);
        mTDLocationType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[80] ],0);
        mTDNumberOfBlocks = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[81] ],0);
        mTDRangeInfo = convertToVector<int64>(aColArr[mapStructFieldToCsvField[82] ],0);
        mTDCostEnergy = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[83] ],0);
        mTDReviveTime = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[84] ],0);
        mIsAllowGoldTransform = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[85] ],0);
        mGoldTransformGroup = convertToVector<int64>(aColArr[mapStructFieldToCsvField[86] ],0);
        mRebornToRedHeroId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[87] ],0);
        mTowerIsFly = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[88] ],0);
        mHeroHallExtraStar = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[89] ],0);
        mLinkTypeHero = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[90] ],0);
        mIsLinked = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[91] ],0);
        mGoldHeroBreakID = convertToVector<int64>(aColArr[mapStructFieldToCsvField[92] ],0);
        mIsAllowWhiteGold = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[93] ],0);
        mWhiteGoldTransform = convertToVector<int64>(aColArr[mapStructFieldToCsvField[94] ],0);
        mRebornToRedGoldId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[95] ],0);
        mWhiteGoldHeroBreakID = convertToVector<int64>(aColArr[mapStructFieldToCsvField[96] ],0);
        mWhiteGoldTalentID = convertToVector<int64>(aColArr[mapStructFieldToCsvField[97] ],0);
        mIsAllowPurpleGold = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[98] ],0);
        mPurpleGoldTransform = convertToVector<int64>(aColArr[mapStructFieldToCsvField[99] ],0);
        mRebornToWhiteGoldId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[100] ],0);
        mPurpleGoldTalentID = convertToVector<int64>(aColArr[mapStructFieldToCsvField[101] ],0);
        mCPstarID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[102] ],0);
        mCPImage = aColArr[mapStructFieldToCsvField[103] ];
        mIsTestUseWhiteGold = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[104] ],0);
        mDefaultSceneID = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[105] ],0);
        mIsAllowChangeScene = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[106] ],0);
        mIsChainedSoul = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[107] ],0);
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[108] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","ModelId","HeroFragmentID","IsFashion","FashionModelId","HeroName","HeroPositionId","HeroDescribeId","AnimateResourcePath","AnimateResourceHighPath","HeadshotResourcePath","SpineResourcePath","BagImageResourcePath","HandbookImageResourcePath","HeroLihuiResourcePath","HeroNameResourcePath","Starup_NameResourcePath","FrameAnim_SpriteResourcePath","RageSkilHeadNormalshotResourcePath","RageSkilHeadshotResourcePath","SkillID","SkillUnlockProgress","AddtionalSkill","ChainSkillList","LevelUpID","AttributeID","TroopID","TroopLv","Formation","PosWeight","PosType","BodySize","IgnoreCollision","ImmuneOverlap","IsLead","IsFemaleLead","IsHero","UnionProfitID","Quality","Aptitude","Gender","Nation","ProfessionIcon","Profession","TargetPriority","PromoteID","PromoteTalentId","PromoteAttributeId","HeroStar","StarUpID","StarUpAttr","StarChangeHtid","StarChangeSkill","AppointmentAptitude","HeroBattleZoom","TeamHeroPaintingVoice","ManOfTheMatchVoice","DeadBodyDisappearRule","ViewBossTimeline","HeroSlotBattleEffectZoom","ModelIdDefault","FavoriteId","FavoriteDes","LikeType","HateType","FavoriteExpId","FavoriteStoryTask","Live2DResourcePath","WalkRunSpeed","HeroForumID","ExclusiveEquipmentId","CameraMaxRange","BossAttrGrowth","IsArShow","IsHideWhenBorn","StarGiveItem","TDAttack1","TDChainSkillList1","TDAttack2","TDChainSkillList2","TDLocationType","TDNumberOfBlocks","TDRangeInfo","TDCostEnergy","TDReviveTime","IsAllowGoldTransform","GoldTransformGroup","RebornToRedHeroId","TowerIsFly","HeroHallExtraStar","LinkTypeHero","IsLinked","GoldHeroBreakID","IsAllowWhiteGold","WhiteGoldTransform","RebornToRedGoldId","WhiteGoldHeroBreakID","WhiteGoldTalentID","IsAllowPurpleGold","PurpleGoldTransform","RebornToWhiteGoldId","PurpleGoldTalentID","CPstarID","CPImage","IsTestUseWhiteGold","DefaultSceneID","IsAllowChangeScene","IsChainedSoul","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","int","int","int","int","int","int","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","assetpath","int[]","int[]","int[][]","int[][]","int","int","int","int","int","int","int","int","int","int","int","int","int","int[]","int","int","int","int","int","int[]","int","int","int[]","int[]","int[]","int[][]","int[][]","int[]","int[]","int","int","string","string","int","assetpath[]","int","int","int[]","int[]","int[]","int[]","int","int[][]","assetpath","int","int","int","int","int[][]","int","int","int[][]","int[]","int[][]","int[]","int[][]","int","int","int[]","int","int","int","int[]","int","int","int","int","int","int[]","int","int[]","int","int[]","int[]","int","int[]","int","int[]","int","assetpath","int","int","int","int","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[109];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigHero);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetModelId</name>
                <replaceName>ModelId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetModelId() const
    {
        return mModelId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroFragmentID</name>
                <replaceName>HeroFragmentID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroFragmentID() const
    {
        return mHeroFragmentID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsFashion</name>
                <replaceName>IsFashion</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsFashion() const
    {
        return mIsFashion;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFashionModelId</name>
                <replaceName>FashionModelId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetFashionModelId() const
    {
        return mFashionModelId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroName</name>
                <replaceName>HeroName</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroName() const
    {
        return mHeroName;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroPositionId</name>
                <replaceName>HeroPositionId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroPositionId() const
    {
        return mHeroPositionId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroDescribeId</name>
                <replaceName>HeroDescribeId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroDescribeId() const
    {
        return mHeroDescribeId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetAnimateResourcePath</name>
                <replaceName>AnimateResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetAnimateResourcePath() const
    {
        return mAnimateResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetAnimateResourceHighPath</name>
                <replaceName>AnimateResourceHighPath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetAnimateResourceHighPath() const
    {
        return mAnimateResourceHighPath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeadshotResourcePath</name>
                <replaceName>HeadshotResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetHeadshotResourcePath() const
    {
        return mHeadshotResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetSpineResourcePath</name>
                <replaceName>SpineResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetSpineResourcePath() const
    {
        return mSpineResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetBagImageResourcePath</name>
                <replaceName>BagImageResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetBagImageResourcePath() const
    {
        return mBagImageResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHandbookImageResourcePath</name>
                <replaceName>HandbookImageResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetHandbookImageResourcePath() const
    {
        return mHandbookImageResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroLihuiResourcePath</name>
                <replaceName>HeroLihuiResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetHeroLihuiResourcePath() const
    {
        return mHeroLihuiResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroNameResourcePath</name>
                <replaceName>HeroNameResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetHeroNameResourcePath() const
    {
        return mHeroNameResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetStarup_NameResourcePath</name>
                <replaceName>Starup_NameResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetStarup_NameResourcePath() const
    {
        return mStarup_NameResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFrameAnim_SpriteResourcePath</name>
                <replaceName>FrameAnim_SpriteResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetFrameAnim_SpriteResourcePath() const
    {
        return mFrameAnim_SpriteResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetRageSkilHeadNormalshotResourcePath</name>
                <replaceName>RageSkilHeadNormalshotResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetRageSkilHeadNormalshotResourcePath() const
    {
        return mRageSkilHeadNormalshotResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetRageSkilHeadshotResourcePath</name>
                <replaceName>RageSkilHeadshotResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetRageSkilHeadshotResourcePath() const
    {
        return mRageSkilHeadshotResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetSkillID</name>
                <replaceName>SkillID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetSkillID() const
    {
        return mSkillID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetSkillUnlockProgress</name>
                <replaceName>SkillUnlockProgress</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetSkillUnlockProgress() const
    {
        return mSkillUnlockProgress;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetAddtionalSkill</name>
                <replaceName>AddtionalSkill</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetAddtionalSkill() const
    {
        return mAddtionalSkill;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetChainSkillList</name>
                <replaceName>ChainSkillList</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetChainSkillList() const
    {
        return mChainSkillList;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetLevelUpID</name>
                <replaceName>LevelUpID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetLevelUpID() const
    {
        return mLevelUpID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetAttributeID</name>
                <replaceName>AttributeID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetAttributeID() const
    {
        return mAttributeID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTroopID</name>
                <replaceName>TroopID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTroopID() const
    {
        return mTroopID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTroopLv</name>
                <replaceName>TroopLv</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTroopLv() const
    {
        return mTroopLv;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFormation</name>
                <replaceName>Formation</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetFormation() const
    {
        return mFormation;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPosWeight</name>
                <replaceName>PosWeight</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPosWeight() const
    {
        return mPosWeight;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPosType</name>
                <replaceName>PosType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPosType() const
    {
        return mPosType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetBodySize</name>
                <replaceName>BodySize</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBodySize() const
    {
        return mBodySize;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIgnoreCollision</name>
                <replaceName>IgnoreCollision</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIgnoreCollision() const
    {
        return mIgnoreCollision;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetImmuneOverlap</name>
                <replaceName>ImmuneOverlap</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetImmuneOverlap() const
    {
        return mImmuneOverlap;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsLead</name>
                <replaceName>IsLead</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsLead() const
    {
        return mIsLead;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsFemaleLead</name>
                <replaceName>IsFemaleLead</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsFemaleLead() const
    {
        return mIsFemaleLead;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsHero</name>
                <replaceName>IsHero</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsHero() const
    {
        return mIsHero;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetUnionProfitID</name>
                <replaceName>UnionProfitID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetUnionProfitID() const
    {
        return mUnionProfitID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetQuality</name>
                <replaceName>Quality</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetQuality() const
    {
        return mQuality;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetAptitude</name>
                <replaceName>Aptitude</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetAptitude() const
    {
        return mAptitude;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetGender</name>
                <replaceName>Gender</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetGender() const
    {
        return mGender;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetNation</name>
                <replaceName>Nation</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetNation() const
    {
        return mNation;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetProfessionIcon</name>
                <replaceName>ProfessionIcon</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetProfessionIcon() const
    {
        return mProfessionIcon;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetProfession</name>
                <replaceName>Profession</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetProfession() const
    {
        return mProfession;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTargetPriority</name>
                <replaceName>TargetPriority</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTargetPriority() const
    {
        return mTargetPriority;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPromoteID</name>
                <replaceName>PromoteID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPromoteID() const
    {
        return mPromoteID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPromoteTalentId</name>
                <replaceName>PromoteTalentId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetPromoteTalentId() const
    {
        return mPromoteTalentId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPromoteAttributeId</name>
                <replaceName>PromoteAttributeId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetPromoteAttributeId() const
    {
        return mPromoteAttributeId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroStar</name>
                <replaceName>HeroStar</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetHeroStar() const
    {
        return mHeroStar;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetStarUpID</name>
                <replaceName>StarUpID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetStarUpID() const
    {
        return mStarUpID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetStarUpAttr</name>
                <replaceName>StarUpAttr</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetStarUpAttr() const
    {
        return mStarUpAttr;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetStarChangeHtid</name>
                <replaceName>StarChangeHtid</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetStarChangeHtid() const
    {
        return mStarChangeHtid;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetStarChangeSkill</name>
                <replaceName>StarChangeSkill</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetStarChangeSkill() const
    {
        return mStarChangeSkill;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetAppointmentAptitude</name>
                <replaceName>AppointmentAptitude</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetAppointmentAptitude() const
    {
        return mAppointmentAptitude;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroBattleZoom</name>
                <replaceName>HeroBattleZoom</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroBattleZoom() const
    {
        return mHeroBattleZoom;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTeamHeroPaintingVoice</name>
                <replaceName>TeamHeroPaintingVoice</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetTeamHeroPaintingVoice() const
    {
        return mTeamHeroPaintingVoice;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetManOfTheMatchVoice</name>
                <replaceName>ManOfTheMatchVoice</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetManOfTheMatchVoice() const
    {
        return mManOfTheMatchVoice;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetDeadBodyDisappearRule</name>
                <replaceName>DeadBodyDisappearRule</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDeadBodyDisappearRule() const
    {
        return mDeadBodyDisappearRule;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetViewBossTimeline</name>
                <replaceName>ViewBossTimeline</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<string>& GetViewBossTimeline() const
    {
        return mViewBossTimeline;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroSlotBattleEffectZoom</name>
                <replaceName>HeroSlotBattleEffectZoom</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroSlotBattleEffectZoom() const
    {
        return mHeroSlotBattleEffectZoom;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetModelIdDefault</name>
                <replaceName>ModelIdDefault</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetModelIdDefault() const
    {
        return mModelIdDefault;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFavoriteId</name>
                <replaceName>FavoriteId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetFavoriteId() const
    {
        return mFavoriteId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFavoriteDes</name>
                <replaceName>FavoriteDes</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetFavoriteDes() const
    {
        return mFavoriteDes;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetLikeType</name>
                <replaceName>LikeType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetLikeType() const
    {
        return mLikeType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHateType</name>
                <replaceName>HateType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetHateType() const
    {
        return mHateType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFavoriteExpId</name>
                <replaceName>FavoriteExpId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetFavoriteExpId() const
    {
        return mFavoriteExpId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetFavoriteStoryTask</name>
                <replaceName>FavoriteStoryTask</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetFavoriteStoryTask() const
    {
        return mFavoriteStoryTask;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetLive2DResourcePath</name>
                <replaceName>Live2DResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetLive2DResourcePath() const
    {
        return mLive2DResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetWalkRunSpeed</name>
                <replaceName>WalkRunSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetWalkRunSpeed() const
    {
        return mWalkRunSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroForumID</name>
                <replaceName>HeroForumID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroForumID() const
    {
        return mHeroForumID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetExclusiveEquipmentId</name>
                <replaceName>ExclusiveEquipmentId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetExclusiveEquipmentId() const
    {
        return mExclusiveEquipmentId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetCameraMaxRange</name>
                <replaceName>CameraMaxRange</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCameraMaxRange() const
    {
        return mCameraMaxRange;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetBossAttrGrowth</name>
                <replaceName>BossAttrGrowth</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetBossAttrGrowth() const
    {
        return mBossAttrGrowth;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsArShow</name>
                <replaceName>IsArShow</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsArShow() const
    {
        return mIsArShow;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsHideWhenBorn</name>
                <replaceName>IsHideWhenBorn</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsHideWhenBorn() const
    {
        return mIsHideWhenBorn;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetStarGiveItem</name>
                <replaceName>StarGiveItem</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetStarGiveItem() const
    {
        return mStarGiveItem;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDAttack1</name>
                <replaceName>TDAttack1</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetTDAttack1() const
    {
        return mTDAttack1;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDChainSkillList1</name>
                <replaceName>TDChainSkillList1</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetTDChainSkillList1() const
    {
        return mTDChainSkillList1;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDAttack2</name>
                <replaceName>TDAttack2</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetTDAttack2() const
    {
        return mTDAttack2;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDChainSkillList2</name>
                <replaceName>TDChainSkillList2</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetTDChainSkillList2() const
    {
        return mTDChainSkillList2;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDLocationType</name>
                <replaceName>TDLocationType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTDLocationType() const
    {
        return mTDLocationType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDNumberOfBlocks</name>
                <replaceName>TDNumberOfBlocks</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTDNumberOfBlocks() const
    {
        return mTDNumberOfBlocks;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDRangeInfo</name>
                <replaceName>TDRangeInfo</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetTDRangeInfo() const
    {
        return mTDRangeInfo;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDCostEnergy</name>
                <replaceName>TDCostEnergy</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTDCostEnergy() const
    {
        return mTDCostEnergy;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTDReviveTime</name>
                <replaceName>TDReviveTime</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTDReviveTime() const
    {
        return mTDReviveTime;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsAllowGoldTransform</name>
                <replaceName>IsAllowGoldTransform</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsAllowGoldTransform() const
    {
        return mIsAllowGoldTransform;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetGoldTransformGroup</name>
                <replaceName>GoldTransformGroup</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetGoldTransformGroup() const
    {
        return mGoldTransformGroup;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetRebornToRedHeroId</name>
                <replaceName>RebornToRedHeroId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRebornToRedHeroId() const
    {
        return mRebornToRedHeroId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetTowerIsFly</name>
                <replaceName>TowerIsFly</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetTowerIsFly() const
    {
        return mTowerIsFly;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetHeroHallExtraStar</name>
                <replaceName>HeroHallExtraStar</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetHeroHallExtraStar() const
    {
        return mHeroHallExtraStar;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetLinkTypeHero</name>
                <replaceName>LinkTypeHero</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetLinkTypeHero() const
    {
        return mLinkTypeHero;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsLinked</name>
                <replaceName>IsLinked</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsLinked() const
    {
        return mIsLinked;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetGoldHeroBreakID</name>
                <replaceName>GoldHeroBreakID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetGoldHeroBreakID() const
    {
        return mGoldHeroBreakID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsAllowWhiteGold</name>
                <replaceName>IsAllowWhiteGold</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsAllowWhiteGold() const
    {
        return mIsAllowWhiteGold;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetWhiteGoldTransform</name>
                <replaceName>WhiteGoldTransform</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetWhiteGoldTransform() const
    {
        return mWhiteGoldTransform;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetRebornToRedGoldId</name>
                <replaceName>RebornToRedGoldId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRebornToRedGoldId() const
    {
        return mRebornToRedGoldId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetWhiteGoldHeroBreakID</name>
                <replaceName>WhiteGoldHeroBreakID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetWhiteGoldHeroBreakID() const
    {
        return mWhiteGoldHeroBreakID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetWhiteGoldTalentID</name>
                <replaceName>WhiteGoldTalentID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetWhiteGoldTalentID() const
    {
        return mWhiteGoldTalentID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsAllowPurpleGold</name>
                <replaceName>IsAllowPurpleGold</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsAllowPurpleGold() const
    {
        return mIsAllowPurpleGold;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPurpleGoldTransform</name>
                <replaceName>PurpleGoldTransform</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetPurpleGoldTransform() const
    {
        return mPurpleGoldTransform;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetRebornToWhiteGoldId</name>
                <replaceName>RebornToWhiteGoldId</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRebornToWhiteGoldId() const
    {
        return mRebornToWhiteGoldId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetPurpleGoldTalentID</name>
                <replaceName>PurpleGoldTalentID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetPurpleGoldTalentID() const
    {
        return mPurpleGoldTalentID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetCPstarID</name>
                <replaceName>CPstarID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCPstarID() const
    {
        return mCPstarID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetCPImage</name>
                <replaceName>CPImage</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetCPImage() const
    {
        return mCPImage;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsTestUseWhiteGold</name>
                <replaceName>IsTestUseWhiteGold</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsTestUseWhiteGold() const
    {
        return mIsTestUseWhiteGold;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetDefaultSceneID</name>
                <replaceName>DefaultSceneID</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetDefaultSceneID() const
    {
        return mDefaultSceneID;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsAllowChangeScene</name>
                <replaceName>IsAllowChangeScene</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsAllowChangeScene() const
    {
        return mIsAllowChangeScene;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetIsChainedSoul</name>
                <replaceName>IsChainedSoul</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetIsChainedSoul() const
    {
        return mIsChainedSoul;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHero</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mModelId;
    int64 mHeroFragmentID;
    int64 mIsFashion;
    int64 mFashionModelId;
    int64 mHeroName;
    int64 mHeroPositionId;
    int64 mHeroDescribeId;
    string mAnimateResourcePath;
    string mAnimateResourceHighPath;
    string mHeadshotResourcePath;
    string mSpineResourcePath;
    string mBagImageResourcePath;
    string mHandbookImageResourcePath;
    string mHeroLihuiResourcePath;
    string mHeroNameResourcePath;
    string mStarup_NameResourcePath;
    string mFrameAnim_SpriteResourcePath;
    string mRageSkilHeadNormalshotResourcePath;
    string mRageSkilHeadshotResourcePath;
    vector<int64> mSkillID;
    vector<int64> mSkillUnlockProgress;
    vector<vector<int64> > mAddtionalSkill;
    vector<vector<int64> > mChainSkillList;
    int64 mLevelUpID;
    int64 mAttributeID;
    int64 mTroopID;
    int64 mTroopLv;
    int64 mFormation;
    int64 mPosWeight;
    int64 mPosType;
    int64 mBodySize;
    int64 mIgnoreCollision;
    int64 mImmuneOverlap;
    int64 mIsLead;
    int64 mIsFemaleLead;
    int64 mIsHero;
    vector<int64> mUnionProfitID;
    int64 mQuality;
    int64 mAptitude;
    int64 mGender;
    int64 mNation;
    int64 mProfessionIcon;
    vector<int64> mProfession;
    int64 mTargetPriority;
    int64 mPromoteID;
    vector<int64> mPromoteTalentId;
    vector<int64> mPromoteAttributeId;
    vector<int64> mHeroStar;
    vector<vector<int64> > mStarUpID;
    vector<vector<int64> > mStarUpAttr;
    vector<int64> mStarChangeHtid;
    vector<int64> mStarChangeSkill;
    int64 mAppointmentAptitude;
    int64 mHeroBattleZoom;
    string mTeamHeroPaintingVoice;
    string mManOfTheMatchVoice;
    int64 mDeadBodyDisappearRule;
    vector<string> mViewBossTimeline;
    int64 mHeroSlotBattleEffectZoom;
    int64 mModelIdDefault;
    vector<int64> mFavoriteId;
    vector<int64> mFavoriteDes;
    vector<int64> mLikeType;
    vector<int64> mHateType;
    int64 mFavoriteExpId;
    vector<vector<int64> > mFavoriteStoryTask;
    string mLive2DResourcePath;
    int64 mWalkRunSpeed;
    int64 mHeroForumID;
    int64 mExclusiveEquipmentId;
    int64 mCameraMaxRange;
    vector<vector<int64> > mBossAttrGrowth;
    int64 mIsArShow;
    int64 mIsHideWhenBorn;
    vector<vector<int64> > mStarGiveItem;
    vector<int64> mTDAttack1;
    vector<vector<int64> > mTDChainSkillList1;
    vector<int64> mTDAttack2;
    vector<vector<int64> > mTDChainSkillList2;
    int64 mTDLocationType;
    int64 mTDNumberOfBlocks;
    vector<int64> mTDRangeInfo;
    int64 mTDCostEnergy;
    int64 mTDReviveTime;
    int64 mIsAllowGoldTransform;
    vector<int64> mGoldTransformGroup;
    int64 mRebornToRedHeroId;
    int64 mTowerIsFly;
    int64 mHeroHallExtraStar;
    int64 mLinkTypeHero;
    int64 mIsLinked;
    vector<int64> mGoldHeroBreakID;
    int64 mIsAllowWhiteGold;
    vector<int64> mWhiteGoldTransform;
    int64 mRebornToRedGoldId;
    vector<int64> mWhiteGoldHeroBreakID;
    vector<int64> mWhiteGoldTalentID;
    int64 mIsAllowPurpleGold;
    vector<int64> mPurpleGoldTransform;
    int64 mRebornToWhiteGoldId;
    vector<int64> mPurpleGoldTalentID;
    int64 mCPstarID;
    string mCPImage;
    int64 mIsTestUseWhiteGold;
    int64 mDefaultSceneID;
    int64 mIsAllowChangeScene;
    int64 mIsChainedSoul;
    int64 mVersion;

};


class ConfigHeroAttribute : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigHeroAttribute failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigHeroAttribute. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigHeroAttribute failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigHeroAttribute failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 44 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:44 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mBaseCommand = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mBaseStrength = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[2] ],0);
        mBaseIntelligence = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[3] ],0);
        mBasePolity = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[4] ],0);
        mBaseFashion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[5] ],0);
        mBaseCritical = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[6] ],0);
        mBasePhysicalHit = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[7] ],0);
        mBaseMagicHit = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[8] ],0);
        mBaseDodge = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[9] ],0);
        mExemption = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[10] ],0);
        mBaseBlock = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[11] ],0);
        mBaseToughness = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[12] ],0);
        mBaseCriticalMultiple = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[13] ],0);
        mBaseSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[14] ],0);
        mBaseHp = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[15] ],0);
        mBasePhysicalAttack = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[16] ],0);
        mBasePhysicalDefend = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[17] ],0);
        mBaseMagicAttack = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[18] ],0);
        mBaseMagicDefend = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[19] ],0);
        mGrowHp = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[20] ],0);
        mGrowPhysicalAttack = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[21] ],0);
        mGrowPhysicalDefend = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[22] ],0);
        mGrowMagicAttack = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[23] ],0);
        mGrowMagicDefend = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[24] ],0);
        mPhysicalAttackTalent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[25] ],0);
        mPhysicalDefendTalent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[26] ],0);
        mMagicAttackTalent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[27] ],0);
        mMagicDefendTalent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[28] ],0);
        mMarchSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[29] ],0);
        mPVPMarchSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[30] ],0);
        mInvestigationValue = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[31] ],0);
        mCityAttackValue = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[32] ],0);
        mMarchSpeedExtra = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[33] ],0);
        mProAttTalent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[34] ],0);
        mProDefTalent = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[35] ],0);
        mUniversalHitProb = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[36] ],0);
        mUniversalDodgeProb = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[37] ],0);
        mUniversalBlockProb = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[38] ],0);
        mPVPPercentAdd = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[39] ],0);
        mPVPPercentSub = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[40] ],0);
        mPVEPercentAdd = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[41] ],0);
        mPVEPercentSub = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[42] ],0);
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[43] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","BaseCommand","BaseStrength","BaseIntelligence","BasePolity","BaseFashion","BaseCritical","BasePhysicalHit","BaseMagicHit","BaseDodge","Exemption","BaseBlock","BaseToughness","BaseCriticalMultiple","BaseSpeed","BaseHp","BasePhysicalAttack","BasePhysicalDefend","BaseMagicAttack","BaseMagicDefend","GrowHp","GrowPhysicalAttack","GrowPhysicalDefend","GrowMagicAttack","GrowMagicDefend","PhysicalAttackTalent","PhysicalDefendTalent","MagicAttackTalent","MagicDefendTalent","MarchSpeed","PVPMarchSpeed","InvestigationValue","CityAttackValue","MarchSpeedExtra","ProAttTalent","ProDefTalent","UniversalHitProb","UniversalDodgeProb","UniversalBlockProb","PVPPercentAdd","PVPPercentSub","PVEPercentAdd","PVEPercentSub","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[44];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigHeroAttribute);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseCommand</name>
                <replaceName>BaseCommand</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseCommand() const
    {
        return mBaseCommand;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseStrength</name>
                <replaceName>BaseStrength</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseStrength() const
    {
        return mBaseStrength;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseIntelligence</name>
                <replaceName>BaseIntelligence</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseIntelligence() const
    {
        return mBaseIntelligence;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBasePolity</name>
                <replaceName>BasePolity</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBasePolity() const
    {
        return mBasePolity;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseFashion</name>
                <replaceName>BaseFashion</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseFashion() const
    {
        return mBaseFashion;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseCritical</name>
                <replaceName>BaseCritical</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseCritical() const
    {
        return mBaseCritical;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBasePhysicalHit</name>
                <replaceName>BasePhysicalHit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBasePhysicalHit() const
    {
        return mBasePhysicalHit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseMagicHit</name>
                <replaceName>BaseMagicHit</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseMagicHit() const
    {
        return mBaseMagicHit;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseDodge</name>
                <replaceName>BaseDodge</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseDodge() const
    {
        return mBaseDodge;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetExemption</name>
                <replaceName>Exemption</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetExemption() const
    {
        return mExemption;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseBlock</name>
                <replaceName>BaseBlock</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseBlock() const
    {
        return mBaseBlock;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseToughness</name>
                <replaceName>BaseToughness</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseToughness() const
    {
        return mBaseToughness;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseCriticalMultiple</name>
                <replaceName>BaseCriticalMultiple</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseCriticalMultiple() const
    {
        return mBaseCriticalMultiple;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseSpeed</name>
                <replaceName>BaseSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseSpeed() const
    {
        return mBaseSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseHp</name>
                <replaceName>BaseHp</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseHp() const
    {
        return mBaseHp;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBasePhysicalAttack</name>
                <replaceName>BasePhysicalAttack</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBasePhysicalAttack() const
    {
        return mBasePhysicalAttack;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBasePhysicalDefend</name>
                <replaceName>BasePhysicalDefend</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBasePhysicalDefend() const
    {
        return mBasePhysicalDefend;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseMagicAttack</name>
                <replaceName>BaseMagicAttack</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseMagicAttack() const
    {
        return mBaseMagicAttack;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetBaseMagicDefend</name>
                <replaceName>BaseMagicDefend</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseMagicDefend() const
    {
        return mBaseMagicDefend;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetGrowHp</name>
                <replaceName>GrowHp</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetGrowHp() const
    {
        return mGrowHp;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetGrowPhysicalAttack</name>
                <replaceName>GrowPhysicalAttack</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetGrowPhysicalAttack() const
    {
        return mGrowPhysicalAttack;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetGrowPhysicalDefend</name>
                <replaceName>GrowPhysicalDefend</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetGrowPhysicalDefend() const
    {
        return mGrowPhysicalDefend;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetGrowMagicAttack</name>
                <replaceName>GrowMagicAttack</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetGrowMagicAttack() const
    {
        return mGrowMagicAttack;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetGrowMagicDefend</name>
                <replaceName>GrowMagicDefend</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetGrowMagicDefend() const
    {
        return mGrowMagicDefend;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPhysicalAttackTalent</name>
                <replaceName>PhysicalAttackTalent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPhysicalAttackTalent() const
    {
        return mPhysicalAttackTalent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPhysicalDefendTalent</name>
                <replaceName>PhysicalDefendTalent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPhysicalDefendTalent() const
    {
        return mPhysicalDefendTalent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetMagicAttackTalent</name>
                <replaceName>MagicAttackTalent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMagicAttackTalent() const
    {
        return mMagicAttackTalent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetMagicDefendTalent</name>
                <replaceName>MagicDefendTalent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMagicDefendTalent() const
    {
        return mMagicDefendTalent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetMarchSpeed</name>
                <replaceName>MarchSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMarchSpeed() const
    {
        return mMarchSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPVPMarchSpeed</name>
                <replaceName>PVPMarchSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPVPMarchSpeed() const
    {
        return mPVPMarchSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetInvestigationValue</name>
                <replaceName>InvestigationValue</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetInvestigationValue() const
    {
        return mInvestigationValue;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetCityAttackValue</name>
                <replaceName>CityAttackValue</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCityAttackValue() const
    {
        return mCityAttackValue;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetMarchSpeedExtra</name>
                <replaceName>MarchSpeedExtra</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetMarchSpeedExtra() const
    {
        return mMarchSpeedExtra;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetProAttTalent</name>
                <replaceName>ProAttTalent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetProAttTalent() const
    {
        return mProAttTalent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetProDefTalent</name>
                <replaceName>ProDefTalent</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetProDefTalent() const
    {
        return mProDefTalent;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetUniversalHitProb</name>
                <replaceName>UniversalHitProb</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetUniversalHitProb() const
    {
        return mUniversalHitProb;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetUniversalDodgeProb</name>
                <replaceName>UniversalDodgeProb</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetUniversalDodgeProb() const
    {
        return mUniversalDodgeProb;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetUniversalBlockProb</name>
                <replaceName>UniversalBlockProb</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetUniversalBlockProb() const
    {
        return mUniversalBlockProb;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPVPPercentAdd</name>
                <replaceName>PVPPercentAdd</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPVPPercentAdd() const
    {
        return mPVPPercentAdd;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPVPPercentSub</name>
                <replaceName>PVPPercentSub</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPVPPercentSub() const
    {
        return mPVPPercentSub;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPVEPercentAdd</name>
                <replaceName>PVEPercentAdd</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPVEPercentAdd() const
    {
        return mPVEPercentAdd;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetPVEPercentSub</name>
                <replaceName>PVEPercentSub</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetPVEPercentSub() const
    {
        return mPVEPercentSub;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigHeroAttribute</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mBaseCommand;
    int64 mBaseStrength;
    int64 mBaseIntelligence;
    int64 mBasePolity;
    int64 mBaseFashion;
    int64 mBaseCritical;
    int64 mBasePhysicalHit;
    int64 mBaseMagicHit;
    int64 mBaseDodge;
    int64 mExemption;
    int64 mBaseBlock;
    int64 mBaseToughness;
    int64 mBaseCriticalMultiple;
    int64 mBaseSpeed;
    int64 mBaseHp;
    int64 mBasePhysicalAttack;
    int64 mBasePhysicalDefend;
    int64 mBaseMagicAttack;
    int64 mBaseMagicDefend;
    int64 mGrowHp;
    int64 mGrowPhysicalAttack;
    int64 mGrowPhysicalDefend;
    int64 mGrowMagicAttack;
    int64 mGrowMagicDefend;
    int64 mPhysicalAttackTalent;
    int64 mPhysicalDefendTalent;
    int64 mMagicAttackTalent;
    int64 mMagicDefendTalent;
    int64 mMarchSpeed;
    int64 mPVPMarchSpeed;
    int64 mInvestigationValue;
    int64 mCityAttackValue;
    int64 mMarchSpeedExtra;
    int64 mProAttTalent;
    int64 mProDefTalent;
    int64 mUniversalHitProb;
    int64 mUniversalDodgeProb;
    int64 mUniversalBlockProb;
    int64 mPVPPercentAdd;
    int64 mPVPPercentSub;
    int64 mPVEPercentAdd;
    int64 mPVEPercentSub;
    int64 mVersion;

};


class ConfigTroop : public CsvStructBase
{
public:

	int InitFieldMap(const vector<string>& aCsvFieldNameArr, const vector<string>& aCsvFieldTypeArr)
	{
		const vector<string>& fieldNameArr = GetFieldNameArr();
		const vector<string>& fieldTypeArr = GetFieldTypeArr();
		if (aCsvFieldNameArr.size() != aCsvFieldTypeArr.size())
		{
			LOG_FATAL("read ConfigTroop failed. csvFieldNameNum:%d typeNum:%d", aCsvFieldNameArr.size(), aCsvFieldTypeArr.size());
			return -1;
		}
		if (aCsvFieldNameArr.size() < fieldNameArr.size())
		{
			LOG_FATAL("invalid csv ConfigTroop. numOfCol:%d,  need:%d", aCsvFieldNameArr.size(), fieldNameArr.size());
			return -1;
		}
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
		for (int i = 0; i < fieldNameArr.size(); i++)
		{
			mapStructFieldToCsvField[i] = -1;
			for (int j = 0; j < aCsvFieldNameArr.size(); j++)
			{
				if (fieldNameArr[i] == aCsvFieldNameArr[j])
				{
					if ((fieldTypeArr[i] != aCsvFieldTypeArr[j]) && (fieldTypeArr[i] != "assetpath") && (fieldTypeArr[i] != "sceneconf[]"))
					{
						LOG_FATAL("read ConfigTroop failed. field:%s type not match. code:%s csv:%s", fieldNameArr[i].c_str(), fieldTypeArr[i].c_str(), aCsvFieldTypeArr[i].c_str() );
						return -1;
					}
					mapStructFieldToCsvField[i] = j;
					break;
				}
			}
			if (mapStructFieldToCsvField[i] < 0)
			{
				LOG_FATAL("read ConfigTroop failed. not found field:%s in csv:%s", fieldNameArr[i].c_str(), vectorToString<string>(aCsvFieldNameArr).c_str());
				return -1;
			}
		}
		return 0;
	}
    int InitFromCsvRow(const vector<string>& aColArr )
    {
        if( aColArr.size() < 21 )
        {
            LOG_FATAL("invalid csv. numOfCol:%d,  need:21 ", aColArr.size());
            return -1;
        }
		int* mapStructFieldToCsvField = GetMapStructFieldToCsvField();
        mId = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[0] ],0);
        mSoldierName = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[1] ],0);
        mAnimateResourcePath = aColArr[mapStructFieldToCsvField[2] ];
        mSoldierType = aColArr[mapStructFieldToCsvField[3] ];
        mEnemyMaterial = aColArr[mapStructFieldToCsvField[4] ];
        mType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[5] ],0);
        mBaseFashion = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[6] ],0);
        mBaseCritical = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[7] ],0);
        mAttackRange = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[8] ],0);
        mBodySize = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[9] ],0);
        mSkillType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[10] ],0);
        mRemoteType = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[11] ],0);
        mRemoteEffect = aColArr[mapStructFieldToCsvField[12] ];
        mRemoteSpeed = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[13] ],0);
        mAttackCd = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[14] ],0);
        mConscription = convertToVector<int64>(aColArr[mapStructFieldToCsvField[15] ],0);
        mReturnRes = convertToVector2<int64>(aColArr[mapStructFieldToCsvField[16] ],0);
        mCurrencyAccelerate = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[17] ],0);
        mWeight = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[18] ],0);
        mDeathrate1 = convertToVector<int64>(aColArr[mapStructFieldToCsvField[19] ],0);
        mVersion = convertFromStr<int64>(aColArr[mapStructFieldToCsvField[20] ],0);

        return 0;
    }

    static const vector<string>& GetFieldNameArr()
    {                
        static vector<string> vectorFieldName({"Id","SoldierName","AnimateResourcePath","SoldierType","EnemyMaterial","Type","BaseFashion","BaseCritical","AttackRange","BodySize","SkillType","RemoteType","RemoteEffect","RemoteSpeed","AttackCd","Conscription","ReturnRes","CurrencyAccelerate","Weight","Deathrate1","Version"});
        return vectorFieldName;
    }
    static const vector<string>& GetFieldTypeArr()
    {        
        static vector<string> vectorFieldType({"int","int","assetpath","assetpath","assetpath","int","int[][]","int","int","int","int","int","assetpath","int","int","int[]","int[][]","int","int","int[]","int"});
        return vectorFieldType;
    }
	static int* GetMapStructFieldToCsvField()
	{
		static int mapStructFieldToCsvField[21];
		return mapStructFieldToCsvField;
	}
	const char* GetTypeIdName()
	{
		const type_info& info = typeid(ConfigTroop);
		return info.name();
	}
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetId</name>
                <replaceName>Id</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetId() const
    {
        return mId;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetSoldierName</name>
                <replaceName>SoldierName</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSoldierName() const
    {
        return mSoldierName;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetAnimateResourcePath</name>
                <replaceName>AnimateResourcePath</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetAnimateResourcePath() const
    {
        return mAnimateResourcePath;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetSoldierType</name>
                <replaceName>SoldierType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetSoldierType() const
    {
        return mSoldierType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetEnemyMaterial</name>
                <replaceName>EnemyMaterial</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetEnemyMaterial() const
    {
        return mEnemyMaterial;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetType</name>
                <replaceName>Type</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetType() const
    {
        return mType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetBaseFashion</name>
                <replaceName>BaseFashion</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetBaseFashion() const
    {
        return mBaseFashion;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetBaseCritical</name>
                <replaceName>BaseCritical</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBaseCritical() const
    {
        return mBaseCritical;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetAttackRange</name>
                <replaceName>AttackRange</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetAttackRange() const
    {
        return mAttackRange;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetBodySize</name>
                <replaceName>BodySize</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetBodySize() const
    {
        return mBodySize;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetSkillType</name>
                <replaceName>SkillType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetSkillType() const
    {
        return mSkillType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetRemoteType</name>
                <replaceName>RemoteType</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRemoteType() const
    {
        return mRemoteType;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetRemoteEffect</name>
                <replaceName>RemoteEffect</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const string& GetRemoteEffect() const
    {
        return mRemoteEffect;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetRemoteSpeed</name>
                <replaceName>RemoteSpeed</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetRemoteSpeed() const
    {
        return mRemoteSpeed;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetAttackCd</name>
                <replaceName>AttackCd</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetAttackCd() const
    {
        return mAttackCd;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetConscription</name>
                <replaceName>Conscription</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetConscription() const
    {
        return mConscription;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetReturnRes</name>
                <replaceName>ReturnRes</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<vector<int64> >& GetReturnRes() const
    {
        return mReturnRes;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetCurrencyAccelerate</name>
                <replaceName>CurrencyAccelerate</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetCurrencyAccelerate() const
    {
        return mCurrencyAccelerate;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetWeight</name>
                <replaceName>Weight</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetWeight() const
    {
        return mWeight;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetDeathrate1</name>
                <replaceName>Deathrate1</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline const vector<int64>& GetDeathrate1() const
    {
        return mDeathrate1;
    } 
    
    /*FOR2LUA
        <Record>
            <name>ConfigTroop</name>
            <Function>
                <name>GetVersion</name>
                <replaceName>Version</replaceName>
                <handler>descripter = csv_cpp()</handler>  
                </Function>
        </Record>
    FOR2LUA*/
    inline int64 GetVersion() const
    {
        return mVersion;
    } 

private:
	
    int64 mId;
    int64 mSoldierName;
    string mAnimateResourcePath;
    string mSoldierType;
    string mEnemyMaterial;
    int64 mType;
    vector<vector<int64> > mBaseFashion;
    int64 mBaseCritical;
    int64 mAttackRange;
    int64 mBodySize;
    int64 mSkillType;
    int64 mRemoteType;
    string mRemoteEffect;
    int64 mRemoteSpeed;
    int64 mAttackCd;
    vector<int64> mConscription;
    vector<vector<int64> > mReturnRes;
    int64 mCurrencyAccelerate;
    int64 mWeight;
    vector<int64> mDeathrate1;
    int64 mVersion;

};



class ConfStructHelper
{
public:
    static CsvStructBase* NewStruct(const char* aTableName)
    {
        if( strcmp(aTableName, "") == 0 )
        {
            return NULL;
        }
        if( strcmp(aTableName, "ConfigAttribute") == 0 )
        {
            return new ConfigAttribute();
        }
        if( strcmp(aTableName, "ConfigBattleConfig") == 0 )
        {
            return new ConfigBattleConfig();
        }
        if( strcmp(aTableName, "ConfigDestructiveObjects") == 0 )
        {
            return new ConfigDestructiveObjects();
        }
        if( strcmp(aTableName, "ConfigDestructiveObjectsEvent") == 0 )
        {
            return new ConfigDestructiveObjectsEvent();
        }
        if( strcmp(aTableName, "ConfigHero") == 0 )
        {
            return new ConfigHero();
        }
        if( strcmp(aTableName, "ConfigHeroAttribute") == 0 )
        {
            return new ConfigHeroAttribute();
        }
        if( strcmp(aTableName, "ConfigTroop") == 0 )
        {
            return new ConfigTroop();
        }

        return NULL;
    }

};
