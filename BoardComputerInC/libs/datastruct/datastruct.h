#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#define maxLength 25
#define maxLengthMessage 100

typedef int bool;
enum 
{
	false,
	true
};

typedef enum
{
	RP6,
	PHONE,
	WEMOS
} SENDERS;

typedef struct
{
	int Day;
	int Month;
	int Year;
	int Hour;
	int Min;
	int Sec;
}TIMESTAMP;

typedef struct
{
	SENDERS Sender;	//Who
	int  sockFd;	//Socket file discriptor
	int  senderId; 	//Sender id number together with Sender form id system
	char senderIpAdress[maxLength];	//Ip adress from sender
	char messageReveived[maxLengthMessage]; //Total message received
	char messageReveivedDataToSendOnward[maxLengthMessage]; //Data received that needs to be send onward
	char destinationIp[maxLength]; //Ip for data that needs to be send onward
	bool dataSendOnward; //Boolean to tell easy if something needs to be send or not
	bool connectionVerifiedACK; //If connection already did the handshake with id and everything
	int  countMessages;	//Keeps track of the amount of messages
	int  totalSizeMessages; //Keeps track of size, good for analytics
	TIMESTAMP time;
} DATAPACKET;

#endif