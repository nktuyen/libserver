///////////////////////////////////////////////////////////
//  ServerTCP.hpp
//  Implementation of the Class ServerTCP
//  Created on:      24-Nov-2024 8:33:41 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_4C649ED1_DF28_43b6_BA44_043FF1BB8EB8__INCLUDED_)
#define EA_4C649ED1_DF28_43b6_BA44_043FF1BB8EB8__INCLUDED_

#include "Server.hpp"
#include "ConnectionTCP.hpp"
#include <map>

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerTCP : public Server
	{
		friend class ConnectionTCP;

	public:
		/**
		 * Destructor
		 */
		virtual ~ServerTCP();

	protected:
		/**
		 * Constructor
		 */
		explicit ServerTCP(const char *ip = nullptr, unsigned short port = 0);
		/**
		 * Initialize server callback
		 */
		virtual bool onInitialize() override;
		/**
		 * Server run loop
		 */
		virtual int onRun() override;
		/**
		 * The callback method that will be called when a connection is closed
		 */
		virtual void onConnectionClose(ConnectionTCP *conn);
		/**
		 * Override onNewConnection callback method
		 */
		virtual ConnectionTCP *onNewConnection(SocketTCP *pSocket) { return new ConnectionTCP(this, pSocket); }

	private:
		std::map<ConnectionHandle, ConnectionTCP *> mConnMap;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif // !defined(EA_4C649ED1_DF28_43b6_BA44_043FF1BB8EB8__INCLUDED_)
