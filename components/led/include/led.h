#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

#define LED_A_PIN GPIO_NUM_2
#define LED_B_PIN GPIO_NUM_4

void led_init();
void led_a_on();
void led_a_off();
void led_b_on();
void led_b_off();

// void toggle_led_b();

#endif