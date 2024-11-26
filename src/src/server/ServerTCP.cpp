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

        auto ite = mConnMap.begin();
        for (; ite != mConnMap.end(); ++ite)
        {
            ConnectionTCP *pConn = ite->second;
            if (pConn != nullptr)
                delete pConn;
        }
        mConnMap.clear();

        FO();
    }

    ConnectionTCP *ServerTCP::onNewConnection(SocketTCP *pSocket)
    {
        FI();

        FO();
        return new ConnectionTCP(this, pSocket);
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
                Socket *incommingSocket = pSocket->Accept();
                if (incommingSocket != nullptr)
                {
                    ConnectionTCP *newConnection = this->onNewConnection(reinterpret_cast<SocketTCP *>(incommingSocket));
                    if (newConnection != nullptr)
                    {
                        if (newConnection->Establish())
                        {
                            mConnMap.insert(std::make_pair(newConnection->handle(), newConnection));
                        }
                        else
                        {
                            delete newConnection;
                        }
                    }
                }
            }
        }

        FO();
        return 0;
    }

    void ServerTCP::onConnectionClose(ConnectionTCP *conn)
    {
        FI();
        if (conn == nullptr)
        {
            FO();
            return;
        }

        if (conn->handle() == InvalidConnection)
        {
            FO();
            return;
        }

        auto ite = mConnMap.find(conn->handle());
        if (ite != mConnMap.end())
        {
            ConnectionTCP *pConn = ite->second;
            delete pConn;
            mConnMap.erase(ite);
        }

        FO();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}