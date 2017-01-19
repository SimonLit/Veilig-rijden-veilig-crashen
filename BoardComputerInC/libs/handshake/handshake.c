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
#include <time.h>
#include "handshake.h"
#include "../datastruct/datastruct.h"
#include "../message/message.h"
#include "../file_handeling/file_handeling.h"

char buffer[2048];
int j = 0;
int counter;
int returnValue;

int waitForAckFromClient(int sockfd)
{
	bool ack = false;
	memset(buffer, 0, sizeof(buffer));
	while(ack == false)
	{
		j = read(sockfd, buffer, 255);
		if(j < 0)
			perror("read");
		printf("Buffer wait ACK is %s\n", buffer);
		if(strcmp(buffer, "#ACK@") == 0)
			ack = true;
		sleep(1);
		memset(buffer, 0, sizeof(buffer));
	}
	return 1;
}

static int waitForFirstContact(int sockfd, DATAPACKET* recv)
{
	memset(buffer, 0, sizeof(buffer));
	while(1)//Break out with a timeout
	{
		//sleep(0.5);
		j = read(sockfd, buffer, 255);
		printf("DEBUG:READ: %s\n", buffer);
		if(j < 0)
			perror("read");
		else
		{
			printf("DEBUG:WAITFORFIRSTCONTACT: The message is: %s\n", buffer);
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
	counter = 0;
	do{
		 returnValue = waitForFirstContact(sockfd, recv);
		 if(returnValue == -1)
		 {
		 	counter++;	
		 	returnValue = send(sockfd, "#NACK@\n", 7, 0);
		 	if(returnValue == -1)
		 	{
		 		perror("send");
		 		send(sockfd, "#NACK@\n", 7, 0);
		 	}
		 }
		 else if(returnValue == 0)
		 {
		 	printf("DEBUG:CONNECT: Send verified\n");
		 	returnValue = send(sockfd, "#ACK@\n", 6, 0);
		 	if(returnValue == -1)
		 	{
		 		perror("send");
		 		send(sockfd, "#ACK@\n", 6, 0);
		 	}
		 	return 0;
		 }
	}while(counter < 4);
	return -1;	
}

static int recvData(int sockfd, DATAPACKET* recveid)
{
	memset(buffer, 0, sizeof(buffer));
	while(1)//Break out with a timeout
	{
		j = read(sockfd, buffer, 255);
		if(j < 0)
			perror("read");
		else
		{	
			printf("DEBUG:RECVDATA: The message is: %s\n", buffer);
			returnValue = dataCutRecvResponse(recveid, buffer);
			if(returnValue == -1)
			{
				returnValue = send(sockfd, "#NACK@\n", 7, 0);
				if(returnValue == -1)
				{
					perror("send");
					send(sockfd, "#NACK@\n", 7, 0);
				}
				return -1;
			}
			else	
			{
				return 0;
			}
		}
	}
	return -1;
}

int handshakeReceiveData(int sockfd, const char* ip)
{
	DATAPACKET connectionData;
	connectionData.sockFd = sockfd;
	memset(buffer, 0, sizeof(buffer));
	returnValue = connectVerify(sockfd, &connectionData);
	printf("DEBUG:HANDSHAKE: Broke out connectVerify\n");
	if(returnValue == -1)
		return -1;
	else
	{
		returnValue = recvData(sockfd, &connectionData);
		if(returnValue == -1)
			return -1;
		else
		{
			strcpy(connectionData.senderIpAdress, ip);
			if(returnValue == -1)
			{
				printf("Something went wrong with respond\n");
				return -1;
			}
			write_To_Log_file(DATALOG, &connectionData);
			printf("Wrote data to log file.\n");
			if(connectionData.sf == true)
			{
				writeDataStructToFile(carCrashData, &connectionData);
				printf("Writing data to send file.\n");
			}
			return 0;
		}
	}
}

int secondDataRec(DATAPACKET* d)
{
	char secondBuffer[255];
	memset(secondBuffer, 0, sizeof(secondBuffer));
	while(1)//Break out with a timeout
		{
			j = read(d->sockFd, secondBuffer, 255);
			if(j < 0)
				perror("read");
			else
			{	
				printf("DEBUG:SECONDRECVDATA: The message is: %s\n", secondBuffer);
				int rv = correctFormatCheckRemoveBitshift(secondBuffer);
				char** ar = NULL;
				int t = split(secondBuffer, '|', &ar);
			    if(strcmp(ar[0], "PDA") == 0)
    			{
        			strcpy(d->stopPhoneData, secondBuffer);
        			send(d->sockFd ,"#ACK@\n", 6,0);
					writeDataStructToFile(phoneInsFile, d);
        			return 0;
    			}
    			else if(strcmp(ar[0], "PDB") == 0)
    			{
        			strcpy(d->crahsPhoneData, secondBuffer);
        			send(d->sockFd ,"#ACK@\n", 6,0);
        			writeDataStructToFile(phoneCrashFile, d);	
        			return 0;
    			}
    			return -1;
			}
		}
}

