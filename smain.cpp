#include "server.hpp"
#include <iostream>

int main() 
{
    int port = 8080; 
    Server server(port);

    try {
        std::cout << "Starting server on port " << port << std::endl;
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
