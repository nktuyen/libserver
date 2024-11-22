///////////////////////////////////////////////////////////
//  SocketTCPv4.cpp
//  Implementation of the Class SocketTCPv4
//  Created on:      22-Nov-2024 1:00:19 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketTCPv4.hpp"

namespace T
{
    /**
     * Constructor
     */
    SocketTCPv4::SocketTCPv4()
        : SocketTCP(AF_INET)
    {
    }

    /**
     * Destructor
     */
    SocketTCPv4::~SocketTCPv4()
    {
    }
}