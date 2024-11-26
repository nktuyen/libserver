///////////////////////////////////////////////////////////
//  ServerTCPv6.hpp
//  Implementation of the Class ServerTCPv6
//  Created on:      25-Nov-2024 11:41:25 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_D9063E8B_483A_4720_BF0B_6452DBDDF74E__INCLUDED_)
#define EA_D9063E8B_483A_4720_BF0B_6452DBDDF74E__INCLUDED_

#include "ServerTCP.hpp"
#include "ConnectionTCPv6.hpp"
namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class ServerTCPv6 : public ServerTCP
	{
		friend class ConnectionTCPv6;

	public:
		virtual ~ServerTCPv6();

	protected:
		explicit ServerTCPv6(const char *ip = nullptr, unsigned short port = 0);
		/**
		 * New connection callback
		 */
		virtual ConnectionTCP *onNewConnection(SocketTCP *pSocket) override { return new ConnectionTCPv6(this, reinterpret_cast<SocketTCPv6 *>(pSocket)); }
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_D9063E8B_483A_4720_BF0B_6452DBDDF74E__INCLUDED_)
