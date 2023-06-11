#include <server_cl.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

void server::open_server() {
    listening_socket = socket(AF_INET,SOCK_STREAM,0);
    if (listening_socket < 0) {
        std::cerr << "Error establishing the server socket" << std::endl;
        exit(0);
    }
    status = true;
}

void server::close_server() {
    close(server_socket);
    std::cout << "Connection closed..." << std::endl;
    status = false;
}


