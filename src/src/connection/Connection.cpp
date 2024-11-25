///////////////////////////////////////////////////////////
//  Connection.cpp
//  Implementation of the Class Connection
//  Created on:      24-Nov-2024 9:11:24 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "Connection.hpp"
#include "Server.hpp"
#include "Socket.hpp"
#include "Logger.hpp"
#ifdef _WINDOWS
#else //! _WINDOWS
#include <unistd.h>
#endif //_WINDOWS

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    AliveChecker::AliveChecker(Connection *pConn, int timeout_seconds)
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
#else//! _WINDOWS
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
    Connection::Connection(Server *pServer, Socket *pSocket, bool aliveChecker, int aliveCheckerTimeout)
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
    Connection::~Connection()
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

    bool Connection::isAlive()
    {
        bool res = false;
        std::lock_guard<std::mutex> locker(mALiveMutex);
        res = mAlive;
        return res;
    }

    void Connection::setAlive(bool bAlive)
    {

        std::lock_guard<std::mutex> locker(mALiveMutex);
        mAlive = bAlive;
    }

    int Connection::onFailure()
    {
        FI();

        if (mAliveChecker != nullptr)
        {
            if (mAliveChecker->isRunning())
                mAliveChecker->Stop();
        }

        if (mSocket != nullptr)
        {
            if (mSocket->handle() != InvalidHandle)
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

    void Connection::onSuccess()
    {
        FI();

        if (mAliveChecker != nullptr)
        {
            if (mAliveChecker->isRunning())
                mAliveChecker->Stop();
        }

        if (mSocket != nullptr)
        {
            if (mSocket->handle() != InvalidHandle)
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