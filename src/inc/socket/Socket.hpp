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
#define AF_INET6 10
#endif // AF_INET6
typedef SOCKET SocketHandle;
#define InvalidHandle INVALID_SOCKET
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
typedef int SocketHandle;
#define InvalidHandle (SocketHandle)(-1)
#define SocketError -1
#endif //_WINDOWS

namespace T
{
	class Socket
	{
	public:
		Socket();

		/**
		 * Constructor
		 */
		explicit Socket(int nFamily, int nType, int nProtocol = 0);
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
		bool isReadable(unsigned int timeout_ms);
		/**
		 * Determines whether the socket is writable or not, waiting if necessary, to
		 * perform synchronous I/O
		 */
		bool isWritable(unsigned int timeout_ms);
		/**
		 * Determines whether the socket is writable/readable or not, waiting if necessary, to
		 * perform synchronous I/O
		 */
		bool isReadWritable(unsigned int timeout_ms);

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
		virtual int Receive(char *buffer, int len, int flags);
		/**
		 * Sends data on a connected socket
		 */
		virtual int Send(const char *buffer, int len, int flags);
		/**
		 * Receives a datagram and stores the source address
		 */
		virtual int ReceiveFrom(char *buffer, int len, const char *ip, unsigned short port, int flags = 0);
		/**
		 * Sends data to a specific destination
		 */
		virtual int SendTo(const char *buffer, int len, const char *ip, unsigned short port, int flags = 0);

	protected:
		virtual Socket *onAccepting(SocketHandle hSocket, int nFamily, const char *ip, unsigned short port) { return nullptr; }
	};
}
#endif // !defined(EA_12B02B79_954B_49c3_9E6F_604C3D7BA59C__INCLUDED_)
