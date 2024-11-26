///////////////////////////////////////////////////////////
//  ServerUDPv4.hpp
//  Implementation of the Class ServerUDPv4
//  Created on:      27-Nov-2024 1:37:11 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_AE3634BB_B252_4f68_841F_70A5B978A740__INCLUDED_)
#define EA_AE3634BB_B252_4f68_841F_70A5B978A740__INCLUDED_

#include "ServerUDP.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerUDPv4 : public ServerUDP
	{
	public:
		/**
		 * Destructor
		 */
		virtual ~ServerUDPv4() override;

	protected:
		/**
		 * Constructor
		 */
		explicit ServerUDPv4(const char *ip, unsigned short port);
		/**
		 * Callback method that will be called when data is received
		 */
		virtual void onDataReceived(const char *data, int len) override { ; }
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_AE3634BB_B252_4f68_841F_70A5B978A740__INCLUDED_)
