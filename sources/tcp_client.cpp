//
// Created by mrmamongo on 12.07.23.
//

#include <tcp_client.h>
#include "exceptions.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

tcp_client::tcp_client(const char* address, int port) : address_(address), port_(port) {
}

void tcp_client::connect() {
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    if (inet_pton(AF_INET, address_, &(server_addr.sin_addr)) <= 0) {
        throw connection_exception("Invalid address or address not supported\n");

    }
    if (::connect(sock_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw connection_exception("Connection failed\n");
    }
}

void tcp_client::send(bytes message, size_t len) const {
    if (::send(sock_, message, len, 0) < 0) {
        throw send_exception(address_);
    }
}

bytes tcp_client::recv() const {
    auto buffer = new char [DEFAULT_BUFFER_SIZE];
    if (::recv(sock_, buffer, DEFAULT_BUFFER_SIZE, 0) < 0) {
        std::cerr << "Failed to receive response" << std::endl;
        return {};
    }
    return buffer;
}

void tcp_client::close() const {
    ::close(sock_);
}

tcp_client::~tcp_client() {
    if (sock_ != INVALID_SOCKET) {
        this->close();
    }
}
