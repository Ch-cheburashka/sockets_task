
#ifndef SOCKETS_TASK_SERVER_HPP
#define SOCKETS_TASK_SERVER_HPP

#include <vector>

#include <i_client.hpp>
#include <tcp_client.hpp>


struct seq {
    int start;
    int step;

    seq(int start, int step) : start(start), step(step) {}
};

class server : public i_client{
    int port = -1;
    int listening_socket = -1;
    int tcp_socket = -1;
public:
    char buffer[500];
    std::vector<seq> start_step_vec;

    explicit server(int port, int socket_domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    ~server() = default;

    server(const server&) = delete;
    server(server&&) = delete;
    server& operator=(const server&) = delete;
    server& operator=(server&&) = delete;

    void _connect() final ;
    void _disconnect() final ;
    void send_message(const std::string&) final;
    bool receive_message() final;

    void create_start_step_vec(const std::string &);
};

#endif //SOCKETS_TASK_SERVER_HPP
