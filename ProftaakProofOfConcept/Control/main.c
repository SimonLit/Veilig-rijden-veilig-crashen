#include "RP6ControlLib.h"
#include "RP6I2CmasterTWI.h"
#include "Drive.h"
#include "Crash.h"
#include <stdbool.h>
#include "RP6Control_I2CMasterLib.h" 	

//#define DEBUG

uint8_t lastButton2State = false;
uint8_t lastButton3State = false;
uint8_t lastButton5State = false;

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

int16_t map(int16_t valueToMap, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
	return (valueToMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t mapPressureSensorValueToNewton(void)
{
	// The sensitivity actualy ranges from 0.2 to 20 instead of 0 - 20.
	// But because this is such a small difference it is much more convenient
	// To avoid the use of decimal numbers. 
	return map(readADC(ADC_5), 0, 1023, 0, 20); 
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

	mleft_dist = 0;
	mright_dist = 0;

	DDRC &= ~IO_PC2; // Right button
	DDRC &= ~IO_PC3; // Left button
	DDRC &= ~IO_PC5; // Back button

	DDRA &= ~ADC5; // Force Sensitive Resistor (FSR)

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

	

	startStopwatch1(); // Timer for checking button state and measuring the FSR.
	startStopwatch2(); // Timer for getting all the sensor data from the RP6 base board.
	startStopwatch3(); // TImer for checking the start/stop program button.

	// Setup ACS power:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_ACS_POWER, ACS_PWR_MED);
	// Enable Watchdog for Interrupt requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT, true);
	// Enable timed watchdog requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT_RQ, true);
	
	BUMPERS_setStateChangedHandler(buttenChanged); // Assign the bumper event to the function from Crash.h.

	crashInfo cInfo;

	float earthAcceleration = 9.81; // Used for the converting from Newton to grams.

	changeDirection(FWD);
	bool startProgram = false;

	while(true)
	{
		task_checkINT0();
		task_I2CTWI();

		// Check start/stop program button.
		uint8_t pressedButton = checkReleasedKeyEvent();

		if(startStopwatch3() > 50)
		{		
			switch(pressedButton)
			{
				case 1:
					writeInteger(pressedButton, DEC);
					writeChar('\n');
					clearLCD();

					// Set the startProgram value to indecate if the RP6 should do anything.
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

		// If the program is started.
		switch(startProgram)
		{
			case true:	

				// Check if one of our self added buttons was pressed.
				// Read the FSR value, convert it to grams and add it to the crashInfo struct.
 				if(getStopwatch1() > 300)
				{	
					task_checkButtonChanged();
					cInfo.impactGram = (mapPressureSensorValueToNewton()/earthAcceleration) * 1000;

					setStopwatch1(0);
				}

				if(!pressed)
				{
					setLEDs(0b0);

					moveAtSpeed(60,60);

					// Update the variables representing the values of the base board sensors.
					// Add the current speed values to an array as one speedData struct value.
					if(getStopwatch2() > 500)
					{
						getAllSensors();
						saveSpeedData(mleft_speed, mright_speed);

						setStopwatch2(0);
					}
				}

				// One of the (self added) bumpers was pressed but the data wasn't formatted and 
				// assigned to the crashInfo struct yet
				//
				// In that case, format and assign all the data and send it over Serial.
				else if(!crashInfoWasSend && pressed)
				{
					crashInfoWasSend = assignCrashInfo(cInfo);
					sendCrashInfo();
				} 

				// If the crash data is assigned and send stop the driving of the RP6.
				else if(crashInfoWasSend && pressed)
				{
					stop();
				}
				break;

			// If the program isn't started or the program was stopped/paused, 
			// Let the RP6 don't do anything.
			case false:
				stop();
				break;
		}	
	}	
}	