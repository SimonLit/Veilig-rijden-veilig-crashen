#ifndef CRASH_H
#define CRASH_H

#include <stdint.h>

extern uint8_t hitSide;
extern uint8_t pressed;
extern uint8_t crashInfoWasSend;

typedef struct
{
	uint8_t speed;
	uint8_t sideHit;
	uint16_t impactGram;
	uint16_t distanceDrivenInCM;
}crashInfo;


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
