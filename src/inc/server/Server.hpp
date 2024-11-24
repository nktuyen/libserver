///////////////////////////////////////////////////////////
//  Server.hpp
//  Implementation of the Class Server
//  Created on:      24-Nov-2024 1:25:56 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_)
#define EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_
#include "Thread.hpp"
#include "Socket.hpp"
#include "Connection.hpp"
#include <map>

#define SERVER_IP_LEN 64

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Server : public Thread
	{
		friend class Connection;

	protected:
		/**
		 * Constructor
		 */
		explicit Server(const char *ip = nullptr, unsigned short port = 0);
		/**
		 * Create server and enter thread loop
		 */
		virtual bool Create(int statckSize = 0) override { return Thread::Create(statckSize); }

	public:
		/**
		 * Destructor
		 */
		virtual ~Server();
		/**
		 * Return server's ip address
		 */
		inline const char *ip() { return mIPAddr; }
		/**
		 * Return server's port
		 */
		inline unsigned short port() { return mPort; }
		/**
		 * Return socket
		 */
		inline Socket *socket() { return mSocket; }
		/**
		 * Start server
		 */
		inline bool Start() { return Thread::Create(); }

	protected:
		/**
		 * The callback method that will be called when a connection is closed
		 */
		virtual void onConnectionClose(Connection *conn);
		/**
		 * The callback method that will be called after a socket is accepted
		 */
		virtual Connection *onNewConnection(Socket *pSocket) { return nullptr; }

	protected:
		Socket *mSocket;
		char mIPAddr[SERVER_IP_LEN];
		unsigned short mPort;
		std::map<ConnectionHandle, Connection *> mConnMap;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_)