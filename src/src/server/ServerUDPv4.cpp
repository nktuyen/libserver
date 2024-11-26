///////////////////////////////////////////////////////////
//  ServerUDPv4.cpp
//  Implementation of the Class ServerUDPv4
//  Created on:      27-Nov-2024 1:37:11 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ServerUDPv4.hpp"
#include "SocketUDPv4.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ServerUDPv4::ServerUDPv4(const char *ip, unsigned short port)
        : ServerUDP(ip, port)
    {
        mSocket = new SocketUDPv4();
    }

    /**
     * Destructor
     */
    ServerUDPv4::~ServerUDPv4()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}