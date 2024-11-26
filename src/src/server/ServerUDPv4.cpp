///////////////////////////////////////////////////////////
//  ServerUDPv4.cpp
//  Implementation of the Class ServerUDPv4
//  Created on:      27-Nov-2024 1:37:11 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerUDPv4.hpp"
#include "SocketUDPv4.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ServerUDPv4::ServerUDPv4(const char *ip, unsigned short port)
        : ServerUDP(ip, port)
    {
        FI();

        mSocket = new SocketUDPv4();

        FO();
    }

    /**
     * Destructor
     */
    ServerUDPv4::~ServerUDPv4()
    {
        FI();

        FO();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}