#ifndef PCF8575_HEAT_MODE_BUTTON_H
#define PCF8575_HEAT_MODE_BUTTON_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_idf_lib_helpers.h"
#include <string.h>
#include "i2cdev.h"
#include "pcf8575.h"
#include "manual_mode.h"
#include "Count_zero.h"
#include "PID.h"

#define pcf8575_SDA_NUM 5
#define pcf8575_SCL_NUM 7

#define pcf8575_HEAT_NUM 11
#define pcf8575_MODE_NUM 12

typedef enum button_mode
{
    BUTTON_MANUAL_MODE = 0,         /**< 编码器按键弹起状态. Manual mode */
    BUTTON_AUTO_MODE,               /**< 编码器按键按下状态. Auto mode */
    BUTTON_MANUAL_READY_MODE,       /**< Manual ready mode */
    BUTTON_AUTO_READY_MODE,         /**< Auto ready mode */
} button_mode_t;

void pcf8575_BHM_init(void);
void pcf8575_BHM_task(void* arg);

bool pcf8575_read(i2c_dev_t current_pcf8575, uint8_t pcf8575_read_bit, bool pcf8575_read_state);

button_mode_t Mode_change_button_read(void);
void Mode_change_button_write(button_mode_t current_mode);

#endif
