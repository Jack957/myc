/*
* example code from https://www.cs.ubbcluj.ro/~dadi/compnet/labs/lab3/udp-broadcast.html
* History : 2023-Dec-20 socket time out options added
*/

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define UDP_PORT       3333       /* the port users will be connecting to */
#define RCVBUFLEN      1024
#define RECV_ADDR      "172.19.1.35"
#define REPEAT_TIMES   8         /* message repeat number */
#define RCVTO          5000       /* socket receive time out */
#define SNDTO          5000       /* socket send time out */
#define BY_BROADCAST		
#define PAUSE_AT_END		          /* pause at end of test */

using namespace std;

int main(void)
{
	WSADATA wsaData;
	(void)WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);



	cout << "\tudpsender program" << endl << endl;

	/* upd socket create
	*  int level           = SOL_SOCKET
	*  int optname         = SO_BROADCAST
	*  const char* optval  = &broadcast
	*  int opteln          = sizeof(broadcast)
	*/
#ifdef BY_BROADCAST
	char broadcast = '1';	/* broadcast */
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
		cout << "\tError in setting Broadcast option" << endl;
		closesocket(sock);
		return 0;
	}
#endif
	/* set receive time out */
	int rcvtimeo = RCVTO;
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

	int len = sizeof(struct sockaddr_in);

	char sendMSG[] = "Hello, is anyone there?";

	char recvbuff[RCVBUFLEN] = "";

	Recv_addr.sin_family = AF_INET;  /* internet protocol */
	Recv_addr.sin_port = htons(UDP_PORT);


#ifdef BY_BROADCAST
	Recv_addr.sin_addr.s_addr = INADDR_BROADCAST; // this is equiv to 255.255.255.255
#else
	/* local subnet broadcast does not work */
	inet_pton(AF_INET, RECV_ADDR, &Recv_addr.sin_addr.s_addr);
#endif

	int iResult = 0;

	int nr = 0;

	while (nr++ < REPEAT_TIMES)
	{
		iResult = sendto(sock, sendMSG, (int)strlen(sendMSG) + 1, 0, (sockaddr*)&Recv_addr, (int)sizeof(Recv_addr));
		if (iResult == SOCKET_ERROR) {
			int errNum = WSAGetLastError();
			if (errNum == WSAETIMEDOUT)
			{
				cout << "\tsend message failed with time out error" << endl;
			}
			else
			{
				cout << "\tsendto failed with error" << WSAGetLastError() << endl;
			}
		}
		else {
#ifdef BY_BROADCAST
			cout << "\tbroadcast " << nr << " \"" << sendMSG << "\" to port ";
#else
			cout << "\tsend " << nr << " \"" << sendMSG << "\" to " << RECV_ADDR << ":";
#endif		
			cout << UDP_PORT << endl;
		}

		/*
		 * int WSAAPI recvfrom
		 * [in]                SOCKET   s,
		 * [out]               char     *buf,
		 * [in]                int      len,
		 * [in]                int      flags,
		 * [out]               sockaddr *from,
		 * [in, out, optional] int      *fromlen
		*/
		struct sockaddr_in from_addr;
		int addr_len = sizeof(from_addr);
		iResult = recvfrom(sock, recvbuff, RCVBUFLEN, 0, (sockaddr*)&from_addr, &addr_len);
		if (iResult == SOCKET_ERROR) {
			int rcvError = WSAGetLastError();
			if (rcvError == WSAETIMEDOUT) {
				cout << "\twaited " << (RCVTO / 1000) << " sec with no reply" << endl;
			}
			else
				cout << "\trecvfrom failed with error " << rcvError << endl;
		}
		else {
			/* report reply message */
			char ip_str[20];
			inet_ntop(AF_INET, &from_addr.sin_addr, ip_str, 20);		/* convert replyer's net address to IP string */
			cout << "\trecv \"" << recvbuff << "\" from " << ip_str << ":" << from_addr.sin_port << endl;
			Sleep(1000);
		}
		cout << endl;

	} /* end while (nr++ < REPEAT_TIMES) */


#ifdef PAUSE_AT_END
	cout << "\tpress any key to exit..." << endl;
	(void)_getch();
#endif

	closesocket(sock);
	WSACleanup();
	}