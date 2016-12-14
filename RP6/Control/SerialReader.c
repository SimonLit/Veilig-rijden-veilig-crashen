#include "SerialReader.h"
#include "RP6uart.h" 
#include <string.h>
#include "ProtocolDefines.h"
#include "Tools.h"

int START_READING_COMMAND = 0;
int START_READING_VALUE = 0;
int STOP_READING = 0;

int getIncomingSerialMessage(char* receiveBufferCommand, char* receiveBufferValue, const int sizeOfCommandBuffer, const int sizeOfValueBuffer)
{

	if(receiveBufferCommand == NULL || receiveBufferValue == NULL || sizeOfCommandBuffer < 1 || sizeOfValueBuffer < 1)
	{
		return -1;
	}
	
	char receivedChar;
	uint8_t nrOfCharsReceived = getBufferLength();
	
	// check if no data was received
	if (nrOfCharsReceived == 0) return -1;
	
	char storeReceiveBufferCommand[sizeOfCommandBuffer];
	char storeReceiveBufferValue[sizeOfValueBuffer];
	
	int commandWriteIndex = 0;
	int valueWriteIndex = 0;

	while(getBufferLength() > 0 && commandWriteIndex < sizeOfCommandBuffer && valueWriteIndex < sizeOfValueBuffer)
	{
		receivedChar = readChar(); // Char read from the buffer.

		// Was the last read character in the buffer a '@'? 
		// If yes then stop reading and interpret the message/act on the message.
		if(receivedChar == END_CHARACTER)
		{
			START_READING_COMMAND = 0;
			START_READING_VALUE = 0;
			STOP_READING = 1;

			memset(receiveBufferCommand, 0, sizeOfCommandBuffer);
			memset(receiveBufferValue, 0, sizeOfValueBuffer);
			
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
	return -1;
}

int waitForConnectRequest(char* receiveBufferCommand)
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