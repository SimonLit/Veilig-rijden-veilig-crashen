#ifndef _FILE_HANDELING_H_
#define _FILE_HANDELING_H_

#include <stdio.h>
#include "../datastruct/datastruct.h"


int createFile(char* filename);
int wirteDataStructToFile(char* filename, DATAPACKET value);
int writeDataStructArrayToFile(char* filename, DATAPACKET* array, int lengthArray, int* newLengthArray);
int getNrOfDatStructs(char* filename);
int readDataStructFromFile(char* filename, DATAPACKET* info, int pos, SENDERS s, int ipAdress);
int readAllDataFromFile(char* filename, int number);
int removeFile(char* filename);

#endif