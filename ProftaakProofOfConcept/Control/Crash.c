#include "Crash.h"
#include "Drive.h"
#include "RP6I2CmasterTWI.h"
#include "RP6uart.h"
#include <stdbool.h>
#include "RP6Control_I2CMasterLib.h" 

//#define SERIAL_DEBUG
#define	USE_SERIAL

//====================================================================================
// Crash
//====================================================================================

uint8_t pressed = false;
uint8_t crashInfoWasSend = false;
uint8_t hitSide;
uint8_t impactGramByteSize[2];

int assignCrashInfo(crashInfo* cInfo)
{
	uint16_t avergeLeftSpeed = calculateAverageLeftSpeed();
	uint16_t avergeRightSpeed = calculateAverageRightSpeed();
	uint16_t averageSpeed = (avergeLeftSpeed + avergeRightSpeed)/2;
	
	// One speed point is equal to 5 segments per second.
	// By multiplying the speed by 5
	// you get the amount of segments past
	// on the encoder per second. 
	// Each segment is +/- 0.24mm (= ENCODER_RESOLUTION). 
	// ENCODER_RESOLUTION is defined in the RP6Config.h file.
	// So by multiplying is by 0.025cm you get the amount of cm/s.
	double speedCMPerSecond = averageSpeed * 5 * ENCODER_RESOLUTION; 	

	#ifdef SERIAL_DEBUG
		writeString("Average left speed: ");
		writeInteger(avergeLeftSpeed, DEC);
		writeChar('\n');
		writeString("Average right speed: ");
		writeInteger(avergeRightSpeed, DEC);
		writeChar('\n');
		writeString("Average speed: ");
		writeInteger(averageSpeed, DEC);
		writeChar('\n');
		writeString("Average: ");
		writeInteger(speedCMPerSecond, DEC);
		writeString(" cm/s");
		writeString("Impact: ");
		writeInteger(cInfo->impactGram, DEC);
		writeString(" grams");
		writeChar('\n');
		writeChar('\n');
	#endif

	cInfo->speed = speedCMPerSecond;
	cInfo->sideHit = hitSide;
	cInfo->distanceDrivenInCM = ((mleft_dist * (ENCODER_RESOLUTION/10)) + (mright_dist * (ENCODER_RESOLUTION/10))) / 2;
	impactGramByteSize[0] = (cInfo->impactGram >> 8) & 0xFF;
	impactGramByteSize[1] = cInfo->impactGram & 0xFF;

	return true;
}

void sendCrashInfo(crashInfo* cInfo)
{
	writeString("SENDING TO ARDUINO\n");

	#ifdef USE_SERIAL	
		writeString("#SPEED:");
		writeInteger(cInfo->speed, DEC);
		writeChar('%');

		writeString("#SIDE_HIT:");
		writeInteger(cInfo->sideHit, DEC);
		writeChar('%');

		writeString("#IMPACT:");
		writeInteger(cInfo->impactGram, DEC);
		writeChar('%');

		writeString("#DIST_DRIVEN:");
		writeInteger(cInfo->distanceDrivenInCM, DEC);
		writeChar('%');

		writeString("#ORIENTATION");
		writeChar('%');
	#endif
}



void buttenChanged(void)
{
	#ifdef SERIAL_DEBUG
		writeString("Bumper changed\n");
	#endif

	if(!pressed)
	{
		#ifdef SERIAL_DEBUG
			writeString("Bumper was pressed\n");
			writeSpeed();
		#endif

	 	if(bumper_left || bumper_right)
	 		hitSide = 1;
	 	else if(PINC & IO_PC2)
	 		hitSide = 4;
	 	else if(PINC & IO_PC3)
	 		hitSide = 3;
	 	else if(PINC & IO_PC5)
	 		hitSide = 2;

		setRP6LEDs(0b1111);
		pressed = true;
	}
	else if(pressed)
	{
		#ifdef SERIAL_DEBUG
			writeString("Bumper was released\n");
		#endif

		pressed = false;
		crashInfoWasSend = false;
	}
}
