#ifndef PCF8575_LIFTTUBE_SPILLOIL_OVERHEAT_H
#define PCF8575_LIFTTUBE_SPILLOIL_OVERHEAT_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_idf_lib_helpers.h"
#include "i2cdev.h"
#include "pcf8575.h"
#include <string.h>
#include "PID.h"

#define pcf8575_SDA_NUM 5
#define pcf8575_SCL_NUM 7

#define pcf8575_LIFT_TUBE_NUM 13
#define pcf8575_SPILL_OIL_NUM 14
#define pcf8575_OVER_HEAT_NUM 15

typedef enum liftTube_spillOil_overHeat_state_enum
{
    normal,     /**< Normal state */
    liftTube,   /**< Lift tube state */
    spillOil,   /**< Spill oil state */
    overHeat,   /**< Overheat state */
} liftTube_spillOil_overHeat_state;

enum use_state
{
    demo_mode,          /**< Demo mode state */
    production_mode,    /**< Production mode state */
};

void pcf8575_liftTube_spillOil_overHeat_init();
void pcf8575_liftTube_spillOil_overHeat_task(void *arg);
void state_use_queue_create(void);
enum use_state use_state_read(void);
void use_state_write(enum use_state current_use_state);
liftTube_spillOil_overHeat_state liftTube_spillOil_overHeat_state_write(void);

#endif