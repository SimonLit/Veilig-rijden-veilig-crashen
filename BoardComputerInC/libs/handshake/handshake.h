#ifndef HANDSHAKE_H_
#define HANDSHAKE_H_

#include "../datastruct/datastruct.h"

int waitForAckFromClient(int sockfd);
int handshakeReceiveData(int sockfd, const char* ip);
int secondDataRec(DATAPACKET* recv);

#endif