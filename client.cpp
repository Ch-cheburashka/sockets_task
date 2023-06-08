#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>


int main(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc != 3)
    {
        std::cerr << "Usage: ip_address port" << std::endl;
        exit(0);
    }
    //grab the IP address and port number
    char *serverIp = argv[1]; int port = atoi(argv[2]);

    char msg[2000];
    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,(sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        std::cout<<"Error connecting to socket!"<<std::endl;
        exit(1);
    }
    std::cout << "Connected to the server!" << std::endl;
    std::cout << "Enter seq: ";
    std::string data, line;
    while (true){
        line.clear();
        std::getline(std::cin, line);
        if (line == "export seq")
            break;
        data+=line + "\n";
    }
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, data.c_str());
    send(clientSd, reinterpret_cast<char*>(&msg), strlen(msg), 0);
    std::cout << "\nAwaiting server response..." << std::endl;
    memset(&msg, 0, sizeof(msg)); //clear the buffer
    recv(clientSd, reinterpret_cast<char*>(&msg), sizeof(msg), 0);
    std::cout << "Server: \n" << msg << std::endl;
    close(clientSd);
    std::cout << "Connection closed" << std::endl;
    return 0;
}