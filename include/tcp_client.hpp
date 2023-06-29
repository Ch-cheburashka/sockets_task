#ifndef SOCKETS_TASK_TCP_CLIENT_HPP
#define SOCKETS_TASK_TCP_CLIENT_HPP
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

class tcp_client {
public:
    static void send_data(int socket, char*);
    static char* recv_data(int socket);
};

#endif //SOCKETS_TASK_TCP_CLIENT_HPP
