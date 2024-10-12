/*
led.h

MIT License

Copyright (c) 2016 Yongqian Tang

*/
#ifndef __LED_H__
#define __LED_H__

#define BLASTER_RG									//Индикатор бластера - оранжевый светодиод
//#define BLASTER_G									//Индикатор бластера - зеленый светодиод

#define LED_PIN_EM				GPIO_Pin_13			//Встроенные(EMbedded) светодиод на плате BLUEPILL
#define GPIO_PORT_EM			GPIOC

#define LED_PIN_R				GPIO_Pin_15			//Красный светодиод
#define GPIO_PORT_R				GPIOB

#define LED_PIN_G				GPIO_Pin_13			//Зеленый светодиод
#define GPIO_PORT_G				GPIOB

//Makros for led ON/OFF
#define LED_ON(GPIO,PIN)        GPIO->BRR = PIN		//Светодиоды подключены к +3.3В, поэтому подача 0 включает их
#define LED_OFF(GPIO,PIN)       GPIO->BSRR = PIN

#include "base.h"

void LED_init(void);

void LED_update(int *LED_counter);

void LED_blink(int *LED_counter, int blink_time);

#endif //__LED_H__
