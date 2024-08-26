/**
  ******************************************************************************
  * @file    hw_config.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "usb_type.h"
#include "stm32f10x_usart.h"
//#include "led.h"
#include <stdbool.h>


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint8_t SetupPin;
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define MASS_MEMORY_START     		0x04002000
#define BULK_MAX_PACKET_SIZE  		0x00000040
//#define LED_ON                		0xF0
//#define LED_OFF               		0xFF

#define DE_Pin						GPIO_Pin_8

#define POW_Pin1					GPIO_Pin_10
#define POW_Pin2					GPIO_Pin_11

#define USART_RX_DATA_SIZE    		2048

#define USART_1						//choose usart. При смене юсарта также нужно в файле stm32_it.c поменять
									//название функции USART1_IRQHandler(void) -> USARTn_IRQHandler(void)
									//где n - выбранный номер юсарта
//#define USART_2
//#define USART_3

/*-------------------------------------------USART DEFINES-----------------------------------------------------*/
#ifdef USART_1

#	define USART 			  		USART1
#	define USART_IRQn		  		USART1_IRQn
#	define USART_CLK		  		RCC_APB2Periph_USART1
#	define USART_TX_RX_GPIO_CLK	    RCC_AHBPeriph_GPIOA

#	define USART_TX_RX_GPIO_PORT	GPIOA
#	define USART_TX_PIN				GPIO_Pin_9
#	define USART_RX_PIN				GPIO_Pin_10
#	define USART_TX_GPIO_SOURCE		GPIO_PinSource9
#	define USART_RX_GPIO_SOURCE		GPIO_PinSource10


//#	define USART_TX_AF				GPIO_AF_
//#	define USART_RX_AF				GPIO_AF_

#endif

#ifdef USART_2

#	define USART 			  		USART2
#	define USART_IRQn		  		USART2_IRQn
#	define USART_CLK		  		RCC_APB1Periph_USART2
#	define USART_TX_RX_GPIO_CLK	    RCC_AHBPeriph_GPIOA

#	define USART_TX_RX_GPIO_PORT	GPIOA
#	define USART_TX_PIN				GPIO_Pin_2
#	define USART_RX_PIN				GPIO_Pin_3
#	define USART_TX_GPIO_SOURCE		GPIO_PinSource2
#	define USART_RX_GPIO_SOURCE		GPIO_PinSource3

#endif

#ifdef USART_3

#	define USART 			  		USART3
#	define USART_IRQn		  		USART3_IRQn
#	define USART_CLK		  		RCC_APB1Periph_USART3
#	define USART_TX_RX_GPIO_CLK	    RCC_AHBPeriph_GPIOB

#	define USART_TX_RX_GPIO_PORT	GPIOB
#	define USART_TX_PIN				GPIO_Pin_10
#	define USART_RX_PIN				GPIO_Pin_11
#	define USART_TX_GPIO_SOURCE		GPIO_PinSource10
#	define USART_RX_GPIO_SOURCE		GPIO_PinSource11

#endif

/*--------------------------------------------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void USB_HW_Config(void);
void USB_Clock_Config(void);
void USB_Interrupts_Config(void);
void USB_GPIO_Config(void);
void USB_EXTI_Config(void);

void USART_Config_Default(void);
bool USART_Config(void);
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes);
void USART_To_USB_Send_Data(void);
void Handle_USBAsynchXfer (void);
void STM_USART_Init(USART_InitTypeDef* USART_InitStruct);

void USB_Cable_Ctrl(FunctionalState NewState);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);

void Get_SerialNum(void);

#endif  /*__HW_CONFIG_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
