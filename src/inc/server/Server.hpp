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
		/**
		 * Override onInitialize method
		 */
		bool onInitialize() override;
		/**
		 * Override onFailure method
		 */
		virtual int onFailure() override;
		/**
		 * Override onSuccess method
		 */
		virtual void onSuccess() override;
		/**
		 * Callback method that will be called when data is received
		 */
		virtual void onDataReceived(const char *data, int len) { ; }

	public:
		/**
		 * Destructor
		 */
		virtual ~Server() override;
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
		Socket *mSocket;
		char mIPAddr[SERVER_IP_LEN];
		unsigned short mPort;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_E83377D8_4BD7_4cf3_91A7_1D9D355E5DDE__INCLUDED_)