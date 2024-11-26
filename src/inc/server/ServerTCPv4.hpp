///////////////////////////////////////////////////////////
//  ServerTCPv4.hpp
//  Implementation of the Class ServerTCPv4
//  Created on:      24-Nov-2024 9:57:30 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_37BD6D8E_5E44_4825_B0F3_5EAEBD0B72B4__INCLUDED_)
#define EA_37BD6D8E_5E44_4825_B0F3_5EAEBD0B72B4__INCLUDED_

#include "ServerTCP.hpp"
#include "ConnectionTCPv4.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerTCPv4 : public ServerTCP
	{
		friend class ConnectionTCPv4;

	public:
		/**
		 * Constructor
		 */
		explicit ServerTCPv4(const char *ip = nullptr, unsigned short port = 0);
		/**
		 * Destructor
		 */
		virtual ~ServerTCPv4();

	protected:
		/**
		 * New connection callback
		 */
		virtual ConnectionTCP *onNewConnection(SocketTCP *pSocket) override { return new ConnectionTCPv4(this, reinterpret_cast<SocketTCPv4 *>(pSocket)); }
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_37BD6D8E_5E44_4825_B0F3_5EAEBD0B72B4__INCLUDED_)
