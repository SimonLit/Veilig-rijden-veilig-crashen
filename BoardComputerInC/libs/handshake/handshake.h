#ifndef HANDSHAKE_H_
#define HANDSHAKE_H_

#include "../datastruct/datastruct.h"

int verificationHandshake(int sockfd, DATAPACKET* senderData);
int handshakeReceiveData(int sockfd, DATAPACKET* senderData);

#endif