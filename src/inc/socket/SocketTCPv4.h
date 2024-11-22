///////////////////////////////////////////////////////////
//  SocketTCPv4.h
//  Implementation of the Class SocketTCPv4
//  Created on:      22-Nov-2024 1:00:19 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_C868A97E_C546_4321_856E_6D6E43A67450__INCLUDED_)
#define EA_C868A97E_C546_4321_856E_6D6E43A67450__INCLUDED_

#include "SocketTCP.h"

namespace T
{
	class SocketTCPv4 : public SocketTCP
	{

	public:
		/**
		 * Constructor
		 */
		SocketTCPv4();
		/**
		 * Destructor
		 */
		~SocketTCPv4();
	};
}
#endif // !defined(EA_C868A97E_C546_4321_856E_6D6E43A67450__INCLUDED_)
