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

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    Connection::Connection(Server *pServer, Socket *pSocket)
        : Thread(), mServer(pServer), mSocket(pSocket), mAlive(true)
    {
    }

    /**
     * Destructor
     */
    Connection::~Connection()
    {
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

        if (mServer != nullptr)
        {
            mServer->onConnectionClose(this);
        }

        FO();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}