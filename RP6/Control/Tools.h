#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>

extern char protocolMessageToSend[20]; // The string that is used in makeProtocolMessage()

int makeProtocolMessage(char* message);
//
//Pre: A char* protocolMessageToSend exists.
//Post: protocolMessageToSend has the value of "START_CHARACTER<message>END_CHARACTER". 
//Return: -1 if message is NULL or the new message doesn't fit in the character array.
//		   0 On succes.

int makeProtocolMessageWithValue(char* message, char* value);
//
//Pre: A char* protocolMessageToSend exists.
//Post: protocolMessageToSend has the value of "START_CHARACTER<message>VALUE_CHARACTER<value>END_CHARACTER". 
//Return: -1 if message or value is NULL or the new message doesn't fit in the character array.
//		   0 On succes.

int16_t map(int16_t valueToMap, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);
//
//Pre: 
//Post: 
//Return:

uint16_t mapPressureSensorValueToNewton(int pressureValue);
//
//Pre: 
//Post: 
//Return:

#endif