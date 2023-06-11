
#ifndef SOCKETS_TASK_SERVER_CL_HPP
#define SOCKETS_TASK_SERVER_CL_HPP
#include <client_cl.hpp>
#include <memory>
class server {
public:
    server() = default;
    ~server() = default;
    server(const server&) = delete;
    server(server&&) = delete;
    server& operator=(const server&) = delete;
    server& operator=(server&&) = delete;
    bool status = false;
    int server_socket = -1;
    int listening_socket = -1;
    void open_server();
    void close_server();
};

#endif //SOCKETS_TASK_SERVER_CL_HPP
