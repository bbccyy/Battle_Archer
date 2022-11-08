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
* @brief
*
**/

#include "StateMachine.h"
#include "Log/Log.h"

const constexpr int Fsm::STATE_ID_START;
const constexpr int Fsm::STATE_ID_END;
const constexpr int Fsm::STATE_ID_ANY;

void DefaultEmpty()
{
}

//State implementation
State::State(int const aId, Fsm& aFsm, const char* aName)
    : mId(aId)
    , mFsm(aFsm)
    , mName(aName)
    , mTransitions(vector<const Transition*>(0))
    , mOnEnter(MakeFunction<>(&DefaultEmpty))
    , mOnTick(nullptr)
    , mOnExit(MakeFunction<>(&DefaultEmpty))
    , mIsDone(true)
{
    //LOG_INFO("State %s created.", aName);
}

State::~State()
{
	for (auto* p : mTransitions)
	{
		delete p;
	}
	mOnEnter->Recycle();
	mOnExit->Recycle();
	TryRecycleFunction(mOnTick);
}

void State::OnEnter()
{
    //LOG_INFO("Entering state %s.", mName->c_str());
    Reset();
    mOnEnter->operator()();
}

void State::OnTick(int const aDeltaTime)
{
    if (!mIsDone)
    {
        mIsDone = mOnTick->operator()(aDeltaTime);
    }
    for (auto* trans : mTransitions)
    {
        if (trans->CanTransit(mIsDone))
        {
            mFsm.DoTransition(trans);
            return;
        }
    }
}

void State::OnExit()
{
    //LOG_INFO("Exiting state %s.", mName->c_str());
    mOnExit->operator()();
}

void State::Reset()
{
    mIsDone = !mOnTick;
}

void State::AddTransition(const Transition& aTrans)
{
    mTransitions.emplace_back(&aTrans);
}

const int State::GetId() const
{
    return mId;
}

const char* State::GetName() const
{
    return mName;
}

void State::SetOnEnter(const IFunctionContainer<void>* aEnter)
{
	TryRecycleFunction(mOnEnter);
	if (aEnter)
	{
		mOnEnter = aEnter;
	}
	else
	{
		mOnEnter = MakeFunction<>(&DefaultEmpty);
	}
}

void State::SetOnTick(const IFunctionContainer<bool, int>* aTick)
{
	TryRecycleFunction(mOnTick);
    mOnTick = aTick;
    mIsDone = !mOnTick;
}

void State::SetOnExit(const IFunctionContainer<void>* aExit)
{
	TryRecycleFunction(mOnExit);
	if (aExit)
	{
		mOnExit = aExit;
	}
	else
	{
		mOnExit = MakeFunction<>(&DefaultEmpty);
	}
}

//Transition implementation
Transition::Transition(State& aSource, State& aTarget, TransitionMode const aMode)
    : mPassThrough(aMode == TransitionMode::Auto)
    , mMode(aMode)
    , mSource(aSource)
    , mTarget(aTarget)
{
    /*
    LOG_DEBUG("Transition from %s to %s created. {PassThrough=%d}",
        aSource.GetName().c_str(), aTarget.GetName().c_str(), aCanPass);
        */
    SetDefaultCondition();
}

Transition::~Transition()
{
	mCondition->Recycle();
}

State& Transition::GetSourceState() const
{
    return mSource;
}

State& Transition::GetTargetState() const
{
    return mTarget;
}

void Transition::SetCondition(const Condition* aCondition)
{
	TryRecycleFunction(mCondition);
	if (aCondition)
	{
		mCondition = aCondition;
	}
	else
	{
		SetDefaultCondition();
	}
}

void Transition::SetDefaultCondition()
{
    if (mMode == TransitionMode::AfterActionDone)
    {
        mCondition = MakeFunction<>(*this, &Transition::ActionDoneCondition);
    }
    else
    {
        mCondition = MakeFunction<>(*this, &Transition::PassThroughCondition);
    }
}

bool Transition::CanTransit(bool const aActionDone) const
{
    return mCondition->operator()(aActionDone);
}

bool Transition::ActionDoneCondition(bool const aActionDone)
{
    return aActionDone;
}

bool Transition::PassThroughCondition(bool const)
{
    return mPassThrough;
}

//Fsm implementation
Fsm::Fsm(const char* aName)
    : mName(aName)
    , mStateMap(unordered_map<int, State*>(0))
    , mStartState(new State(STATE_ID_START, *this, STATE_NAME_START))
    , mEndState(new State(STATE_ID_END, *this, STATE_NAME_END))
    , mAnyState(new State(STATE_ID_ANY, *this, STATE_NAME_ANY))
    , mCurState(mStartState)
    , mStateCount(0)
{
    //LOG_DEBUG("Fsm %s created.", aName);
    mStateMap.emplace(STATE_ID_START, mStartState);
    mStateMap.emplace(STATE_ID_END, mEndState);
    mStateMap.emplace(STATE_ID_ANY, mAnyState);
}

Fsm::~Fsm()
{
	for (auto& pair : mStateMap)
	{
		delete pair.second;
	}
}

const char* Fsm::GetName() const
{
    return mName;
}

State& Fsm::GetCurrentState() const
{
    return *mCurState;
}

State& Fsm::GetAnyState() const
{
    return *mAnyState;
}

State& Fsm::GetStartState() const
{
    return *mStartState;
}

State& Fsm::GetEndState() const
{
    return *mEndState;
}

bool Fsm::IsInState(int const aId) const
{
    return mCurState->mId == aId;
}

bool Fsm::IsAtEnd() const
{
    return mCurState == mEndState;
}

void Fsm::Transit(const Transition* aTrans)
{
    /*LOG_INFO("Fsm %s, transit from %s to %s",
           mName->c_str(),
           mCurState->GetName().c_str(),
           aTrans->GetTargetState().GetName().c_str());*/
    mCurState->OnExit();
    mCurState = &(aTrans->GetTargetState());
	mCurStateId = mCurState->GetId();
    mCurState->OnEnter();
}

void Fsm::DoTransition(const Transition* aTriggered)
{
    State* source = &aTriggered->GetSourceState();
    bool fromAny = source == mAnyState;
    if (fromAny || source == mCurState)
    {
        /*LOG_DEBUG("Fsm %s, transition {%s->%s} triggered.", 
            mName->,
            source->GetName(),
            aTriggered->GetTargetState().GetName());*/
        Transit(aTriggered);
    }
    else
    {
        LOG_DEBUG("Fsm %s, transition from {%s->%s} trigger failed, current state = %s"
            , mName
            , source->GetName()
            , aTriggered->GetTargetState().GetName()
            , mCurState->GetName());
    }
}

void Fsm::OnTick(int const aDeltaTime)
{
    mCurState->OnTick(aDeltaTime);
}

void Fsm::Reset()
{
    mCurState = mStartState;
	mCurStateId = mCurState->GetId();
    for (auto& state : mStateMap)
    {
        state.second->Reset();
    }
}

void Fsm::SetState(State* aState)
{
	mCurState = aState;
	mCurStateId = mCurState->GetId();
	for (auto& state : mStateMap)
	{
		state.second->Reset();
	}
}

State* Fsm::AddState(const char* aName)
{
	auto* st = new State(mStateCount, *this, aName);
	mStateMap[mStateCount] = st;
    mStateCount = mStateCount + 1;
    return st;
}

Transition* Fsm::AddTransition(State& aSource, State& aTarget, TransitionMode const aMode)
{
    auto* ret = new Transition(aSource, aTarget, aMode);
    aSource.AddTransition(*ret);
    return ret;
}
