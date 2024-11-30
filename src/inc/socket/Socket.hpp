///////////////////////////////////////////////////////////
//  Socket.hpp
//  Implementation of the Class Socket
//  Created on:      21-Nov-2024 11:21:43 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////
#pragma once
#if !defined(EA_12B02B79_954B_49c3_9E6F_604C3D7BA59C__INCLUDED_)
#define EA_12B02B79_954B_49c3_9E6F_604C3D7BA59C__INCLUDED_

#ifdef _WINDOWS
#include <Windows.h>
#ifndef AF_INET6
#define AF_INET6 23
#endif // AF_INET6
typedef SOCKET SocketHandle;
typedef int SocketSize_t;
#define InvalidSocketHandle INVALID_SOCKET
#define SocketError SOCKET_ERROR
#else // ! _WINDOWS
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
typedef int SocketHandle;
typedef socklen_t SocketSize_t;
#define InvalidSocketHandle (SocketHandle)(-1)
#define SocketError -1
#endif //_WINDOWS

namespace T
{
	class Socket
	{
		friend class Server;

	protected:
		/**
		 * Constructor
		 */
		explicit Socket(int nFamily, int nType, int nProtocol = 0);

	public:
		/**
		 * Destructor
		 */
		virtual ~Socket();
		/**
		 * Return socket's handle
		 */
		inline SocketHandle handle()
		{
			return mHandle;
		}
		/**
		 * Return socket's address family
		 */
		inline int family()
		{
			return mFamily;
		}
		/**
		 * Return socket's protocol
		 */
		inline int protocol()
		{
			return mProtocol;
		}
		/**
		 * Return socket's type
		 */
		inline int type()
		{
			return mType;
		}
		/**
		 * Return reused address option value
		 */
		inline bool optReusedAddress()
		{
			return mOptReusedAddr;
		}
		/**
		 * Set reused address option
		 */
		bool setOptReusedAddress(bool bReused);
		/**
		 * Return non-blocking option value
		 */
		inline bool optNonBlocking()
		{
			return mOptNonBlocking;
		}
		/**
		 * Set non-blocking option
		 */
		bool setOptNonBlocking(bool bNonBlock);
		/**
		 * Return receive buffer size
		 */
		inline int optRecvBufferSize()
		{
			return mOptRecvBufferSize;
		}
		/**
		 * Set receive buffer size
		 */
		bool setOptRecvBufferSize(int nSize);
		/**
		 * Return receive timeout
		 */
		inline int optRecvTimeout()
		{
			return mOptRecvTimeout;
		}
		/**
		 * Set receive timeout
		 */
		bool setOptRecvTimeout(int timeout_ms);
		/**
		 * Return send buffer size
		 */
		inline int optSendBufferSize()
		{
			return mOptSendBufferSize;
		}
		/**
		 * Set send buffer size
		 */
		bool setOptSendBufferSize(int nSize);
		/**
		 * Return send timeout
		 */
		int optSendTimeout()
		{
			return mOptSendTimeout;
		}
		/**
		 * Set send timeout
		 */
		bool setOptSendTimeout(int timeout_ms);
		/**
		 * Close created socket
		 */
		bool Close();
		/**
		 * Create actual socket
		 */
		bool Create();
		/**
		 * Determines whether the socket is readable or not, waiting if necessary, to
		 * perform synchronous I/O
		 */
		bool isReadable(unsigned int timeout_ms = 0);
		/**
		 * Determines whether the socket is writable or not, waiting if necessary, to
		 * perform synchronous I/O
		 */
		bool isWritable(unsigned int timeout_ms = 0);
		/**
		 * Determines whether the socket is writable/readable or not, waiting if necessary, to
		 * perform synchronous I/O
		 */
		bool isReadWritable(unsigned int timeout_ms = 0);

	private:
		/**
		 * Socket's address family
		 */
		int mFamily;
		/**
		 * Socket's handle
		 */
		SocketHandle mHandle;
		/**
		 * Socket's protocol
		 */
		int mProtocol;
		/**
		 * Socket's type
		 */
		int mType;
		/**
		 * Reused address option
		 */
		bool mOptReusedAddr;
		/**
		 * Received buffer size
		 */
		int mOptRecvBufferSize;
		/**
		 * Send buffer size
		 */
		int mOptSendBufferSize;
		/**
		 * Send timeout
		 */
		int mOptSendTimeout;
		/**
		 * Receive timeout
		 */
		int mOptRecvTimeout;
		/**
		 * Non-blocking mode status
		 */
		bool mOptNonBlocking;

	protected:
		/**
		 * Associates a local address with a socket
		 */
		virtual bool Bind(const char *ip, unsigned short port);
		/**
		 * Places a socket in a state in which it is listening for an incoming connection
		 */
		virtual bool Listen(int backlog = SOMAXCONN);
		/**
		 * Permits an incoming connection attempt on a socket
		 */
		virtual Socket *Accept();
		/**
		 * Establishes a connection to a specified socket
		 */
		virtual bool Connect(const char *ip, unsigned short port);
		/**
		 * Receives data from a connected socket or a bound connectionless socket
		 */
		virtual int Receive(char *buffer, int len, int flags = 0);
		/**
		 * Sends data on a connected socket
		 */
		virtual int Send(const char *buffer, int len, int flags = 0);
		/**
		 * Receives a datagram and stores the source address
		 */
		virtual int ReceiveFrom(char *buffer, int len, const char *ip, unsigned short port, int flags = 0);
		/**
		 * Sends data to a specific destination
		 */
		virtual int SendTo(const char *buffer, int len, const char *ip, unsigned short port, int flags = 0);

	protected:
		/**
		 * Callback method which is called on accepting new connection. Return new socket object to accept the connect. Return null to reject
		 */
		virtual Socket *onAccepting(SocketHandle hSocket, int nFamily, const char *ip, unsigned short port) { return nullptr; }
		/**
		 * Attach to an existing socket by handle
		 */
		virtual Socket &Attach(SocketHandle hSocket);
	};
}
#endif // !defined(EA_12B02B79_954B_49c3_9E6F_604C3D7BA59C__INCLUDED_)
