/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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
#define SWITCH_D_LED_Pin GPIO_PIN_13
#define SWITCH_D_LED_GPIO_Port GPIOC
#define SWITCH_D_Pin GPIO_PIN_14
#define SWITCH_D_GPIO_Port GPIOC
#define SWITCH_D_EXTI_IRQn EXTI4_15_IRQn
#define SWITCH_A_LED_Pin GPIO_PIN_0
#define SWITCH_A_LED_GPIO_Port GPIOA
#define SWITCH_A_Pin GPIO_PIN_1
#define SWITCH_A_GPIO_Port GPIOA
#define SWITCH_A_EXTI_IRQn EXTI0_1_IRQn
#define SWITCH_B_LED_Pin GPIO_PIN_2
#define SWITCH_B_LED_GPIO_Port GPIOA
#define SWITCH_B_Pin GPIO_PIN_3
#define SWITCH_B_GPIO_Port GPIOA
#define SWITCH_B_EXTI_IRQn EXTI2_3_IRQn
#define SWITCH_C_LED_Pin GPIO_PIN_4
#define SWITCH_C_LED_GPIO_Port GPIOA
#define SWITCH_C_Pin GPIO_PIN_5
#define SWITCH_C_GPIO_Port GPIOA
#define SWITCH_C_EXTI_IRQn EXTI4_15_IRQn
#define KNOB_SWITCH_Pin GPIO_PIN_6
#define KNOB_SWITCH_GPIO_Port GPIOA
#define KNOB_SWITCH_EXTI_IRQn EXTI4_15_IRQn
#define KNOB_B_Pin GPIO_PIN_7
#define KNOB_B_GPIO_Port GPIOA
#define KNOB_B_EXTI_IRQn EXTI4_15_IRQn
#define KNOB_A_Pin GPIO_PIN_0
#define KNOB_A_GPIO_Port GPIOB
#define KNOB_A_EXTI_IRQn EXTI0_1_IRQn
#define DEBUG_LED_A_Pin GPIO_PIN_1
#define DEBUG_LED_A_GPIO_Port GPIOB
#define DEBUG_LED_B_Pin GPIO_PIN_2
#define DEBUG_LED_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
