#ifndef SERIAL_READER_H
#define SERIAL_READER_H

int getIncomingSerialMessage(char* receiveBufferCommand, char* receiveBufferValue);
// The receiveBufferLength is the maximum length of the buffer.
// 
//Pre: the recieveBuffer pointer is not NULL.
//Post: a message over serial read from '#' to '@' is stored in the receiveBuffer
//Return: -1 if there in no serial data to read, one of the char pointers is NULL or receiveBufferLength > 10.
//		   0 if '@' was received.

int sendMessage(char* command);
//
// Pre: makeProtocolMessage() is defined and implemented.
// Post: command is send over serial.
// Return: 0 on succes
//        -1 if command is NULL.

int sendMessageWithValue(char* command, char* value);
//
// Pre: makeProtocolMessageWithValue() is defined and implemented
// Post: command with value is send over serial.
// Return: 0 on succes
//        -1 if command or value is NULL.

int timeoutHandler(void);
//
// Pre: MAX_COMMAND_LENGTH, MAX_VALUE_LENGTH, MAX_NACK_COUNTER, MAX_HEARTBEAT_TIMEOUT and protocolMessageToSend are defined and Stopwatch5 is started.
// Post: The program waits for an ACK. If ACK is received 0 is returned. If NACK is received the protocolMessageToSend is send again.
//       If the amount of NACK's received is greater than or equal to MAX_NACK_COUNTER -1 is returned. If Stopwatch5 is greater than or equal to 
//       MAX_HEARTBEAT_TIMEOUT -1 is returned. While there is waited for an ACK there is also checked for the heartbeat.

#endif
