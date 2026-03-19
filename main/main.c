#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "joystick.h"

void app_main(void)
{
    // Initialize joystick
    joystick_init();

    while(1){
        car_control_t cmd;
        // Waits for a new snapshot of the PAD state
        if (xQueueReceive(queue, &cmd, portMAX_DELAY)) {
            printf("Sterzo: %ld | Gas (R2): %ld | Freno (L2): %ld | Tasto X: %d\n", 
                    cmd.steer, cmd.throttle, cmd.brake, cmd.action_btn);
            
            // TODO l298n_set_drive_speed() and l298n_set_steer_speed()
        }
    }
}