#include "SerialReaderSender.h"
#include "RP6uart.h" 
#include <string.h>
#include "ProtocolDefines.h"
#include "Tools.h"
#include "Stopwatch.h"

int START_READING_COMMAND = 0;
int START_READING_VALUE = 0;
int STOP_READING = 0;

char storeReceiveBufferCommand[MAX_COMMAND_LENGTH];
char storeReceiveBufferValue[MAX_VALUE_LENGTH];
	
int commandWriteIndex = 0;
int valueWriteIndex = 0;

int getIncomingSerialMessage(char* receiveBufferCommand, char* receiveBufferValue)
{

	if(receiveBufferCommand == NULL || receiveBufferValue == NULL)
	{
		return -1;
	}
	
	char receivedChar;
	uint8_t nrOfCharsReceived = getBufferLength();
	
	// check if no data was received
	if (nrOfCharsReceived == 0) return -1;

	if(getBufferLength() > 0 && commandWriteIndex < MAX_COMMAND_LENGTH && valueWriteIndex < MAX_VALUE_LENGTH)
	{ 
		receivedChar = readChar(); // Char read from the buffer.

		// Was the last read character in the buffer a '@'? 
		// If yes then stop reading and interpret the message/act on the message.
		if(receivedChar == *END_CHARACTER)
		{
			START_READING_COMMAND = 0;
			START_READING_VALUE = 0;
			STOP_READING = 1;

			commandWriteIndex = 0;
			valueWriteIndex = 0;

			memset(receiveBufferCommand, 0, MAX_COMMAND_LENGTH);
			memset(receiveBufferValue, 0, MAX_VALUE_LENGTH);
			
			// Append the received message to the command and value char*.
			// By using strcat the null terminator is added automatically.

			strcat(receiveBufferCommand, storeReceiveBufferCommand);
			strcat(receiveBufferValue, storeReceiveBufferValue);

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
		if(receivedChar == *VALUE_CHARACTER)
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
		if(receivedChar == *START_CHARACTER)
		{
			START_READING_COMMAND = 1;
			START_READING_VALUE = 0;
			STOP_READING = 0;
				
			commandWriteIndex = 0;
			valueWriteIndex = 0;

			// Make sure the temporery command and value strings are clean.
			// Otherwise string could get mixesd with each other.
			memset(storeReceiveBufferCommand, 0, MAX_COMMAND_LENGTH);
			memset(storeReceiveBufferValue, 0, MAX_VALUE_LENGTH);
		}
	}
	return -1;
}

void sendMessage(char* command)
{
	makeProtocolMessage(command);
	writeString(protocolMessageToSend);
}

void sendMessageWithValue(char* command, char* value)
{
	makeProtocolMessageWithValue(command, value);
	writeString(protocolMessageToSend);
}

int timeoutHandler(void)
{
	long timoutTimer = 0;
	int nackCounter = 0;

	char commandBuffer[MAX_COMMAND_LENGTH];
	char valueBuffer[MAX_VALUE_LENGTH];

	while (nackCounter < MAX_NACK_COUNTER && (getStopwatch5() - timoutTimer) < MAX_HEARTBEAT_TIMEOUT)
	{
		if(getIncomingSerialMessage(commandBuffer, valueBuffer) == 0)
		{
			if(checkForACK(commandBuffer) == 0)
			{
				return 0;
			}
			else if(checkForNACK(commandBuffer) == 0)
			{
				writeString(protocolMessageToSend);
				nackCounter++;
				timoutTimer = getStopwatch5();
			}
		}
	}

	if(nackCounter > MAX_NACK_COUNTER || (getStopwatch5() - timoutTimer) > MAX_HEARTBEAT_TIMEOUT) {return -1;}
}
