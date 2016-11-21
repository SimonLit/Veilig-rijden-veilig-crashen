#ifndef SPEED_H
#define SPPED_H

#include "RP6uart.h"
#include "stdint.h"

typedef struct
{
	uint8_t speedLeft;
	uint8_t speedRight;
}speedData;


void saveSpeedData(speedData* sData);

uint16_t calculateAverageLeftSpeed(void);
uint16_t calculateAverageRightSpeed(void);
void writeSpeed(void);

#endif
