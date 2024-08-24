/*
led.h

MIT License

Copyright (c) 2016 Yongqian Tang

*/
#ifndef __LED_H__
#define __LED_H__

#include "base.h"

void LED_init(void);

void LED_update(int *LED_counter);

void LED_blink(int *LED_counter, int blink_time);

#endif //__LED_H__
