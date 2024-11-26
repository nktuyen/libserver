#include <iostream>
#include <cstdio>
#include "Logger.hpp"
#include "ConnectionTCPv4.hpp"
#include "ServerTCPv4.hpp"
#include "SocketTCPv4.hpp"

class MyServer;
class MyConnection : public T::ConnectionTCPv4
{
public:
    MyConnection(MyServer *pServer, T::SocketTCPv4 *pSocket);
    virtual ~MyConnection() override {}

protected:
    void onData(const char *data, int len)
    {
        if (data != nullptr)
        {
            char *buf = new char[len + 255];
            memset(buf, 0, len + 255);
            snprintf(buf, len + 255, "You said %s", data);
            T::SocketTCPv4 *pSocket = reinterpret_cast<T::SocketTCPv4 *>(socket());
            if (pSocket != nullptr)
                pSocket->Send(buf, len + 255);

            delete[] buf;
        }
    }
};

class MyServer : public T::ServerTCPv4
{
public:
    MyServer(const char *ip, unsigned short port) : T::ServerTCPv4(ip, port) {}
    virtual ~MyServer() override {}

protected:
    T::ConnectionTCP *onNewConnection(T::SocketTCP *pSocket) override { return new MyConnection(this, reinterpret_cast<T::SocketTCPv4 *>(pSocket)); }
};

MyConnection::MyConnection(MyServer *pServer, T::SocketTCPv4 *pSocket)
    : T::ConnectionTCPv4(pServer, pSocket, true, 5)
{
    FI();

    FO();
}

int main(int argc, char *argv[])
{
    T::Logger::Init("libserver");
#ifdef _WINDOWS
#pragma comment(lib, "Ws2_32.lib")
    WSADATA wsd = {0};
    WSAStartup(MAKEWORD(2, 2), &wsd);
#endif //_WINDOWS
    char ip[SERVER_IP_LEN] = {0};
    unsigned port = 0;
    if (argc > 1)
    {
        strncpy(ip, argv[1], SERVER_IP_LEN);
    }
    if (argc > 1)
    {
        port = std::atoi(argv[2]);
    }

    MyServer server(ip, port);
    if (!server.Start())
        return 1;
    return server.Wait();
}