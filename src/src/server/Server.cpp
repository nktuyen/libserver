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

        FM("mIPAddr=%s, mPort=%d", mIPAddr, mPort);

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