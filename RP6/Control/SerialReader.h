#ifndef SERIAL_READER_H
#define SERIAL_READER_H

int getIncomingSerialMessage(char* receiveBufferCommand, char* receiveBufferValue, const int sizeOfCommandBuffer, const int sizeOfValueBuffer);
// The receiveBufferLength is the maximum length of the buffer.
// 
//Pre: the recieveBuffer pointer is not NULL.
//Post: a message over serial read from '#' to '%' is stored in the receiveBuffer
//Return: -1 if there in no serial data to read, one of the char pointers is NULL or receiveBufferLength > 10.
//		   0 if '%' was received.

int waitForConnectRequest(char* receiveBufferCommand);
//
//Pre: -
//Post: The message that came from the wemos over serial is compared to the 
// 	    connect request from the protocol. If the message was the connect request.
//		a connect ACK is send to the wemos.
//Return: 0 if message was the connect reqeust from the wemos.	
//		 -1 if message wasn't the connect reqeust from the wemos.
#endif
