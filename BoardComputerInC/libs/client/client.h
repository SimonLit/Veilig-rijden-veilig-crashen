#ifndef CLIENT_H_
#define CLIENT_H_
#include "../datastruct/datastruct.h"

int setupClientConnection(const char* node,int service, int* socknumber);
int sendDataOverConnection(int socketFd, const char* string);

#endif