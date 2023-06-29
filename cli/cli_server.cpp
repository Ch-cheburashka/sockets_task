#include<iostream>
#include <thread>
#include <chrono>
#include <string>
#include "server.hpp"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: port" << std::endl;
        exit(0);
    }

    server server(std::stoi(argv[1])); // constructed the server from a port (with a default socket initialization)

    std::cout << "Sdravia zhelayu!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    server._connect(); // creating addr, binding to addr, listening and accepting client

    std::cout << "\nClient connected :)\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    server.receive_message(); // receiving sequences

    server.create_start_step_vec(server.buffer); // creating a vector with start positions and steps

    std::string result;
    for (auto &i: server.start_step_vec) {
        result += std::to_string(i.start) + " "; // creating first elements of sequences
    }

    server.send_message(result);// sent first elements

    std::cout << "...processing...\n";

    while (true) {
        if (!server.receive_message()) { // checking if client isn't dead
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        result.clear();
        for (auto &i: server.start_step_vec) {
            result += std::to_string(i.start + i.step) + " ";  // increasing each element by its step
            i.start += i.step;
        }
        server.send_message(result); // sending increased elements
    }

    std::cout << "\nWaiting for other clients to connect...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(8000));

    server._disconnect(); // closing all the server sockets

    std::cout << "\nYa ustal zhdat.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Gute Nacht!\n";

    exit(0);
}
