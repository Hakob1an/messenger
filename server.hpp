#ifndef SERVER_HPP
#define SERVER_HPP

#include "user.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <mutex>
#include <thread>
#include <string>
#include <algorithm>
#include <cstring>


class Server 
{
public:
    Server(int port);
    ~Server();

    void start();

private:
    void setupServerSocket();
    void acceptConnections();
    void handleClient(int clientSocket);
    void broadcastMessage(const std::string& message, int senderFd);

private:
    int port;
    int server_socket;
    std::unordered_map<int, std::unique_ptr<User>> clients;
    std::mutex clients_mutex;
};

Server::Server(int port) : port(port), server_socket(-1) 
{
    setupServerSocket();
}

Server::~Server() 
{
    close(server_socket);
}

void Server::start() 
{
    std::thread accept_thread(&Server::acceptConnections, this);
    accept_thread.detach();
    std::cout << "Server started. Press enter to exit." << std::endl;
    std::cin.get();
}

void Server::setupServerSocket() 
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

void Server::acceptConnections() 
{
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (true) {
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        std::thread client_thread(&Server::handleClient, this, client_socket);
        client_thread.detach();
        std::cout << "Accepted new connection." << std::endl;
    }
}

void Server::handleClient(int client_socket) 
{
    char buffer[1024] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }

    std::string username(buffer, bytes_read);
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients[client_socket] = std::make_unique<User>(client_socket, username);
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read <= 0) {
            break;
        }

        std::string message = username + ": " + std::string(buffer, bytes_read);
        broadcastMessage(message, client_socket);
    }

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.erase(client_socket);
    }
    close(client_socket);
    std::cout << "Connection closed." << std::endl;
}

void Server::broadcastMessage(const std::string& message, int senderFd) 
{
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (const auto& pair : clients) {
        int client_fd = pair.first;
        if (client_fd != senderFd) {
            send(client_fd, message.c_str(), message.length(), 0);
        }
    }
}

#endif //SERVER_HPP