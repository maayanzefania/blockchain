#include <exception>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")

#define PORT 5078

int main() {
    std::string input = "";
    std::cout << "Enter 'a' for server, anything else for client\n";
    std::cin >> input;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    if (input == "a")
    {
      

        SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET) {
            std::cerr << "Error creating socket\n";
            WSACleanup();
            return 1;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(PORT);

        if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Listen failed\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Waiting for incoming connections...\n";
        sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Peer connected\n";
        while (true);
        // Handle communication with connected peer

        closesocket(clientSocket);
        closesocket(listenSocket);
    }
    else
    {
        std::cout << "Enter server IP : ";
        std::cin >> input;
        SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error creating socket\n";
            WSACleanup();
            return 1;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("1.0.0.127");
        serverAddr.sin_port = htons(PORT);

        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            int error = WSAGetLastError();
            std::cerr << "Connection failed with error: " << error << "\n";
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Connected to peer\n";
        while (true);

        // Handle communication with connected peer

        closesocket(clientSocket);
        

    }

    


    WSACleanup();
    return 0;
}