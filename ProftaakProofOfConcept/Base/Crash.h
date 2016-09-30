#ifndef CRASH_H
#define CRASH_H

#include <stdint.h>
#include "MPU9250.h"

extern uint8_t pressed;
extern uint8_t crashInfoWasSend;

struct crashInfo
{
	double speed;
	uint16_t GyX;
	uint16_t GyY;
	uint16_t GyZ;
	uint8_t sideHit;
	uint16_t impact;
};

uint8_t assignCrashInfo(gyroData gData);

void sendCrashInfo(void);

void buttenChanged(void);

#endif