/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_system.h"
#include "freertos/queue.h"
#include "joystick.h"

void app_main(void)
{
    while(1){
        joystick_dir_t dir;
        xQueueReceive(queue, &dir, portMAX_DELAY);
        switch (dir)
        {
        case CENTER:
            printf("CENTER\n");
            break;
        case UP:
            printf("UP\n");
            break;
        case DOWN:
            printf("DOWN\n");
            break;
        case LEFT:
            printf("LEFT\n");
            break;
        case RIGHT:
            printf("RIGHT\n");
            break;
        default:
            break;
        }
    }
}
