#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "joystick.h"

// Bluetooth e Bluepad32 libraries
#include <uni.h>
#include <btstack_port_esp32.h>
#include <btstack_run_loop.h>

QueueHandle_t queue;

// Bluepad32 functions

static void my_platform_init(int argc, const char** argv) {}

static void my_platform_on_init_complete(void) {
    uni_bt_enable_new_connections_safe(true); // deprecated -> form bluepad32 4.2 it is automatic
}

static void my_platform_on_device_connected(uni_hid_device_t* d) {
    printf("[PS4] Controller connectet!\n");
}

static void my_platform_on_device_disconnected(uni_hid_device_t* d) {
    printf("[PS4] Controller disconnected!\n");
}

static uni_error_t my_platform_on_device_ready(uni_hid_device_t *d) {
    printf("[PS4] Controller ready to use!\n");
    return 0;
}

static void my_platform_on_oob_event(uni_platform_oob_event_t event, void* data) {}

static const uni_property_t* my_platform_get_properties(uni_property_idx_t idx) {
    return NULL; 
}

// Data reading

/// @brief This function is automatically called when the controller is touched, it captures
/// the button pressed or stick moved and sends the event to the queue.
/// @param d physical device
/// @param ctl logic controller
static void my_platform_on_controller_data(uni_hid_device_t* d, uni_controller_t* ctl) {
    uni_gamepad_t *gp = &ctl->gamepad;

    // Current state snapshot
    car_control_t current_state;
    
    // Steer (L3 stick)
    current_state.steer = gp->axis_x; // axis_x: min = -511, max = +512       
    
    // Throttle (R2)
    int32_t normalized_throttle = (gp->throttle) / 103.2;
    current_state.throttle = normalized_throttle; // throttle: min = 0, max = 1023

    // Brake (L2)
    int32_t normalized_brake = (gp->brake) / 103.2;
    current_state.brake = normalized_brake; // brake: min = 0, max = 1023
    
    // Lights (X button) TODO
    current_state.action_btn = (gp->buttons & BUTTON_A) ? true : false;

    // default state
    static car_control_t last_state = {0, 0, 0, false};
    
    // Deadzone filter to remove noise
    // if (abs(current_state.steer) < 15) current_state.steer = 0;
    // if (current_state.throttle < 5) current_state.throttle = 0;
    // if (current_state.brake < 5) current_state.brake = 0;

    if (current_state.steer != last_state.steer || 
        current_state.throttle != last_state.throttle ||
        current_state.brake != last_state.brake ||
        current_state.action_btn != last_state.action_btn) 
    {
        // Send the struct to the queue
        xQueueSend(queue, &current_state, pdMS_TO_TICKS(0));
        last_state = current_state; // Refresh state
    }
}

// Bluepad32 configuration
static struct uni_platform my_platform = {
    .name = "RC Car",
    .init = my_platform_init,
    .on_init_complete = my_platform_on_init_complete,
    .on_device_connected = my_platform_on_device_connected,
    .on_device_disconnected = my_platform_on_device_disconnected,
    .on_device_ready = my_platform_on_device_ready,
    .on_oob_event = my_platform_on_oob_event,
    .on_controller_data = my_platform_on_controller_data,
    .get_property = my_platform_get_properties,
};

struct uni_platform* get_my_platform(void) {
    return &my_platform;
}

// Bluetooth task
void joystick_task(void *args) {
    // Initialize bluetooth antenna
    btstack_init();
    uni_platform_set_custom(get_my_platform());
    uni_init(0, NULL);
    
    btstack_run_loop_execute();
}

void joystick_init(void) {
    queue = xQueueCreate(10, sizeof(car_control_t));
    
    xTaskCreate(joystick_task, "ps4_task", 4096, NULL, 5, NULL);
}