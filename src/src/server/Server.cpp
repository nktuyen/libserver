///////////////////////////////////////////////////////////
//  Server.cpp
//  Implementation of the Class Server
//  Created on:      24-Nov-2024 1:25:56 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "Server.hpp"
#include "Socket.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**
     * Constructor
     */
    Server::Server(const char *ip, unsigned short port)
        : mSocket(nullptr), mPort(port)
    {
        FI();

        memset(mIPAddr, 0, SERVER_IP_LEN);
        if (ip != nullptr)
        {
            strncpy(mIPAddr, ip, SERVER_IP_LEN);
        }

        FO();
    }

    /**
     * Destructor
     */
    Server::~Server()
    {
        FI();

        FO();
    }

    void Server ::onConnectionClose(Connection *conn)
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
            Connection *pConn = ite->second;
            delete pConn;
            mConnMap.erase(ite);
        }

        FO();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
}