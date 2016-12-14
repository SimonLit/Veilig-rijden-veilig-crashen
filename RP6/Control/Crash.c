#include "Crash.h" 
#include "Drive.h"
#include "RP6I2CmasterTWI.h"
#include "RP6uart.h"
#include "Adc.h"
#include "RP6Control_I2CMasterLib.h"
#include "Tools.h"

//====================================================================================
// Crash
//====================================================================================

uint8_t pressed = false;
uint8_t crashInfoWasSend = false;
uint8_t hitSide;

uint8_t lastButton2State = false;
uint8_t lastButton3State = false;
uint8_t lastButton5State = false;

// Used for the converting from Newton to grams.
float earthAcceleration = 9.81; 

int assignCrashInfo(crashInfo* cInfo)
{
	if(cInfo == NULL)
	{
		return -1;
	}

	uint16_t averageSpeed = calculateAverageSpeed();
	
	// One speed point is equal to 5 segments per second.
	// By multiplying the speed by 5
	// you get the amount of segments past
	// on the encoder per second. 
	// Each segment is +/- 0.24mm (= ENCODER_RESOLUTION). 
	// ENCODER_RESOLUTION is defined in the RP6Config.h file.
	// So by multiplying is by 0.025cm you get the amount of cm/s.
	double speedCMPerSecond = averageSpeed * 5 * ENCODER_RESOLUTION; 	

	cInfo->speed = speedCMPerSecond;
	cInfo->sideHit = hitSide;
	cInfo->impactGram = (mapPressureSensorValueToNewton(readADC(ADC_5))/earthAcceleration) * 1000;
	cInfo->distanceDrivenInCM = ((mleft_dist * (ENCODER_RESOLUTION/10)) + (mright_dist * (ENCODER_RESOLUTION/10))) / 2;

	return 0;
}

int sendCrashInfo(crashInfo* cInfo)
{
	if(cInfo == NULL)
	{
		return -1;
	}

	writeString("\n#SPEED:");
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

	crashInfoWasSend = true;

	return 0;
}

void buttenChanged(void)
{
	if(!pressed)
	{
	 	if(bumper_left || bumper_right)
	 	{
	 		hitSide = 1;
	 	}
	 	else if(PINC & IO_PC2)
	 	{
	 		hitSide = 4;
	 	}
	 	else if(PINC & IO_PC3)
	 	{
	 		hitSide = 3;
	 	}
	 	else if(PINC & IO_PC5)
	 	{
	 		hitSide = 2;
	 	}
	 	
		pressed = true;
	}
	else
	{
		pressed = false;
		crashInfoWasSend = false;
	}
}

int task_checkButtonChanged(void)
{
	if(getStopwatch4() > 50)
	{
		uint8_t button2State = PINC & IO_PC2;
		uint8_t button3State = PINC & IO_PC3;
		uint8_t button5State = PINC & IO_PC5;

		if(button2State !=  lastButton2State)
		{
			buttenChanged();
			lastButton2State = button2State;

			return 0;
		}	

		else if(button3State !=  lastButton3State)
		{
			buttenChanged();
			lastButton3State = button3State;

			return 0;
		}	

		else if(button5State !=  lastButton5State)
		{
			buttenChanged();
			lastButton5State = button5State;

			return 0;
		}	

		setStopwatch4(0);
	}

	return -1;
}
