#include <stdio.h>
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

char buffer[256];
int n = 0;
bool waitingForAck = false;
char temp[25];
int returnValue;

int verificationHandshake(int sockfd, DATAPACKET* senderData)
{
	memset(buffer, 0, sizeof(buffer));
	//Send connected to server, serverId
	returnValue = send(sockfd, "#BOARD1,CONNECTED,REQUEST@", 25, 0);
    if(returnValue == -1)
    	perror("Send");
	//Wait for ACK with name,ID
	//Save ip, name, id in struct
	//Send ack; verified,
	//End this function
	return 0;
}

int handshakeReceiveData(int sockfd, DATAPACKET* senderData)
{
	//Send to verified connection make request
	//Wait for ACK received message, and response with request
	//ACK reveice request, do stuff with request
	//Report back what happend with request
	//Wait for ACK
	//Listen for new request, if not time out and close connection
	return 0;
}
