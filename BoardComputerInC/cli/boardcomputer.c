#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "serversocket/serverSocket.h"

#define NodeInternal "10.10.0.1"
#define ServiceInternal "5000"
#define NodeExternal "192.168.1.100"
#define SeriveExternal "5500"

void networkFork(int fileadressInternal, int fileadressExternal);
void mainFork(void);

int main(int argc, char const *argv[])
{
    int internalNetwork = 0;
    int extrenalNetwork = 0;
	setupCommunicationServer(NodeInternal, ServiceInternal, &internalNetwork);
    setupCommunicationServer(NodeExternal, SeriveExternal, &extrenalNetwork);
	pid_t pid;
	pid = fork();
	if(pid == 0)
		networkFork(internalNetwork, extrenalNetwork);
	else
		mainFork();	
	printf("Done with program\n");	
    return 0;
}

void networkFork(int fileadressInternal, int fileadressExternal)
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
		acceptinConnectionsOnServer(fileadressInternal);   
	else
		acceptinConnectionsOnServer(fileadressExternal);	
}

void mainFork(void)
{
	//Do other tasks then networking	
}