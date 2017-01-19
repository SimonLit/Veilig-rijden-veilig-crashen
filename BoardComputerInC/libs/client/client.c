#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "client.h"
#include "../datastruct/datastruct.h"
#include "../handshake/handshake.h"

int setupClientConnection(const char* node, int service, int* socknumber)
{
	printf("Starting setup client connection\n");
	int clientSocket, rv;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	//Create the socket
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(clientSocket == 0)
	{
		printf("Error ClientSocket\n");
	}
	*socknumber = clientSocket;
	//Configure server connection settings
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons((uint16_t)service);//Set the port
	serverAddr.sin_addr.s_addr = inet_addr(node);//Set the ip address of server
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
	//Connect to server
	addr_size = sizeof(serverAddr);
	printf("Trying to connect.\n");
	rv = connect(clientSocket, (struct  sockaddr*) &serverAddr, addr_size);
	if(rv == 0)
	{
		printf("\n");
		printf("Connection is succesfull with Insurance server\n");
		printf("\n");
		return 0;
	}
	else if(rv == -1)
	{
		printf("Connection error to server, %s\n", strerror(errno));
		return -1;
	}
	return 1;
}

int sendDataOverConnection(int socketFd, const char* string, int lenghtMessage)
{
	int rv;
	rv = send(socketFd, "#CONNECT@", 9,0);
	printf("Send connect to C#\n");
	if(rv == -1)
	{
		printf("Retrying sending connect\n");
		send(socketFd, "#CONNECT@", 9,0);
	}
	printf("Wainting for ACK from C#\n");
	rv = waitForAckFromClient(socketFd);//Server send ACK and we are connected
	if(rv == 1)
	{
		sleep(0.5);
		printf("Send data to c#\n");
		printf("String is %s, %d\n", string, lenghtMessage);
		rv = send(socketFd, string, lenghtMessage, 0);		
		if(rv == -1)
		{
			send(socketFd, string, lenghtMessage, 0);
		}
		printf("Waiting for ACK\n");
		rv = waitForAckFromClient(socketFd);
		if(rv == 1)
		{
			printf("Succesfull send data to pc\n");
			return 0;
		}
		return -1;
	}
	return -1;
}
