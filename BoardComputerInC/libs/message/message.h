#ifndef MESSAGE_H_
#define MESSAGE_H_

int findStartOfMessage(const char* message);
int findEndOfMessage(const char* message);
int lengthOfMessage(const char* message);
int correctFormatCheckRemoveBitshift(char* ms);
int split (char *str, char c, char ***arr);
int checkSender(DATAPACKET* recv, const char* sender);
int verificationStringCut(DATAPACKET* recv, const char* bf);
int dataCutRecvResponse(DATAPACKET* recv, const char* bf);
int messageCrashSend(char* string, DATAPACKET* d, DATAPACKET* e, int* l);
int messageInsSend(char* string, DATAPACKET* d, int* l);
#endif