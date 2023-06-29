#ifndef SOCKETS_TASK_I_CLIENT_HPP
#define SOCKETS_TASK_I_CLIENT_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class i_client {
public:
    virtual void _connect() = 0;
    virtual void _disconnect() = 0;
    virtual void send_message(const std::string&) = 0;
    virtual bool receive_message() = 0;
};

#endif //SOCKETS_TASK_I_CLIENT_HPP
