#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../datastruct/datastruct.h"

int correctFormatCheckRemoveBitshift(char* ms)
{
	return 0;
}


int split (char *str, char c, char ***arr)
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


int verificationStringCut(DATAPACKET* recv, char* bf)
{
	char* message = bf;
	int rv = correctFormatCheckRemoveBitshift(message);


	char **arr = NULL;
	int c = split(bf, '|', &arr);
	for(int i = 0; i < c; i++)
		printf("The parts of the message are: %s\n", arr[i]);//Debug line
	if(strcmp(arr[0], "CON") == 0)
	{

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
