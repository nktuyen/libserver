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
		friend class ServerTCP;
		friend class ConnectionTCP;

	protected:
		/**
		 * Constructor
		 */
		explicit SocketTCP(int nFamily);

	public:
		/**
		 * Destructor
		 */
		virtual ~SocketTCP();
		/**
		 * Associates a local address with a socket
		 */
		virtual bool Bind(const char *ip, unsigned short port) override;
		/**
		 * Places a socket in a state in which it is listening for an incoming connection
		 */
		virtual bool Listen(int backlog = SOMAXCONN) override;
		/**
		 * Establishes a connection to a specified socket
		 */
		virtual bool Connect(const char *ip, unsigned short port) override;
		/**
		 * Receives data from a connected socket or a bound connectionless socket
		 */
		virtual int Receive(char *buffer, int len, int flags = 0) override;
		/**
		 * Sends data on a connected socket
		 */
		virtual int Send(const char *buffer, int len, int flags = 0) override;

	protected:
		virtual Socket *onAccepting(SocketHandle hSocket, int nFamily, const char *ip, unsigned short port) override { return new SocketTCP(nFamily); };
	};
}
#endif // !defined(EA_E8306D78_E2A9_445f_ABCD_217BCCF9816B__INCLUDED_)
