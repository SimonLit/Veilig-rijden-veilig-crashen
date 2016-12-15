#ifndef SPEED_H
#define SPEED_H

#include <stdint.h>

extern int baseSpeed;
extern uint8_t rightSpeed;
extern uint8_t leftSpeed;

typedef struct
{
	uint8_t speedLeft;
	uint8_t speedRight;
}speedData;


int saveSpeedData(void);
//
//Pre:
//Post:
//Return:

uint16_t calculateAverageSpeed(void);
//
//Pre:
//Post:
//Return:

void drive(void);
//
//Pre:
//Post:
//Return:

#endif
