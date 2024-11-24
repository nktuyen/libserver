///////////////////////////////////////////////////////////
//  SocketUDPv6.h
//  Implementation of the Class SocketUDPv6
//  Created on:      22-Nov-2024 1:00:15 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_3502A567_9995_4935_9C3B_9BD184086634__INCLUDED_)
#define EA_3502A567_9995_4935_9C3B_9BD184086634__INCLUDED_

#include "SocketUDP.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SocketUDPv6 : public SocketUDP
	{
	protected:
		/**
		 * Constructor
		 */
		explicit SocketUDPv6();

	public:
		/**
		 * Destructor
		 */
		virtual ~SocketUDPv6();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_3502A567_9995_4935_9C3B_9BD184086634__INCLUDED_)
