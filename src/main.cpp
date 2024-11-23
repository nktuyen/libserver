#include <iostream>
#include <cstdio>
#include "SocketTCPv6.hpp"

int main(int argc, char *argv[])
{
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
    return 0;
}