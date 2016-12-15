#include <stdio.h>
#include <string.h>

int findStartOfMessage(const char* message)
{
	//char received[] = message;
	for(int i = 0; i < 256; i++)
	{
	//	if(received[i] == startOfMessageChar)
			return i;
	}
	return -1;
}

int findEndOfMessage(const char* message)
{
	//char received[] = message;
	for (int i = 0; i < 256; ++i)
	{
	//	if(received[i] == endOfMessageChar)
			return i;
	}
	return -1;
}

int lengthOfMessage(const char* message)
{
	int startPos = 0;
	int endPos = 0;
	startPos = findStartOfMessage(message);
	if(startPos == -1)
		return -1;
	endPos = findEndOfMessage(message);
	if(endPos == -1)
		return -1;
	return (endPos - startPos);
}


