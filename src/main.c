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

/*-----------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;   		//Структура для инициализации пинов

//Объявлены в качестве extern в hw_config.h, также там содержатся другие объявления пинов
uint8_t SetupPin;
int LED_counter = 0;

void SetupPinInit(void);					//Настроечный пин, от значения на нем зависит, будет ли устройство
											//функционировать как Com - порт или как Altera Usb Byte Blaster
void BlasterInit(void);

void DE_PinInit(void);						//Пин для полудуплексного режима передачи.В функции EP2_OUT_Callback
										    //выставляется перед началом передачи данных при помощи
											//USB_To_USART_Send_Data и сбрасывается после нее
//void CDCInit(void);

int main(void)
{
	SetupPinInit();
	SetupPin = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
//	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
//		CDCInit();
//	else
	DE_PinInit();
	BlasterInit();

	timebase_init();
	LED_init();

    USB_HW_Config();
    USB_Init();

//    led_flash(1000, 100, 0);

    while (1) {
//    	if(LED_counter > 0)
//    		LED_counter--;
//    	else
//    		GPIOC->BRR = GPIO_Pin_13;
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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;					// Первый вывод порта
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

void BlasterInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// disable JTAG��use SWD only
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
