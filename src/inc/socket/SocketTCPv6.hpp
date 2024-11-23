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

	public:
		/**
		 * Constructor
		 */
		SocketTCPv6();
		/**
		 * Destructor
		 */
		~SocketTCPv6();

	protected:
		virtual Socket *onAccepting(SocketHandle hSocket, int nFamily, const char *ip, unsigned short port) override { return new SocketTCPv6(); };
	};
}
#endif // !defined(EA_BAF2D552_2BCD_40af_AF6C_C7F0635D9FDE__INCLUDED_)
