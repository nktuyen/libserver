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
		 * Override onNewConnection callback method
		 */
		Connection *onNewConnection(Socket *pSocket) override { return new ConnectionTCP(this, pSocket); }
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif // !defined(EA_4C649ED1_DF28_43b6_BA44_043FF1BB8EB8__INCLUDED_)
