#ifndef HANDSHAKE_H_
#define HANDSHAKE_H_

#include "../datastruct/datastruct.h"

int verificationHandshake(int sockfd);
int handshakeReceiveData(int sockfd);

#endif