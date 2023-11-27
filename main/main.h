/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_log.h"
#include "bsp/ws_7inch.h"
#include "lvgl.h"
#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "Count_zero.h"
#include "manual_mode.h"
// #include "NTC_thermistor.h"
#include "Max6675.h"
#include "PID.h"
// #include "pwm.h"
// #include "menu.h"
#include "math.h"
#include "stdio.h"
#include "nvs_component.h"
#include "rotary_encoder.h"
#include "encoder.h"
#include "lvgl_indev_port.h"
#include "lvgl.h"
#include "demos/benchmark/lv_demo_benchmark.h"
#include "esp_heap_caps.h"
#include "softpwm.h"
#include "cJSON.h"
#include "ui_events.c"
#include "buzzer.h"
// #include "lv_example_textarea_3.c"
// #include "lv_example_textarea_1.c"
// #include "lv_example_keyboard_1.c"

#undef LVGL_BENCHMARK

#define TAG "ESP-EXAMPLE"
#define VERSION_NUMBER "v1.2.2"

/*******************************************************************************
 * Private functions
 *******************************************************************************/

/**
 * @brief Create lv_timer, update temperature from rotary encoder
 */
void UI_task(void *pvParameters);

// *INDENT-OFF*

/**
 * @brief Init UI
 */
void app_lvgl_display(void);

/**
 * @brief Update temperature sensor to screen label
 */
void NTC_thermistor_update_UI(lv_timer_t *timer);

void msgbox_timer_mode_drop_callback(lv_event_t * e);

/**
 * @brief Update manual mode's countdown time label on screen
 */
void manual_mode_countdown_update_UI(lv_timer_t *timer);

/**
 * @brief Monitor memory using heap information API
 */
void memory_monitor_task(void *pvParameters);

/**
 * @brief Calculate heap size
 */
uint32_t getHeapSize(void);

typedef enum screen_is_loaded
{
    Manual_Loaded = 0, 
    Auto_Loaded,    
    Setting_Loaded,
    No_loaded
} screen_is_loaded_t;

void my_ScreenAuto_cb(lv_event_t *e);

void my_ScreenManual_cb(lv_event_t *e);

void my_ScreenSetting_cb(lv_event_t *e);

void set_language_by_nvs_for_power_on(void);
