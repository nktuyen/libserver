///////////////////////////////////////////////////////////
//  ServerUDP.cpp
//  Implementation of the Class ServerUDP
//  Created on:      27-Nov-2024 1:37:06 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerUDP.hpp"
#include "SocketUDP.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ServerUDP::ServerUDP(const char *ip, unsigned short port)
        : Server(ip, port), mRecvBuffer(nullptr), mRecvBufSize(0)
    {
    }

    /**
     * Destructor
     */
    ServerUDP::~ServerUDP()
    {
        if (mRecvBuffer != nullptr)
        {
            delete[] mRecvBuffer;
            mRecvBuffer = nullptr;
        }
    }

    bool ServerUDP::onInitialize()
    {
        FI();

        if (!Server::onInitialize())
        {
            FO();
            return false;
        }

        mRecvBufSize = socket()->optRecvBufferSize();
        mRecvBuffer = new char[mRecvBufSize + 1];

        FO();
        return true;
    }

    int ServerUDP::onRun()
    {
        FI();

        SocketUDP *pSocket = reinterpret_cast<SocketUDP *>(socket());
        if (pSocket == nullptr)
        {
            FO();
            return 0;
        }

        while (isRunning())
        {
            if (pSocket->isReadable())
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
                    break;
                }
            }
        }

        FO();
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}