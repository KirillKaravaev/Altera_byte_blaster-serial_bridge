/*
main.c

MIT License

Copyright (c) 2016 Yongqian Tang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include <stdio.h>
#include "base.h"
#include "timebase.h"
#include "led.h"
#include "bitband.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "blaster.h"
#include "adc.h"

/*-----------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;   		//Структура для инициализации пинов

//Чтобы поменять частоту, нужно в папке cmsis/stm32/inc/stm32f10x.h поменять строку #define HSE_VALUE в
//соответствии с установленным кварцем, а также в sys/system_stm32f10x.с поменять SYSCLK_FREQ_XXMHz,
//добавить elsif и написать свою функцию SetSysClockToXX, поменяв в ней строку
// RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9); , где нужно выбрать свой множитель
//RCC_CFGR_PLLMULL9 так, чтобы частота после умножения на него HSE была не более 90 Мгц, иначе USB не заработает,
//так как для него максимальная частота 48 Мгц и максимальный делитель от PLLCLK равен 2.5 . Для его установки
<<<<<<< HEAD
//нужно отредактировать файл  stdperiph/inc/stm32f10x_rcc.h , добавив делители 2 и 2.5 в соответствии с rm (RCC_USBCLKSource_PLLCLK_2Div5), а
=======
//нужно отредактировать файл  stdperiph/inc/stm32f10x_rcc.h , добавив делители 2 и 2.5 в соответствии с rm, а
>>>>>>> 6ae5cb4d0eaf3c4d89de5265e0d51c15cba1dcc8
//также изменить делитель в usb\hw_config.c в функции USB_Clock_Config

//Объявлены в качестве extern в hw_config.h, также там содержатся другие объявления пинов
uint8_t SetupPin = 0;
int LED_counter = 0;
float ADCValue1;
float ADCValue2;

void SetupPinInit(void);					//Настроечный пин, от значения на нем зависит, будет ли устройство
											//функционировать как Com - порт или как Altera Usb Byte Blaster
void BlasterInit(void);

void DE_PinInit(void);						//Пин для полудуплексного режима передачи.В функции EP2_OUT_Callback
										    //выставляется перед началом передачи данных при помощи
											//USB_To_USART_Send_Data и сбрасывается после нее

void POW_PinInit(void);						//2 пина, которые сообщают информацию о возможностях источника питания
											//в соответствии с таблицей ниже
// 	 Напряжение на СС1 или СС2, В   |    Выдаваемый USB-хостом ток, А    |   POW_Pin1   |   POW_Pin2   |
//				  0					|				 ?					 |      0		|		0	   |
//	   	     0.2 - 0.65             |               0.5 				 |		0		|		1	   |
//		     0.66 - 1.22            |               1.5 				 |		1		|		0	   |
//		     1.23 - 2.04 		    |			  	3   				 |		1		|		1	   |

//Случай нулевого напряжения на СС1 и СС2 соответствует подключению кабеля стандарта USB 2.0 и ниже, где нет линий
//СС

int main(void)
{
	ADCInit();
	//Следующий код позволяет последовательно читать разные каналы ADC без DMA
	//Активируем преобразование на первом канале ADC1, ждем завершения преобразования и считываем значение
	ADC1_Ch_Start(ADC_Channel_1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET){};
	ADCValue1 = ADC_GetConversionValue(ADC1)*3.3/4095; //приводим к вольтам.4095 = 2^12 (12 битный ацп).3.3 - Vbat
	//Активируем преобразование на втором канале ADC1, ждем завершения преобразования и считываем значение
	ADC1_Ch_Start(ADC_Channel_2);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET){};
	ADCValue2 = ADC_GetConversionValue(ADC1)*3.3/4095;
	//На всякий случай выключаем АЦП,он нам больше не понадобится
	ADC_DeInit(ADC1);

	//Задавать режим работы можно либо напрямую через пин GPIO0, либо полярностью подключения Type-C
	SetupPinInit();
	SetupPin = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) || (ADCValue1 > 0.2); //Если установлен, то UART



	DE_PinInit();
	POW_PinInit();
	BlasterInit();

	timebase_init();
	LED_init();

    USB_HW_Config();
    USB_Init();

    if((ADCValue1 < 0.2) && (ADCValue2 < 0.2) ){	//Ток хоста неизвестен
        GPIO_ResetBits(GPIOB,POW_Pin1);
        GPIO_ResetBits(GPIOB,POW_Pin2);

    }
    else if((ADCValue1 > 0.2) && (ADCValue1 < 0.65) || (ADCValue2 > 0.2) && (ADCValue2 < 0.65)){
    	GPIO_ResetBits(GPIOB,POW_Pin1);
    	GPIO_SetBits(GPIOB,POW_Pin2);
    }
    else if((ADCValue1 > 0.66) && (ADCValue1 < 1.22) || (ADCValue2 > 0.66) && (ADCValue2 < 1.22)){
    	GPIO_SetBits(GPIOB,POW_Pin1);
    	GPIO_ResetBits(GPIOB,POW_Pin2);
    }
    else if((ADCValue1 > 1.23) && (ADCValue1 < 2.04) || (ADCValue2 > 1.23) && (ADCValue2 < 2.04)){
        GPIO_SetBits(GPIOB,POW_Pin1);
        GPIO_SetBits(GPIOB,POW_Pin2);
    }


    while (1) {
        LED_update(&LED_counter);
        if (bDeviceState == CONFIGURED)
        {
            blaster_exec();
        }
    }
}

/*-----------------------------------*/
void SetupPinInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//Включаем тактирование GPIOA

//	GPIO_StructInit(&GPIO_InitStructure);						//Заполняет поля структуры значениями по умолчанию

	//Заполняем поля структуры нашими параметрами
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;					// Первый вывод порта
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// Скорость на 50Мгц
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;				// Режим "Вход" InputPullDown - IPD
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// Применяем настроки на порт А

//	int PinState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);	//Читаем состояние настроечного пина
}

void DE_PinInit(void){
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//Включаем тактирование GPIOA

	//Заполняем поля структуры нашими параметрами
	GPIO_InitStructure.GPIO_Pin = DE_Pin;						// Первый вывод порта
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// Скорость на 50Мгц
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			// Режим "Выход" Push-Pull - подтягиваем к 0 или 1
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// Применяем настроки на порт А
}

void POW_PinInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//Включаем тактирование GPIOB

	//Заполняем поля структуры нашими параметрами
	GPIO_InitStructure.GPIO_Pin = POW_Pin1;						// Первый вывод порта
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// Скорость на 50Мгц
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			// Режим "Выход" Push-Pull - подтягиваем к 0 или 1
	GPIO_Init(GPIOB, &GPIO_InitStructure);						// Применяем настроки на порт B

	//Заполняем поля структуры нашими параметрами
	GPIO_InitStructure.GPIO_Pin = POW_Pin2;						// Первый вывод порта
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// Скорость на 50Мгц
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			// Режим "Выход" Push-Pull - подтягиваем к 0 или 1
	GPIO_Init(GPIOB, &GPIO_InitStructure);						// Применяем настроки на порт B
}

void BlasterInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// disable JTAG, use SWD only
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	blaster_init();
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1) {
    }
}
#endif //USE_FULL_ASSERT
