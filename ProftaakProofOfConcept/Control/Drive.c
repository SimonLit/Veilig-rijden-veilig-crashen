#include "Drive.h"
#include "RP6uart.h"

//====================================================================================
// Drive
//====================================================================================

uint8_t speedArraySize = 15;
uint8_t speedArrayIndexToWriteTo = 0;
struct speedData sData;


void saveSpeedData(uint8_t leftSpeed, uint8_t speedRight) 
{
	sData.speedLeft = leftSpeed;
	sData.speedRight = speedRight;
	int arraySize = sizeof(sDataArray)/sizeof(sDataArray[0]);

	for (int i = 0; i < (arraySize - 1); i++)
	{
		sDataArray[i] = sDataArray[i + 1];
	}

	sDataArray[arraySize - 1] = sData;
}

uint16_t calculateAverageLeftSpeed(void)
{
	uint16_t sum = 0;

	for(uint8_t i = 0; i < speedArraySize; i++)
	{
		sum += sDataArray[i].speedLeft;
	}

	uint16_t average = sum/speedArraySize;

	return average;
}

uint16_t calculateAverageRightSpeed(void)
{
	uint16_t sum = 0;

	for(uint8_t i = 0; i < speedArraySize; i++)
	{
		sum += sDataArray[i].speedRight;
	}

	uint16_t average = sum/speedArraySize;
	
	return average;
}

void writeSpeed(void)
{

	writeString("Index ");
	writeInteger((speedArrayIndexToWriteTo -1), DEC);
	writeString(" changed.");
	writeChar('\n');

	for(uint8_t index = 0; index < speedArraySize; index++)
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
