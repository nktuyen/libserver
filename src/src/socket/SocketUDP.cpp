///////////////////////////////////////////////////////////
//  SocketUDP.cpp
//  Implementation of the Class SocketUDP
//  Created on:      22-Nov-2024 12:55:46 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketUDP.h"



/**
 * Constructor
 */
SocketUDP::SocketUDP(int nFamily)
  :Socket(nFamily, SOCK_DGRAM, IPPROTO_UDP)
{

}


/**
 * Destructor
 */
SocketUDP::~SocketUDP(){

}


/**
 * Receives a datagram and stores the source address
 */
int SocketUDP::ReceiveFrom(char* buffer, int len, const char* ip, unsigned short port, int flags){

	return 0;
}


/**
 * Sends data to a specific destination
 */
int SocketUDP::SendTo(const char* buffer, int len, const char* ip, unsigned short port, int flags){

	return 0;
}