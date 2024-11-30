///////////////////////////////////////////////////////////
//  ConnectionTCP.hpp
//  Implementation of the Class ConnectionTCP
//  Created on:      24-Nov-2024 9:11:24 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_F6FA6ACF_1BA5_4e9a_BAC9_42034F67D0E5__INCLUDED_)
#define EA_F6FA6ACF_1BA5_4e9a_BAC9_42034F67D0E5__INCLUDED_
#include "Thread.hpp"
#include <mutex>

#define ConnectionHandle ThreadHandle
#define InvalidConnection InvalidThreadHandle

namespace T
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerTCP;
	class SocketTCP;
	class ConnectionTCP;

	class AliveChecker : public Thread
	{
		friend class ConnectionTCP;

	private:
		AliveChecker(ConnectionTCP *pConn, int timeout_seconds = 60);
		bool onInitialize() override;
		int onRun() override;
		int getElapsed();
		void setElapsed(int val);

	public:
		virtual ~AliveChecker() override;
		void Restart();

	private:
		ConnectionTCP *mConn;
		int mTimeout;
		int mElapsed;
		std::mutex mMutex;
	};

	class ConnectionTCP : public Thread
	{
		friend class AliveChecker;
		friend class ServerTCP;

	public:
		/**
		 * Destructor
		 */
		virtual ~ConnectionTCP() override;
		/**
		 * return associated server
		 */
		inline ServerTCP *server()
		{
			return mServer;
		}
		/**
		 * Return associated socket
		 */
		inline SocketTCP *socket() { return mSocket; }
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
		explicit ConnectionTCP(ServerTCP *pServer = nullptr, SocketTCP *pSocket = nullptr, bool aliveChecker = false, int aliveCheckerTimeout = 60);
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
		virtual void onDataReceived(const char *data, int len) { ; }
		/**
		 * Initialize connection
		 */
		virtual bool onInitialize() override;
		/**
		 * Connection run loop
		 */
		virtual int onRun() override;

	protected:
		AliveChecker *mAliveChecker;

	private:
		ServerTCP *mServer;
		SocketTCP *mSocket;
		bool mAlive;
		std::mutex mALiveMutex;
		char *mRecvBuffer;
		int mRecvBufSize;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_F6FA6ACF_1BA5_4e9a_BAC9_42034F67D0E5__INCLUDED_)
