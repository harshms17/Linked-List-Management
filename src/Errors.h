#ifndef ERRORS_H
#define ERRORS_H

namespace Errors{ // Custom Error Class
    class file_error: public std::exception{ // error in opening file
        std::string message;
        public:
        // file_error(std::string msg):message("\033[1;31mFile Eror: " + msg) {} //color
        file_error(std::string msg):message("File Eror: " + msg) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    };
    class invalid_input: public std::exception{ // invalid input
        std::string message;
        public:
        // invalid_input(std::string msg): message("\033[1;31mInvalid Input: " + msg) {}  // color
        invalid_input(std::string msg): message("Invalid Input: " + msg) {} 
        const char* what() const noexcept override {
            return message.c_str();
        }
    };
    class invalid_request: public std::exception{ // invalid request
        std::string message;
        public:
        // invalid_request(std::string msg): message("\033[1;31mInvalid Request: " + msg) {} // color
        invalid_request(std::string msg): message("Invalid Request: " + msg) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
    };
}

#endif