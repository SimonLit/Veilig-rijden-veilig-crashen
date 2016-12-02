#include "RP6ControlLib.h"
#include "RP6I2CmasterTWI.h"
#include "Drive.h"
#include "Crash.h"
#include "Serial.h"
#include "stdint.h"
#include "RP6Control_I2CMasterLib.h" 	

int baseSpeed = 0;
uint8_t rightSpeed = 0;
uint8_t leftSpeed = 0;

void writeSpeedOnLCD(char* buffer, int rightSpeed, int leftSpeed)
{
	clearLCD();
	setCursorPosLCD(0,0);
	writeStringLCD("Rs      Ls      ");
	setCursorPosLCD(1,0);
	writeIntegerLCD(rightSpeed, DEC);
	setCursorPosLCD(1,8);
	writeIntegerLCD(leftSpeed, DEC);
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

	// Set the distance values of the RP6 to 0;
	// When being crashed the distence driven is measured.
	mleft_dist = 0;
	mright_dist = 0;

	// Right button
	DDRC &= ~IO_PC2;
	// Left button
	DDRC &= ~IO_PC3; 
	// Back button
	DDRC &= ~IO_PC5; 
	// Force Sensitive Resistor (FSR)
	DDRA &= ~ADC5; 	

	startStopwatch1(); // Timer for checking button state and measuring the FSR.
	startStopwatch2(); // Timer for getting all the sensor data from the RP6 base board.
	startStopwatch3(); // TImer for checking the start/stop program button.
	startStopwatch4();

	// Setup ACS power:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_ACS_POWER, ACS_PWR_MED);
	// Enable Watchdog for Interrupt requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT, true);
	// Enable timed watchdog requests:
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT_RQ, true);
	
	// Assign the bumper event to the function from Crash.h.
	BUMPERS_setStateChangedHandler(buttenChanged); 

	crashInfo cInfo;

	const int maxRecieveCommandBufferLength = 6;
	const int maxRecieveValueBufferLength = 5;
	char receivBufferCommand[maxRecieveCommandBufferLength];
	char receivBufferValue[maxRecieveValueBufferLength];

	memset(receivBufferCommand, 0, maxRecieveCommandBufferLength);
	memset(receivBufferValue, 0, maxRecieveValueBufferLength);

	// User to inidcate if program runs or not.
	uint8_t startProgram = 1;

	// Initial driving direction.
	changeDirection(FWD);

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
						writeString("#STOPPING_PROGRAM");
						writeChar('%');
						writeStringLCD("Stopping Program");
					}
					else
					{   startProgram = true;
						writeString("#STARTING_PROGRAM");
						writeChar('%');
						writeStringLCD("Starting Program");
					}					
			}
			setStopwatch3(0);
		}

		// If the program is started.
		switch(startProgram)
		{
			case true:	
				task_checkButtonChanged();

				// Check if one of our self added buttons was pressed.
				// Read the FSR value, convert it to grams and add it to the crashInfo struct.
 				if(getStopwatch1() > 5)
				{	
					if(getRCProtocolValuesToDrive(receivBufferCommand, receivBufferValue, maxRecieveCommandBufferLength, maxRecieveValueBufferLength) == 0)
					{
						int receivedMessageValid = interpretMessage(receivBufferCommand, receivBufferValue, maxRecieveCommandBufferLength, maxRecieveValueBufferLength, &baseSpeed, &rightSpeed, &leftSpeed);

						if(receivedMessageValid = 0)
						{
							writeString("#ACK");
							writeChar('%');
						}
						else if(receivedMessageValid == 1)
						{
							//sendCrashInfo(&cInfo);
						}
						else
						{
							writeString("#NACK");
							writeChar('%');
						}

						if(leftSpeed > 150)
						{
							leftSpeed = 150;
						}

						if(rightSpeed > 150)
						{
							rightSpeed = 150;
						}
					}

					writeSpeedOnLCD(receivBufferCommand, leftSpeed, rightSpeed);

					setStopwatch1(0);
				}

				if(!pressed)
				{
					if(baseSpeed < 0)
					{
						changeDirection(BWD);
					}
					else
					{
						changeDirection(FWD);
					}

					moveAtSpeed(leftSpeed, rightSpeed);

					// Update the variables representing the values of the base board sensors.
					// Add the current speed values to an array as one speedData struct value.
					if(getStopwatch2() > 500)
					{
						getAllSensors();
						saveSpeedData();

						setStopwatch2(0);
					}
				}

				// One of the (self added) bumpers was pressed but the data wasn't formatted and 
				// assigned to the crashInfo struct yet
				//
				// In that case, format and assign all the data and send it over Serial.
				else if(!crashInfoWasSend && pressed)
				{
					crashInfoWasSend = assignCrashInfo(&cInfo);
					sendCrashInfo(&cInfo);
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
