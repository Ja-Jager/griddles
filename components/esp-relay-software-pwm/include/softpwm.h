#ifndef _SOFT_PWM_H
#define _SOFT_PWM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include <unistd.h>
#include <stdint.h>
#include "math.h"
#include "PID.h"
#include "driver/gpio.h"

#define NOP() asm volatile("nop") // NOP函数

/**
 * @brief 占空比百分比
 * **/
typedef enum
{
    Percent_0,   /*0%*/
    Percent_10,  /*10%*/
    Percent_20,  /*20%*/
    Percent_30,  /*30%*/
    Percent_40,  /*40%*/
    Percent_50,  /*50%*/
    Percent_60,  /*60%*/
    Percent_70,  /*70%*/
    Percent_80,  /*80%*/
    Percent_90,  /*90%*/
    Percent_100, /*100%*/
} dutyPercent_t;

/**
 * @brief 软件PWM结构体
 * **/
typedef struct softpwm
{
    dutyPercent_t dutypercent; /*占空比百分比*/
    int PWMPin;                /*引脚*/
    float freq;                /*频率*/
} softPwm_t;

/**
 * @brief 初始化PWM
 * @param softpwm 软件PWM结构体
 * **/
void softPwmSetup(softPwm_t *softpwm);

/**
 * @brief PWM写值
 * @param softpwm 软件PWM结构体
 * **/
// void softPwmWrite(softPwm_t *softpwm);

void softpwm_init(softPwm_t *softpwm);

void task_softpwm(void *arg);

#endif // !_SOFT_PWM_H