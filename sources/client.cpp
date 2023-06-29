#include <client.hpp>

client::client(int port, int socket_domain, int type, int protocol) : port(port), tcp_socket(socket(socket_domain,type,protocol)){}


void client::_connect() {
    sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int status = connect(tcp_socket, (sockaddr *) &client_addr, sizeof(client_addr));
    if (status < 0) {
        std::cout << "Error connecting to socket!" << std::endl;
        exit(1);
    }
}

void client::_disconnect() {
    close(tcp_socket);
}



void client::send_message(const std::string& s) {
    memset(&buffer, 0, sizeof(buffer));
    strcpy(buffer,s.c_str());
    tcp_client::send_data(tcp_socket,buffer);
}

bool client::receive_message() {
    memset(&buffer, 0, sizeof(buffer));
    char* received_buf = tcp_client::recv_data(tcp_socket);
    if (received_buf == nullptr)
        return false;
    strcpy(buffer,  received_buf);
    return true;
}

std::string client::read_seqs() {
    std::string data, line;
    while (true) {
        line.clear();
        std::getline(std::cin, line);
        if (line == "export seq")
            break;
        data += line + "\n";
    }
    return data;
}

