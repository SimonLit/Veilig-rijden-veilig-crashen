#include "Crash.h"
#include "Drive.h"
#include "MPU9250.h"
#include "RP6I2CmasterTWI.h"
#include "RP6uart.h"
//#include "Leds.h"
#include <stdbool.h>

//====================================================================================
// Crash
//====================================================================================

#define ARDUINO_DEVICE_ADDRESS (42)
#define ARDUINO_WRITE_ADDRESS (ARDUINO_DEVICE_ADDRESS << 1)
#define ARDUINO_READ_ADDRESS (ARDUINO_WRITE_ADDRESS + 1)

struct crashInfo crashInfoToSend;
uint8_t pressed = false;
uint8_t crashInfoWasSend = false;
uint8_t hitSide;

int assignCrashInfo(void)
{
	uint16_t avergeLeftSpeed = calculateAverageLeftSpeed();
	uint16_t avergeRightSpeed = calculateAverageRightSpeed();
	uint16_t averageSpeed = (avergeLeftSpeed + avergeRightSpeed)/2;
	double speedCMPerSecond = averageSpeed * 5 * 0.025; // By multiplying the speed by 5
													    // you get the amount of segments past
														// on the encoder per second. 
													    // Each segment is +/- 0.25mm. So by 
														// multiplying is by 0.025cm you get the 
														// amount of cm/s.

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
	writeChar('\n');
	writeChar('\n');

	crashInfoToSend.speed = speedCMPerSecond;
	crashInfoToSend.sideHit = hitSide;
	crashInfoToSend.impact = 1;

	writeString("GyX: ");
	writeInteger(((gDataArray[14].GyroX_H << 8) | gDataArray[14].GyroX_L), DEC);
	writeChar('\n');
	writeChar('\n');
	writeString("GyY: ");
	writeInteger(((gDataArray[14].GyroY_H << 8) | gDataArray[14].GyroY_L), DEC);
	writeChar('\n');
	writeChar('\n');
	writeString("GyZ: ");
	writeInteger(((gDataArray[14].GyroZ_H << 8) | gDataArray[14].GyroZ_L), DEC);
	writeChar('\n');
	writeChar('\n');


	return true;
}

void sendCrashInfo(void)
{
	writeString("SENDING TO ARDUINO");
	I2CTWI_transmit2Bytes(ARDUINO_WRITE_ADDRESS, 1, crashInfoToSend.speed); // In cm/s
	I2CTWI_transmit3Bytes(ARDUINO_WRITE_ADDRESS, 2, gDataArray[14].GyroX_H, gDataArray[14].GyroX_L);
	I2CTWI_transmit3Bytes(ARDUINO_WRITE_ADDRESS, 3, gDataArray[14].GyroY_H, gDataArray[14].GyroY_L);
	I2CTWI_transmit3Bytes(ARDUINO_WRITE_ADDRESS, 4, gDataArray[14].GyroZ_H, gDataArray[14].GyroZ_L);
	I2CTWI_transmit2Bytes(ARDUINO_WRITE_ADDRESS, 5, crashInfoToSend.sideHit); 	// 1: fromt
																				// 2: right
																				// 3: left
																				// 4: back	

	I2CTWI_transmit2Bytes(ARDUINO_WRITE_ADDRESS, 6, crashInfoToSend.impact);
}



void buttenChanged(void)
{
	stop();

	if(!pressed)
	{
	 	if(getBumperLeft() || getBumperRight())
	 		hitSide = 1;
	 	/*else if(getBumperRightSide(12))
	 		hitSide = 2;
	 	else if(getBumperLeftSide(12))
	 		hitSide = 3;
	 	else if(getBumperBack(12))
	 		hitSide = 4;*/

		setLEDs(0b1111);
		pressed = true;

		writeSpeed();
		writeGyro();
	}
	else if(pressed)
	{
		pressed = false;
		crashInfoWasSend = false;
	}
}