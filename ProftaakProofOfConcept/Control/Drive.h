#ifndef SPEED_H
#define SPPED_H

#include <stdint.h>

struct speedData
{
	uint8_t speedLeft;
	uint8_t speedRight;
}sDataArray[15];


void saveSpeedData(uint8_t leftSpeed, uint8_t speedRight);

uint16_t calculateAverageLeftSpeed(void);
uint16_t calculateAverageRightSpeed(void);
void writeSpeed(void);

#endif
