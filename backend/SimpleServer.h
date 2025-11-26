#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <functional>

#pragma comment(lib, "ws2_32.lib")

class SimpleServer {
public:
    void start(int port, std::function<std::string(std::string)> handler) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2), &wsaData);

        SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        listen(serverSocket, 5);

        std::cout << "Server running at http://localhost:" << port << std::endl;

        while (true) {
            SOCKET clientSocket;
            sockaddr_in clientAddr{};
            int clientSize = sizeof(clientAddr);

            clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

            char buffer[4096];
            int bytesReceived = recv(clientSocket, buffer, 4096, 0);
            if (bytesReceived <= 0) continue;

            buffer[bytesReceived] = '\0';
            std::string request(buffer);

            std::string response = handler(request);

            send(clientSocket, response.c_str(), response.size(), 0);
            closesocket(clientSocket);
        }

        closesocket(serverSocket);
        WSACleanup();
    }
};
