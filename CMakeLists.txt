cmake_minimum_required(VERSION 3.22)
project(sockets_task)

set(CMAKE_CXX_STANDARD 17)

add_library(
        server
        sources/server.cpp
)

add_library(
        client
        sources/client.cpp
)

add_library(
        tcp_client
        sources/tcp_client.cpp
)

target_include_directories(server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

target_include_directories(tcp_client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )


target_include_directories(client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

add_library(i_client INTERFACE)

target_include_directories(i_client INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

add_executable(cli_server cli/cli_server.cpp)
add_executable(cli_client include/utils.hpp include/i_client.h sources/tcp_client.cpp include/tcp_client.h sources/client.cpp include/client.h cli/cli_client.cpp)

target_link_libraries(cli_server server)
target_link_libraries(cli_client client)

target_link_libraries(cli_client tcp_client)
target_link_libraries(cli_server tcp_client)

target_link_libraries(client i_client)
target_link_libraries(server i_client)
