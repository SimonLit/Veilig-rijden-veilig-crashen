#ifndef MESSAGE_H_
#define MESSAGE_H_

int verificationStringCut(DATAPACKET* recv, const char* bf);
int dataCutRecvResponse(DATAPACKET* recv, const char* bf, RESPONSES* rsp);

#endif