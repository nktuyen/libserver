///////////////////////////////////////////////////////////
//  Connection.cpp
//  Implementation of the Class Connection
//  Created on:      24-Nov-2024 9:11:24 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ConnectionTCP.hpp"
#include "ServerTCP.hpp"
#include "SocketTCP.hpp"
#include "Logger.hpp"
#ifdef _WINDOWS
#else //! _WINDOWS
#include <unistd.h>
#endif //_WINDOWS

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    AliveChecker::AliveChecker(ConnectionTCP *pConn, int timeout_seconds)
        : mConn(pConn), mTimeout(timeout_seconds), mElapsed(0)
    {
        FI();
        FO();
    }

    AliveChecker::~AliveChecker()
    {
        FI();
        FO();
    }

    bool AliveChecker::onInitialize()
    {
        FI();

        if (mConn == nullptr)
        {
            FO();
            return false;
        }

        mElapsed = 0;
        FO();
        return true;
    }

    int AliveChecker::getElapsed()
    {
        int res = 0;
        std::lock_guard<std::mutex> locker(mMutex);
        res = mElapsed;

        return res;
    }

    void AliveChecker::setElapsed(int val)
    {
        std::lock_guard<std::mutex> locker(mMutex);
        mElapsed = val;
    }

    void AliveChecker::Restart()
    {
        FI();
        setElapsed(0);
        FO();
    }

    int AliveChecker::onRun()
    {
        FI();
        while (isRunning())
        {
#ifdef _WINDOWS
            ::Sleep(1000);
#else  //! _WINDOWS
            ::sleep(1);
#endif //_WINDOWS
            setElapsed(mElapsed + 1);
            if (getElapsed() > mTimeout)
            {
                mConn->setAlive(false);
                break;
            }
        }

        FO();
        return 0;
    }

    /**
     * Constructor
     */
    ConnectionTCP::ConnectionTCP(ServerTCP *pServer, SocketTCP *pSocket, bool aliveChecker, int aliveCheckerTimeout)
        : Thread(), mServer(pServer), mSocket(pSocket), mAlive(true), mAliveChecker(nullptr)
    {
        FI();

        if (aliveChecker)
        {
            mAliveChecker = new AliveChecker(this, aliveCheckerTimeout);
        }

        FO();
    }

    /**
     * Destructor
     */
    ConnectionTCP::~ConnectionTCP()
    {
        if (mAliveChecker != nullptr)
        {
            delete mAliveChecker;
            mAliveChecker = nullptr;
        }
        if (mSocket != nullptr)
        {
            delete mSocket;
            mSocket = nullptr;
        }
    }

    bool ConnectionTCP::isAlive()
    {
        bool res = false;
        std::lock_guard<std::mutex> locker(mALiveMutex);
        res = mAlive;
        return res;
    }

    void ConnectionTCP::setAlive(bool bAlive)
    {
        FI();
        FM("bAlive = %d", bAlive);
        std::lock_guard<std::mutex> locker(mALiveMutex);
        mAlive = bAlive;
        FO();
    }

    bool ConnectionTCP::onInitialize()
    {
        FI();

        if (socket() == nullptr)
        {
            FO();
            return false;
        }

        mRecvBufSize = socket()->optRecvBufferSize();
        mRecvBuffer = new char[mRecvBufSize + 1];

        FO();
        return true;
    }

    int ConnectionTCP::onRun()
    {
        FI();

        SocketTCP *pSocket = socket();
        if (mAliveChecker != nullptr)
        {
            mAliveChecker->Create();
        }

        while (isRunning() && isAlive())
        {
            if (socket()->isReadable())
            {
                memset(mRecvBuffer, 0, mRecvBufSize);
                int n = pSocket->Receive(mRecvBuffer, mRecvBufSize);
                if (n > 0)
                {
                    if (mAliveChecker != nullptr)
                    {
                        mAliveChecker->Restart();
                    }
                    this->setAlive(true);
                    this->onDataReceived(mRecvBuffer, n);
                    if (mServer != nullptr)
                    {
                        mServer->onDataReceived(mRecvBuffer, n);
                    }
                }
                else if (n == 0)
                {
                    setAlive(false);
                    break;
                }
                else if (n == SocketError)
                {
                    setAlive(false);
                    break;
                }
            }
        }

        if (mAliveChecker != nullptr)
        {
            if (mAliveChecker->isRunning())
            {
                mAliveChecker->Stop();
                mAliveChecker->Wait();
            }
        }

        FO();
        return 0;
    }

    int ConnectionTCP::onFailure()
    {
        FI();

        if (mAliveChecker != nullptr)
        {
            if (mAliveChecker->isRunning())
                mAliveChecker->Stop();
        }

        if (mSocket != nullptr)
        {
            if (mSocket->handle() != InvalidSocketHandle)
            {
                mSocket->Close();
            }
        }

        if (mServer != nullptr)
        {
            mServer->onConnectionClose(this);
        }

        FO();
        return 1;
    }

    void ConnectionTCP::onSuccess()
    {
        FI();

        if (mAliveChecker != nullptr)
        {
            if (mAliveChecker->isRunning())
                mAliveChecker->Stop();
        }

        if (mSocket != nullptr)
        {
            if (mSocket->handle() != InvalidSocketHandle)
            {
                mSocket->Close();
            }
        }

        if (mServer != nullptr)
        {
            mServer->onConnectionClose(this);
        }

        FO();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}