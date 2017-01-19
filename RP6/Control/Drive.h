#ifndef DRIVE_H
#define DRIVE_H

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
//Pre: -
//Post: The speed values in the array are shifted and the newest speed value is added at the end.
//      The speed value is an avarage of the left and right speed.
//Return: 0 on succes.

uint16_t calculateAverageSpeed(void);
//
//Pre: -
//Post: The avarage speed in the speed array is calculated
//Return: The avarage speed is returned.

void drive(void);
//
//Pre: - 
//Post: Set the left and right speed of the RP6 to the extern rightSpeed and leftSpeed.
//      If baseSpeed is less than 0 set the RP6 is reverse otherwise drive straight.

#endif
