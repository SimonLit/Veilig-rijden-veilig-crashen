#include "RP6ControlLib.h"
#include "RP6I2CmasterTWI.h"
#include "Drive.h"
//#include "MPU9250.h"
//#include "MPU_DMP.h"
#include "Crash.h"
#include <stdbool.h>
#include "RP6Control_I2CMasterLib.h" 	

//#define DEBUG

uint8_t lastButton2State = false;
uint8_t lastButton3State = false;
uint8_t lastButton5State = false;
uint16_t FSRRawValue[5];
uint16_t averageFSRValue;

#ifdef DEBUG
	uint8_t sideHit = 0;
	uint8_t timesPressed2 = 0;
	uint8_t timesPressed3 = 0;
	uint8_t timesPressed5 = 0;
#endif

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

void task_checkButtonChanged(void)
{
	uint8_t button2State = PINC & IO_PC2;
	uint8_t button3State = PINC & IO_PC3;
	uint8_t button5State = PINC & IO_PC5;

	if(button2State !=  lastButton2State)
	{
		buttenChanged();
		lastButton2State = button2State;

		#ifdef DEBUG
			if(button2State)
			{
				sideHit = 2;
				timesPressed2++;
				writeButtonPressOnLCD(sideHit, timesPressed2);

				writeString("Button 2 pressed ");
				writeInteger(timesPressed2, DEC);
				writeString(" times.");
				writeString("\n");
			}

			writeString("lastButton2State: ");
			writeInteger(lastButton2State, DEC);
			writeChar('\n');
		#endif
	}	

	else if(button3State !=  lastButton3State)
	{
		buttenChanged();
		lastButton3State = button3State;

		#ifdef DEBUG
			if(button3State)
			{
				sideHit = 3;
				timesPressed3++;
				writeButtonPressOnLCD(sideHit, timesPressed3);

				writeString("Button 3 pressed ");
				writeInteger(timesPressed3, DEC);
				writeString(" times.");
				writeString("\n");
			}

			writeString("lastButton32State: ");
			writeInteger(lastButton3State, DEC);
			writeChar('\n');
		#endif	
	}	

	else if(button5State !=  lastButton5State)
	{
		buttenChanged();
		lastButton5State = button5State;

		#ifdef DEBUG
			if(button5State)
			{
				sideHit = 5;
				timesPressed5++;
				writeButtonPressOnLCD(sideHit, timesPressed5);

				writeString("Button 5 pressed ");
				writeInteger(timesPressed5, DEC);
				writeString(" times.");
				writeString("\n");
			}

			writeString("lastButton5State: ");
			writeInteger(lastButton5State, DEC);
			writeChar('\n');
		#endif
	}	
}

void task_readFSRRawValueAddToArray_AssignAvareFSRValue(void)
{
	uint16_t sum = 0;
	uint16_t arraySize = sizeof(FSRRawValue)/sizeof(FSRRawValue[0]);

	for (uint8_t i = 0; i < (arraySize -1); ++i)
	{
		FSRRawValue[i] = FSRRawValue[i + 1];
		sum += FSRRawValue[i];
	}

	FSRRawValue[arraySize] = readADC(ADC_5);
	sum += FSRRawValue[arraySize];

	averageFSRValue = sum/arraySize;
}

long map(long valueToMap, long in_min, long in_max, long out_min, long out_max)
{
	return (valueToMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapPressureSensorValueToNewton(void)
{
	return map(averageFSRValue, 0, 1023, 0.2, 20);
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
	startStopwatch3();	

	// Setup ACS power:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_ACS_POWER, ACS_PWR_MED);
	// Enable Watchdog for Interrupt requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT, true);
	// Enable timed watchdog requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT_RQ, true);
	
	BUMPERS_setStateChangedHandler(buttenChanged);

	//initMPU9250();

	//gyroData gData;
	crashInfo cInfo;

	float earthAcceleration = 9.81;

	changeDirection(FWD);
	bool startProgram = false;

	while(true)
	{
		task_checkINT0();
		task_I2CTWI();

		uint8_t pressedButton = checkReleasedKeyEvent();

		if(startStopwatch3() > 50)
		{		
			switch(pressedButton)
			{
				case 1:
					writeInteger(pressedButton, DEC);
					writeChar('\n');
					clearLCD();
					if(startProgram)
					{
						startProgram = false;
						writeStringLCD("Stopping Program");
					}
					else
					{   startProgram = true;
						writeStringLCD("Starting Program");
					}					
			}
			setStopwatch3(0);
		}

		switch(startProgram)
		{
			case true:	    
				if(getStopwatch1() > 300)
				{	
					task_checkButtonChanged();
					task_readFSRRawValueAddToArray_AssignAvareFSRValue();
					cInfo.impactGram = (uint16_t)((mapPressureSensorValueToNewton()/earthAcceleration) * 1000);
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
						//saveGyroData(gData);

						setStopwatch2(0);
					}
				}
				else if(!crashInfoWasSend && pressed)
				{
					crashInfoWasSend = assignCrashInfo(cInfo);
					sendCrashInfo();
				} 
				else if(crashInfoWasSend && pressed)
				{
					stop();
				}
				break;

			case false:
				stop();
				break;
		}	
	}	
}	