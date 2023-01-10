/*
	example code from https://www.cs.ubbcluj.ro/~dadi/compnet/labs/lab3/udp-broadcast.html
*/
#include"winsock2.h"
#include<iostream>
#include<conio.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define MYPORT 3333    // the port users will be connecting to
#define RCVBUFFLEN 51
#define UDPCNT2RCV 20

static volatile bool g_exit = false;
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
	g_exit = true;
	return TRUE;
}

int main()
{
	WSADATA wsaData;
	SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
	(void)WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	char broadcast = '1';

	//     This option is needed on the socket in order to be able to receive broadcast messages

	//   If not set the receiver will not receive broadcast messages in the local network.

	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
		cout << "Error in setting Broadcast option";
		closesocket(sock);
		return 0;
	}

	struct sockaddr_in Recv_addr;
	struct sockaddr_in Sender_addr;
	int len = sizeof(struct sockaddr_in);
	char recvbuff[RCVBUFFLEN];
	char sendMSG[] = "Broadcast message from READER";

	Recv_addr.sin_family = AF_INET;
	Recv_addr.sin_port = htons(MYPORT);
	Recv_addr.sin_addr.s_addr = INADDR_ANY;

	cout << "\n\t Waiting for UDP broadcast data...\n";
	if (bind(sock, (sockaddr*)&Recv_addr, sizeof(Recv_addr)) < 0)
	{
		cout << "Error in BINDING" << WSAGetLastError();
		(void)_getch();
		closesocket(sock);
		return 0;
	}
	while(!g_exit) {

		recvbuff[recvfrom(sock, recvbuff, RCVBUFFLEN-1, 0, (sockaddr*)&Sender_addr, &len)]='\0';
		cout << "\n\tReceived Message is : " << recvbuff;
	}
	cout << "\n\n\tPress Any to send message";
	(void)_getch();

#if 0	// no reply message

	if (sendto(sock, sendMSG, strlen(sendMSG) + 1, 0, (sockaddr*)&Sender_addr, sizeof(Sender_addr)) < 0)
	{
		cout << "Error in Sending." << WSAGetLastError();
		cout << "\n\n\t\t Press any key to continue....";
		_getch();
		closesocket(sock);
		return 0;
	}
	else
		cout << "\n\n\n\tREADER sends the broadcast message Successfully";

	cout << "\n\n\tpress any key to CONT...";
	_getch();

#endif

	closesocket(sock);
	WSACleanup();
}