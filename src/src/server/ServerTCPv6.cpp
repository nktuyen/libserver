///////////////////////////////////////////////////////////
//  ServerTCPv6.cpp
//  Implementation of the Class ServerTCPv6
//  Created on:      25-Nov-2024 11:41:26 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerTCPv6.hpp"
#include "SocketTCPv6.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ServerTCPv6::ServerTCPv6(const char *ip, unsigned short port)
        : ServerTCP(ip, port)
    {
        FI();

        mSocket = new SocketTCPv6();

        FO();
    }

    ServerTCPv6::~ServerTCPv6()
    {
        FI();

        FO();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}