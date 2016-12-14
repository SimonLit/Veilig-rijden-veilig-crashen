#include "RP6ControlLib.h"
#include "RP6I2CmasterTWI.h"
#include "RP6Control_I2CMasterLib.h" 	
#include "ProtocolDefines.h"
#include "Tools.h"
#include "SerialReader.h"
#include "InterpretSerial.h"
#include "Drive.h"
#include "Crash.h"
#include <stdint.h>

typedef enum
{
	DISCONNECTED,
	CONNECTED
} connection;

typedef enum
{
	STARTED_PROGRAM,
	STOPPED_PROGRAM
} stateRP6;

connection RP6ToWemosConnection = DISCONNECTED;
stateRP6 RP6State = STOPPED_PROGRAM;

long lastControllerValueReceived = 0;
long lastHeartbeatRequestReceived = 0;
int maxTimeout = 200;

// Show the speed of the tires on the LCD.
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
	BUMPERS_setStateChangedHandler(buttenChanged); // Assign the bumper event to the function from Crash.h

	// Initialize the following bits on ports to inputs.	
	DDRC &= ~IO_PC2; // Right button	
	DDRC &= ~IO_PC3; // Left button	
	DDRC &= ~IO_PC5; // Back button
	DDRA &= ~ADC5; 	// Force Sensitive Resistor (FSR)

	crashInfo cInfo; // This is used to store te crash variables.

	char receiveBufferCommand[20];
	char receiveBufferValue[20];
	const int sizeOfCommandBuffer = sizeof(receiveBufferCommand); // 
	const int sizeOfValueBuffer = sizeof(receiveBufferValue);     // There two sizes include '\0'.

	// Clear the buffers to make sure the you are working with a clean buffer.
	memset(receiveBufferCommand, 0,  sizeOfCommandBuffer);
	memset(receiveBufferValue, 0,  sizeOfValueBuffer);

	// Set the distance values of the RP6 to 0;
	// When crashed the distence driven is measured.
	mleft_dist = 0;
	mright_dist = 0;

	startStopwatch1(); // Timer for checking button state and measuring the FSR.
	startStopwatch2(); // Timer for getting all the sensor data from the RP6 base board.
	startStopwatch3(); // TImer for checking the start/stop program button.
	startStopwatch4();

	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_ACS_POWER, ACS_PWR_MED); // Setup ACS power	
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT, true); // Enable Watchdog for Interrupt requests	
	I2CTWI_transmit3Bytes(I2C_RP6_BASE_ADR, 0, CMD_SET_WDT_RQ, true); // Enable timed watchdog requests

	changeDirection(FWD); // Initial driving direction.

	uint8_t pressedButton = 0;

	//====================================================================================
	// Main loop program
	//====================================================================================
	while(true)
	{
		task_checkINT0();
		task_I2CTWI();

		switch(RP6ToWemosConnection)
		{	
			// Wait for a connect request from the wemos.
			case DISCONNECTED:
				if(getIncomingSerialMessage(receiveBufferCommand, receiveBufferValue, sizeOfCommandBuffer, sizeOfValueBuffer) == 0)
				{
					if(waitForConnectRequest(receiveBufferCommand) == 0)
					{
						RP6ToWemosConnection = CONNECTED;
					}
				}
				break;

			// Exchange data with the wemos.
			case CONNECTED:
				// Check start/stop program button.
				pressedButton = checkReleasedKeyEvent();

				if(startStopwatch3() > 50)
				{		
					switch(pressedButton)
					{
						case 1:
							writeInteger(pressedButton, DEC);
							writeChar('\n');
							clearLCD();

							switch(RP6State)
							{
								case STARTED_PROGRAM:
									RP6State = STOPPED_PROGRAM;
									break;
								case STOPPED_PROGRAM:
									RP6State = STARTED_PROGRAM;
									break;
							}					
					}
					setStopwatch3(0);
				}

				// If the program is started.
				switch(RP6State)
				{
					case STARTED_PROGRAM:	
						task_checkButtonChanged();

						// Check if one of our self added buttons was pressed.
						// Read the FSR value, convert it to grams and add it to the crashInfo struct.
		 				if(getStopwatch1() > 5)
						{	
							if(getIncomingSerialMessage(receiveBufferCommand, receiveBufferValue, sizeOfCommandBuffer, sizeOfValueBuffer) == 0)
							{
								interpretMessageForSpeedValues(receiveBufferCommand, receiveBufferValue, sizeOfCommandBuffer, 
																						  sizeOfValueBuffer, &baseSpeed, &rightSpeed, &leftSpeed);

							}
							
							setStopwatch1(0);
						}

						if(!pressed)
						{
							
							drive();

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
					case STOPPED_PROGRAM:
						stop();
						break;
				}
				break;	
		}
	}	
}	
