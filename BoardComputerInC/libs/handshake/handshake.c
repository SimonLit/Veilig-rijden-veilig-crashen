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
#include "../datastruct/datastruct.h"
#include "../response/response.h"
#include "../message/message.h"
#include "../file_handeling/file_handeling.h"

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
		else if( j == 0)//End of fd read
		{
			printf("The message is: %s\n", buffer);
			returnValue = verificationStringCut(recv, buffer);
			if(returnValue == 0)
			{
				recv -> sockFd = sockfd;
				//Timestamp
				return 0;
			}
			else
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
		 else if(returnValue = 0)
		 {
		 	verifiedCon = true;
		 }
	}while(verifiedCon == false || counter < 4);
	if(verifiedCon = true)
		return 0;
	else
		return -1;	
}

static int recvData(int sockfd, DATAPACKET* recv, bool* sf)
{
	memset(buffer, 0, sizeof(buffer));
	RESPONSES rsp;
	while(1)//Break out with a timeout
	{
		j = read(sockfd, buffer, 255);
		if(j < 0)
			perror("read");
		else
		{	
			printf("The message is: %s\n", buffer);
			returnValue = dataCutRecvResponse(recv, buffer, &rsp);
			if(returnValue == -1)
				return -1;
			else	
			{
				//Do response
				//Set sf flag
				return 0;
			}
		}
	}
	return -1;

}

int handshakeReceiveData(int sockfd, const char* ip)
{
	DATAPACKET connectionData;
	bool sendFlag = false;
	returnValue = connectVerify(sockfd, &connectionData);
	if(returnValue == -1)
		return -1;
	else
	{
		returnValue = recvData(sockfd, &connectionData, &sendFlag);
		if(returnValue == -1)
			return -1;
		else
		{
			strcpy(connectionData.senderIpAdress, ip);
			writeDataStructToFile(DATALOG, &connectionData);
			printf("Wrote data to log file.\n");
			if(sendFlag == true)
			{
				writeDataStructToFile(DATASEND, &connectionData);
				printf("Writing data to send file.\n");
			}
			return 0;
		}
	}
}
