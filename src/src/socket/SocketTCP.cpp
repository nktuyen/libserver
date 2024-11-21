///////////////////////////////////////////////////////////
//  SocketTCP.cpp
//  Implementation of the Class SocketTCP
//  Created on:      22-Nov-2024 12:55:53 AM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "SocketTCP.h"



/**
 * Constructor
 */
SocketTCP::SocketTCP(int nFamily)
  : Socket(nFamily, SOCK_STREAM, IPPROTO_TCP)
{

}


/**
 * Destructor
 */
SocketTCP::~SocketTCP(){

}


/**
 * Permits an incoming connection attempt on a socket
 */
Socket* SocketTCP::Accept(int nFamily, const char* ip, unsigned short port){

	return  NULL;
}


/**
 * Associates a local address with a socket
 */
bool SocketTCP::Bind(char* ip, unsigned short port){

	return false;
}


/**
 * Establishes a connection to a specified socket
 */
bool SocketTCP::Connect(const char* ip, unsigned short port){

	return false;
}


/**
 * Places a socket in a state in which it is listening for an incoming connection
 */
bool SocketTCP::Listen(int backlog){

	return false;
}


/**
 * Receives data from a connected socket or a bound connectionless socket
 */
int SocketTCP::Receive(char* buffer, int len, int flags){

	return 0;
}


/**
 * Sends data on a connected socket
 */
int SocketTCP::Send(const char* buffer, int len, int flags){

	return 0;
}