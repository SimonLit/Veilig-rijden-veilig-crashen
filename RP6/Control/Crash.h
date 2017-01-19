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
//Pre: -
//Post: All the collected data is assigned to cInfo
//Return: 0 on succes.
//		 -1 if cInfo is NULL 
int sendCrashInfo(crashInfo* cInfo);
//
//Pre: -
//Post: The values of cInfo are send over serial with a handshake.
//Return: 0 on succes
//       -1 if cInfo is NULL or the handshake couldn't be made in timeoutHandler()
void buttenChanged(void);
//
//Pre: -
//Post: If a butten was pressed a variable with the hit side is assigned
//      and a boolean indicating a button was pressed is set to true.

int task_checkButtonChanged(void);
//
//Pre: -
//Post: Check every 50 milliseconds if a button was pressed. If it was pressed call buttenChanged().
//      If the timer exceeds 50 milliseconds reset it to 0.
//Return: 0 on succes
//       -1 if no button was pressed or the timer is less then 50 millisecods

#endif
