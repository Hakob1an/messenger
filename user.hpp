#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
    User(int socket, const std::string& name) : _socket(socket), _username(name) {}

    int getSocket() const { return _socket; }
    std::string getUsername() const { return _username; }
    void setUsername(const std::string& name) { _username = name; }

private:
    int _socket; 
    std::string _username; 
};

#endif //USER_HPP
