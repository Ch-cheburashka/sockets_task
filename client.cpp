#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <csignal>
#include <thread>
#include <chrono>
#include <client_cl.hpp>
#include <csignal>

static volatile sig_atomic_t flag = 0;

void signal_handler( int signum ) {
    flag = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ip_address port" << std::endl;
        exit(0);
    }
    signal(SIGINT, signal_handler);
    client client;
    char msg[200];

    char *server_ip = argv[1];
    int port = atoi(argv[2]);

    client.open_client();

    sockaddr_in sendSockAddr;
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_port = htons(port);
    sendSockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int status = connect(client.client_socket, (sockaddr *) &sendSockAddr, sizeof(sendSockAddr));
    if (status < 0) {
        std::cout << "Error connecting to socket!" << std::endl;
        exit(1);
    }

    std::cout << "Connected to the server!" << std::endl;
    std::cout << "Enter seq: ";
    std::string data, line;
    while (true) {
        line.clear();
        std::getline(std::cin, line);
        if (line == "export seq")
            break;
        data += line + "\n";
    }
    // created data with sequences
    const char *buf = "+";

    memset(&msg, 0, sizeof(msg));
    strcpy(msg, data.c_str());

    send(client.client_socket, reinterpret_cast<char *>(&msg), strlen(msg), 0);
    //sent sequences
    memset(&msg, 0, sizeof(msg));
    recv(client.client_socket, reinterpret_cast<char *>(&msg), sizeof(msg), 0);
    std::cout << msg << "\n";
    while (true) {
        if (flag == 1) {
            break;
        }
        send(client.client_socket, reinterpret_cast<char *>(&buf), strlen(msg), 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        memset(&msg, 0, sizeof(msg));
        recv(client.client_socket, reinterpret_cast<char *>(&msg), sizeof(msg), 0);
        std::cout << msg << "\n";
    }
    client.close_client();
}