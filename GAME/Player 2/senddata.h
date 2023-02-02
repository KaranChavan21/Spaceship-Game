#pragma once
#include <WS2tcpip.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
class senddata
{
public:
	sockaddr_in server;
	SOCKET out;
	void startwsa()
	{
		WSADATA data;

		WORD version = MAKEWORD(2, 2);


		int wsOk = WSAStartup(version, &data);
		if (wsOk != 0)
		{
			cout << "Can't start Winsock! " << wsOk;
			return;
		}
	}
	void connect()
	{

		server.sin_family = AF_INET;
		server.sin_port = htons(54000);                     //define the server structure of player 1 
		inet_pton(AF_INET, "192.168.1.10", &server.sin_addr);
		out = socket(AF_INET, SOCK_DGRAM, 0);
	}
	void sendinfo(string data)
	{
		int sendOk = sendto(out, data.c_str(), data.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	}
	void closesocketclient()
	{
		closesocket(out);
		WSACleanup();
	}
};
