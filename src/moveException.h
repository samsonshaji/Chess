#ifndef MOVEEXCEPTION_H
#define MOVEEXCEPTION_H

#include <exception>
#include <string>

class MoveException : public std::exception {
    public:
        MoveException(std::string msg) : msg(msg) {}
        const char* what() const noexcept override { return msg.c_str(); }
    private:
        std::string msg;
};

#endif