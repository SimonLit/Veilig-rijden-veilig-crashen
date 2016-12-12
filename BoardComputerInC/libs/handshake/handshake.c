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
#include "../response/response.h"
#include "../datastruct/datastruct.h"

#define SERVERNAME "BOARDCOMPUTER";
#define SERVERID 1;

#define startOfMessageChar '#'
#define endOfMessageChar '@'
#define ackString "ACK"

char buffer[256];
int j = 0;
bool waitingForAck = false;
char temp[25];
int returnValue;
char bufferRead;
int ackValue;

int findStartOfMessage(const char* message)
{
	//char received[] = message;
	for(int i = 0; i < 256; i++)
	{
	//	if(received[i] == startOfMessageChar)
			return i;
	}
	return -1;
}

int findEndOfMessage(const char* message)
{
	//char received[] = message;
	for (int i = 0; i < 256; ++i)
	{
	//	if(received[i] == endOfMessageChar)
			return i;
	}
	return -1;
}

int lengthOfMessage(const char* message)
{
	int startPos = 0;
	int endPos = 0;
	startPos = findStartOfMessage(message);
	if(startPos == -1)
		return -1;
	endPos = findEndOfMessage(message);
	if(endPos == -1)
		return -1;
	return (endPos - startPos);
}

int waitForAckFromClient(int sockfd)
{
	bool ack = false;
	memset(buffer, 0, sizeof(buffer));
	while(ack == false)
	{
		j = read(sockfd, buffer, 255);
		printf("Wait for ACK, message is : %s\n", buffer);
		if(j < 0)
			perror("read");
		if(strcmp(buffer, ackString) == 0)
			ack = true;
	}
	return 1;
}

//Input enum, wich kind of message to expect
int readBufferForMessageAndVerify(int sockfd)
{
	memset(buffer, 0, sizeof(buffer));
	bool messageReceived = false;
	while(messageReceived == false)
	{

	}
	return 1;
}

int verificationHandshake(int sockfd)
{
	returnValue = send(sockfd, "#BOARDPC|CONNECTED@", 19, 0);
    if(returnValue == -1)
    	perror("Send");
    ackValue = waitForAckFromClient(sockfd);
    if(ackValue != 1)
    {
    	//Do something, resent otherwise kill connection
    }
    returnValue = send(sockfd, "#BOARDPC|REQUEST|VERIFICATION@", 29, 0);
    if(returnValue == -1)
    	perror("send");
    ackValue = -5;
    ackValue = waitForAckFromClient(sockfd);
    if(ackValue != 1)
    {
    	//Do something
    }
    returnValue = readBufferForMessageAndVerify(sockfd);
    if(returnValue != 1)
    {
    	//Do something
    }
    returnValue = send(sockfd, "#BOARDPC|ACK@", 12, 0);
    if(returnValue == -1)
    	perror("send");
    //Send verified or not verified
    ackValue = -5;
    ackValue = waitForAckFromClient(sockfd);
    if(ackValue != 1)
    {
    	//Do something
    }
    return 0;
}

int handshakeReceiveData(int sockfd)
{
	//Send to verified connection make request
	//Wait for ACK received message, and response with request
	//ACK reveice request, do stuff with request
	//Report back what happend with request
	//Wait for ACK
	//Listen for new request, if not time out and close connection
	return 0;
}
