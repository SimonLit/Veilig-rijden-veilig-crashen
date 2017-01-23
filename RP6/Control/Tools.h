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
//Pre: -
//Post: valueToMap is mapped from range in_min to in_max, to out_min to out_max.
//Return: mapped value of valueToMap.

uint16_t mapPressureSensorValueToNewton(int pressureValue);
//
//Pre:-
//Post: map() is called to map pressureValue from 0-1023 to 0-20
//Return: pressureValue mapped.

int uint8_tToString(uint8_t value, char* string, unsigned int stringLength);
//
// Pre: stringLength at most the length of string.
// Post: value is converted to a string and put into string.
// Return: number of characters written into string.

int uint16_tToString(uint16_t value, char* string, unsigned int stringLength);
//
// Pre: stringLength at most the length of string.
// Post: value is converted to a string and put into string.
// Return: number of characters written into string.

#endif