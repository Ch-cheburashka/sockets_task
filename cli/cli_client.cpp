#include <iostream>
#include <string>
#include <csignal>
#include <thread>
#include <chrono>
#include <client.hpp>
static volatile sig_atomic_t flag = 0;

void signal_handler( int signum ) {
    flag = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: port" << std::endl;
        exit(0);
    }

    signal(SIGINT, signal_handler);

    client client(std::stoi(argv[1]));

    client._connect();

    std::cout << "Connected to server :) \n";

    std::this_thread::sleep_for(std::chrono::milliseconds(700));

    std::cout << "Enter seqs bistra :  ";
    client.send_message(client::read_seqs());

    client.receive_message();
    std::cout << client.buffer << "\n";  // received first elements

    const std::string pilus = "+";

    while (true) {
        if (flag == 1) {
            break;
        }

        client.send_message(pilus);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        client.receive_message();
        std::cout << client.buffer << "\n";
    }
    client._disconnect();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::cout << "Spoki noki!\n";
    exit(0);

}

