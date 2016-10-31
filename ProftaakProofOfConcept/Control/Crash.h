#ifndef CRASH_H
#define CRASH_H

#include <stdint.h>
#include "MPU9250.h"

extern uint8_t hitSide;
extern uint8_t pressed;
extern uint8_t crashInfoWasSend;

struct crashInfo
{
	double speed;
	uint8_t sideHit;
	uint16_t impactGram;
};

int assignCrashInfo(void);

void sendCrashInfo(void);

void buttenChanged(void);

#endif