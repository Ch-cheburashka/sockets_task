//
// Created by mrmamongo on 12.07.23.
//

#ifndef SOCKETS_TASK_CLIENT_H
#define SOCKETS_TASK_CLIENT_H

#include <memory>
#include "tcp_client.h"

class client {
private:
    std::unique_ptr<tcp_client> client_;
public:
    client();

    void send(std::string message);
    std::string receive();

    void connect(std::string host, int port);
    void close();
};

#endif //SOCKETS_TASK_CLIENT_H
