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

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "Socket.h"
#include "Log/Log.h"

#ifdef BATTLE_SOCKET

#define CHECK_RET() if(ret != 0) \
{\
    return ret;\
}

UnixSocket::UnixSocket():mFd(-1), mBuffLen(1024*1024)
{
    mBuff = (uint8*)malloc(mBuffLen);
}

UnixSocket::~UnixSocket()
{
    if(mFd > 0)
    {
        close(mFd);
    }
    free(mBuff);
}


int UnixSocket::Read(uint8* aBuff, size_t aLen)
{
    int ret = 0, offset = 0;
    while(aLen > 0)
    {
        ret = read(mFd, aBuff+offset, aLen);
        if(ret <= 0)
        {
            return -1;
        }
        aLen -= ret;
        offset += ret;
    }
    return 0;
}

int UnixSocket::Write(uint8* aBuff, size_t aLen)
{
    int ret = 0, offset = 0;
    while(aLen > 0)
    {
        ret = write(mFd, aBuff+offset, aLen);
        if(ret <= 0)
        {
            return -1;
        }
        aLen -= ret;
        offset += ret;
    }
    return 0;
}

int UnixSocket::Send(BattleMsg* aMsg)
{    
    SerializeUInt32(aMsg->MsgSize(), mBuff);
    SerializeUInt32((uint32)aMsg->mMsgId, mBuff+4);
    auto ret = Write(mBuff, 8);
    CHECK_RET()
    int len = aMsg->Serialize(mBuff, mBuffLen);
    return Write(mBuff, len);
}

int UnixSocket::Recv(BattleMsg*& aMsg)
{
    int ret = Read(mBuff, 4);
    CHECK_RET()
    uint32 msgSize = UnserializeUInt32(mBuff);
    ret = Read(mBuff, 4);
    CHECK_RET()
    MsgId msgId = (MsgId)UnserializeUInt32(mBuff);
    aMsg = nullptr;
    if( mBuffLen < msgSize)
    {
        free(mBuff);
        mBuffLen = msgSize;
        mBuff = (uint8*)malloc(mBuffLen);
    }
    ret = Read(mBuff, msgSize);
    CHECK_RET()
    switch(msgId)
    {
    case MsgId::Log:
        aMsg = new BattleMsgLog();        
        break;
    case MsgId::BattleReq:
        aMsg = new BattleMsgReq();        
        break;
    case MsgId::BattleRsp:
        aMsg = new BattleMsgRsp();        
        break;
    case MsgId::Quit:
        aMsg = new BattleMsgQuit();        
        break;
    case MsgId::QuitConfirm:
        aMsg = new BattleMsgQuitConfirm();        
        break;
    default:
        LOG_FATAL("get invalid msg. msgId:%d", msgId);
        return -1;
    }
    ret = aMsg->Unserialize(mBuff, msgSize);
    return ret;
}

ErrorNo UnixSocketServer::InitServer(const char* aSocketPath, int aBacklog)
{
    mSocketPath = aSocketPath;
    if ( (mSocketFd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
    {
        return ErrorNo::CreateSocket;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, aSocketPath, sizeof(addr.sun_path)-1);
    unlink(aSocketPath);

    if (bind(mSocketFd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    {
        return ErrorNo::Bind;
    }

    if (listen(mSocketFd, aBacklog) == -1) 
    {
        return ErrorNo::Listen;
    }
    return ErrorNo::Ok;
}

ErrorNo UnixSocketServer::Accept(UnixSocket* aConn)
{
    int fd;
    if ( (fd = accept(mSocketFd, NULL, NULL)) == -1) 
    {
        return ErrorNo::Accept;
    }
    aConn->SetFd(fd);
    return ErrorNo::Ok;
}

ErrorNo UnixSocketClient::InitClient(const char* aSocketPath)
{
    mSocketPath = aSocketPath;
    if ( (mFd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
    {
        return ErrorNo::CreateSocket;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, aSocketPath, sizeof(addr.sun_path)-1);

    if (connect(mFd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    {
        return ErrorNo::Connect;
    }
    return ErrorNo::Ok;
}

#endif