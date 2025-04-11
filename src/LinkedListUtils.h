#ifndef LINKED_LIST_UTILS_H
#define LINKED_LIST_UTILS_H

template<typename T>
std::string convertToString(T data){ // convert any data to string
    std::stringstream ss;
    ss << data;
    return ss.str();
}
#endif