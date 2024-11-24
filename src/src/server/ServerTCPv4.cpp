///////////////////////////////////////////////////////////
//  ServerTCPv4.cpp
//  Implementation of the Class ServerTCPv4
//  Created on:      24-Nov-2024 9:57:30 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerTCPv4.hpp"
#include "SocketTCPv4.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ServerTCPv4::ServerTCPv4(const char *ip, unsigned short port)
        : ServerTCP(ip, port)
    {
        FI();
        mSocket = new SocketTCPv4();

        FO();
    }

    /**
     * Destructor
     */
    ServerTCPv4::~ServerTCPv4()
    {
        FI();

        FO();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}