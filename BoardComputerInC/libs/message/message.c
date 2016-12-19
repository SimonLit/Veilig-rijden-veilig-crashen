#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../datastruct/datastruct.h"

static int findStartOfMessage(const char* message)
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

static int findEndOfMessage(const char* message)
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

static int lengthOfMessage(const char* message)
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

static int correctFormatCheckRemoveBitshift(char** ms)
{
    int indexStart, indexEnd, length;
    indexStart = findStartOfMessage(*ms);
    indexEnd = findEndOfMessage(*ms);
    if(indexEnd < 1 || indexStart == -1)
        return -1;
    length = lengthOfMessage(*ms);
    for(int i = 0; i <= length; i++)
        *ms[i] = *ms[i + 1];
    *ms[indexEnd - 1] = '\0';
	return 0;
}


static int split (char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

static int checkSender(DATAPACKET* recv, const char* sender)
{
    if(strcmp(sender, "CAR") == 0)
    {
        recv -> Sender = CAR;
        return 0;
    }
    else if(strcmp(sender, "PHONE") == 0)
    {
        recv -> Sender = PHONE;
        return 0;
    }
    return -1;
}

int verificationStringCut(DATAPACKET* recv, char* bf)
{
	char* message = bf;
	int rv = correctFormatCheckRemoveBitshift(&message);
    if(rv == -1)
        return -1;
	char **arr = NULL;
	int c = split(message, ':', &arr);
	for(int i = 0; i < c; i++)
		printf("The parts of the message are: %s\n", arr[i]);//Debug line
	if(strcmp(arr[0], "CONNECT") == 0)
	{
		printf("Ontvangen CONNECT\n");
        rv = checkSender(recv, arr[1]);
        if(rv == 0)
            return 0;
        else
            return -1;
    }
	else
	{
		return -1;
	}
	return 0;
}

int dataCutRecvResponse(DATAPACKET* recv, char bf, RESPONSES rsp)
{
	return 0;
}
