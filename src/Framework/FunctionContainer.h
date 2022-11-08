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
* @brief 方法容器（用法类似std::function）,支持存放c函数指针与成员方法指针
*
**/

#pragma once
#include "SharedPool.h"

//map to a "function ... end" block in lua
template<typename R, typename... A>
class IFunctionContainer : public IPoolable
{
	using L = const void(*)(const IFunctionContainer<R, A...>*);
public:
    virtual R operator()(A... aArg) const = 0;
	void WhenRecycle(L aRecycle)
	{
		OnRecycle = aRecycle;
	}
	void Recycle() const
	{
		OnRecycle(this);
	}
	static void DefaultRecycle(const IFunctionContainer<R, A...>* aPtr)
	{
		delete aPtr;
	}
private:
	L OnRecycle;
};

template<class W, typename R, typename... A>
class FunctionContainer : public IFunctionContainer<R, A...>, public EnableSharedFromThis<FunctionContainer<W, R, A...>>
{
    using F = R(W::*)(A...);  //typedef F as a function pointer points to any member func under domain W with R return and A... inputs
public:
    void Init(W& aOwner, F aFunc)
    {
        mOwner = &aOwner;
        mFunc = aFunc;
    }

	void Reset()
	{
		mOwner = nullptr;
		mFunc = nullptr;
	}

    inline R operator()(A... aArg) const
    {
        return ((mOwner->*mFunc)(aArg...));
    }
private:
    W* mOwner;
    F mFunc;
};

template<typename R, typename... A>
class FunctionPointer : public IFunctionContainer<R, A...>, public EnableSharedFromThis<FunctionPointer<R, A...>>
{
    using F = R(*)(A...);
public:
    void Init(F aFunc)
    {
        mFunc = aFunc;
    }

	void Reset()
	{
		mFunc = nullptr;
	}

    inline R operator()(A... aArg) const
    {
        return mFunc(aArg...);
    }
private:
    F mFunc;
};

template<class W, typename R, typename... A, typename I = const IFunctionContainer<R, A...>*>
I MakeFunction(W& aOwner, R(W::*aFunc)(A...), bool aUsePool = true)
{
	using F = FunctionContainer<W, R, A...>;
	if (!aUsePool)
	{
		auto func = new F;
		func->Init(aOwner, aFunc);
		func->WhenRecycle(reinterpret_cast<const void(*)(I)>(&IFunctionContainer<R, A...>::DefaultRecycle));
		return func;
	}
    auto func = SharedPool<F>::GetRaw();
    func->Init(aOwner, aFunc);
	func->WhenRecycle(reinterpret_cast<const void(*)(I)>(&SharedPool<F>::PutRaw));
    return func;
}

template<typename R, typename... A, typename I = const IFunctionContainer<R, A...>*>
I MakeFunction(R(*aFunc)(A...), bool aUsePool = true)
{
	using F = FunctionPointer<R, A...>;
	if (!aUsePool)
	{
		auto func = new F;
		func->Init(aFunc);
		func->WhenRecycle(reinterpret_cast<const void(*)(I)>(&IFunctionContainer<R, A...>::DefaultRecycle));
		return func;
	}
	auto func = SharedPool<F>::GetRaw();
	func->Init(aFunc);
	func->WhenRecycle(reinterpret_cast<const void(*)(I)>(&SharedPool<F>::PutRaw));
	return func;
}

template<typename F>
void TryRecycleFunction(F& aFunc)
{
	if (aFunc)
	{
		aFunc->Recycle();
		aFunc = nullptr;
	}
}
