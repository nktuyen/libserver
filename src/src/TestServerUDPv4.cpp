#include <iostream>
#include <cstdio>
#include "ServerUDPv4.hpp"
#include "Logger.hpp"

class MyServer : public T::ServerUDPv4
{
public:
    MyServer(const char *ip, unsigned short port) : T::ServerUDPv4(ip, port)
    {
        FO();
        FO();
    }
    virtual ~MyServer() override {}

protected:
    void onDataReceived(const char *data, int len)
    {
        FI();
        printf("%s\n", data);
        FO();
    }
};

int main(int argc, char *argv[])
{
    T::Logger::Init("TestServerUDPv4");
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