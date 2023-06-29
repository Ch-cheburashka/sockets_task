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

    client client(std::stoi(argv[1])); // constructed client from port (with a default socket initialization)

    client._connect(); // creating addr, connecting to server

    std::cout << "Connected to server :) \n";

    std::this_thread::sleep_for(std::chrono::milliseconds(700));

    std::cout << "Enter seqs bistra :  ";
    client.send_message(client::read_seqs()); // created and sent a string with entered sequences

    client.receive_message(); // received first elements of sequences
    std::cout << client.buffer << "\n";

    const std::string pilus = "+"; // pilus to inform the server that the client is alive

    while (true) {
        if (flag == 1) {
            break;
        }

        client.send_message(pilus); // sent pilus

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        client.receive_message(); // received increased elements
        std::cout << client.buffer << "\n";
    }

    client._disconnect(); // closing the client socket
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::cout << "Spoki noki!\n";
    exit(0);

}

