#ifndef CRASH_H
#define CRASH_H

#include "stdint.h"
#include "Drive.h"
#include "RP6I2CmasterTWI.h"
#include "RP6uart.h"
#include "Adc.h"
#include "RP6Control_I2CMasterLib.h"

extern uint8_t hitSide;
extern uint8_t pressed;
extern uint8_t crashInfoWasSend;

typedef struct
{
	double speed;
	uint8_t sideHit;
	uint16_t impactGram;
	uint16_t distanceDrivenInCM;
}crashInfo;

int16_t map(int16_t valueToMap, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max);
//
//Pre: 
//Post: 
//Return:

uint16_t mapPressureSensorValueToNewton(void);
//
//Pre: 
//Post: 
//Return:

int assignCrashInfo(crashInfo* cInfo);
//
//Pre: 
//Post: 
//Return:

int sendCrashInfo(crashInfo* cInfo);
//
//Pre:
//Post:
//Return:

void buttenChanged(void);
//
//Pre:
//Post:
//Return:

int task_checkButtonChanged(void);
//
//Pre:
//Post:
//Return:

#endif
