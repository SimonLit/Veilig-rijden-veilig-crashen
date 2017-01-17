#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "serial/sercom.h"
#include "handshake/handshake.h"
#include "serversocket/serverSocket.h"
#include "client/client.h"

#define NodeInternal "10.10.0.1"
#define ServiceInternal "5000"
#define NodeExternal "192.168.1.102"
int SerivecExternal  = 6000;

void networkFork(int fileadressInternal);
void mainFork(void);

int main(int argc, char const *argv[])
{
    int internalNetwork = 0;

	setupCommunicationServer(NodeInternal, ServiceInternal, &internalNetwork);
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		networkFork(internalNetwork);	
	}
	else
	{
		mainFork();				
	}
    return 0;
}

void networkFork(int fileadressInternal)
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		while(1)
		{
			acceptinConnectionsOnServer(fileadressInternal);   		
		}
	}
	else
	{
		int extrenalNetwork = 0;
		int rv = -1;
		char bufferToSend[255];
		while(rv == -1)
		{
			rv = setupClientConnection(NodeExternal, SerivecExternal, &extrenalNetwork);
		}
		while(1)
		{
			//Read out file every x amount of second if the file exists 
			//Take out the data to send
			rv = sendDataOverConnection(extrenalNetwork, bufferToSend);
		}
	}
}

void mainFork(void)
{
	while(1)
	{
		serialCommunicatie();//Reads out buffer and (respons to do)		
	}
}