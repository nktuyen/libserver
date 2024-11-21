///////////////////////////////////////////////////////////
//  Socket.cpp
//  Implementation of the Class Socket
//  Created on:      21-Nov-2024 11:21:43 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "Socket.hpp"


namespace T {
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Constructor
 */
Socket::Socket(int nFamily, int nType, int nProtocol)
:mHandle(INVALID_SOCKET)
,mFamily(nFamily)
,mType(nType)
,mProtocol(nProtocol)
{

}


/**
 * Destructor
 */
Socket::~Socket(){

}



/**
 * Close created socket
 */
bool Socket::Close(){

	return false;
}


/**
 * Create actual socket
 */
bool Socket::Create(){

	return false;
}


/**
 * Associates a local address with a socket
 */
bool Socket::Bind(char* ip, unsigned short port){

	return false;
}


/**
 * Places a socket in a state in which it is listening for an incoming connection
 */
bool Socket::Listen(int backlog){

	return false;
}


/**
 * Establishes a connection to a specified socket
 */
bool Socket::Connect(char* ip, unsigned short port){

	return false;
}


/**
 * Permits an incoming connection attempt on a socket
 */
Socket* Socket::Accept(int nFamily, char* ip, unsigned short port){

	return  NULL;
}


/**
 * Determines whether the socket is readable or not, waiting if necessary, to
 * perform synchronous I/O
 */
bool Socket::isReadable(unsigned int timeout){

	return false;
}


/**
 * Determines whether the socket is writable or not, waiting if necessary, to
 * perform synchronous I/O
 */
bool Socket::isWritable(unsigned int timeout){

	return false;
}


/**
 * Permits an incoming connection attempt on a socket
 */
Socket* Socket::Accept(int nFamily, const char* ip, unsigned short port){

	return  NULL;
}


/**
 * Associates a local address with a socket
 */
bool Socket::Bind(const char* ip, unsigned short port){

	return false;
}


/**
 * Establishes a connection to a specified socket
 */
bool Socket::Connect(const char* ip, unsigned short port){

	return false;
}


/**
 * Receives data from a connected socket or a bound connectionless socket
 */
int Socket::Receive(char* buffer, int len, int flags){

	return 0;
}


/**
 * Sends data on a connected socket
 */
int Socket::Send(const char* buffer, int len, int flags){

	return 0;
}


/**
 * Permits an incoming connection attempt on a socket
 */
Socket* Socket::Accept(int nFamily, const char* ip, unsigned short port){

	return  NULL;
}


/**
 * Associates a local address with a socket
 */
bool Socket::Bind(const char* ip, unsigned short port){

	return false;
}


/**
 * Establishes a connection to a specified socket
 */
bool Socket::Connect(const char* ip, unsigned short port){

	return false;
}


/**
 * Receives a datagram and stores the source address
 */
int Socket::ReceiveFrom(char* buffer, int len, const char* ip, unsigned short port, int flags){

	return 0;
}


/**
 * Sends data on a connected socket
 */
int Socket::Send(const char* buffer, int len, int flags){

	return 0;
}


/**
 * Sends data to a specific destination
 */
int Socket::SendTo(const char* buffer, int len, const char* ip, unsigned short port, int flags){

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace T