#include <iostream>
#include <cstdio>
#include "Logger.hpp"
#include "SocketTCPv6.hpp"
#include "ServerTCPv4.hpp"

int main(int argc, char *argv[])
{
    T::Logger::Init("libserver");

#ifdef _WINDOWS
#pragma comment(lib, "Ws2_32.lib")
    WSADATA wsd = {0};
    WSAStartup(MAKEWORD(2, 2), &wsd);
#endif //_WINDOWS
#if 0
    T::SocketTCPv6 socket;
    bool res = socket.Create();
    printf("Create result:%d\n", res);
    bool b = socket.optNonBlocking();
    printf("Non-Blocking option:%d\n", b);
    b = socket.optReusedAddress();
    printf("Re-used address:%d\n", b);
    int i = socket.optRecvBufferSize();
    printf("Receive buffer size:%d\n", i);
    i = socket.optRecvTimeout();
    printf("Receive timeout:%d\n", i);
    i = socket.optSendBufferSize();
    printf("Send buffer size:%d\n", i);
    i = socket.optSendTimeout();
    printf("Send timeout:%d\n", i);

    socket.setOptNonBlocking(true);
    socket.setOptReusedAddress(true);

    printf("=============================================\n");
    b = socket.optNonBlocking();
    printf("Non-Blocking option:%d\n", b);
    b = socket.optReusedAddress();
    printf("Re-used address:%d\n", b);
    i = socket.optRecvBufferSize();
    printf("Receive buffer size:%d\n", i);
    i = socket.optRecvTimeout();
    printf("Receive timeout:%d\n", i);
    i = socket.optSendBufferSize();
    printf("Send buffer size:%d\n", i);
    i = socket.optSendTimeout();
    printf("Send timeout:%d\n", i);

    res = socket.Close();
#endif
    T::ServerTCPv4 server("127.0.0.1", 5678);
    server.Start();

    return server.Wait();
}