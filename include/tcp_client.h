//
// Created by mrmamongo on 12.07.23.
//

#ifndef SOCKETS_TASK_TCP_CLIENT_H
#define SOCKETS_TASK_TCP_CLIENT_H

#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <utility>
#include <csignal>
#include "i_client.h"

constexpr int DEFAULT_BUFFER_SIZE = 1024;

class tcp_client: public i_client{
private:
    int sock_ = -1;
    const char* address_;
    int port_;
public:
    tcp_client(const char* ip, int port);
    ~tcp_client() override;

    void connect() override;
    void send(bytes message, size_t len) const override;
    [[nodiscard]] bytes recv() const override;
    void close() const override;
};

#endif //SOCKETS_TASK_TCP_CLIENT_H
