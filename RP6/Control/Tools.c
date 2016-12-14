#include "Tools.h"
#include <string.h>
#include "ProtocolDefines.h"

char protocolMessageToSend[20];

int makeProtocolMessage(char* message)
{
	if(message == NULL) {return -1;}

	// Check if the message fits into protocolMessageToSend.
	// The +1 is for the '\0'.
	if((strlen((char*)START_CHARACTER) + strlen(message) + strlen((char*)END_CHARACTER))+1 > sizeof(protocolMessageToSend)) {return -1;}

	memset(protocolMessageToSend, 0, sizeof(protocolMessageToSend));

	strcat(protocolMessageToSend, START_CHARACTER);
	strcat(protocolMessageToSend, message);
	strcat(protocolMessageToSend, END_CHARACTER);

	return 0;
}

int makeProtocolMessageWithValue(char* message, char* value)
{
	if(message == NULL || value == NULL) {return -1;}

	// Check if the message fits into protocolMessageToSend.
	// The +1 is for the '\0'.
	if((strlen((char*)START_CHARACTER) + strlen(message) + strlen((char*)VALUE_CHARACTER) + strlen(value) + strlen((char*)END_CHARACTER))+1
		> sizeof(protocolMessageToSend)) {return -1;}

	memset(protocolMessageToSend, 0, sizeof(protocolMessageToSend));

	strcat(protocolMessageToSend, START_CHARACTER);
	strcat(protocolMessageToSend, message);
	strcat(protocolMessageToSend, VALUE_CHARACTER);
	strcat(protocolMessageToSend, value);
	strcat(protocolMessageToSend, END_CHARACTER);

	return 0;
}

int16_t map(int16_t valueToMap, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
	return (valueToMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t mapPressureSensorValueToNewton(int pressureValue)
{
	// The sensitivity actualy ranges from 0.2 to 20 instead of 0 - 20.
	// But because this is such a small difference it is much more convenient
	// To avoid the use of decimal numbers. 
	return map(pressureValue, 0, 1023, 0, 20); 
}