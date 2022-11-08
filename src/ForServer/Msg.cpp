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

#include <string.h> 
#include "Msg.h"

#ifdef BATTLE_SOCKET

int BattleMsgLog::Serialize(uint8*& aBuff, int& aBuffLen )
{
    int msgSize = MsgSize();
    if( aBuffLen < msgSize )
    {
        free(aBuff);
        aBuffLen = msgSize;
        aBuff = (uint8*)malloc(aBuffLen);
    }
    SerializeUInt32(mLevel, aBuff);    
    SerializeUInt32(mContent.size(), aBuff+4);
    memcpy(aBuff+8, mContent.c_str(), mContent.size());
    return msgSize;
}

int BattleMsgLog::Unserialize(uint8* aBuff, int aBuffLen )
{
    mLevel = UnserializeUInt32(aBuff);
    uint32 len = UnserializeUInt32(aBuff+4);
    mContent.assign((char*)aBuff+8, len);
    return 0;
}

int BattleMsgLog::MsgSize()
{
    return 8 + mContent.size();
}

int BattleMsgReq::Serialize(uint8*& aBuff, int& aBuffLen )
{
    int msgSize = MsgSize();
    if( aBuffLen < msgSize )
    {
        free(aBuff);
        aBuffLen = msgSize;
        aBuff = (uint8*)malloc(aBuffLen);
    }    
    SerializeUInt32(mBattleArgs.size(), aBuff);
    memcpy(aBuff+4, mBattleArgs.c_str(), mBattleArgs.size());

    int offset = 4 + mBattleArgs.size();
    SerializeUInt32(mToken.size(), aBuff + offset);
    memcpy(aBuff+4+offset, mToken.c_str(), mToken.size());
    return msgSize;
}

int BattleMsgReq::Unserialize(uint8* aBuff, int aBuffLen )
{
    uint32 len = UnserializeUInt32(aBuff);
    mBattleArgs.assign((char*)aBuff+4, len);

    int offset = 4+len;
    len = UnserializeUInt32(aBuff+offset);
    mToken.assign((char*)aBuff+4+offset, len);
    return 0;
}

int BattleMsgReq::MsgSize()
{
    return 8 + mBattleArgs.size() + mToken.size();
}

int BattleMsgRsp::Serialize(uint8*& aBuff, int& aBuffLen )
{
    int msgSize = mBattleResult.size() + mErrMsg.size() + 8;
    if( aBuffLen < msgSize )
    {
        free(aBuff);
        aBuffLen = msgSize;
        aBuff = (uint8*)malloc(aBuffLen);
    }    
    int offset = 0;
    SerializeUInt32(mBattleResult.size(), aBuff);
    memcpy(aBuff+4, mBattleResult.c_str(), mBattleResult.size());
    offset += 4 + mBattleResult.size();
    SerializeUInt32(mErrMsg.size(), aBuff + offset);
    memcpy(aBuff+4+offset, mErrMsg.c_str(), mErrMsg.size());
    return msgSize;
}

int BattleMsgRsp::Unserialize(uint8* aBuff, int aBuffLen )
{
    uint32 len = UnserializeUInt32(aBuff);
    mBattleResult.assign((char*)aBuff+4, len);

    int offset = 4+len;
    len = UnserializeUInt32(aBuff+offset);
    mErrMsg.assign((char*)aBuff+ 4 + offset, len);
    return 0;
}

int BattleMsgRsp::MsgSize()
{
    return mBattleResult.size() + mErrMsg.size() + 8;
}

void SerializeUInt32(uint32 aValue, uint8* aBuffer)
{
    *aBuffer = (uint8)( (aValue >> 24) & 0xff);
    *(aBuffer+1) = (uint8)( (aValue >> 16) & 0xff);
    *(aBuffer+2) = (uint8)( (aValue >> 8) & 0xff);
    *(aBuffer+3) = (uint8)( aValue & 0xff);
}

uint32 UnserializeUInt32(uint8* aBuffer)
{
    uint32 value;
    value = (uint32)aBuffer[0];
    value = (value << 8) + (uint32)aBuffer[1];
    value = (value << 8) + (uint32)aBuffer[2];
    value = (value << 8) + (uint32)aBuffer[3];
    return value;
}

#endif