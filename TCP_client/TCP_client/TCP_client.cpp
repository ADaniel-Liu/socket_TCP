// TCP_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")



int main()
{

	SOCKET socket1;
	WSADATA wsadata;

	int ErrorCode;

	if (WSAStartup(MAKEWORD(2, 1), &wsadata))
	{
		printf("Winsock initiate failed!");
		WSACleanup();
		return 0;
	}

	printf("Winsock client start ...\n");

	//设置IP和端口
	const char* ip = "192.168.1.101";
	struct sockaddr_in server;
	int len = sizeof(server);

	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	server.sin_addr.s_addr = inet_addr(ip);

	socket1 = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(socket1, (SOCKADDR*)&server, sizeof(SOCKADDR)) == 0)
	{

		while (1) {
			// 一收一发 无限循环
			char buffer[1024] = "\0";

			printf("input message:\n");
			scanf("%s", buffer);

			if (strcmp(buffer, "bye") == 0)
			{
				printf("exit, bye!!\n");
				Sleep(100);
				closesocket(socket1);
				break;
			}

			if (send(socket1, buffer, strlen(buffer) + 1, 0) != SOCKET_ERROR)
			{
				printf("sending...\n");
				Sleep(100);
				if (recv(socket1, buffer, sizeof(buffer), 0) != SOCKET_ERROR)
				{
					printf("recevie from server: %s\n", buffer);
				}
			}
		}
	}

	closesocket(socket1);
	system("pause");

    return 0;
}

