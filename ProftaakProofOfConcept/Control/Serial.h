#ifndef SERIAL_H
#define SERIAL_H

#include "RP6uart.h" 
#include "stdint.h"
#include <string.h>

int getRCProtocolValuesToDrive(char* receiveBufferCommand, char* receiveBufferValue, const int receiveCommandBufferLength, const int receiveValueBufferLength);
// The receiveBufferLength is the maximum length of the buffer.
// 
//Pre: the recieveBuffer pointer is not NULL.
//Post: a message over serial read from '#' to '%' is stored in the receiveBuffer
//Return: -1 if there in no serial data to read, one of the char pointers is NULL or receiveBufferLength > 10.
//		   0 if '%' was received.

int interpretMessage(char* receivedCommand, char* receivedValue, const int receiveCommandBufferLength, const int receiveValueBufferLength, int* baseSpeed, uint8_t* rightSpeed, uint8_t* leftSpeed);
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
			

#endif
