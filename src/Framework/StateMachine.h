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

#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "FunctionContainer.h"

using std::string;
using std::vector;
using std::unordered_map;

class Fsm;
class State;
class Transition;

class State
{
public:
    State() = delete;
    State(const int, Fsm&, const char*);
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    ~State();

    void OnEnter();
    void OnTick(int);
    void OnExit();
    void Reset();
    void AddTransition(const Transition&);

    const int GetId() const;
    const char* GetName() const;
    void SetOnEnter(const IFunctionContainer<void>*);
    void SetOnTick(const IFunctionContainer<bool, int>*);
    void SetOnExit(const IFunctionContainer<void>*);
public:
	int mId;
private:
    Fsm& mFsm;
    const char* mName;
    vector<const Transition*> mTransitions;
    bool mIsDone;
    const IFunctionContainer<void>* mOnEnter;
	const IFunctionContainer<bool, int>* mOnTick;
	const IFunctionContainer<void>* mOnExit;
};

enum class TransitionMode
{
    Auto = 0,
    AfterActionDone,
    Manual,
};

class Transition
{
public:
    using Condition = IFunctionContainer<bool, bool>;
    Transition() = delete;
    Transition(State&, State&, TransitionMode);
    Transition(const Transition&) = delete;
    Transition& operator=(const Transition&) = delete;
    ~Transition();

    State& GetSourceState() const;
    State& GetTargetState() const;
    bool CanTransit(bool) const;
    void SetCondition(const Condition*);
private:
    bool mPassThrough;
    TransitionMode mMode;
    State& mSource;
    State& mTarget;
    const Condition* mCondition;
    void SetDefaultCondition();
    bool ActionDoneCondition(bool);
    bool PassThroughCondition(bool);
};

class Fsm
{
public:
    const constexpr static int STATE_ID_START = -1;
    const constexpr static int STATE_ID_END = -2;
    const constexpr static int STATE_ID_ANY = -3;
    Fsm(const char*);
	~Fsm();
    const char* GetName() const;
    State& GetCurrentState() const;
    State& GetAnyState() const;
    State& GetStartState() const;
    State& GetEndState() const;
    bool IsInState(int) const;
    void DoTransition(const Transition*);
    void OnTick(int);
    void Reset();
	void SetState(State*);
    State* AddState(const char*);
    Transition* AddTransition(State&, State&, TransitionMode);
public:
	int mCurStateId = 0;
private:
    const constexpr static char* STATE_NAME_START = "Start";
    const constexpr static char* STATE_NAME_END = "End";
    const constexpr static char* STATE_NAME_ANY = "Any";
    const char* mName;
    State* mStartState;
    State* mEndState;
    State* mAnyState;
    State* mCurState;
    unordered_map<int, State*> mStateMap;
    int mStateCount;
    void Transit(const Transition*);
    bool IsAtEnd() const;
};