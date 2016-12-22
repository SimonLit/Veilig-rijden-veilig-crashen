#ifndef MESSAGE_H_
#define MESSAGE_H_

int findStartOfMessage(const char* message);
int findEndOfMessage(const char* message);
int lengthOfMessage(const char* message);
int correctFormatCheckRemoveBitshift(char** ms);
int verificationStringCut(DATAPACKET* recv, char* bf);
int dataCutRecvResponse(DATAPACKET* recv, char* bf, RESPONSES* rsp);

#endif