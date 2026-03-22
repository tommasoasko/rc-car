#ifndef DUAL_H_BRIDGE_H
#define DUAL_H_BRIDGE_H

#include "driver/gpio.h"
#include "driver/ledc.h" // Library for PWM signal 

// Pins for Motor A (Traction)
#define MOT_A_IN1 GPIO_NUM_26
#define MOT_A_IN2 GPIO_NUM_27
#define MOT_A_ENA GPIO_NUM_14 // Pin PWM

// Pins for Motor B (Steer)
#define MOT_B_IN3 GPIO_NUM_32
#define MOT_B_IN4 GPIO_NUM_33
#define MOT_B_ENB GPIO_NUM_25 // Pin PWM

void motor_init();
void set_motor_a_drive(int speed);
void set_motor_b_drive(int speed);

#endif