#include "Drive.h"

//====================================================================================
// Drive
//====================================================================================

uint8_t speedArrayIndexToWriteTo = 0;
const int sDataArraySize = 15;
speedData sDataArray[15];

int saveSpeedData(void) 
{
	speedData sData = {mleft_speed, mright_speed};

	for (int i = 0; i < (sDataArraySize - 1); i++)
	{
		sDataArray[i] = sDataArray[i + 1];
	}

	sDataArray[sDataArraySize - 1] = sData;

	return 0;
}

uint16_t calculateAverageSpeed(void)
{
	uint16_t sum = 0;

	for(uint8_t i = 0; i < sDataArraySize; i++)
	{
		sum += (sDataArray[i].speedLeft + sDataArray[i].speedRight);
	}

	return sum/sDataArraySize;
}