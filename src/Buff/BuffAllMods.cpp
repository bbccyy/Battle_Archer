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
* @brief Buff中构造BuffMod的方法
*
**/

#include "Buff/Mod/BuffModAbsorbDamage.h"
#include "Buff/Mod/BuffModAttackSpeed.h"
#include "Buff/Mod/BuffModAddSkill.h"
#include "Buff/Mod/BuffModProperty.h"
#include "Buff/Mod/BuffModChgArcherSkill.h"

#include "BuffAllMods.h"
#include "Entity/Unit.h"


BuffModPropertyEntry& AddModPropertyEntry(const pb::BuffDataModel& aData, int const aLevel, EAttribute const aType, vector<BuffModPropertyEntry>& aArr)
{
    auto entry = BuffModPropertyEntry();
    entry.mAdd = int64(aData.valuegrowth()) * aLevel +aData.valueparma();
    entry.mPercent = int64(aData.percentgrowth()) * aLevel + aData.percentparam();
    entry.mProperty = aType;
	entry.mValue = 0;
    aArr.push_back(entry);
    return aArr.back();
}

BuffModPropertyEntry& AddModPropertyEntry(const pb::BuffModArmAttrAdd& aData, int const aLevel, vector<BuffModPropertyEntry>& aArr)
{
	auto entry = BuffModPropertyEntry();
	entry.mAdd = int64(aData.levelparam()) * aLevel;
	entry.mPercent = int64(aData.percentparam());
	entry.mSourceProperty = static_cast<EAttribute>(aData.attrsource());
	entry.mProperty = static_cast<EAttribute>(aData.attrtarget());
	aArr.push_back(entry);
	return aArr.back();
}

BuffModPropertyEntry& AddModPropertyEntry(EAttribute const aType, vector<BuffModPropertyEntry>& aArr)
{
	auto entry = BuffModPropertyEntry();
	entry.mAdd = 0;
	entry.mPercent = 0;
	entry.mSourceProperty = aType;
	entry.mProperty = aType;
	aArr.push_back(entry);
	return aArr.back();
}

void AddModPropertyData(BuffSubType aType, EAttribute aAttr, int64 aValue, int64 aValueGrowth, int const aLevel, vector<ChangeDataByBuffSub>& aArr)
{
	auto data = ChangeDataByBuffSub();
	data.mType = aType;
	data.mAttr = aAttr;
	data.mValue = aValue + aValueGrowth * aLevel;
	aArr.push_back(data);
}

void Buff::AddModsByConf(const SharedPtr<Unit>& aUtilizer, const SharedPtr<Buff>& aBuff, int const aLevelFactor, const BuffData* aBuffConf)
{
	if (aBuffConf->buffmodabsorbdamageconfig().active())
	{//吸收伤害 
		const auto& conf = aBuffConf->buffmodabsorbdamageconfig();
		auto* m = CreateMod<BuffModAbsorbDamage>(aBuff);
		auto& p = m->mParams;
		p.mThreshold = 0;
		if (conf.absorbcalculatetype() == int(BuffAbsorbDamageValueType::FixValue))
		{
			p.mAbsorbLimit = conf.valueparma() + int64(conf.valuegrowth()) * aLevelFactor;
		}
		else
		{
			auto pecent = conf.attributepercenteparam() + conf.attributepercentegrowth() * aLevelFactor;
			Unit* attrUnit = conf.attributeoriginal() == int(BuffAttrSource::Owner) ? mOwner.Get() : mSourceUtilizer.Get();
			p.mAbsorbLimit = GetUnitAttr(attrUnit, static_cast<BuffAttrId>(conf.attributetype())) * pecent / DENOM;
		}
		if (p.mAbsorbLimit < 0)
		{
			LOG_WARN("Invalid BuffModAbsorbDamage, AbsorbLimit < 0, buffId = %d", aBuff->GetId());
			p.mAbsorbLimit = 1;
		}
		p.mAbsorbHeal = conf.iscureself() > 0;
		p.mHealPercent = conf.percentparam() + conf.percentgrowth() * aLevelFactor;
		p.mType = static_cast<ShieldType>(conf.absorbtype());
		if (p.mType == ShieldType::UniversalCount)
		{
			p.mCount = conf.absorbcount();
			p.mThreshold = conf.threshold();
		}
		m->Init(BuffSubType::AbsorbDamage, *aBuff, conf.delaytime());
	}
    if(aBuffConf->buffmodpropertyconfig().active())
    {//战斗属性改变 
        const auto& conf = aBuffConf->buffmodpropertyconfig();
        auto* m = CreateMod<BuffModProperty>(aBuff);
        auto& p = m->mParams;
        for (auto& property : conf.dataarr())
        {
            if (property.type() == static_cast<int>(EAttribute::HpBase))
            {//改变生命上限 
                auto& data = property.data();
                p.mMaxHpAdd = int64(data.valuegrowth()) * aLevelFactor + data.valueparma();
                p.mMaxHpPercent = int64(data.percentgrowth()) * aLevelFactor + data.percentparam();
                p.mHpChangePercent = int64(conf.lifeaddpercent());
            }
			else
			{
				AddModPropertyEntry(property.data(), aLevelFactor, static_cast<EAttribute>(property.type()), p.mEntries);
			}
        }
        m->Init(BuffSubType::ChangeProperty, *aBuff, conf.delaytime());
    }
    if (aBuffConf->buffmodattackspeedconfig().active())
    {//改变攻速 
        const auto& conf = aBuffConf->buffmodattackspeedconfig();
        auto* m = CreateMod<BuffModAttackSpeed>(aBuff);
        auto& p = m->mParams;
        p.mPercent = conf.percentparam() + conf.percentgrowth() * aLevelFactor;
        m->Init(BuffSubType::AttackSpeedUp, *aBuff, conf.delaytime());
    }
	if (aBuffConf->buffmodbattlearchermodifyconfig().active())
	{//改变ArcherSkill
		const auto& conf = aBuffConf->buffmodbattlearchermodifyconfig();
		auto* m = CreateMod<BuffModChgArcherSkill>(aBuff);
		auto& p = m->mParams;
		for (int key : conf.key())
		{
			p.mKeyList.emplace_back(key);
		}
		for (int val : conf.value())
		{
			p.mValueList.emplace_back(val);
		}
		m->Init(BuffSubType::BattleArcherModify, *aBuff, conf.delaytime());
	}
	if (aBuffConf->buffmodaddskillconfig().active())
	{//添加技能 
		const auto& conf = aBuffConf->buffmodaddskillconfig();
		auto* m = CreateMod<BuffModAddSkill>(aBuff);
		auto& p = m->mParams;
		auto* list = new vector<int>();
		list->reserve(conf.skillidarr_size());
		for (int id : conf.skillidarr())
		{
			list->push_back(static_cast<int>(id));
		}
		p.mSkillIdArr = SharedPtr<vector<int>>(list);
		p.mSkillLevel = 1;
		if (conf.useparentskilllevel())
		{
			p.mSkillLevel = -1;
		}
		else if (conf.has_skilllevel())
		{
			p.mSkillLevel = static_cast<int>(conf.skilllevel());
		}
		m->Init(BuffSubType::AddSkill, *aBuff, conf.delaytime());
	}
	
}