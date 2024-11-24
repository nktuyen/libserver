cmake_minimum_required(VERSION 3.0)
project(libserver VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "C++ TCP/IP server libary")

include_directories(libserver PUBLIC
    inc
    inc/socket
    inc/logger
    inc/thread
    inc/server
    inc/connection
)

add_library(libserver
    src/logger/Logger.cpp
    src/thread/Thread.cpp
    src/socket/Socket.cpp
    src/socket/SocketUDP.cpp
    src/socket/SocketTCP.cpp
    src/socket/SocketUDPv4.cpp
    src/socket/SocketUDPv6.cpp
    src/socket/SocketTCPv4.cpp
    src/socket/SocketTCPv6.cpp
    src/server/Server.cpp
    src/connection/Connection.cpp
    src/connection/ConnectionTCP.cpp
    src/connection/ConnectionTCPv4.cpp
    src/connection/ConnectionTCPv6.cpp
    src/server/ServerTCP.cpp
    src/server/ServerTCPv4.cpp
    src/server/ServerTCPv6.cpp
)

add_executable(test
    main.cpp
)

target_link_libraries(test libserver pthread)
target_compile_definitions(test PUBLIC __DEBUG__=1)