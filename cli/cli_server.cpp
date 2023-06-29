#include<iostream>
#include <thread>
#include <chrono>
#include <string>
#include "server.hpp"
#include <vector>


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

std::vector<seq> build_seqs(const std::string &s) {
    std::vector<seq> start_step_vec;
    std::vector<std::string> strings = split_strs(s);
    for (auto &i: strings) {
        start_step_vec.emplace_back(
                std::stoi(i.substr(i.find_first_of(' ') + 1, i.find(' ', i.find_first_of(' ') + 1))),
                std::stoi(i.substr(i.find(' ', i.find_first_of(' ') + 1) + 1, i.find_last_of(' '))));
    }
    return start_step_vec;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: port" << std::endl;
        exit(0);
    }

    server server(std::stoi(argv[1]));
    std::cout << "Sdravia zhelayu!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    server._connect();
    std::cout << "\nClient connected :)\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    server.receive_message();
    std::vector<seq> start_step_vec = build_seqs(server.buffer);
    std::string result;
    for (auto &i: start_step_vec) {
        result += std::to_string(i.start) + " ";
    }
    server.send_message(result); // sent first elements
    std::cout << "...processing...\n";
    while (true) {
        if (!server.receive_message()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        result.clear();
        for (auto &i: start_step_vec) {
            result += std::to_string(i.start + i.step) + " ";
            i.start += i.step;
        }
        server.send_message(result);
        memset(&server.buffer, 0, sizeof(server.buffer));
    }

    std::cout << "\nWaiting for other clients to connect...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(8000));
    server._disconnect();

    std::cout << "\nYa ustal zhdat.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Gute Nacht!\n";
    exit(0);
}
