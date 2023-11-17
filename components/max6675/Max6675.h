#ifndef MAIN_MAX6675_H_
#define MAIN_MAX6675_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#define F_CPU 8000000 /* 定义时钟频率为 8Mhz */

/* 数码管短线、字母与段码在数组中的对应关系 */
#define dis_F 16
#define dis_C 17

/* 读数偏移修正 */
#define TEM_FIX 70

/* 需要用到的引脚 */
#define CSA 15
#define SCK 16
#define MDIO 14

/* 设置片选信号 CSn 和时钟信号 SCK 对应引脚为输出状态 */
/* 设置数据信号 MDIO 对应引脚为输入状态 */
#define TEM_CSA_OUT gpio_set_direction(CSA, GPIO_MODE_OUTPUT)
#define TEM_SCK_OUT gpio_set_direction(SCK, GPIO_MODE_OUTPUT)
#define TEM_MDIO_IN gpio_set_direction(MDIO, GPIO_MODE_INPUT)

/* 设置数据信号 MDIO 对应引脚为拉高状态 */
#define TEM_MDIO_PULL gpio_set_pull_mode(MDIO, GPIO_PULLUP_ONLY)

#define MAX6675_TAG "MAX6675"

void NTC_thermistor_queue_write(double temperature);
double NTC_thermistor_queue_read(void); // 从队列读

void NTC_thermistor_calibration_queue_write(int calibration_value);
int NTC_thermistor_calibration_queue_read(void);

void Max6675_init(void); /* Max6675 初始化函数 */

#endif /* MAIN_MAX6675_H_ */
