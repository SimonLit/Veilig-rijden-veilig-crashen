#include <stdio.h>
#include <string.h>
#include "../datastruct/datastruct.h"

int findStartOfMessage(const char* message)
{
	char received[256];
	sprintf(received, "%s", message);
	for(int i = 0; i < 256; i++)
	{
		if(received[i] == '#')
			return i;
	}
	return -1;
}

int findEndOfMessage(const char* message)
{
	char received[256];
	sprintf(received, "%s" ,message);
	for (int i = 0; i < 256; ++i)
	{
		if(received[i] == '@')
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

int verificationStringCut(DATAPACKET* recv, const char* bf)
{
	return 0;
}

int dataCutRecvResponse(DATAPACKET* recv, const char bf, RESPONSES rsp)
{
	return 0;
}
