/*
led.c - led driver

MIT License

*/

//#include "base.h"
#include "led.h"

#define LED_PIN_EM				GPIO_Pin_13		//Встроенные(EMbedded) светодиод на плате BLUEPILL
#define GPIO_PORT_EM			GPIOC

#define LED_PIN_R				GPIO_Pin_15			//Красный светодиод
#define GPIO_PORT_R				GPIOB

#define LED_PIN_G				GPIO_Pin_13			//Зеленый светодиод
#define GPIO_PORT_G				GPIOB

//Makros for led ON/OFF
#define LED_ON(GPIO,PIN)        GPIO->BRR = PIN		//Светодиоды подключены к +3.3В, поэтому подача 0 включает их
#define LED_OFF(GPIO,PIN)       GPIO->BSRR = PIN

extern uint8_t SetupPin;

static void LED_gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


    // GPIOC Configuration: Pin 13
    GPIO_InitStructure.GPIO_Pin =  LED_PIN_EM;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_PORT_EM, &GPIO_InitStructure);

    // GPIOB Configuration: Pin 13
    GPIO_InitStructure.GPIO_Pin =  LED_PIN_G;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_PORT_G, &GPIO_InitStructure);

    if(SetupPin){
    // GPIOB Configuration: Pin 15
    GPIO_InitStructure.GPIO_Pin =  LED_PIN_R;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_PORT_R, &GPIO_InitStructure);
    }



}

/*-----------------------------------*/
//Далее переключаем все пины, но при этом работать будут только проинициализированные
void LED_init(void)
{
    LED_gpio_config();
    LED_ON(GPIO_PORT_EM,LED_PIN_EM);
    LED_ON(GPIO_PORT_G,LED_PIN_G);
    LED_ON(GPIO_PORT_R,LED_PIN_R);

}

void LED_update(int *LED_counter){
	if(*LED_counter > 0)
		(*LED_counter)--;
	else{
		LED_ON(GPIO_PORT_EM,LED_PIN_EM);
		LED_ON(GPIO_PORT_G,LED_PIN_G);
		LED_ON(GPIO_PORT_R,LED_PIN_R);
	}
}
void LED_blink(int *LED_counter, int blink_time){  //blink_time in ms, but it work correctly only with blink_time = 1-10
	LED_OFF(GPIO_PORT_EM,LED_PIN_EM);
	LED_OFF(GPIO_PORT_G,LED_PIN_G);
	LED_OFF(GPIO_PORT_R,LED_PIN_R);
	*LED_counter = SystemCoreClock*blink_time/1000;
}

