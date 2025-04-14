/*
 * lsm6dso.c
 *
 *  Created on: Mar 6, 2025
 *      Author: KovacsV
 */
#include "main.h"
#include "lsm6dso.h"

// TODO 1.1
// Uncomment the declaration of the handle
 extern I2C_HandleTypeDef hi2c1;


uint8_t _deviceReady=0;

uint8_t LSM6DSO_IsDeviceReady(){
	return _deviceReady;
}

uint8_t LSM6DSO_Init(){
	uint8_t id=0;
	HAL_StatusTypeDef status;
	// TODO 1.1
	// Read the ID (WHO_AM_I) register content (HAL_I2C_Mem_Read)
	// Compare it with the value of LSM6DSO_REG_WHOAMI_VALUE
	// If the two don't match or the transaction status is not HAL_OK, return an error
	uint8_t address = 0;
	status = HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_I2C_ADDR, LSM6DSO_REG_WHOAMI, 1, &address, 1,
	10);
	if (address != LSM6DSO_REG_WHOAMI_VALUE || status != HAL_OK) {
	return 0;
	}
	// Set the LSM6DSO_REG_CTRL1_XL register as follows:
	// Set the accelerometer sampling frequency to 12.5Hz LSM6DSO_REG_CTRL1_XL_FREQ_12_5HZ
	// Set the full scale to ±2G LSM6DSO_REG_CTRL1_XL_2G
	// using HAL_I2C_Mem_Write()
	// If an error occurs, return 0
	uint8_t accel_reg = LSM6DSO_REG_CTRL1_XL_FREQ_12_5HZ | LSM6DSO_REG_CTRL1_XL_2G;
	status = HAL_I2C_Mem_Write(&hi2c1, LSM6DSO_I2C_ADDR, LSM6DSO_REG_CTRL1_XL, 1, &accel_reg,
	1, 10);
	if (status != HAL_OK) {
	return 0;
	}
	// Set the LSM6DSO_REG_CTRL2_G register as follows:
	// Set the gyroscope sampling frequency to 104Hz LSM6DSO_REG_CTRL2_G_FREQ_104HZ
	// Set the full scale to ±500dps (degrees per second) LSM6DSO_REG_CTRL2_G_500DPS
	// using HAL_I2C_Mem_Write()
	// If an error occurs, return 0
	uint8_t gyro_reg = LSM6DSO_REG_CTRL2_G_FREQ_104HZ | LSM6DSO_REG_CTRL2_G_500DPS;
	status = HAL_I2C_Mem_Write(&hi2c1, LSM6DSO_I2C_ADDR, LSM6DSO_REG_CTRL2_G, 1, &gyro_reg, 1,
	10);
	if (status != HAL_OK) {
	return 0;
	}
	// If no errors, set _deviceReady to 1 and return 1!
	_deviceReady = 1;
	return 1;
	}
	uint8_t LSM6DSO_Update(LSM6DSOData_t* pData){
	if (_deviceReady==0){return 0;}
	if (pData==NULL) {return 0;}
	HAL_StatusTypeDef status;
	// TODO 1.2
	// Read the current accelerometer values!
	// The data starts from the LSM6DSO_REG_OUTX_L_A address, 3x16bit! The the byte order is LSB, so you
	can use int16_t!
	// Scale the data according to the previous settings, i.e., full scale ±2G -> 4G is represented by 65536 LSB
	steps
	// Convert the values to float type! Store them in pData!
	// If there is an error, return 0!
	int16_t accel_value[3];
	status = HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_I2C_ADDR, LSM6DSO_REG_OUTX_L_A, 1, accel_value,
	6, 10);
	if (status != HAL_OK) {
	return 0;
	}
	pData->Accelero_X = accel_value[0] / 65536.0f * 4;
	pData->Accelero_Y = accel_value[1] / 65536.0f * 4;
	pData->Accelero_Z = accel_value[2] / 65536.0f * 4;
	// Read the current gyroscope values!
	// The data starts from the LSM6DSO_REG_OUTX_L_G address, 3x16bit! The the byte order is LSB, so you
	can use int16_t!
	// Scale the data according to the previous settings, i.e., full scale ±500 dps -> 1000dps is represented by
	65536 LSB steps
	// Convert the values to float type! Store them in pData!
	// If there is an error, return 0!
	int16_t gyro_value[3];
	status = HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_I2C_ADDR, LSM6DSO_REG_OUTX_L_G, 1, gyro_value,
	6, 10);
	if (status != HAL_OK) {
	return 0;
	}
	pData->Gyro_X = gyro_value[0] / 65536.0f * 1000;
	pData->Gyro_Y = gyro_value[1] / 65536.0f * 1000;
	pData->Gyro_Z = gyro_value[2] / 65536.0f * 1000;
	return 1;
	}