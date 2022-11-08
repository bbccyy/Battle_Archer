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

#include "Define.h"
#include "Msg.h"

#ifdef BATTLE_SOCKET

using namespace std;

enum class ErrorNo
{
    Ok = 0,
    CreateSocket = -10,
    Bind = -11,
    Listen = -12,
    Accept = -13,
    Connect = -14
};


class UnixSocket
{
public:
    UnixSocket();
    ~UnixSocket();

    void SetFd(int aFd)
    {
        mFd = aFd;
    }
    int Read(uint8* aBuff, size_t aLen);
    int Write(uint8* aBuff, size_t aLen);
    int Send(BattleMsg* aMsg);
    int Recv(BattleMsg*& aMsg);
protected:
    string mSocketPath;
    int mFd;
    uint8* mBuff;
    int mBuffLen;
};

class UnixSocketServer : public UnixSocket
{
public:
    ErrorNo InitServer(const char* aSocketPath, int aBacklog);
    ErrorNo Accept(UnixSocket*);
private:    
    int mSocketFd;
};

class UnixSocketClient : public UnixSocket
{
public:
    ErrorNo InitClient(const char* aSocketPath);
};


#endif