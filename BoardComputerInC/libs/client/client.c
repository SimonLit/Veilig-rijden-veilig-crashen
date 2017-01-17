#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "client.h"
#include "../datastruct/datastruct.h"

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
	printf("Return value conncet %d\n", rv);
	if(rv == 0)
	{
		printf("\n");
		printf("Connection is succesfull with Insurance server\n");
		printf("\n");
		return 0;
	}
	else if(rv == -1)
	{
		printf("Connection error to server\n");
		return -1;
	}
	return 1;
}

int sendDataOverConnection(int socketFd, const char* string)
{
	int rv;
	char buffer[1024];
	//Request connection
	//#CONNECT@
	//Listen for ack
	//#ACK@ #NACK@
	//Send data from parameter

	//listen for ack

	//Exit connection


	//printf("Sending data over socketFd\n");
	rv = send(socketFd, "#Hqsf,eqsf,lqfs,lqsf,oqsf,qdfq,qsd@", 35, 0);
	rv = read(socketFd, buffer, 255);
	if(rv < 0)
		printf("Read error\n");
	printf("Read buffer is %s \n", buffer );
	return 0;

}
