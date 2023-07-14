//
// Created by mrmamongo on 12.07.23.
//

#include "client.h"
#include "exceptions.hpp"

client::client() {

}

void client::send(std::string message) {
    if (!client_) {
        throw send_exception("Client is not connected");
    }

    client_->send(message.c_str(), message.size());
}

std::string client::receive() {
    return {client_->recv()};
}

void client::connect(std::string host, int port) {
    if (client_) {
        throw connection_exception("Connection is already established");
    }
    client_ = std::make_unique<tcp_client>(host.c_str(), port);

    client_->connect();
}

void client::close() {
    client_->close();
    client_.reset();
}
