/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

#include "stm32l5xx_ll_ucpd.h"
#include "stm32l5xx_ll_bus.h"
#include "stm32l5xx_ll_cortex.h"
#include "stm32l5xx_ll_rcc.h"
#include "stm32l5xx_ll_system.h"
#include "stm32l5xx_ll_utils.h"
#include "stm32l5xx_ll_pwr.h"
#include "stm32l5xx_ll_gpio.h"
#include "stm32l5xx_ll_dma.h"

#include "stm32l5xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BL_PWM_Pin GPIO_PIN_1
#define LCD_BL_PWM_GPIO_Port GPIOE
#define LED_GREEN_Pin GPIO_PIN_12
#define LED_GREEN_GPIO_Port GPIOG
#define BTN1_Pin GPIO_PIN_6
#define BTN1_GPIO_Port GPIOD
#define BTN1_EXTI_IRQn EXTI6_IRQn
#define MOT_EN_Pin GPIO_PIN_2
#define MOT_EN_GPIO_Port GPIOD
#define L3_Pin GPIO_PIN_11
#define L3_GPIO_Port GPIOC
#define L1_2_Pin GPIO_PIN_10
#define L1_2_GPIO_Port GPIOC
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define _7SEG__OE_Pin GPIO_PIN_0
#define _7SEG__OE_GPIO_Port GPIOE
#define BTN2_Pin GPIO_PIN_10
#define BTN2_GPIO_Port GPIOG
#define BTN2_EXTI_IRQn EXTI10_IRQn
#define LED_RED_Pin GPIO_PIN_3
#define LED_RED_GPIO_Port GPIOD
#define GYRO_ACC_INT_Pin GPIO_PIN_3
#define GYRO_ACC_INT_GPIO_Port GPIOF
#define GYRO_ACC_INT_EXTI_IRQn EXTI3_IRQn
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define LCD_TE_Pin GPIO_PIN_8
#define LCD_TE_GPIO_Port GPIOA
#define _7SEL1_Pin GPIO_PIN_4
#define _7SEL1_GPIO_Port GPIOF
#define LED4_Pin GPIO_PIN_7
#define LED4_GPIO_Port GPIOC
#define MOT_PWM2_Pin GPIO_PIN_9
#define MOT_PWM2_GPIO_Port GPIOC
#define MOT_PWM1_Pin GPIO_PIN_8
#define MOT_PWM1_GPIO_Port GPIOC
#define LCD_PWR_ON_Pin GPIO_PIN_0
#define LCD_PWR_ON_GPIO_Port GPIOH
#define SPI_CS_ADC_Pin GPIO_PIN_5
#define SPI_CS_ADC_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOA
#define SW2_EXTI_IRQn EXTI1_IRQn
#define ENC_B_Pin GPIO_PIN_13
#define ENC_B_GPIO_Port GPIOD
#define SW1_Pin GPIO_PIN_0
#define SW1_GPIO_Port GPIOA
#define SW1_EXTI_IRQn EXTI0_IRQn
#define SW4_Pin GPIO_PIN_5
#define SW4_GPIO_Port GPIOC
#define SW4_EXTI_IRQn EXTI5_IRQn
#define LCD_RST_Pin GPIO_PIN_14
#define LCD_RST_GPIO_Port GPIOF
#define _7SEL0_Pin GPIO_PIN_11
#define _7SEL0_GPIO_Port GPIOD
#define ENC_A_Pin GPIO_PIN_12
#define ENC_A_GPIO_Port GPIOD
#define STMOD_SEL12_Pin GPIO_PIN_11
#define STMOD_SEL12_GPIO_Port GPIOF
#define SPI_CS_TEMP_Pin GPIO_PIN_13
#define SPI_CS_TEMP_GPIO_Port GPIOB
#define UCPD_FLT_Pin GPIO_PIN_14
#define UCPD_FLT_GPIO_Port GPIOB
#define VBUS_SENSE_Pin GPIO_PIN_4
#define VBUS_SENSE_GPIO_Port GPIOA
#define STMOD_SEL34_Pin GPIO_PIN_12
#define STMOD_SEL34_GPIO_Port GPIOF
#define CTP_RST_Pin GPIO_PIN_15
#define CTP_RST_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOB
#define POTMETER_Pin GPIO_PIN_5
#define POTMETER_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_4
#define SW3_GPIO_Port GPIOC
#define SW3_EXTI_IRQn EXTI4_IRQn
#define _7SEG_LE_Pin GPIO_PIN_0
#define _7SEG_LE_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
