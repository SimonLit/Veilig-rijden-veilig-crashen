#ifndef MESSAGE_H_
#define MESSAGE_H_

int verificationStringCut(DATAPACKET* recv, char* bf);
int dataCutRecvResponse(DATAPACKET* recv, char* bf, RESPONSES* rsp);

#endif