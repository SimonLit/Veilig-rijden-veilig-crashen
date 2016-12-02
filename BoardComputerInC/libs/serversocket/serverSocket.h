#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

int setupCommunicationServer(const char* node, const char* service, int* socketnumber);
int acceptinConnectionsOnServer(int sockfd);

#endif