cmake_minimum_required(VERSION 3.22)
project(sockets_task)

set(CMAKE_CXX_STANDARD 17)

add_library(
        server_cl
        sources/server_cl.cpp
)

add_library(
        client_cl
        sources/client_cl.cpp
)

target_include_directories(server_cl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )



target_include_directories(client_cl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

add_executable(main_server server.cpp)
add_executable(main_client client.cpp)

target_link_libraries(main_server server_cl)
target_link_libraries(main_client server_cl)
target_link_libraries(main_server client_cl)
target_link_libraries(main_client client_cl)
