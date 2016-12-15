#include "InterpretSerial.h"
#include <string.h>
#include <stdlib.h>
#include "Tools.h"
#include "ProtocolDefines.h"

int indexOf(char* array, char value, const int sizeOfArray)
{
	if(array == NULL || sizeOfArray < 1) {return -1;}
	
	int index = 0;
	while(index < sizeOfArray && array[index] != value) {index++;}
	return ((index == sizeOfArray) ? -1 : index);
}

int interpretMessageForSpeedValues(char* receiveBufferCommand, char* receiveBufferValue, int* baseSpeed, uint8_t* rightSpeed, uint8_t* leftSpeed)
{
	if(receiveBufferCommand == NULL || receiveBufferValue == NULL || baseSpeed == NULL || rightSpeed == NULL || leftSpeed == NULL)
	{
		return -1;
	}

	int indexOfValueSeparator = indexOf(receiveBufferValue, *MULTI_VALUE_SEPARATOR, MAX_VALUE_LENGTH);

	// Copy the first value of the received value to the speedValueString and add a null terminator.
	char speedValueString[5];
	strncpy(speedValueString, receiveBufferValue, indexOfValueSeparator);
	speedValueString[indexOfValueSeparator] = '\0';

	// Shift the whole receiveBufferValue to the left to get the steer value of received value. 
	char steerValueString[5];
	int i = 0;
	while(i < 5 && receiveBufferValue[i] != '\0')
	{
		steerValueString[i] = receiveBufferValue[(indexOfValueSeparator+1)+i];
		i++;
	}

	// Convert the value char array to an int.
	int speedValue = atoi(speedValueString);
	int steerValue = atoi(steerValueString);

	if(speedValue > 150 || speedValue < -150 || steerValue > 100 || steerValue < -100)
	{
		// SEND A NACK OR SOMETHING.
	}

	if(strcmp(receiveBufferCommand, CONTROLLER_VALUES) == 0)
	{	
		*baseSpeed = speedValue;

		int baseSpeedToUse = *baseSpeed;
	
		if(baseSpeedToUse < 0)
		{
			baseSpeedToUse = baseSpeedToUse * -1;
		}
		
		// Calculate how much the speed has to change relatice to the base speed.
		uint8_t relativeValueOfValueFromBaseSpeed = baseSpeedToUse*steerValue/100;
		
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

		return 0;
	}
	else
	{	
		return -1;
	}
}

int waitForConnectRequest(char* receiveBufferCommand, char* receiveBufferValue)
{
	return ((strcmp(receiveBufferCommand, CONNECT_TO_DEVICE_RECEIVE) == 0 && strcmp(receiveBufferValue, WEMOS_NAME) == 0) ? 0 : -1);
}

int checkForHeartbeat(char* receiveBufferCommand)
{
	return ((strcmp(receiveBufferCommand, HEARTBEAT_RP6) == 0) ? 0 : -1);
}

int checkForRP6StateChange(char* receiveBufferCommand)
{
	if((strcmp(receiveBufferCommand, RP6_STARTED_PROGRAM) == 0))
	{
		return 1;
	}
	else if((strcmp(receiveBufferCommand, RP6_STOPPED_PROGRAM) == 0))
	{
		return 0;
	}
	else 
	{
		return -1;
	}
}