/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief
*
**/

#pragma once

#define BATTLE_SOCKET

#ifdef BATTLE_SOCKET

#include <string>
#include "Define.h"

using namespace std;

enum class MsgId
{
    BattleInvalid = 0,
    BattleReq,
    BattleRsp,
    Quit,
    QuitConfirm,
    Log
};

//TODO msg使用对象池
class BattleMsg
{
public:
    BattleMsg()
    {
        mMsgId = MsgId::BattleInvalid;
    }
    virtual ~BattleMsg(){}

    virtual int Serialize(uint8*& aBuff, int & aBuffLen ){return 0;};
    virtual int Unserialize(uint8* aBuff, int aBuffLen ){return 0;};
    virtual int MsgSize(){return 0;};
    MsgId mMsgId;
};


class BattleMsgQuit : public  BattleMsg
{
public:
    BattleMsgQuit()
    {
        mMsgId=MsgId::Quit;
    }
};

class BattleMsgQuitConfirm : public  BattleMsg
{
public:
    BattleMsgQuitConfirm()
    {
        mMsgId=MsgId::QuitConfirm;
    }
};

class BattleMsgLog : public  BattleMsg
{
public:
    BattleMsgLog()
    {
        mMsgId = MsgId::Log;
    }
    virtual int Serialize(uint8*& aBuff, int & aBuffLen );
    virtual int Unserialize(uint8* aBuff, int aBuffLen );
    virtual int MsgSize();
    uint32 mLevel;
    string mContent;
};


class BattleMsgReq : public  BattleMsg
{
public:
    BattleMsgReq()
    {
        mMsgId = MsgId::BattleReq;
    }
    virtual int Serialize(uint8*& aBuff, int & aBuffLen );
    virtual int Unserialize(uint8* aBuff, int aBuffLen );
    virtual int MsgSize();
    string mBattleArgs;
    string mToken;
};


class BattleMsgRsp : public  BattleMsg
{
public:
    BattleMsgRsp()
    {
        mMsgId = MsgId::BattleRsp;
    }
    virtual int Serialize(uint8*& aBuff, int & aBuffLen );
    virtual int Unserialize(uint8* aBuff, int aBuffLen );
    virtual int MsgSize();
    string mBattleResult;
    string mErrMsg;
};


void SerializeUInt32(uint32 aValue, uint8* aBuffer);
uint32 UnserializeUInt32(uint8* aBuffer);

#endif