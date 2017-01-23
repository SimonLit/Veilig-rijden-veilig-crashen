#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../datastruct/datastruct.h"
#include "../file_handeling/file_handeling.h"
#include "../handshake/handshake.h"

#define VictimId "114457896"

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

int correctFormatCheckRemoveBitshift(char* ms)
{
    int lenght, start, end;
    start = findStartOfMessage(ms);
    if(start == -1)
        return -1;
    end = findEndOfMessage(ms);
    if(end == -1)
        return -1;
    lenght = lengthOfMessage(ms);
    if(lenght < 0)
    {
        return -1;
    }
    for(int i = 0; i < lenght; i++)
    {
        ms[i] = ms[i+1];
    }
    ms[end - 1] = '\0';
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

int checkSender(DATAPACKET* recv, const char* sender)
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

int verificationStringCut(DATAPACKET* recv, const char* bf)
{
    char message[] = "                                                                           ";
    strcpy(message, bf);
	int rv = correctFormatCheckRemoveBitshift(message);
    if(rv == -1)
        return -1;

	char **arr = NULL;
	int c = split(message, ':', &arr);
	if(strcmp(arr[0], "CONNECT") == 0)
	{
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
}

//Set respons, check bf on start and end point, split it save shit in datapacket
int dataCutRecvResponse(DATAPACKET* recv, const char* bf)
{
    char message[] = "                                                                         ";
    strcpy(message, bf);
    int rv = correctFormatCheckRemoveBitshift(message);
    if(rv == -1)
        return -1;
    char **array = NULL;
    int c = split(message, '|', &array);
    if(strcmp(array[0], "DAT") == 0)
    {
        strcpy(recv -> messageReceived, message);
        recv -> sf = true;
        recv-> Sender = CAR;
        send(recv->sockFd, "#ACK@", 5, 0);
        writeToFile(carStatusFile, 3);
        return 0;
    }
    else if(strcmp(array[0], "START_RP6") == 0)
    {
        recv->Sender = CAR;
        send(recv->sockFd, "#ACK@", 5, 0);
        writeToFile(carStatusFile, 1);
        return 0;
    }
    else if(strcmp(array[0], "STOP_RP6") == 0)
    {
        recv->Sender = CAR;
        send(recv->sockFd, "#ACK@", 5, 0);
        writeToFile(carStatusFile, 2);
        return 0;
    }
    else if(strcmp(array[0], "REQ") == 0)
    {
        if(strcmp(array[1], "DRI") == 0)
        {
            recv->Sender = PHONE;
            int v = 0;
            printf("Received car mode request\n");
            readFromFile(carStatusFile, &v);
            switch(v){
                case 1:
                    printf("Send drive\n");
                    send(recv->sockFd, "#DRIVE@\n", 8,0);//Niks terug
                break; 
                case 2:
                     printf("Send stop\n");
                     send(recv->sockFd, "#STOP@\n", 7,0);//PDA|INS:int@
                     secondDataRec(recv);
                break;
                case 3:
                    printf("Send crash\n");
                    send(recv->sockFd, "#CRASH@\n", 8,0);//PDB|INS:int|COR:double8:double8@
                    secondDataRec(recv);
                    writeToFile(carStatusFile, 2);
                    break;
                case 4:
                    printf("Send touched\n");
                    send(recv->sockFd, "#TOUCHED@\n", 10,0);
                    //sleep(5);
                    //writeToFile(carStatusFile, 2);
                    break;
                default:
                    printf("Error\n");
                    send(recv->sockFd, "#NODATA@\n", 9,0);
                break;
            }
        }
        return 0;
    }
    else if(strcmp(array[0], "TOUCH") == 0)
    {
        printf("Phone touched by user: %s\n", array[1]);
        writeToFile(carStatusFile, 4);
        return 0;
    }
	return -1;
}

int messageCrashSend(char* string, DATAPACKET* d, DATAPACKET* e, int* l)
{
    char message[maxLengthMessage];
    strcpy(message, "\0");
    strcat(message, "#");
    strcat(message, VictimId);
    strcat(message, "|");
    strcat(message, d->messageReceived);
    strcat(message, "|");
    strcat(message, e->crahsPhoneData);
    strcat(message, "@");
    *l = lengthOfMessage(message);
    *l += 1;
    strcpy(string, message);
    return 0;
}

int messageInsSend(char* string, DATAPACKET* d, int *l)
{
    char message[maxLengthMessage];
    strcpy(message, "\0");
    strcat(message, "#");
    strcat(message, VictimId);
    strcat(message, "|");
    strcat(message, d->stopPhoneData);
    strcat(message, "@");
    *l = lengthOfMessage(message);
    *l += 1;
    strcpy(string, message);
    return 0;
}
