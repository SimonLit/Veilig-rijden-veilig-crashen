#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "handshake.h"
#include "../message/message.h"
#include "../response/response.h"
#include "../datastruct/datastruct.h"

char buffer[256];
int j = 0;
int counter;
int returnValue;

static int waitForAckFromClient(int sockfd)
{
	bool ack = false;
	memset(buffer, 0, sizeof(buffer));
	while(ack == false)
	{
		j = read(sockfd, buffer, 255);
		if(j < 0)
			perror("read");
		if(strcmp(buffer, "#ACK@") == 0)
			ack = true;
	}
	return 1;
}

static int waitForFirstContact(int sockfd, DATAPACKET* recv)
{
	memset(buffer, 0, sizeof(buffer));
	while(1)//Break out with a timeout
	{
		j = read(sockfd, buffer, 255);
		if(j < 0)
			perror("read");
		else
		{
			printf("The message is: %s\n", buffer);
			//Read message, check if proper one
			//If message is correct, send back Verified
			//Else return -1
			//Save in data struct
			return -1;
		}
	}
	return -1;
}

static int connectVerify(int sockfd, DATAPACKET* recv)
{
	bool verifiedCon = false;
	do{
		 returnValue = waitForFirstContact(sockfd, recv);
		 if(returnValue == -1)
		 {
		 	counter++;	
		 	returnValue = send(sockfd, "NACK", 4, 0);
		 	if(returnValue == -1)
		 	{
		 		perror("send");
		 		send(sockfd, "NACK", 4, 0);
		 	}
		 }
		 else
		 {
		 	verifiedCon = true;
		 }
	}while(verifiedCon == false || counter < 4);
	if(verifiedCon = true)
		return 0;
	else
		return -1;	
}

static int recvData(int sockfd, DATAPACKET* recv)
{
	memset(buffer, 0, sizeof(buffer));
	while(1)//Break out with a timeout
	{
		j = read(sockfd, buffer, 255);
		if(j < 0)
			perror("read");
		else
		{	
			printf("The message is: %s\n", buffer);
			//Read message, check the command
			//If message is correct, do response accordanly to responses
			//Else return -1
			return -1;
		}
	}
	return -1;

}

int handshakeReceiveData(int sockfd)
{
	DATAPACKET connectionData;
	returnValue = connectVerify(sockfd, &connectionData);
	if(returnValue == -1)
		return -1;
	else
	{
		returnValue = recvData(sockfd, &connectionData);
		if(returnValue == -1)
			return -1;
		else
		{
			//Write data to file
		}
	}
}
