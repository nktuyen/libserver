#include <iostream>
#include <cstdio>
#include "Logger.hpp"
#include "ConnectionTCPv6.hpp"
#include "ServerTCPv6.hpp"
#include "SocketTCPv6.hpp"

class MyServer;
class MyConnection : public T::ConnectionTCPv6
{
public:
    MyConnection(MyServer *pServer, T::Socket *pSocket);
    virtual ~MyConnection() override {}

protected:
    void onData(const char *data, int len)
    {
        if (data != nullptr)
        {
            char *buf = new char[len + 255];
            memset(buf, 0, len + 255);
            snprintf(buf, len + 255, "You said %s", data);
            T::SocketTCPv6 *pSocket = reinterpret_cast<T::SocketTCPv6 *>(socket());
            if (pSocket != nullptr)
                pSocket->Send(buf, len + 255);

            delete[] buf;
        }
    }
};

class MyServer : public T::ServerTCPv6
{
public:
    MyServer(const char *ip, unsigned short port) : T::ServerTCPv6(ip, port) {}
    virtual ~MyServer() override {}

protected:
    T::Connection *onNewConnection(T::Socket *pSocket) override { return new MyConnection(this, pSocket); }
};

MyConnection::MyConnection(MyServer *pServer, T::Socket *pSocket)
    : T::ConnectionTCPv6(pServer, pSocket, true, 5)
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