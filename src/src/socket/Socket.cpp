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
		SocketHandle hSocket = ::accept(mHandle, reinterpret_cast<sockaddr *>(&addrinfo), &len);
		if (hSocket == InvalidHandle)
		{
			FO();
			return nullptr;
		}

		const char *ip = inet_ntoa(addrinfo.sin_addr);
		Socket *newSocket = this->onAccepting(hSocket, addrinfo.sin_family, ip, ntohs(addrinfo.sin_port));
		if (newSocket == nullptr)
		{
#ifdef _WINDOWS
			::closesocket(hSocket);
#else  // ! _WINDOWS
			::close(hSocket);
#endif //_WINDOWS
			hSocket = InvalidHandle;
		}

		FO();
		return newSocket;
	}

	/**
	 * Determines whether the socket is readable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isReadable(unsigned int timeout_ms)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		struct timeval timeout = {0};
		timeout.tv_usec = timeout_ms;
		fd_set readfd;
		FD_ZERO(&readfd);
		FD_SET(mHandle, &readfd);

		int res = ::select(mHandle, &readfd, nullptr, nullptr, &timeout);
		if (res <= 0)
		{
			FO();
			return false;
		}

		FO();
		return FD_ISSET(mHandle, &readfd);
	}

	/**
	 * Determines whether the socket is writable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isWritable(unsigned int timeout_ms)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		struct timeval timeout = {0};
		timeout.tv_usec = timeout_ms;
		fd_set writefd;
		FD_ZERO(&writefd);
		FD_SET(mHandle, &writefd);

		int res = ::select(mHandle, nullptr, &writefd, nullptr, &timeout);
		if (res <= 0)
		{
			FO();
			return false;
		}

		FO();
		return FD_ISSET(mHandle, &writefd);
	}

	/**
	 * Determines whether the socket is writable/readable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isReadWritable(unsigned int timeout_ms)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		struct timeval timeout = {0};
		timeout.tv_usec = timeout_ms;
		fd_set writefd;
		fd_set readfd;
		FD_ZERO(&writefd);
		FD_ZERO(&readfd);
		FD_SET(mHandle, &writefd);
		FD_SET(mHandle, &readfd);

		int res = ::select(mHandle, &readfd, &writefd, nullptr, &timeout);
		if (res <= 0)
		{
			FO();
			return false;
		}

		FO();
		return (FD_ISSET(mHandle, &writefd)) || (FD_ISSET(mHandle, &readfd));
	}

	/**
	 * Receives data from a connected socket or a bound connectionless socket
	 */
	int Socket::Receive(char *buffer, int len, int flags)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return SocketError;
		}

		FO();
		return ::recv(mHandle, buffer, len, flags);
	}

	/**
	 * Receives a datagram and stores the source address
	 */
	int Socket::ReceiveFrom(char *buffer, int len, const char *ip, unsigned short port, int flags)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return SocketError;
		}

		struct sockaddr_in addrinfo = {0};
#ifdef _WINDOWS
		int outlen = 0;
#else  // ! _WINDOWS
		socklen_t outlen = 0;
#endif //_WINDOWS
		addrinfo.sin_family = mFamily;
		addrinfo.sin_port = htons(port);
		addrinfo.sin_addr.s_addr = inet_addr(ip);

		FO();
		return ::recvfrom(mHandle, buffer, len, flags, reinterpret_cast<sockaddr *>(&addrinfo), &outlen);
	}

	/**
	 * Sends data on a connected socket
	 */
	int Socket::Send(const char *buffer, int len, int flags)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return SocketError;
		}

		FO();
		return ::send(mHandle, buffer, len, flags);
	}

	/**
	 * Sends data to a specific destination
	 */
	int Socket::SendTo(const char *buffer, int len, const char *ip, unsigned short port, int flags)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return SocketError;
		}

		struct sockaddr_in addrinfo = {0};
#ifdef _WINDOWS
		int outlen = sizeof(addrinfo);
#else  // ! _WINDOWS
		socklen_t outlen = sizeof(addrinfo);
#endif //_WINDOWS
		addrinfo.sin_family = mFamily;
		addrinfo.sin_port = htons(port);
		addrinfo.sin_addr.s_addr = inet_addr(ip);

		FO();
		return ::sendto(mHandle, buffer, len, flags, reinterpret_cast<sockaddr *>(&addrinfo), outlen);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace T