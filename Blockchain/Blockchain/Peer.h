#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <thread>
#include "Helper.h"
#include <mutex>
#include "AES.h"
#include <exception>
#include "Requests.h"
#include "FileManager.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define SERVER_IP "127.0.0.1"
#define PORT 5078

#define NEW_USER "a"
#define CONNECTING "b"
#define PORT_SIZE 5
#define BIG_SIZE 15

class Peer
{
public:
	
	
	//Declarations
	static void recieveMessageAndHandle(SOCKET sc);
	static void connectMoreUsers(SOCKET listenSocket, int port);
	static int start();
private:
	static std::map<std::string, netInfo> users;
	static userInfo user;
	static std::string name;
	static std::vector<Transaction*> queue;
	static WSADATA wsaData;
	static std::mutex lock_users;

	static std::string getNameOfUser(SOCKET sc);
	static void sendToAllUsers(std::string code, std::string input);
	static bool checkPort(std::string port);
	static bool checkNum(std::string num);
	static std::string keyExchangeRecieving(SOCKET clientSocket);
	static std::string keyExchangeEntering(SOCKET clientSocket);
	static void sendDetails(SOCKET clientSocket);
	static void mineCurBlock();


};

