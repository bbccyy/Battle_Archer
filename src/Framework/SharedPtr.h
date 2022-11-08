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
#include <functional>
#include "Log/Log.h"

using std::hash;
using std::nullptr_t;


template<class T>
class WeakPtr;


template<class T>
class DefaultPtrDeleter
{
public:
    void operator()(T* aPtr)
    {
        delete aPtr;
    }
};


class RefCounterBase 
{
public:
    RefCounterBase() :
        mSharedRefs(1),
        mWeakRefs(0)
    {}

    void incShared() 
    {
        ++mSharedRefs;
    }

    void decShared() 
    {
        if (mSharedRefs == 0) 
        {
            throw "shared references: already zero";
        }
        --mSharedRefs;
    }

    void incWeak() 
    {
        ++mWeakRefs;
    }

    void decWeak() 
    {
        if (mWeakRefs == 0) 
        {
            throw "weak references: already zero";
        }
        --mWeakRefs;
    }

    int getSharedRefs() const 
    {
        return mSharedRefs;
    }

    int getWeakRefs() const 
    {
        return mWeakRefs;
    }

    bool hasRefs() const 
    {
        return mSharedRefs + mWeakRefs > 0;
    }

    virtual void del(void* aPtr) = 0;
private:
    int mSharedRefs;
    int mWeakRefs;
};



template<class T, class D>
class RefCounterImple : public RefCounterBase
{
public:
    RefCounterImple(D aDeleter) :
        mDeleter(aDeleter)
    {}

    void del(void* aPtr) override
    {
        mDeleter((T*)aPtr);
    }
private:
    D mDeleter;
};


template<class T>
class SharedPtr 
{
public:
    SharedPtr() 
    {
        initWithDefaultDeleter(nullptr);
    }
    SharedPtr(nullptr_t) 
    {
        initWithDefaultDeleter(nullptr);
    }
    //TODO 目前我们应该只会在SharedPool中通过裸指针构造。可以通过注释这个函数验证一下  
    template<class Y>
    explicit SharedPtr(Y* aPtr) 
    {
        initWithDefaultDeleter(aPtr);
        enableSharedFromThisHelper(mRefCntrPtr, aPtr, aPtr);
    }

    template<typename Y>
    SharedPtr(const SharedPtr<Y>& aSharedPtr, T* aRawPtr) noexcept
        : mObjPtr(aRawPtr), mRefCntrPtr(aSharedPtr.mRefCntrPtr)
    {
		mRefCntrPtr->incShared();
	}

    
    template<class Y, class D>
    explicit SharedPtr(Y* aPtr, D aDeleter) 
    {
        mRefCntrPtr = new RefCounterImple<T, D>(aDeleter);
        mObjPtr = aPtr;
        enableSharedFromThisHelper(mRefCntrPtr, aPtr, aPtr);
    }

    SharedPtr(const SharedPtr<T>& aOther) 
    {
		if (!aOther)
		{
			initWithDefaultDeleter(nullptr);
			return;
		}
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        mRefCntrPtr->incShared();
    }

    SharedPtr(SharedPtr<T> && aOther) noexcept
    {
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        aOther.resetNoDelete();
    }

    SharedPtr<T> & operator=(const SharedPtr<T> & aOther) 
    {
		if (aOther.mObjPtr == mObjPtr)
		{
			return *this;
		}
        Release();
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        mRefCntrPtr->incShared();
        return *this;
    }

    SharedPtr<T> & operator=(SharedPtr<T> && aOther) 
    {
        Release();
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        aOther.resetNoDelete();
        return *this;
    }



    template<class U>
    SharedPtr(const SharedPtr<U> & aOther) 
    {
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        mRefCntrPtr->incShared();
    }

    template<class U>
    SharedPtr(SharedPtr<U> && aOther) 
    {
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        aOther.resetNoDelete();
    }

    template<class U>
    SharedPtr<T> & operator=(const SharedPtr<U> & aOther) 
    {
        Release();
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        mRefCntrPtr->incShared();
        return *this;
    }

    template<class U>
    SharedPtr<T> & operator=(SharedPtr<U> && aOther) 
    {
        Release();
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        aOther.resetNoDelete();
        return *this;
    }

    template<class U>
    SharedPtr(const WeakPtr<U> & aPtr) 
    {
		if (aPtr.mRefCntrPtr)
		{
            LOG_ASSERT(!aPtr.Expired());
			mObjPtr = aPtr.mObjPtr;
			mRefCntrPtr = aPtr.mRefCntrPtr;
			mRefCntrPtr->incShared();
		}
		else
		{
			initWithDefaultDeleter(nullptr);
		}
    }

    ~SharedPtr() 
    {
        checkDeletePtr();
    }

    void Release() 
    {
        checkDeletePtr();
    }

    void Reset(T* aPtr) 
    {
        checkDeletePtr();
        initWithDefaultDeleter(aPtr);
    }

    template<class U>
    void Reset(U* aPtr) 
    {
        checkDeletePtr();
        initWithDefaultDeleter(aPtr);
    }

    void Swap(SharedPtr<T> & aOther) 
    {
        std::swap(mObjPtr, aOther.mObjPtr);
        std::swap(mRefCntrPtr, aOther.mRefCntrPtr);
    }

    inline T* Get() const 
    {
        return mObjPtr;
    }

    T& operator*() const 
    {
        return *mObjPtr;
    }

    T* operator->() const 
    {
        return mObjPtr;
    }

    int GetSharedRefs() const 
    {
        if (mRefCntrPtr == nullptr) 
        {
            return 0;
        }
        return mRefCntrPtr->getSharedRefs();
    }

    bool isUnique() const 
    {
        return GetSharedRefs() == 1;
    }

    explicit operator bool() const 
    {
        return mObjPtr != nullptr;
    }


    template <class U>
    bool operator==(const SharedPtr<U>& aOther) const 
    {
        return Get() == aOther.Get();
    }

    template<class U>
    bool operator==(const U* aOther) const
    {
        return mObjPtr == aOther;
    }


    template <class U>
    bool operator!=(const SharedPtr<U>& aOther) const 
    {
        return !(*this == aOther);
    }

    template <class U>
    bool operator<(const SharedPtr<U>& aOther) const 
    {
        return Get() < aOther.Get();
    }

    template <class U>
    bool operator>(const SharedPtr<U>& aOther) const 
    {
        return !(*this < aOther) && *this != aOther;
    }

    template <class U>
    bool operator<=(const SharedPtr<U>& aOther) const 
    {
        return !(Get() > aOther.Get());
    }

    template <class U>
    bool operator>=(const SharedPtr<U>& aOther) const 
    {
        return !(Get() < aOther.Get());
    }

    inline size_t Hash() const
    {
        return (hash<T*>{}(mObjPtr));
    }

    template<typename U>
    friend class SharedPtr;

private:
    void checkDeletePtr() 
    {
        if (mRefCntrPtr == nullptr) 
        {
            return;
        }
       
        mRefCntrPtr->decShared();
        if (!mRefCntrPtr->hasRefs()) 
        {
            //LOG_DEBUG("shared release counter %p", mRefCntrPtr);
            mRefCntrPtr->del(mObjPtr); 
            delete mRefCntrPtr;
        }
        else
        {
            //when mObjPtr contains the only WeakPtr of mObjPtr
            //if the shared ref count is decreased to 0
            //after mRefCntrPtr->del(mObjPtr), the WeakPtr will have deleted mRefCntrPtr
            //causing futher access to mRefCntrPtr invalid
            if (mRefCntrPtr->getSharedRefs() == 0) 
            {
                mRefCntrPtr->del(mObjPtr);            
            }
        }
        
        resetNoDelete();
    }

    void resetNoDelete() 
    {
        mObjPtr = nullptr;
        mRefCntrPtr = nullptr;
    }

    void resetRefCounter(T* aPtr, RefCounterBase* aRefCntrPtr) 
    {
        mObjPtr = aPtr;
        mRefCntrPtr = aRefCntrPtr;
    }

    void initWithDefaultDeleter(T* aPtr) 
    {
        mRefCntrPtr = new RefCounterImple<T, DefaultPtrDeleter<T> >(DefaultPtrDeleter<T>());
        mObjPtr = aPtr;
    }

    template<class U>
    friend class WeakPtr;

private:
    T* mObjPtr;
    RefCounterBase* mRefCntrPtr;
};

namespace std
{
	template<class T>
	struct hash<SharedPtr<T> >
	{
		size_t operator()(const SharedPtr<T>& aVal) const
		{
			return aVal.Hash();
		}
	};

    template<class T>
    struct hash<WeakPtr<T> >
    {
        size_t operator()(const WeakPtr<T>& aVal) const
        {
            return aVal.Hash();
        }
    };
}

template<class T>
class WeakPtr 
{
public:
    WeakPtr() :
        mObjPtr(nullptr),
        mRefCntrPtr(nullptr)
    {}

    WeakPtr(const SharedPtr<T> & aPtr) :
        mObjPtr(aPtr.mObjPtr),
        mRefCntrPtr(aPtr.mRefCntrPtr) 
    {
        mRefCntrPtr->incWeak();
    }

    WeakPtr(const WeakPtr<T> & aOther) 
    {
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;        
		if (mRefCntrPtr)
			mRefCntrPtr->incWeak();
    }

    WeakPtr(nullptr_t) :
        mObjPtr(nullptr),
        mRefCntrPtr(nullptr)
    {
    }

    WeakPtr<T> & operator=(const WeakPtr<T> & aOther) 
    {
        Release();
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        if (mRefCntrPtr)
            mRefCntrPtr->incWeak();
        return *this;
    }

    template<class U>
    WeakPtr(const SharedPtr<U> & aPtr) :
        mObjPtr(aPtr.mObjPtr),
        mRefCntrPtr(aPtr.mRefCntrPtr) 
    {
        mRefCntrPtr->incWeak();
    }

    template<class U>
    WeakPtr(const WeakPtr<U> & aOther) 
    {
        mObjPtr = aOther.mObjPtr;
        mRefCntrPtr = aOther.mRefCntrPtr;
        mRefCntrPtr->incWeak();
    }

    ~WeakPtr() 
    {
        checkDeletePtr();
    }
     
    T* operator->() const 
    {
		if (Expired())
			return nullptr;
        return mObjPtr;
    }

    void operator=(nullptr_t) 
    {
        Release();
    }
    bool operator!=(nullptr_t) const 
    {
        return !Expired();
    }
    
    template <class U>
    bool operator==(const WeakPtr<U>& aOther) const 
    {
        return Get() == aOther.Get();
    }

    template <class U>
    bool operator==(const SharedPtr<U>& aOther) const 
    {
        return Get() == aOther.Get();
    }

    template<class U>
    bool operator==(const U* aOther) const
    {
        return mObjPtr == aOther;
    }


    template <class U>
    bool operator!=(const WeakPtr<U>& aOther) const 
    {
        return !(*this == aOther);
    }

    explicit operator bool() const 
    {
		if (Expired())
			return false;
        return mObjPtr != nullptr;
    }

    T& operator*() const 
    {
        LOG_ASSERT(!Expired());
        return *mObjPtr;
    }

    inline T* Get() const 
    {        
        return Expired() ? nullptr : mObjPtr;
    }
    
    void Release() 
    {
        checkDeletePtr();
    }

    void Swap(WeakPtr<T> & aOther) 
    {
        std::swap(mObjPtr, aOther.mObjPtr);
        std::swap(mRefCntrPtr, aOther.mRefCntrPtr);
    }

    int GetSharedRefs() const 
    {
        if (mRefCntrPtr == nullptr) 
        {
            return 0;
        }
        return mRefCntrPtr->getSharedRefs();
    }

    bool Expired() const 
    {
        if (mRefCntrPtr == nullptr) 
        {
            return true;
        }
        return mRefCntrPtr->getSharedRefs() == 0;
    }

    inline size_t Hash() const
    {
        return (hash<T*>{}(mObjPtr));
    }

    // SharedPtr<T> Lock() const 
    // {
    //     if (Expired()) 
    //     {
    //         return SharedPtr<T>();
    //     }
    //     return SharedPtr<T>(*this);
    // }
private:
    void checkDeletePtr() 
    {
        if (!mRefCntrPtr)
            return;
        mRefCntrPtr->decWeak();
        if (!mRefCntrPtr->hasRefs()) 
        {
            //LOG_DEBUG("weak release counter %p", mRefCntrPtr);
            delete mRefCntrPtr;
        }
        resetNoDelete();
    }

    void resetNoDelete() 
    {
        mObjPtr = nullptr;
        mRefCntrPtr = nullptr;
    }

    void set( RefCounterBase* const aRefCount, T* aPtr)
    {
        if( Expired() )
        {            
            if (mRefCntrPtr)
            {
                checkDeletePtr();
            }
            mObjPtr = aPtr;                
            mRefCntrPtr = aRefCount;
            mRefCntrPtr->incWeak();
        }
        else
        {
            /*
            这个函数在通过裸指针构造SharedPtr时，enableSharedFromThisHelper中被调用。
            我们只允许裸指针在生命周期中只能发生一次，这个操作  
            */
            LOG_ASSERT(false);
        }
    }

    template<class U>
    friend class EnableSharedFromThis;
    template<class U>
    friend class SharedPtr;
private:
    T* mObjPtr;
    RefCounterBase* mRefCntrPtr;

};



template<class T> 
class EnableSharedFromThis
{
protected:
    EnableSharedFromThis() noexcept
    {
    }

    EnableSharedFromThis(EnableSharedFromThis const &) noexcept
    {
    }

    EnableSharedFromThis & operator=(EnableSharedFromThis const &) noexcept
    {
        return *this;
    }

    ~EnableSharedFromThis() noexcept // ~weak_ptr<T> newer throws, so this call also must not throw
    {
    }

public:
    SharedPtr<T> SharedFromThis()
    {
        LOG_ASSERT(mWeakOfThis != nullptr);
        SharedPtr<T> p( mWeakOfThis );
        LOG_ASSERT( p.Get() == (this) );
        return p;
    }

    WeakPtr<T> WeakFromThis() noexcept
    {
        return mWeakOfThis;
    }

public: // actually private, but avoids compiler template friendship issues

    template<class Y> 
    void internalAcceptOwner( RefCounterBase* const aRefCounter, Y * aObjPtr ) const noexcept
    {
        mWeakOfThis.set(aRefCounter, aObjPtr);
    }

private:
    mutable WeakPtr<T> mWeakOfThis;
};



template<typename T, typename Y>
void enableSharedFromThisHelper( RefCounterBase* const aRefCounter, const EnableSharedFromThis<T>* aPtr1, Y* aPtr2) noexcept
{
    if (aPtr1 != nullptr)
    {
        aPtr1->internalAcceptOwner(aRefCounter, aPtr2);
    }
}

inline void enableSharedFromThisHelper(...) noexcept
{
}





template<class Tt, class Tf>
inline SharedPtr<Tt> DynamicPointerCast(const SharedPtr<Tf>& aFromPtr) noexcept
{
    if (Tt* toPtr = dynamic_cast<Tt*>(aFromPtr.Get()))
    {
        return SharedPtr<Tt>(aFromPtr, toPtr);
    }
    return SharedPtr<Tt>();
}


