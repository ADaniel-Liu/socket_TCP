// socket_TCP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")


using namespace std;

int main()
{

	SOCKET RecvSocket;
	WSADATA wsadata;

	int ErrorCode;

		//初始化Winsock
	if (WSAStartup(MAKEWORD(2, 1), &wsadata))
	{
		printf("Winsock initiate failed!");
		WSACleanup();
		return 1;
	}

	printf("Winsock start ...\n");

	//设置IP和端口
	const char* ip = "192.168.1.101";
	u_short SERV_PORT = 12345;
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(SERV_PORT);
	local.sin_addr.s_addr = inet_addr(ip);

	struct sockaddr_in client;
	int len = sizeof(client);

	RecvSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	bind(RecvSocket, (struct sockaddr*)&local, sizeof(local));

	while (1) {

		char buffer[1024] = "\0";

		printf("waiting for message from the client...\n");

		if (listen(RecvSocket, 10) != SOCKET_ERROR)
		{
			SOCKADDR_IN clientAddr;
			int len1 = sizeof(SOCKADDR);

			SOCKET connSocket = accept(RecvSocket, (SOCKADDR*)&clientAddr, &len1);
			if (connSocket == INVALID_SOCKET)
			{
				printf("accept failed!");
				return -1;
			}

			while (1)
			{
				char recvBuf[100];
				if (recv(connSocket, recvBuf, sizeof(recvBuf), 0) != SOCKET_ERROR)
				{
					printf("recevie message: [%s] --- %s\n", inet_ntoa(clientAddr.sin_addr), recvBuf);
					send(connSocket, recvBuf, strlen(recvBuf) + 1, 0);
				}

			}

			closesocket(connSocket);
		}

	}

	closesocket(RecvSocket);
	system("pause");

	return 0;

}

