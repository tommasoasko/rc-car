#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

// typedef enum {
//     CROSS,
//     CIRCLE,
//     SQUARE,
//     TRIANGLE,
//     D_PAD_UP,
//     D_PAD_DOWN,
//     D_PAD_LEFT,
//     D_PAD_RIGHT,
//     R1,
//     R2,
//     L1,
//     L2,
//     R3_STICK,
//     R3_BUTTON,
//     L3_STICK,
//     L3_BUTTON
//     SHARE,
//     OPTION,
// } joystick_event_t;

typedef struct {
    int32_t steer;       // Left stick (from -512 to +511)
    int32_t throttle;    // Trigger R2 (from 0 to 1023)
    int32_t brake;       // Trigger L2 (from 0 to 1023)
    bool action_btn; // X button (lights maybe???)
} car_control_t;

extern QueueHandle_t queue;

void joystick_init(void);

#endif // JOYSTICK_H