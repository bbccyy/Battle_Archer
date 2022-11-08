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


#include "ConfigMgr/Pb/module/BuffData.pb.h"
#include "Framework/SharedPool.h"
#include "Skill/Skill.h"
#include "Entity/UnitDefine.h"
#include "BuffMod.h"


namespace pb
{
    class BuffData;
}
using pb::BuffData;

template<class M>
M* Buff::CreateMod(const SharedPtr<Buff>& aBuff)
{
    auto m = SharedPool<M>::Get();
    auto mod = SharedPtr<BuffMod>(m);
    aBuff->AddMod(mod);
	m->mParams = typename M::Params();
    m->SetCommonParams(static_cast<BuffMod::CommonParams*>(&m->mParams));
    return static_cast<M*>(mod.Get());
}

template<class Params, class Conf>
void InitModHpOrRageParams(Params& aParam, const Conf& aConf, int const aLevel)
{
    aParam.mCount = aConf.count();
    aParam.mInterval = aConf.interval();
    aParam.mType = static_cast<BuffModHpOrRageType>(aConf.type());
    auto& percent = aConf.data().percentparam();
    auto& percentGrowth = aConf.data().percentgrowth();
    auto& value = aConf.data().valueparma();
    auto& valueGrowth = aConf.data().valuegrowth();
    for (int i = 0; i < percent.size(); ++i)
    {
        aParam.mPercent.push_back(percent.Get(i) + percentGrowth.Get(i) * aLevel);
    }
    for (int i = 0; i < value.size(); ++i)
    {
        aParam.mAdded.push_back(value.Get(i) + valueGrowth.Get(i) * aLevel);
    }
    aParam.mPhaseAdded = aConf.valuegrowth();
    aParam.mPhasePercent = aConf.percentgrowth();
}


