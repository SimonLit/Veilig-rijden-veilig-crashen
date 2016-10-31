#include "RP6ControlLib.h"
#include "RP6I2CmasterTWI.h"
#include "Drive.h"
#include "MPU9250.h"
#include "Crash.h"
#include <stdbool.h>
#include "RP6Control_I2CMasterLib.h" 	

#define DEBUG

bool lastButton2State = false;
bool lastButton3State = false;
bool lastButton5State = false;
uint16_t FSRRawValue[5];
uint16_t averageFSRValue;

#ifdef DEBUG
	uint8_t sideHit = 0;
	uint8_t timesPressed2 = 0;
	uint8_t timesPressed3 = 0;
	uint8_t timesPressed5 = 0;
#endif

void task_checkButtonChanged(void)
{
	if((PINC & IO_PC2) !=  lastButton2State)
	{
		buttenChanged();

		#ifdef DEBUG
			if(PINC & IO_PC2)
			{
				sideHit = 2;
				timesPressed2++;
				writeButtonPressOnLCD(sideHit, timesPressed2);

				writeString("Button 2 pressed ");
				writeInteger(timesPressed2, DEC);
				writeString(" times.");
				writeString("\n");
			}
		#endif

		lastButton2State = PINC & IO_PC2;
	}	

	else if((PINC & IO_PC3) !=  lastButton3State)
	{
		buttenChanged();

		#ifdef DEBUG
			if(PINC & IO_PC3)
			{
				sideHit = 3;
				timesPressed3++;
				writeButtonPressOnLCD(sideHit, timesPressed3);

				writeString("Button 3 pressed ");
				writeInteger(timesPressed3, DEC);
				writeString(" times.");
				writeString("\n");
			}
			#endif

		lastButton3State = PINC & IO_PC3;
	}	

	else if((PINC & IO_PC5) !=  lastButton5State)
	{
		buttenChanged();

		#ifdef DEBUG
			if(PINC & IO_PC5)
			{
				sideHit = 5;
				timesPressed5++;
				writeButtonPressOnLCD(sideHit, timesPressed5);

				writeString("Button 5 pressed ");
				writeInteger(timesPressed5, DEC);
				writeString(" times.");
				writeString("\n");
			}
		#endif

		lastButton5State = PINC & IO_PC5;
	}	
}

void task_readFSRRawValueAddToArray_AssignAvareFSRValue(void)
{
	uint16_t sum = 0;
	uint16_t arraySize = sizeof(pressureSensorRawValue)/sizeof(pressureSensorRawValue[0]);

	for (uint8_t i = 0; i < (arraySize -1); ++i)
	{
		pressureSensorRawValue[i] = pressureSensorRawValue[i + 1];
		sum += pressureSensorRawValue[i];
	}

	pressureSensorRawValue[arraySize] = readADC(ADC_5);
	sum += pressureSensorRawValue[arraySize];

	averageFSRValue = sum/arraySize;
}

float mapPressureSensorValueToNewton(void)
{
	return map(averageFSRValue, 0, 1023, 0.2, 20);
}

long map(long valueToMap, long in_min, long in_max, long out_min, long out_max)
{
	return (valueToMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * This function gets called automatically if there was an I2C Error like
 * the slave sent a "not acknowledge" (NACK, error codes e.g. 0x20 or 0x30).
 * The most common mistakes are: 
 *   - using the wrong address for the slave
 *   - slave not active or not connected to the I2C-Bus
 *   - too fast requests for a slower slave
 * Be sure to check this if you get I2C errors!
 */
void I2C_transmissionError(uint8_t errorState)
{
	writeString_P("\nI2C ERROR - TWI STATE: 0x");
	writeInteger(errorState, HEX);
	writeChar('\n');
}


/**
 * Timed Watchdog display only - the other heartbeat function
 * does not work in this example as we use blocked moving functions here.
 */
void watchDogRequest(void)
{	
	static uint8_t heartbeat2 = false;
	if(heartbeat2)
	{
		clearPosLCD(0, 14, 1);
		heartbeat2 = false;
	}
	else
	{
		setCursorPosLCD(0, 14);
		writeStringLCD_P("#"); 
		heartbeat2 = true;
	}
}


void writeButtonPressOnLCD(uint8_t button, int pressed)
{
	clearLCD();
	setCursorPosLCD(0,0);
	writeStringLCD("btn:     times:");
	setCursorPosLCD(1,0);
	writeIntegerLCD(button, DEC);
	writeStringLCD("        ");
	writeIntegerLCD(pressed, DEC);
}


/************************************************************************************/
//====================================================================================
// Main - The program starts here:
//====================================================================================
/************************************************************************************/

int main(void)
{
	initRP6Control(); 	
	initI2C_RP6Lib();
	I2CTWI_setTransmissionErrorHandler(I2C_transmissionError);

	WDT_setRequestHandler(watchDogRequest); 

	DDRC &= ~IO_PC2; 
	DDRC &= ~IO_PC3;  
	DDRC &= ~IO_PC5; 

	DDRA &= ~ADC5; 

	#ifdef DEBUG
		if(PINC & IO_PC2) 
			writeString_P("\n\nPC2 is HIGH!\n\n");
		else
			writeString_P("\n\nPC2 is LOW!\n\n");

		if(PINC & IO_PC3) 
			writeString_P("\n\nPC3 is HIGH!\n\n");
		else
			writeString_P("\n\nPC3 is LOW!\n\n");

		if(PINC & IO_PC5) 
			writeString_P("\n\nPC5 is HIGH!\n\n");
		else
			writeString_P("\n\nPC5 is LOW!\n\n");
	#endif

	

	startStopwatch1();
	startStopwatch2();	

	// Setup ACS power:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_ACS_POWER, ACS_PWR_MED);
	// Enable Watchdog for Interrupt requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT, true);
	// Enable timed watchdog requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT_RQ, true);
	
	BUMPERS_setStateChangedHandler(buttenChanged);

	initMPU9250();

	gyroData gData;

	bool arrayIsFilled = false;
	uint8_t counter = 0;

	float earthAcceleration = 9.81;

	changeDirection(FWD);

	while(true)
	{
		task_checkINT0();
	    task_I2CTWI();

		if(getStopwatch1() > 300)
		{
			task_checkButtonChanged();
			task_readFSRRawValueAddToArray_AssignAvareFSRValue();
			crashInfo.impactGram = (uint16_t)((mapPressureSensorValueToNewton()/earthAcceleration) * 1000);
			setStopwatch1(0);
		}

		if(!pressed)
		{
			setLEDs(0b0);

			moveAtSpeed(60,60);

			if(getStopwatch2() > 500)
			{
				getAllSensors();
				saveSpeedData(mleft_speed, mright_speed);
				saveGyroData(gData);

				setStopwatch2(0);
			}
		}
		else if(!crashInfoWasSend && pressed)
		{
			crashInfoWasSend = assignCrashInfo();
			sendCrashInfo();
		} 
		else if(crashInfoWasSend && pressed)
		{
			stop();
		}
	}	
}