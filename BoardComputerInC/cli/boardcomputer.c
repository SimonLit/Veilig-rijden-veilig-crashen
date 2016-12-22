#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "serial/sercom.h"
#include "handshake/handshake.h"
#include "serversocket/serverSocket.h"

#define NodeInternal "10.10.0.1"
#define ServiceInternal "5000"
#define NodeExternal "192.168.1.105"
#define SeriveExternal "6000"

void networkFork(int fileadressInternal, int fileadressExternal);
void mainFork(void);

int main(int argc, char const *argv[])
{
    int internalNetwork = 0;
    int extrenalNetwork = 0;
	setupCommunicationServer(NodeInternal, ServiceInternal, &internalNetwork);
    //setupCommunicationServer(NodeExternal, SeriveExternal, &extrenalNetwork);
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		networkFork(internalNetwork, extrenalNetwork);	
	}
	else
	{
		mainFork();				
	}
    return 0;
}

void networkFork(int fileadressInternal, int fileadressExternal)
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
		//acceptinConnectionsOnServer(fileadressExternal);	
	}
}

void mainFork(void)
{
	while(1)
	{
		serialCommunicatie();//Reads out buffer and (respons to do)		
	}
}