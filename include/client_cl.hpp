#ifndef SOCKETS_TASK_CLIENT_CL_HPP
#define SOCKETS_TASK_CLIENT_CL_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <csignal>

class client {
public:
    bool status = false;
    int client_socket = -1;
    void open_client();
    void close_client();
};

#endif //SOCKETS_TASK_CLIENT_CL_HPP
