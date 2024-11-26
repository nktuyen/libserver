///////////////////////////////////////////////////////////
//  ConnectionTCPv6.hpp
//  Implementation of the Class ConnectionTCPv6
//  Created on:      25-Nov-2024 11:31:38 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_FBCD7576_1B7D_4a0e_BDF8_927642A3D600__INCLUDED_)
#define EA_FBCD7576_1B7D_4a0e_BDF8_927642A3D600__INCLUDED_

#include "ConnectionTCP.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerTCPv6;
	class SocketTCPv6;
	class ConnectionTCPv6 : public ConnectionTCP
	{
		friend class ServerTCPv6;

	public:
		/**
		 * Destructor
		 */
		virtual ~ConnectionTCPv6();

	protected:
		/**
		 * Constructor
		 */
		explicit ConnectionTCPv6(ServerTCPv6 *pServer = nullptr, SocketTCPv6 *pSocket = nullptr, bool aliveChecker = false, int aliveCheckerTimeout = 60);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_FBCD7576_1B7D_4a0e_BDF8_927642A3D600__INCLUDED_)
