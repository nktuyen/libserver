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
		: mHandle(InvalidHandle),
		  mFamily(nFamily),
		  mType(nType),
		  mProtocol(nProtocol),
		  mOptReusedAddr(false),
		  mOptRecvBufferSize(-1),
		  mOptSendBufferSize(-1),
		  mOptSendTimeout(-1),
		  mOptRecvTimeout(-1),
		  mOptNonBlocking(false)
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
	 * Attach to an existing socket by handle
	 */
	Socket &Socket::Attach(SocketHandle hSocket)
	{
		if (mHandle != InvalidHandle)
		{
			this->Close();
		}
		mHandle = hSocket;
		if (mHandle != InvalidHandle)
		{
			// Obtain options
			char buffer[sizeof(int)] = {0};
			SocketSize_t len = sizeof(buffer);
			// SO_REUSEADDR
			// memset(buffer, 0, sizeof(buffer));
			int res = ::getsockopt(mHandle, SOL_SOCKET, SO_REUSEADDR, buffer, &len);
			if (res != SocketError)
			{
				memcpy(&mOptReusedAddr, &buffer, len);
			}
			// SO_RCVBUF
			memset(buffer, 0, sizeof(buffer));
			res = ::getsockopt(mHandle, SOL_SOCKET, SO_RCVBUF, buffer, &len);
			if (res != SocketError)
			{
				memcpy(&mOptRecvBufferSize, buffer, len);
			}
			// SO_RCVTIMEO
			memset(buffer, 0, sizeof(buffer));
			res = ::getsockopt(mHandle, SOL_SOCKET, SO_RCVTIMEO, buffer, &len);
			if (res != SocketError)
			{
				memcpy(&mOptRecvTimeout, buffer, len);
			}
			// SO_SNDBUF
			memset(buffer, 0, sizeof(buffer));
			res = ::getsockopt(mHandle, SOL_SOCKET, SO_SNDBUF, buffer, &len);
			if (res != SocketError)
			{
				memcpy(&mOptSendBufferSize, buffer, len);
			}
			// SO_SNDTIMEO
			memset(buffer, 0, sizeof(buffer));
			res = ::getsockopt(mHandle, SOL_SOCKET, SO_SNDTIMEO, buffer, &len);
			if (res != SocketError)
			{
				memcpy(&mOptSendTimeout, buffer, len);
			}

			// Set initial non-blocking mode
#ifdef _WINDOWS
			u_long flags = mOptNonBlocking ? 1 : 0;
			res = ::ioctlsocket(mHandle, FIONBIO, &flags);
#else  // ! _WINDOWS
			int flags = fcntl(mHandle, F_GETFL, 0);
			res = ::fcntl(mHandle, F_SETFL, mOptNonBlocking ? (flags | O_NONBLOCK) : (flags ^ O_NONBLOCK));
#endif //_WINDOWS
		}
		return *this;
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

			if (mHandle != InvalidHandle)
			{
				// Obtain options
				char buffer[sizeof(int)] = {0};
				SocketSize_t len = sizeof(buffer);
				// SO_REUSEADDR
				// memset(buffer, 0, sizeof(buffer));
				int res = ::getsockopt(mHandle, SOL_SOCKET, SO_REUSEADDR, buffer, &len);
				if (res != SocketError)
				{
					memcpy(&mOptReusedAddr, &buffer, len);
				}
				// SO_RCVBUF
				memset(buffer, 0, sizeof(buffer));
				res = ::getsockopt(mHandle, SOL_SOCKET, SO_RCVBUF, buffer, &len);
				if (res != SocketError)
				{
					memcpy(&mOptRecvBufferSize, buffer, len);
				}
				// SO_RCVTIMEO
				memset(buffer, 0, sizeof(buffer));
				res = ::getsockopt(mHandle, SOL_SOCKET, SO_RCVTIMEO, buffer, &len);
				if (res != SocketError)
				{
					memcpy(&mOptRecvTimeout, buffer, len);
				}
				// SO_SNDBUF
				memset(buffer, 0, sizeof(buffer));
				res = ::getsockopt(mHandle, SOL_SOCKET, SO_SNDBUF, buffer, &len);
				if (res != SocketError)
				{
					memcpy(&mOptSendBufferSize, buffer, len);
				}
				// SO_SNDTIMEO
				memset(buffer, 0, sizeof(buffer));
				res = ::getsockopt(mHandle, SOL_SOCKET, SO_SNDTIMEO, buffer, &len);
				if (res != SocketError)
				{
					memcpy(&mOptSendTimeout, buffer, len);
				}

				// Set initial non-blocking mode
#ifdef _WINDOWS
				u_long flags = mOptNonBlocking ? 1 : 0;
				res = ::ioctlsocket(mHandle, FIONBIO, &flags);
#else  // ! _WINDOWS
				int flags = fcntl(mHandle, F_GETFL, 0);
				res = ::fcntl(mHandle, F_SETFL, mOptNonBlocking ? (flags | O_NONBLOCK) : (flags ^ O_NONBLOCK));
#endif //_WINDOWS
			}
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
		SocketSize_t len = sizeof(addrinfo);
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

		newSocket->Attach(hSocket);
		FO();
		return newSocket;
	}

	/**
	 * Determines whether the socket is readable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isReadable(unsigned int timeout_ms)
	{
		if (mHandle == InvalidHandle)
		{
			return false;
		}

		struct timeval timeout = {0};
		timeout.tv_usec = timeout_ms;
		fd_set readfd;
		FD_ZERO(&readfd);
		FD_SET(mHandle, &readfd);

		int res = ::select(mHandle + 1, &readfd, nullptr, nullptr, &timeout);
		if (res <= 0)
		{
			return false;
		}

		return FD_ISSET(mHandle, &readfd) > 0;
	}

	/**
	 * Determines whether the socket is writable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isWritable(unsigned int timeout_ms)
	{
		if (mHandle == InvalidHandle)
		{
			return false;
		}

		struct timeval timeout = {0};
		timeout.tv_usec = timeout_ms;
		fd_set writefd;
		FD_ZERO(&writefd);
		FD_SET(mHandle, &writefd);

		int res = ::select(mHandle + 1, nullptr, &writefd, nullptr, &timeout);
		if (res <= 0)
		{
			return false;
		}

		return FD_ISSET(mHandle, &writefd) > 0;
	}

	/**
	 * Determines whether the socket is writable/readable or not, waiting if necessary, to
	 * perform synchronous I/O
	 */
	bool Socket::isReadWritable(unsigned int timeout_ms)
	{

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

		int res = ::select(mHandle + 1, &readfd, &writefd, nullptr, &timeout);
		if (res <= 0)
		{
			return false;
		}

		return (FD_ISSET(mHandle, &writefd) > 0) || (FD_ISSET(mHandle, &readfd) > 0);
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
		SocketSize_t outlen = 0;
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
		SocketSize_t outlen = sizeof(addrinfo);
		addrinfo.sin_family = mFamily;
		addrinfo.sin_port = htons(port);
		addrinfo.sin_addr.s_addr = inet_addr(ip);

		FO();
		return ::sendto(mHandle, buffer, len, flags, reinterpret_cast<sockaddr *>(&addrinfo), outlen);
	}

	/**
	 * Set non-blocking option
	 */
	bool Socket::setOptNonBlocking(bool bNonBlocking)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		// Set initial non-blocking mode
#ifdef _WINDOWS
		u_long flags = bNonBlocking ? 1 : 0;
		int res = ::ioctlsocket(mHandle, FIONBIO, &flags);
#else  // ! _WINDOWS
		int flags = fcntl(mHandle, F_GETFL, 0);
		int res = ::fcntl(mHandle, F_SETFL, bNonBlocking ? (flags | O_NONBLOCK) : (flags ^ O_NONBLOCK));
#endif //_WINDOWS
		mOptNonBlocking = bNonBlocking;

		FO();
		return res != SocketError;
	}

	/**
	 * Set reused address option
	 */
	bool Socket::setOptReusedAddress(bool bReused)
	{
		FI();

		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		char buffer[sizeof(int)] = {0};
		memcpy(buffer, &bReused, sizeof(bReused));
		SocketSize_t len = sizeof(buffer);
		int res = ::setsockopt(mHandle, SOL_SOCKET, SO_REUSEADDR, buffer, len);
		mOptReusedAddr = bReused;

		FO();
		return res != SocketError;
	}

	/**
	 * Set receive buffer size
	 */
	bool Socket::setOptRecvBufferSize(int nSize)
	{
		FI();
		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		char buffer[sizeof(int)] = {0};
		memcpy(buffer, &nSize, sizeof(nSize));
		SocketSize_t len = sizeof(buffer);
		int res = ::setsockopt(mHandle, SOL_SOCKET, SO_RCVBUF, buffer, len);
		mOptRecvBufferSize = nSize;

		FO();
		return res != SocketError;
	}

	/**
	 * Set receive timeout
	 */
	bool Socket::setOptRecvTimeout(int timeout_ms)
	{
		FI();
		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		char buffer[sizeof(int)] = {0};
		memcpy(buffer, &timeout_ms, sizeof(timeout_ms));
		SocketSize_t len = sizeof(buffer);
		int res = ::setsockopt(mHandle, SOL_SOCKET, SO_RCVTIMEO, buffer, len);
		mOptRecvTimeout = timeout_ms;

		FO();
		return res != SocketError;
	}

	/**
	 * Set send buffer size
	 */
	bool Socket::setOptSendBufferSize(int nSize)
	{
		FI();
		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		char buffer[sizeof(int)] = {0};
		memcpy(buffer, &nSize, sizeof(nSize));
		SocketSize_t len = sizeof(buffer);
		int res = ::setsockopt(mHandle, SOL_SOCKET, SO_SNDBUF, buffer, len);
		mOptSendBufferSize = nSize;

		FO();
		return res != SocketError;
	}

	/**
	 * Set send timeout
	 */
	bool Socket::setOptSendTimeout(int timeout_ms)
	{
		FI();
		if (mHandle == InvalidHandle)
		{
			FO();
			return false;
		}

		char buffer[sizeof(int)] = {0};
		memcpy(buffer, &timeout_ms, sizeof(timeout_ms));
		SocketSize_t len = sizeof(buffer);
		int res = ::setsockopt(mHandle, SOL_SOCKET, SO_SNDTIMEO, buffer, len);
		mOptSendTimeout = timeout_ms;

		FO();
		return res != SocketError;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace T