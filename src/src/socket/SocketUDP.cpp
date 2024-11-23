///////////////////////////////////////////////////////////
//  SocketUDP.cpp
//  Implementation of the Class SocketUDP
//  Created on:      22-Nov-2024 12:55:46 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketUDP.hpp"
#include "Logger.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * Constructor
	 */
	SocketUDP::SocketUDP(int nFamily)
		: Socket(nFamily, SOCK_DGRAM, IPPROTO_UDP)
	{
	}

	/**
	 * Destructor
	 */
	SocketUDP::~SocketUDP()
	{
	}

	/**
	 * Receives a datagram and stores the source address
	 */
	int SocketUDP::ReceiveFrom(char *buffer, int len, const char *ip, unsigned short port, int flags)
	{
		FI();
		FO();
		return Socket::ReceiveFrom(buffer, len, ip, port, flags);
	}

	/**
	 * Sends data to a specific destination
	 */
	int SocketUDP::SendTo(const char *buffer, int len, const char *ip, unsigned short port, int flags)
	{
		FI();
		FO();
		return Socket::SendTo(buffer, len, ip, port, flags);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
}