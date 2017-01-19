#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#define maxLength 25
#define maxLengthMessage 255

#define DATALOG "logfile"
#define DATASEND "sendfile"

typedef int bool;
enum 
{
	false,
	true
};

bool driving;
bool crashed;

typedef enum
{
	NOBODY,
	CAR,
	PHONE,
} SENDER;

typedef enum
{
	CRASHDATA,
	RP6STATUS,
	GSMSTATUSREQUEST,
	DRIVING
} RESPONSES;

typedef struct 
{
	int speed;
	int side_hit;
	int impact;
	int distance_driven;
	int orientation_ypr;
} DATCRASH;

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
	char infoSend[maxLengthMessage];
	RESPONSES action; //The action that should be done with the received datas
	bool sf; 
	TIMESTAMP time;
} DATAPACKET;


#endif