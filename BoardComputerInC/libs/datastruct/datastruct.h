#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#define maxLength 25
#define maxLengthMessage 200

#define DATALOG "logfile.bin"
#define carCrashData "carCrashData.bin"
#define carStatusFile "carStatusFile.bin"
#define phoneCrashFile "phoneCrashFile.bin"
#define phoneInsFile "phoneInsFile.bin"

typedef int bool;
enum 
{
	false,
	true
};

typedef enum
{
	NOBODY,
	CAR,
	PHONE,
} SENDER;

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
	char crahsPhoneData[maxLengthMessage];
	char stopPhoneData[maxLengthMessage];
	bool sf; 
} DATAPACKET;


#endif