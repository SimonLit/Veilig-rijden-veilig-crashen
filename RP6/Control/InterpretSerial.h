#ifndef INTERPRET_SERIAL_H
#define INTERPRET_SERIAL_H

#include <stdint.h>


int indexOf(char* array, char value, const int sizeOfArray);
//
//Pre: -
//Post: The index of the value charactecter is determined.
//Return: -1 if array is NULL or sizeOfArray < 0.
//		   On succes the index of value is returned.

int interpretMessageForSpeedValues(char* receiveBufferCommand, char* receiveBufferValue, int* baseSpeed, uint8_t* rightSpeed, uint8_t* leftSpeed);
// The receivedMessageLength is the maximum length of the buffer.
//
//Pre: the receivedMessage, baseSpeed, rightSpeed and leftSpeed pointer is not NULL.
//Post: the new received baseSpeed, rightSpeed and leftSpeed are stored in the speed pointers.
// 		these values must be checked for negative values in order to set the tire direction (FWD, BWD).
//Return: -1 if one of the pointers is NULL, the the message wasn't one from the protocol or 
//			receivedMessageLength was greater than the buffer (=10).
//		   0 on succes. 
//		   1 NACK is recieved.

int waitForConnectRequest(char* receiveBufferCommand, char* receiveBufferValue);
//
//Pre: -
//Post: The message that came from the wemos over serial is compared to the 
// 	    connect request from the protocol. If the message was the connect request.
//		a connect ACK is send to the wemos.
//Return: 0 if message was the connect reqeust from the wemos.	
//		 -1 if message wasn't the connect reqeust from the wemos.

int checkForHeartbeat(char* receiveBufferCommand);
//
// Pre: -
// Post: If receiveBufferCommand was the heartbeat request from the wemos
//       ACK is send back to the wemos.
// Return: -1 if receiveBufferCommand is NULL or wasn't a heartbeat request.
//			0 on succes.

int checkForRP6StateChange(char* receiveBufferCommand);
//
// Pre: -
// Post:
// Return:

int checkForACK(char* receiveBufferCommand);

int checkForNACK(char* receiveBufferCommand);

#endif