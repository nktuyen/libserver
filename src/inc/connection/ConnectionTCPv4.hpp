///////////////////////////////////////////////////////////
//  ConnectionTCPv4.hpp
//  Implementation of the Class ConnectionTCPv4
//  Created on:      24-Nov-2024 9:55:13 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_17ED2541_CA95_4a51_9467_A31A06261172__INCLUDED_)
#define EA_17ED2541_CA95_4a51_9467_A31A06261172__INCLUDED_

#include "ConnectionTCP.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerTCPv4;
	class ConnectionTCPv4 : public ConnectionTCP
	{
		friend class ServerTCPv4;

	public:
		/**
		 * Destructor
		 */
		virtual ~ConnectionTCPv4();

	protected:
		/**
		 * Constructor
		 */
		explicit ConnectionTCPv4(ServerTCPv4 *pServer = nullptr, Socket *pSocket = nullptr);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_17ED2541_CA95_4a51_9467_A31A06261172__INCLUDED_)
