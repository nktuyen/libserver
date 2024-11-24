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

        memset(mIP, 0, SERVER_IP_LEN);
        if (ip != nullptr)
        {
            strncpy(mIP, ip, SERVER_IP_LEN);
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}