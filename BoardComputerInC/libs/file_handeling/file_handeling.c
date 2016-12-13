#include <stdio.h>
#include <unistd.h>
#include "../datastruct/datastruct.h"
#include "file_handeling.h"

int createFile(char* filename)
{
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
		return -1;
	fclose(fp);
	return 0;
}

int wirteDataStructToFile(char* filename, const DATAPACKET* value)
{
	if(filename == NULL)
		return -1;
	if(value == NULL)
		return -1;
	FILE* fp = fopen(filename, "r+");
	if(fp == NULL)
		return -1;//File does not exist
	fclose(fp);
	fp = fopen(filename, "a");
	int returnvalueWrite = fwrite(value, sizeof(DATAPACKET), 1, fp);
	fclose(fp);
	if(returnvalueWrite == 1)
		return 0;
	return -1;
}

int writeDataStructArrayToFile(char* filename, DATAPACKET* array, int amountOfDatapackets)
{
	if(array == NULL)
		return -1;
	FILE* fp = fopen(filename, "a");
	if(fp == NULL)
		return -1;
	int rv = fwrite(array, sizeof(DATAPACKET), amountOfDatapackets, fp);
	fclose(fp);
	if(rv == amountOfDatapackets)
		return 0;
	return -1;
}

int getNrOfDatStructs(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if(fp == NULL)
		return -1;
	fseek(fp, 0L, SEEK_END);
	int amountOfStructs = ftell(fp)/sizeof(DATAPACKET);
	fseek(fp, 0L, SEEK_SET);
	fclose(fp);
	return amountOfStructs;
}

int readDataStructFromFile(char* filename, DATAPACKET* info, int pos)
{
	return 0;
}

int readAllDataFromFile(char* filename, DATAPACKET* array, int number)
{
	if(filename == NULL)
		return -1;
	if(array == NULL)
		return -1;
	FILE* fp = fopen(filename, "r");
	if(fp == NULL)
		return -1;
	int amountOfDatapackets = getNrOfDatStructs(filename);
	if(amountOfDatapackets == -1)
		return -1;
	else if(number > amountOfDatapackets)
		number = amountOfDatapackets;
	int nrRead = fread(array, sizeof(DATAPACKET), number, fp);
	fclose(fp);
	return nrRead;
}

int removeFile(char* filename)
{
	if(access(filename, F_OK) == 0)
	{
		remove(filename);
		return 0;
	}
	return -1;
}