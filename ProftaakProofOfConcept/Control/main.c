#include "RP6ControlLib.h"
#include "RP6I2CmasterTWI.h"
/*#include "Drive.h"
#include "MPU9250.h"
#include "Crash.h"*/

#include "RP6Control_I2CMasterLib.h" 	

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


void writePressedButton(uint8_t side, uint8_t times)
{
	clearLCD();
	setCursorPosLCD(0, 0);
	writeStringLCD("btn:   times:");
	setCursorPosLCD(1, 0);
	writeIntegerLCD(side, DEC);
	writeStringLCD("      ");
	writeIntegerLCD(times, DEC);
}

int main(void)
{
	initRP6Control(); 	

	WDT_setRequestHandler(watchDogRequest); 

	uint8_t sideHit = 0;
	uint8_t timesPressed2 = 0;
	uint8_t timesPressed3 = 0;
	uint8_t timesPressed5 = 0;
	
	DDRC &= ~IO_PC2; 
	PORTC &= ~IO_PC2;

	DDRC &= ~IO_PC3; 
	PORTC &= ~IO_PC3; 

	DDRC &= ~IO_PC5; 
	PORTC &= ~IO_PC5;

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

	int lastButton2State = false;
	int lastButton3State = false;
	int lastButton5State = false;

	startStopwatch1();

	while(true)
	{
		if(getStopwatch1() > 50)
		{
			if((PINC & IO_PC2) !=  lastButton2State)
			{
				if(PINC & IO_PC2)
				{
					sideHit = 2;
					timesPressed2++;
					writePressedButton(sideHit, timesPressed2);

					writeString("Button 2 pressed ");
					writeInteger(timesPressed2, DEC);
					writeString(" times.");
					writeString("\n");
				}
			}	

			lastButton2State = PINC & IO_PC2;


			if((PINC & IO_PC3) !=  lastButton3State)
			{
				if(PINC & IO_PC3)
				{
					sideHit = 3;
					timesPressed3++;

					writePressedButton(sideHit, timesPressed3);

					writeString("Button 3 pressed ");
					writeInteger(timesPressed3, DEC);
					writeString(" times.");
					writeString("\n");
				}
			}	

			lastButton3State = PINC & IO_PC3;


			if((PINC & IO_PC5) !=  lastButton5State)
			{
				if(PINC & IO_PC5)
				{
					sideHit = 5;
					timesPressed5++;
					writePressedButton(sideHit, timesPressed5);
					writeString("Button 5 pressed ");
					writeInteger(timesPressed5, DEC);
					writeString(" times.");
					writeString("\n");
				}
			}	

			lastButton5State = PINC & IO_PC5;
			setStopwatch1(0);
		}

	}	
}