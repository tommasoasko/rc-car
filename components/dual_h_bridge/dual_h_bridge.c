#include "include/dual_h_bridge.h"
#include <stdlib.h>

void motor_init() {
    // Pin configuration traction motor (A)
    gpio_set_direction(MOT_A_IN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOT_A_IN2, GPIO_MODE_OUTPUT);

    // Pin configuration steering motor (B)
    gpio_set_direction(MOT_B_IN3, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOT_B_IN4, GPIO_MODE_OUTPUT);

    // PWM configuration
    
    // Timer for PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_10_BIT, // 0-1023 resolution
        .freq_hz          = 5000,              // 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Link pin ENA to channel 0 (Traction)
    ledc_channel_config_t ledc_channel_a = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = MOT_A_ENA,
        .duty           = 0, // Not moving at the start
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel_a);

    // Link pin ENB to channel 1 (Steering)
    ledc_channel_config_t ledc_channel_b = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_1,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = MOT_B_ENB,
        .duty           = 0, // Not moving at the start
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel_b);
}

void set_motor_a_drive(int speed) {
    if (speed > 1023) speed = 1023;
    if (speed < -1023) speed = -1023;

    if (speed > 0) {
        // FORWARD
        gpio_set_level(MOT_A_IN1, 1);
        gpio_set_level(MOT_A_IN2, 0);
        
    } else if (speed < 0) {
        // BACKWARD
        gpio_set_level(MOT_A_IN1, 0);
        gpio_set_level(MOT_A_IN2, 1);
        
    } else {
        // Not moving
        gpio_set_level(MOT_A_IN1, 0);
        gpio_set_level(MOT_A_IN2, 0);
    }
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, abs(speed)); 

    // Update duty cycle
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void set_motor_b_drive(int speed) {
    if (speed > 1023) speed = 1023;
    if (speed < -1023) speed = -1023;
    if (speed < 50 && speed > -50) speed = 0;

    if (speed > 0) {
        // FORWARD
        gpio_set_level(MOT_B_IN3, 1);
        gpio_set_level(MOT_B_IN4, 0);
        
    } else if (speed < 0) {
        // BACKWARD
        gpio_set_level(MOT_B_IN3, 0);
        gpio_set_level(MOT_B_IN4, 1);
        
    } else {
        // Not moving
        gpio_set_level(MOT_B_IN3, 0);
        gpio_set_level(MOT_B_IN4, 0);
    }
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, abs(speed)); 

    // Update duty cycle
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
}