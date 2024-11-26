///////////////////////////////////////////////////////////
//  ServerUDP.cpp
//  Implementation of the Class ServerUDP
//  Created on:      27-Nov-2024 1:37:06 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerUDP.hpp"
#include "SocketUDP.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ServerUDP::ServerUDP(const char *ip, unsigned short port)
        : Server(ip, port), mRecvBuffer(nullptr), mRecvBufSize(0)
    {
        FI();

        FO();
    }

    /**
     * Destructor
     */
    ServerUDP::~ServerUDP()
    {
        FI();

        if (mRecvBuffer != nullptr)
        {
            delete[] mRecvBuffer;
            mRecvBuffer = nullptr;
        }

        FO();
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
            if (pSocket->isReadWritable())
            {
                memset(mRecvBuffer, 0, mRecvBufSize);
                int n = pSocket->ReceiveFrom(mRecvBuffer, mRecvBufSize, mIPAddr, mPort);
                if (n > 0)
                {
                    this->onDataReceived(mRecvBuffer, n);
                }
                else if (n == 0)
                {
                    //break;
                }
                else if (n == SocketError)
                {
                    //break;
                }
            }
        }

        FO();
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}