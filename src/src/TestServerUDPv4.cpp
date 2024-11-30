#include <iostream>
#include <cstdio>
#include "ServerUDPv4.hpp"
#include "SocketUDPv4.hpp"
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
    void onDataReceived(const char *data, int len) override
    {
        FI();
        printf("%s\n", data);
        FO();
    }
};

class ClientThread : public T::Thread
{
public:
    ClientThread(const char *ip, unsigned port) : Thread(), mSocket()
    {
        memset(mIPAddr, 0, SERVER_IP_LEN);
        if (ip != nullptr)
        {
            strncpy(mIPAddr, ip, SERVER_IP_LEN);
        }
        mPort = port;
    }

    virtual ~ClientThread() override
    {
    }

private:
    T::SocketUDPv4 mSocket;
    char mIPAddr[SERVER_IP_LEN];
    unsigned short mPort;

protected:
    bool onInitialize() override
    {
        return mSocket.Create();
    }

    int onRun() override
    {
        FI();

        char buff[32];
        memset(buff, 0, 32);
        strncpy(buff, "Hello, World!", 32);

        while (isRunning())
        {
            int n = mSocket.SendTo(buff, sizeof(buff), mIPAddr, mPort);
        }

        FO();
        return 0;
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

    ClientThread client(ip, port);
    if (!client.Create())
        server.Stop();

    return server.Wait();
}