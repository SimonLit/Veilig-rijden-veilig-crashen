#include "Serial.h"

#define CONTROLLER_RECEIVE_LEFT_RIGHT "STEER"
#define CONTROLLER_RECEIVE_SPEED "SPEED"
#define PROTOCOL_START_CHARACTER '#'
#define PROTOCOL_END_CHARACTER '%'
#define PROTOCOL_VALUE_CHARACTER ':'

int START_READING_COMMAND = 0;
int START_READING_VALUE = 0;
int STOP_READING = 0;

int getRCProtocolValuesToDrive(char* receiveBufferCommand, char* receiveBufferValue, const int receiveCommandBufferLength, const int receiveValueBufferLength)
{

	if(receiveBufferCommand == NULL || receiveBufferValue == NULL || receiveCommandBufferLength > 6 || receiveValueBufferLength > 5)
	{
		return -1;
	}
	
	char receivedChar;
	uint8_t nrOfCharsReceived = getBufferLength();
	
	// check if no data was received
	if (nrOfCharsReceived == 0) return -1;
	
	char storeReceiveBufferCommand[receiveCommandBufferLength];
	char storeReceiveBufferValue[receiveValueBufferLength];
	
	int commandWriteIndex = 0;
	int valueWriteIndex = 0;

	while(getBufferLength() > 0)
	{
		if(commandWriteIndex < receiveCommandBufferLength && valueWriteIndex < receiveValueBufferLength)
		{
			receivedChar = readChar(); // Char read from the buffer.

			// Was the last read character in the buffer a '%'? 
			// If yes then stop reading and interpret the message/act on the message.
			if(receivedChar == PROTOCOL_END_CHARACTER)
			{
				writeString("Stop reading\n");
				START_READING_COMMAND = 0;
				START_READING_VALUE = 0;
				STOP_READING = 1;
				
				strncpy(receiveBufferCommand, storeReceiveBufferCommand, receiveCommandBufferLength);
				strncpy(receiveBufferValue, storeReceiveBufferValue, receiveValueBufferLength);
			
				return 0;
			}

			// Is the boolean START_READING_VALUE set to true?. (was ':' the last received character).
			if(START_READING_VALUE)
			{
				writeString("Writing value\n");
				writeChar(receivedChar);
				writeString("\n");
				
				storeReceiveBufferValue[valueWriteIndex] = receivedChar;
				
				valueWriteIndex++;
			}

			// Was the last read character in the buffer a ':'? 
			// If yes then set the boolean START_READING_VALUE to true. This means the value array will start filling.
			// The value can be a digit with a maximum of 3 digits. Max value is 999. 
			if(receivedChar == PROTOCOL_VALUE_CHARACTER)
			{
				writeString("Start reading value\n");
				START_READING_COMMAND = 0;
				START_READING_VALUE = 1;
				STOP_READING = 0;
			}

			// Is the boolean START_READING_COMMAND set to true?. (was '#' the last received character).
			if(START_READING_COMMAND)
			{
				writeString("Writing command\n");
				writeChar(receivedChar);
				writeString("\n");
				
				storeReceiveBufferCommand[commandWriteIndex] = receivedChar;
				
				commandWriteIndex++;
			}

			// Was the last read character in the buffer a '#'? 
			// If yes then set the boolean START_READING_COMMAND to true. This means the command array will start filling.
			// Also clear all the arrays to be sure only the currend command is used while interpreting.
			if(receivedChar == PROTOCOL_START_CHARACTER)
			{
				writeString("Start reading command\n");
				START_READING_COMMAND = 1;
				START_READING_VALUE = 0;
				STOP_READING = 0;
				
				commandWriteIndex = 0;
				valueWriteIndex = 0;

				memset(storeReceiveBufferCommand, 0, receiveCommandBufferLength);
				memset(storeReceiveBufferValue, 0, receiveValueBufferLength);
			}
		}
		else
		{
			return -1;
		}
	}

	return 0;
}

int interpretMessage(char* receivedCommand, char* receivedValue, 
					const int receiveCommandBufferLength, const int receiveValueBufferLength,
					int* baseSpeed, uint8_t* rightSpeed, uint8_t* leftSpeed)
{	
	if(receivedCommand == NULL || receivedValue == NULL
		|| baseSpeed == NULL || rightSpeed == NULL || leftSpeed == NULL)
	{
		return -1;
	}

	// Convert the value char array to an int.
	int value = atoi(receivedValue);
 	
	if(strcmp(receivedCommand, CONTROLLER_RECEIVE_LEFT_RIGHT) == 0)
	{		
		int baseSpeedToUse = *baseSpeed;
	
		if(baseSpeedToUse < 0)
		{
			baseSpeedToUse = baseSpeedToUse * -1;
		}
		
		int relativeValueOfValueFromBaseSpeed = baseSpeedToUse*value/100;
		
		if(baseSpeedToUse == 0)
		{
			if(value < 0)
			{
				*rightSpeed = value * -1;
			}
			else
			{
				*leftSpeed = value;
			}
		}
		else
		{
			//First divide the given base value by two to be able to 
			//calculte the new left and right speeds in the desired range.
			//
			//Then calculate the percentage of the current base speed to 
			//calculate the new left and right speed.
			if(value > 0)
			{
				*rightSpeed = baseSpeedToUse - relativeValueOfValueFromBaseSpeed;
				*leftSpeed =  baseSpeedToUse;
			}
			else if (value < 0)
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

		memset(receivedCommand, 0, receiveCommandBufferLength);
		memset(receivedValue, 0, receiveValueBufferLength);

		return 0;
	}
	else if (strcmp(receivedCommand, CONTROLLER_RECEIVE_SPEED) == 0)
	{
		*baseSpeed = value; // set the base speed between -100 and 100.

		// When the value is less than 0 it has to be multiplied by -1 to 
		// get a positve value. This way the right and left speed are ready for use.
		if(value < 0)
		{
			value = value * -1;
		}

		*rightSpeed = value;
		*leftSpeed = value;

		memset(receivedCommand, 0, receiveCommandBufferLength);
		memset(receivedValue, 0, receiveValueBufferLength);

		return 0;
	}
	else
	{
		return -1;
	}
}
