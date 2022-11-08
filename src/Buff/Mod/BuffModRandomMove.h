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
* @brief （圆形范围内）随机乱走
*
**/

#pragma once
#include "Buff/BuffMod.h"
#include "Framework/Transform.h"
#include "Skill/RefTarget.h"

struct ControlToken;

class BuffModRandomMove : public BuffMod
{
public:
    struct Params : public BuffMod::CommonParams
    {
    public:
        int64 mRadius;
		bool initTarget;
    } mParams;
public:
    void StackAdded(int) override;
    void StackRemoved(int) override;
    void OnEnable() override;
    void OnDisable(bool) override;
	void ResetValues() override;
private:
    const static Vector3 DIRS[];
    const constexpr static int DIR_SIZE = 4;
    SharedPtr<ControlToken> mControlState = nullptr;
    Vector3 mMoveTarget = Vector3(0,0,0);
	RefTarget mRefTarget;
    bool Move(int);
    void NextPos();
};