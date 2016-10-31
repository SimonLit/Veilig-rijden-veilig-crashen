#include "MPU9250.h"
#include "RP6uart.h"
#include "Stopwatch.h"
#include "RP6I2CmasterTWI.h"
#include <stdbool.h>
#include "Stopwatch.h"

//====================================================================================
// MPU-9250 gryoscope
//====================================================================================

#define MPU9250_DEVICE_ADDRESS (0x68)
#define MPU9250_WRITE_ADDRESS (MPU9250_DEVICE_ADDRESS << 1)
#define MPU9250_READ_ADDRESS (MPU9250_WRITE_ADDRESS + 1)

uint8_t gyroArraySize = 15;
uint8_t gyroArrayIndexToWriteTo = 0;
gyroData gDataArray[15];

bool doneReadingGyro = false;

void initMPU9250(void)
{
	I2CTWI_transmit2Bytes(MPU9250_WRITE_ADDRESS, 0x4B, 0);
}

void getGyroData(gyroData* gData) 
{
	// Read gryo data from the X-ax
	I2CTWI_transmitByte(MPU9250_WRITE_ADDRESS, 0x43);
	gData->GyroX_H = I2CTWI_readByte(MPU9250_READ_ADDRESS);
	I2CTWI_transmitByte(MPU9250_WRITE_ADDRESS, 0x44);
	gData->GyroX_L = I2CTWI_readByte(MPU9250_READ_ADDRESS);

	// Read gryo data from the Y-ax
	I2CTWI_transmitByte(MPU9250_WRITE_ADDRESS, 0x45);
	gData->GyroY_H = I2CTWI_readByte(MPU9250_READ_ADDRESS);
	I2CTWI_transmitByte(MPU9250_WRITE_ADDRESS, 0x46);
	gData->GyroY_L = I2CTWI_readByte(MPU9250_READ_ADDRESS);

	// Read gryo data from the Z-ax
	I2CTWI_transmitByte(MPU9250_WRITE_ADDRESS, 0x47);
	gData->GyroZ_H = I2CTWI_readByte(MPU9250_READ_ADDRESS);
	I2CTWI_transmitByte(MPU9250_WRITE_ADDRESS, 0x48);
	gData->GyroZ_L = I2CTWI_readByte(MPU9250_READ_ADDRESS);

	doneReadingGyro = true;
}

void saveGyroData(gyroData gData)
{

	startStopwatch1();
	getGyroData(&gData);
	gDataArray[gyroArrayIndexToWriteTo] = gData;
	gyroArrayIndexToWriteTo++;


	if(gyroArrayIndexToWriteTo == gyroArraySize)
	{
		gyroArrayIndexToWriteTo = 0;
	}

	setStopwatch1(0);

	if(doneReadingGyro)
	{
		getGyroData(&gData);

		int arraySize = sizeof(gDataArray)/sizeof(gDataArray[0]);

		for (int i = 0; i < (arraySize - 1); i++)
		{
			gDataArray[i] = gDataArray[i + 1];
		}

		gDataArray[arraySize - 1] = gData;
	}	
	
	doneReadingGyro = false;
}

void writeGyro(void)
{

	writeString("Index ");
	if(gyroArrayIndexToWriteTo != 0)
	{
		writeInteger((gyroArrayIndexToWriteTo -1), DEC);
	}
	else
	{
		writeInteger(0, DEC);
	}
	writeString(" changed.");
	writeChar('\n');

	for(uint8_t index = 0; index < gyroArraySize; index++)
	{	
		writeString("Gyro: ");
		writeInteger(index, DEC);
		writeString(" X: ");
		writeInteger(((gDataArray[index].GyroX_H << 8) | gDataArray[index].GyroX_L), DEC);

		writeString(" Gyro: ");
		writeInteger(index, DEC);
		writeString(" Y: ");
		writeInteger(((gDataArray[index].GyroY_H << 8) | gDataArray[index].GyroY_L), DEC);

		writeString(" Gyro: ");
		writeInteger(index, DEC);
		writeString(" Z: ");
		writeInteger(((gDataArray[index].GyroZ_H << 8) | gDataArray[index].GyroZ_L), DEC);

		writeChar('\n');
	}

	writeChar('\n');
	writeChar('\n');
}