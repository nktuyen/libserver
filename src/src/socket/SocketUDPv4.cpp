///////////////////////////////////////////////////////////
//  SocketUDPv4.cpp
//  Implementation of the Class SocketUDPv4
//  Created on:      22-Nov-2024 1:00:09 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketUDPv4.hpp"

namespace T
{
    /**
     * Constructor
     */
    SocketUDPv4::SocketUDPv4()
        : SocketUDP(AF_INET)
    {
    }

    /**
     * Destructor
     */
    SocketUDPv4::~SocketUDPv4()
    {
    }
}