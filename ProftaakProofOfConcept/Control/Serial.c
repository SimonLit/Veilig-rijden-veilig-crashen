#include "Serial.h"
#include <stdint.h>

#define CONTROLLER_RECEIVE_LEFT_RIGHT "x"
#define CONTROLLER_RECEIVE_SPEED "SPEED"

int writeBufferIndex = 0;
int startReading = 0;

int getRCProtocolValuesToDrive(char* receiveBuffer, int recieveBufferLength)
{
	if(receiveBuffer == NULL)
	{
		return -1;
	}
	
	char receivedChar;
	
	if(getBufferLength() > 0)
	{
		if(writeBufferIndex > recieveBufferLength)
		{
			//Reset the write index so that the next time 
			//there can be written in the receive buffer.
			writeBufferIndex = 0;
			return -1;
		}
		
		receivedChar = readChar();
		
		if(startReading)
		{
			receiveBuffer[writeBufferIndex] = receivedChar;
		}
		
		if(receivedChar == '%')
		{
			startReading = 0;
			writeBufferIndex = 0;
			return 0;
		}
		
		if(receivedChar == '#')
		{
			startReading = 1;
			return 0;
		}
		
	}
	
	return -1;
}

int interpretMessage(char* receivedMessage, const int receivedMessageLength, 
					int *baseSpeed, int* rightSpeed, int* leftSpeed)
{	
	if(receivedMessage == NULL || baseSpeed == NULL
		 || rightSpeed == NULL || leftSpeed == NULL)
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
			if(receivedMessage[i] == ':')
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
			if(receivedMessage[i] == '%')
			{
				value = atoi(valueFromBuffer);
				break;
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
		*baseSpeed = value;
		return 0;
	}
	else
	{
		return -1;
	}
}
