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

#include "SharedPool.h"

THREAD_LOCAL vector<SharedPoolBase*> SharedPoolBase::sAllPool;

void SharedPoolBase::ReleaseAllPool()
{
    auto threadId = std::this_thread::get_id();        
    for(auto* p : sAllPool)
    {
        p->PrintSummary(false);            
    }
    LOG_INFO("thread:%d start release all pool", threadId);  
    //可能因对象析构顺序，导致不是所有的对象都会回到池子。所以需要循环release
    for(int i = 0; i < 10000; i++)
    {
        int allReleaseNum = 0;
        for(auto* p : sAllPool)
        {
            allReleaseNum += p->doRelease();
        }
        if(allReleaseNum == 0)
        {
            break;
        }
		LOG_WARN("thread:%d release %d obj in iter:%d", threadId, allReleaseNum,  i);
    }
    int allUsing = 0;
    for(auto* p : sAllPool)
    {
        p->PrintSummary(true);    
        allUsing += p->mNumUsing;        
    }    
    sAllPool.clear();
	LOG_WARN("thread:%d release all pool done. still using:%d", threadId, allUsing);
}

void SharedPoolBase::PrintSummary(bool aOnlyError)
{
    if(mNumUsing > 0)
    {
        LOG_WARN("SharedPool<%s> thread:%d numUsing:%d numInPool:%d", mTypeName, mThreadId, mNumUsing, mNumInPool);
    }    
}