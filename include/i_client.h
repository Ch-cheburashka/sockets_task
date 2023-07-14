//
// Created by mrmamongo on 12.07.23.
//

#ifndef SOCKETS_TASK_I_CLIENT_H
#define SOCKETS_TASK_I_CLIENT_H


using byte = const char;
using bytes = byte*;

constexpr int INVALID_SOCKET = -1;

class i_client {
public:
    virtual ~i_client() = default;
    virtual void connect() = 0;
    virtual void send(bytes message, size_t len) const = 0;
    [[nodiscard]] virtual bytes recv() const = 0;
    virtual void close() const = 0;
};


#endif //SOCKETS_TASK_I_CLIENT_H
