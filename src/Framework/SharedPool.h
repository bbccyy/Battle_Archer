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
#pragma once

#include <stack>
#include <queue>
#include <vector>
#include <mutex>
#include <thread>
#include <string.h>
#include "SharedPtr.h"
using namespace std;

#ifdef MULTI_THREAD
#define THREAD_LOCAL thread_local
#else
#define THREAD_LOCAL
#endif

class IPoolable
{
public:
    inline bool IsInPool()
    {
        return mIsInPool;
    }
    inline void SetInPool(bool aValue)
    {
        mIsInPool = aValue;
    }
private:
    bool mIsInPool;   

};

class SharedPoolBase
{
public:
    static void ReleaseAllPool();
protected:
    static void Register(SharedPoolBase* aPool)
    {  
        sAllPool.push_back(aPool);
    }

    virtual int doRelease() = 0;    
    void PrintSummary(bool);
protected:
    static THREAD_LOCAL vector<SharedPoolBase*> sAllPool;
    thread::id mThreadId;
    const char* mTypeName;
    int mNumUsing;
    int mNumInPool;
};

//TODO 线程完全问题
template <class T>
class SharedPool : public SharedPoolBase
{
    //单例实现
public:

    inline static SharedPool<T>* GetInstance()
    {    
		static THREAD_LOCAL SharedPool<T> instance;
        return &instance;
    }

    inline static SharedPtr<T> Get()
    {
        return SharedPool<T>::GetInstance()->doGet();
    }

    inline static T* GetRaw()
    {
        return SharedPool<T>::GetInstance()->doGetRaw();
    }

    inline static void PutRaw(T* aPtr)
    {
        SharedPool<T>::GetInstance()->doPut(aPtr);
    }

private:

    SharedPool() 
    {
        mThreadId = std::this_thread::get_id();
        mTypeName = typeid(T).name();
        mNumInPool = 0;
        mNumUsing = 0;
        Register(this);        
    }

    class PutToPool
    {
    public:
        void operator()(T* aPtr)
        {
            SharedPool<T>::GetInstance()->doPut(aPtr);
        }
    };

    inline void doPut(T* aPtr) 
    {                       
        //aPtr->Reset();                
        //// std::lock_guard<std::mutex> lck(mMutex);                
        //LOG_ASSERT(!aPtr->IsInPool());           
        //aPtr->SetInPool(true);               
        //mPool.push(aPtr);
        //mNumUsing--;
        //mNumInPool++;

		aPtr->Reset();
		LOG_ASSERT(!aPtr->IsInPool());
		aPtr->SetInPool(true);
		if (_mPool.empty())
		{ //如果队列为空，就再创建一个全新的对象放在队首  
			T* ptr = new T();
			ptr->SetInPool(true);
			_mPool.push(ptr);
			mNumInPool++;
		}
		_mPool.push(aPtr);
		mNumUsing--;
		mNumInPool++;
    }

    SharedPtr<T> doGet() 
    {
        // std::lock_guard<std::mutex> lck(mMutex);
        /*T* ptr = nullptr;
        if ( mPool.empty() )
        {
            ptr = new T();
        }
        else
        {
            ptr = mPool.top();
            mPool.pop();  
            LOG_ASSERT(ptr->IsInPool());      
            mNumInPool--;      
        }            
        ptr->SetInPool(false);
        mNumUsing++;                
        return SharedPtr<T>(ptr, SharedPool<T>::PutToPool());*/
		
		T* ptr = nullptr;
		if (_mPool.empty())
		{
			ptr = new T();
		}
		else
		{
			ptr = _mPool.front();
			_mPool.pop();
			LOG_ASSERT(ptr->IsInPool());
			mNumInPool--;
		}
		ptr->SetInPool(false);
		mNumUsing++;
		return SharedPtr<T>(ptr, SharedPool<T>::PutToPool());
    }
    
    T* doGetRaw()
    {
        // std::lock_guard<std::mutex> lck(mMutex);        
       /* T* ptr = nullptr;
        if ( mPool.empty() )
        {
            ptr = new T();
        }
        else
        {
            ptr = mPool.top();
            mPool.pop();
            LOG_ASSERT(ptr->IsInPool());   
            mNumInPool--;     
        }                 
        ptr->SetInPool(false);
        mNumUsing++;           
        return ptr;*/

		T* ptr = nullptr;
		if (_mPool.empty())
		{
			ptr = new T();
		}
		else
		{
			ptr = _mPool.front();
			_mPool.pop();
			LOG_ASSERT(ptr->IsInPool());
			mNumInPool--;
		}
		ptr->SetInPool(false);
		mNumUsing++;
		return ptr;
    }

protected:
    virtual int doRelease()
    {
        /*int num = mPool.size();
        T* ptr = nullptr;
        while(!mPool.empty())        
        {
            ptr = mPool.top();
            mPool.pop();
            delete ptr;
        }                
        return num;*/

		int num = _mPool.size();
		T* ptr = nullptr;
		while (!_mPool.empty())
		{
			ptr = _mPool.front();
			_mPool.pop();
			delete ptr;
		}
		return num;
    }
private:    
    //stack<T* > mPool;
	queue<T*> _mPool;
    //std::mutex mMutex;
    
};



