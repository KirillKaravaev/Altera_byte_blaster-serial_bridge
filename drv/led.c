/*
led.c - led driver

MIT License

*/

#include "led.h"

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


    // GPIOB Configuration: Pin 15
    GPIO_InitStructure.GPIO_Pin =  LED_PIN_R;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_PORT_R, &GPIO_InitStructure);

}

/*-----------------------------------*/
//Далее переключаем все пины, но при этом работать будут только проинициализированные
void LED_init(void)
{
    LED_gpio_config();
    LED_ON(GPIO_PORT_EM,LED_PIN_EM);
    LED_ON(GPIO_PORT_G,LED_PIN_G);
#if defined(BLASTER_RG)
    if(SetupPin)							//SetupPin = 1 для USB-UART преобразователя
    	LED_OFF(GPIO_PORT_R,LED_PIN_R);
	else
		LED_ON(GPIO_PORT_R,LED_PIN_R);

#elif defined (BLASTER_G)
    if(SetupPin)
        LED_ON(GPIO_PORT_R,LED_PIN_R);
    else
    	LED_OFF(GPIO_PORT_R,LED_PIN_R);
#endif

}

void LED_update(int *LED_counter){
	if(*LED_counter > 0)
		(*LED_counter)--;
	else{
		LED_ON(GPIO_PORT_EM,LED_PIN_EM);
		LED_ON(GPIO_PORT_G,LED_PIN_G);
#if defined(BLASTER_RG)
		if(SetupPin)
			LED_OFF(GPIO_PORT_R,LED_PIN_R);
		else
			LED_ON(GPIO_PORT_R,LED_PIN_R);

#elif defined (BLASTER_G)
		if(SetupPin)
			LED_ON(GPIO_PORT_R,LED_PIN_R);
		else
			LED_OFF(GPIO_PORT_R,LED_PIN_R);
#endif
	}
}
void LED_blink(int *LED_counter, int blink_time){  //blink_time in ms, but it work correctly only with blink_time = 1-10
	LED_OFF(GPIO_PORT_EM,LED_PIN_EM);
	LED_OFF(GPIO_PORT_G,LED_PIN_G);
	LED_OFF(GPIO_PORT_R,LED_PIN_R);
	*LED_counter = SystemCoreClock*blink_time/1000;
}

