#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_


#define maxLength 25
#define maxLengthMessage 100

typedef struct
{
	char senderName[maxLength]
	char ipAdress[maxLength]
	char message[maxLengthMessage]
	char destinationIp[maxLength]
	sockaddr snederInformation 
} DATAPACKET;


#endif