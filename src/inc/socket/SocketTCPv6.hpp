///////////////////////////////////////////////////////////
//  SocketTCPv6.h
//  Implementation of the Class SocketTCPv6
//  Created on:      22-Nov-2024 1:00:22 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_BAF2D552_2BCD_40af_AF6C_C7F0635D9FDE__INCLUDED_)
#define EA_BAF2D552_2BCD_40af_AF6C_C7F0635D9FDE__INCLUDED_

#include "SocketTCP.hpp"

namespace T
{
	class SocketTCPv6 : public SocketTCP
	{
		friend class ServerTCPv6;
		friend class ConnectionTCPv6;

	protected:
		/**
		 * Constructor
		 */
		explicit SocketTCPv6();

	public:
		/**
		 * Destructor
		 */
		virtual ~SocketTCPv6();

	protected:
		/**
		 * Associates a local address with a socket
		 */
		virtual bool Bind(const char *ip, unsigned short port) override;

		virtual Socket *onAccepting(SocketHandle hSocket, int nFamily, const char *ip, unsigned short port) override { return new SocketTCPv6(); };
	};
}
#endif // !defined(EA_BAF2D552_2BCD_40af_AF6C_C7F0635D9FDE__INCLUDED_)
