cmake_minimum_required(VERSION 3.0)
project(server VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "C++ TCP/IP server libary")

include_directories(server PUBLIC
    inc
    inc/socket
    inc/logger
    inc/thread
    inc/server
    inc/connection
)

add_library(server
    inc/logger/Logger.hpp
    inc/thread/Thread.hpp
    inc/socket/Socket.hpp
    inc/socket/SocketUDP.hpp
    inc/socket/SocketTCP.hpp
    inc/socket/SocketUDPv4.hpp
    inc/socket/SocketTCPv4.hpp
    inc/server/Server.hpp
    inc/connection/ConnectionTCP.hpp
    inc/connection/ConnectionTCPv4.hpp
    inc/server/ServerTCP.hpp
    inc/server/ServerTCPv4.hpp
    inc/server/ServerUDP.hpp
    inc/server/ServerUDPv4.hpp

    src/logger/Logger.cpp
    src/thread/Thread.cpp
    src/socket/Socket.cpp
    src/socket/SocketUDP.cpp
    src/socket/SocketTCP.cpp
    src/socket/SocketUDPv4.cpp
    src/socket/SocketTCPv4.cpp
    src/server/Server.cpp
    src/connection/ConnectionTCP.cpp
    src/connection/ConnectionTCPv4.cpp
    src/server/ServerTCP.cpp
    src/server/ServerTCPv4.cpp
    src/server/ServerUDP.cpp
    src/server/ServerUDPv4.cpp
)

add_executable(TestServerTCPv4
    src/TestServerTCPv4.cpp
)

target_link_libraries(TestServerTCPv4 server pthread)
target_compile_definitions(TestServerTCPv4 PUBLIC _DEBUG=1)


add_executable(TestServerUDPv4
    src/TestServerUDPv4.cpp
)

target_link_libraries(TestServerUDPv4 server pthread)
target_compile_definitions(TestServerUDPv4 PUBLIC _DEBUG=1)