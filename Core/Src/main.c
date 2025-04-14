/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "icache.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "ucpd.h"
#include "usb_device.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SevenSegment.h"
#include "IMU.h"
#include "Log.h"
#include "CanCommunication.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t _btn1State=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_FMC_Init();
  MX_ICACHE_Init();
  MX_LPUART1_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_UCPD1_Init();
  MX_SPI3_Init();
  MX_TIM3_Init();
  MX_ADC2_Init();
  MX_USB_Device_Init();
  /* USER CODE BEGIN 2 */

  // TODO 2.2
  // Create a deviceId variable and store the states of switches SW1 and SW2 in the lower two bits.
  uint8_t switch1=HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin);
  uint8_t switch2=HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin);
  uint8_t deviceId = switch1 | (switch2<<1);
  Log_Init(1);

  // TODO 1.3
  // Call IMU_Init() function!
  IMU_Init();


  // TODO 1.4
  // Call the IMU calibration function, e.g., with a 1000ms delay: IMU_CalibrateGyro()
  // Check if the gyroscope measurement data has improved!
  IMU_CalibrateGyro(1000);

  // TODO 2.1
  // Call CanCommunication_Init() function!
  CanCommunication_Init(deviceId);
  Log("\r\nHello STM32 kommunikacio!\r\n");

  SevenSegment_Init();

  /* USER CODE END 2 */
  IMUData_t current_measurement;
  uint8_t prevState=0;
  uint8_t curState;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 // TODO 1.3
	 // Declare a structure instance for the IMU data: IMUData_t
	 // Try to update the IMU data
	 // If successful, write the acceleration and angular velocity data as text into a char[]!
	 // Convert the float type to int, scale the data, e.g., by 1000 times
	 // Write the data via Log() to the debugger UART, check the data
  if (IMU_Update(&current_measurement)) {
  char buffer[100];
  int accel_x = (int)(current_measurement.Accelero_X * 1000);
  int accel_y = (int)(current_measurement.Accelero_Y * 1000);
  int accel_z = (int)(current_measurement.Accelero_Z * 1000);
  int gyro_x = (int)(current_measurement.Gyro_X * 1000);
  int gyro_y = (int)(current_measurement.Gyro_Y * 1000);
  int gyro_z = (int)(current_measurement.Gyro_Z * 1000);
  sprintf(buffer, "Ax: %d Ay: %d Az: %d Gx: %d Gy: %d Gz: %d \r\n", accel_x,
  accel_y,accel_z,gyro_x, gyro_y, gyro_z);
  Log(buffer);
  }

  AppCanMessage_t msg;
  char buffer2[100];
  if (CanCommunication_Receive(0,&msg))
  {
  sprintf(buffer2,"MessageID:%x",msg.Id);
  Log(buffer2);
  SevenSegment_UpdateValueHex(msg.Id);
  }
  // TODO 2.3
  // Check for the BTN1 button press, on the rising edge:
  // Use an AppCanMessage_t instance,
  // Set the ID to 0x010 and copy the device ID into the lower 2 bits
  // Write the state of the switches into the lower 4 bits of the data
  // Send the message using the CanCommunication_Send function.
  curState=HAL_GPIO_ReadPin(BTN1_GPIO_Port,BTN1_Pin);
  AppCanMessage_t send_msg;
  if (prevState==0 && curState)
  {
  send_msg.Id=0x010 | deviceID;
  uint8_t sw1=HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin);
  uint8_t sw2=HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin);
  uint8_t sw3=HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin);
  uint8_t sw4=HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin);
  send_msg.Message= (sw1<<3)|(sw2<<2)|(sw3<<1)|(sw4<<0);
  CanCommunication_Send(&send_msg);
  }
  prevState=curState;
  CanCommunication_Loop();
  SevenSegment_Loop();

  }
}
  
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 55;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
