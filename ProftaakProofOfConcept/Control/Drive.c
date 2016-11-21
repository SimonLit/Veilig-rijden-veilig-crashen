#include "Drive.h"

//====================================================================================
// Drive
//====================================================================================

uint8_t speedArrayIndexToWriteTo = 0;
const int sDataArraySize = 15;
speedData sDataArray[15];

void saveSpeedData(speedData* sData) 
{
	for (int i = 0; i < (sDataArraySize - 1); i++)
	{
		sDataArray[i] = sDataArray[i + 1];
	}

	sDataArray[sDataArraySize - 1] = *sData;
}

uint16_t calculateAverageLeftSpeed(void)
{
	uint16_t sum = 0;

	for(uint8_t i = 0; i < sDataArraySize; i++)
	{
		sum += sDataArray[i].speedLeft;
	}

	uint16_t average = sum/sDataArraySize;

	return average;
}

uint16_t calculateAverageRightSpeed(void)
{
	uint16_t sum = 0;

	for(uint8_t i = 0; i < sDataArraySize; i++)
	{
		sum += sDataArray[i].speedRight;
	}

	uint16_t average = sum/sDataArraySize;
	
	return average;
}


void writeSpeed(void)
{

	writeString("Index ");
	writeInteger((speedArrayIndexToWriteTo -1), DEC);
	writeString(" changed.");
	writeChar('\n');

	for(uint8_t index = 0; index < sDataArraySize; index++)
	{	
		writeString("Speed ");
		writeInteger(index, DEC);
		writeString(" left: ");
		writeInteger(sDataArray[index].speedLeft, DEC);

		writeString(" Speed ");
		writeInteger(index, DEC);
		writeString(" right: ");
		writeInteger(sDataArray[index].speedRight, DEC);
		writeChar('\n');
	}

	writeChar('\n');
	writeChar('\n');
}
