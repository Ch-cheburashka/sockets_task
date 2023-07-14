//
// Created by mrmamongo on 29.06.23.
//

#ifndef SOCKETS_TASK_EXCEPTIONS_HPP
#define SOCKETS_TASK_EXCEPTIONS_HPP

#include <cstring>
#include <exception>

class connection_exception : public std::exception {
private:
    char* error_;
public:
    explicit connection_exception(char* error): error_(error){};

    [[nodiscard]] char* what() const noexcept override {
        return error_;
    }
};

class send_exception : public std::exception {
private:
    const char* address_;
public:
    explicit send_exception(const char* address): address_(address) {};

    [[nodiscard]] const char* what() const noexcept override {
        char* error;
        sprintf(error, "Exception while sending message to server: %s", address_);

        return error;
    }
};

class not_implemented_exception : public std::exception {
    [[nodiscard]] char * what() const noexcept override {
        return "Not implemented!";
    }
};

#endif //SOCKETS_TASK_EXCEPTIONS_HPP
