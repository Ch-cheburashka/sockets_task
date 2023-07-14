#include <client.h>
#include "exceptions.hpp"

//
// Created by mrmamongo on 12.07.23.
//
int main() {
    try {
        client cl{};
        cl.connect("127.0.0.1", 9998);
        std::string message = "Hello, server!";
        cl.send(message);
        std::string response = cl.receive();
        std::cout << "Server response: " << response << std::endl;
        cl.close();
        return 0;
    } catch (const send_exception& ex) {
        std::cout << "Send exception occurred: " << ex.what() << std::endl;
        return 1;
    } catch (const connection_exception& ex) {
        std::cout << "Connection exception occurred: " << ex.what() << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cout << "Exception occurred: " << ex.what() << std::endl;
        return 1;
    }

}