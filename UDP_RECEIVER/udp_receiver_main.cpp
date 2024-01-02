/*
* example code from https://www.cs.ubbcluj.ro/~dadi/compnet/labs/lab3/udp-broadcast.html
* History : 2023-Dec-20 add socket time out option
*/

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <conio.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define MYPORT         3333    /* the port users will be connecting to */
#define RCVBUFFLEN     1024
#define UDPCNT2RCV     20	/* not used */
#define RCVTO          2000     /* socket receive time out */
#define SNDTO          5000     /* socket send time out */
#undef  SOCK_BROADCAST_ON

int reply_message(SOCKET sock, sockaddr* sender_addr, int sender_addr_len);

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

	//     This option is needed on the socket in order to be able to receive broadcast messages
	//   If not set the receiver will not receive broadcast messages in the local network.
#ifdef SOCK_BROADCAST_ON
	char broadcast = '1';
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
		cout << "Error in setting Broadcast option" << endl;
		closesocket(sock);
		return 0;
	}
#endif
	/* set receive time out */
	int rcvtimeo = RCVTO; /* 3 seconds */
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&rcvtimeo, sizeof(rcvtimeo)) < 0)
	{
		cout << "\tError in setting receive time out option" << endl;
		closesocket(sock);
		return 0;
	}
	/* set send time out */
	int sndtimeo = SNDTO;
	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&sndtimeo, sizeof(sndtimeo)) < 0)
	{
		cout << "\tError in setting send time out option" << endl;
		closesocket(sock);
		return 0;
	}

	struct sockaddr_in Recv_addr;
	struct sockaddr_in Sender_addr;
	int len = sizeof(struct sockaddr_in);
	char recvbuff[RCVBUFFLEN];


	Recv_addr.sin_family = AF_INET;
	Recv_addr.sin_port = htons(MYPORT);
	Recv_addr.sin_addr.s_addr = INADDR_ANY;

	cout << "\tWaiting for UDP data..." << endl;

	/* bind socket to service port */
	if (bind(sock, (sockaddr*)&Recv_addr, sizeof(Recv_addr)) < 0)
	{
		cout << "\tError in BINDING " << WSAGetLastError() << endl;
		(void)_getch();
		closesocket(sock);
		return 0;
	}

	int msg_count = 0;
	while (!g_exit) {
		/* receive message from service port */
		int result = recvfrom(sock, recvbuff, RCVBUFFLEN - 1, 0, (sockaddr*)&Sender_addr, &len);
		if (result == SOCKET_ERROR ) {
			int errCode = WSAGetLastError();
			if (errCode != WSAETIMEDOUT) {
				g_exit = true;
				cout << "\tError in recvfrom " << errCode << endl;
			}
		}
		else if(result>0)
		{
			recvbuff[result] = '\0';
			msg_count++;
			char sender_ip_str[20];
			inet_ntop(AF_INET, &Sender_addr.sin_addr, sender_ip_str, 20);  /* convert sender address to  IP string */
			cout << endl << "\tReceived:  \"" << recvbuff << "\" from " << sender_ip_str <<":"<< Sender_addr.sin_port << endl;

			/* reply message to sender */
			reply_message(sock, (sockaddr*)&Sender_addr, (int)sizeof(Sender_addr));
			cout << "\tNumber of messages received is " <<  msg_count  << endl;
		}
	} /* while (!g_exit) */

	cout << endl << "\tPress Any key to exit" << endl;
	(void)_getch();

	closesocket(sock);
	WSACleanup();
}

int reply_message(SOCKET sock, sockaddr* sender_addr, int sender_addr_len)
/*
* Description : reply message
*/
{
	int Result;
	char sendMSG[] = "Hi, what can I do for you?";
	Result = sendto(sock, sendMSG, (int)strlen(sendMSG) + 1, 0, sender_addr, sender_addr_len);
	if (Result == SOCKET_ERROR)
		cout << "Error in Sending." << WSAGetLastError() << endl;
	else 
		cout << "\tSend return message \"" << sendMSG << "\" successfully" << endl;

	return Result;
}