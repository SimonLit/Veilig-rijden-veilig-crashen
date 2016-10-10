#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>

typedef struct 
{
	int8_t GyroX_H;
	int8_t GyroX_L;
	int8_t GyroY_H;
	int8_t GyroY_L;
	int8_t GyroZ_H;
	int8_t GyroZ_L;
}gyroData;



extern gyroData gDataArray[15];


void initMPU9250(void);

void getGyroData(gyroData *gData);

void saveGyroData(gyroData gData);

void writeGyro(void);

#endif