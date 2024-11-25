///////////////////////////////////////////////////////////
//  SocketTCPv6.cpp
//  Implementation of the Class SocketTCPv6
//  Created on:      22-Nov-2024 1:00:22 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketTCPv6.hpp"
#include "Logger.hpp"
#include <iostream>
#include <arpa/inet.h>

namespace T
{
    /**
     * Constructor
     */
    SocketTCPv6::SocketTCPv6()
        : SocketTCP(AF_INET6)
    {
        FI();
        FO();
    }

    /**
     * Destructor
     */
    SocketTCPv6::~SocketTCPv6()
    {
        FI();
        FO();
    }

    /**
     * Associates a local address with a socket
     */
    bool SocketTCPv6::Bind(const char *ip, unsigned short port)
    {
        FI();

        if (handle() == InvalidHandle)
        {
            FO();
            return false;
        }

        struct sockaddr_in6 addrinfo = {0};
        addrinfo.sin6_family = family();
        addrinfo.sin6_port = htons(port);
        inet_pton(family(), ip, &addrinfo.sin6_addr);
        int res = ::bind(handle(), reinterpret_cast<sockaddr *>(&addrinfo), sizeof(addrinfo));

        FO();
        return res != SocketError;
    }
}