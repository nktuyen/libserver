///////////////////////////////////////////////////////////
//  SocketUDPv4.h
//  Implementation of the Class SocketUDPv4
//  Created on:      22-Nov-2024 1:00:09 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_D5D87918_61C7_4067_9361_03F58A7333C8__INCLUDED_)
#define EA_D5D87918_61C7_4067_9361_03F58A7333C8__INCLUDED_

#include "SocketUDP.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SocketUDPv4 : public SocketUDP
	{
	public:
		/**
		 * Constructor
		 */
		explicit SocketUDPv4();
		/**
		 * Destructor
		 */
		virtual ~SocketUDPv4() override;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_D5D87918_61C7_4067_9361_03F58A7333C8__INCLUDED_)
