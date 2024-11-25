///////////////////////////////////////////////////////////
//  ServerTCP.cpp
//  Implementation of the Class ServerTCP
//  Created on:      24-Nov-2024 8:33:41 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerTCP.hpp"
#include "SocketTCP.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ServerTCP::ServerTCP(const char *ip, unsigned short port)
        : Server(ip, port)
    {
        FI();

        FO();
    }

    /**
     * Destructor
     */
    ServerTCP::~ServerTCP()
    {
        FI();

        FO();
    }

    bool ServerTCP::onInitialize()
    {
        FI();

        if (ip() == nullptr)
        {
            FO();
            return false;
        }

        if (socket() == nullptr)
        {
            FO();
            return false;
        }

        SocketTCP *pSocket = reinterpret_cast<SocketTCP *>(socket());
        if (pSocket == nullptr)
        {
            FO();
            return false;
        }

        if (!pSocket->Create())
        {
            FO();
            return false;
        }

        pSocket->setOptReusedAddress(true);
        pSocket->setOptNonBlocking(true);

        if (!pSocket->Bind(ip(), port()))
        {
            FO();
            return false;
        }

        if (!pSocket->Listen())
        {
            FO();
            return false;
        }

        FO();
        return true;
    }

    int ServerTCP::onRun()
    {
        FI();

        SocketTCP *pSocket = reinterpret_cast<SocketTCP *>(socket());
        if (pSocket == nullptr)
        {
            FO();
            return 1;
        }

        while (isRunning())
        {
            if (pSocket->isReadWritable())
            {
                FS("isReadWritable");
                Socket *incommingSocket = pSocket->Accept();
                if (incommingSocket != nullptr)
                {
                    Connection *newConnection = this->onNewConnection(incommingSocket);
                    if (newConnection != nullptr)
                    {
                        mConnMap.insert(std::make_pair(newConnection->handle(), newConnection));
                        newConnection->Establish();
                    }
                }
            }
        }

        FO();
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}