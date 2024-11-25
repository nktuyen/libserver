///////////////////////////////////////////////////////////
//  ConnectionTCP.hpp
//  Implementation of the Class ConnectionTCP
//  Created on:      24-Nov-2024 9:32:15 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_9AB36C62_0DE2_418d_BBE2_2716C666FC42__INCLUDED_)
#define EA_9AB36C62_0DE2_418d_BBE2_2716C666FC42__INCLUDED_

#include "Connection.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ServerTCP;
	class Socket;
	class ConnectionTCP : public Connection
	{
		friend class ServerTCP;

	public:
		/**
		 * Destructor
		 */
		virtual ~ConnectionTCP();

	protected:
		/**
		 * Constructor
		 */
		explicit ConnectionTCP(ServerTCP *pServer = nullptr, Socket *pSocket = nullptr, bool aliveChecker = false, int aliveCheckerTimeout = 60);
		/**
		 * Initialize connection
		 */
		virtual bool onInitialize() override;
		/**
		 * Connection run loop
		 */
		virtual int onRun() override;

	private:
		char *mRecvBuffer;
		int mRecvBufSize;
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_9AB36C62_0DE2_418d_BBE2_2716C666FC42__INCLUDED_)
