///////////////////////////////////////////////////////////
//  ConnectionTCP.cpp
//  Implementation of the Class ConnectionTCP
//  Created on:      24-Nov-2024 9:32:16 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ConnectionTCP.hpp"
#include "ServerTCP.hpp"
#include "SocketTCP.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ConnectionTCP::ConnectionTCP(ServerTCP *pServer, Socket *pSocket, bool aliveChecker, int aliveCheckerTimeout)
        : Connection(pServer, pSocket, aliveChecker, aliveCheckerTimeout), mRecvBuffer(nullptr), mRecvBufSize(0)
    {
        FI();

        FO();
    }

    /**
     * Destructor
     */
    ConnectionTCP::~ConnectionTCP()
    {
        FI();

        if (mRecvBuffer != nullptr)
        {
            delete[] mRecvBuffer;
            mRecvBuffer = nullptr;
        }

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

        SocketTCP *pSocket = reinterpret_cast<SocketTCP *>(socket());
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
                    this->onData(mRecvBuffer, n);
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
                mAliveChecker->Stop();
        }

        FO();
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}