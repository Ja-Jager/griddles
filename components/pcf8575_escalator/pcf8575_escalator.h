#ifndef PCF8575_ESCALATOR_H
#define PCF8575_ESCALATOR_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_idf_lib_helpers.h"
#include <string.h>
#include "i2cdev.h"
#include "pcf8575.h"
#include "PID.h"
#include "manual_mode.h"
#include "Count_zero.h"

#define pcf8575_SDA_NUM 5
#define pcf8575_SCL_NUM 7

// 右边升降机
#define pcf8575_ESCALATOR_A_NUM 6
#define pcf8575_ESCALATOR_B_NUM 7
// 左边升降机
#define pcf8575_ESCALATOR_C_NUM 8
#define pcf8575_ESCALATOR_D_NUM 9

typedef enum Motor_Left_Right_enum
{
    motor_left,
    motor_right,
    motor_both,
} Motor_Left_Right;

void pcf8575_escalator_init(void);
void pcf8575_escalator_task(void* arg);

Motor_Left_Right motor_left_right_queue_read(void);
void motor_left_right_queue_write(Motor_Left_Right current_motor_left_right);

#endif
