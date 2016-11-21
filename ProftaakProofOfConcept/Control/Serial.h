#ifndef SERIAL_H
#define SERIAL_H

#include "RP6uart.h" 
#include "stdint.h"
#include "string.h"

int getRCProtocolValuesToDrive(char* receiveBuffer, int recieveBufferLength);
//
//Pre: the recieveBuffer pointer is not NULL.
//Post: a message over serial read from '#' to '%' is stored in the receiveBuffer
//Return: -1 if the recieveBuffer is full, recieve buffer was a NULL pointer or there are no serial messages. 
//		   0 if a character was read that was '#', '%' or something after '#' and before '%'.

int interpretMessage(char* receivedMessage, const int receivedMessageLength, int *baseSpeed, int* rightSpeed, int* leftSpeed);
//
//Pre: the receivedMessage, baseSpeed, rightSpeed and leftSpeed pointer is not NULL.
//Post: the new received baseSpeed, rightSpeed and leftSpeed are stored in the speed pointers.
// 		these values must be checked for negative values in order to set the tire direction (FWD, BWD)
//		and be multiplied by two to get the right values for the RP6s.
//Return: -1 if one of the pointers is NULL or the the message wasn't one from the protocol.
//		   0 on succes. 
			

#endif
