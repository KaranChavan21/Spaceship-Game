#pragma once
#include <WS2tcpip.h>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
class recvdata
{
public:
	sockaddr_in server;
	SOCKET in;
	sockaddr_in client;
	int clientLength = sizeof(client);
	void wsastartup()
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
	void bindsocket()
	{

		in = socket(AF_INET, SOCK_DGRAM, 0);
		sockaddr_in serverHint;
		serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
		serverHint.sin_family = AF_INET;
		serverHint.sin_port = htons(54000);
		if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
		{
			cout << "Can't bind socket! " << WSAGetLastError() << endl;
			return;
		}
		cout << "bind complete";

	}
	string recv()
	{
		char buf[1024];


		ZeroMemory(&client, clientLength);
		ZeroMemory(buf, 1024);

		int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
		}
		string s = buf;
		return s;


	}
	void closesocketserv()
	{
		closesocket(in);
		WSACleanup();
	}
};
