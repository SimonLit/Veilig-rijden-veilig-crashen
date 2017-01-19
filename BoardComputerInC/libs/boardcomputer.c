#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "serial/sercom.h"
#include "handshake/handshake.h"
#include "serversocket/serverSocket.h"
#include "client/client.h"
#include "datastruct/datastruct.h"
#include "file_handeling/file_handeling.h"
#include "message/message.h"

#define NodeInternal "10.10.0.1"
#define ServiceInternal "5000"
#define NodeExternal "192.168.1.101"
int SerivecExternal  = 6000;

void networkFork(int fileadressInternal);
void mainFork(void);

int main(int argc, char const *argv[])
{
	writeToFile(carStatusFile, 2);
	removeFile(carCrashData);
	removeFile(phoneCrashFile);
	removeFile(phoneInsFile);
	if(access(DATALOG, F_OK) == 0)
	{
		remove(DATALOG);
	}
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
		int lenght = 0;
		DATAPACKET tempA, tempB;
		while(rv == -1)
		{
			rv = setupClientConnection(NodeExternal, SerivecExternal, &extrenalNetwork);
		}
		while(1)
		{
			sleep(1);	
			if(access(phoneCrashFile, F_OK) == 0)
			{
				if(access(carCrashData, F_OK) == 0)
				{
					//If exist make message with data car and phone and send, remove files car phone Crash and phone Ins
					memset(bufferToSend, 0, sizeof(bufferToSend));
					readDataStructFromFile(carCrashData, &tempA, 0);
					readDataStructFromFile(phoneCrashFile, &tempB, 0);
					messageCrashSend(bufferToSend, &tempA, &tempB, &lenght);
					printf("Crash buffer to send is %s\n", bufferToSend);
					sendDataOverConnection(extrenalNetwork, bufferToSend, lenght);
					lenght = 0;
					memset(bufferToSend, 0, sizeof(bufferToSend));
				}
				removeFile(phoneCrashFile);
				removeFile(carCrashData);
				if(access(phoneInsFile, F_OK) == 0)
				{
					removeFile(phoneInsFile);
				}
			}
			else if(access(phoneInsFile, F_OK) == 0)
			{
				//Make message and send , remove phoneIns file
				memset(bufferToSend, 0, sizeof(bufferToSend));
				readDataStructFromFile(phoneInsFile, &tempA, 0);
				messageInsSend(bufferToSend, &tempA, &lenght);
				printf("Insurance buffer to send is %s\n", bufferToSend);
				sendDataOverConnection(extrenalNetwork, bufferToSend, lenght);
				lenght = 0;
				memset(bufferToSend, 0, sizeof(bufferToSend));
				removeFile(phoneInsFile);
			}		
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