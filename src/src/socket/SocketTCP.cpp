///////////////////////////////////////////////////////////
//  SocketTCP.cpp
//  Implementation of the Class SocketTCP
//  Created on:      22-Nov-2024 12:55:53 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketTCP.hpp"
#include "Logger.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * Constructor
	 */
	SocketTCP::SocketTCP(int nFamily)
		: Socket(nFamily, SOCK_STREAM, IPPROTO_TCP)
	{
	}

	/**
	 * Destructor
	 */
	SocketTCP::~SocketTCP()
	{
	}

	/**
	 * Associates a local address with a socket
	 */
	bool SocketTCP::Bind(const char *ip, unsigned short port)
	{
		FI();
		FO();
		return Socket::Bind(ip, port);
	}
	/**
	 * Places a socket in a state in which it is listening for an incoming connection
	 */
	bool SocketTCP::Listen(int backlog)
	{
		FI();
		FO();
		return Socket::Listen(backlog);
	}
	/**
	 * Establishes a connection to a specified socket
	 */
	bool SocketTCP::Connect(const char *ip, unsigned short port)
	{
		FI();
		FO();
		return Socket::Connect(ip, port);
	}
	/**
	 * Receives data from a connected socket or a bound connectionless socket
	 */
	int SocketTCP::Receive(char *buffer, int len, int flags)
	{
		FI();
		FO();
		return Socket::Receive(buffer, len, flags);
	}
	/**
	 * Sends data on a connected socket
	 */
	int SocketTCP::Send(const char *buffer, int len, int flags)
	{
		FI();
		FO();
		return Socket::Send(buffer, len, flags);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
}