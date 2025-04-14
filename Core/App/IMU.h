/*
 * IMU.h
 *
 *  Created on: Mar 30, 2025
 *      Author: KovacsV
 */

#ifndef APP_IMU_H_
#define APP_IMU_H_

#define IMU_UPDATE_PERIOD_MS (50)

typedef struct {
	float Accelero_X;
	float Accelero_Y;
	float Accelero_Z;
	float Gyro_X;
	float Gyro_Y;
	float Gyro_Z;
} IMUData_t;

uint8_t IMU_Init();
uint8_t IMU_Update(IMUData_t* pData);
uint8_t IMU_CalibrateGyro(uint32_t time);

#endif /* APP_IMU_H_ */
