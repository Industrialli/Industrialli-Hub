/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define LOW 0
#define HIGH 1

#define SPI4_SCK_PE2_Pin GPIO_PIN_2
#define SPI4_SCK_PE2_GPIO_Port GPIOE
#define ISO_DIS_PE3_Pin GPIO_PIN_3
#define ISO_DIS_PE3_GPIO_Port GPIOE
#define SPI4_NSS_PE4_Pin GPIO_PIN_4
#define SPI4_NSS_PE4_GPIO_Port GPIOE
#define SPI4_MISO_PE5_Pin GPIO_PIN_5
#define SPI4_MISO_PE5_GPIO_Port GPIOE
#define SPI4_MOSI_PE6_Pin GPIO_PIN_6
#define SPI4_MOSI_PE6_GPIO_Port GPIOE
#define DEBUG_RTC_OUT_ALARM_Pin GPIO_PIN_13
#define DEBUG_RTC_OUT_ALARM_GPIO_Port GPIOC
#define IC1_ISO_DIAG_PC0_Pin GPIO_PIN_0
#define IC1_ISO_DIAG_PC0_GPIO_Port GPIOC
#define IC2_ISO_DIAG_PC1_Pin GPIO_PIN_1
#define IC2_ISO_DIAG_PC1_GPIO_Port GPIOC
#define PGOOD1_PC2_C_Pin GPIO_PIN_2
#define PGOOD1_PC2_C_GPIO_Port GPIOC
#define PGOOD2_PC3_C_Pin GPIO_PIN_3
#define PGOOD2_PC3_C_GPIO_Port GPIOC
#define ADC_04_PA0_Pin GPIO_PIN_0
#define ADC_04_PA0_GPIO_Port GPIOA
#define OCTOSPIM_P1_IO3_Pin GPIO_PIN_1
#define OCTOSPIM_P1_IO3_GPIO_Port GPIOA
#define OCTOSPIM_P1_IO0_Pin GPIO_PIN_2
#define OCTOSPIM_P1_IO0_GPIO_Port GPIOA
#define OCTOSPIM_P1_IO2_Pin GPIO_PIN_3
#define OCTOSPIM_P1_IO2_GPIO_Port GPIOA
#define SPI1_NSS_PA4_Pin GPIO_PIN_4
#define SPI1_NSS_PA4_GPIO_Port GPIOA
#define SPI1_SCK_PA5_Pin GPIO_PIN_5
#define SPI1_SCK_PA5_GPIO_Port GPIOA
#define SPI1_MISO_PA6_Pin GPIO_PIN_6
#define SPI1_MISO_PA6_GPIO_Port GPIOA
#define SPI1_MOSI_PA7_Pin GPIO_PIN_7
#define SPI1_MOSI_PA7_GPIO_Port GPIOA
#define ADC_03_PC4_Pin GPIO_PIN_4
#define ADC_03_PC4_GPIO_Port GPIOC
#define ADC_02_PC5_Pin GPIO_PIN_5
#define ADC_02_PC5_GPIO_Port GPIOC
#define OCTOSPIM_P1_IO1_Pin GPIO_PIN_0
#define OCTOSPIM_P1_IO1_GPIO_Port GPIOB
#define ADC_01_PB1_Pin GPIO_PIN_1
#define ADC_01_PB1_GPIO_Port GPIOB
#define OCTOSPIM_P1_CLK_Pin GPIO_PIN_2
#define OCTOSPIM_P1_CLK_GPIO_Port GPIOB
#define RS485_MOD_UART7_RX_PE7_Pin GPIO_PIN_7
#define RS485_MOD_UART7_RX_PE7_GPIO_Port GPIOE
#define RS485_MOD_UART7_TX_PE8_Pin GPIO_PIN_8
#define RS485_MOD_UART7_TX_PE8_GPIO_Port GPIOE
#define RS485_MOD_UART7_DE_PE9_Pin GPIO_PIN_9
#define RS485_MOD_UART7_DE_PE9_GPIO_Port GPIOE
#define RS485_TER_SEL_PE10_Pin GPIO_PIN_10
#define RS485_TER_SEL_PE10_GPIO_Port GPIOE
#define OCTOSPIM_P1_NCS_Pin GPIO_PIN_11
#define OCTOSPIM_P1_NCS_GPIO_Port GPIOE
#define EXTI_04_PE12_Pin GPIO_PIN_12
#define EXTI_04_PE12_GPIO_Port GPIOE
#define EXTI_03_PE13_Pin GPIO_PIN_13
#define EXTI_03_PE13_GPIO_Port GPIOE
#define EXTI_02_PE14_Pin GPIO_PIN_14
#define EXTI_02_PE14_GPIO_Port GPIOE
#define EXTI_01_PE15_Pin GPIO_PIN_15
#define EXTI_01_PE15_GPIO_Port GPIOE
#define DEBUG_LED_PB10_Pin GPIO_PIN_10
#define DEBUG_LED_PB10_GPIO_Port GPIOB
#define LORA_GPIO_PB11_Pin GPIO_PIN_11
#define LORA_GPIO_PB11_GPIO_Port GPIOB
#define SPI2_NSS_PB12_Pin GPIO_PIN_12
#define SPI2_NSS_PB12_GPIO_Port GPIOB
#define SPI2_SCK_PB13_Pin GPIO_PIN_13
#define SPI2_SCK_PB13_GPIO_Port GPIOB
#define SPI2_MISO_PB14_Pin GPIO_PIN_14
#define SPI2_MISO_PB14_GPIO_Port GPIOB
#define SPI2_MOSI_PB15_Pin GPIO_PIN_15
#define SPI2_MOSI_PB15_GPIO_Port GPIOB
#define NEXTION_USART3_TX_PD8_Pin GPIO_PIN_8
#define NEXTION_USART3_TX_PD8_GPIO_Port GPIOD
#define NEXTION_USART3_RX_PD9_Pin GPIO_PIN_9
#define NEXTION_USART3_RX_PD9_GPIO_Port GPIOD
#define DIP_01_PD10_Pin GPIO_PIN_10
#define DIP_01_PD10_GPIO_Port GPIOD
#define DIP_03_PD11_Pin GPIO_PIN_11
#define DIP_03_PD11_GPIO_Port GPIOD
#define I2C4_SCL_PD12_Pin GPIO_PIN_12
#define I2C4_SCL_PD12_GPIO_Port GPIOD
#define I2C4_SDA_PD13_Pin GPIO_PIN_13
#define I2C4_SDA_PD13_GPIO_Port GPIOD
#define DIP_02_PD14_Pin GPIO_PIN_14
#define DIP_02_PD14_GPIO_Port GPIOD
#define BUZZER_PD15_Pin GPIO_PIN_15
#define BUZZER_PD15_GPIO_Port GPIOD
#define LORA_USART6_TX_PC6_Pin GPIO_PIN_6
#define LORA_USART6_TX_PC6_GPIO_Port GPIOC
#define LORA_USART6_RX_PC7_Pin GPIO_PIN_7
#define LORA_USART6_RX_PC7_GPIO_Port GPIOC
#define SDMMC1_D0_Pin GPIO_PIN_8
#define SDMMC1_D0_GPIO_Port GPIOC
#define SDMMC1_D1_Pin GPIO_PIN_9
#define SDMMC1_D1_GPIO_Port GPIOC
#define DIP_04_PA8_Pin GPIO_PIN_8
#define DIP_04_PA8_GPIO_Port GPIOA
#define ANLG_SEL_01_PA9_Pin GPIO_PIN_9
#define ANLG_SEL_01_PA9_GPIO_Port GPIOA
#define ANLG_SEL_02_PA10_Pin GPIO_PIN_10
#define ANLG_SEL_02_PA10_GPIO_Port GPIOA
#define CARD_DETECT_PA15_Pin GPIO_PIN_15
#define CARD_DETECT_PA15_GPIO_Port GPIOA
#define ANLG_SEL_03_PD0_Pin GPIO_PIN_0
#define ANLG_SEL_03_PD0_GPIO_Port GPIOD
#define ANLG_SEL_04_PD1_Pin GPIO_PIN_1
#define ANLG_SEL_04_PD1_GPIO_Port GPIOD
#define W5500_INT_PD3_Pin GPIO_PIN_3
#define W5500_INT_PD3_GPIO_Port GPIOD
#define RS485_USART2_DE_PD4_Pin GPIO_PIN_4
#define RS485_USART2_DE_PD4_GPIO_Port GPIOD
#define RS485_USART2_TX_PD5_Pin GPIO_PIN_5
#define RS485_USART2_TX_PD5_GPIO_Port GPIOD
#define RS485_USART2_RX_PD6_Pin GPIO_PIN_6
#define RS485_USART2_RX_PD6_GPIO_Port GPIOD
#define W5500_RST_PD7_Pin GPIO_PIN_7
#define W5500_RST_PD7_GPIO_Port GPIOD
#define EXTI_05_PB4_Pin GPIO_PIN_4
#define EXTI_05_PB4_GPIO_Port GPIOB
#define EXTI_06_PB5_Pin GPIO_PIN_5
#define EXTI_06_PB5_GPIO_Port GPIOB
#define EXTI_07_PB6_Pin GPIO_PIN_6
#define EXTI_07_PB6_GPIO_Port GPIOB
#define EXTI_08_PB7_Pin GPIO_PIN_7
#define EXTI_08_PB7_GPIO_Port GPIOB
#define I2C1_SCL_PB8_Pin GPIO_PIN_8
#define I2C1_SCL_PB8_GPIO_Port GPIOB
#define I2C1_SDA_PB9_Pin GPIO_PIN_9
#define I2C1_SDA_PB9_GPIO_Port GPIOB
#define LORA_UART8_RX_PE0_Pin GPIO_PIN_0
#define LORA_UART8_RX_PE0_GPIO_Port GPIOE
#define LORA_UART8_TX_PE1_Pin GPIO_PIN_1
#define LORA_UART8_TX_PE1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
