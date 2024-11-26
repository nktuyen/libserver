///////////////////////////////////////////////////////////
//  SocketUDP.h
//  Implementation of the Class SocketUDP
//  Created on:      22-Nov-2024 12:55:46 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_03A8B787_7231_4b42_B827_E574DD6894CD__INCLUDED_)
#define EA_03A8B787_7231_4b42_B827_E574DD6894CD__INCLUDED_

#include "Socket.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SocketUDP : public Socket
	{
	protected:
		/**
		 * Constructor
		 */
		explicit SocketUDP(int nFamily);

	public:
		/**
		 * Destructor
		 */
		virtual ~SocketUDP() override;
		/**
		 * Receives a datagram and stores the source address
		 */
		virtual int ReceiveFrom(char *buffer, int len, const char *ip, unsigned short port, int flags = 0) override;
		/**
		 * Sends data to a specific destination
		 */
		virtual int SendTo(const char *buffer, int len, const char *ip, unsigned short port, int flags = 0) override;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_03A8B787_7231_4b42_B827_E574DD6894CD__INCLUDED_)
