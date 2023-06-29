#include <server.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

server::server(int port, int socket_domain, int type, int protocol) : port(port), listening_socket(
        socket(socket_domain, type, protocol)) {}

void server::_connect() {
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    socklen_t size = sizeof(serv_addr);

    int bind_status = bind(listening_socket, reinterpret_cast<struct sockaddr *>(&serv_addr), size);
    if (bind_status < 0) {
        std::cerr << "Error binding socket to local address! :| " << std::endl;
        exit(0);
    }

    listen(listening_socket, 1);

    std::cout << "Waiting for clients to connect... :(\n";

    tcp_socket = accept(listening_socket, reinterpret_cast<struct sockaddr *>(&serv_addr), &size);
    if (tcp_socket < 0) {
        std::cerr << "Error accepting request from client!" << std::endl;
        exit(0);
    }
}

void server::_disconnect() {
    close(listening_socket);
    close(tcp_socket);
}

void server::send_message(const std::string& s) {
    strcpy(buffer,s.c_str());
    tcp_client::send_data(tcp_socket,buffer);
}

bool server::receive_message() {
    memset(&buffer, 0, sizeof(buffer));
    char* received_buf = tcp_client::recv_data(tcp_socket);
    if (received_buf == nullptr)
        return false;
    strcpy(buffer,  received_buf);
    return true;
}








