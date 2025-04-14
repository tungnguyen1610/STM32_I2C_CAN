/*
 * IMU.c
 *
 *  Created on: Mar 30, 2025
 *      Author: KovacsV
 */

#include "main.h"
#include "lsm6dso.h"
#include "IMU.h"


uint32_t _lastUpdateTime=0;
float _calibX=0;
float _calibY=0;
float _calibZ=0;


uint8_t IMU_Init(){
	uint8_t ok=LSM6DSO_Init();
	return ok;
}

uint8_t IMU_CalibrateGyro(uint32_t time){
	if (LSM6DSO_IsDeviceReady()==0){return 0;}

	uint32_t nexttime=HAL_GetTick();
	uint32_t endtime=nexttime+time;

	float sumx=0;
	float sumy=0;
	float sumz=0;
	int count=0;

	while(1){
		uint32_t t=HAL_GetTick();
		if (t>endtime) break;
		if (t<nexttime) continue;
		nexttime=t+10;

		LSM6DSOData_t data;
		if (LSM6DSO_Update(&data)){
			sumx+=data.Gyro_X;
			sumy+=data.Gyro_Y;
			sumz+=data.Gyro_Z;
			count++;
		}

	}

	_calibX=sumx/count;
	_calibY=sumy/count;
	_calibZ=sumz/count;
	return 1;
}

uint8_t IMU_Update(IMUData_t* pData){
	if (LSM6DSO_IsDeviceReady()==0) return 0;

	uint32_t time=HAL_GetTick();
	if (time-_lastUpdateTime<IMU_UPDATE_PERIOD_MS) {return 0;}

	LSM6DSOData_t data;
	if (LSM6DSO_Update(&data)==0) return 0;

	pData->Accelero_X=data.Accelero_X;
	pData->Accelero_Y=data.Accelero_Y;
	pData->Accelero_Z=data.Accelero_Z;

	pData->Gyro_X=data.Gyro_X-_calibX;
	pData->Gyro_Y=data.Gyro_Y-_calibY;
	pData->Gyro_Z=data.Gyro_Z-_calibZ;

	_lastUpdateTime=time;
	return 1;

}
