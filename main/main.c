#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "joystick.h"
#include "led.h"
#include "dual_h_bridge.h"

void app_main(void)
{
    // Initialize joystick
    joystick_init();

    // Initialize led
    led_init();

    while(1){
        car_control_t cmd;
        // Waits for a new snapshot of the PAD state
        if (xQueueReceive(queue, &cmd, portMAX_DELAY)) {
            printf("Sterzo: %ld | Gas (R2): %ld | Freno (L2): %ld | Tasto X: %d\n", cmd.steer, cmd.throttle, cmd.brake, cmd.action_btn);
            
            // TEST LED
            if (cmd.brake){
                led_a_on();
            } else {
                led_a_off();
            }

            if(cmd.throttle){
                led_b_on();
            } else {
                led_b_off();
            }
            // END TEST
            
            // TODO l298n_set_drive_speed() and l298n_set_steer_speed()
            set_motor_a_drive((cmd.throttle - cmd.brake) * 103.2);
            set_motor_b_drive(cmd.steer * 2);
        }
    }
}