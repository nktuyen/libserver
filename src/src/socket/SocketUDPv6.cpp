///////////////////////////////////////////////////////////
//  SocketUDPv6.cpp
//  Implementation of the Class SocketUDPv6
//  Created on:      22-Nov-2024 1:00:15 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketUDPv6.hpp"

namespace T
{
    /**
     * Constructor
     */
    SocketUDPv6::SocketUDPv6()
        : SocketUDP(AF_INET6)
    {
    }

    /**
     * Destructor
     */
    SocketUDPv6::~SocketUDPv6()
    {
    }
}