///////////////////////////////////////////////////////////
//  ServerUDP.hpp
//  Implementation of the Class ServerUDP
//  Created on:      27-Nov-2024 1:37:06 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_7EB17BBD_DF27_4beb_ACB6_471BD1D2E3FF__INCLUDED_)
#define EA_7EB17BBD_DF27_4beb_ACB6_471BD1D2E3FF__INCLUDED_

#include "Server.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class ServerUDP : public Server
	{

	public:
		/**
		 * Destructor
		 */
		virtual ~ServerUDP() override;

	protected:
		/**
		 * Constructor
		 */
		explicit ServerUDP(const char *ip, unsigned short port);
		/**
		 * Callback method that will be called when data is received
		 */
		virtual void onDataReceived(const char *data, int len) override { ; }
		/**
		 * Override onInitialize method
		 */
		bool onInitialize() override;
		/**
		 * Override onRun method
		 */
		int onRun() override;

	private:
		char *mRecvBuffer;
		int mRecvBufSize;
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_7EB17BBD_DF27_4beb_ACB6_471BD1D2E3FF__INCLUDED_)
