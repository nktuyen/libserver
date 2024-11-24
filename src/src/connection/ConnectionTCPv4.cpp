///////////////////////////////////////////////////////////
//  ConnectionTCPv4.cpp
//  Implementation of the Class ConnectionTCPv4
//  Created on:      24-Nov-2024 9:55:13 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ConnectionTCPv4.hpp"
#include "ServerTCPv4.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ConnectionTCPv4::ConnectionTCPv4(ServerTCPv4 *pServer, Socket *pSocket)
        : ConnectionTCP(pServer, pSocket)
    {
    }

    /**
     * Destructor
     */
    ConnectionTCPv4::~ConnectionTCPv4()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
}