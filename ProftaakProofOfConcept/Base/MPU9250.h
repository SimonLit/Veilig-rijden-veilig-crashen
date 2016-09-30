#ifndef MPU9250_H
#define MPU9250_H

#include <stdint.h>

typedef struct 
{
	uint16_t GyroX;
	uint16_t GyroY;
	uint16_t GyroZ;
}gyroData;


void initMPU9250(void);

void getGyroData(gyroData *gData);

void saveGyroData(gyroData gData);

void writeGyro(void);

#endif