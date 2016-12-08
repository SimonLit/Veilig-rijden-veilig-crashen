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

char buffer[256];
int n = 0;
bool waitingForAck = false;
char temp[25];
int returnValue;

int verificationHandshake(int sockfd, bool* verfied)
{
	memset(buffer, 0, sizeof(buffer));
	//Send connected to server, serverId
	returnValue = send(sockfd, "#BOARD1,CONNECTED,REQUEST@", 25, 0);
    if(returnValue == -1)
    	perror("Send");
    waitingForAck = true;
	//Wait for ACK with name,ID
    while(waitingForAck)
    {
        n = read(sockfd, buffer, 255);
        printf("Message is : %s\n", buffer);
        if(n < 0)
            perror("read");
        for(int i = 0; i <256; i++)
        {
        	if(strncmp(buffer[i], "#", 1) == 0)
        	{
        		waitingForAck = false;
        		*verfied = true; //Temp
        		memset(buffer, 0, sizeof(buffer));
        		//Cut the message up and save it
    			//Work with the return values
    			//If verified save data from sender for futher use
        	}
        	else
        	{

        	}
        }
    }
    if(*verfied)
    {
    	//append message and send back
    	returnValue = send(sockfd, "#VERIFIED@", 9,0);
    	if(returnValue == -1)
    		perror("Send");
    	memset(buffer, 0, sizeof(buffer));
    	waitingForAck = true;
    	while(waitingForAck)
    	{
    		n = read(sockfd, buffer, 255);
    		printf("Message is : %s\n", buffer);
    		if(n < 0)
    			perror("read");
    		for(int i = 0; i < 256; i++)
    		{
    			if(strncmp(buffer[i], "#", 1) == 0)
    			{
    				waitingForAck = false;
    				//Cut up buffer and read the ack signal
					    			
    			}
    		}
    	}
    }
    else//Not verified
    {
    	returnValue = send(sockfd, "#NOT VERIFIED@", 14,0);
    	if(returnValue == -1)
    		perror("send");
    	return -1;
    }
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
