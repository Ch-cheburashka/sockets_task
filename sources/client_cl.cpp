#include <client_cl.hpp>

void client::open_client() {
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    status = true;
}

void client::close_client() {
    close(client_socket);
    std::cout << "Connection closed..." << std::endl;
}
