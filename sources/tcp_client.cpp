
#include "tcp_client.hpp"


void tcp_client::send_data(int socket, char * buffer) {
    send(socket, buffer, strlen(buffer), 0);
}

char* tcp_client::recv_data(int socket) {
    static char* buffer[500];
    memset(&buffer, 0, sizeof(buffer));
    if (recv(socket,reinterpret_cast<char *>(&buffer), sizeof(buffer), 0) <= 0) {
        return nullptr;
    }
    return reinterpret_cast<char *>(&buffer);
}

