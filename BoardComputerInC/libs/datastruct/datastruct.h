#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#define maxLength 25
#define maxLengthMessage 100

#define DATALOG "logfile"
#define DATASEND "sendfile"

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
} SENDER;

typedef enum
{
	CRASHDATA
	RP6STATUS
	GSMSTATUSREQUEST
} RESPONSES;

typedef struct
{
	int Day;
	int Month;
	int Year;
	int Hour;
	int Min;
	int Sec;
}TIMESTAMP;

typedef struct datapacket
{
	SENDER Sender;	//Who
	int  sockFd;	//Socket file discriptor
	char senderIpAdress[maxLength];	//Ip adress from sender
	char messageReceived[maxLengthMessage]; //Full message received
	char informationReceived[maxLengthMessage];
	RESPONSES action; //The action that should be done with the received data
	TIMESTAMP time;
} DATAPACKET;

#endif