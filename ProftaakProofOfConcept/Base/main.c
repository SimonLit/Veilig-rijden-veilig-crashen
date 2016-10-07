/*****************************************************************************/
// Includes:

#include "RP6RobotBaseLib.h" 	
#include "RP6I2CmasterTWI.h"
#include "Drive.h"
#include "MPU9250.h"
#include "Crash.h"
#include "stdbool.h"


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

/************************************************************************************/
//====================================================================================
// Main - The program starts here:
//====================================================================================
/************************************************************************************/

int main(void)
{
	initRobotBase();
	

	I2CTWI_initMaster(100); // Initialize the TWI Module for Master operation
				// with 100kHz SCL Frequency
				// PCF8574 and PCF8591 are only specified for
				// up to 100kHz SCL freq - not 400kHz HighSpeed mode!
	
	I2CTWI_setTransmissionErrorHandler(I2C_transmissionError);
	BUMPERS_setStateChangedHandler(buttenChanged);
	
	powerON();

	initMPU9250();
	startStopwatch1();

	gyroData gData;

	bool arrayIsFilled = false;
	uint8_t counter = 0;

	setMotorDir(FWD, FWD);

	while(true)  
	{
		task_motionControl();
		task_Bumpers();
		task_I2CTWI();

		if(!pressed)
		{
			setLEDs(0b0);

			//if(arrayIsFilled)
			//{
				moveAtSpeed(60,60);
			//}

			if(getStopwatch1() > 500)
			{
				saveSpeedData(mleft_speed, mright_speed);
				saveGyroData(gData);
				
				
				/*if(!arrayIsFilled)
				{
					counter++;

					writeSpeed();
					writeGyro();

					if(counter > 10)
					{
						arrayIsFilled = true;
					}
				}*/

				setStopwatch1(0);
			}
		}
		else if(!crashInfoWasSend && pressed)
		{
			crashInfoWasSend = assignCrashInfo();
			sendCrashInfo();
		} 
	}
	return 0;
}
