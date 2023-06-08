#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>

std::vector<int> seq_generator(int start, int step) {
    std::vector<int> seqs;
    seqs.emplace_back(start);
    for (int i = 0; i < 4; ++i) {
        seqs.emplace_back(start + step);
        start += step;
    }
    return seqs;
}

std::string build_msg (const std::vector<std::vector<int>>& seqs) {
    std::string msg;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < seqs.size(); ++j) {
            msg += std::to_string(seqs[j][i]) + " ";
        }
        msg+= "\n";
    }
    return msg;
}

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

struct seq {
    int start;
    int step;

    seq(int start, int step) : start(start), step(step) {}
};

std::vector<seq> split_seqs(const std::vector<std::string> &strs) {
    std::vector<seq> data;

    for (auto &s: strs) {
        data.emplace_back(std::stoi(s.substr(s.find_first_of(' ') + 1, s.find_last_of(' '))),
                          std::stoi(s.substr(s.find_last_of(' ') + 1)));
    }

    return data;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: port" << std::endl;
        exit(0);
    }
    int port = atoi(argv[1]);

    char msg[2000];

    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
    socklen_t size = sizeof(servAddr);

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0) {
        std::cerr << "Error establishing the server socket" << std::endl;
        exit(0);
    }

    int bindStatus = bind(serverSd, reinterpret_cast<struct sockaddr *>(&servAddr), sizeof(servAddr));
    if (bindStatus < 0) {
        std::cerr << "Error binding socket to local address" << std::endl;
        exit(0);
    }
    listen(serverSd, 1);

    int newSd = accept(serverSd, reinterpret_cast<struct sockaddr *>(&servAddr), &size);
    if (newSd < 0) {
        std::cerr << "Error accepting request from client!" << std::endl;
        exit(1);
    }
    std::cout << "Connected with client!" << std::endl;

    std::cout << "Awaiting client response..." << std::endl;
    memset(&msg, 0, sizeof(msg));
    recv(newSd, reinterpret_cast<char *>(&msg), sizeof(msg), 0);
    std::cout << "Client: " << msg << std::endl;

    std::string msg_s(msg);
    std::vector<std::string> strs = split_strs(msg_s);
    std::vector<seq> data = split_seqs(strs);
    std::vector<std::vector<int>> seqs;
    for (auto& i : data) {
        seqs.emplace_back(seq_generator(i.start,i.step));
    }

    memset(&msg, 0, sizeof(msg));

    msg_s = build_msg(seqs);

    strcpy(msg,msg_s.c_str());

    send(newSd, reinterpret_cast<char *>(&msg), strlen(msg), 0);
    std::cout << "Data was sent to the client\n";

    close(newSd);
    close(serverSd);
    std::cout << "Connection closed..." << std::endl;
    return 0;
}