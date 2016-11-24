#include "Serial.h"

#define CONTROLLER_RECEIVE_LEFT_RIGHT "x"
#define CONTROLLER_RECEIVE_SPEED "SPEED"
#define PROTOCOL_START_CHARACTER '#'
#define PROTOCOL_END_CHARACTER '%'
#define PROTOCOL_VALUE_CHARACTER ':'


int writeBufferIndex = 0;
int startReading = 0;

int getRCProtocolValuesToDrive(char* receiveBuffer, const int receiveBufferLength)
{
	if(receiveBuffer == NULL || receiveBufferLength > 10)
	{
		return -1;
	}
	
	char receivedChar;
	
	if(getBufferLength() > 0)
	{
		if(writeBufferIndex > receiveBufferLength)
		{
			//Reset the write index so that the next time 
			//there can be written in the receive buffer.
			writeBufferIndex = 0;
			return -1;
		}
		
		receivedChar = readChar();
		
		if(startReading)
		{
			receiveBuffer[writeBufferIndex++] = receivedChar;
		}
		
		if(receivedChar == PROTOCOL_END_CHARACTER)
		{
			startReading = 0;
			writeBufferIndex = 0;
			return 0;
		}
		
		if(receivedChar == PROTOCOL_START_CHARACTER)
		{
			startReading = 1;
			return 0;
		}
		
	}
	
	return -1;
}

int interpretMessage(char* receivedMessage, const int receivedMessageLength, 
					int* baseSpeed, int* rightSpeed, int* leftSpeed)
{	
	if(receivedMessage == NULL || baseSpeed == NULL
		 || rightSpeed == NULL || leftSpeed == NULL
		 || receivedMessageLength > 10)
	{
		return -1;
	}
	
	char commandFromBuffer[receivedMessageLength];
	char valueFromBuffer[receivedMessageLength];
	int value = 0;
	
	int readMode = 0;
	
	for (int i = 0; i < receivedMessageLength; i++)
	{
		if(!readMode)
		{
			if(receivedMessage[i] == PROTOCOL_VALUE_CHARACTER)
			{
				readMode = 1;
			}
			else
			{
				commandFromBuffer[i] = receivedMessage[i];
			}
		}
		else
		{
			if(receivedMessage[i] == PROTOCOL_END_CHARACTER)
			{
				// Convert the received value to an int.
				value = atoi(valueFromBuffer);

				clearLCD();
				setCursorPosLCD(0,0);
				writeStringLCD(commandFromBuffer);
				setCursorPosLCD(1,0);
				writeStringLCD(valueFromBuffer);

				writeString("#");
				writeString(commandFromBuffer);
				writeString("%\n");
				//break;
			}
			else
			{
				valueFromBuffer[i] = receivedMessage[i];
			}
		}
 	}
 	
	if(strcmp(commandFromBuffer, CONTROLLER_RECEIVE_LEFT_RIGHT) == 0)
	{		
		if(*baseSpeed == 0)
		{
			*rightSpeed = value * -1;
			*leftSpeed = value;
			return 0;
		}
		else
		{
			//First divide the given base value by two to be able to 
			//calculte the new left and right speeds in the desired range.
			//
			//Then calculate the percentage of the current base speed to 
			//calculate the new left and right speed.
			*rightSpeed = ((*baseSpeed)/2) - ((*baseSpeed) * (value/100));
			*leftSpeed = ((*baseSpeed)/2) + ((*baseSpeed) * (value/100));
			return 0;
		}
	}
	else if (strcmp(commandFromBuffer, CONTROLLER_RECEIVE_SPEED) == 0)
	{
		int valueToUse = value;

		*baseSpeed = valueToUse;

		if(*baseSpeed < 0)
		{
			valueToUse = value * -1;
		}

		*rightSpeed = valueToUse;
		*leftSpeed = valueToUse;
		return 0;
	}
	else
	{
		return -1;
	}
}
