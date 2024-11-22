///////////////////////////////////////////////////////////
//  SocketTCP.h
//  Implementation of the Class SocketTCP
//  Created on:      22-Nov-2024 12:55:53 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_E8306D78_E2A9_445f_ABCD_217BCCF9816B__INCLUDED_)
#define EA_E8306D78_E2A9_445f_ABCD_217BCCF9816B__INCLUDED_

#include "Socket.hpp"

namespace T
{
	class SocketTCP : public Socket
	{

	public:
		SocketTCP();

		/**
		 * Constructor
		 */
		SocketTCP(int nFamily);
		/**
		 * Destructor
		 */
		virtual ~SocketTCP();
		/**
		 * Permits an incoming connection attempt on a socket
		 */
		virtual Socket *Accept(int nFamily, const char *ip, unsigned short port);
		/**
		 * Associates a local address with a socket
		 */
		virtual bool Bind(char *ip, unsigned short port);
		/**
		 * Establishes a connection to a specified socket
		 */
		virtual bool Connect(const char *ip, unsigned short port);
		/**
		 * Places a socket in a state in which it is listening for an incoming connection
		 */
		virtual bool Listen(int backlog = SOMAXCONN);
		/**
		 * Receives data from a connected socket or a bound connectionless socket
		 */
		virtual int Receive(char *buffer, int len, int flags);
		/**
		 * Sends data on a connected socket
		 */
		virtual int Send(const char *buffer, int len, int flags);
	};
}
#endif // !defined(EA_E8306D78_E2A9_445f_ABCD_217BCCF9816B__INCLUDED_)
