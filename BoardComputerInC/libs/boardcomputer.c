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
		int position = 0;
		int currentSizeFile = 0;
		int lastKnowSizeOfFile = 0;
		int lenght = 0;
		DATAPACKET toSend;
		while(rv == -1)
		{
			rv = setupClientConnection(NodeExternal, SerivecExternal, &extrenalNetwork);
		}
		while(1)
		{
			sleep(1);	
			//Read if file exist with data of phone crash data
			//If exist make message with data car and phone and send, remove files car phone Crash and phone Ins
			

			//IF Read if file exist with data of stopPhone
			//Make message and send , remove phoneIns file




/*
			memset(bufferToSend, 0, sizeof(bufferToSend));
			currentSizeFile = getNrOfDatStructs(DATASEND);
			printf("Size of file is %d\n", currentSizeFile);
			for(int i = 0; i < (currentSizeFile - lastKnowSizeOfFile); i++)
			{
				printf("Loop number %d\n", i);
				printf("Dat before reading %s\n", toSend.messageReceived);
				readDataStructFromFile(DATASEND, &toSend, position);
				printf("Data to send is %s\n", toSend.messageReceived);
				makeMessageToSend(toSend.messageReceived, &toSend, &lenght);
				printf("Message to send is %s\n", toSend.infoSend);
				strcpy(bufferToSend, toSend.infoSend);
				rv = sendDataOverConnection(extrenalNetwork, bufferToSend, lenght);//Send to C# app	
				position++;
				memset(toSend.infoSend, 0, maxLengthMessage);
				memset(toSend.messageReceived, 0, maxLengthMessage);
			}
			lastKnowSizeOfFile = currentSizeFile;
*/		}
	}
}

void mainFork(void)
{
	while(1)
	{
		serialCommunicatie();//Reads out buffer and (respons to do)		
	}
}