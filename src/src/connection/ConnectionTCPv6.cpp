///////////////////////////////////////////////////////////
//  ConnectionTCPv6.cpp
//  Implementation of the Class ConnectionTCPv6
//  Created on:      25-Nov-2024 11:31:38 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "ConnectionTCPv6.hpp"
#include "ServerTCPv6.hpp"
#include "Logger.hpp"

namespace T
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * Constructor
     */
    ConnectionTCPv6::ConnectionTCPv6(ServerTCPv6 *pServer, Socket *pSocket, bool aliveChecker, int aliveCheckerTimeout)
        : ConnectionTCP(pServer, pSocket, aliveChecker, aliveCheckerTimeout)
    {
        FI();

        FO();
    }

    /**
     * Destructor
     */
    ConnectionTCPv6::~ConnectionTCPv6()
    {
        FI();

        FO();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
}