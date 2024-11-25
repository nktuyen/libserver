///////////////////////////////////////////////////////////
//  Connection.hpp
//  Implementation of the Class Connection
//  Created on:      24-Nov-2024 9:11:24 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_F6FA6ACF_1BA5_4e9a_BAC9_42034F67D0E5__INCLUDED_)
#define EA_F6FA6ACF_1BA5_4e9a_BAC9_42034F67D0E5__INCLUDED_
#include "Thread.hpp"
#include <mutex>

#define ConnectionHandle ThreadHandle
#define InvalidConnection InvalidThread

namespace T
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Server;
	class Socket;
	class Connection;

	class AliveChecker : public Thread
	{
		friend class Connection;

	private:
		AliveChecker(Connection *pConn, int timeout_seconds = 60);
		bool onInitialize() override;
		int onRun() override;
		int getElapsed();
		void setElapsed(int val);

	public:
		virtual ~AliveChecker();
		void Restart();

	private:
		Connection *mConn;
		int mTimeout;
		int mElapsed;
		std::mutex mMutex;
	};

	class Connection : public Thread
	{
		friend class AliveChecker;

	public:
		/**
		 * Destructor
		 */
		virtual ~Connection();
		/**
		 * return associated server
		 */
		inline Server *server() { return mServer; }
		/**
		 * Return associated socket
		 */
		inline Socket *socket() { return mSocket; }
		/**
		 * Establish connection
		 */
		inline bool Establish() { return Thread::Create(); }
		/**
		 * Return alive status
		 */
		bool isAlive();

	protected:
		/**
		 * Constructor
		 */
		explicit Connection(Server *pServer = nullptr, Socket *pSocket = nullptr, bool aliveChecker = false, int aliveCheckerTimeout = 60);
		/**
		 * Create connection
		 */
		virtual bool Create(int statckSize = 0) override { return Thread::Create(statckSize); }
		/**
		 * Set alive status
		 */
		void setAlive(bool bAlive);
		/**
		 * Override onFailure() callback
		 */
		virtual int onFailure() override;
		/**
		 * Override onSuccess() callback
		 */
		virtual void onSuccess() override;
		/**
		 * Data callback
		 */
		virtual void onData(const char *data, int len) { ; }

	protected:
		AliveChecker *mAliveChecker;

	private:
		Server *mServer;
		Socket *mSocket;
		bool mAlive;
		std::mutex mALiveMutex;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_F6FA6ACF_1BA5_4e9a_BAC9_42034F67D0E5__INCLUDED_)
