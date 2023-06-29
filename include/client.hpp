#ifndef SOCKETS_TASK_CLIENT_HPP
#define SOCKETS_TASK_CLIENT_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <i_client.hpp>
#include <tcp_client.hpp>

class client : public i_client {
private:
    int port = -1;
    int tcp_socket = -1;
public:
    char buffer[500];

    explicit client(int port, int socket_domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);

    void _connect() final ;
    void _disconnect() final ;
    void send_message(const std::string&) final;
    bool receive_message() final;

    static std::string read_seqs();
};

#endif //SOCKETS_TASK_CLIENT_HPP
