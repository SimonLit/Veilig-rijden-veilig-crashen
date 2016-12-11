#include "Serial.h"
#include "RP6uart.h" 
#include <string.h>

// ================================================================
// ===           GENERAL SERIAL COMMUNICATION PROTOCOL          ===
// ================================================================
#define START_CHARACTER '#'
#define END_CHARACTER '@'
#define VALUE_CHARACTER ':'
#define MULTI_VALUE_SEPARATOR ','
// ================================================================
// ===            SERIAL COMMUNICATION RP6 PROTOCOL             ===
// ================================================================
#define CONNECT_TO_DEVICE_RECEIVE "CONNECT"
#define CONNECTED_ACK "CONNECTED"
#define RP6_STARTED_PROGRAM "START_RP6"
#define RP6_STOPPED_PROGRAM "STOP_RP6"
#define SPEED_PROTOCOL_SEND "SPEED"
#define SIDE_HIT_PROTOCOL_SEND_RECEIVE "SIDE_HIT"
#define CONTROLLER_DISCONNECTED "CTRL_DISCONNECTED"
#define CONTROLLER_CONNECTED "CTRL_CONNECTED"
#define IMPACT_PROTOCOL_SEND_RECEIVE "IMPACT"
#define DIST_DRIVEN_PROTOCOL_SEND_RECEIVE "DIST_DRIVEN"
#define ORIENTATION_PROTOCOL_SEND "ORIENTATION_YPR"
#define ORIENTATION_PROTOCOL_RECEIVE "ORIENTATION"
#define HEARTBEAT_RP6 "HEARTBEAT"
#define CONTROLLER_VALUES "CONTROLLER_VALUES"
// ================================================================
// ===               GENERAL COMMUNICATION PROTOCOL             ===
// ================================================================
#define GENERAL_ACK "ACK"
#define GENERAL_NACK "NACK"
#define RP6_NAME "RP6"
#define WEMOS_NAME "WEMOS"
#define WEMOS_NUMBER 1
// ================================================================

char receiveBufferCommand[20];
char receiveBufferValue[20];
const int sizeOfCommandBuffer = sizeof(receiveBufferCommand);
const int sizeOfValueBuffer = sizeof(receiveBufferValue);

char protocolMessageToSend[20];

int START_READING_COMMAND = 0;
int START_READING_VALUE = 0;
int STOP_READING = 0;

int indexOf(char* array, char value, const int sizeOfArray)
{
	if(array == NULL)
	{
		return -1;	
	}
	
	int index = 0;
	while(index < sizeOfArray && array[index] != value) index++;
	return ((index == sizeOfArray) ? -1 : index);
}

void makeProtocolMessage(char* message)
{
	strcat(protocolMessageToSend, START_CHARACTER);
	strcat(protocolMessageToSend, message);
	strcat(protocolMessageToSend, END_CHARACTER);
}

void makeProtocolMessageWithValue(char* message, char* value)
{
	strcat(protocolMessageToSend, START_CHARACTER);
	strcat(protocolMessageToSend, message);
	strcat(protocolMessageToSend, VALUE_CHARACTER);
	strcat(protocolMessageToSend, value);
	strcat(protocolMessageToSend, END_CHARACTER);
}

int getIncomingSerialMessage(void)
{/*char* receiveBufferCommand, char* receiveBufferValue, const int receiveCommandBufferLength, const int receiveValueBufferLength*/

	/*if(receiveBufferCommand == NULL || receiveBufferValue == NULL)
	{
		return -1;
	}*/
	
	char receivedChar;
	uint8_t nrOfCharsReceived = getBufferLength();
	
	// check if no data was received
	if (nrOfCharsReceived == 0) return -1;
	
	char storeReceiveBufferCommand[sizeOfCommandBuffer];
	char storeReceiveBufferValue[sizeOfValueBuffer];
	
	int commandWriteIndex = 0;
	int valueWriteIndex = 0;

	while(getBufferLength() > 0)
	{
		if(commandWriteIndex < sizeOfCommandBuffer && valueWriteIndex < sizeOfValueBuffer)
		{
			receivedChar = readChar(); // Char read from the buffer.

			// Was the last read character in the buffer a '@'? 
			// If yes then stop reading and interpret the message/act on the message.
			if(receivedChar == END_CHARACTER)
			{
				START_READING_COMMAND = 0;
				START_READING_VALUE = 0;
				STOP_READING = 1;
				
				// Coppy the received message to the command and value char*.
				strcpy(receiveBufferCommand, storeReceiveBufferCommand);
				strcpy(receiveBufferValue, storeReceiveBufferValue);

				return 0;
			}

			// Is the boolean START_READING_VALUE set to true?. (was ':' the last received character).
			if(START_READING_VALUE)
			{
				storeReceiveBufferValue[valueWriteIndex] = receivedChar;
				valueWriteIndex++;
			}

			// Was the last read character in the buffer a ':'? 
			// If yes then set the boolean START_READING_VALUE to true. This means the value array will start filling.
			// The value can be a digit with a maximum of 3 digits. Max value is 999. 
			if(receivedChar == VALUE_CHARACTER)
			{
				START_READING_COMMAND = 0;
				START_READING_VALUE = 1;
				STOP_READING = 0;
			}

			// Is the boolean START_READING_COMMAND set to true?. (was '#' the last received character).
			if(START_READING_COMMAND)
			{				
				storeReceiveBufferCommand[commandWriteIndex] = receivedChar;
				commandWriteIndex++;
			}

			// Was the last read character in the buffer a '#'? 
			// If yes then set the boolean START_READING_COMMAND to true. This means the command array will start filling.
			// Also clear all the arrays to be sure only the currend command is used while interpreting.
			if(receivedChar == START_CHARACTER)
			{
				START_READING_COMMAND = 1;
				START_READING_VALUE = 0;
				STOP_READING = 0;
				
				commandWriteIndex = 0;
				valueWriteIndex = 0;

				// Make sure the temporery command and value strings are clean.
				// Otherwise string could get mixesd with each other.
				memset(storeReceiveBufferCommand, 0, sizeOfCommandBuffer);
				memset(storeReceiveBufferValue, 0, sizeOfValueBuffer);
			}
		}
		else
		{
			return -1;
		}
	}

	return -1;
}

int interpretMessageForSpeedValues(int* baseSpeed, uint8_t* rightSpeed, uint8_t* leftSpeed)
{/*har* receivedCommand, char* receivedValue, 
					const int receiveCommandBufferLength, const int receiveValueBufferLength,*/
	if(baseSpeed == NULL || rightSpeed == NULL || leftSpeed == NULL)
	{
		return -1;
	}

	int indexOfValueSeparator = indexOf(receiveBufferValue, MULTI_VALUE_SEPARATOR, sizeOfValueBuffer);

	// Copy the first value of the received value to the speedValueString and add a null terminator.
	char* speedValueString = strncpy(speedValueString, receiveBufferValue, indexOfValueSeparator+1);
	speedValueString[indexOfValueSeparator+2] = '\0';

	// Shift the whole receiveBufferValue to the left to get the steer value of received value. 
	char* steerValueString = NULL;
	for(int i = 0; i < indexOfValueSeparator+1; i++)
	{
		for(int k = 0; k < sizeOfValueBuffer; k++)
		{
			steerValueString[k] = receiveBufferValue[k+1];
		}
	}

	int speedValue = atoi(speedValueString);
	uint8_t steerValue = atoi(steerValueString);
	// Convert the value char array to an int.
 	
	if(strcmp(receiveBufferCommand, CONTROLLER_VALUES) == 0)
	{	
		*baseSpeed = speedValue;

		int baseSpeedToUse = *baseSpeed;
	
		if(baseSpeedToUse < 0)
		{
			baseSpeedToUse = baseSpeedToUse * -1;
		}
		
		int relativeValueOfValueFromBaseSpeed = baseSpeedToUse*steerValue/100;
		
		if(baseSpeedToUse == 0)
		{
			if(steerValue < 0)
			{
				*rightSpeed = steerValue * -1;
			}
			else if ( steerValue > 0)
			{
				*leftSpeed = steerValue;
			}
			else
			{
			 	*rightSpeed	= 0;
			 	*leftSpeed = 0;
			}
		}
		else
		{
			//First divide the given base value by two to be able to 
			//calculte the new left and right speeds in the desired range.
			//
			//Then calculate the percentage of the current base speed to 
			//calculate the new left and right speed.
			if(steerValue > 0)
			{
				*rightSpeed = baseSpeedToUse - relativeValueOfValueFromBaseSpeed;
				*leftSpeed =  baseSpeedToUse;
			}
			else if (steerValue < 0)
			{
				*rightSpeed = baseSpeedToUse;
				*leftSpeed =  baseSpeedToUse + relativeValueOfValueFromBaseSpeed;
			}
			else
			{
				*rightSpeed = baseSpeedToUse;
				*leftSpeed = baseSpeedToUse;
			}
		}

		// Clear the buffers to make sure the you are working with a clean buffer.
		memset(storeReceiveBufferCommand, 0, sizeOfCommandBuffer);
		memset(storeReceiveBufferValue, 0, sizeOfValueBuffer);

		return 0;
	}
	else
	{	
		return -1;
	}
}

int waitForConnectRequest(void)
{
	if(strcmp(receiveBufferCommand, CONNECT_TO_DEVICE_RECEIVE) == 0)
	{
		makeProtocolMessageWithValue(CONNECTED_ACK, RP6_NAME);
		writeString(protocolMessageToSend);
		memset(protocolMessageToSend, 0, sizeof(protocolMessageToSend));

		return 0;
	}

	return -1;
}