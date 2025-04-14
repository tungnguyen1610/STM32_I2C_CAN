/*
 * lsm6dso.h
 *
 *  Created on: Mar 6, 2025
 *      Author: KovacsV
 */

#ifndef APP_LSM6DSO_H_
#define APP_LSM6DSO_H_



#define LSM6DSO_I2C_ADDR (0xD4)

#define LSM6DSO_REG_WHOAMI (0x0f)
#define LSM6DSO_REG_WHOAMI_VALUE (0x6c)
#define LSM6DSO_REG_CTRL1_XL (0x10)
#define LSM6DSO_REG_CTRL2_G (0x11)
#define LSM6DSO_REG_OUT_TEMP_L (0x20)
#define LSM6DSO_REG_OUT_TEMP_H (0x21)
#define LSM6DSO_REG_OUTX_L_G (0x22)
#define LSM6DSO_REG_OUTX_L_A (0x28)

#define LSM6DSO_REG_CTRL1_XL_2G (0b00000000)
#define LSM6DSO_REG_CTRL1_XL_16G (0b00000100)
#define LSM6DSO_REG_CTRL1_XL_4G (0b00001000)
#define LSM6DSO_REG_CTRL1_XL_8G (0b00001100)
#define LSM6DSO_REG_CTRL1_XL_FREQ_0HZ (0b00000000)
#define LSM6DSO_REG_CTRL1_XL_FREQ_12_5HZ (0b00010000)
#define LSM6DSO_REG_CTRL1_XL_FREQ_104HZ (0b01000000)

#define LSM6DSO_REG_CTRL2_G_FREQ_104HZ (0b01000000)
#define LSM6DSO_REG_CTRL2_G_500DPS (0b00000100)

typedef struct {
	float Accelero_X;
	float Accelero_Y;
	float Accelero_Z;
	float Gyro_X;
	float Gyro_Y;
	float Gyro_Z;
} LSM6DSOData_t;

uint8_t LSM6DSO_Init();
uint8_t LSM6DSO_Update(LSM6DSOData_t* pData);
uint8_t LSM6DSO_IsDeviceReady();

#endif /* APP_LSM6DSO_H_ */
