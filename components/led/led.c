#include "include/led.h"

// Initialization function (pin configuration)
void led_init(){
    // Configure Pin 2 for LED A
    gpio_reset_pin(LED_A_PIN);
    gpio_set_direction(LED_A_PIN, GPIO_MODE_OUTPUT);

    // Configure Pin 4 for LED B
    gpio_reset_pin(LED_B_PIN);
    gpio_set_direction(LED_B_PIN, GPIO_MODE_OUTPUT);
}


void led_a_on(){
    gpio_set_level(LED_A_PIN, 1);
}

void led_a_off(){
    gpio_set_level(LED_A_PIN, 0);
}

void led_b_on(){
    gpio_set_level(LED_B_PIN, 1);
}

void led_b_off(){
    gpio_set_level(LED_B_PIN, 0);
}
