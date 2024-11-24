///////////////////////////////////////////////////////////
//  Server.hpp
//  Implementation of the Class Server
//  Created on:      24-Nov-2024 1:25:56 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_)
#define EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_
#include "Thread.hpp"

#define SERVER_IP_LEN 64

namespace T
{
	class Socket;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Server : public Thread
	{
	protected:
		/**
		 * Constructor
		 */
		explicit Server(const char *ip = nullptr, unsigned short port = 0);
		/**
		 * Create server and enter thread loop
		 */
		virtual bool Create(int statckSize = 0) override;

	public:
		/**
		 * Destructor
		 */
		virtual ~Server();
		/**
		 * Return server's ip address
		 */
		inline const char *ip() { return mIP; }
		/**
		 * Return server's port
		 */
		inline unsigned short port() { return mPort; }
		/**
		 * Start server
		 */
		bool Start() { return Thread::Create(); }

	private:
		Socket *mSocket;
		char mIPAddr[SERVER_IP_LEN];
		unsigned short mPort;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_)
