#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "serversocket/serverSocket.h"

#define NodeInternal "10.10.0.1"
#define ServiceInternal "5000"
#define NodeExternal "192.168.1.100"
#define SeriveExternal "5500"

int main(int argc, char const *argv[])
{
    int internalNetwork = 0;
    int extrenalNetwork = 0;
	setupCommunicationServer(NodeInternal, ServiceInternal, &internalNetwork);
    setupCommunicationServer(NodeExternal, SeriveExternal, &extrenalNetwork);
	pid_t pid;
	pid = fork();
	if(pid == 0)
		acceptinConnectionsOnServer(internalNetwork);   
	else
		acceptinConnectionsOnServer(extrenalNetwork);	
	printf("Done with fork\n");	
    return 0;
}