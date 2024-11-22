///////////////////////////////////////////////////////////
//  Socket.cpp
//  Implementation of the Class Socket
//  Created on:      21-Nov-2024 11:21:43 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "Socket.hpp"
#include "Logger.hpp"
#ifndef _WINDOWS
#include <errno.h>
#include <arpa/inet.h>
#endif //_WINDOWS
namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * Constructor
	 */
	Socket::Socket(int nFamily, int nType, int nProtocol)
		: mHandle(InvalidHandle), mFamily(nFamily), mType(nType), mProtocol(nProtocol)
	{
		FI();

		FO();
	}

	/**
	 * Destructor
	 */
	Socket::~Socket()
	{
		FI();

		this->Close();

		FO();
	}

	/**
	 * Close created socket
	 */
	bool Socket::Close()
	{
		FI();

		int res = 0;

		if (mHandle != InvalidHandle)
		{
#ifdef _WINDOWS
			res = ::closesocket(mHandle);
#else  // ! _WINDOWS
			res = ::close(mHandle);
#endif //_WINDOWS
			mHandle = InvalidHandle;
		}

		FO();
		return res != SocketError;
	}

	/**
	 * Create actual socket
	 */
	bool Socket::Create()
	{
		FI();

		try
		{
			mHandle = ::socket(mFamily, mType, mProtocol);
		}
		catch (const std::exception &ex)
		{
			FS(ex.what());
		}

		FO();
		return mHandle != InvalidHandle;
	}

	/**
	 * Associates a local address with a socket
	 */
	bool Socket::Bind(const char *ip, unsigned short port)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}
		struct sockaddr_in addrinfo = {0};
		addrinfo.sin_family = mFamily;
		addrinfo.sin_port = htons(port);
		addrinfo.sin_addr.s_addr = inet_addr(ip);
		int res = ::bind(mHandle, reinterpret_cast<sockaddr *>(&addrinfo), sizeof(addrinfo));

		FO();
		return res != SocketError;
	}

	/**
	 * Places a socket in a state in which it is listening for an incoming connection
	 */
	bool Socket::Listen(int backlog)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		int res = ::listen(mHandle, backlog);

		FO();
		return res != SocketError;
		;
	}

	/**
	 * Establishes a connection to a specified socket
	 */
	bool Socket::Connect(const char *ip, unsigned short port)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		struct sockaddr_in addrinfo = {0};
		addrinfo.sin_family = mFamily;
		addrinfo.sin_port = htons(port);
		addrinfo.sin_addr.s_addr = inet_addr(ip);

		int res = ::connect(mHandle, reinterpret_cast<sockaddr *>(&addrinfo), sizeof(addrinfo));

		FO();
		return res != SocketError;
	}

	/**
	 * Permits an incoming connection attempt on a socket
	 */
	Socket *Socket::Accept()
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return nullptr;
		}

		struct sockaddr_in addrinfo = {0};
#ifdef _WINDOWS
		int len = sizeof(addrinfo);
#else  // ! _WINDOWS
		socklen_t len = sizeof(addrinfo);
#endif //_WINDOWS
		SocketHandle hSocket = ::accept(mHandle, reinterpret_cast<sockaddr*>( &addrinfo), &len);
		if (hSocket == InvalidHandle)
		{
			FO();
			return nullptr;
		}

		const char *ip = inet_ntoa(addrinfo.sin_addr);
		Socket *newSocket = this->onAccepting(hSocket, addrinfo.sin_family, ip, ntohs(addrinfo.sin_port));

		FO();
		return newSocket;
	}

	/**
	 * Determines whether the socket is readable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isReadable(unsigned int timeout)
	{

		return false;
	}

	/**
	 * Determines whether the socket is writable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isWritable(unsigned int timeout)
	{

		return false;
	}

	/**
	 * Receives data from a connected socket or a bound connectionless socket
	 */
	int Socket::Receive(char *buffer, int len, int flags)
	{

		return 0;
	}

	/**
	 * Receives a datagram and stores the source address
	 */
	int Socket::ReceiveFrom(char *buffer, int len, const char *ip, unsigned short port, int flags)
	{

		return 0;
	}

	/**
	 * Sends data on a connected socket
	 */
	int Socket::Send(const char *buffer, int len, int flags)
	{

		return 0;
	}

	/**
	 * Sends data to a specific destination
	 */
	int Socket::SendTo(const char *buffer, int len, const char *ip, unsigned short port, int flags)
	{

		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace T