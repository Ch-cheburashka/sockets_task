#include<iostream>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <server_cl.hpp>
#include <client_cl.hpp>
#include <csignal>
#include <vector>

static volatile sig_atomic_t flag = 0;

void signal_handler(int signum) {
    flag = 1;
}

struct seq {
    int start;
    int step;

    seq(int start, int step) : start(start), step(step) {}
};

std::vector<std::string> split_strs(const std::string &str) {
    std::vector<std::string> res;
    std::string cur;
    for (auto &i: str) {
        if (i == '\n') {
            res.emplace_back(cur);
            cur.clear();
            continue;
        }
        cur += i;
    }
    if (!cur.empty()) {
        res.emplace_back(cur);
    }
    return res;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: port" << std::endl;
        exit(0);
    }
    char msg[2000]; // Вот это можно перенести в класс сервера. Это типа буфер сообщений приходящих
    int port = std::atoi(argv[1]);
    signal(SIGINT, signal_handler);
    server server;
    server.open_server();

    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
    socklen_t size = sizeof(servAddr);

    int bind_status = bind(server.listening_socket, reinterpret_cast<struct sockaddr *>(&servAddr), size);
    if (bind_status < 0) {
        std::cerr << "Error binding socket to local address!" << std::endl;
        exit(0);
    }

    listen(server.listening_socket, 1);

    server.server_socket = accept(server.listening_socket, reinterpret_cast<struct sockaddr *>(&servAddr), &size);
    if (server.server_socket < 0) {
        std::cerr << "Error accepting request from client!" << std::endl;
        exit(1);
    }

    std::cout << "Connected with client!" << std::endl;
    std::cout << "Awaiting response from a client..." << std::endl;

    memset(&msg, 0, sizeof(msg));
    recv(server.server_socket, reinterpret_cast<char *>(&msg), sizeof(msg), 0);
    // got sequences

    std::vector<seq> start_step_vec;

    std::string s = msg;
    std::vector<std::string> strings = split_strs(s);

    for (auto &i: strings) {
        start_step_vec.emplace_back(std::stoi(i.substr(i.find_first_of(' ') + 1, i.find_last_of(' '))),
                                    std::stoi(i.substr(i.find_last_of(' ') + 1)));
    }

    memset(&msg, 0, sizeof(msg));

    for (auto &i: start_step_vec) {
        strcat(msg, (std::to_string(i.start) + " ").c_str());
    }
    send(server.server_socket, reinterpret_cast<char *>(&msg), strlen(msg), 0);
    //sent the first element
    const char *buf = "+";
    while (true) {
        if (recv(server.server_socket, reinterpret_cast<char *>(&buf), strlen(msg), 0) <= 0) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::string tmp;
        for (auto &i: start_step_vec) {
            tmp += std::to_string(i.start + i.step) + " ";
            i.start += i.step;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        memset(&msg, 0, sizeof(msg));
        strcat(msg, tmp.c_str());
        send(server.server_socket, reinterpret_cast<char *>(&msg), strlen(msg), 0);
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << "Waiting for other clients to connect...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
    server.close_server();

    return 0;
}
