#ifndef SERIAL_H
#define SERIAL_H

#include "stdint.h"

extern char receiveBufferCommand[20];
extern char receiveBufferValue[20];
extern char protocolMessageToSend[20];

int indexOf(char* array, char value, const int sizeOfArray);
//
//Pre:
//Post:
//Return:

void makeProtocolMessage(char* message);
//
//Pre:
//Post:
//Return:

void makeProtocolMessageWithValue(char* message, char* value);
//
//Pre:
//Post:
//Return:

int getIncomingSerialMessage(void);
/*char* receiveBufferCommand, char* receiveBufferValue, const int receiveCommandBufferLength, const int receiveValueBufferLength*/
// The receiveBufferLength is the maximum length of the buffer.
// 
//Pre: the recieveBuffer pointer is not NULL.
//Post: a message over serial read from '#' to '%' is stored in the receiveBuffer
//Return: -1 if there in no serial data to read, one of the char pointers is NULL or receiveBufferLength > 10.
//		   0 if '%' was received.

int interpretMessageForSpeedValues(int* baseSpeed, uint8_t* rightSpeed, uint8_t* leftSpeed);
/*har* receivedCommand, char* receivedValue, 
					const int receiveCommandBufferLength, const int receiveValueBufferLength,*/
// The receivedMessageLength is the maximum length of the buffer.
//
//Pre: the receivedMessage, baseSpeed, rightSpeed and leftSpeed pointer is not NULL.
//Post: the new received baseSpeed, rightSpeed and leftSpeed are stored in the speed pointers.
// 		these values must be checked for negative values in order to set the tire direction (FWD, BWD)
//		and be multiplied by two to get the right values for the RP6s.
//Return: -1 if one of the pointers is NULL, the the message wasn't one from the protocol or 
//			receivedMessageLength was greater than the buffer (=10).
//		   0 on succes. 
//		   1 NACK is recieved.

int waitForConnectRequest(void);
//
//Pre: -
//Post: The message that came from the wemos over serial is compared to the 
// 	    connect request from the protocol. If the message was the connect request.
//		a connect ACK is send to the wemos.
//Return: 0 if message was the connect reqeust from the wemos.	
//		 -1 if message wasn't the connect reqeust from the wemos.
#endif
